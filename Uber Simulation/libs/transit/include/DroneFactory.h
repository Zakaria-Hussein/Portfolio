#ifndef LIBS_TRANSIT_INCLUDE_DRONEFACTORY_H_
#define LIBS_TRANSIT_INCLUDE_DRONEFACTORY_H_

#include "IEntity.h"
#include "IEntityFactory.h"
#include "Drone.h"

#include <vector>

class DroneFactory : public IEntityFactory {
 public:
    /**
     * @brief Destroy the Drone Factory object
     * 
     */
    virtual ~DroneFactory() {}
    /**
     * @brief Create a drone
     * 
     * @param entity 
     * @return IEntity* 
     */
    IEntity* CreateEntity(JsonObject& entity);
};

#endif  // LIBS_TRANSIT_INCLUDE_DRONEFACTORY_H_
