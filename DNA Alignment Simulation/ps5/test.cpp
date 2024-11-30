// Copyright 2024 <Thomas Boyajian>
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE EDistance_Tests
#include <fstream>
#include <string>
#include "EDistance.hpp"
#include <boost/test/included/unit_test.hpp>

// Helper function to read input strings from stdin
std::pair<std::string, std::string> readStrings(std::istream& input) {
    std::string str1, str2;
    std::getline(input, str1);
    std::getline(input, str2);
    if (!str1.empty() && str1.back() == '\r') str1.pop_back();
    if (!str2.empty() && str2.back() == '\r') str2.pop_back();
    return {str1, str2};
}

// Helper function to calculate total alignment cost
int calculateAlignmentCost(const std::string& alignment) {
    int total_cost = 0;
    std::string remaining = alignment;
    size_t pos = 0;
    while ((pos = remaining.find('\n')) != std::string::npos) {
        total_cost += remaining[pos - 1] - '0';
        remaining = remaining.substr(pos + 1);
    }
    return total_cost;
}

BOOST_AUTO_TEST_SUITE(EDistanceTests)

// Test for verifying correct cost calculation and alignment format
BOOST_AUTO_TEST_CASE(WrongCostTest) {
    std::string str1 = "ACGT";
    std::string str2 = "TGCA";

    EDistance ed(str1, str2);
    int opt_cost = ed.optDistance();
    std::string alignment = ed.alignment();
    int align_cost = calculateAlignmentCost(alignment);

    BOOST_CHECK_MESSAGE(opt_cost == align_cost,
        "Optimal cost (" << opt_cost << ") doesn't match alignment cost (" << align_cost << ")");

    size_t expected_lines = std::max(str1.length(), str2.length());
    size_t actual_lines = 0;
    std::string temp = alignment;
    size_t pos = 0;
    while ((pos = temp.find('\n')) != std::string::npos) {
        actual_lines++;
        std::string line = temp.substr(0, pos);
        BOOST_CHECK_MESSAGE(line.length() >= 5, "Invalid alignment line format");
        BOOST_CHECK_MESSAGE(line[1] == ' ' && line[3] == ' ', "Invalid spacing in alignment");
        BOOST_CHECK_MESSAGE(std::isdigit(line[4]), "Invalid cost in alignment");
        temp = temp.substr(pos + 1);
    }
    BOOST_CHECK_MESSAGE(actual_lines == expected_lines,
        "Alignment length (" << actual_lines
         << ") doesn't match expected length (" << expected_lines << ")");
}

// Test for checking if alignment is reversed
BOOST_AUTO_TEST_CASE(Reversed) {
    std::string str1 = "CAG";
    std::string str2 = "GAC";
    EDistance ed(str1, str2);
    std::string expected =
        "C G 1\n"
        "A A 0\n"
        "G C 1\n";
    ed.optDistance();
    BOOST_REQUIRE_EQUAL(expected, ed.alignment());
}

// Test for verifying correct column ordering
BOOST_AUTO_TEST_CASE(SwappedCols) {
    std::string str1 = "ACGT";
    std::string str2 = "TGCA";
    EDistance ed(str1, str2);
    std::string expected =
        "A T 1\n"
        "C G 1\n"
        "G C 1\n"
        "T A 1\n";
    ed.optDistance();
    BOOST_REQUIRE_EQUAL(expected, ed.alignment());
}

// Test for checking complete alignment including end characters
BOOST_AUTO_TEST_CASE(CutEnds) {
    std::string str1 = "AGTC";
    std::string str2 = "AGC";
    EDistance ed(str1, str2);
    std::string expected =
        "A A 0\n"
        "G G 0\n"
        "T - 2\n"
        "C C 0\n";
    ed.optDistance();
    BOOST_REQUIRE_EQUAL(expected, ed.alignment());
}

// Test for verifying correct matrix traversal direction
BOOST_AUTO_TEST_CASE(WrongDirection) {
    std::string str1 = "ATCG";
    std::string str2 = "TCG";
    EDistance ed(str1, str2);
    std::string expected =
        "A - 2\n"
        "T T 0\n"
        "C C 0\n"
        "G G 0\n";
    ed.optDistance();
    BOOST_REQUIRE_EQUAL(expected, ed.alignment());
}

BOOST_AUTO_TEST_SUITE_END()
