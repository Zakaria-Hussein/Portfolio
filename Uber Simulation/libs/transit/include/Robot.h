#ifndef LIBS_TRANSIT_INCLUDE_ROBOT_H_
#define LIBS_TRANSIT_INCLUDE_ROBOT_H_

#include <vector>

#include "IEntity.h"
#include "math/vector3.h"
#include "util/json.h"

class Robot : public IEntity {
 public:
  /**
   * @brief Construct a new Robot object
   * 
   * @param obj 
   */
  Robot(JsonObject& obj);

  /**
   * @brief Destroy the Robot object
   * 
   */
  ~Robot() override = default;

  /**
   * @brief Get the Position object
   * 
   * @return Vector3 
   */
  Vector3 GetPosition() const { return position; }

  /**
   * @brief Get the Direction object
   * 
   * @return Vector3 
   */
  Vector3 GetDirection() const { return direction; }

  /**
   * @brief Get the Destination object
   * 
   * @return Vector3 
   */
  Vector3 GetDestination() const { return destination; }

  /**
   * @brief Get the Availability object
   * 
   * @return true 
   * @return false 
   */
  bool GetAvailability() const { return available; }

  /**
   * @brief Get the Details object
   * 
   * @return JsonObject 
   */
  JsonObject GetDetails() const override;

  /**
   * @brief Get the Speed object
   * 
   * @return float 
   */
  float GetSpeed() const { return speed; }

  /**
   * @brief Get the Strategy Name object
   * 
   * @return std::string 
   */
  std::string GetStrategyName() {return strategyName;}

  /**
   * @brief Set the Availability object
   * 
   * @param choice 
   */
  void SetAvailability(bool choice);

  /**
   * @brief Set the Position object
   * 
   * @param pos_ 
   */
  void SetPosition(Vector3 pos_) { position = pos_; }

  /**
   * @brief Set the Direction object
   * 
   * @param dir_ 
   */
  void SetDirection(Vector3 dir_) { direction = dir_; }

  /**
   * @brief Set the Destination object
   * 
   * @param des_ 
   */
  void SetDestination(Vector3 des_) { destination = des_; }

  /**
   * @brief Set the Strategy Name object
   * 
   * @param strategyName_ 
   */
  void SetStrategyName(std::string strategyName_)
  { strategyName = strategyName_;}

  /**
   * @brief rotates the robot
   * 
   * @param angle 
   */
  void Rotate(double angle);

 private:
  JsonObject details;
  Vector3 position;
  Vector3 direction;
  Vector3 destination;
  float speed;
  bool available;
  std::string strategyName;
};

#endif  // LIBS_TRANSIT_INCLUDE_ROBOT_H_

