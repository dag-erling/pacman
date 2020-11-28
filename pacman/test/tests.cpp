#include <gtest/gtest.h>
#include "../lib/PacMan.hpp"

TEST(PacManTest, InitialPosition) {
  Board board;
  PacMan pacMan(board);
  EXPECT_EQ(pacMan.currentPosition().x, 14);
  EXPECT_EQ(pacMan.currentPosition().y, 23);
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}