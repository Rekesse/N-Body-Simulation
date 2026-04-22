#pragma once

#include <Types.hpp>

struct Planet {
  Mass m;
  Position3D pos;
  Velocity3D vel;
  VForce force;

  /*
  * 1. MASS IS REQUIRED: 
  You cannot create a planet without mass. If you don't provide it, 
  the compiler will throw an error. This prevents physics bugs (like dividing by zero).
  * 2. POSITION AND VELOCITY ARE OPTIONAL (FLEXIBLE CREATION):
  If you provide them, the planet spawns exactly where you want it, moving 
  at the correct speed. If you don't, it defaults to (0,0,0) and stands still.
  * 3. WHY IS FORCE MISSING FROM THE INPUTS?
  When a planet is first created (Time = 0), it hasn't interacted with 
  anything yet. Therefore, the user should never manually set a starting force.
  Instead, we automatically set it to zero using `force(VForce())`. 
  The physics engine will calculate the real gravitational force later.
  */

  Planet(Mass mass, Position3D position = Position3D(),
         Velocity3D velocity = Velocity3D())
      : m(mass), pos(position), vel(velocity), force(VForce()) {}

  void compute_force(const Planet &other);
  void reset_force();
  Acceleration3D get_acc() const;
};
