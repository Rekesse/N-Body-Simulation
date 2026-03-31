#include "EulerIntegrator.hpp"
#include "Pianeta.hpp"
#include <vector>

void EulerIntegrator::doStep(std::vector<Pianeta> &universe, double dt) {
  // 1. Force Reset Phase: Clear all accumulated forces from the previous dt
  // step.
  for (Pianeta &p : universe) {
    p.reset_force();
  }

  // 2. Pairwise Force Computation Phase: O(N^2) complexity.
  // Calculates the gravitational pull between every unique pair of planets.
  for (int i{0}; i < universe.size(); i++) {
    for (int j{0}; j < universe.size(); j++) {
      if (j !=
          i) { // Prevent a body from exerting gravitational force upon itself.
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
  for (Pianeta &p : universe) {
    // Step 3a: Extract the instantaneous acceleration vector a = F/m
    double ax{p.getAccX()};
    double ay{p.getAccY()};
    double az{p.getAccZ()};

    // Step 3b: Accumulate velocity — v(t+dt) = v(t) + a(t) * dt
    double new_vx{p.getVx() + ax * dt};
    double new_vy{p.getVy() + ay * dt};
    double new_vz{p.getVz() + az * dt};

    // Step 3c: Accumulate position — x(t+dt) = x(t) + v(t+dt) * dt
    double new_x{p.getX() + new_vx * dt};
    double new_y{p.getY() + new_vy * dt};
    double new_z{p.getZ() + new_vz * dt};

    // Step 3d: Write the updated state back into the Pianeta entity
    p.setVx(new_vx);
    p.setVy(new_vy);
    p.setVz(new_vz);

    p.setX(new_x);
    p.setY(new_y);
    p.setZ(new_z);
  }
}