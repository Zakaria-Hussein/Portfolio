#ifndef LIBS_TRANSIT_INCLUDE_DRONE_H_
#define LIBS_TRANSIT_INCLUDE_DRONE_H_

#include <vector>

#include "IEntity.h"
#include "IStrategy.h"
#include "math/vector3.h"

// Represents a drone in a physical system.
// Drones move using euler integration based on a specified
// velocity and direction.
class Drone : public IEntity {
 public:
  // Drones are created with a name
  /**
   * @brief Construct a new Drone object
   * 
   * @param obj drone
   */
  Drone(JsonObject& obj);
  // Destructor
  /**
   * @brief Destroy the Drone object
   * 
   */
  ~Drone();

  /**
   * @brief Get the Speed object
   * 
   * @return float 
   */
  float GetSpeed() const { return speed; }

  // Gets the drone position
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
  JsonObject GetDetails() const { return details; }

  /**
   * @brief Get the Availability object
   * 
   * @return true 
   * @return false 
   */
  bool GetAvailability() const { return available; }

  void GetNearestEntity(std::vector<IEntity*> scheduler,
                        std::vector<IEntity*> rechargeStations);

  // Updates the drone's position
  void Update(double dt, std::vector<IEntity*> scheduler,
              std::vector<IEntity*> rechargeStations);
  /**
   * @brief Set the Position object
   * 
   * @param pos_ 
   */
  void SetPosition(Vector3 pos_) { position = pos_; }

  // Sets the drone's direction
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

  // Rotates a drone
  /**
   * @brief rotates the drone
   * 
   * @param angle 
   */
  void Rotate(double angle);

  /**
   * @brief makes the drone jump
   * 
   * @param height 
   */
  void Jump(double height);

  std::string GetColor() const { return color; }

  void SetColor(float charge);

  // Removing the copy constructor and assignment operator
  // so that drones cannot be coppied.
  /**
   * @brief removes the copy constructor
   * 
   * @param drone 
   */
  Drone(const Drone& drone) = delete;

  /**
   * @brief removes the assignment operator
   * 
   * @param drone 
   * @return Drone& 
   */
  Drone& operator=(const Drone& drone) = delete;

 private:
  JsonObject details;
  Vector3 position;
  Vector3 direction;
  float jumpHeight = 0;
  bool goUp = true;
  Vector3 destination;
  float speed;
  bool available;
  bool pickedUp;
  std::string strategyName;
  std::string color = "None";
  IEntity* nearestEntity = NULL;
  IStrategy* toTargetPosStrategy = NULL;
  IStrategy* toTargetDestStrategy = NULL;
  IStrategy* toTargetRandomStrategy = NULL;
  float charge = 100.0;
};
#endif  // LIBS_TRANSIT_INCLUDE_DRONE_H_

