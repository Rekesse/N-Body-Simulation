#include "Pianeta.hpp"
#include "Types.hpp"
#include <Planet.hpp>
#include <cmath>

void Planet::compute_force(const Planet &other) {
  GraviConst G(6.67430e-11);
  Position3D delta_pos = other.pos - pos;
  SquaredDistance r_sq = squared_norm(delta_pos);
  Distance d(std::sqrt(r_sq.value()));

  Force Ftot = G * m * other.m / r_sq;
  force = delta_pos * Ftot / d;
}

void Planet::reset_force() { force = force * 0.0; }

Acceleration3D Planet::get_acc() const { return force / m; }