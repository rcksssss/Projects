// Copyright 2024 <Thomas Boyajian>
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE SokobanTest
#include <fstream>
#include <sstream>
#include "Sokoban.hpp"
#include <boost/test/included/unit_test.hpp>
struct SokobanTestFixture {
    SokobanTestFixture() {
        // Basic level with box and wall
        std::stringstream basicLevel;
        basicLevel << "5 5\n"
                  << "#####\n"
                  << "#@.A#\n"
                  << "#.a.#\n"
                  << "#...#\n"
                  << "#####\n";
        game1.reset(new SB::Sokoban);
        basicLevel >> *game1;
        // Level with multiple boxes
        std::stringstream multiBoxLevel;
        multiBoxLevel << "5 5\n"
                     << "#####\n"
                     << "#@AA#\n"
                     << "#aaa#\n"
                     << "#...#\n"
                     << "#####\n";
        game2.reset(new SB::Sokoban);
        multiBoxLevel >> *game2;
        // Edge level (1x1, for strict boundary testing)
        std::stringstream edgeLevel;
        edgeLevel << "1 1\n"
                  << "@\n";
        game3.reset(new SB::Sokoban);
        edgeLevel >> *game3;
        // Many boxes and targets level
        std::stringstream manyBoxesLevel;
        manyBoxesLevel << "6 4\n"
                      << "######\n"
                      << "#@AAA#\n"
                      << "#aaaa#\n"
                      << "######\n";
        game4.reset(new SB::Sokoban);
        manyBoxesLevel >> *game4;
        // Symbol test level
        std::stringstream symbolLevel;
        symbolLevel << "3 3\n"
                   << "#@.#\n"
                   << "#.a#\n"
                   << "####\n";
        game5.reset(new SB::Sokoban);
        symbolLevel >> *game5;
    }
    std::unique_ptr<SB::Sokoban> game1;  // Basic level
    std::unique_ptr<SB::Sokoban> game2;  // Multiple box level
    std::unique_ptr<SB::Sokoban> game3;  // Edge level
    std::unique_ptr<SB::Sokoban> game4;  // Many boxes level
    std::unique_ptr<SB::Sokoban> game5;  // Symbol test level
};
BOOST_FIXTURE_TEST_SUITE(sokoban_tests, SokobanTestFixture)
// Tests that player cannot move beyond game boundaries
// Should: Stay in place when attempting to move off-screen in any direction
// Shouldn't: Allow movement outside level boundaries
BOOST_AUTO_TEST_CASE(test_off_screen_boundaries) {
    auto initialPos = game3->playerLoc();
    game3->movePlayer(SB::Direction::Left);
    BOOST_CHECK_EQUAL(game3->playerLoc().x, initialPos.x);
    game3->movePlayer(SB::Direction::Right);
    BOOST_CHECK_EQUAL(game3->playerLoc().x, initialPos.x);
    game3->movePlayer(SB::Direction::Up);
    BOOST_CHECK_EQUAL(game3->playerLoc().y, initialPos.y);
    game3->movePlayer(SB::Direction::Down);
    BOOST_CHECK_EQUAL(game3->playerLoc().y, initialPos.y);
}
// Tests victory conditions with multiple boxes
// Should: Only register victory when all boxes are on targets
// Shouldn't: Win with partial completion
BOOST_AUTO_TEST_CASE(test_multiple_boxes_and_targets) {
    auto initialPos = game4->playerLoc();
    BOOST_CHECK(!game4->isWon());
    game4->movePlayer(SB::Direction::Right);
    game4->movePlayer(SB::Direction::Down);
    BOOST_CHECK(!game4->isWon());
    game4->reset();
    BOOST_CHECK_EQUAL(game4->playerLoc().x, initialPos.x);
}
// Tests basic movement implementation
// Should: Allow movement into empty spaces
// Shouldn't: Stay stuck in starting position
BOOST_AUTO_TEST_CASE(test_cant_move) {
    auto initialPos = game1->playerLoc();
    game1->movePlayer(SB::Direction::Right);
    auto newPos = game1->playerLoc();
    bool moved = (newPos.x != initialPos.x);
    BOOST_CHECK(moved);
}
// Tests box blocking mechanics
// Should: Stop when encountering a box
// Shouldn't: Pass through boxes
BOOST_AUTO_TEST_CASE(test_box_blocking) {
    auto initialPos = game1->playerLoc();
    game1->movePlayer(SB::Direction::Right);
    game1->movePlayer(SB::Direction::Right);
    auto finalPos = game1->playerLoc();
    bool boxBlocks = (finalPos.x == initialPos.x + 1);
    BOOST_CHECK(boxBlocks);
}
// Tests box-wall collision
// Should: Prevent box from being pushed into wall
// Shouldn't: Allow boxes to move into walls
BOOST_AUTO_TEST_CASE(test_box_wall_collision) {
    game1->movePlayer(SB::Direction::Right);
    auto beforePushPos = game1->playerLoc();
    game1->movePlayer(SB::Direction::Right);
    auto afterPushPos = game1->playerLoc();
    BOOST_CHECK_EQUAL(afterPushPos.x, beforePushPos.x);
}
// Tests multiple box pushing mechanics
// Should: Prevent pushing multiple boxes at once
// Shouldn't: Allow movement when trying to push multiple boxes
BOOST_AUTO_TEST_CASE(test_multiple_box_collision) {
    auto initialPos = game2->playerLoc();
    game2->movePlayer(SB::Direction::Right);
    auto afterPushPos = game2->playerLoc();
    BOOST_CHECK_EQUAL(afterPushPos.x, initialPos.x);
}
BOOST_AUTO_TEST_SUITE_END()
