#include "EulerIntegrator.hpp"
#include "Pianeta.hpp"
#include <vector>

void EulerIntegrator::doStep(std::vector<Pianeta> &universe, double dt) {
  // 1. Force Reset Phase: Clear all accumulated forces from the previous dt step.
  for (Pianeta &p : universe) {
    p.reset_force();
  }
  
  // 2. Pairwise Force Computation Phase: O(N^2) complexity.
  // Calculates the gravitational pull between every unique pair of planets.
  for (int i{0}; i < universe.size(); i++) {
    for (int j{0}; j < universe.size(); j++) {
      if (j != i) { // Prevent a body from exerting gravitational force upon itself.
        universe[i].compute_force(universe[j]);
      }
    }
  }
  
  // 3. State Update Phase: Apply Explicit Euler kinematics.
  // Translates the accumulated force into acceleration, then velocity, then position.
  for (Pianeta &p : universe) {
    p.update(dt);
  }
}