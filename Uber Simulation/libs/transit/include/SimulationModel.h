#ifndef LIBS_TRANSIT_INCLUDE_SIMULATIONMODEL_H_
#define LIBS_TRANSIT_INCLUDE_SIMULATIONMODEL_H_

#include "IController.h"
#include "CompositeFactory.h"
#include "IEntity.h"
#include "graph.h"
using namespace routing;

//--------------------  Model ----------------------------

/// Simulation Model handling the transit simulation.  The model can communicate
/// with the controller.
class SimulationModel {
 public:
  /**
   * @brief Construct a new Simulation Model object
   * 
   * @param controller 
   */
  SimulationModel(IController& controller);

  /**
   * @brief Set the Graph object
   * 
   * @param graph 
   */
  void SetGraph(const IGraph* graph) { this->graph = graph; }

  /// Creates an simulation entity

  /**
   * @brief Create a simulation model
   * 
   * @param entity 
   */
  void CreateEntity(JsonObject& entity);

  /// Schedules a trip for an object in the scene

  /**
   * @brief schedule a trip
   * 
   * @param details 
   */
  void ScheduleTrip(JsonObject& details);

  /// Updates the simulation
  /**
   * @brief update the simulation
   * 
   * @param dt time
   */
  void Update(double dt);

  // Adds a new entity type
  /**
   * @brief adds a new entity factory
   * 
   * @param factory 
   */
  void AddFactory(IEntityFactory* factory);

 protected:
  IController& controller;
  std::vector<IEntity*> entities;
  std::vector<IEntity*> scheduler;
  std::vector<IEntity*> rechargeStations;
  const IGraph* graph;
  CompositeFactory* compFactory;
};

#endif  // LIBS_TRANSIT_INCLUDE_SIMULATIONMODEL_H_

