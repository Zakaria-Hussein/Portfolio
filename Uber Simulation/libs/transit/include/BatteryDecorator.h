#ifndef LIBS_TRANSIT_INCLUDE_BATTERYDECORATOR_H_
#define LIBS_TRANSIT_INCLUDE_BATTERYDECORATOR_H_

#include <vector>
#include "math/vector3.h"
#include "IEntity.h"
#include "IStrategy.h"
#include "SimulationModel.h"
#include "BeelineStrategy.h"
#include "DfsStrategy.h"
#include "AstarStrategy.h"
#include "DijkstraStrategy.h"


class BatteryDecorator : public IStrategy {
 public:
      BatteryDecorator(IStrategy *strategy_, IEntity* robot_, float charge_,
                    std::vector<IEntity*> stations_);
      void Move(IEntity *entity, double dt);
      /**
      * @brief checks if destination has been reached
      * 
      * @return true 
      * @return false 
      */
      bool IsCompleted();
      void GetNearestRechargeStation(std::vector<IEntity*>
                                     rechargeStations, Vector3 position);
      void Recharge(double dt);
      /**
      * @brief Get the Charge of the drone
      * 
      * @return drone 
      */
      float GetCharge();
      /**
      * @brief Set the Charge of the drone
      * 
      * @param c
      */
      void SetCharge(float c);

 private:
      IStrategy* strategy = NULL;
      IEntity* robot = NULL;
      IEntity* nearestStation = NULL;
      std::vector<IEntity*> stations;
      float charge = 100.0;
};

#endif  // LIBS_TRANSIT_INCLUDE_BATTERYDECORATOR_H_
