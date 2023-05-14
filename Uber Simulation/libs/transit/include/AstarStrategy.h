#ifndef LIBS_TRANSIT_INCLUDE_ASTARSTRATEGY_H_
#define LIBS_TRANSIT_INCLUDE_ASTARSTRATEGY_H_

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
class AstarStrategy : public IStrategy {
 public:
    /**
     * @brief Construct a new Astar Strategy object
     * 
     * @param position 
     * @param destination 
     * @param graph 
     */
    AstarStrategy(Vector3 position, Vector3 destination, const IGraph* graph);

    /**
     * @brief Destroy the Astar Strategy object
     * 
     */
    ~AstarStrategy();

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
    std::vector<std::vector<float>> path;
    int currentIndex;
    int maxIndex;
};

#endif  // LIBS_TRANSIT_INCLUDE_ASTARSTRATEGY_H_
