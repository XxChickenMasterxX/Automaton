#include <iostream>
#include <iomanip>

#include "gtest/gtest.h"

#include "Automaton.h"

TEST(AutomatonTest, Empty) {
  fa::Automaton fa;

  EXPECT_EQ(fa.countStates(), 0u);
  EXPECT_EQ(fa.countTransitions(), 0u);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
