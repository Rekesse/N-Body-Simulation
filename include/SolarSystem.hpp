#pragma once

#include "IIntegrator.hpp"
#include "Pianeta.hpp"
#include <vector>

/**
 * @brief The computational domain orchestrator.
 * 
 * The SolarSystem acts as the physical environment. It strictly owns the memory
 * of the planets (universe vector) and utilizes Dependency Injection to delegate
 * mathematical calculations to an interchangeable IIntegrator.
 */
class SolarSystem {
private:
  std::vector<Pianeta> universe;
  IIntegrator *integrator; // Pointer to an abstract interface (Loose Coupling)

public:
  /**
   * @brief Constructs a new Solar System with a specific physics engine.
   * @param integrator Pointer to the chosen integration algorithm.
   */
  SolarSystem(IIntegrator *integrator);

  /**
   * @brief Injects a celestial body into the simulation space.
   */
  void addPlanet(const Pianeta &planet);

  /**
   * @brief Advances the entire universe forward by one dt step.
   */
  void integrate(double dt);

  /**
   * @brief Provides read-only access to the planetary coordinate vectors.
   * 
   * The returned "const std::vector<Pianeta>&" guarantees O(1) high-performance 
   * read access without copying memory, while enforcing strict encapsulation
   * (the caller cannot modify or delete the planets).
   */
  const std::vector<Pianeta> &getUniverse() const;
};