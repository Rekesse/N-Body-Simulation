#include "Pianeta.hpp"
#include <basetsd.h>

/**
 * @brief Class Constructor. Initializes the dynamic state and zeros the force
 * accumulators.
 */
Pianeta::Pianeta(double m, double x, double y, double z, double vx, double vy,
                 double vz)
    : m(m), x(x), y(y), z(z), vx(vx), vy(vy), vz(vz), fx(0), fy(0), fz(0) {}

/**
 * @brief Euclidean distance computation in a 3D Cartesian coordinate system.
 */
double Pianeta::compute_distance(const Pianeta &other) const {
  double dx = x - other.x;
  double dy = y - other.y;
  double dz = z - other.z;
  return std::sqrt(dx * dx + dy * dy + dz * dz);
}

/**
 * @brief Evaluates pairwise gravitational interaction.
 *
 * Implements the magnitude F = G * (m1 * m2) / r^2.
 * The direction is normalized by dividing by the distance scalar,
 * avoiding computationally expensive trigonometric function evaluations.
 */
void Pianeta::compute_force(const Pianeta &other) {
  double dx = other.x - x;
  double dy = other.y - y;
  double dz = other.z - z;
  double r = dx * dx + dy * dy + dz * dz;
  double r_sqrt = std::sqrt(r);
  double Ftot = G * m * other.m / r;

  fx += Ftot * (dx / r_sqrt);
  fy += Ftot * (dy / r_sqrt);
  fz += Ftot * (dz / r_sqrt);
}

void Pianeta::reset_force() {
  fx = 0;
  fy = 0;
  fz = 0;
}

/**
 * @brief State evaluation using Explicit Euler Integration.
 *
 * Uses Newton's Second Law (F = ma) to derive acceleration, and integrates
 * sequentially to determine the new velocity and positional space vectors.
 * Note: Euler integration is not symplectic and may introduce secular energy
 * drift.
 */
void Pianeta::update(double dt) {
  double ax = fx / m;
  double ay = fy / m;
  double az = fz / m;

  vx += ax * dt;
  vy += ay * dt;
  vz += az * dt;

  x += vx * dt;
  y += vy * dt;
  z += vz * dt;
}

double Pianeta::getX() { return x; }

double Pianeta::getY() { return y; }

double Pianeta::getZ() { return z; }