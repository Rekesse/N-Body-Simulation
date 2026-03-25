#pragma once

#include "Pianeta.hpp"
#include <vector>

/**
 * @brief Abstract Base Class (Interface) for Numerical Integrators.
 * 
 * This interface defines the "Strategy" design pattern for the physics engine.
 * By using an abstract interface, the SolarSystem remains completely decoupled
 * from the underlying mathematical integration method (e.g., Euler, Verlet).
 * Any class inheriting from IIntegrator MUST implement the doStep() method.
 */
class IIntegrator {
public:
  /**
   * @brief Virtual destructor.
   * 
   * A virtual destructor is mandatory in C++ interfaces. It ensures that when 
   * derived classes (like EulerIntegrator) are deleted via a base class pointer,
   * their specific destructors are called, preventing memory leaks.
   */
  virtual ~IIntegrator() = default;

  /**
   * @brief Executes a single time step of the simulation.
   * 
   * @param universe A reference to the standard vector containing all celestial bodies.
   * @param dt The discrete time step (delta time) in seconds.
   * 
   * The "= 0" syntax declares this as a "Pure Virtual Function", forcing derived
   * classes to provide the concrete implementation.
   */
  virtual void doStep(std::vector<Pianeta> &universe, double dt) = 0;
};