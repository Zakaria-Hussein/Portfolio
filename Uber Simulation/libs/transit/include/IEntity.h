#ifndef LIBS_TRANSIT_INCLUDE_IENTITY_H_
#define LIBS_TRANSIT_INCLUDE_IENTITY_H_

#include <vector>

#include "graph.h"
#include "math/vector3.h"
#include "util/json.h"

using namespace routing;

//--------------------  Controller Interface ----------------------------

/// Abstract controller class used in the Transit Service.  Uses the Model View
/// Controller Pattern
class IEntity {
 public:
  /**
   * @brief Construct a new IEntity object
   * 
   */
  IEntity() {
    static int currentId = 0;
    id = currentId;
    currentId++;
  }

  /**
   * @brief Destroy the IEntity object
   * 
   */
  virtual ~IEntity() {}

  /**
   * @brief Get the Id object
   * 
   * @return int 
   */
  virtual int GetId() const { return id; }

  /**
   * @brief Get the Position object
   * 
   * @return Vector3 
   */
  virtual Vector3 GetPosition() const = 0;

  /**
   * @brief Get the Direction object
   * 
   * @return Vector3 
   */
  virtual Vector3 GetDirection() const = 0;

  /**
   * @brief Get the Destination object
   * 
   * @return Vector3 
   */
  virtual Vector3 GetDestination() const = 0;

  /**
   * @brief Get the Details object
   * 
   * @return JsonObject 
   */
  virtual JsonObject GetDetails() const = 0;

  /**
   * @brief Get the Speed object
   * 
   * @return float 
   */
  virtual float GetSpeed() const = 0;

  /**
   * @brief Get the Availability object
   * 
   * @return true 
   * @return false 
   */
  virtual bool GetAvailability() const {}

  /**
   * @brief Get the Strategy Name object
   * 
   * @return std::string 
   */
  virtual std::string GetStrategyName() {}

  /**
   * @brief Set the Availability object
   * 
   * @param choice 
   */
  virtual void SetAvailability(bool choice) {}
  virtual std::string GetColor() const { return "None"; }
  virtual void SetColor(float charge) {}
  virtual void Update(double dt, std::vector<IEntity*> scheduler,
                      std::vector<IEntity*> rechargeStations) {}
  void SetGraph(const IGraph* graph) { this->graph = graph; }

  /**
   * @brief Set the Position object
   * 
   * @param pos_ 
   */
  virtual void SetPosition(Vector3 pos_) {}

  /**
   * @brief Set the Direction object
   * 
   * @param dir_ 
   */
  virtual void SetDirection(Vector3 dir_) {}

  /**
   * @brief Set the Destination object
   * 
   * @param des_ 
   */
  virtual void SetDestination(Vector3 des_) {}

  /**
   * @brief Set the Strategy Name object
   * 
   * @param strategyName_ 
   */
  virtual void SetStrategyName(std::string strategyName_) {}

  /**
   * @brief rotates the entity
   * 
   * @param angle 
   */
  virtual void Rotate(double angle) {}

  /**
   * @brief makes the entity jump
   * 
   * @param height 
   */
  virtual void Jump(double height) {}

 protected:
  int id;
  const IGraph* graph;
};

#endif  // LIBS_TRANSIT_INCLUDE_IENTITY_H_

