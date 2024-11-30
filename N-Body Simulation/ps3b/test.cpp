// Copyright 2024 <Thomas Boyajian>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE UniverseTest
#include <fstream>
#include <sstream>
#include <cmath>
#include "Universe.hpp"
#include "CelestialBody.hpp"
#include <boost/test/included/unit_test.hpp>

// Value used for floating-point comparisons
const double EPSILON = 1e-6;

// This test checks if we can read a universe from a file
BOOST_AUTO_TEST_CASE(test_universe_input_operator_2) {
    NB::Universe universe;
    std::fstream in("nbody/1body.txt");
    in >> universe;

    universe.step(1000);
    BOOST_REQUIRE_EQUAL(universe[0].getPosition().x, 2010);
    BOOST_REQUIRE_EQUAL(universe[0].getPosition().y, 1020);
}

 /*BOOST_AUTO_TEST_CASE(test_universe_input_operator_3) {
    
     NB::Universe universe;
     std::fstream in("nbody/3body-zero-gravity.txt");
    in >> universe;

    
     // Verify universe size and radius
     BOOST_REQUIRE_EQUAL(universe.size(), 3);
     BOOST_CHECK_EQUAL(universe.radius(), 512);

     const NB::CelestialBody& earth = universe[0];
     BOOST_CHECK_EQUAL(earth.getPosition().x, 0.0);
     BOOST_CHECK_EQUAL(earth.getPosition().y, 128.0);
     BOOST_CHECK_EQUAL(earth.velocity().x, 1.0);
     BOOST_CHECK_EQUAL(earth.velocity().y, 2.0);
     BOOST_CHECK_EQUAL(earth.mass(), 1e-50);

     const NB::CelestialBody& venus = universe[1];
     BOOST_CHECK_EQUAL(venus.getPosition().x, 0.0);
     BOOST_CHECK_EQUAL(venus.getPosition().y, 128.0);
     BOOST_CHECK_EQUAL(venus.velocity().x, 1.0);
     BOOST_CHECK_EQUAL(venus.velocity().y, 2.0);
     BOOST_CHECK_EQUAL(venus.mass(), 1e-50);

     const NB::CelestialBody& mars = universe[2];
     BOOST_CHECK_EQUAL(mars.getPosition().x, 0.0);
     BOOST_CHECK_EQUAL(mars.getPosition().y, 128.0);
     BOOST_CHECK_EQUAL(mars.velocity().x, 1.0);
     BOOST_CHECK_EQUAL(mars.velocity().y, 2.0);
     BOOST_CHECK_EQUAL(mars.mass(), 1e-50);

 }*/

BOOST_AUTO_TEST_CASE(test_initial_movement) {
    NB::Universe universe;
    std::fstream in("nbody/planets.txt");
    in >> universe;

    universe.step(1);

    BOOST_CHECK_EQUAL(universe[0].getPosition().x, 149600000000);
    BOOST_CHECK_CLOSE(universe[0].getPosition().y, 29800, EPSILON);
    BOOST_CHECK_EQUAL(universe[1].getPosition().x, 227899998000);
    BOOST_CHECK_CLOSE(universe[1].getPosition().y, 24100, EPSILON);
    BOOST_CHECK_EQUAL(universe[2].getPosition().x, 57899999200);
    BOOST_CHECK_CLOSE(universe[2].getPosition().y, 47900, EPSILON);
}

 /*BOOST_AUTO_TEST_CASE(test_no_acceleration) {
     NB::Universe universe;
     std::ifstream in("nbody/3body-zero-gravity.txt");
     BOOST_REQUIRE(in.is_open());
     in >> universe;

     universe.BOOST_CHECK_EQUALstep(1000);  

     const NB::CelestialBody& earth = universe[0];
     BOOST_CHECK_CLOSE(earth.velocity().x, 1.0, EPSILON);
     BOOST_CHECK_CLOSE(earth.velocity().y, 1.0, EPSILON);

     const NB::CelestialBody& venus = universe[1];
     BOOST_CHECK_CLOSE(venus.velocity().x, 2.0, EPSILON);
     BOOST_CHECK_CLOSE(venus.velocity().y, 1.0, EPSILON);

    const NB::CelestialBody& mars = universe[2];
     BOOST_CHECK_CLOSE(mars.velocity().x, 1.0, EPSILON);
     BOOST_CHECK_CLOSE(mars.velocity().y, 2.0, EPSILON);
}*/

/*BOOST_AUTO_TEST_CASE(test_leapfrog_integration) {
    NB::Universe universe;
    std::ifstream in("nbody/3body-zero-gravity.txt"); 
    in >> universe;

    universe.step(1000);

    const NB::CelestialBody& earth = universe[0];
    BOOST_CHECK(earth.getPosition().x != 0.0); 
    BOOST_CHECK(earth.velocity().y != 0.0); 
}*/


/*
BOOST_AUTO_TEST_CASE(test_universe_input_operator_4) {
    
    NB::Universe universe;
    std::fstream in("nbody/3body-zero-gravity.txt");
    in >> universe;

    
    // Verify universe size and radius
    BOOST_REQUIRE_EQUAL(universe.size(),3);
    BOOST_CHECK_CLOSE(universe.radius(), 512, 0.0001);

    const NB::CelestialBody& earth = universe[0];
    BOOST_CHECK_CLOSE(earth.getPosition().x, 0, 0.0001);
    BOOST_CHECK_CLOSE(earth.getPosition().y, 0, 0.0001);
    BOOST_CHECK_CLOSE(earth.velocity().x, 3.40282e38, 0.0001);
    BOOST_CHECK_CLOSE(earth.velocity().y, 3.40282e38, 0.0001);
    BOOST_CHECK_CLOSE(earth.mass(), 1e-30, 0.0001);

    const NB::CelestialBody& venus = universe[1];
    BOOST_CHECK_CLOSE(venus.getPosition().x, 128, 0.0001);
    BOOST_CHECK_CLOSE(venus.getPosition().y, 0, 0.0001);
    BOOST_CHECK_CLOSE(venus.velocity().x, 3.40282e38, 0.0001);
    BOOST_CHECK_CLOSE(venus.velocity().y, 3.40282e38, 0.0001);
    BOOST_CHECK_CLOSE(venus.mass(), 1e-40, 0.0001);

    const NB::CelestialBody& mars = universe[2];
    BOOST_CHECK_CLOSE(mars.getPosition().x, 0, 0.0001);
    BOOST_CHECK_CLOSE(mars.getPosition().y, 128, 0.0001);
    BOOST_CHECK_CLOSE(mars.velocity().x, 3.40282e38, 0.0001);
    BOOST_CHECK_CLOSE(mars.velocity().y, 3.40282e38, 0.0001);
    BOOST_CHECK_CLOSE(mars.mass(), 1e-50, 0.0001);

}*/

// Check the getters to see if they return the right values for getPosition,
// velocity, and mass

// Check that the input operator (>>) reads the universe details right

// Check that the input operator (>>) reads the celestialbody details right

// Check that the output operator (<<) for CelestialBody writes the details
// for celestialbody back to the ostream correctly

// Check that the output operator (<<) for Universe writes the details for the
// universe back to the ostream correctly

// Check and ensure that the size getter is able to get the input and output
// the correct size back to the ostream
