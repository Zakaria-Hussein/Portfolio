#ifndef LIBS_TRANSIT_INCLUDE_ICONTROLLER_H_
#define LIBS_TRANSIT_INCLUDE_ICONTROLLER_H_

#include "IEntity.h"
#include "util/json.h"

//--------------------  Controller Interface ----------------------------

/// Abstract controller class used in the Transit Service.  Uses the Model View
/// Controller Pattern
class IController {
 public:
  /**
   * @brief Destroy the IController object
   * 
   */
  virtual ~IController() {}
  /// Adds an entity to the program

  /**
   * @brief adds the entity to the program
   * 
   * @param entity 
   */
  virtual void AddEntity(const IEntity& entity) = 0;
  /// Adds an entity to the program

  /**
   * @brief updates the entity
   * 
   * @param entity 
   */
  virtual void UpdateEntity(const IEntity& entity) = 0;
  /// Removes an entity from the program

  /**
   * @brief removes the entity
   * 
   * @param id 
   */
  virtual void RemoveEntity(int id) = 0;

  /**
   * @brief Adds a path to the program
   * 
   * @param id 
   * @param path 
   */
  virtual void AddPath(int id,
                       const std::vector<std::vector<float> >& path) = 0;
  /// Removes a path from the program

  /**
   * @brief removes the path
   * 
   * @param id 
   */
  virtual void RemovePath(int id) = 0;
  /// Allows messages to be passed back to the view

  /**
   * @brief Allows messages to be passed back to the view
   * 
   * @param event 
   * @param details 
   */
  virtual void SendEventToView(const std::string& event,
                               const JsonObject& details) = 0;
};

#endif  // LIBS_TRANSIT_INCLUDE_ICONTROLLER_H_

