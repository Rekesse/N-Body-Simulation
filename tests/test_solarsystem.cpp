#include <gtest/gtest.h>
#include <EulerIntegrator.hpp>
#include <Planet.hpp>
#include <SolarSystem.hpp>
#include <Reader.hpp>



class SolarSystemTest : public::testing::Test{
    protected:
    EulerIntegrator integrator;
    std::map<std::string, std::array<double,6>> dataMapp;
    std::map<std::string, double> massDatabase;
    
    void SetUp(){
        Reader reader("../data");
        reader.readData();

        dataMapp = reader.getMap();

        massDatabase = {
            {"Earth.txt", 5.972e24}
        };
    };
};

TEST_F(SolarSystemTest, InitialisationPlanetSun){

    SolarSystem universe(&integrator, dataMapp, massDatabase);
    auto vector = universe.getUniverse();

    ASSERT_EQ(vector.size(),2u) << "Not enough planet!!!";

    EXPECT_DOUBLE_EQ(vector[0].m.value(),1.989e30)<<"Different mass for sun";
    EXPECT_NE(vector[1].pos.x.value(),0.0)<<"Earth";
}