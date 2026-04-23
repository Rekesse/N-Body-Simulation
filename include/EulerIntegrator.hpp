#pragma once

#include <IIntegrator.hpp>
#include <Planet.hpp>
#include <vector>

/**
 * @brief Concrete implementation of the Explicit Euler integration method.
 * 
 * This class inherits from IIntegrator, satisfying its contractual obligation
 * to implement the physics logic for a single discrete time step. 
 * The Explicit Euler method is an O(dt) first-order numerical procedure.
 */
class EulerIntegrator : public IIntegrator {
public:
  /**
   * @brief Computes pairwise forces and translates bodies using Euler's rule.
   * 
   * The 'override' keyword is a C++11 safety feature. It explicitly tells the 
   * compiler that we intend to override the virtual function from the base class.
   * If the base class signature changes, the compiler will catch the mismatch here.
   */
  void doStep(std::vector<Planet> &universe, Time dt) override;
};