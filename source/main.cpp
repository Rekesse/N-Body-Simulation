#include <Planet.hpp>
#include <string>
#include <vector>

#include "EulerIntegrator.hpp"
#include "Pianeta.hpp"
#include "Planet.hpp"
#include "Reader.hpp"
#include "SolarSystem.hpp"
#include "Types.hpp"
#include <matplotlibcpp.h>
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
  SolarSystem solarSystem(&eulerIntegrator);

  Reader reader("../Data");
  reader.readData();
  auto data_map = reader.getMap();

  Planet sun_(Mass(1.989e30));

  Pianeta sun(1.989e30, 0, 0, 0, 0, 0, 0);
  solarSystem.addPlanet(sun);
  Pianeta earth(5.972e24, data_map.at("Earth.txt").at(0),
                data_map.at("Earth.txt").at(1), data_map.at("Earth.txt").at(2),
                data_map.at("Earth.txt").at(3), data_map.at("Earth.txt").at(4),
                data_map.at("Earth.txt").at(5));
  solarSystem.addPlanet(earth);
  int dt{86400};

  std::vector<double> earth_x, earth_y;
  std::vector<double> sun_x, sun_y;

  for (int step{0}; step < 365; step++) {
    solarSystem.integrate(dt);

    const std::vector<Pianeta> &univ = solarSystem.getUniverse();
    sun_x.push_back(univ[0].getX());
    sun_y.push_back(univ[0].getY());
    earth_x.push_back(univ[1].getX());
    earth_y.push_back(univ[1].getY());
  }

  matplotlibcpp::plot(earth_x, earth_y, "b-");
  matplotlibcpp::plot(sun_x, sun_y, "yo");

  matplotlibcpp::show();

  return 0;
}
