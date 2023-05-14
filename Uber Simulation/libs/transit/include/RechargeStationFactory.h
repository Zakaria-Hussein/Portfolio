#ifndef LIBS_TRANSIT_INCLUDE_RECHARGESTATIONFACTORY_H_
#define LIBS_TRANSIT_INCLUDE_RECHARGESTATIONFACTORY_H_

#include "IEntity.h"
#include "IEntityFactory.h"
#include "RechargeStation.h"
#include <vector>

class RechargeStationFactory : public IEntityFactory {
 public:
    /**
     * @brief Create a recharge station
     * 
     * @param entity 
     * @return IEntity* 
     */
    IEntity* CreateEntity(JsonObject& entity);
};

#endif  // LIBS_TRANSIT_INCLUDE_RECHARGESTATIONFACTORY_H_
