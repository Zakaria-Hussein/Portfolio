#ifndef LIBS_TRANSIT_INCLUDE_ISTRATEGY_H_
#define LIBS_TRANSIT_INCLUDE_ISTRATEGY_H_

#include <vector>
#include "graph.h"
#include "IEntity.h"

using namespace routing;

class IStrategy {
 public:
        /**
         * @brief moves the entity
         * 
         * @param entity 
         * @param dt time
         */
        virtual void Move(IEntity* entity, double dt) = 0;

        /**
         * @brief checks if destination has been reached
         * 
         * @return true 
         * @return false 
         */
        virtual bool IsCompleted() = 0;

        /**
         * @brief Get the Charge object
         * 
         * @return float 
         */
        virtual float GetCharge() {}

        /**
         * @brief Set the Charge object
         * 
         * @param c 
         */
        virtual void SetCharge(float c) {}

 protected:
        const IGraph* graph;
};

#endif  // LIBS_TRANSIT_INCLUDE_ISTRATEGY_H_
