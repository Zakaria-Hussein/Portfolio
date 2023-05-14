#ifndef LIBS_TRANSIT_INCLUDE_SPINDECORATOR_H_
#define LIBS_TRANSIT_INCLUDE_SPINDECORATOR_H_

#include <vector>

#include "CelebrationDecorator.h"
#include "IStrategy.h"

class SpinDecorator : public CelebrationDecorator {
 public:
  /**
   * @brief Construct a new Spin Decorator object
   * 
   * @param strategy_ 
   */
  SpinDecorator(IStrategy* strategy_) : CelebrationDecorator(strategy_) {}

  /**
   * @brief checks if the destination has been reached
   * 
   * @return true 
   * @return false 
   */
  bool IsCompleted();

  /**
   * @brief moves the entity
   * 
   * @param entity 
   * @param dt time
   */
  void Move(IEntity* entity, double dt);
};  // close class

#endif  // LIBS_TRANSIT_INCLUDE_SPINDECORATOR_H_
