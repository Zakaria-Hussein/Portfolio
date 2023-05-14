#ifndef LIBS_TRANSIT_INCLUDE_CELEBRATIONDECORATOR_H_
#define LIBS_TRANSIT_INCLUDE_CELEBRATIONDECORATOR_H_

#include <vector>

#include "IStrategy.h"

class CelebrationDecorator : public IStrategy {
 public:
  /**
   * @brief Construct a new Celebration Decorator object
   * 
   * @param strategy_ 
   */
  CelebrationDecorator(IStrategy *strategy_) {
    strategy = strategy_;
    time = 0;
  }

  /**
   * @brief moves the entity
   * 
   * @param entity 
   * @param dt time
   */
  void Move(IEntity *entity, double dt);

  /**
   * @brief checks if the destination has been reached
   * 
   * @return true 
   * @return false 
   */
  bool IsCompleted();

 protected:
  IStrategy *strategy;
  float time;
};
#endif  // LIBS_TRANSIT_INCLUDE_CELEBRATIONDECORATOR_H_
