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

//--------------------------------------------------------
//---------------------- addState ------------------------
//--------------------------------------------------------
TEST(AutomatonTest, AddState) {
	fa::Automaton fa;
	fa.addState(1);
	EXPECT_EQ(fa.countStates(), 1u);
	EXPECT_EQ(fa.countTransitions(), 0u);
}

TEST(AutomatonTest, AddStateAlreadyAdded) {
	fa::Automaton fa;
	fa.addState(1);
	EXPECT_DEATH(fa.addState(1),"");
}

//--------------------------------------------------------
//-------------------- removeState -----------------------
//--------------------------------------------------------
TEST(AutomatonTest, RemovePresentState) {
	fa::Automaton fa;
	fa.addState(1);
	fa.removeState(1);
	EXPECT_EQ(fa.countStates(), 0u);
	EXPECT_EQ(fa.countTransitions(), 0u);
}

TEST(AutomatonTest, RemoveNotPresentState) {
	fa::Automaton fa;
	EXPECT_DEATH(fa.removeState(1),"");
	EXPECT_EQ(fa.countStates(), 0u);
	EXPECT_EQ(fa.countTransitions(), 0u);
}

TEST(AutomatonTest, RemoveJustTheSpecifiedState) {
	fa::Automaton fa;
	fa.addState(1);
	fa.addState(0);
	fa.removeState(1);
	EXPECT_EQ(fa.countStates(), 1u);
	EXPECT_EQ(fa.countTransitions(), 0u);
}

//--------------------------------------------------------
//---------------------- hasState ------------------------
//--------------------------------------------------------
TEST(AutomatonTest, hasStateTrue) {
	fa::Automaton fa;
	fa.addState(1);
	EXPECT_TRUE(fa.hasState(1));
	EXPECT_EQ(fa.countStates(), 1u);
	EXPECT_EQ(fa.countTransitions(), 0u);
}

TEST(AutomatonTest, hasStateFalse) {
	fa::Automaton fa;
	EXPECT_FALSE(fa.hasState(1));
	EXPECT_EQ(fa.countStates(), 0u);
	EXPECT_EQ(fa.countTransitions(), 0u);
}

//--------------------------------------------------------
//--------------------- countState -----------------------
//--------------------------------------------------------
TEST(AutomatonTest, Count0State) {
	fa::Automaton fa;
	EXPECT_EQ(fa.countStates(), 0u);
}

TEST(AutomatonTest, Count1State) {
	fa::Automaton fa;
	fa.addState(1);
	EXPECT_EQ(fa.countStates(), 1u);
}

TEST(AutomatonTest, Count1StateThenRemove) {
	fa::Automaton fa;
	fa.addState(1);
	fa.removeState(1);
	EXPECT_EQ(fa.countStates(), 0u);
}

TEST(AutomatonTest, countManyState) {
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

TEST(AutomatonTest, countManyStateThenRemoveOne) {
	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.addState(3);
	EXPECT_EQ(fa.countStates(), 3u);
	fa.removeState(1);
	EXPECT_EQ(fa.countStates(), 2u);
}

TEST(AutomatonTest, countManyStateThenRemoveAll) {
	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.addState(3);
	EXPECT_EQ(fa.countStates(), 3u);
	fa.removeState(1);
	fa.removeState(2);
	fa.removeState(3);
	EXPECT_EQ(fa.countStates(), 0u);
}

//--------------------------------------------------------
//------------------- setStateInitial --------------------
//--------------------------------------------------------
TEST(AutomatonTest, setStateInitialGhost) {
	fa::Automaton fa;
	EXPECT_DEATH(fa.setStateInitial(1), "");
}

TEST(AutomatonTest, setStateInitialOne) {
	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	EXPECT_EQ(fa.countStates(), 1u);
	EXPECT_TRUE(fa.hasState(1));
	EXPECT_TRUE(fa.isStateInitial(1));
}

TEST(AutomatonTest, setStateInitialWhenIsAlreadyFinal) {
	fa::Automaton fa;
	fa.addState(1);
	fa.setStateFinal(1);
	
	fa.setStateInitial(1);
	
	EXPECT_TRUE(fa.isStateFinal(1));
	EXPECT_EQ(fa.countStates(), 1u);
	EXPECT_TRUE(fa.hasState(1));
	EXPECT_TRUE(fa.isStateInitial(1));
}

TEST(AutomatonTest, setAlreadyInitialState) {
	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	EXPECT_EQ(fa.countStates(), 1u);
	EXPECT_TRUE(fa.hasState(1));
	EXPECT_TRUE(fa.isStateInitial(1));
	fa.setStateInitial(1);
	EXPECT_EQ(fa.countStates(), 1u);
	EXPECT_TRUE(fa.hasState(1));
	EXPECT_TRUE(fa.isStateInitial(1));
}

//--------------------------------------------------------
//------------------- isStateInitial ---------------------
//--------------------------------------------------------

TEST(AutomatonTest, isStateInitialTrue) {
	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	EXPECT_TRUE(fa.isStateInitial(1));
}

TEST(AutomatonTest, isStateInitialFalseWithNoInitialState) {
	fa::Automaton fa;
	fa.addState(1);
	EXPECT_FALSE(fa.isStateInitial(1));
}

TEST(AutomatonTest, isFinalStateInitialTrue) {
	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
    fa.setStateFinal(1);
	EXPECT_TRUE(fa.isStateInitial(1));
}

TEST(AutomatonTest, isStateInitialFalseWithFinalState) {
	fa::Automaton fa;
	fa.addState(1);
    fa.setStateFinal(1);
	EXPECT_FALSE(fa.isStateInitial(1));
}

TEST(AutomatonTest, isStateInitialNotPresentState) {
	fa::Automaton fa;
	EXPECT_DEATH(fa.isStateInitial(1), "");
}

//--------------------------------------------------------
//-------------------- setStateFinal ---------------------
//--------------------------------------------------------
TEST(AutomatonTest, setStateFinalNotPresentState) {
	fa::Automaton fa;
	EXPECT_DEATH(fa.setStateFinal(1), "");
}

TEST(AutomatonTest, setStateFinal) {
	fa::Automaton fa;
	fa.addState(1);
	fa.setStateFinal(1);
    EXPECT_TRUE(fa.hasState(1));
	EXPECT_TRUE(fa.isStateFinal(1));
}

TEST(AutomatonTest, setStateInitialFinal) {
	fa::Automaton fa;
	fa.addState(1);
    fa.setStateInitial(1);
	fa.setStateFinal(1);
    EXPECT_TRUE(fa.hasState(1));
    EXPECT_TRUE(fa.isStateInitial(1));
	EXPECT_TRUE(fa.isStateFinal(1));
}

TEST(AutomatonTest, setStateFinalFinal) {
	fa::Automaton fa;
	fa.addState(1);
	fa.setStateFinal(1);
    fa.setStateFinal(1);
    EXPECT_TRUE(fa.hasState(1));
	EXPECT_TRUE(fa.isStateFinal(1));
}

//--------------------------------------------------------
//-------------------- isStateFinal --------------------
//--------------------------------------------------------
TEST(AutomatonTest, isStateFinalNotPresentState) {
	fa::Automaton fa;
	EXPECT_DEATH(fa.isStateFinal(1),"");
}

TEST(AutomatonTest, isLambdaStateFinal) {
	fa::Automaton fa;
	fa.addState(1);
	EXPECT_FALSE(fa.isStateFinal(1));
}

TEST(AutomatonTest, isStateFinalTrue) {
	fa::Automaton fa;
	fa.addState(1);
	fa.setStateFinal(1);
	EXPECT_TRUE(fa.isStateFinal(1));
}

TEST(AutomatonTest, isInitialStateFinal) {
	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	EXPECT_FALSE(fa.isStateFinal(1));
}

TEST(AutomatonTest, isInitialAndFinalStateFinal) {
	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	fa.setStateFinal(1);
	EXPECT_TRUE(fa.isStateFinal(1));
}

//--------------------------------------------------------
//-------------------- addTransition ----------------------
//--------------------------------------------------------
TEST(AutomatonTest, addTransitionWithNoState) {
  	fa::Automaton fa;
	EXPECT_DEATH(fa.addTransition(1,'a',1),"");
}

TEST(AutomatonTest, addTransitionWithExistAndNoState) {
  	fa::Automaton fa;
  	fa.addState(1);
	EXPECT_DEATH(fa.addTransition(1,'a',2),"");
}

TEST(AutomatonTest, addTransitionWithNoAndExistState) {
  	fa::Automaton fa;
  	fa.addState(1);
	EXPECT_DEATH(fa.addTransition(2,'a',1),"");
}

TEST(AutomatonTest, addTransitionOnOneState) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.addTransition(1,'a',1);
  	EXPECT_EQ(fa.countStates(), 1u);
  	EXPECT_EQ(fa.countTransitions(), 1u);
}

TEST(AutomatonTest, addTransitionBetweenTwoState) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.addTransition(1,'a',2);
  	EXPECT_EQ(fa.countStates(), 2u);
  	EXPECT_EQ(fa.countTransitions(), 1u);
}

TEST(AutomatonTest, addTransitionWithOneStateAndNoPrintableAlpha) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.addTransition(1,'\a',1);
  	EXPECT_EQ(fa.countStates(), 1u);
  	EXPECT_EQ(fa.countTransitions(), 0u);
}

TEST(AutomatonTest, addTransitionWithTwoStateAndNoPrintableAlpha) {
 	fa::Automaton fa;
  	fa.addState(1);
  	fa.addState(2);
	fa.addTransition(1,'\a',2);
  	EXPECT_EQ(fa.countStates(), 2u);
  	EXPECT_EQ(fa.countTransitions(), 0u);
}

TEST(AutomatonTest, addTransitionOnOneFinalState) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.setStateFinal(1);
	fa.addTransition(1,'a',1);
  	EXPECT_EQ(fa.countStates(), 1u);
  	EXPECT_EQ(fa.countTransitions(), 1u);
}

TEST(AutomatonTest, addTransitionOnOneInitalState) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	fa.addTransition(1,'a',1);
  	EXPECT_EQ(fa.countStates(), 1u);
  	EXPECT_EQ(fa.countTransitions(), 1u);
}

TEST(AutomatonTest, addTransitionBetweenFinalAndLambdaState) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.setStateFinal(1);
	fa.addTransition(1,'a',2);
  	EXPECT_EQ(fa.countStates(), 2u);
  	EXPECT_EQ(fa.countTransitions(), 1u);
}

TEST(AutomatonTest, addTransitionBetweenLambdaAndFinalState) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.setStateFinal(1);
	fa.addTransition(2,'a',1);
  	EXPECT_EQ(fa.countStates(), 2u);
  	EXPECT_EQ(fa.countTransitions(), 1u);
}

TEST(AutomatonTest, addTransitionBetweenInitalAndLambdaState) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.setStateInitial(1);
	fa.addTransition(1,'a',2);
  	EXPECT_EQ(fa.countStates(), 2u);
  	EXPECT_EQ(fa.countTransitions(), 1u);
}

TEST(AutomatonTest, addTransitionBetweenLanbdaAndInitalState) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.setStateInitial(1);
	fa.addTransition(2,'a',1);
  	EXPECT_EQ(fa.countStates(), 2u);
  	EXPECT_EQ(fa.countTransitions(), 1u);
}

TEST(AutomatonTest, addTransitionBetweenTwoFinalState) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.setStateFinal(1);
	fa.setStateFinal(2);
	fa.addTransition(2,'a',1);
  	EXPECT_EQ(fa.countStates(), 2u);
  	EXPECT_EQ(fa.countTransitions(), 1u);
}

TEST(AutomatonTest, addTransitionBetweenTwoInitalState) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.setStateInitial(1);
	fa.setStateInitial(2);
	fa.addTransition(2,'a',1);
  	EXPECT_EQ(fa.countStates(), 2u);
  	EXPECT_EQ(fa.countTransitions(), 1u);
}

TEST(AutomatonTest, addTransitionBetweenFinalAndInitalState) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.setStateInitial(1);
	fa.setStateFinal(2);
	fa.addTransition(2,'a',1);
  	EXPECT_EQ(fa.countStates(), 2u);
  	EXPECT_EQ(fa.countTransitions(), 1u);
}

TEST(AutomatonTest, addTransitionBetweenInitialAndFinalState) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.setStateInitial(1);
	fa.setStateFinal(2);
	fa.addTransition(2,'a',1);
  	EXPECT_EQ(fa.countStates(), 2u);
  	EXPECT_EQ(fa.countTransitions(), 1u);
}

//--------------------------------------------------------
//-------------------- hasTransition ---------------------
//--------------------------------------------------------
TEST(AutomatonTest, hasTransitionWithNoState) {
  	fa::Automaton fa;
	EXPECT_DEATH(fa.hasTransition(1,'a',1),"");
}

TEST(AutomatonTest, hasTransitionBetweenExistantAndGhostState) {
  	fa::Automaton fa;
	fa.addState(1);
	EXPECT_DEATH(fa.hasTransition(1,'a',2),"");
}

TEST(AutomatonTest, hasTransitionBetweenGhostAndExistantState) {
  	fa::Automaton fa;
	fa.addState(1);
	EXPECT_DEATH(fa.hasTransition(2,'a',1),"");
}

TEST(AutomatonTest, hasTransitionFalse) {
  	fa::Automaton fa;
	fa.addState(1);
	EXPECT_FALSE(fa.hasTransition(1,'a',1));
  	EXPECT_EQ(fa.countStates(), 1u);
  	EXPECT_EQ(fa.countTransitions(), 0u);
}

TEST(AutomatonTest, hasTransitionWithOneState) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.addTransition(1,'a',1);
	EXPECT_TRUE(fa.hasTransition(1,'a',1));
  	EXPECT_EQ(fa.countStates(), 1u);
  	EXPECT_EQ(fa.countTransitions(), 1u);
}

TEST(AutomatonTest, hasTransitionWithTwoState) {
 	fa::Automaton fa;
  	fa.addState(1);
  	fa.addState(2);
	fa.addTransition(1,'a',2);
	EXPECT_TRUE(fa.hasTransition(1,'a',2));
  	EXPECT_EQ(fa.countStates(), 2u);
  	EXPECT_EQ(fa.countTransitions(), 1u);
}

TEST(AutomatonTest, hasTransitionWithOneStateAndNoPrintableAlpha) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.addTransition(1,'\a',1);
	EXPECT_FALSE(fa.hasTransition(1,'\a',1));
  	EXPECT_EQ(fa.countStates(), 1u);
  	EXPECT_EQ(fa.countTransitions(), 0u);
}

TEST(AutomatonTest, hasTransitionWithTwoStateAndNoPrintableAlpha) {
 	fa::Automaton fa;
  	fa.addState(1);
  	fa.addState(2);
	fa.addTransition(1,'\a',2);
	EXPECT_FALSE(fa.hasTransition(1,'\a',2));
  	EXPECT_EQ(fa.countStates(), 2u);
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

TEST(AutomatonTest, hasTransitionWithRemovedStateALL) {
 	fa::Automaton fa;
  	fa.addState(1);
  	fa.addState(2);
	fa.addTransition(1,'a',2);
	EXPECT_TRUE(fa.hasTransition(1,'a',2));
  	EXPECT_EQ(fa.countStates(), 2u);
  	EXPECT_EQ(fa.countTransitions(), 1u);
  	fa.removeState(1);
  	fa.removeState(2);
  	EXPECT_FALSE(fa.hasTransition(1,'a',2));
  	EXPECT_EQ(fa.countStates(), 0u);
  	EXPECT_EQ(fa.countTransitions(), 0u);
}


//--------------------------------------------------------
//------------------- removeTransition -------------------
//--------------------------------------------------------
TEST(AutomatonTest, removeTransitionWithNoState) {
  	fa::Automaton fa;
	EXPECT_DEATH(fa.removeTransition(1,'a',1),"");
}

TEST(AutomatonTest, removeTransitionOnOneState) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.addTransition(1,'a',1);
	fa.removeTransition(1,'a',1);
  	EXPECT_EQ(fa.countStates(), 1u);
  	EXPECT_EQ(fa.countTransitions(), 0u);
}

TEST(AutomatonTest, removeTransitionBetweenTwoState) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.addTransition(1,'a',2);
	fa.removeTransition(1,'a',2);
  	EXPECT_EQ(fa.countStates(), 2u);
  	EXPECT_EQ(fa.countTransitions(), 0u);
}

TEST(AutomatonTest, removeTransitionBetweenExistAndNotState) {
  	fa::Automaton fa;
	fa.addState(1);
	EXPECT_DEATH(fa.removeTransition(1,'a',2),"");
}

TEST(AutomatonTest, removeTransitionWithOneStateAndNoPrintableAlpha) {
  	fa::Automaton fa;
	fa.addState(1);
	EXPECT_DEATH(fa.removeTransition(1,'\a',1),"");
}

//--------------------------------------------------------
//------------------- countTransition --------------------
//--------------------------------------------------------
TEST(AutomatonTest, count0TransitionOneState) {
  	fa::Automaton fa;
	fa.addState(1);
  	EXPECT_EQ(fa.countTransitions(), 0u);
}

TEST(AutomatonTest, count1TransitionOneState) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.addTransition(1,'a',1);
  	EXPECT_EQ(fa.countTransitions(), 1u);
}

TEST(AutomatonTest, count1TransitionBetweenTwoState) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.addTransition(1,'a',2);
  	EXPECT_EQ(fa.countTransitions(), 1u);
}

TEST(AutomatonTest, countRemovedTransitionBetweenTwoState) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.addTransition(1,'a',2);
	fa.removeTransition(1,'a',2);
  	EXPECT_EQ(fa.countTransitions(), 0u);
}

TEST(AutomatonTest, countTransitionOneRemovedState) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.addTransition(1,'a',1);
	fa.removeState(1);
  	EXPECT_EQ(fa.countTransitions(), 0u);
}

TEST(AutomatonTest, count1TransitionBetweenTwoStateRemoveOneState) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.addTransition(1,'a',2);
	fa.removeState(1);
  	EXPECT_EQ(fa.countTransitions(), 0u);
}

TEST(AutomatonTest, count1TransitionBetweenTwoStateRemoveAllState) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.addTransition(1,'a',2);
	fa.removeState(1);
	fa.removeState(2);
  	EXPECT_EQ(fa.countTransitions(), 0u);
}

TEST(AutomatonTest, countManyTransition) {
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

//--------------------------------------------------------
//------------------- getAlphabetSize --------------------
//--------------------------------------------------------
TEST(AutomatonTest, alphabetSizeWithoutState) {
  	fa::Automaton fa;
  	EXPECT_EQ(fa.getAlphabetSize(), 0u);
}

TEST(AutomatonTest, alphabetSizeWithoutTransition) {
  	fa::Automaton fa;
	fa.addState(1);
  	EXPECT_EQ(fa.getAlphabetSize(), 0u);
}

TEST(AutomatonTest, alphabetSizeWithOneState) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.addTransition(1,'a',1);
  	EXPECT_EQ(fa.getAlphabetSize(), 1u);
}

TEST(AutomatonTest, alphabetSizeTransWithTwoState) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.addTransition(1,'a',2);
  	EXPECT_EQ(fa.getAlphabetSize(), 1u);
}

TEST(AutomatonTest, alphabetSizeTransWithTwoStateRemovedTransition) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.addTransition(1,'a',2);
	fa.removeTransition(1,'a',2);
  	EXPECT_EQ(fa.getAlphabetSize(), 1u);
}

TEST(AutomatonTest, alphabetSize2TransWithTwoStateSameAlpha) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.addTransition(1,'a',2);
	fa.addTransition(2,'a',1);
  	EXPECT_EQ(fa.getAlphabetSize(), 1u);
}

TEST(AutomatonTest, alphabetSize2TransWithTwoState1RemovedTransitionSameAlpha) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.addTransition(1,'a',2);
	fa.addTransition(2,'a',1);
	fa.removeTransition(1,'a',2);
  	EXPECT_EQ(fa.getAlphabetSize(), 1u);
}

TEST(AutomatonTest, alphabetSize2TransWithTwoStateRemoveAllTransitionSameAlpha) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.addTransition(1,'a',2);
	fa.addTransition(2,'a',1);
	fa.removeTransition(1,'a',2);
	fa.removeTransition(2,'a',1);
  	EXPECT_EQ(fa.getAlphabetSize(), 1u);
}

TEST(AutomatonTest, alphabetSize2TransWithTwoStateNotSameAlpha) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.addTransition(1,'a',2);
	fa.addTransition(2,'b',1);
  	EXPECT_EQ(fa.getAlphabetSize(), 2u);
}

TEST(AutomatonTest, alphabetSize2TransWithTwoState1RemovedTransitionNotSameAlpha) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.addTransition(1,'a',2);
	fa.addTransition(2,'b',1);
	fa.removeTransition(1,'a',2);
  	EXPECT_EQ(fa.getAlphabetSize(), 2u);
}

TEST(AutomatonTest, alphabetSize2TransWithTwoStateRemoveAllTransitionNotSameAlpha) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.addTransition(1,'a',2);
	fa.addTransition(2,'b',1);
	fa.removeTransition(1,'a',2);
	fa.removeTransition(2,'b',1);
  	EXPECT_EQ(fa.getAlphabetSize(), 2u);
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

//--------------------------------------------------------
//------------------- isDeterministic --------------------
//--------------------------------------------------------
TEST(AutomatonTest, NoDeterministicNoState) {
  	fa::Automaton fa;
  	EXPECT_FALSE(fa.isDeterministic());
}

TEST(AutomatonTest, NoDeterministicLambdaStateNoTransition) {
  	fa::Automaton fa;
  	fa.addState(1);
  	EXPECT_FALSE(fa.isDeterministic());
}

TEST(AutomatonTest, DeterministicInitialFinalState) {
  	fa::Automaton fa;
  	fa.addState(1);
  	fa.setStateInitial(1);
  	fa.setStateFinal(1);
  	EXPECT_TRUE(fa.isDeterministic());
}

TEST(AutomatonTest, NoDeterministicFinalStateNoTransition) {
  	fa::Automaton fa;
	fa.addState(2);
	fa.setStateFinal(2);
  	EXPECT_FALSE(fa.isDeterministic());
}

TEST(AutomatonTest, NoDeterministicInitialStateNoTransition) {
  	fa::Automaton fa;
	fa.addState(2);
	fa.setStateInitial(2);
  	EXPECT_FALSE(fa.isDeterministic());
}

TEST(AutomatonTest, NoDeterministicTwoInitialState) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.setStateInitial(1);
	fa.setStateInitial(2);
  	EXPECT_FALSE(fa.isDeterministic());
}


TEST(AutomatonTest, NoDeterministicWithEpsilonTransition) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.setStateInitial(1);
	fa.setStateFinal(2);
	fa.addTransition(1,'\a',1);
  	EXPECT_FALSE(fa.isDeterministic());
}

TEST(AutomatonTest, NoDeterministicNoInitState) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.setStateFinal(2);
	fa.addTransition(1,'a',1);
	fa.addTransition(1,'b',2);
	fa.addTransition(2,'a',2);
	fa.addTransition(2,'b',1);
  	EXPECT_FALSE(fa.isDeterministic());
}

TEST(AutomatonTest, DeterministicNoFinalStateNoTransition) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	fa.addState(2);
  	EXPECT_FALSE(fa.isDeterministic());
}

TEST(AutomatonTest, NoDeterministicNoFinalState) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	fa.addState(2);
	fa.addTransition(1,'a',1);
	fa.addTransition(1,'b',2);
	fa.addTransition(2,'a',2);
	fa.addTransition(2,'b',1);
  	EXPECT_FALSE(fa.isDeterministic());
}

TEST(AutomatonTest, NoDeterministicTwoTransitionFromOneStateSameAlpha) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	fa.addState(2);
	fa.setStateFinal(2);
	fa.addTransition(1,'b',1);
	fa.addTransition(1,'b',2);
  	EXPECT_FALSE(fa.isDeterministic());
}

TEST(AutomatonTest, DeterministicInitEqualFinal) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	fa.setStateFinal(1);
	fa.addState(2);
	fa.addTransition(1,'a',1);
	fa.addTransition(1,'b',2);
	fa.addTransition(2,'a',2);
	fa.addTransition(2,'b',1);
  	EXPECT_TRUE(fa.isDeterministic());
}

TEST(AutomatonTest, DeterministicTwoFinalState) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	fa.setStateFinal(1);
	fa.addState(2);
	fa.setStateFinal(2);
	fa.addTransition(1,'a',1);
	fa.addTransition(1,'b',2);
	fa.addTransition(2,'a',2);
	fa.addTransition(2,'b',1);
  	EXPECT_TRUE(fa.isDeterministic());
}


//--------------------------------------------------------
//------------------- isComplete --------------------
//--------------------------------------------------------
TEST(AutomatonTest, CompleteVoid) {
  	fa::Automaton fa;
  	EXPECT_TRUE(fa.isComplete());
}

TEST(AutomatonTest, Complete) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	fa.setStateFinal(1);
	fa.addState(2);
	fa.addTransition(1,'a',1);
	fa.addTransition(1,'b',2);
	fa.addTransition(2,'a',2);
	fa.addTransition(2,'b',1);
  	EXPECT_TRUE(fa.isComplete());
}

TEST(AutomatonTest, NotComplete) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	fa.addState(2);
	fa.setStateFinal(2);
	fa.addTransition(1,'a',1);
	fa.addTransition(1,'b',1);
	fa.addTransition(1,'b',2);
  	EXPECT_FALSE(fa.isComplete());
}

//--------------------------------------------------------
//-------------------- makeComplete ----------------------
//--------------------------------------------------------
TEST(AutomatonTest, makeCompleteVoid) {
  	fa::Automaton fa;
  	fa.makeComplete();
  	EXPECT_EQ(fa.countStates(), 0u);
  	EXPECT_EQ(fa.countTransitions(), 0u);
  	EXPECT_EQ(fa.getAlphabetSize(), 0u);
}

TEST(AutomatonTest, makeCompleteAlreadyComplete) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	fa.setStateFinal(1);
	fa.addState(2);
	fa.addTransition(1,'a',1);
	fa.addTransition(1,'b',2);
	fa.addTransition(2,'a',2);
	fa.addTransition(2,'b',1);
	EXPECT_TRUE(fa.isComplete());
	fa.makeComplete();
  	EXPECT_TRUE(fa.isComplete());
}

TEST(AutomatonTest, makeCompleteNotComplete) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	fa.addState(2);
	fa.setStateFinal(2);
	fa.addTransition(1,'a',1);
	fa.addTransition(1,'b',1);
	fa.addTransition(1,'b',2);
	EXPECT_FALSE(fa.isComplete());
	fa.makeComplete();
  	EXPECT_TRUE(fa.isComplete());
}

//--------------------------------------------------------
//-------------------- makeComplement --------------------
//--------------------------------------------------------
TEST(AutomatonTest, makeComplementVoid) {
  	fa::Automaton fa;
  	EXPECT_DEATH(fa.makeComplement(),"");
}

TEST(AutomatonTest, makeComplementWithNoDeterministic) {
  	fa::Automaton fa;
  	fa.addState(1);
  	EXPECT_DEATH(fa.makeComplement(),"");
}

TEST(AutomatonTest, makeComplementWithNoComplete) {
  	fa::Automaton fa;
  	fa.addState(1);
	fa.setStateInitial(1);
	fa.addState(2);
	fa.setStateFinal(2);
	fa.addTransition(1,'a',1);
	fa.addTransition(1,'b',1);
	EXPECT_TRUE(fa.isDeterministic());
  	EXPECT_DEATH(fa.makeComplement(),"");
}

TEST(AutomatonTest, makeComplementWithDeterministicAndComplete) {
  	fa::Automaton fa;
	fa.addState(0);
	fa.addState(1);
	fa.addState(2);
	fa.addState(3);
	
	fa.setStateInitial(0);
	fa.setStateFinal(2);
	
	fa.addTransition(0,'a',1);
	fa.addTransition(0,'b',3);
	fa.addTransition(1,'a',1);
	fa.addTransition(1,'b',2);
	fa.addTransition(2,'b',2);
	fa.addTransition(2,'a',3);
	fa.addTransition(3,'a',3);
	fa.addTransition(3,'b',3);
	
	fa.makeComplement();
	
	EXPECT_TRUE(fa.hasState(0));
	EXPECT_TRUE(fa.hasState(1));
	EXPECT_TRUE(fa.hasState(2));
	EXPECT_TRUE(fa.hasState(3));
	
	EXPECT_TRUE(fa.isStateInitial(0));
	EXPECT_TRUE(fa.isStateFinal(0));
	EXPECT_FALSE(fa.isStateInitial(1));
	EXPECT_TRUE(fa.isStateFinal(1));
	EXPECT_FALSE(fa.isStateInitial(2));
	EXPECT_FALSE(fa.isStateFinal(2));
	EXPECT_FALSE(fa.isStateInitial(3));
	EXPECT_TRUE(fa.isStateFinal(3));
	
	EXPECT_TRUE(fa.hasTransition(0,'a',1));
	EXPECT_TRUE(fa.hasTransition(0,'b',3));
	EXPECT_TRUE(fa.hasTransition(1,'a',1));
	EXPECT_TRUE(fa.hasTransition(1,'b',2));
	EXPECT_TRUE(fa.hasTransition(2,'b',2));
	EXPECT_TRUE(fa.hasTransition(2,'a',3));
	EXPECT_TRUE(fa.hasTransition(3,'a',3));
	EXPECT_TRUE(fa.hasTransition(3,'b',3));
}

//--------------------------------------------------------
//------------------- isLanguageEmpty --------------------
//--------------------------------------------------------
TEST(AutomatonTest, LanguageEmptyVoid) {
  	fa::Automaton fa;
  	EXPECT_TRUE(fa.isLanguageEmpty());
}

TEST(AutomatonTest, LanguageNotEmpty) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	fa.addState(2);
	fa.setStateFinal(2);
	fa.addTransition(1,'a',1);
	fa.addTransition(1,'b',2);
	fa.addTransition(2,'a',2);
	fa.addTransition(2,'b',1);
  	EXPECT_FALSE(fa.isLanguageEmpty());
}

TEST(AutomatonTest, LanguageNotEmptyInitEqualFinal) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	fa.setStateFinal(1);
	fa.addTransition(1,'a',1);
  	EXPECT_FALSE(fa.isLanguageEmpty());
}

TEST(AutomatonTest, LanguageEmptyInitEqualFinal) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	fa.setStateFinal(1);
  	EXPECT_TRUE(fa.isLanguageEmpty());
}

TEST(AutomatonTest, LanguageEmpty) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	fa.addState(2);
	fa.setStateFinal(2);
  	EXPECT_TRUE(fa.isLanguageEmpty());
}

TEST(AutomatonTest, LanguageEmptyNoInitState) {
  	fa::Automaton fa;
  	fa.addState(2);
	fa.setStateFinal(2);
  	EXPECT_TRUE(fa.isLanguageEmpty());
}

TEST(AutomatonTest, LanguageEmptyNoFinalState) {
  	fa::Automaton fa;
  	fa.addState(1);
	fa.setStateInitial(1);
  	EXPECT_TRUE(fa.isLanguageEmpty());
}

//--------------------------------------------------------
//--------------- removeNonAccessibleState ---------------
//--------------------------------------------------------
TEST(AutomatonTest, RemoveUnaccesibleStateWithNoState) {
  	fa::Automaton fa;
	fa.removeNonAccessibleStates();
	EXPECT_EQ(fa.countStates(), 0u);
  	EXPECT_EQ(fa.countTransitions(), 0u);
  	EXPECT_EQ(fa.getAlphabetSize(), 0u);
}

TEST(AutomatonTest, RemoveUnaccesibleStateLambdaState) {
  	fa::Automaton fa;
	fa.addState(1);
	
	fa.removeNonAccessibleStates();
  	EXPECT_FALSE(fa.hasState(1));
}

TEST(AutomatonTest, NoRemoveUnaccesibleStateWithOneInitialState) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	
	fa.removeNonAccessibleStates();
  	EXPECT_TRUE(fa.hasState(1));
}

TEST(AutomatonTest, NoRemoveUnaccesibleStateWithOneInitialStateWithTransition) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	fa.addTransition(1,'a',1);
	
	fa.removeNonAccessibleStates();
  	EXPECT_TRUE(fa.hasState(1));
}

TEST(AutomatonTest, RemoveUnaccesibleStateWithOneFinalState) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.setStateFinal(1);
	
	fa.removeNonAccessibleStates();
  	EXPECT_FALSE(fa.hasState(1));
}

TEST(AutomatonTest, RemoveUnaccesibleStateWithOneFinalalState) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.setStateFinal(1);
	fa.addTransition(1,'a',1);
	
	fa.removeNonAccessibleStates();
  	EXPECT_FALSE(fa.hasState(1));
}

TEST(AutomatonTest, RemoveUnaccesibleStateInitAndLambdaWithoutTransition) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	fa.addState(2);
	
	fa.removeNonAccessibleStates();
  	EXPECT_FALSE(fa.hasState(2));
  	EXPECT_TRUE(fa.hasState(1));
}

TEST(AutomatonTest, RemoveUnaccesibleStateInitAndFinalWithoutTransition) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	fa.addState(2);
	fa.setStateFinal(2);
	
	fa.removeNonAccessibleStates();
  	EXPECT_FALSE(fa.hasState(2));
  	EXPECT_TRUE(fa.hasState(1));
}

TEST(AutomatonTest, RemoveUnaccesibleStateInitAndFinalAndLambdaWithoutTransition) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	fa.addState(2);
	fa.setStateFinal(2);
	fa.addState(3);
	
	fa.removeNonAccessibleStates();
	EXPECT_FALSE(fa.hasState(3));
  	EXPECT_FALSE(fa.hasState(2));
  	EXPECT_TRUE(fa.hasState(1));
}

TEST(AutomatonTest, NoRemoveUnaccesibleStateInitTransitionFinalTransitionLambda) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	fa.addState(2);
	fa.addState(3);
	fa.setStateFinal(3);
	fa.addTransition(1,'a',3);
	fa.addTransition(3,'a',2);
	
	fa.removeNonAccessibleStates();
	EXPECT_TRUE(fa.hasState(3));
  	EXPECT_TRUE(fa.hasState(2));
  	EXPECT_TRUE(fa.hasState(1));
}

TEST(AutomatonTest, NoRemoveUnaccesibleStateInitTransitionLambdaTransitionFinal) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	fa.addState(2);
	fa.addState(3);
	fa.setStateFinal(3);
	fa.addTransition(1,'a',2);
	fa.addTransition(2,'a',3);
	
	fa.removeNonAccessibleStates();
	EXPECT_TRUE(fa.hasState(3));
  	EXPECT_TRUE(fa.hasState(2));
  	EXPECT_TRUE(fa.hasState(1));
}

TEST(AutomatonTest, RemoveUnaccesibleStateFinalTransitionLambdaTransitionInit) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	fa.addState(2);
	fa.addState(3);
	fa.setStateFinal(3);
	fa.addTransition(3,'a',2);
	fa.addTransition(2,'a',1);
	
	fa.removeNonAccessibleStates();
	EXPECT_FALSE(fa.hasState(3));
  	EXPECT_FALSE(fa.hasState(2));
  	EXPECT_TRUE(fa.hasState(1));
}

TEST(AutomatonTest, RemoveUnaccesibleStateLambdaTransitionFinalTransitionInit) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	fa.addState(2);
	fa.addState(3);
	fa.setStateFinal(3);
	fa.addTransition(2,'a',3);
	fa.addTransition(3,'a',1);
	
	fa.removeNonAccessibleStates();
	EXPECT_FALSE(fa.hasState(3));
  	EXPECT_FALSE(fa.hasState(2));
  	EXPECT_TRUE(fa.hasState(1));
}

TEST(AutomatonTest, NoRemoveUnaccesibleStateInitTransitionLambda) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	fa.addState(2);
	fa.addTransition(1,'a',2);
	
	fa.removeNonAccessibleStates();
  	EXPECT_TRUE(fa.hasState(2));
  	EXPECT_TRUE(fa.hasState(1));
}

TEST(AutomatonTest, RemoveUnaccesibleStateLambdaTransitionInit) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	fa.addState(2);
	fa.addTransition(2,'a',1);
	
	fa.removeNonAccessibleStates();
  	EXPECT_FALSE(fa.hasState(2));
  	EXPECT_TRUE(fa.hasState(1));
}

TEST(AutomatonTest, NoRemoveUnaccesibleStateWithTwoInitialStates) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	fa.addState(2);
	fa.setStateInitial(2);
	
	fa.removeNonAccessibleStates();
  	EXPECT_TRUE(fa.hasState(1));
  	EXPECT_TRUE(fa.hasState(2));
}

TEST(AutomatonTest, NoRemoveUnaccesibleState) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	fa.addState(2);
	fa.setStateFinal(2);
	fa.addTransition(1,'a',2);
	fa.removeNonAccessibleStates();
  	EXPECT_TRUE(fa.hasState(2));
  	EXPECT_TRUE(fa.hasState(1));
}

//--------------------------------------------------------
//-------------- removeNonCoAccessibleState ---------------
//--------------------------------------------------------
TEST(AutomatonTest, RemoveNonCoaccesibleStateWithNoState) {
  	fa::Automaton fa;
	fa.removeNonCoAccessibleStates();
	EXPECT_EQ(fa.countStates(), 0u);
  	EXPECT_EQ(fa.countTransitions(), 0u);
  	EXPECT_EQ(fa.getAlphabetSize(), 0u);
}

TEST(AutomatonTest, RemoveUnCoaccessibleStateWithLambdaState) {
  	fa::Automaton fa;
	fa.addState(1);
	
	fa.removeNonCoAccessibleStates();
  	EXPECT_FALSE(fa.hasState(1));
}

TEST(AutomatonTest, RemoveUnCoaccessibleStateWithInitState) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	
	fa.removeNonCoAccessibleStates();
  	EXPECT_FALSE(fa.hasState(1));
}

TEST(AutomatonTest, RemoveUnCoaccessibleStateWithInitStateWithTransitionOnIt) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	fa.addTransition(1,'a',1);
	
	fa.removeNonCoAccessibleStates();
  	EXPECT_FALSE(fa.hasState(1));
}

TEST(AutomatonTest, NoRemoveUnCoaccessibleStateWithFinalState) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.setStateFinal(1);
	
	fa.removeNonCoAccessibleStates();
  	EXPECT_TRUE(fa.hasState(1));
}

TEST(AutomatonTest, NoRemoveUnCoaccessibleStateWithFinalStateWithTransitionOnIt) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.setStateFinal(1);
	fa.addTransition(1,'a',1);
	
	fa.removeNonCoAccessibleStates();
  	EXPECT_TRUE(fa.hasState(1));
}

TEST(AutomatonTest, RemoveUnCoaccessibleState) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	fa.addState(2);
	fa.setStateFinal(2);
	fa.removeNonCoAccessibleStates();
  	EXPECT_TRUE(fa.hasState(2));
  	EXPECT_FALSE(fa.hasState(1));
}

TEST(AutomatonTest, RemoveUnCoaccessibleStateFinalLambdaInitState) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	fa.addState(2);
	fa.setStateFinal(2);
	fa.addState(3);
	fa.removeNonCoAccessibleStates();
  	EXPECT_TRUE(fa.hasState(2));
  	EXPECT_FALSE(fa.hasState(1));
  	EXPECT_FALSE(fa.hasState(3));
}

TEST(AutomatonTest, RemoveUnCoaccessibleStateFinalTransitionLambdaTransitionInitState) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	fa.addState(3);
	fa.setStateFinal(3);
	fa.addState(2);
	fa.addTransition(3,'a',2);
	fa.addTransition(2,'a',1);
	
	fa.removeNonCoAccessibleStates();
  	EXPECT_TRUE(fa.hasState(3));
  	EXPECT_FALSE(fa.hasState(1));
  	EXPECT_FALSE(fa.hasState(2));
}

TEST(AutomatonTest, RemoveUnCoaccessibleStateFinalTransitionInitTransitionLambdaState) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	fa.addState(3);
	fa.setStateFinal(3);
	fa.addState(2);
	fa.addTransition(3,'a',1);
	fa.addTransition(1,'a',2);
	
	fa.removeNonCoAccessibleStates();
  	EXPECT_TRUE(fa.hasState(3));
  	EXPECT_FALSE(fa.hasState(1));
  	EXPECT_FALSE(fa.hasState(2));
}

TEST(AutomatonTest, NoRemoveUnCoaccessibleStateInitialTransitionLambdaTransitionFinalState) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	fa.addState(3);
	fa.setStateFinal(3);
	fa.addState(2);
	fa.addTransition(1,'a',2);
	fa.addTransition(2,'a',3);
	
	fa.removeNonCoAccessibleStates();
  	EXPECT_TRUE(fa.hasState(3));
  	EXPECT_TRUE(fa.hasState(1));
  	EXPECT_TRUE(fa.hasState(2));
}

TEST(AutomatonTest, NoRemoveUnCoaccessibleStateLambdaTransitionInitialTransitionFinalState) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	fa.addState(3);
	fa.setStateFinal(3);
	fa.addState(2);
	fa.addTransition(2,'a',1);
	fa.addTransition(1,'a',3);
	
	fa.removeNonCoAccessibleStates();
  	EXPECT_TRUE(fa.hasState(3));
  	EXPECT_TRUE(fa.hasState(1));
  	EXPECT_TRUE(fa.hasState(2));
}

TEST(AutomatonTest, RemoveUnCoaccessibleStateLambdaTransitionFinalTransitionInitialState) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	fa.addState(3);
	fa.setStateFinal(3);
	fa.addState(2);
	fa.addTransition(2,'a',3);
	fa.addTransition(3,'a',1);
	
	fa.removeNonCoAccessibleStates();
  	EXPECT_TRUE(fa.hasState(3));
  	EXPECT_FALSE(fa.hasState(1));
  	EXPECT_TRUE(fa.hasState(2));
}

TEST(AutomatonTest, RemoveUnCoaccessibleStateInitialTransitionFinalTransitionLambdaState) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	fa.addState(3);
	fa.setStateFinal(3);
	fa.addState(2);
	fa.addTransition(1,'a',3);
	fa.addTransition(3,'a',2);
	
	fa.removeNonCoAccessibleStates();
  	EXPECT_TRUE(fa.hasState(3));
  	EXPECT_FALSE(fa.hasState(2));
  	EXPECT_TRUE(fa.hasState(1));
}

TEST(AutomatonTest, NoRemoveUnCoaccessibleStateWithTwoFinalStates) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.setStateFinal(1);
	fa.addState(2);
	fa.setStateFinal(2);
	
	fa.removeNonCoAccessibleStates();
  	EXPECT_TRUE(fa.hasState(1));
  	EXPECT_TRUE(fa.hasState(2));
}

TEST(AutomatonTest, NoRemoveUnCoaccesibleState) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.setStateFinal(2);
	fa.addTransition(1,'a',2);
	fa.removeNonCoAccessibleStates();
  	EXPECT_TRUE(fa.hasState(2));
  	EXPECT_TRUE(fa.hasState(1));
}

TEST(AutomatonTest, NoRemoveUnCoaccesibleStateFi) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.setStateFinal(2);
	fa.addTransition(1,'a',2);
	fa.removeNonCoAccessibleStates();
  	EXPECT_TRUE(fa.hasState(2));
  	EXPECT_TRUE(fa.hasState(1));
}

//--------------------------------------------------------
//-------------------- createProduct ---------------------
//--------------------------------------------------------
TEST(AutomatonTest, createProductWithNoState) {
  	fa::Automaton fa;
  	fa::Automaton fb;
	fa::Automaton fp;
	fp = fp.createProduct(fa,fb); // automate produit
	EXPECT_EQ(fp.countStates(), 0u);
  	EXPECT_EQ(fp.countTransitions(), 0u);
  	EXPECT_EQ(fp.getAlphabetSize(), 0u);
}

TEST(AutomatonTest, CreateProduct) {
  	fa::Automaton fa; // automate a
	fa.addState(1);
	fa.addState(2);
	
	fa.setStateInitial(1);
	fa.setStateFinal(2);
	
	fa.addTransition(1,'a',2);
	fa.addTransition(2,'b',2);
	
	fa::Automaton fb; // automate b
	fb.addState(1);
	fb.addState(2);
	
	fb.setStateInitial(1);
	fb.setStateFinal(2);
	
	fb.addTransition(1,'a',2);
	
	fa::Automaton fp;
	fp = fp.createProduct(fa,fb); // automate produit
	EXPECT_TRUE(fp.hasState(1));
  	EXPECT_TRUE(fp.hasState(0));
  	EXPECT_TRUE(fp.hasTransition(0,'a',1));
	
}

//--------------------------------------------------------
//--------------- hasEmptyIntersectioWith ----------------
//--------------------------------------------------------
TEST(AutomatonTest, emptyIntersectionVoid) {
  	fa::Automaton fa; // automate a
	
	EXPECT_FALSE(fa.hasEmptyIntersectionWith(fa));
}

TEST(AutomatonTest, emptyIntersectionWithOther) {
  	fa::Automaton fa; // automate a
	fa.addState(1);
	fa.addState(2);
	
	fa.setStateInitial(1);
	fa.setStateFinal(2);
	
	fa.addTransition(1,'b',2);
	
	fa::Automaton fb; // automate b
	fb.addState(1);
	fb.addState(2);
	
	fb.setStateInitial(1);
	fb.setStateFinal(2);
	
	fb.addTransition(1,'a',2);
	
	EXPECT_TRUE(fa.hasEmptyIntersectionWith(fb));
}

TEST(AutomatonTest, emptyIntersectionWithItSelf) {
  	fa::Automaton fa; // automate a
	fa.addState(1);
	fa.addState(2);
	
	fa.setStateInitial(1);
	fa.setStateFinal(2);
	
	fa.addTransition(1,'b',2);
	
	EXPECT_FALSE(fa.hasEmptyIntersectionWith(fa));
}

TEST(AutomatonTest, emptyIntersectionWithSame) {
  	fa::Automaton fa; // automate a
	fa.addState(1);
	fa.addState(2);
	
	fa.setStateInitial(1);
	fa.setStateFinal(2);
	
	fa.addTransition(1,'a',2);
	
	fa::Automaton fb; // automate b
	fb.addState(1);
	fb.addState(2);
	
	fb.setStateInitial(1);
	fb.setStateFinal(2);
	
	fb.addTransition(1,'a',2);
	
	EXPECT_FALSE(fa.hasEmptyIntersectionWith(fb));
}

//--------------------------------------------------------
//--------------------- readString -----------------------
//--------------------------------------------------------
TEST(AutomatonTest, readStringVoid) {
  	fa::Automaton fa;
	std::set<int> s;

	s=fa.readString("a");
	EXPECT_EQ(s.size(),0u);
}

TEST(AutomatonTest, readStringSimple) {
  	fa::Automaton fa; // automate a
	fa.addState(1);
	fa.addState(2);
	
	fa.setStateInitial(1);
	fa.setStateFinal(2);
	
	
	fa.addTransition(1,'a',2);

    std::set<int> s;

	s=fa.readString("a");
	
	EXPECT_TRUE(*s.find(1)==1);
	EXPECT_TRUE(*s.find(2)==2);
	EXPECT_TRUE(s.size()==2);
	
}

//--------------------------------------------------------
//------------------------ match -------------------------
//--------------------------------------------------------
TEST(AutomatonTest, matchLangageEmptyWordEmpty){
    fa::Automaton fa; 
	
	EXPECT_TRUE(fa.match(""));
}

TEST(AutomatonTest, matchLangageEmptyWordNotEmpty){
    fa::Automaton fa; 
	
	EXPECT_FALSE(fa.match("a"));
}

TEST(AutomatonTest, matchLangageNotEmptyWordEmpty){
    fa::Automaton fa; // automate a
	fa.addState(1);
	fa.addState(2);
	
	fa.setStateInitial(1);
	fa.setStateFinal(2);
	
	fa.addTransition(1,'a',2);
	
	EXPECT_TRUE(fa.match(""));
}

TEST(AutomatonTest, matchLangageNotEmptyWordNotEmpty){
    fa::Automaton fa; // automate a
	fa.addState(1);
	fa.addState(2);
	
	fa.setStateInitial(1);
	fa.setStateFinal(2);
	
	fa.addTransition(1,'a',2);
	
	EXPECT_TRUE(fa.match("a"));
}

TEST(AutomatonTest, noMatchLangageNotEmptyWordNotEmpty){
    fa::Automaton fa; // automate a
	fa.addState(1);
	fa.addState(2);
	
	fa.setStateInitial(1);
	fa.setStateFinal(2);
	
	fa.addTransition(1,'a',2);
	
	EXPECT_FALSE(fa.match("b"));
}

//--------------------------------------------------------
//------------------ createDeterministic -----------------
//--------------------------------------------------------
TEST(AutomatonTest, createDeterministicWithNoState) {
  	fa::Automaton fa;
  	fa::Automaton fd;
	fd = fd.createDeterministic(fa); // automate determiniser
	EXPECT_EQ(fd.countStates(), 0u);
  	EXPECT_EQ(fd.countTransitions(), 0u);
  	EXPECT_EQ(fd.getAlphabetSize(), 0u);
  	EXPECT_FALSE(fd.isDeterministic());
}

TEST(AutomatonTest, createAlreadyDeterministic){
    fa::Automaton fa; // automate a determiniser
	fa.addState(1);
	fa.addState(2);
	
	fa.setStateInitial(1);
	fa.setStateFinal(2);
	fa.addTransition(1,'a',2);
	
	
	fa::Automaton fd; // automate determinisé
	fd = fd.createDeterministic(fa);
	EXPECT_TRUE(fd.hasState(1));
	EXPECT_TRUE(fd.hasState(2));
	EXPECT_TRUE(fd.isStateInitial(1));
	EXPECT_TRUE(fd.isStateFinal(2));
	EXPECT_TRUE(fd.hasTransition(1,'a',2));
	EXPECT_FALSE(fd.isLanguageEmpty());
	EXPECT_TRUE(fd.isDeterministic());
}

TEST(AutomatonTest, createDeterministic){
    fa::Automaton fa; // automate a determiniser
	fa.addState(1);
	fa.addState(2);
	
	fa.setStateInitial(1);
	fa.setStateFinal(2);
	
	
	fa::Automaton fd; // automate determinisé
	fd=fd.createDeterministic(fa);
	EXPECT_TRUE(fd.isLanguageEmpty());
	EXPECT_TRUE(fd.isDeterministic());
}

TEST(AutomatonTest, createDeterministic2){
    fa::Automaton fa; // automate a determiniser
	fa.addState(1);
	fa.addState(2);
	
	fa.setStateInitial(1);
	fa.setStateFinal(2);
	fa.addTransition(1,'a',1);
	
	
	fa::Automaton fd; // automate determinisé
	fd=fd.createDeterministic(fa);
	EXPECT_TRUE(fd.isLanguageEmpty());
	EXPECT_TRUE(fd.isDeterministic());
}

TEST(AutomatonTest, createDeterministic3){
    fa::Automaton fa; // automate a determiniser
	fa.addState(1);
	fa.addState(2);
	fa.addState(3);
	fa.addState(4);
	
	fa.setStateInitial(1);
	fa.setStateFinal(2);
	fa.addTransition(1,'a',2);
	fa.addTransition(1,'a',3);
	fa.addTransition(4,'a',3);
	fa.addTransition(4,'a',1);
	
	
	fa::Automaton fd; // automate determinisé
	fd=fd.createDeterministic(fa);
	EXPECT_FALSE(fd.isLanguageEmpty());
	EXPECT_TRUE(fd.isDeterministic());
}


//--------------------------------------------------------
//-------------------- isIncludedIn ----------------------
//--------------------------------------------------------
TEST(AutomatonTest, isIncludedInVoid) {
  	fa::Automaton fa;
  	fa::Automaton fb;
  	EXPECT_DEATH(fa.isIncludedIn(fb),"");
}

TEST(AutomatonTest, EmptyIsIncludedInNotEmpty){
    fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	fa.setStateFinal(1);
	fa.addTransition(1,'a',1);
  	
  	fa::Automaton fb;
  	EXPECT_TRUE(fb.isIncludedIn(fa));
}

TEST(AutomatonTest, NotEmptyIsIncludedInEmpty) {
  	fa::Automaton fa;
  	fa.addState(1);
  	fa.addState(2);
	
	fa.setStateInitial(1);
	fa.setStateFinal(2);
	
	fa.addTransition(1,'a',2);
  	
  	fa::Automaton fb;
  	EXPECT_DEATH(fa.isIncludedIn(fb),"");
}

TEST(AutomatonTest, LangAIsIncludedInLangAB){
    fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	fa.setStateFinal(1);
	fa.addTransition(1,'a',1);
	fa.addTransition(1,'b',1);
	
	fa::Automaton fb;
	fb.addState(1);
	fb.setStateInitial(1);
	fb.setStateFinal(1);
	fb.addTransition(1,'a',1);
  	
  	EXPECT_TRUE(fb.isIncludedIn(fa));
}


TEST(AutomatonTest, LangABIsIncludedInLangA){
    fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	fa.setStateFinal(1);
	fa.addTransition(1,'a',1);
	fa.addTransition(1,'b',1);
	
	fa::Automaton fb;
	fb.addState(1);
	fb.setStateInitial(1);
	fb.setStateFinal(1);
	fb.addTransition(1,'a',1);
  	
  	EXPECT_FALSE(fa.isIncludedIn(fb));
}

//--------------------------------------------------------
//------------------- createMinimalMoore ------------------
//--------------------------------------------------------
TEST(AutomatonTest, MooreVoid) {
  	fa::Automaton fa;
  	fa::Automaton fm;
  	EXPECT_DEATH(fm.createMinimalMoore(fa),"");
}
/*
TEST(AutomatonTest, MooreOneInitialState) {
  	fa::Automaton fa;
     fa.addState(0);
	fa.setStateInitial(0);
	fa.addState(1);
	fa.addState(2);
	fa.setStateFinal(2);
	fa.addState(3);
	fa.setStateFinal(3);
	fa.addState(4);
	fa.addState(5);
	
	fa.addTransition(0,'a',1);
	fa.addTransition(0,'b',2);
	fa.addTransition(1,'a',3);
	fa.addTransition(1,'b',1);
	fa.addTransition(2,'a',4);
	fa.addTransition(2,'b',2);
	fa.addTransition(3,'a',1);
	fa.addTransition(3,'b',3);
	fa.addTransition(4,'a',2);
	fa.addTransition(4,'b',4);
	fa.addTransition(5,'a',3);
	fa.addTransition(5,'b',4);
	
	fa::Automaton fm;
	fm = fm.createMinimalMoore(fa);
	
	EXPECT_TRUE(fm.hasState(0));
	EXPECT_TRUE(fm.isStateInitial(0));
	EXPECT_TRUE(fm.hasState(1));
	EXPECT_TRUE(fm.hasState(2));
	EXPECT_TRUE(fm.isStateFinal(2));
	EXPECT_TRUE(fm.hasTransition(0,'a',1));
	EXPECT_TRUE(fm.hasTransition(0,'b',2));
	EXPECT_TRUE(fm.hasTransition(1,'a',2));
	EXPECT_TRUE(fm.hasTransition(1,'b',1));
	EXPECT_TRUE(fm.hasTransition(2,'a',1));
	EXPECT_TRUE(fm.hasTransition(2,'b',2));
}
*/
//--------------------------------------------------------
//--------------- createMinimalBrzozowski ----------------
//--------------------------------------------------------
/*TEST(AutomatonTest, BrzozowskiVoid) {
  	fa::Automaton fa;
  	fa::Automaton fm;
  	EXPECT_DEATH(fm.createMinimalBrzozowski(fa),"");
}

TEST(AutomatonTest, BrzozowskiOneInitialState) {
  	fa::Automaton fa;
    fa.addState(0);
	fa.setStateInitial(0);
	fa.addState(1);
	fa.addState(2);
	fa.setStateFinal(2);
	fa.addState(3);
	fa.setStateFinal(3);
	fa.addState(4);
	fa.addState(5);
	
	fa.addTransition(0,'a',1);
	fa.addTransition(0,'b',2);
	fa.addTransition(1,'a',3);
	fa.addTransition(1,'b',1);
	fa.addTransition(2,'a',4);
	fa.addTransition(2,'b',2);
	fa.addTransition(3,'a',1);
	fa.addTransition(3,'b',3);
	fa.addTransition(4,'a',2);
	fa.addTransition(4,'b',4);
	fa.addTransition(5,'a',3);
	fa.addTransition(5,'b',4);
	
	fa::Automaton fm;
	fm = fm.createMinimalBrzozowski(fa);
	
	EXPECT_TRUE(fm.hasState(0));
	EXPECT_TRUE(fm.isStateInitial(0));
	EXPECT_TRUE(fm.hasState(1));
	EXPECT_TRUE(fm.hasState(2));
	EXPECT_TRUE(fm.isStateFinal(2));
	EXPECT_TRUE(fm.hasTransition(0,'a',1));
	EXPECT_TRUE(fm.hasTransition(0,'b',2));
	EXPECT_TRUE(fm.hasTransition(1,'a',2));
	EXPECT_TRUE(fm.hasTransition(1,'b',1));
	EXPECT_TRUE(fm.hasTransition(2,'a',1));
	EXPECT_TRUE(fm.hasTransition(2,'b',2));
}*/
//--------------------------------------------------------
//----------------- createMinimalHopcroft ----------------
//--------------------------------------------------------
/*TEST(AutomatonTest, HopcroftVoid) {
  	fa::Automaton fa;
  	fa::Automaton fm;
  	EXPECT_DEATH(fm.createMinimalHopcroft(fa),"");
}

TEST(AutomatonTest, HopcroftOneInitialState) {
    fa::Automaton fa;
  	fa.addState(0);
	fa.setStateInitial(0);
	fa.addState(1);
	fa.addState(2);
	fa.setStateFinal(2);
	fa.addState(3);
	fa.setStateFinal(3);
	fa.addState(4);
	fa.addState(5);
	
	fa.addTransition(0,'a',1);
	fa.addTransition(0,'b',2);
	fa.addTransition(1,'a',3);
	fa.addTransition(1,'b',1);
	fa.addTransition(2,'a',4);
	fa.addTransition(2,'b',2);
	fa.addTransition(3,'a',1);
	fa.addTransition(3,'b',3);
	fa.addTransition(4,'a',2);
	fa.addTransition(4,'b',4);
	fa.addTransition(5,'a',3);
	fa.addTransition(5,'b',4);
	
	fa::Automaton fm;
	fm = fm.createMinimalHopcroft(fa);
	
	EXPECT_TRUE(fm.hasState(0));
	EXPECT_TRUE(fm.isStateInitial(0));
	EXPECT_TRUE(fm.hasState(1));
	EXPECT_TRUE(fm.hasState(2));
	EXPECT_TRUE(fm.isStateFinal(2));
	EXPECT_TRUE(fm.hasTransition(0,'a',1));
	EXPECT_TRUE(fm.hasTransition(0,'b',2));
	EXPECT_TRUE(fm.hasTransition(1,'a',2));
	EXPECT_TRUE(fm.hasTransition(1,'b',1));
	EXPECT_TRUE(fm.hasTransition(2,'a',1));
	EXPECT_TRUE(fm.hasTransition(2,'b',2));
}
*/
//--------------------------------------------------------
//------------------ createWithoutEpsilon ----------------
//--------------------------------------------------------
TEST(AutomatonTest, createWithoutEpsilonVoid) {
  	fa::Automaton fa;
  	fa::Automaton fwe;
  	fwe = fwe.createWithoutEpsilon(fa);
  	EXPECT_EQ(fwe.countStates(), 0u);
  	EXPECT_EQ(fwe.countTransitions(), 0u);
  	EXPECT_EQ(fwe.getAlphabetSize(), 0u);
}
/*
TEST(AutomatonTest, createWithoutEpsilon) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.addState(3);
	fa.setStateInitial(1);
	fa.setStateFinal(2);
	fa.addTransition(1,'a',1);
	fa.addTransition(1,(char)0,2);
	fa.addTransition(2,'b',2);
	fa.addTransition(2,(char)0,3);
	fa.addTransition(3,'c',3);
  	
  	fa::Automaton fwe;
  	fwe = fwe.createWithoutEpsilon(fa);
  	
  	EXPECT_TRUE(fwe.hasState(0));
	EXPECT_TRUE(fwe.isStateInitial(0));
	EXPECT_TRUE(fwe.isStateFinal(0));
	EXPECT_TRUE(fwe.hasState(1));
	EXPECT_TRUE(fwe.isStateFinal(1));
	EXPECT_TRUE(fwe.hasState(2));
	EXPECT_TRUE(fwe.isStateFinal(2));
	
	EXPECT_TRUE(fwe.hasTransition(0,'a',1));
	EXPECT_TRUE(fwe.hasTransition(0,'b',1));
	EXPECT_TRUE(fwe.hasTransition(0,'c',2));
	EXPECT_TRUE(fwe.hasTransition(1,'b',1));
	EXPECT_TRUE(fwe.hasTransition(1,'c',2));
	EXPECT_TRUE(fwe.hasTransition(2,'c',2));
}
*/
int main(int argc, char **argv) {
::testing::InitGoogleTest(&argc, argv);
::testing::FLAGS_gtest_death_test_style="threadsafe";
  	return RUN_ALL_TESTS();
}
