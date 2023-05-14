#ifndef LIBS_TRANSIT_INCLUDE_BEELINESTRATEGY_H_
#define LIBS_TRANSIT_INCLUDE_BEELINESTRATEGY_H_

/**
 * include
 */
#include "math/vector3.h"
#include <vector>
#include "IStrategy.h"
#include "IEntity.h"
/**
 * @brief this class inhertis from the IStrategy class and is responsible for generating the beeline that the drone will take.
 */
class BeelineStrategy : public IStrategy {
 public:
    /**
     * @brief Construct a new Beeline Strategy object
     * 
     * @param position 
     * @param destination 
     */
    BeelineStrategy(Vector3 position, Vector3 destination);

    /**
     * @brief Destroy the Beeline Strategy object
     * 
     */
    ~BeelineStrategy();
    /**
     * @brief moves the entity
     * 
     * @param entity 
     * @param dt time
     */
    void Move(IEntity* entity, double dt);

    /**
     * @brief checks if the destination has been reached
     * 
     * @return true 
     * @return false 
     */
    bool IsCompleted();

 private:
    Vector3 position;
    Vector3 destination;
};
#endif  // LIBS_TRANSIT_INCLUDE_BEELINESTRATEGY_H_
