#include <gtest/gtest.h>
#include <EulerIntegrator.hpp>
#include <Planet.hpp>
#include <SolarSystem.hpp>


TEST(SolarSystemTest, InitialisationPlanetSun){
    EulerIntegrator integrator;
    std::map<std::string, std::array<double,6>> dataMapp;
    std::map<std::string, double> massDatabase;

    SolarSystem universe(&integrator, dataMapp, massDatabase);
    auto vector = universe.getUniverse();

    EXPECT_EQ(vector.size(),1);
    EXPECT_DOUBLE_EQ(vector[0].m.value(),1.989e30);
}