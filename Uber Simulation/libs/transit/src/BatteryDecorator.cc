#include "BatteryDecorator.h"

#include <iostream>

BatteryDecorator::BatteryDecorator(IStrategy *strategy_, IEntity *robot_,
                                   float charge_,
                                   std::vector<IEntity *> stations_) {
  strategy = strategy_;
  robot = robot_;
  charge = charge_;
  stations = stations_;
}

void BatteryDecorator::Move(IEntity *entity, double dt) {
  entity->SetColor(charge);
  std::cout << charge << std::endl;
  Vector3 position = entity->GetPosition();
  GetNearestRechargeStation(stations, position);
  Vector3 destination = nearestStation->GetPosition();
  if (charge <= 20.0 && robot != NULL &&
      charge >=
          0.0) {  // if charge is under 20% and is currently carrying robot
    // std::cout << "low charge with robot" << charge << std::endl;
    Vector3 oldDestination = robot->GetDestination();
    // oldDestination.Print();
    delete strategy;
    strategy = NULL;
    // entity->SetDestination(destination);
    // destination.Print();
    charge -= dt * 0.2;
    strategy = new BeelineStrategy(entity->GetPosition(), destination);
    strategy->Move(entity, dt);

    robot->SetPosition(entity->GetPosition());
    robot->SetDirection(entity->GetDirection());
    if (strategy->IsCompleted()) {
      // std::cout << "charging with robot " << charge << std::endl;
      Recharge(dt);
      entity->SetDestination(oldDestination);
      delete strategy;
      strategy = NULL;
      strategy = new BeelineStrategy(entity->GetPosition(), oldDestination);
      // std::cout << "going to origional dest" << std::endl;
      // oldDestination.Print();
    }
  } else if (charge <= 20.0 &&
             charge >= 0.0) {  // charge is under 10% and not carrying robot
    // std::cout << "inside charge is under 10 and not carrying robot and
    // charge: " << charge << std::endl;
    Vector3 oldDestination = entity->GetDestination();
    delete strategy;
    strategy = NULL;
    // entity->SetDestination(destination);
    // oldDestination.Print();
    // destination.Print();
    charge -= dt * 0.2;
    strategy = new BeelineStrategy(entity->GetPosition(), destination);
    strategy->Move(entity, dt);
    // std::cout << "before if statement " << charge << std::endl;
    if (strategy->IsCompleted()) {
      // std::cout << "inside if statement " << charge << std::endl;
      Recharge(dt);
      // if(robot){
      // std::string targetStrategyName = robot->GetStrategyName():
      // if(targetStrategyName.compare("astar") == 0){
      //     strategy = new AstarStrategy(nearestEntity->GetPosition(),
      //     nearestEntity->GetDestination(), graph);
      //   } else if (targetStrategyName.compare("dfs") == 0){
      //     strategy = new DfsStrategy(nearestEntity->GetPosition(),
      //     nearestEntity->GetDestination(), graph);
      //   } else if (targetStrategyName.compare("dijkstra") == 0){
      //     strategy = new DijkstraStrategy(nearestEntity->GetPosition(),
      //     nearestEntity->GetDestination(), graph);
      //   } else {
      //     strategy = new BeelineStrategy(entity->GetPosition,
      //     oldDestination);
      //   }
      // entity->SetDestination(oldDestination);
      delete strategy;
      strategy = NULL;
      strategy = new BeelineStrategy(entity->GetPosition(), oldDestination);
    }
  } else {  // when charge isn't low
    // std::cout << "inside when charge isn't low and charge: " << charge <<
    // std::endl;
    if (charge >= 0.0) {
      // entity->GetDestination().Print();
      // std::cout << "inside charge >= 0" << std::endl;
      charge -= dt * 0.2;
      strategy->Move(entity, dt);
      // if (robot != NULL) {
      //   robot->SetPosition(entity->GetPosition());
      //   robot->SetDirection(entity->GetDirection());
      // }
    }
  }
}

void BatteryDecorator::GetNearestRechargeStation(
    std::vector<IEntity *> rechargeStations, Vector3 position) {
  float minDis = std::numeric_limits<float>::max();
  nearestStation = NULL;
  for (auto station : rechargeStations) {
    float disToStation = position.Distance(station->GetPosition());
    if (disToStation <= minDis) {
      minDis = disToStation;
      nearestStation = station;
    }
  }
}

void BatteryDecorator::Recharge(double dt) {
  std::cout << "inside recharge" << std::endl;
  while (charge <= 100.0) {
    std::cout << "inside recharge charge: " << charge << std::endl;
    charge += dt;
  }
  // pause the program here for a couple seconds
}

bool BatteryDecorator::IsCompleted() { return strategy->IsCompleted(); }

float BatteryDecorator::GetCharge() { return charge; }

void BatteryDecorator::SetCharge(float c) { charge = c; }
