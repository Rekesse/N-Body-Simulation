#include <Planet.hpp>
#include <string>
#include <vector>

#include "EulerIntegrator.hpp"
#include "Pianeta.hpp"
#include "Planet.hpp"
#include "Reader.hpp"
#include "SolarSystem.hpp"
#include "Types.hpp"
//#include <matplotlibcpp.h>


/**
 * @file main.cpp
 * @brief Entry point for the N-Body Simulation formulation.
 *
 * Handles the ingestion of initial empirical Data from the NASA Horizons
 * Ephemeris System, executing unit normalization, and bootstrapping the
 * computational Universe.
 */
int main() {

  EulerIntegrator eulerIntegrator;
  
  Reader reader("../Data");
  reader.readData();
  const auto& data_map = reader.getMap();
  std::map<std::string, double> massDatabase = {
    {"Earth.txt",5.972e24}
  };
  
  SolarSystem solarSystem(&eulerIntegrator, data_map, massDatabase);

  // Planet sun(Mass(1.989e30));
  // solarSystem.addPlanet(sun);

  // Pianeta sun(1.989e30, 0, 0, 0, 0, 0, 0);
  // Planet earth(Mass(5.972e24), earth_data.at(0),
  //               data_map.at("Earth.txt").at(1), data_map.at("Earth.txt").at(2),
  //               data_map.at("Earth.txt").at(3), data_map.at("Earth.txt").at(4),
  //               data_map.at("Earth.txt").at(5));
  // solarSystem.addPlanet(earth);
  Time t(86400);

  std::vector<Position3D> earth_coord;
  std::vector<Position3D> sun_coord;

  for (int step{0}; step < 365; step++) {
    solarSystem.integrate(t);

    //const std::vector<Planet> &univ = solarSystem.getUniverse();

    sun_coord.push_back(solarSystem.getUniverse()[0].pos);
    earth_coord.push_back(solarSystem.getUniverse()[1].pos);
  }

  // matplotlibcpp::plot(earth_x, earth_y, "b-");
  // matplotlibcpp::plot(sun_x, sun_y, "yo");

  // matplotlibcpp::show();

  return 0;
}
