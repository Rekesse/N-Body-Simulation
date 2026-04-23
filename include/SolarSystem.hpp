#pragma once

#include <IIntegrator.hpp>
#include <Planet.hpp>
#include <vector>
#include <iostream>
#include <map>
#include <array>

/**
 * @brief The computational domain orchestrator.
 * 
 * The SolarSystem acts as the physical environment. It strictly owns the memory
 * of the planets (universe vector) and utilizes Dependency Injection to delegate
 * mathematical calculations to an interchangeable IIntegrator.
 */

struct SolarSystem {
  std::vector<Planet> universe;

  /**
   * @brief Pointer to the abstract integration strategy (Loose Coupling).
   *
   * A pointer (IIntegrator*) is chosen over a reference (IIntegrator&) for
   * three fundamental reasons in C++ object-oriented design:
   *
   * 1. REASSIGNABILITY — A reference, once bound to an object at construction,
   *    can never be reseated to point elsewhere. A pointer can be reassigned
   *    at runtime, enabling hot-swapping of integration algorithms (e.g.,
   *    switching from Euler to Verlet mid-simulation).
   *
   * 2. NULLABLE SEMANTICS — A pointer can represent the absence of an object
   *    (nullptr), which is useful for deferred initialization or error states.
   *    A reference must always refer to a valid object.
   *
   * 3. POLYMORPHISM — The pointer type is the abstract base class IIntegrator*.
   *    At runtime, the actual object behind the pointer can be any concrete
   *    derived class (EulerIntegrator, VerletIntegrator, etc.). This is the
   *    runtime polymorphism mechanism that enables the Strategy Pattern.
   *
   * NOTE: In production-grade C++, this raw pointer would be replaced by
   * std::unique_ptr<IIntegrator> to enforce automatic memory management
   * (RAII) and make the ownership semantics explicit. In the current design
   * the integrator is stack-allocated in main(), so no manual delete is needed.
   */
  IIntegrator *integrator;
  /**
   * @brief Constructs a new Solar System with a specific physics engine.
   * @param integrator Pointer to the chosen integration algorithm.
   */
  SolarSystem(IIntegrator *integrator,
  const std::map<std::string,std::array<double,6>>& dataMapp,
  const std::map<std::string, double>& massDatabase);

  /**
   * @brief Injects a celestial body into the simulation space.
   */
  void addPlanet(const Planet &planet);

  /**
   * @brief Advances the entire universe forward by one dt step.
   */
  void integrate(Time dt);

  /**
   * @brief Provides read-only access to the planetary coordinate vectors.
   * 
   * The returned "const std::vector<Pianeta>&" guarantees O(1) high-performance 
   * read access without copying memory, while enforcing strict encapsulation
   * (the caller cannot modify or delete the planets).
   */
  const std::vector<Planet> &getUniverse() const;
};