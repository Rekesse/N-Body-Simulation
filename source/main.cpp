#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "EulerIntegrator.hpp"
#include "Pianeta.hpp"
#include "SolarSystem.hpp"
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
  // Open the localized data source file containing planetary ephemerides
  std::ifstream fs("../Data/Earth.txt");
  std::string line;

  EulerIntegrator eulerIntegrator;
  SolarSystem solarSystem(&eulerIntegrator);

  Pianeta sun(1.989e30, 0, 0, 0, 0, 0, 0);
  solarSystem.addPlanet(sun);
  int dt{86400};

  std::vector<double> earth_x, earth_y;
  std::vector<double> sun_x, sun_y;

  if (!fs.is_open()) {
    return 1;
  }

  // Parse the file stream iteratively until exhaustion
  while (std::getline(fs, line)) {
    // NASA Horizons system designates the Start of Ephemeris (SOE) data block
    // with "$$SOE"
    if (line == "$$SOE") {
      // Extract the immediate subsequent line containing the empirical state
      // vectors
      std::getline(fs, line);
      std::stringstream ss(line);
      std::string word;

      // Discard preceding temporal coordinate columns (Julian Date, Calendar
      // Date)
      std::getline(ss, word, ',');
      std::getline(ss, word, ',');

      // Parse Cartesian elements mapping structural transformation from [km] to
      // [m] (SI Units) X-axis celestial coordinate

      std::getline(ss, word, ',');
      double x{std::stod(word) * 1000.0};
      // Y-axis celestial coordinate
      std::getline(ss, word, ',');
      double y{std::stod(word) * 1000.0};
      // Z-axis celestial coordinate
      std::getline(ss, word, ',');
      double z{std::stod(word) * 1000.0};
      // X-axis velocity vector invariant
      std::getline(ss, word, ',');
      double vx{std::stod(word) * 1000.0};
      // Y-axis velocity vector invariant
      std::getline(ss, word, ',');
      double vy{std::stod(word) * 1000.0};
      // Z-axis velocity vector invariant
      std::getline(ss, word, ',');
      double vz{std::stod(word) * 1000.0};

      // Instantiate the celestial entity with Earth's invariant inertial mass
      // [kg]
      Pianeta earth(5.973e24, x, y, z, vx, vy, vz);

      // Inject the entity into the global simulation spatial domain
      solarSystem.addPlanet(earth);

      break;
    }
  }

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
