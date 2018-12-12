#include <iostream>
#include <iomanip>
#include <fstream>
#include "gtest/gtest.h"
#include "Automaton.h"

//TODO: faire un test de démonstration

#define DOT_PRINT(automaton, fileName, nameOfStream)\
    std::ofstream nameOfStream;\
    nameOfStream.open("../dot/" + fileName +".dot");\
    if (!nameOfStream) {\
    std::cout << "error";\
    exit(EXIT_FAILURE);\
    }\
    automaton.dotPrint(nameOfStream);\
    nameOfStream.close();

class AutomatonTestFixture : public ::testing::Test {
protected:
    void SetUp() override {
        intitAutomatonNotCompleteNotDeterministic();
        intitAutomatonNotCompleteDeterministic();
        intitAutomatonCompleteNotDeterministic();
        intitAutomatonCompleteDeterministic();
        initAutomaton();
        initAutomatonInutile();
        initAutomatonCoAccessible();
        initAutomatonEmptyInutileIsInitial();
        initAutomatonEmpty();
        initAutomatonEmptyNoFinal();
        initAutomatonEmptyNoInitial();
    }

    void intitAutomatonNotCompleteNotDeterministic() {
        automatonNotCompleteNotDeterministic.addState(0);
        automatonNotCompleteNotDeterministic.setStateInitial(0);
        automatonNotCompleteNotDeterministic.addState(1);
        automatonNotCompleteNotDeterministic.setStateFinal(1);
        automatonNotCompleteNotDeterministic.setStateInitial(1);
        automatonNotCompleteNotDeterministic.addState(3);
        automatonNotCompleteNotDeterministic.addState(2);
        automatonNotCompleteNotDeterministic.addState(4);
        automatonNotCompleteNotDeterministic.setStateFinal(4);
        automatonNotCompleteNotDeterministic.addTransition(0, 'a', 1);
        automatonNotCompleteNotDeterministic.addTransition(0, 'a', 2);
        automatonNotCompleteNotDeterministic.addTransition(0, 'a', 3);
        automatonNotCompleteNotDeterministic.addTransition(1, 'b', 3);
        automatonNotCompleteNotDeterministic.addTransition(2, 'a', 3);
        automatonNotCompleteNotDeterministic.addTransition(2, 'b', 4);
        automatonNotCompleteNotDeterministic.addTransition(3, 'a', 3);
        automatonNotCompleteNotDeterministic.addTransition(3, 'b', 4);
        automatonNotCompleteNotDeterministic.addTransition(4, 'a', 4);
    }

    void intitAutomatonNotCompleteDeterministic() {
        automatonNotCompleteDeterministic.addState(0);
        automatonNotCompleteDeterministic.setStateInitial(0);
        automatonNotCompleteDeterministic.addState(1);
        automatonNotCompleteDeterministic.addState(2);
        automatonNotCompleteDeterministic.setStateFinal(2);
        automatonNotCompleteDeterministic.addTransition(0, 'a', 1);
        automatonNotCompleteDeterministic.addTransition(1, 'b', 2);
        automatonNotCompleteDeterministic.addTransition(2, 'a', 2);
        automatonNotCompleteDeterministic.addTransition(2, 'b', 2);
    }

    void intitAutomatonCompleteNotDeterministic() {
        automatonCompleteNotDeterministic.addState(0);
        automatonCompleteNotDeterministic.setStateInitial(0);
        automatonCompleteNotDeterministic.addState(1);
        automatonCompleteNotDeterministic.setStateFinal(1);
        automatonCompleteNotDeterministic.addTransition(0, 'a', 1);
        automatonCompleteNotDeterministic.addTransition(0, 'b', 1);
        automatonCompleteNotDeterministic.addTransition(1, 'a', 0);
        automatonCompleteNotDeterministic.addTransition(1, 'a', 1);
        automatonCompleteNotDeterministic.addTransition(1, 'b', 1);
    }

    void intitAutomatonCompleteDeterministic() {
        automatonCompleteDeterministic.addState(0);
        automatonCompleteDeterministic.setStateInitial(0);
        automatonCompleteDeterministic.addState(1);
        automatonCompleteDeterministic.setStateFinal(1);
        automatonCompleteDeterministic.addTransition(0, 'a', 1);
        automatonCompleteDeterministic.addTransition(0, 'b', 1);
        automatonCompleteDeterministic.addTransition(1, 'a', 0);
        automatonCompleteDeterministic.addTransition(1, 'b', 1);
    }

    void initAutomaton() {
        automaton.addState(0);
        automaton.addState(1);
        automaton.addState(2);
        automaton.addState(3);
        automaton.addState(4);
        automaton.addState(5);
        automaton.addState(6);
        automaton.addState(7);
        automaton.addState(8);
        automaton.setStateInitial(0);
        automaton.setStateInitial(2);
        automaton.setStateInitial(8);
        automaton.setStateFinal(2);
        automaton.setStateFinal(3);
        automaton.setStateFinal(7);
        automaton.addTransition(0, 'o', 1);
        automaton.addTransition(0, 'a', 0);
        automaton.addTransition(0, 'z', 1);
        automaton.addTransition(0, 'u', 8);
        automaton.addTransition(0, (char) 122, 8);
        automaton.addTransition(1, 'a', 4);
        automaton.addTransition(1, 'a', 5);
        automaton.addTransition(3, '7', 1);
        automaton.addTransition(8, 'v', 1);
        automaton.addTransition(5, '0', 0);
        automaton.addTransition(5, '0', 7);
        automaton.addTransition(7, 'j', 2);
        automaton.addTransition(3, 'o', 1);
        automaton.addTransition(3, 'j', 7);
    }

    void initAutomatonInutile() {
        automatonInutile.addState(1);
        automatonInutile.setStateInitial(1);
        automatonInutile.addState(2);
        automatonInutile.setStateFinal(2);
        automatonInutile.addState(3);
        automatonInutile.addTransition(1, 'a', 2);
        automatonInutile.addTransition(2, 'a', 1);
    }

    void initAutomatonCoAccessible() {
        automatonCoAccessible.addState(1);
        automatonCoAccessible.setStateInitial(1);
        automatonCoAccessible.addState(2);
        automatonCoAccessible.setStateFinal(2);
        automatonCoAccessible.addState(3);
        automatonCoAccessible.addState(4);
        automatonCoAccessible.addState(5);
        automatonCoAccessible.addTransition(1, 'a', 2);
        automatonCoAccessible.addTransition(1, 'b', 2);
        automatonCoAccessible.addTransition(2, 'a', 1);
        automatonCoAccessible.addTransition(2, 'b', 1);
        automatonCoAccessible.addTransition(3, 'a', 1);
        automatonCoAccessible.addTransition(3, 'a', 2);
        automatonCoAccessible.addTransition(4, 'a', 3);
        automatonCoAccessible.addTransition(5, 'a', 3);
    }

    void initAutomatonEmptyInutileIsInitial() {
        automatonEmptyInutileIsInitial.addState(1);
        automatonEmptyInutileIsInitial.addState(2);
        automatonEmptyInutileIsInitial.setStateFinal(2);
        automatonEmptyInutileIsInitial.addState(3);
        automatonEmptyInutileIsInitial.setStateInitial(3);
        automatonEmptyInutileIsInitial.addTransition(1, 'a', 2);
        automatonEmptyInutileIsInitial.addTransition(2, 'a', 1);
    }

    void initAutomatonEmpty() {
        automatonEmpty.addState(1);
        automatonEmpty.setStateInitial(1);
        automatonEmpty.addState(2);
        automatonEmpty.setStateFinal(2);
        automatonEmpty.addState(3);
        automatonEmpty.addTransition(3, 'a', 2);
        automatonEmpty.addTransition(3, 'a', 1);
    }

    void initAutomatonEmptyNoInitial() {
        automatonEmptyNoInitial.addState(1);
        automatonEmptyNoInitial.addState(2);
        automatonEmptyNoInitial.setStateFinal(2);
    }

    void initAutomatonEmptyNoFinal() {
        automatonEmptyNoFinal.addState(1);
        automatonEmptyNoFinal.setStateInitial(1);
        automatonEmptyNoFinal.addState(2);
    }

    fa::Automaton automatonNotCompleteNotDeterministic;
    fa::Automaton automatonNotCompleteDeterministic;
    fa::Automaton automatonCompleteNotDeterministic;
    fa::Automaton automatonCompleteDeterministic;
    fa::Automaton automatonInutile;
    fa::Automaton automatonCoAccessible;
    fa::Automaton automaton;
    fa::Automaton automatonEmptyInutileIsInitial;
    fa::Automaton automatonEmpty;
    fa::Automaton automatonEmptyNoInitial;
    fa::Automaton automatonEmptyNoFinal;

};


TEST(AutomatonTest, Empty) {
    fa::Automaton fa;

    EXPECT_EQ(fa.countStates(), 0u);
    EXPECT_EQ(fa.countTransitions(), 0u);
}


//*************************************************************************************
//                  AUTOMATON TEST
//*************************************************************************************

//addState
TEST_F(AutomatonTestFixture, addState) {
    EXPECT_EQ(automatonNotCompleteNotDeterministic.countStates(), 5u);
    EXPECT_TRUE(automatonNotCompleteNotDeterministic.hasState(0));
    EXPECT_TRUE(automatonNotCompleteNotDeterministic.hasState(1));
    EXPECT_TRUE(automatonNotCompleteNotDeterministic.hasState(2));
    EXPECT_TRUE(automatonNotCompleteNotDeterministic.hasState(3));
    EXPECT_TRUE(automatonNotCompleteNotDeterministic.hasState(4));
}

//removeState
TEST_F(AutomatonTestFixture, removeState) {
    automatonNotCompleteNotDeterministic.removeState(0);
    EXPECT_EQ(automatonNotCompleteNotDeterministic.countStates(), 4u);
    EXPECT_FALSE(automatonNotCompleteNotDeterministic.hasState(0));
}

//Initial/Final
TEST(AutomatonTest, setInitialTestStateDontExist) {
    fa::Automaton aut;
    EXPECT_DEATH(aut.setStateInitial(123), "");
}

TEST(AutomatonTest, setInitialTestStateExistIsInitial) {
    fa::Automaton aut;
    aut.addState(0);
    aut.setStateInitial(0);
    ASSERT_TRUE(aut.isStateInitial(0));
}

TEST(AutomatonTest, setInitialTestStateExistNotInitial) {
    fa::Automaton aut;
    aut.addState(0);
    ASSERT_FALSE(aut.isStateInitial(0));
}


TEST(AutomatonTest, setFinalTestDontExist) {
    fa::Automaton aut;
    EXPECT_DEATH(aut.setStateInitial(123), "");
}

TEST(AutomatonTest, setFinalTestStateExistIsInitial) {
    fa::Automaton aut;
    aut.addState(0);
    aut.setStateFinal(0);
    ASSERT_TRUE(aut.isStateFinal(0));
}

TEST(AutomatonTest, setFinalTestStateExistNotFinal) {
    fa::Automaton aut;
    aut.addState(0);
    ASSERT_FALSE(aut.isStateFinal(0));
}

//addTransition

TEST(AutomatonTest, addAlphabetTestNotPrintable) {
    fa::Automaton aut;
    aut.addState(0);
    aut.addState(1);
    EXPECT_DEATH(aut.addTransition(0, (char) 12, 1), "");
}

TEST(AutomatonTest, addTransitionTestStateExistTransitionExist) {
    fa::Automaton aut;
    aut.addState(0);
    aut.addState(1);
    aut.addTransition(0, 'a', 1);
    EXPECT_TRUE(aut.hasTransition(0, 'a', 1));
    EXPECT_EQ(1u, aut.getAlphabetSize());
    EXPECT_EQ(1u, aut.countTransitions());
}

TEST(AutomatonTest, addTransitionTestStateDontExist) {
    fa::Automaton aut;
    EXPECT_DEATH({ aut.addTransition(123, 't', 456); }, "");
    EXPECT_EQ(0u, aut.countTransitions());
}

TEST(AutomatonTest, addTransitionTestState2DontExist) {
    fa::Automaton aut;
    aut.addState(0);
    EXPECT_DEATH({ aut.addTransition(0, 't', 1); }, "");
    EXPECT_EQ(0u, aut.getAlphabetSize());
}

TEST(AutomatonTest, addTransitionTestState1DontExist) {
    fa::Automaton aut;
    aut.addState(1);
    EXPECT_DEATH({ aut.addTransition(0, 't', 1); }, "");
    EXPECT_EQ(0u, aut.getAlphabetSize());
}


TEST(AutomatonTest, addTransitionTestStateExistTransitionDontExist) {
    fa::Automaton aut;
    aut.addState(0);
    aut.addState(1);
    EXPECT_FALSE(aut.hasTransition(0, 'a', 1));
    EXPECT_EQ(0u, aut.countTransitions());

}

//removeTransition


TEST(AutomatonTest, removeTransitionTestStateExistTransitionExist) {
    fa::Automaton aut;
    aut.addState(0);
    aut.addState(1);
    aut.addTransition(0, 'a', 1);
    aut.removeTransition(0, 'a', 1);
    EXPECT_FALSE(aut.hasTransition(0, 'a', 1));
    EXPECT_EQ(1u, aut.getAlphabetSize());
    EXPECT_EQ(0u, aut.countTransitions());
}

TEST(AutomatonTest, removeTransitionTestStateDontExist) {
    fa::Automaton aut;
    EXPECT_DEATH({ aut.removeTransition(123, 't', 456); }, "");
}

TEST(AutomatonTest, removeTransitionTestState2DontExist) {
    fa::Automaton aut;
    aut.addState(1);
    aut.addState(0);
    aut.addTransition(0, 'a', 1);
    EXPECT_DEATH({ aut.removeTransition(0, 't', 3); }, "");
}

TEST(AutomatonTest, removeTransitionTestState1DontExist) {
    fa::Automaton aut;
    aut.addState(1);
    aut.addState(0);
    aut.addTransition(0, 'a', 1);
    EXPECT_DEATH({ aut.removeTransition(3, 't', 1); }, "");
}


TEST(AutomatonTest, removeTransitionTestStateExistTransitionDontExist) {
    fa::Automaton aut;
    aut.addState(0);
    aut.addState(1);
    EXPECT_DEATH(aut.removeTransition(0, 'a', 1), "");
}

/**
 * Print an automaton.
 */
TEST_F(AutomatonTestFixture, prettyPrint) {
    DOT_PRINT(automaton, std::string("automaton"), ofstream0)
    DOT_PRINT(automatonNotCompleteNotDeterministic, std::string("automatonNotCompleteNotDeterministic"), ofstream1)
    DOT_PRINT(automatonNotCompleteDeterministic, std::string("automatonNotCompleteDeterministic"), ofstream2)
    DOT_PRINT(automatonCompleteNotDeterministic, std::string("automatonCompleteNotDeterministic"), ofstream3)
    DOT_PRINT(automatonInutile, std::string("automatonInutile"), ofstream4)
    DOT_PRINT(automatonCompleteDeterministic, std::string("automatonCompleteDeterministic"), ofstream5)
    DOT_PRINT(automatonCoAccessible, std::string("automatonCoAccessible"), ofstream6)
    DOT_PRINT(automatonEmptyInutileIsInitial, std::string("automatonEmptyInutileIsInitial"), ofstream7)
    DOT_PRINT(automatonEmpty, std::string("automatonEmpty"), ofstream8)
    DOT_PRINT(automatonEmptyNoInitial, std::string("automatonEmptyNoInitial"), ofstream9)
    DOT_PRINT(automatonEmptyNoFinal, std::string("automatonEmptyNoFinal"), ofstream10)
}

//******************************************************
//              Part 2
//******************************************************

//isDeterministic

TEST_F(AutomatonTestFixture, isDeterministicTestAutomatonCompleteDeterministic) {
    EXPECT_TRUE(automatonCompleteDeterministic.isDeterministic());
}

TEST_F(AutomatonTestFixture, isDeterministicTestAutomatonNotCompleteDeterministic) {
    EXPECT_TRUE(automatonNotCompleteDeterministic.isDeterministic());
}

TEST_F(AutomatonTestFixture, isDeterministicTestAutomatonCompleteNotDeterministic) {
    EXPECT_FALSE(automatonCompleteNotDeterministic.isDeterministic());
}

TEST_F(AutomatonTestFixture, isDeterministicTcestAutomatonNotCompleteNotDeterministic) {
    EXPECT_FALSE(automatonNotCompleteNotDeterministic.isDeterministic());
}

TEST_F(AutomatonTestFixture, isDeterministicTcestAutomaton) {
    EXPECT_FALSE(automaton.isDeterministic());
}

TEST_F(AutomatonTestFixture, isDeterministicTestAutomatonInutile) {
    EXPECT_TRUE(automatonInutile.isDeterministic());
}

TEST_F(AutomatonTestFixture, isDeterministicTestAutomatonCoAccessible) {
    EXPECT_FALSE(automatonCoAccessible.isDeterministic());
}

//isComplete

TEST_F(AutomatonTestFixture, isCompleteTestAutomatonCompleteDeterministic) {
    EXPECT_TRUE(automatonCompleteDeterministic.isComplete());
}

TEST_F(AutomatonTestFixture, isCompleteTestAutomatonNotCompleteDeterministic) {
    EXPECT_FALSE(automatonNotCompleteDeterministic.isComplete());
}

TEST_F(AutomatonTestFixture, isCompleteTestAutomatonCompleteNotDeterministic) {
    EXPECT_TRUE(automatonCompleteNotDeterministic.isComplete());
}

TEST_F(AutomatonTestFixture, isCompleteTestAutomatonNotCompleteNotDeterministic) {
    EXPECT_FALSE(automatonNotCompleteNotDeterministic.isComplete());
}

TEST_F(AutomatonTestFixture, isCompleteTestAutomaton) {
    EXPECT_FALSE(automaton.isComplete());
}

TEST_F(AutomatonTestFixture, isCompleteTestAutomatonInutile) {
    EXPECT_FALSE(automatonInutile.isComplete());
}

TEST_F(AutomatonTestFixture, isCompleteTestAutomatonCoAccessible) {
    EXPECT_FALSE(automatonCoAccessible.isComplete());
}
//makeComplete

TEST_F(AutomatonTestFixture, makeCompleteTestNotComplete) {
    size_t size = automatonNotCompleteNotDeterministic.getAlphabetSize();
    EXPECT_FALSE(automatonNotCompleteNotDeterministic.isComplete());
    automatonNotCompleteNotDeterministic.makeComplete();
    EXPECT_EQ(size, automatonNotCompleteNotDeterministic.getAlphabetSize());
    EXPECT_TRUE(automatonNotCompleteNotDeterministic.isComplete());
    EXPECT_TRUE(automatonNotCompleteNotDeterministic.match("abaaaaaaaaaaaaaaaaa"));
}

TEST_F(AutomatonTestFixture, makeCompleteTestAutomaton) {
    size_t size = automaton.getAlphabetSize();
    EXPECT_FALSE(automaton.isComplete());
    automaton.makeComplete();
    EXPECT_EQ(size, automaton.getAlphabetSize());
    EXPECT_TRUE(automaton.isComplete());
    EXPECT_TRUE(automaton.match("aaaaaaaaaaaaoa0j"));
}

TEST_F(AutomatonTestFixture, makeCompleteTestAlphabetSame) {
    size_t i = automatonNotCompleteNotDeterministic.getAlphabetSize();
    automatonNotCompleteNotDeterministic.makeComplete();
    EXPECT_EQ(i, automatonNotCompleteNotDeterministic.getAlphabetSize());
}

TEST_F(AutomatonTestFixture, makeCompleteTestComplete) {
    EXPECT_TRUE(automatonCompleteNotDeterministic.isComplete());
    automatonNotCompleteNotDeterministic.makeComplete();
    EXPECT_TRUE(automatonCompleteNotDeterministic.isComplete());
}

//make Complement

TEST_F(AutomatonTestFixture, makeComplement) {
    automatonInutile.makeComplement();
    EXPECT_TRUE(automatonInutile.isStateFinal(1));
    EXPECT_FALSE(automatonInutile.isStateFinal(2));
    EXPECT_TRUE(automatonInutile.isStateFinal(3));
}

//******************************************************
//              Part 3
//******************************************************

//isLanguageEmpty

TEST_F(AutomatonTestFixture, isLanguageEmptyAutomate) {
    EXPECT_FALSE(automaton.isLanguageEmpty());
}

TEST_F(AutomatonTestFixture, isLanguageEmptyAutomatonCoAccessible) {
    EXPECT_FALSE(automatonCoAccessible.isLanguageEmpty());
}

TEST_F(AutomatonTestFixture, isLanguageEmptyAutomatonCompleteDeterministic) {
    EXPECT_FALSE(automatonCompleteDeterministic.isLanguageEmpty());
}

TEST_F(AutomatonTestFixture, isLanguageEmptyAutomatonCompleteNotDeterministic) {
    EXPECT_FALSE(automatonCompleteNotDeterministic.isLanguageEmpty());
}

TEST_F(AutomatonTestFixture, isLanguageEmptyAutomatonNotCompleteNotDeterministic) {
    EXPECT_FALSE(automatonNotCompleteNotDeterministic.isLanguageEmpty());
}

TEST_F(AutomatonTestFixture, isLanguageEmptyAutomatonEmpty) {
    EXPECT_TRUE(automatonEmpty.isLanguageEmpty());
}

TEST_F(AutomatonTestFixture, isLanguageEmptyAutomatonEmptyInutileIsInitial) {
    EXPECT_TRUE(automatonEmptyInutileIsInitial.isLanguageEmpty());
}

TEST_F(AutomatonTestFixture, isLanguageEmptyAutomatonEmptyNoFinal) {
    EXPECT_TRUE(automatonEmptyNoFinal.isLanguageEmpty());
}

TEST_F(AutomatonTestFixture, isLanguageEmptyAutomatonInutile) {
    EXPECT_FALSE(automatonInutile.isLanguageEmpty());
}

TEST_F(AutomatonTestFixture, isLanguageEmptyAutomatonNotCompleteDeterministic) {
    EXPECT_FALSE(automatonNotCompleteDeterministic.isLanguageEmpty());
}

TEST_F(AutomatonTestFixture, isLanguageEmptyAutomatonEmptyNoInitial) {
    EXPECT_TRUE(automatonEmptyNoInitial.isLanguageEmpty());
}

//removeNonAccessibleStates

TEST_F(AutomatonTestFixture, removeNonAccessibleStatesAutomate) {
    automaton.removeNonAccessibleStates();
    EXPECT_EQ((unsigned)7, automaton.countStates());
    EXPECT_TRUE(automaton.match("aaaaaaaaaaaaoa0j"));

}

TEST_F(AutomatonTestFixture, removeNonAccessibleStatesAutomatonCoAccessible) {
    automatonCoAccessible.removeNonAccessibleStates();
    EXPECT_EQ((unsigned)2, automatonCoAccessible.countStates());
}

TEST_F(AutomatonTestFixture, removeNonAccessibleStatesAutomatonCompleteDeterministic) {
    automatonCompleteDeterministic.removeNonAccessibleStates();
    EXPECT_EQ((unsigned)2, automatonCompleteDeterministic.countStates());
}

TEST_F(AutomatonTestFixture, removeNonAccessibleStatesAutomatonCompleteNotDeterministic) {
    automatonCompleteNotDeterministic.removeNonAccessibleStates();
    EXPECT_EQ((unsigned)2, automatonCompleteDeterministic.countStates());
}

TEST_F(AutomatonTestFixture, removeNonAccessibleStatesAutomatonNotCompleteNotDeterministic) {
    automatonNotCompleteNotDeterministic.removeNonAccessibleStates();
    EXPECT_EQ((unsigned)5, automatonNotCompleteNotDeterministic.countStates());
}

TEST_F(AutomatonTestFixture, removeNonAccessibleStatesAutomatonEmpty) {
    automatonEmpty.removeNonAccessibleStates();
    EXPECT_EQ((unsigned)1, automatonEmpty.countStates());
}

TEST_F(AutomatonTestFixture, removeNonAccessibleStatesAutomatonEmptyInutileIsInitial) {
    automatonEmptyInutileIsInitial.removeNonAccessibleStates();
    EXPECT_EQ((unsigned)1, automatonEmptyInutileIsInitial.countStates());
}

TEST_F(AutomatonTestFixture, removeNonAccessibleStatesAutomatonEmptyNoFinal) {
    automatonEmptyNoFinal.removeNonAccessibleStates();
    EXPECT_EQ((unsigned)1, automatonEmptyNoFinal.countStates());
}

TEST_F(AutomatonTestFixture, removeNonAccessibleStatesAutomatonInutile) {
    automatonInutile.removeNonAccessibleStates();
    EXPECT_EQ((unsigned)2, automatonInutile.countStates());
}

TEST_F(AutomatonTestFixture, removeNonAccessibleStatesAutomatonNotCompleteDeterministic) {
    automatonNotCompleteDeterministic.removeNonAccessibleStates();
    EXPECT_EQ((unsigned)3, automatonNotCompleteDeterministic.countStates());
}

TEST_F(AutomatonTestFixture, removeNonAccessibleStatesAutomatonEmptyNoInitial) {
    automatonEmptyNoInitial.removeNonAccessibleStates();
    EXPECT_EQ((unsigned)0, automatonEmptyNoInitial.countStates());
}

//removeNonCoAccessibleStates

TEST_F(AutomatonTestFixture, removeNonCoAccessibleStatesAutomate) {
    automaton.removeNonCoAccessibleStates();
    EXPECT_EQ((unsigned)7, automaton.countStates());
    EXPECT_TRUE(automaton.match("aaaaaaaaaaaaoa0j"));

}

TEST_F(AutomatonTestFixture, removeNonCoAccessibleStatesAutomatonCoAccessible) {
    automatonCoAccessible.removeNonCoAccessibleStates();
    EXPECT_EQ((unsigned)5, automatonCoAccessible.countStates());
}

TEST_F(AutomatonTestFixture, removeNonCoAccessibleStatesAutomatonCompleteDeterministic) {
    automatonCompleteDeterministic.removeNonCoAccessibleStates();
    EXPECT_EQ((unsigned)2, automatonCompleteDeterministic.countStates());
}

TEST_F(AutomatonTestFixture, removeNonCoAccessibleStatesAutomatonCompleteNotDeterministic) {
    automatonCompleteNotDeterministic.removeNonCoAccessibleStates();
    EXPECT_EQ((unsigned)2, automatonCompleteDeterministic.countStates());
}

TEST_F(AutomatonTestFixture, removeNonCoAccessibleStatesAutomatonNotCompleteNotDeterministic) {
    automatonNotCompleteNotDeterministic.removeNonCoAccessibleStates();
    EXPECT_EQ((unsigned)5, automatonNotCompleteNotDeterministic.countStates());
}

TEST_F(AutomatonTestFixture, removeNonCoAccessibleStatesAutomatonEmpty) {
    automatonEmpty.removeNonCoAccessibleStates();
    EXPECT_EQ((unsigned)2, automatonEmpty.countStates());
}

TEST_F(AutomatonTestFixture, removeNonCoAccessibleStatesAutomatonEmptyInutileIsInitial) {
    automatonEmptyInutileIsInitial.removeNonCoAccessibleStates();
    EXPECT_EQ((unsigned)2, automatonEmptyInutileIsInitial.countStates());
}

TEST_F(AutomatonTestFixture, removeNonCoAccessibleStatesAutomatonEmptyNoFinal) {
    automatonEmptyNoFinal.removeNonCoAccessibleStates();
    EXPECT_EQ((unsigned)0, automatonEmptyNoFinal.countStates());
}

TEST_F(AutomatonTestFixture, removeNonCoAccessibleStatesAutomatonInutile) {
    automatonInutile.removeNonCoAccessibleStates();
    EXPECT_EQ((unsigned)2, automatonInutile.countStates());
}

TEST_F(AutomatonTestFixture, removeNonCoAccessibleStatesAutomatonNotCompleteDeterministic) {
    automatonNotCompleteDeterministic.removeNonCoAccessibleStates();
    EXPECT_EQ((unsigned)3, automatonNotCompleteDeterministic.countStates());
}

TEST_F(AutomatonTestFixture, removeNonCoAccessibleStatesAutomatonEmptyNoInitial) {
    automatonEmptyNoInitial.removeNonCoAccessibleStates();
    EXPECT_EQ((unsigned)1, automatonEmptyNoInitial.countStates());
}

//createProduct.

TEST_F(AutomatonTestFixture, createProduct) {
    fa::Automaton res = fa::Automaton::createProduct(automatonCompleteDeterministic, automatonNotCompleteDeterministic);
    EXPECT_TRUE(res.isStateInitial(0));
    EXPECT_FALSE(res.isStateInitial(4));
    EXPECT_FALSE(res.isStateInitial(5));
    EXPECT_FALSE(res.isStateInitial(2));
    EXPECT_FALSE(res.isStateFinal(0));
    EXPECT_FALSE(res.isStateFinal(4));
    EXPECT_FALSE(res.isStateFinal(2));
    EXPECT_TRUE(res.isStateFinal(5));
}

TEST_F(AutomatonTestFixture, createProduct_match) {
    fa::Automaton res = fa::Automaton::createProduct(automatonCompleteDeterministic, automatonNotCompleteDeterministic);
    EXPECT_FALSE(res.match("aab"));
    EXPECT_TRUE(res.match("ab"));
    EXPECT_TRUE(res.match("abbbbbbb"));
    EXPECT_TRUE(res.match("abbbbbbbbbbbbbbbbbbbaaab"));
    EXPECT_FALSE(res.match("aab"));
    EXPECT_FALSE(res.match("aaabbbbbbbbbbbbbbbbb"));
    EXPECT_FALSE(res.match("aaaaaaaaaaaaaaaaa"));
    EXPECT_FALSE(res.match("aa"));
    EXPECT_FALSE(res.match(""));
}


TEST_F(AutomatonTestFixture, createProductAutomatonCompleteDeterministic) {
    fa::Automaton res = fa::Automaton::createProduct(automatonCompleteDeterministic, automatonCompleteDeterministic);
    EXPECT_TRUE(res.isStateInitial(0));
    EXPECT_FALSE(res.isStateInitial(3));
    EXPECT_FALSE(res.isStateFinal(0));
    EXPECT_TRUE(res.isStateFinal(3));
}

TEST_F(AutomatonTestFixture, createProductAutomatonCompleteDeterministic_match) {
    fa::Automaton res = fa::Automaton::createProduct(automatonCompleteDeterministic, automatonCompleteDeterministic);
    EXPECT_TRUE(res.match("aab"));
    EXPECT_TRUE(res.match("aaabbbbbbbbbbbbbbbbb"));
    EXPECT_FALSE(res.match("aa"));
    EXPECT_FALSE(res.match(""));
    EXPECT_FALSE(res.match("hniure"));
}


TEST_F(AutomatonTestFixture, createProductAutomatonNotCompleteDeterministic) {
    fa::Automaton res = fa::Automaton::createProduct(automatonNotCompleteDeterministic, automatonNotCompleteDeterministic);
    EXPECT_EQ((unsigned)3, res.countStates());
    EXPECT_TRUE(res.isStateInitial(0));
    EXPECT_FALSE(res.isStateInitial(4));
    EXPECT_FALSE(res.isStateInitial(8));
    EXPECT_FALSE(res.isStateFinal(0));
    EXPECT_FALSE(res.isStateFinal(4));
    EXPECT_TRUE(res.isStateFinal(8));
}

TEST_F(AutomatonTestFixture, createProductAutomatonNotCompleteDeterministic_match) {
    fa::Automaton res = fa::Automaton::createProduct(automatonNotCompleteDeterministic, automatonNotCompleteDeterministic);
    EXPECT_FALSE(res.match("aa"));
    EXPECT_FALSE(res.match("aaaaaaaaaaaaaa"));
    EXPECT_TRUE(res.match("abaaaaaa"));
    EXPECT_TRUE(res.match("abbbbbbbbbbbbbbbbb"));
    EXPECT_TRUE(res.match("ab"));
    EXPECT_FALSE(res.match("hniure"));
}

TEST_F(AutomatonTestFixture, createProductAutomatonCompleteNotDeterministic) {
    fa::Automaton res = fa::Automaton::createProduct(automatonCompleteNotDeterministic, automatonCompleteNotDeterministic);
    EXPECT_EQ((unsigned)4, res.countStates());
    EXPECT_TRUE(res.isStateInitial(0));
    EXPECT_FALSE(res.isStateInitial(2));
    EXPECT_FALSE(res.isStateInitial(3));
    EXPECT_FALSE(res.isStateFinal(0));
    EXPECT_FALSE(res.isStateFinal(2));
    EXPECT_TRUE(res.isStateFinal(3));
}

TEST_F(AutomatonTestFixture, createProductAutomatonCompleteNotDeterministic_match) {
    fa::Automaton res = fa::Automaton::createProduct(automatonCompleteNotDeterministic, automatonCompleteNotDeterministic);
    EXPECT_TRUE(res.match("aab"));
    EXPECT_TRUE(res.match("aaabbbbbbbbbbbbbbbbb"));
    EXPECT_TRUE(res.match("aaaaaaaaaaaaaaaaa"));
    EXPECT_TRUE(res.match("aa"));
    EXPECT_FALSE(res.match(""));
    EXPECT_FALSE(res.match("hniure"));
}

TEST_F(AutomatonTestFixture, createProductAutomatonNotCompleteNotDeterministic) {
    fa::Automaton res = fa::Automaton::createProduct(automatonNotCompleteNotDeterministic, automatonCompleteNotDeterministic);
    EXPECT_TRUE(res.match("a"));
    EXPECT_TRUE(res.match("aaaaaaaaaaaaaabaaaaaaa"));
    EXPECT_TRUE(res.match("abb"));
    EXPECT_TRUE(res.match("ab"));
    EXPECT_TRUE(res.match("aab"));
    EXPECT_FALSE(res.match("aaaaaaaaaaaaaaaaa"));
    EXPECT_FALSE(res.match("aa"));
}

TEST_F(AutomatonTestFixture, createProductAutomaton) {
    fa::Automaton res = fa::Automaton::createProduct(automaton, automatonNotCompleteNotDeterministic);
    EXPECT_TRUE(res.isLanguageEmpty());
}

TEST_F(AutomatonTestFixture, createProductAutomatonEmpty) {
    fa::Automaton res = fa::Automaton::createProduct(automatonEmptyNoFinal, automatonCompleteNotDeterministic);
    EXPECT_TRUE(res.isLanguageEmpty());
}

TEST_F(AutomatonTestFixture, createProductAutomatonANDautomatonCoAccessible) {
    fa::Automaton res = fa::Automaton::createProduct(automatonCompleteDeterministic, automatonCoAccessible);

}

TEST_F(AutomatonTestFixture, createAANDB) {
    fa::Automaton A;
    A.addState(0);
    A.setStateInitial(0);
    A.addState(1);
    A.setStateFinal(1);
    A.addTransition(0, 'a', 1);

    fa::Automaton B;
    B.addState(0);
    B.setStateInitial(0);
    B.addState(1);
    B.setStateFinal(1);
    B.addTransition(0, 'b', 1);
    fa::Automaton res = fa::Automaton::createProduct(A, B);
    EXPECT_TRUE(res.isLanguageEmpty());
}

//******************************************************
//              hasEmptyIntersectionWith
//******************************************************

TEST_F(AutomatonTestFixture, hasEmptyIntersectionWithAutomatonANDAutomatonCoAccessible){
    EXPECT_FALSE(automatonCompleteDeterministic.hasEmptyIntersectionWith(automatonCoAccessible));
}

TEST_F(AutomatonTestFixture, hasEmptyIntersectionWithAutomatonANDAutomatonInutile){
    EXPECT_FALSE(automatonCompleteDeterministic.hasEmptyIntersectionWith(automatonInutile));
}

TEST_F(AutomatonTestFixture, hasEmptyIntersectionWithAutomatonANDAutomatonEmpty){
    EXPECT_TRUE(automatonCompleteDeterministic.hasEmptyIntersectionWith(automatonEmpty));
}

TEST_F(AutomatonTestFixture, hasEmptyIntersectionWithAutomatonANDAutomatonNotCompleteNotDeterministic){
    EXPECT_FALSE(automatonCompleteDeterministic.hasEmptyIntersectionWith(automatonNotCompleteNotDeterministic));
}

TEST_F(AutomatonTestFixture, hasEmptyIntersectionWithAutomatonANDAutomatonEmptyNoInitial){
    EXPECT_TRUE(automatonCompleteDeterministic.hasEmptyIntersectionWith(automatonEmptyNoInitial));
}

TEST_F(AutomatonTestFixture, hasEmptyIntersectionWithAutomatonANDAutomatonEmptyNoFinal){
    EXPECT_TRUE(automatonCompleteDeterministic.hasEmptyIntersectionWith(automatonEmptyNoFinal));
}

TEST_F(AutomatonTestFixture, hasEmptyIntersectionWithAutomatonANDAutomaton){
    EXPECT_TRUE(automatonCompleteDeterministic.hasEmptyIntersectionWith(automaton));
}

TEST_F(AutomatonTestFixture, hasEmptyIntersectionWithAutomatonEmptyANDAutomatonEmptyInutileIsInitial){
    EXPECT_TRUE(automatonCompleteDeterministic.hasEmptyIntersectionWith(automatonEmptyInutileIsInitial));
}

//******************************************************
//              readString
//******************************************************

TEST_F(AutomatonTestFixture, readString){
    std::set<int> res = automaton.readString("za0");
    EXPECT_TRUE(res.find(0) != res.end());
    EXPECT_TRUE(res.find(1) != res.end());
    EXPECT_TRUE(res.find(5) != res.end());
    EXPECT_TRUE(res.find(7) != res.end());
    EXPECT_EQ((unsigned)4, res.size());
}

TEST_F(AutomatonTestFixture, readStringEmptyWord){
    std::set<int> res = automaton.readString("");
    EXPECT_TRUE(res.find(2) != res.end());
}
//TODO: tester NULL partout.
//******************************************************
//              match
//******************************************************

TEST_F(AutomatonTestFixture, matchAutomaton){
    EXPECT_TRUE(automaton.match("za0j"));
//    EXPECT_FALSE(automaton.match(nullptr));
    EXPECT_TRUE(automaton.match("za0"));
    EXPECT_TRUE(automaton.match("za0za0"));
    EXPECT_TRUE(automaton.match(""));
    EXPECT_FALSE(automaton.match("za"));
    EXPECT_FALSE(automaton.match("hniure"));
}

TEST_F(AutomatonTestFixture, matchAutomatonCoAccessible){
    EXPECT_TRUE(automatonCoAccessible.match("aab"));
    EXPECT_TRUE(automatonCoAccessible.match("a"));
    EXPECT_FALSE(automatonCoAccessible.match("aa"));
    EXPECT_FALSE(automatonCoAccessible.match(""));
    EXPECT_FALSE(automatonCoAccessible.match("hniure"));
}


TEST_F(AutomatonTestFixture, matchAutomatonCompleteDeterministic){
    EXPECT_TRUE(automatonCompleteDeterministic.match("aab"));
    EXPECT_TRUE(automatonCompleteDeterministic.match("aaabbbbbbbbbbbbbbbbb"));
    EXPECT_FALSE(automatonCompleteDeterministic.match("aa"));
    EXPECT_FALSE(automatonCompleteDeterministic.match(""));
    EXPECT_FALSE(automatonCompleteDeterministic.match("hniure"));
}

TEST_F(AutomatonTestFixture, matchAutomatonCompleteNotDeterministic){
    EXPECT_TRUE(automatonCompleteNotDeterministic.match("aab"));
    EXPECT_TRUE(automatonCompleteNotDeterministic.match("aaabbbbbbbbbbbbbbbbb"));
    EXPECT_TRUE(automatonCompleteNotDeterministic.match("aaaaaaaaaaaaaaaaa"));
    EXPECT_TRUE(automatonCompleteNotDeterministic.match("aa"));
    EXPECT_FALSE(automatonCompleteNotDeterministic.match(""));
    EXPECT_FALSE(automatonCompleteNotDeterministic.match("hniure"));
}

TEST_F(AutomatonTestFixture, matchAutomatonEmpty){
    EXPECT_FALSE(automatonEmpty.match(""));
    EXPECT_FALSE(automatonEmpty.match("aaabbbbbbbbbbbbbbbbb"));
    EXPECT_FALSE(automatonEmpty.match("aa"));
    EXPECT_FALSE(automatonEmpty.match("hniure"));
}

TEST_F(AutomatonTestFixture, matchAutomatonInutile){
    EXPECT_FALSE(automatonInutile.match("aa"));
    EXPECT_TRUE(automatonInutile.match("aaaaaaaaaaaaa"));
    EXPECT_FALSE(automatonInutile.match("aaabbbbbbbbbbbbbbbbb"));
    EXPECT_FALSE(automatonInutile.match("hniure"));
}

TEST_F(AutomatonTestFixture, matchAutomatonNotCompleteDeterministic){
    EXPECT_FALSE(automatonNotCompleteDeterministic.match("aa"));
    EXPECT_FALSE(automatonNotCompleteDeterministic.match("aaaaaaaaaaaaaa"));
    EXPECT_FALSE(automatonNotCompleteDeterministic.match("aaaaaaaaaaaaaab"));
    EXPECT_TRUE(automatonNotCompleteDeterministic.match("abbbbbbbbbbbbbbbbb"));
    EXPECT_TRUE(automatonNotCompleteDeterministic.match("ab"));
    EXPECT_TRUE(automatonNotCompleteDeterministic.match("abaaaaaaaaaaaaaaa"));
    EXPECT_FALSE(automatonNotCompleteDeterministic.match("hniure"));
}

TEST_F(AutomatonTestFixture, matchAutomatonNotCompleteNotDeterministic){
    EXPECT_TRUE(automatonNotCompleteNotDeterministic.match("a"));
    EXPECT_TRUE(automatonNotCompleteNotDeterministic.match("aaaaaaaaaaaaaabaaaaaaa"));
    EXPECT_TRUE(automatonNotCompleteNotDeterministic.match("abb"));
    EXPECT_TRUE(automatonNotCompleteNotDeterministic.match("ab"));
    EXPECT_FALSE(automatonNotCompleteNotDeterministic.match("aaaaaaaaaaaaaaaaaaa"));
    EXPECT_FALSE(automatonNotCompleteNotDeterministic.match("hniure"));
}

//******************************************************
//              createDeterministic
//******************************************************


TEST_F(AutomatonTestFixture, createDeterimisticAutomaton){
    fa::Automaton res = fa::Automaton::createDeterministic(automaton);
    EXPECT_TRUE(res.isDeterministic());
}

TEST_F(AutomatonTestFixture, createDeterimisticAutomaton_match){
    fa::Automaton res = fa::Automaton::createDeterministic(automaton);
    EXPECT_TRUE(res.match("za0j"));
//    EXPECT_FALSE(res.match(nullptr));
    EXPECT_TRUE(res.match("za0"));
    EXPECT_TRUE(res.match(""));
    EXPECT_FALSE(res.match("za"));
    EXPECT_FALSE(res.match("hniure"));
}

TEST_F(AutomatonTestFixture, createDeterimisticAutomatonCoAccessible){
    fa::Automaton res = fa::Automaton::createDeterministic(automatonCoAccessible);
    EXPECT_TRUE(res.isDeterministic());
}

TEST_F(AutomatonTestFixture, createDeterimisticAutomatonCoAccessible_match){
    fa::Automaton res = fa::Automaton::createDeterministic(automatonCoAccessible);
    EXPECT_TRUE(res.match("aab"));
    EXPECT_TRUE(res.match("a"));
    EXPECT_FALSE(res.match("aa"));
    EXPECT_FALSE(res.match(""));
    EXPECT_FALSE(res.match("hniure"));
}

TEST_F(AutomatonTestFixture, createDeterimisticAutomatonCompleteDeterministic){
    fa::Automaton res = fa::Automaton::createDeterministic(automatonCompleteDeterministic);
    EXPECT_TRUE(res.isDeterministic());
}

TEST_F(AutomatonTestFixture, createDeterimisticAutomatonCompleteDeterministic_match){
    fa::Automaton res = fa::Automaton::createDeterministic(automatonCompleteDeterministic);
    EXPECT_TRUE(res.match("aab"));
    EXPECT_TRUE(res.match("aaabbbbbbbbbbbbbbbbb"));
    EXPECT_FALSE(res.match("aa"));
    EXPECT_FALSE(res.match(""));
    EXPECT_FALSE(res.match("hniure"));
}

TEST_F(AutomatonTestFixture, createDeterministicCompleteNotDeterministic){
    fa::Automaton res = fa::Automaton::createDeterministic(automatonCompleteNotDeterministic);
    EXPECT_TRUE(res.isDeterministic());
}

TEST_F(AutomatonTestFixture, createDeterministicCompleteNotDeterministic_match){
    fa::Automaton res = fa::Automaton::createDeterministic(automatonCompleteNotDeterministic);
    EXPECT_TRUE(res.match("aab"));
    EXPECT_TRUE(res.match("aaabbbbbbbbbbbbbbbbb"));
    EXPECT_TRUE(res.match("aaaaaaaaaaaaaaaaa"));
    EXPECT_TRUE(res.match("aa"));
    EXPECT_FALSE(res.match(""));
    EXPECT_FALSE(res.match("hniure"));
}

TEST_F(AutomatonTestFixture, createDeterimisticAutomatonEmpty){
    fa::Automaton res = fa::Automaton::createDeterministic(automatonEmpty);
    EXPECT_TRUE(res.isDeterministic());
}

TEST_F(AutomatonTestFixture, createDeterimisticAutomatonEmpty_match){
    fa::Automaton res = fa::Automaton::createDeterministic(automatonEmpty);
    EXPECT_TRUE(res.isDeterministic());
}

TEST_F(AutomatonTestFixture, createDeterimisticAutomatonInutile){
    fa::Automaton res = fa::Automaton::createDeterministic(automatonInutile);
    EXPECT_TRUE(res.isDeterministic());
}

TEST_F(AutomatonTestFixture, createDeterimisticAutomatonInutile_match){
    fa::Automaton res = fa::Automaton::createDeterministic(automatonInutile);
    EXPECT_FALSE(res.match("aa"));
    EXPECT_TRUE(res.match("aaaaaaaaaaaaa"));
    EXPECT_FALSE(res.match("aaabbbbbbbbbbbbbbbbb"));
    EXPECT_FALSE(res.match("hniure"));
}

TEST_F(AutomatonTestFixture, createDeterimisticAutomatonNotCompleteDEterministic){
    fa::Automaton res = fa::Automaton::createDeterministic(automatonNotCompleteDeterministic);
    EXPECT_TRUE(res.isDeterministic());
}

TEST_F(AutomatonTestFixture, createDeterimisticAutomatonNotCompleteDEterministic_match){
    fa::Automaton res = fa::Automaton::createDeterministic(automatonNotCompleteDeterministic);
    EXPECT_FALSE(res.match("aa"));
    EXPECT_FALSE(res.match("aaaaaaaaaaaaaa"));
    EXPECT_FALSE(res.match("aaaaaaaaaaaaaab"));
    EXPECT_TRUE(res.match("abbbbbbbbbbbbbbbbb"));
    EXPECT_TRUE(res.match("ab"));
    EXPECT_TRUE(res.match("abaaaaaaaaaaaaaaa"));
    EXPECT_FALSE(res.match("hniure"));
}

TEST_F(AutomatonTestFixture, createDeterimisticAutomatonNotCompleteNotDEterministic){
    fa::Automaton res = fa::Automaton::createDeterministic(automatonNotCompleteNotDeterministic);
    EXPECT_TRUE(res.isDeterministic());
}

TEST_F(AutomatonTestFixture, createDeterimisticAutomatonNotCompleteNotDEterministic_match){
    fa::Automaton res = fa::Automaton::createDeterministic(automatonNotCompleteNotDeterministic);
    EXPECT_TRUE(res.match("a"));
    EXPECT_TRUE(res.match("aaaaaaaaaaaaaabaaaaaaa"));
    EXPECT_TRUE(res.match("abb"));
    EXPECT_TRUE(res.match("ab"));
    EXPECT_FALSE(res.match("aaaaaaaaaaaaaaaaaaa"));
    EXPECT_FALSE(res.match("hniure"));
}

//******************************************************
//              isIncludedIn
//******************************************************


//******************************************************
//              createWithoutEpsilon
//******************************************************
/*
TEST(AutomatonTest, createWithoutEpsilonAutomatonEpsilonTwoStateMatch){
    fa::Automaton automatonEpsilonTwoState;
    automatonEpsilonTwoState.addState(0);
    automatonEpsilonTwoState.addState(1);
    automatonEpsilonTwoState.setStateInitial(0);
    automatonEpsilonTwoState.setStateFinal(1);
    automatonEpsilonTwoState.addTransition(0, '\0', 1);
    fa::Automaton res = fa::Automaton::createWithoutEpsilon(automatonEpsilonTwoState);
    EXPECT_TRUE(res.match(""));
}

TEST(AutomatonTest, createWithoutEpsilonAutomatonEpsilonTwoStateCount){
    fa::Automaton automatonEpsilonTwoState;
    automatonEpsilonTwoState.addState(0);
    automatonEpsilonTwoState.addState(1);
    automatonEpsilonTwoState.setStateInitial(0);
    automatonEpsilonTwoState.setStateFinal(1);
    automatonEpsilonTwoState.addTransition(0, '\0', 1);
    fa::Automaton res = fa::Automaton::createWithoutEpsilon(automatonEpsilonTwoState);
    EXPECT_EQ((unsigned) 2, res.countStates());
}

TEST(AutomatonTest, createWithoutEpsilonAutomatonEpsiloBoucleEpsilonMatchn){
    fa::Automaton automatonEpsilon;
    automatonEpsilon.addState(0);
    automatonEpsilon.addState(1);
    automatonEpsilon.addState(2);
    automatonEpsilon.addState(3);
    automatonEpsilon.addState(4);
    automatonEpsilon.addState(5);
    automatonEpsilon.addState(6);
    automatonEpsilon.addState(7);
    automatonEpsilon.addState(8);
    automatonEpsilon.setStateInitial(0);
    automatonEpsilon.setStateInitial(2);
    automatonEpsilon.setStateInitial(8);
    automatonEpsilon.setStateFinal(2);
    automatonEpsilon.setStateFinal(3);
    automatonEpsilon.setStateFinal(7);
    automatonEpsilon.addTransition(0, 'o', 1);
    automatonEpsilon.addTransition(0, 'a', 0);
    automatonEpsilon.addTransition(0, '\0', 1);
    automatonEpsilon.addTransition(0, 'u', 8);
    automatonEpsilon.addTransition(0, (char) 122, 8);
    automatonEpsilon.addTransition(1, '\0', 4);
    automatonEpsilon.addTransition(1, '\0', 5);
    automatonEpsilon.addTransition(3, '7', 1);
    automatonEpsilon.addTransition(8, 'v', 1);
    automatonEpsilon.addTransition(5, '\0', 0);
    automatonEpsilon.addTransition(5, '0', 7);
    automatonEpsilon.addTransition(7, 'j', 2);
    automatonEpsilon.addTransition(3, 'o', 1);
    automatonEpsilon.addTransition(3, 'j', 7);
    DOT_PRINT(automatonEpsilon, std::string("res"), ofstream)
    fa::Automaton res = fa::Automaton::createWithoutEpsilon(automatonEpsilon);
    DOT_PRINT(res, std::string("res123"), ofstream1)

    EXPECT_TRUE(res.match("0j"));
    EXPECT_TRUE(res.match("0"));
    EXPECT_TRUE(res.match(""));
    EXPECT_FALSE(res.match("za"));
    EXPECT_FALSE(res.match("hniure"));s
}

TEST(AutomatonTest, createWithoutEpsilonAutomatonEpsilomatch){
    fa::Automaton automatonEpsilon;
    automatonEpsilon.addState(0);
    automatonEpsilon.addState(1);
    automatonEpsilon.addState(2);
    automatonEpsilon.addState(3);
    automatonEpsilon.addState(4);
    automatonEpsilon.addState(5);
    automatonEpsilon.addState(6);
    automatonEpsilon.addState(7);
    automatonEpsilon.addState(8);
    automatonEpsilon.setStateInitial(0);
    automatonEpsilon.setStateInitial(2);
    automatonEpsilon.setStateInitial(8);
    automatonEpsilon.setStateFinal(2);
    automatonEpsilon.setStateFinal(3);
    automatonEpsilon.setStateFinal(7);
    automatonEpsilon.addTransition(0, 'o', 1);
    automatonEpsilon.addTransition(0, 'a', 0);
    automatonEpsilon.addTransition(0, '\0', 1);
    automatonEpsilon.addTransition(0, 'u', 8);
    automatonEpsilon.addTransition(0, (char) 122, 8);
    automatonEpsilon.addTransition(1, '\0', 4);
    automatonEpsilon.addTransition(1, '\0', 5);
    automatonEpsilon.addTransition(3, '7', 1);
    automatonEpsilon.addTransition(8, 'v', 1);
    automatonEpsilon.addTransition(5, 'P', 0);
    automatonEpsilon.addTransition(5, '0', 7);
    automatonEpsilon.addTransition(7, 'j', 2);
    automatonEpsilon.addTransition(3, 'o', 1);
    automatonEpsilon.addTransition(3, 'j', 7);
    fa::Automaton res = fa::Automaton::createWithoutEpsilon(automatonEpsilon);
    DOT_PRINT(automatonEpsilon, std::string("res"), ofstream)
    DOT_PRINT(res, std::string("res1234"), ofstream1)


    EXPECT_TRUE(res.match("0j"));
    EXPECT_TRUE(res.match("o0"));
    EXPECT_TRUE(res.match("0"));
    EXPECT_TRUE(res.match("PoPuv0"));
    EXPECT_TRUE(res.match("uv0"));
    EXPECT_TRUE(res.match(""));
    EXPECT_FALSE(res.match("za"));
    EXPECT_FALSE(res.match("hniure"));
}




*/


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
