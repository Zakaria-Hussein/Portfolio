#ifndef LIBS_TRANSIT_INCLUDE_IENTITYFACTORY_H_
#define LIBS_TRANSIT_INCLUDE_IENTITYFACTORY_H_

#include "util/json.h"

#include "IEntity.h"
#include "IEntityFactory.h"
#include "Drone.h"

class IEntityFactory {
 public:
    /**
     * @brief Destroy the IEntityFactory object
     * 
     */
    virtual ~IEntityFactory() {}

    /**
     * @brief Create a Entity object
     * 
     * @param entity 
     * @return IEntity* 
     */
    virtual IEntity* CreateEntity(JsonObject& entity) = 0;
};

#endif  // LIBS_TRANSIT_INCLUDE_IENTITYFACTORY_H_
