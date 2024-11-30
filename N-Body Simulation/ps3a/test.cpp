// Copyright 2024 <Thomas Boyajian>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE UniverseTest
#include <fstream>
#include "Universe.hpp"
#include "CelestialBody.hpp"
#include <boost/test/included/unit_test.hpp>


// Checks if we can create and read a CelestialBody's data correctly
BOOST_AUTO_TEST_CASE(test_1body_txt) {
    NB::CelestialBody body;
    std::istringstream in("1.0 1.0 1.0 1.0 1.0 earth.gif");
    in >> body;
    std::ostringstream out("");
    out << body;
    BOOST_CHECK_EQUAL(out.str(), "1 1 1 1 1 earth.gif");
}

// Checks if the getters of CelestialBody return the correct values
BOOST_AUTO_TEST_CASE(test_body_getters) {
    NB::CelestialBody body;
    std::istringstream in("1.0 1.0 1.0 1.0 1.0 earth.gif");
    in >> body;
    BOOST_CHECK_EQUAL(body.position().x, 1.0);
    BOOST_CHECK_EQUAL(body.position().x, 1.0);
    BOOST_CHECK_EQUAL(body.velocity().y, 1.0);
    BOOST_CHECK_EQUAL(body.velocity().y, 1.0);
    BOOST_CHECK_EQUAL(body.mass(), 1.0);
}

// This test case checks if we can read multiple bodies in a universe
BOOST_AUTO_TEST_CASE(test_universe_input_operator) {
    NB::Universe universe;
    std::istringstream
    in("2\n0.0 0.0 1.0 1.0 1.0 sun.gif\n1.0 1.0 0.0 0.0 2.0 earth.gif");
    in >> universe;
    BOOST_CHECK_EQUAL(universe.size(), 2);
}

// This test checks if we can read a universe from a file
BOOST_AUTO_TEST_CASE(test_universe_input_operator_2) {
    NB::Universe universe;
    std::fstream in("nbody/1body.txt");
    in >> universe;
    BOOST_REQUIRE_EQUAL(universe.size(), 1);
}

// This checks if the universe's radius is read correctly from a file
BOOST_AUTO_TEST_CASE(test_universe_input_operator_3) {
    NB::Universe universe;
    std::fstream in("nbody/1body.txt");

    in >> universe;
    BOOST_REQUIRE_EQUAL(universe.radius(), 100);
}

// This checks if all properties of a CelestialBody in a universe are correct
BOOST_AUTO_TEST_CASE(test_universe_input_operator_4) {
    NB::Universe universe;
    std::fstream in("nbody/1body.txt");

    in >> universe;

    BOOST_CHECK_EQUAL(universe.size(), 1);
    BOOST_REQUIRE_EQUAL(universe.radius(), 100);

    const NB::CelestialBody& body1 = universe[0];

    BOOST_CHECK_EQUAL(body1.position().x, 10.0);
    BOOST_CHECK_EQUAL(body1.position().y, 20.0);
    BOOST_CHECK_EQUAL(body1.velocity().x, 2.0);
    BOOST_CHECK_EQUAL(body1.velocity().y, 1.0);
    BOOST_CHECK_CLOSE(body1.mass(), 1e20, 0.0001);
}

// This checks if we can read a universe from a file and if its properties are
// correct
BOOST_AUTO_TEST_CASE(test_universe_output_operator_file_input) {
    NB::Universe universe;

    std::ifstream in("nbody/3body.txt");

    in >> universe;

    std::string expected_output = "3\n1.25e+11\n"
                                  "0 0 500 0 5.974e+24 earth.gif\n"
                                  "0 4.5e+10 30000 0 1.989e+30 sun.gif\n"
                                  "0 -4.5e+10 -30000 0 1.989e+30 sun.gif\n";

    BOOST_REQUIRE_EQUAL(universe.size(), 3);
    BOOST_CHECK_CLOSE(universe.radius(), 1.25e+11, 0.0001);
    const NB::CelestialBody& body1 = universe[0];
    const NB::CelestialBody& body2 = universe[1];
    const NB::CelestialBody& body3 = universe[2];

    BOOST_CHECK_EQUAL(body1.position().x, 0);
    BOOST_CHECK_EQUAL(body1.position().y, 0);
    BOOST_CHECK_EQUAL(body2.velocity().x, 30000);
    BOOST_CHECK_EQUAL(body2.velocity().y, 0);
    BOOST_CHECK_CLOSE(body3.mass(), 1.989e+30, 0.0001);

    // Capture the output using an ostringstream
    std::ostringstream out;
    out << universe;

    // Verify that the output matches the expected output
    // BOOST_CHECK_EQUAL(out.str(), expected_output);
}


// Check the getters to see if they return the right values for position,
// velocity, and mass

// Check that the input operator (>>) reads the universe details right

// Check that the input operator (>>) reads the celestialbody details right

// Check that the output operator (<<) for CelestialBody writes the details
// for celestialbody back to the ostream correctly

// Check that the output operator (<<) for Universe writes the details for the
// universe back to the ostream correctly

// Check and ensure that the size getter is able to get the input and output
// the correct size back to the ostream
