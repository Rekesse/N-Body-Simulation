#include <SolarSystem.hpp>
#include <IIntegrator.hpp>
#include <Pianeta.hpp>

// Constructor using a Member Initializer List for explicit dependency injection
SolarSystem::SolarSystem(IIntegrator *integrator, const std::map<std::string, std::array<double,6>>& dataMapp,
const std::map<std::string, double>& massDatabase ): integrator(integrator) {
  addPlanet(Planet(Mass(1.989e30)));
  for(auto &[name, mass] : massDatabase){
    Mass m(mass);
    auto it_data = dataMapp.find(name);
    
    if(it_data == dataMapp.end()){
      continue;
    }

    const auto& data = it_data->second;

    Position3D p = {
      // data[n] should be faster then data.at(n) 
      .x = Distance(data[0]),
      .y = Distance(data[1]),
      .z = Distance(data[2])
    };
    Velocity3D v = {
      .x = Speed(data[3]),
      .y = Speed(data[4]),
      .z = Speed(data[5])
    };
    addPlanet(Planet(m,p,v));
  };
}

void SolarSystem::addPlanet(const Planet &planet) {
  universe.push_back(planet);
}

// Delegation: The SolarSystem does no math itself; it commands the active integrator.
void SolarSystem::integrate(Time dt) { 
  integrator->doStep(universe, dt); 
}

// Getter returning a secure, read-only reference (&) to the internal state, preventing O(N) copies.
const std::vector<Planet> &SolarSystem::getUniverse() const {
  return universe;
}