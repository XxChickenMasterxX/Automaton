#include <iostream>
#include <iomanip>

#include "gtest/gtest.h"

#include "Automaton.h"

TEST(AutomatonTest, Empty) {
  	fa::Automaton fa;

  	EXPECT_EQ(fa.countStates(), 0u);
  	EXPECT_EQ(fa.countTransitions(), 0u);
}


/*
----------- TEST STATE -----------------
*/

// test addState
TEST(AutomatonTest, AddState) {
	fa::Automaton fa;
	fa.addState(1);
	EXPECT_EQ(fa.countStates(), 1u);
	EXPECT_EQ(fa.countTransitions(), 0u);
}

// test removeState
TEST(AutomatonTest, RemovePresentState) {
	fa::Automaton fa;
	fa.addState(1);
	fa.removeState(1);
	EXPECT_EQ(fa.countStates(), 0u);
	EXPECT_EQ(fa.countTransitions(), 0u);
}

TEST(AutomatonTest, RemoveNotPresentState) {
	fa::Automaton fa;
	fa.removeState(1);
	EXPECT_EQ(fa.countStates(), 0u);
	EXPECT_EQ(fa.countTransitions(), 0u);
}

// test hasState
TEST(AutomatonTest, hasStateTrue) {
	fa::Automaton fa;
	fa.addState(1);
	EXPECT_TRUE(fa.hasState(1));
	EXPECT_EQ(fa.countTransitions(), 0u);
}

TEST(AutomatonTest, hasStateFalse) {
	fa::Automaton fa;
	EXPECT_FALSE(fa.hasState(1));
	EXPECT_EQ(fa.countTransitions(), 0u);
}

// test countState
TEST(AutomatonTest, countState) {
	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.addState(3);
	fa.addState(1);
	EXPECT_EQ(fa.countStates(), 3u);
	fa.removeState(1);
	EXPECT_EQ(fa.countStates(), 2u);
	EXPECT_EQ(fa.countTransitions(), 0u);
}

// test setStateInitial
TEST(AutomatonTest, setStateInitial) {
	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	EXPECT_TRUE(fa.isStateInitial(1));
}

// test isStateInitial
TEST(AutomatonTest, isStateInitialTrue) {
	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	EXPECT_TRUE(fa.isStateInitial(1));
}

TEST(AutomatonTest, isStateInitialFalse) {
	fa::Automaton fa;
	fa.addState(1);
	EXPECT_FALSE(fa.isStateInitial(1));
}

TEST(AutomatonTest, isStateInitialNotPresentState) {
	fa::Automaton fa;
	EXPECT_FALSE(fa.isStateInitial(1));
}

// test setStateFinal
TEST(AutomatonTest, setStateFinal) {
	fa::Automaton fa;
	fa.addState(1);
	fa.setStateFinal(1);
	EXPECT_TRUE(fa.isStateFinal(1));
}

// test isStateFinal
TEST(AutomatonTest, isStateFinalTrue) {
	fa::Automaton fa;
	fa.addState(1);
	fa.setStateFinal(1);
	EXPECT_TRUE(fa.isStateFinal(1));
}

TEST(AutomatonTest, isStateFinalFalse) {
	fa::Automaton fa;
	fa.addState(1);
	EXPECT_FALSE(fa.isStateFinal(1));
}

TEST(AutomatonTest, isStateFinalNotPresentState) {
	fa::Automaton fa;
	EXPECT_FALSE(fa.isStateFinal(1));
}

/*
----------- TEST TRANSITION -----------------
*/

// test addTransition
TEST(AutomatonTest, addTransition) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.addTransition(1,'a',1);
  	EXPECT_EQ(fa.countStates(), 1u);
  	EXPECT_EQ(fa.countTransitions(), 1u);
}

// test hasTransition
TEST(AutomatonTest, hasTransitionTrue) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.addTransition(1,'a',1);
	EXPECT_TRUE(fa.hasTransition(1,'a',1));
  	EXPECT_EQ(fa.countStates(), 1u);
  	EXPECT_EQ(fa.countTransitions(), 1u);
}

TEST(AutomatonTest, hasTransitionWithNoState) {
  	fa::Automaton fa;
	fa.addTransition(1,'a',1);
	EXPECT_FALSE(fa.hasTransition(1,'a',1));
  	EXPECT_EQ(fa.countStates(), 0u);
  	EXPECT_EQ(fa.countTransitions(), 0u);
}

TEST(AutomatonTest, hasTransitionWithRemovedStateFrom) {
 	fa::Automaton fa;
  	fa.addState(1);
  	fa.addState(2);
	fa.addTransition(1,'a',2);
	EXPECT_TRUE(fa.hasTransition(1,'a',2));
  	EXPECT_EQ(fa.countStates(), 2u);
  	EXPECT_EQ(fa.countTransitions(), 1u);
  	fa.removeState(1);
  	EXPECT_FALSE(fa.hasTransition(1,'a',2));
  	EXPECT_EQ(fa.countStates(), 1u);
  	EXPECT_EQ(fa.countTransitions(), 0u);
}

TEST(AutomatonTest, hasTransitionWithRemovedStateTo) {
 	fa::Automaton fa;
  	fa.addState(1);
  	fa.addState(2);
	fa.addTransition(1,'a',2);
	EXPECT_TRUE(fa.hasTransition(1,'a',2));
  	EXPECT_EQ(fa.countStates(), 2u);
  	EXPECT_EQ(fa.countTransitions(), 1u);
  	fa.removeState(2);
  	EXPECT_FALSE(fa.hasTransition(1,'a',2));
  	EXPECT_EQ(fa.countStates(), 1u);
  	EXPECT_EQ(fa.countTransitions(), 0u);
}

TEST(AutomatonTest, hasTransitionFalse) {
  	fa::Automaton fa;
	fa.addState(1);
	EXPECT_FALSE(fa.hasTransition(1,'a',1));
  	EXPECT_EQ(fa.countStates(), 1u);
  	EXPECT_EQ(fa.countTransitions(), 0u);
}

// test removeTransition
TEST(AutomatonTest, removeTransition) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.addTransition(1,'a',1);
	EXPECT_TRUE(fa.hasTransition(1,'a',1));
	EXPECT_EQ(fa.countTransitions(), 1u);
	fa.removeTransition(1,'a',1);
  	EXPECT_EQ(fa.countStates(), 1u);
  	EXPECT_EQ(fa.countTransitions(), 0u);
}

// test countTransition
TEST(AutomatonTest, countTransition) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.addTransition(1,'a',1);
	fa.addTransition(1,'a',1);
	fa.addTransition(1,'b',1);
	fa.addTransition(2,'a',1);
	fa.addTransition(1,'a',2);
  	EXPECT_EQ(fa.countStates(), 2u);
  	EXPECT_EQ(fa.countTransitions(), 4u);
}

// test getAlphabetSize
TEST(AutomatonTest, alphabetSizeSimple) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.addTransition(1,'a',1);
  	EXPECT_EQ(fa.getAlphabetSize(), 1u);
}

TEST(AutomatonTest, alphabetSizeLessSimple) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.addTransition(1,'a',1);
	fa.addTransition(1,'a',1);
	fa.addTransition(1,'b',1);
	fa.addTransition(2,'a',1);
	fa.addTransition(1,'a',2);
  	EXPECT_EQ(fa.getAlphabetSize(), 2u);
}

// test isDeterministic

int main(int argc, char **argv) {
  	::testing::InitGoogleTest(&argc, argv);
  	return RUN_ALL_TESTS();
}

