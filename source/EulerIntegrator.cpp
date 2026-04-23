#include "EulerIntegrator.hpp"
#include "Planet.hpp"
#include <vector>

void EulerIntegrator::doStep(std::vector<Planet> &universe, Time dt) {
  // 1. Force Reset Phase: Clear all accumulated forces from the previous dt
  // step.
  for (Planet &p : universe) {
    p.reset_force();
  }

  // 2. Pairwise Force Computation Phase: O(N^2) complexity.
  // Calculates the gravitational pull between every unique pair of planets.
  for (int i{0}; i < universe.size(); i++) {
    for (int j{0}; j < universe.size(); j++) {
      if (j != i) { 
        // Prevent a body from exerting gravitational force upon itself.
        universe[i].compute_force(universe[j]);
      }
    }
  }

  // 3. State Update Phase: Explicit Euler Forward Integration.
  //
  // The integration equations are derived from Newton's Second Law (F = ma):
  //   a(t)       = F(t) / m          — Instantaneous acceleration vector
  //   v(t + dt)  = v(t) + a(t) * dt  — Velocity accumulation (1st integral)
  //   x(t + dt)  = x(t) + v(t+dt)*dt — Position accumulation (2nd integral)
  //
  // CRITICAL: the formulas are ACCUMULATIVE (+=), not assignments (=).
  // Overwriting the state (v = a*dt) instead of accumulating (v += a*dt)
  // would discard all previous kinematic history, collapsing the orbit
  // into a straight line emanating from the origin.
  for (Planet &p : universe) {
    // Extract the instantaneous acceleration vector a = F/m
    Acceleration3D a {p.get_acc()};

    p.vel += a * dt;

    p.pos +=  p.vel*dt;
  }
}