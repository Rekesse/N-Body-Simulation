#include "SolarSystem.hpp"
#include "IIntegrator.hpp"
#include "Pianeta.hpp"
#include <vector>

// Constructor using a Member Initializer List for explicit dependency injection
SolarSystem::SolarSystem(IIntegrator *integrator) : integrator(integrator) {}

void SolarSystem::addPlanet(const Pianeta &planet) {
  universe.push_back(planet);
}

// Delegation: The SolarSystem does no math itself; it commands the active integrator.
void SolarSystem::integrate(double dt) { 
  integrator->doStep(universe, dt); 
}

// Getter returning a secure, read-only reference (&) to the internal state, preventing O(N) copies.
const std::vector<Pianeta> &SolarSystem::getUniverse() const {
  return universe;
}