#pragma once
#include <cmath>

/**
 * @brief Universal gravitational constant (G).
 * Expressed in the International System of Units (SI): m^3 * kg^-1 * s^-2.
 */
// const double G = 6.67430e-11;

/**
 * @class Pianeta
 * @brief Represents a celestial body (planet) in an N-Body gravitational
 * simulation.
 *
 * This class encapsulates the fundamental state vectors (spatial position and
 * velocity) and dynamic accumulators (forces) required to compute orbital
 * mechanics and integration.
 */
class Pianeta {
private:
  double m;  ///< Mass of the celestial body [kg]
  double x;  ///< X-coordinate of the spatial position [m]
  double y;  ///< Y-coordinate of the spatial position [m]
  double z;  ///< Z-coordinate of the spatial position [m]
  double vx; ///< X-component of the velocity vector [m/s]
  double vy; ///< Y-component of the velocity vector [m/s]
  double vz; ///< Z-component of the velocity vector [m/s]
  double fx; ///< X-component of the accumulated force vector [N]
  double fy; ///< Y-component of the accumulated force vector [N]
  double fz; ///< Z-component of the accumulated force vector [N]

public:
  /**
   * @brief Constructs a celestial body with defined mass and state vectors.
   *
   * @param m Mass [kg]
   * @param x Initial X-position [m]
   * @param y Initial Y-position [m]
   * @param z Initial Z-position [m]
   * @param vx Initial X-velocity [m/s]
   * @param vy Initial Y-velocity [m/s]
   * @param vz Initial Z-velocity [m/s]
   */
  Pianeta(double m, double x, double y, double z, double vx, double vy,
          double vz);

  /**
   * @brief Computes the Euclidean distance to another celestial body.
   *
   * @param other The target Pianeta object to measure distance against.
   * @return The scalar Euclidean distance in meters [m].
   */
  double compute_distance(const Pianeta &other) const;

  /**
   * @brief Computes and accumulates the gravitational force exerted by another
   * body.
   *
   * Applies Newton's law of universal gravitation. The computed force vector
   * is added to the internal force accumulators (fx, fy, fz).
   *
   * @param other The celestial body exerting the gravitational pull.
   */
  void compute_force(const Pianeta &other);

  /**
   * @brief Resets the accumulated force components to zero.
   *
   * Must be invoked prior to the N-body pair-wise force computation loop
   * at the beginning of each discrete time step.
   */
  void reset_force();

  // --- State Vector Accessors (Read-Only) ---
  // These getters were introduced during the "Make It Right" refactoring phase
  // to externalize the integration logic from Pianeta into IIntegrator.
  // By exposing read-only access to the internal state, the Pianeta class
  // adheres to the Single Responsibility Principle: it models the physical
  // entity, while the IIntegrator handles the mathematical time-stepping.

  /**
   * @brief Retrieves the X coordinate (Read-Only).
   *
   * The 'const' qualifier at the end of the method signature is known as
   * "Const Correctness". It explicitly guarantees to the compiler that calling
   * this method will NEVER modify the internal state variables (x, y, z, m) of
   * the Pianeta object. Without this, the compiler would prevent us from
   * reading coordinates from a 'const Pianeta' reference.
   *
   * @return double The current X coordinate in meters.
   */
  double getX() const;

  /**
   * @brief Retrieves the Y coordinate (Read-Only).
   * @return double The current Y coordinate in meters.
   */
  double getY() const;

  /**
   * @brief Retrieves the Z coordinate (Read-Only).
   * @return double The current Z coordinate in meters.
   */
  double getZ() const;

  /**
   * @brief Retrieves the X-component of the velocity vector (Read-Only).
   * @return double The current Vx in meters per second [m/s].
   */
  double getVx() const;

  /**
   * @brief Retrieves the Y-component of the velocity vector (Read-Only).
   * @return double The current Vy in meters per second [m/s].
   */
  double getVy() const;

  /**
   * @brief Retrieves the Z-component of the velocity vector (Read-Only).
   * @return double The current Vz in meters per second [m/s].
   */
  double getVz() const;

  /**
   * @brief Retrieves the X-component of the accumulated gravitational force.
   * @return double The net force Fx in Newtons [N].
   */
  double getForceX() const;

  /**
   * @brief Retrieves the Y-component of the accumulated gravitational force.
   * @return double The net force Fy in Newtons [N].
   */
  double getForceY() const;

  /**
   * @brief Retrieves the Z-component of the accumulated gravitational force.
   * @return double The net force Fz in Newtons [N].
   */
  double getForceZ() const;

  /**
   * @brief Computes and returns the instantaneous X-acceleration.
   *
   * Derived from Newton's Second Law: a = F/m. This method performs the
   * division on-the-fly rather than caching the result, ensuring the returned
   * value always reflects the most recently accumulated force state.
   *
   * @return double The acceleration ax in [m/s^2].
   */
  double getAccX() const;

  /**
   * @brief Computes and returns the instantaneous Y-acceleration (a = F/m).
   * @return double The acceleration ay in [m/s^2].
   */
  double getAccY() const;

  /**
   * @brief Computes and returns the instantaneous Z-acceleration (a = F/m).
   * @return double The acceleration az in [m/s^2].
   */
  double getAccZ() const;

  // --- State Vector Mutators ---
  // These setters enable the IIntegrator to write the updated kinematic state
  // back into the Pianeta after computing the numerical integration step.
  // By using explicit setter methods instead of public member variables, we
  // preserve encapsulation: the internal representation can change without
  // affecting external consumers.

  /** @brief Sets the X-component of the velocity vector [m/s]. */
  void setVx(double v_x);

  /** @brief Sets the Y-component of the velocity vector [m/s]. */
  void setVy(double v_y);

  /** @brief Sets the Z-component of the velocity vector [m/s]. */
  void setVz(double v_z);

  /** @brief Sets the X-coordinate of the spatial position [m]. */
  void setX(double x_pos);

  /** @brief Sets the Y-coordinate of the spatial position [m]. */
  void setY(double y_pos);

  /** @brief Sets the Z-coordinate of the spatial position [m]. */
  void setZ(double z_pos);
};