#include "Pianeta.hpp"
#include <array>
// #include <basetsd.h>

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
  double dx = other.getX() - x;
  double dy = other.getY() - y;
  double dz = other.getZ() - z;
  double r = dx * dx + dy * dy + dz * dz;
  double r_sqrt = std::sqrt(r);
  /*double Ftot = G * m * other.m / r;

  fx += Ftot * (dx / r_sqrt);
  fy += Ftot * (dy / r_sqrt);
  fz += Ftot * (dz / r_sqrt);
  */
}

void Pianeta::reset_force() {
  fx = 0;
  fy = 0;
  fz = 0;
}

// --------------------------------------------------------------------------
// State Vector Accessors
// --------------------------------------------------------------------------
// The following getters were introduced to externalize the Euler integration
// logic from Pianeta into the IIntegrator hierarchy (Strategy Pattern).
// Pianeta now acts purely as a data entity ("Model"), while the mathematical
// time-stepping is delegated to the concrete integrator class.

double Pianeta::getForceX() const { return fx; }

double Pianeta::getForceY() const { return fy; }

double Pianeta::getForceZ() const { return fz; }

double Pianeta::getX() const { return x; }

double Pianeta::getY() const { return y; }

double Pianeta::getZ() const { return z; }

/**
 * @brief Velocity vector accessors.
 *
 * These are essential for the Explicit Euler accumulation formula:
 *   v(t+dt) = v(t) + a * dt
 * Without read access to the current velocity, the integrator would
 * overwrite (instead of accumulate) the kinematic state.
 */
double Pianeta::getVx() const { return vx; }

double Pianeta::getVy() const { return vy; }

double Pianeta::getVz() const { return vz; }

/**
 * @brief Computes instantaneous acceleration from Newton's Second Law: a = F/m.
 *
 * The division is performed on-the-fly (not cached) to guarantee the returned
 * value always reflects the most recently accumulated force state. This is
 * critical because forces are reset and recomputed at every discrete time step.
 */
double Pianeta::getAccX() const { return fx / m; }

double Pianeta::getAccY() const { return fy / m; }

double Pianeta::getAccZ() const { return fz / m; }

// --------------------------------------------------------------------------
// State Vector Mutators
// --------------------------------------------------------------------------
// These setters allow the IIntegrator to write the newly computed kinematic
// state back into the Pianeta object after each integration step.
// The separation of read (getters) and write (setters) enforces a clear
// data-flow contract: only the active integrator may modify the state.

void Pianeta::setVx(double v_x) { vx = v_x; }

void Pianeta::setVy(double v_y) { vy = v_y; }

void Pianeta::setVz(double v_z) { vz = v_z; }

void Pianeta::setX(double x_pos) { x = x_pos; }

void Pianeta::setY(double y_pos) { y = y_pos; }

void Pianeta::setZ(double z_pos) { z = z_pos; }