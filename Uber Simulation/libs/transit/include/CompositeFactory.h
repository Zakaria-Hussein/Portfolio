#ifndef LIBS_TRANSIT_INCLUDE_COMPOSITEFACTORY_H_
#define LIBS_TRANSIT_INCLUDE_COMPOSITEFACTORY_H_

#include "IEntityFactory.h"

class CompositeFactory : public IEntityFactory {
 public:
    /**
     * @brief Create a Entity object
     * 
     * @param entity 
     * @return IEntity* 
     */
    IEntity* CreateEntity(JsonObject& entity);

    /**
     * @brief adds the new factory
     * 
     * @param factoryEntity 
     */
    void AddFactory(IEntityFactory* factoryEntity);
    /**
     * @brief Destroy the Composite Factory object
     * 
     */
    virtual ~CompositeFactory();

 private:
    std::vector<IEntityFactory*> componentFactories;
};

#endif  // LIBS_TRANSIT_INCLUDE_COMPOSITEFACTORY_H_
