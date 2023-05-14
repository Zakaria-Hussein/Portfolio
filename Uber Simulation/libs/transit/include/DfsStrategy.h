#ifndef LIBS_TRANSIT_INCLUDE_DFSSTRATEGY_H_
#define LIBS_TRANSIT_INCLUDE_DFSSTRATEGY_H_

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
class DfsStrategy : public IStrategy {
 public:
    /**
     * @brief Construct a new Dfs Strategy object
     * 
     * @param position 
     * @param destination 
     * @param graph 
     */
    DfsStrategy(Vector3 position, Vector3 destination, const IGraph* graph);

    /**
     * @brief Destroy the Dfs Strategy object
     * 
     */
    ~DfsStrategy();

    /**
     * @brief moves the entity
     * 
     * @param entity 
     * @param dt 
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
#endif  // LIBS_TRANSIT_INCLUDE_DFSSTRATEGY_H_
