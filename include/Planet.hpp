#pragma once

#include <Types.hpp>

struct Planet {
  Mass m;
  Position3D pos;
  Velocity3D vel;
  VForce force;

  Planet(Mass mass, Position3D position = Position3D(),
         Velocity3D velocity = Velocity3D())
      : m(mass), pos(position), vel(velocity), force(VForce()) {}

  void compute_force(const Planet &other);
  void reset_force();
  Acceleration3D get_acc() const;
};
