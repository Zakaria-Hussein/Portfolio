#ifndef LIBS_TRANSIT_INCLUDE_RECHARGESTATION_H_
#define LIBS_TRANSIT_INCLUDE_RECHARGESTATION_H_

#include <vector>

#include "IEntity.h"
#include "IStrategy.h"
#include "math/vector3.h"

class RechargeStation : public IEntity {
 public:
  /**
   * @brief Construct a new Recharge Station object
   * 
   * @param obj 
   */
  RechargeStation(JsonObject& obj);

  /**
   * @brief Destroy the Recharge Station object
   * 
   */
  ~RechargeStation() {}

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

 private:
  JsonObject details;
  Vector3 position;
  Vector3 direction;
  Vector3 destination;
  float speed;
};

#endif  // LIBS_TRANSIT_INCLUDE_RECHARGESTATION_H_
