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
TEST(AutomatonTest, NoDeterministicNoInitStateNoTransition) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.setStateFinal(2);
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

TEST(AutomatonTest, NoDeterministicNoFinalStateNoTransition) {
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

TEST(AutomatonTest, DeterministicInitNotEqualFinal) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	fa.addState(2);
	fa.setStateFinal(2);
	fa.addTransition(1,'a',1);
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


// test isComplete
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

// test makeComplete
TEST(AutomatonTest, CompleteInitEqualFinal) {
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

TEST(AutomatonTest, CompleteInitNotEqualFinal) {
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

// test makeComplement
TEST(AutomatonTest, makeComplement) {
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

// test islanguageEmpty
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

TEST(AutomatonTest, LanguageEmptyNoState) {
  	fa::Automaton fa;
  	EXPECT_TRUE(fa.isLanguageEmpty());
}

// test removeNonAccessibleStates
TEST(AutomatonTest, RemoveUnaccesibleState) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.setStateInitial(1);
	fa.addState(2);
	fa.setStateFinal(2);
	
	fa.removeNonAccessibleStates();
  	EXPECT_FALSE(fa.hasState(2));
  	EXPECT_TRUE(fa.hasState(1));
}

TEST(AutomatonTest, RemoveUnaccesibleStateWithNoInitOrFinalState) {
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

// test removeNonCoAccessibleStates

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

TEST(AutomatonTest, RemoveUnCoaccessibleStateWithNoInitOrFinalState) {
  	fa::Automaton fa;
	fa.addState(1);
	
	fa.removeNonCoAccessibleStates();
  	EXPECT_FALSE(fa.hasState(1));
}

TEST(AutomatonTest, NoRemoveUnCoaccessibleStateWithOneFinalState) {
  	fa::Automaton fa;
	fa.addState(1);
	fa.setStateFinal(1);
	
	fa.removeNonCoAccessibleStates();
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

// test CreateProduct
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

// test emptyIntersection
TEST(AutomatonTest, emptyIntersectionTrue) {
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

// test emptyIntersection
TEST(AutomatonTest, emptyIntersectionFalse) {
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

//test readString
TEST(AutomatonTest, readStringSimple) {
  	fa::Automaton fa; // automate a
	fa.addState(1);
	fa.addState(2);
	
	fa.setStateInitial(1);
	fa.setStateFinal(2);
	
	
	fa.addTransition(1,'a',2);

    std::set<int> s;

	s=fa.readString("a");
	
	//while()
	
	EXPECT_TRUE(s.size()==2);
	
}

//test match
TEST(AutomatonTest, matchTrue){
    fa::Automaton fa; // automate a
	fa.addState(1);
	fa.addState(2);
	
	fa.setStateInitial(1);
	fa.setStateFinal(2);
	
	fa.addTransition(1,'a',2);
	
	EXPECT_TRUE(fa.match("a"));
}

TEST(AutomatonTest, matchFalse){
    fa::Automaton fa; // automate a
	fa.addState(1);
	fa.addState(2);
	
	fa.setStateInitial(1);
	fa.setStateFinal(2);
	
	fa.addTransition(1,'a',2);
	
	EXPECT_FALSE(fa.match("b"));
}

// test createDeterministic
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

// test createDeterministic
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

// test createDeterministic
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

// test createDeterministic
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


// test isIncludedIn

//test createMinimalMoore

// test createMinimalBrzozowski

//test createMinimalHopcroft

// test createWithoutEpsilon


int main(int argc, char **argv) {
::testing::InitGoogleTest(&argc, argv);
  	return RUN_ALL_TESTS();
}
