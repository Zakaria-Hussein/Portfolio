#define _USE_MATH_DEFINES
#include "Drone.h"

#include <cmath>
#include <iostream>
#include <limits>

#include "AstarStrategy.h"
#include "BatteryDecorator.h"
#include "BeelineStrategy.h"
#include "DfsStrategy.h"
#include "DijkstraStrategy.h"
#include "JumpDecorator.h"
#include "SpinDecorator.h"

Drone::Drone(JsonObject& obj) : details(obj) {
  JsonArray pos(obj["position"]);
  position = {pos[0], pos[1], pos[2]};

  JsonArray dir(obj["direction"]);
  direction = {dir[0], dir[1], dir[2]};

  speed = obj["speed"];

  available = true;
}

Drone::~Drone() {
  // Delete dynamically allocated variables
}

void Drone::GetNearestEntity(std::vector<IEntity*> scheduler,
                             std::vector<IEntity*> rechargeStations) {
  float minDis = std::numeric_limits<float>::max();
  for (auto entity : scheduler) {
    if (entity->GetAvailability()) {
      float disToEntity = this->position.Distance(entity->GetPosition());
      if (disToEntity <= minDis) {
        minDis = disToEntity;
        nearestEntity = entity;
      }
    }
  }

  if (nearestEntity) {
    nearestEntity->SetAvailability(
        false);  // set availability to the nearest entity
    available = false;
    pickedUp = false;

    destination = nearestEntity->GetPosition();
    toTargetPosStrategy = new BeelineStrategy(this->GetPosition(), destination);
    toTargetPosStrategy = new BatteryDecorator(toTargetPosStrategy, NULL,
                                               charge, rechargeStations);

    std::string targetStrategyName = nearestEntity->GetStrategyName();
    if (targetStrategyName.compare("astar") == 0) {
      toTargetDestStrategy = new AstarStrategy(
          nearestEntity->GetPosition(), nearestEntity->GetDestination(), graph);
      toTargetDestStrategy = new SpinDecorator(toTargetDestStrategy);
    } else if (targetStrategyName.compare("dfs") == 0) {
      toTargetDestStrategy = new DfsStrategy(
          nearestEntity->GetPosition(), nearestEntity->GetDestination(), graph);
      toTargetDestStrategy = new JumpDecorator(toTargetDestStrategy);
    } else if (targetStrategyName.compare("dijkstra") == 0) {
      toTargetDestStrategy = new DijkstraStrategy(
          nearestEntity->GetPosition(), nearestEntity->GetDestination(), graph);
      toTargetDestStrategy = new SpinDecorator(toTargetDestStrategy);
      toTargetDestStrategy = new JumpDecorator(toTargetDestStrategy);
    }
    toTargetDestStrategy = new BatteryDecorator(
        toTargetDestStrategy, nearestEntity, charge, rechargeStations);
  }
}

void Drone::Update(double dt, std::vector<IEntity*> scheduler,
                   std::vector<IEntity*> rechargeStations) {
  if (available) {  // drone is on standby
    GetNearestEntity(scheduler, rechargeStations);
  }

  if (toTargetPosStrategy) {
    if (toTargetRandomStrategy) {
      charge = toTargetRandomStrategy->GetCharge();
      delete toTargetRandomStrategy;
      toTargetRandomStrategy = NULL;
    }
    // std::cout << "Drone to Robot move" << std::endl;
    // std::cout << "beeline" << std::endl;
    toTargetPosStrategy->Move(this, dt);
    if (toTargetPosStrategy->IsCompleted()) {
      charge = toTargetPosStrategy->GetCharge();
      toTargetDestStrategy->SetCharge(charge);
      delete toTargetPosStrategy;
      toTargetPosStrategy = NULL;
    }
  } else if (toTargetDestStrategy) {
    // std::cout << "Drone & Robot move" << std::endl;
    if (toTargetRandomStrategy) {
      // charge = toTargetRandomStrategy->GetCharge();
      delete toTargetRandomStrategy;
      toTargetRandomStrategy = NULL;
    }
    std::cout << nearestEntity->GetStrategyName() << std::endl;
    toTargetDestStrategy->Move(this, dt);

    // Moving the robot
    nearestEntity->SetPosition(this->GetPosition());
    nearestEntity->SetDirection(this->GetDirection());
    if (toTargetDestStrategy->IsCompleted()) {
      charge = toTargetDestStrategy->GetCharge();
      delete toTargetDestStrategy;
      toTargetDestStrategy = NULL;
      available = true;
      nearestEntity = NULL;
    }
  }
  if (toTargetRandomStrategy) {  // this makes drone fly around when there are
                                 // no new robots
    // std::cout << "Random move" << std::endl;
    // std::cout << "beeline" << std::endl;
    toTargetRandomStrategy->Move(this, dt);

    if (toTargetRandomStrategy->IsCompleted()) {
      charge = toTargetRandomStrategy->GetCharge();
      delete toTargetRandomStrategy;
      toTargetRandomStrategy = NULL;
    }
  } else {
    srand(unsigned(time(NULL)));
    float newx = rand_r() % 2900 - 1400;
    float newy = 270;
    float newz = rand_r() % 1600 - 800;
    this->SetDestination(Vector3(newx, newy, newz));
    toTargetRandomStrategy =
        new BeelineStrategy(this->GetPosition(), destination);
    toTargetRandomStrategy = new BatteryDecorator(toTargetRandomStrategy, NULL,
                                                  charge, rechargeStations);
  }
}

void Drone::Rotate(double angle) {
  Vector3 dirTmp = direction;
  direction.x = dirTmp.x * std::cos(angle) - dirTmp.z * std::sin(angle);
  direction.z = dirTmp.x * std::sin(angle) + dirTmp.z * std::cos(angle);
}

void Drone::Jump(double height) {
  if (goUp) {
    position.y += height;
    jumpHeight += height;
    if (jumpHeight > 5) {
      goUp = false;
    }
  } else {
    position.y -= height;
    jumpHeight -= height;
    if (jumpHeight < 0) {
      goUp = true;
    }
  }
}

void Drone::SetColor(float charge) {
  if (charge <= 101.0 && charge > 60.0) {
    color = "#33FF3F";
  } else if (charge <= 60.0 && charge > 40.0) {
    color = "#CAFF33";
  } else if (charge <= 40.0 && charge > 20.0) {
    color = "#FFCE33";
  } else if (charge <= 20.0 && charge > 10.0) {
    color = "#FF9C33";
  } else if (charge > 0.0) {
    color = "#FF4633";
  } else {
    color = "#000000";
  }
}
