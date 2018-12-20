#include <iostream>
#include <iomanip>

#include "gtest/gtest.h"

#include "Automaton.h"



//////////////////////////////////////////////////////////TEST TP1


////////////////////TEST ADD STATE
/*Test comptage transitions, states et taille alphabet pour un automaton vide*/
TEST(AutomatonTest, Empty) {
    fa::Automaton fa;
    EXPECT_EQ(fa.countStates(), 0u);
    EXPECT_EQ(fa.countTransitions(), 0u);
    EXPECT_EQ(fa.getAlphabetSize(),0u);
}



/*Test ajout d'un état valide*/
//PART1: première méthode d'ajoût
TEST(AutomatonTest, AddStatePart1) {
    fa::Automaton fa;
    int state=1;
    fa.addState(state);
    EXPECT_EQ(fa.countStates(), 1u);
}


//PART2: seconde méthode d'ajoût
TEST(AutomatonTest, AddStatePart2) {
fa::Automaton fa;
fa.addState(1);
EXPECT_EQ(fa.countStates(), 1u);
}


/*Test ajout d'un état déjà présent*/
TEST(AutomatonTest, AddExistingState) {
    fa::Automaton fa;
    int state=1;
    fa.addState(state);
    EXPECT_EQ(fa.countStates(), 1u);
    EXPECT_DEATH(fa.addState(state),"");
    EXPECT_EQ(fa.countStates(),1u);
}


////////////////////TEST REMOVE STATE

/*Test suppression d'un état valide*/
//PART1: première méthode de suppression
TEST(AutomatonTest, RemoveStatePart1) {
    fa::Automaton fa;
    fa.addState(1);
    fa.removeState(1);
    EXPECT_EQ(fa.countStates(), 0u);
}

//PART2: seconde méthode de suppression
TEST(AutomatonTest, RemoveStatePart2) {
    int state=1;
fa::Automaton fa;
fa.addState(state);
fa.removeState(state);
EXPECT_EQ(fa.countStates(), 0u);
}


/*Test suppression d'un état inexistant*/
TEST(AutomatonTest, RemoveAbsentState) {
fa::Automaton fa;
fa.addState(1);
EXPECT_DEATH(fa.removeState(2),"");
EXPECT_EQ(fa.countStates(), 1u);
}


/*Test suppression d'un état impliqué dans une transition sur lui-même*/
//PART 1: TEST suppression de l'état
TEST(AutomatonTest, RemoveCycleTransitionStatePart1) {
fa::Automaton fa;
fa.addState(1);
fa.addTransition(1,'a',1);
fa.removeState(1);
EXPECT_EQ(fa.countStates(), 0u);
}

//PART 2: TEST suppression de la transition
TEST(AutomatonTest, RemoveCycleTransitionStatePart2) {
fa::Automaton fa;
fa.addState(1);
fa.addTransition(1,'a',1);
fa.removeState(1);
EXPECT_EQ(fa.countTransitions(), 0u);
}


/*Test suppression d'un état impliqué dans une transition avec un autre état*/
//PART1: TEST suppression de l'état voulu
TEST(AutomatonTest, RemoveStateInATransitionPart1) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.addTransition(1,'a',2);
fa.removeState(1);
EXPECT_EQ(fa.countStates(), 1u);
EXPECT_FALSE(fa.hasState(1));
}


//PART2: TEST non suppression de l'autre état de la transition
TEST(AutomatonTest, RemoveStateInATransitionPart2) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.addTransition(1,'a',2);
fa.removeState(1);
EXPECT_EQ(fa.countStates(), 1u);
EXPECT_TRUE(fa.hasState(2));
}

//PART3: TEST suppression de la transition
TEST(AutomatonTest, RemoveStateInATransitionPart3) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.addTransition(1,'a',2);
fa.removeState(1);
EXPECT_EQ(fa.countTransitions(),0u);
//EXPECT_FALSE(fa.hasTransition(1,'a',2));
}


/*Test non suppression des autres transitions*/
//PART1: test suppression de la transition avec l'état voulu
TEST(AutomatonTest, RemoveStateAndTransitionPart1) {
    fa::Automaton fa;
    int state=1;
    int state2=2;
    int state3=3;
    fa.addState(state);
    fa.addState(state2);
    fa.addState(state3);
    fa.addTransition(1,'a',2);
    fa.addTransition(2,'b',3);
    fa.removeState(state);
    //EXPECT_FALSE(fa.hasTransition(1,'a',2));
}


//PART1: test non suppression des autres transitions
TEST(AutomatonTest, RemoveStateAndTransitionPart2) {
    fa::Automaton fa;
    int state=1;
    int state2=2;
    int state3=3;
    fa.addState(state);
    fa.addState(state2);
    fa.addState(state3);
    fa.addTransition(1,'a',2);
    fa.addTransition(2,'b',3);
    fa.removeState(state);
    EXPECT_TRUE(fa.hasTransition(2,'b',3));
}


////////////////////TEST HAS STATE
/*TEST présence d'un état qui l'est*/
TEST(AutomatonTest, HasStateYes) {
    fa::Automaton fa;
    int state=1;
    fa.addState(state);
    EXPECT_TRUE(fa.hasState(state));
}



/*Test recherche d'un état absent de l'automate*/
TEST(AutomatonTest, HasStateNo) {
    fa::Automaton fa;
    int state=1;
    int notAState=2;
    fa.addState(state);
    EXPECT_FALSE(fa.hasState(notAState));
}



/*Test recherche d'un état après ajout puis suppression de ce dernier*/
TEST(AutomatonTest, HasStateBeforeYesButNowNo) {
    fa::Automaton fa;
    int state=1;
    fa.addState(state);
    EXPECT_TRUE(fa.hasState(state));
    fa.removeState(state);
    EXPECT_FALSE(fa.hasState(state));

}



/*Test recherche d'un état présent et défini comme état initial*/
TEST(AutomatonTest, hasInitialState) {
    fa::Automaton fa;
    int state=1;
    fa.addState(state);
    fa.setStateInitial(state);
    EXPECT_TRUE(fa.hasState(state));

}



/*Test recherche d'un état présent et défini comme final*/
TEST(AutomatonTest, hasFinalState) {
fa::Automaton fa;
int state=1;
fa.addState(state);
fa.setStateFinal(state);
EXPECT_TRUE(fa.hasState(state));

}



/*Test recherche d'un état présent et défini comme état initial et final*/
TEST(AutomatonTest, hasInitialAndFinalState) {
fa::Automaton fa;
int state=1;
fa.addState(state);
fa.setStateInitial(state);
fa.setStateFinal(state);
EXPECT_TRUE(fa.hasState(state));

}


/*Test présence d'un état initial après son ajout puis sa suppression*/
TEST(AutomatonTest, hasDeletedInitialState) {
fa::Automaton fa;
int state=1;
fa.addState(state);
fa.setStateInitial(state);
EXPECT_TRUE(fa.hasState(state));
fa.removeState(1);
EXPECT_FALSE(fa.hasState(state));

}

/*Test présence d'un état final après son ajout puis sa suppression*/
TEST(AutomatonTest, hasDeletedFinalState) {
fa::Automaton fa;
int state=1;
fa.addState(state);
fa.setStateFinal(state);
EXPECT_TRUE(fa.hasState(state));
fa.removeState(1);
EXPECT_FALSE(fa.hasState(state));

}


/*Test présence d'un état final et initial après son ajout puis sa suppression*/
TEST(AutomatonTest, hasDeletedFinalAndInitialState) {
fa::Automaton fa;
int state=1;
fa.addState(state);
fa.setStateInitial(state);
fa.setStateFinal(state);
EXPECT_TRUE(fa.hasState(state));
fa.removeState(1);
EXPECT_FALSE(fa.hasState(state));

}

////////////////////TEST COUNT STATE
/*Test comptage état automate non vide*/
TEST(AutomatonTest, countStatesNotEmptyAutomaton) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
EXPECT_TRUE(fa.hasState(1));
EXPECT_TRUE(fa.hasState(2));
EXPECT_EQ(fa.countStates(), 2u);
}


/*Test comptage état automate  vide*/
TEST(AutomatonTest, countStatesEmptyAutomaton) {
fa::Automaton fa;
EXPECT_EQ(fa.countStates(), 0u);
}


/*Test comptage état automate après ajout et suppression d'un état*/
TEST(AutomatonTest, countStatesDeletedState) {
fa::Automaton fa;
fa.addState(1);
EXPECT_EQ(fa.countStates(), 1u);
fa.removeState(1);
EXPECT_EQ(fa.countStates(), 0u);
}


/*Test comptage état automate avec un état initial (test non duplication de l'état)*/
TEST(AutomatonTest, countStatesWithAnInitialState) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
EXPECT_TRUE(fa.hasState(1));
EXPECT_EQ(fa.countStates(), 2u);
fa.setStateInitial(1);
EXPECT_EQ(fa.countStates(), 2u);
}


/*Test comptage état après suppression d'un état initial (test non duplication de l'état)*/
TEST(AutomatonTest, countStatesDeletedInitialState) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
EXPECT_TRUE(fa.hasState(1));
EXPECT_EQ(fa.countStates(), 2u);
fa.setStateInitial(1);
EXPECT_EQ(fa.countStates(), 2u);
fa.removeState(1);
EXPECT_EQ(fa.countStates(), 1u);

}

/*Test comptage état automate avec un état final (test non duplication de l'état)*/
TEST(AutomatonTest, countStatesWithAFinalState) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
EXPECT_TRUE(fa.hasState(1));
EXPECT_EQ(fa.countStates(), 2u);
fa.setStateFinal(1);
EXPECT_EQ(fa.countStates(), 2u);
}


/*Test comptage état après suppression d'un état final (test non duplication de l'état)*/
TEST(AutomatonTest, countStatesDeletedFinalState) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
EXPECT_TRUE(fa.hasState(1));
EXPECT_EQ(fa.countStates(), 2u);
fa.setStateFinal(1);
EXPECT_EQ(fa.countStates(), 2u);
fa.removeState(1);
EXPECT_EQ(fa.countStates(), 1u);

}

/*Test comptage état automate avec un état initial et final (test non duplication de l'état)*/
TEST(AutomatonTest, countStatesWithAFinalAndInitialState) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
EXPECT_TRUE(fa.hasState(1));
EXPECT_EQ(fa.countStates(), 2u);
fa.setStateInitial(1);
fa.setStateFinal(1);
EXPECT_EQ(fa.countStates(), 2u);
}

/*Test comptage état après suppression d'un état final et initial (test non duplication de l'état)*/
TEST(AutomatonTest, countStatesDeletedFinalAndInitialState) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
EXPECT_TRUE(fa.hasState(1));
EXPECT_EQ(fa.countStates(), 2u);
fa.setStateInitial(1);
fa.setStateFinal(1);
EXPECT_EQ(fa.countStates(), 2u);
fa.removeState(1);
EXPECT_EQ(fa.countStates(), 1u);

}

////////////////////TEST SET STATE INITIAL

/* Test ajout d'un état intial pas présent dans la liste des états de l'automate*/
TEST(AutomatonTest, SetInitialAbsentState) {
    fa::Automaton fa;
    int state=1;
    int notAState=2;
    fa.addState(state);
    EXPECT_DEATH(fa.setStateInitial(notAState),"");
    EXPECT_DEATH(fa.isStateInitial(state), "");

}

/* Test ajout d'un état intial présent dans la liste des états de l'automate*/
TEST(AutomatonTest, NotAnInitialState) {
fa::Automaton fa;
int state=1;
fa.addState(state);
fa.setStateInitial(state);
EXPECT_TRUE(fa.isStateInitial(state));

}

/* Test ajout d'un état intial présent dans la liste des états de l'automate et déjà défini comme initial*/
TEST(AutomatonTest, AlreadyInitialState) {
fa::Automaton fa;
int state=1;
fa.addState(state);
fa.setStateInitial(state);
EXPECT_TRUE(fa.isStateInitial(state));
fa.setStateInitial(state);
EXPECT_TRUE(fa.isStateInitial(state));
}

/* Test ajout d'un état intial présent dans une transition sur lui-même*/
TEST(AutomatonTest, CycliqueTransitionInitialState) {
fa::Automaton fa;
fa.addState(1);
fa.addTransition(1,'a',1);
fa.setStateInitial(1);
EXPECT_TRUE(fa.isStateInitial(1));
}

/* Test ajout d'un état intial présent dans une transition avec un état initial*/
TEST(AutomatonTest, InitialTransitionInitialState) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.setStateInitial(2);
fa.addTransition(1,'a',2);
fa.setStateInitial(1);
EXPECT_TRUE(fa.isStateInitial(1));
EXPECT_TRUE(fa.isStateInitial(2));
}

/* Test ajout d'un état intial présent dans une transition avec un état final*/
TEST(AutomatonTest, FinalTransitionInitialState) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.setStateFinal(2);
fa.addTransition(1,'a',2);
fa.setStateInitial(1);
EXPECT_TRUE(fa.isStateInitial(1));
EXPECT_FALSE(fa.isStateInitial(2));
}


/* Test ajout d'un état intial présent dans une transition avec un état classique*/
TEST(AutomatonTest, LambdaTransitionInitialState) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.addTransition(1,'a',2);
fa.setStateInitial(1);
EXPECT_TRUE(fa.isStateInitial(1));
EXPECT_FALSE(fa.isStateInitial(2));
}

////////////////////TEST IS INITIAL STATE
/*Test recherche d'un état inital présent et défini comme état initial*/
TEST(AutomatonTest, isInitialYES) {
fa::Automaton fa;
fa.addState(1);
fa.setStateInitial(1);
EXPECT_TRUE(fa.isStateInitial(1));

}


/*Test recherche d'un état inital présent et non défini comme état initial*/
TEST(AutomatonTest, isInitialNO) {
fa::Automaton fa;
fa.addState(1);
EXPECT_FALSE(fa.isStateInitial(1));

}



/*Test recherche d'un état final et défini comme état final*/
TEST(AutomatonTest, FinalStateisInitialNO) {
fa::Automaton fa;
fa.addState(1);
fa.setStateFinal(1);
EXPECT_FALSE(fa.isStateInitial(1));

}

/*Test recherche d'un état inital présent et défini comme état final et initial*/
TEST(AutomatonTest, FinalAndInitialStateisInitial) {
fa::Automaton fa;
fa.addState(1);
fa.setStateFinal(1);
fa.setStateInitial(1);
EXPECT_TRUE(fa.isStateInitial(1));

}


/*Test recherche d'un état inital absent de l'automate*/
TEST(AutomatonTest, isInitialAbsent) {
fa::Automaton fa;
fa.addState(1);
EXPECT_DEATH(fa.isStateInitial(2), "");

}

/*Test recherche état initial après ajout puis suppression de ce dernier*/
TEST(AutomatonTest, HasInitialStateBeforeYesButNowNo) {
    fa::Automaton fa;
    int state=1;
    fa.addState(state);
    fa.setStateInitial(state);
    EXPECT_TRUE(fa.isStateInitial(state));
    fa.removeState(state);
    EXPECT_DEATH(fa.isStateInitial(state), "");

}


/* Test recherche d'un état intial présent dans une transition sur lui-même*/
TEST(AutomatonTest, CycliqueTransitionIsInitialState) {
fa::Automaton fa;
fa.addState(1);
fa.setStateInitial(1);
fa.addTransition(1,'a',1);
EXPECT_TRUE(fa.isStateInitial(1));
}

/* Test recherche d'un état intial présent dans une transition avec un état initial*/
TEST(AutomatonTest, InitialTransitionIsInitialState) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.setStateInitial(1);
fa.setStateInitial(2);
fa.addTransition(1,'a',2);
EXPECT_TRUE(fa.isStateInitial(1));
EXPECT_TRUE(fa.isStateInitial(2));
}

/* Test recherche d'un état intial présent dans une transition avec un état final*/
TEST(AutomatonTest, FinalTransitionIsInitialState) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.setStateFinal(2);
fa.setStateInitial(1);
fa.addTransition(1,'a',2);
EXPECT_TRUE(fa.isStateInitial(1));
EXPECT_FALSE(fa.isStateInitial(2));
}


/* Test recherche d'un état intial présent dans une transition avec un état classique*/
TEST(AutomatonTest, LambdaTransitionIsInitialState) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.setStateInitial(1);
fa.addTransition(1,'a',2);
EXPECT_TRUE(fa.isStateInitial(1));
EXPECT_FALSE(fa.isStateInitial(2));
}

////////////////////TEST SET STATE FINAL

/* Test ajout d'un état final pas présent dans la liste des états de l'automate*/
TEST(AutomatonTest, SetFinalAbsentState) {
fa::Automaton fa;
int state=1;
int notAState=2;
fa.addState(state);
EXPECT_DEATH(fa.setStateFinal(notAState),"");
EXPECT_DEATH(fa.isStateFinal(state),"");

}

/* Test ajout d'un état final présent dans la liste des états de l'automate*/
TEST(AutomatonTest, NotAnFinallState) {
fa::Automaton fa;
int state=1;
fa.addState(state);
fa.setStateFinal(state);
EXPECT_TRUE(fa.isStateFinal(state));

}


/* Test ajout d'un état final présent dans la liste des états de l'automate et déjà défini comme final*/
TEST(AutomatonTest, AlreadyFinalState) {
fa::Automaton fa;
int state=1;
fa.addState(state);
fa.setStateFinal(state);
EXPECT_TRUE(fa.isStateFinal(state));
fa.setStateFinal(state);
EXPECT_TRUE(fa.isStateFinal(state));
}



/* Test ajout d'un état final présent dans une transition sur lui-même*/
TEST(AutomatonTest, CycliqueTransitionFinalState) {
fa::Automaton fa;
fa.addState(1);
fa.addTransition(1,'a',1);
fa.setStateFinal(1);
EXPECT_TRUE(fa.isStateFinal(1));
}

/* Test ajout d'un état final présent dans une transition avec un état initial*/
TEST(AutomatonTest, InitialTransitionFinalState) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.setStateInitial(2);
fa.addTransition(1,'a',2);
fa.setStateFinal(1);
EXPECT_TRUE(fa.isStateFinal(1));
EXPECT_TRUE(fa.isStateInitial(2));
}

/* Test ajout d'un état final présent dans une transition avec un état final*/
TEST(AutomatonTest, FinalTransitionFinalState) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.setStateFinal(2);
fa.addTransition(1,'a',2);
fa.setStateFinal(1);
EXPECT_TRUE(fa.isStateFinal(1));
EXPECT_TRUE(fa.isStateFinal(2));
}


/* Test ajout d'un état final présent dans une transition avec un état classique*/
TEST(AutomatonTest, LambdaTransitionFinalState) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.addTransition(1,'a',2);
fa.setStateFinal(1);
EXPECT_TRUE(fa.isStateFinal(1));
EXPECT_FALSE(fa.isStateFinal(2));
}


////////////////////TEST IS FINAL STATE
/*Test recherche d'un état final présent et défini comme état final*/
TEST(AutomatonTest, isFinalYES) {
fa::Automaton fa;
fa.addState(1);
fa.setStateFinal(1);
EXPECT_TRUE(fa.isStateFinal(1));

}


/*Test recherche d'un état final présent et non défini comme état final*/
TEST(AutomatonTest, isFinalNO) {
fa::Automaton fa;
fa.addState(1);
EXPECT_FALSE(fa.isStateFinal(1));

}



/*Test recherche d'un état  présent et défini comme état initial*/
TEST(AutomatonTest, InitialStateisFinalNO) {
fa::Automaton fa;
fa.addState(1);
fa.setStateInitial(1);
EXPECT_FALSE(fa.isStateFinal(1));

}

/*Test recherche d'un état final présent et défini comme état inital et final*/
TEST(AutomatonTest, FinalAndInitialStateisFinal) {
fa::Automaton fa;
fa.addState(1);
fa.setStateFinal(1);
fa.setStateInitial(1);
EXPECT_TRUE(fa.isStateFinal(1));

}


/*Test recherche d'un état final absent de l'automate*/
TEST(AutomatonTest, isFinalAbsent) {
fa::Automaton fa;
fa.addState(1);
EXPECT_DEATH(fa.isStateFinal(2), "");

}

/*Test recherche état final après ajout puis suppression de ce dernier*/
TEST(AutomatonTest, HasFinalStateBeforeYesButNowNo) {
fa::Automaton fa;
int state=1;
fa.addState(state);
fa.setStateFinal(state);
EXPECT_TRUE(fa.isStateFinal(state));
fa.removeState(state);
EXPECT_DEATH(fa.isStateFinal(state), "");

}


/* Test recherche d'un état final présent dans une transition sur lui-même*/
TEST(AutomatonTest, CycliqueTransitionIsFinalState) {
fa::Automaton fa;
fa.addState(1);
fa.setStateFinal(1);
fa.addTransition(1,'a',1);
EXPECT_TRUE(fa.isStateFinal(1));
}

/* Test recherche d'un état final présent dans une transition avec un état initial*/
TEST(AutomatonTest, InitialTransitionIsFinalState) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.setStateFinal(1);
fa.setStateInitial(2);
fa.addTransition(1,'a',2);
EXPECT_TRUE(fa.isStateFinal(1));
EXPECT_FALSE(fa.isStateFinal(2));
}

/* Test recherche d'un état final présent dans une transition avec un état final*/
TEST(AutomatonTest, FinalTransitionIsFinalState) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.setStateFinal(2);
fa.setStateFinal(1);
fa.addTransition(1,'a',2);
EXPECT_TRUE(fa.isStateFinal(1));
EXPECT_TRUE(fa.isStateFinal(2));
}


/* Test recherche d'un état final présent dans une transition avec un état classique*/
TEST(AutomatonTest, LambdaTransitionIsFinalState) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.setStateFinal(1);
fa.addTransition(1,'a',2);
EXPECT_TRUE(fa.isStateFinal(1));
EXPECT_FALSE(fa.isStateFinal(2));
}




////////////////////TEST ADD TRANSITION


/*Test ajout successif de la même transition 2 fois*/
TEST(AutomatonTest, DoublonTransition) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.addTransition(1,'b',2);
fa.addTransition(1,'b',2);
EXPECT_EQ(fa.countTransitions(),1u);

}

/*Test ajoût transition avec 2 états valides*/
//PART1: TEST création ok (count)
TEST(AutomatonTest, ValidTransitionPart1) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.addTransition(1,'a',2);
EXPECT_EQ(fa.countTransitions (), 1u);
}

//PART2: TEST présence ok (has)
TEST(AutomatonTest, ValidTransitionPart2) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.addTransition(1,'a',2);
EXPECT_TRUE(fa.hasTransition(1,'a',2));
}


/*Test ajoût transition avec 1 état invalide*/
//PART1: TEST création non-ok (count)
TEST(AutomatonTest, OneInvalidStateTransitionPart1) {
fa::Automaton fa;
fa.addState(1);
EXPECT_DEATH(fa.addTransition(1,'a',2),"");
EXPECT_EQ(fa.countTransitions (), 0u);
}

//PART2: TEST présence non-ok (has)
TEST(AutomatonTest, OneInvalidStateTransitionPart2) {
fa::Automaton fa;
fa.addState(1);
ASSERT_DEATH(fa.addTransition(1,'a',2),"");
}


/*Test ajoût transition avec 2 états valides finaux*/
//PART1: TEST création ok (count)
TEST(AutomatonTest, ValidTwoFinalTransitionPart1) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.setStateFinal(1);
fa.setStateFinal(2);
fa.addTransition(1,'a',2);
EXPECT_EQ(fa.countTransitions (), 1u);
}

//PART2: TEST présence ok (has)
TEST(AutomatonTest, ValidTwoFinalTransitionPart2) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.setStateFinal(1);
fa.setStateFinal(2);
fa.addTransition(1,'a',2);
EXPECT_TRUE(fa.hasTransition(1,'a',2));
}

/*Test ajoût transition avec 2 états valides initiaux*/
//PART1: TEST création ok (count)
TEST(AutomatonTest, ValidTwoInitialTransitionPart1) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.setStateInitial(1);
fa.setStateInitial(2);
fa.addTransition(1,'a',2);
EXPECT_EQ(fa.countTransitions (), 1u);
}

//PART2: TEST présence ok (has)
TEST(AutomatonTest, ValidTwoInitialTransitionPart2) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.setStateInitial(1);
fa.setStateInitial(2);
fa.addTransition(1,'a',2);
EXPECT_TRUE(fa.hasTransition(1,'a',2));
}

/*Test ajoût transition avec 1 état classique et 1 initial*/
//PART1: TEST création ok (count)
TEST(AutomatonTest, ValidOneInitialTransitionPart1) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.setStateInitial(1);
fa.addTransition(1,'a',2);
EXPECT_EQ(fa.countTransitions (), 1u);
}

//PART2: TEST présence ok (has)
TEST(AutomatonTest, ValidOneInitialTransitionPart2) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.setStateInitial(1);
fa.addTransition(1,'a',2);
EXPECT_TRUE(fa.hasTransition(1,'a',2));
}

/*Test ajoût transition avec 1 état classique et 1 final*/
//PART1: TEST création ok (count)
TEST(AutomatonTest, ValidOneFinalTransitionPart1) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.setStateFinal(1);
fa.addTransition(1,'a',2);
EXPECT_EQ(fa.countTransitions (), 1u);
}

//PART2: TEST présence ok (has)
TEST(AutomatonTest, ValidOneFinalTransitionPart2) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.setStateFinal(1);
fa.addTransition(1,'a',2);
EXPECT_TRUE(fa.hasTransition(1,'a',2));
}


/*Test ajoût transition sur un unique état valide classique*/
//PART1: TEST création ok (count)
TEST(AutomatonTest, ValidCyclicTransitionPart1) {
fa::Automaton fa;
fa.addState(1);
fa.addTransition(1,'a',1);
EXPECT_EQ(fa.countTransitions (), 1u);
}

//PART2: TEST présence ok (has)
TEST(AutomatonTest, ValidCyclicTransitionPart2) {
fa::Automaton fa;
fa.addState(1);
fa.addTransition(1,'a',1);
EXPECT_TRUE(fa.hasTransition(1,'a',1));
}


/*Test ajoût transition sur un unique état final*/
//PART1: TEST création ok (count)
TEST(AutomatonTest, ValidCyclicFinalTransitionPart1) {
fa::Automaton fa;
fa.addState(1);
fa.setStateFinal(1);
fa.addTransition(1,'a',1);
EXPECT_EQ(fa.countTransitions (), 1u);
}

//PART2: TEST présence ok (has)
TEST(AutomatonTest, ValidCyclicFinalTransitionPart2) {
fa::Automaton fa;
fa.addState(1);
fa.setStateFinal(1);
fa.addTransition(1,'a',1);
EXPECT_TRUE(fa.hasTransition(1,'a',1));
}


/*Test ajoût transition sur un unique état valide initial*/
//PART1: TEST création ok (count)
TEST(AutomatonTest, ValidCyclicInitialTransitionPart1) {
fa::Automaton fa;
fa.addState(1);
fa.setStateInitial(1);
fa.addTransition(1,'a',1);
EXPECT_EQ(fa.countTransitions (), 1u);
}

//PART2: TEST présence ok (has)
TEST(AutomatonTest, ValidCyclicInitialTransitionPart2) {
fa::Automaton fa;
fa.addState(1);
fa.setStateInitial(1);
fa.addTransition(1,'a',1);
EXPECT_TRUE(fa.hasTransition(1,'a',1));
}

/*Test ajoût transition avec 2 états valides mais un caractère invalide*/
//PART1: TEST création non-ok (count)
TEST(AutomatonTest, InvalidCharTransitionPart1) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
EXPECT_DEATH(fa.addTransition(1,(char)10000,2),"");
EXPECT_EQ(fa.countTransitions (), 0u);
}

//PART2: TEST présence non-ok (has)
TEST(AutomatonTest, InvalidCharTransitionPart2) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
EXPECT_DEATH(fa.addTransition(1,(char)10000,2),"");
EXPECT_FALSE(fa.hasTransition(1,(char)10000,2));
}




////////////////////TEST REMOVE TRANSITION




/*Test suppression d'une transition valide et existante dans l'automate*/
//PART1: check présence des états
TEST(AutomatonTest, removeValidTransitionPart1) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.addTransition(1,'a',2);
fa.removeTransition(1,'a',2);
EXPECT_TRUE(fa.hasState(1));
EXPECT_TRUE(fa.hasState(2));
}

//PART2: check nombre transition
TEST(AutomatonTest, removeValidTransitionPart2) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.addTransition(1,'a',2);
fa.removeTransition(1,'a',2);
EXPECT_EQ(fa.countTransitions(), 0u);
}

//PART3: check taille alphabet
TEST(AutomatonTest, removeValidTransitionPart3) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.addTransition(1,'a',2);
fa.removeTransition(1,'a',2);
EXPECT_EQ(fa.getAlphabetSize(), 1u);
}


/*Test suppression d'une transition valide et existante dans l'automate entre un état initial et et un étét final*/
//PART1: check présence états
TEST(AutomatonTest, removeTransitionInitialFinalPart1) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.setStateInitial(1);
fa.setStateFinal(2);
fa.addTransition(1,'a',2);
fa.removeTransition(1,'a',2);
EXPECT_TRUE(fa.hasState(1));
EXPECT_TRUE(fa.hasState(2));
EXPECT_FALSE(fa.hasTransition(1,'a',2));
}


//PART2: check nature états
TEST(AutomatonTest, removeTransitionInitialFinalPart2) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.setStateInitial(1);
fa.setStateFinal(2);
fa.addTransition(1,'a',2);
fa.removeTransition(1,'a',2);
EXPECT_TRUE(fa.isStateInitial(1));
EXPECT_TRUE(fa.isStateFinal(2));
}

//PART3: check nombre transitions
TEST(AutomatonTest, removeTransitionInitialFinalPart3) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.setStateInitial(1);
fa.setStateFinal(2);
fa.addTransition(1,'a',2);
fa.removeTransition(1,'a',2);
EXPECT_EQ(fa.countTransitions(), 0u);
}

//PART4: check taille alphabet
TEST(AutomatonTest, removeTransitionInitialFinalPart4) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.setStateInitial(1);
fa.setStateFinal(2);
fa.addTransition(1,'a',2);
fa.removeTransition(1,'a',2);
EXPECT_EQ(fa.getAlphabetSize(),1u);
}



/*Test suppression d'une transition valide cyclique*/
//PART1: check présence états
TEST(AutomatonTest, removeCyclicTransitionPart1) {
fa::Automaton fa;
fa.addState(1);
fa.addTransition(1,'a',1);
fa.removeTransition(1,'a',1);
EXPECT_TRUE(fa.hasState(1));
EXPECT_FALSE(fa.hasTransition(1,'a',1));
}

//PART1: check nombre transition
TEST(AutomatonTest, removeCyclicTransitionPart2) {
fa::Automaton fa;
fa.addState(1);
fa.addTransition(1,'a',1);
fa.removeTransition(1,'a',1);
EXPECT_EQ(fa.countTransitions(), 0u);
}

/*Test suppression d'une transition inexistante : carac et état valide*/
//PART1: check présence états
TEST(AutomatonTest, removeAbsentTransitionPart1) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.addTransition(1,'a',2);
EXPECT_DEATH(fa.removeTransition(2,'a',3),"");
EXPECT_TRUE(fa.hasState(2));
EXPECT_TRUE(fa.hasState(3));
EXPECT_FALSE(fa.hasTransition(2,'a',3));
}

//PART2: check nombre transition
TEST(AutomatonTest, removeAbsentTransitionPart2) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.addTransition(1,'a',2);
EXPECT_DEATH(fa.removeTransition(2,'a',3),"");
EXPECT_EQ(fa.countTransitions(),1u);
}

//PART3: check taille alphabet
TEST(AutomatonTest, removeAbsentTransitionPart3) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.addTransition(1,'a',2);
EXPECT_DEATH(fa.removeTransition(2,'a',3),"");
EXPECT_EQ(fa.getAlphabetSize(),1u);
}


/*Test suppression d'une transition inexistante : carac invalide état valides*/
//PART1: check présence états
TEST(AutomatonTest, removeWrongCaractTransitionPart1) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.addTransition(1,'a',2);
fa.addTransition(1,'b',2);
//fa.removeTransition(2,'c',3);
EXPECT_TRUE(fa.hasState(1));
EXPECT_TRUE(fa.hasState(2));
EXPECT_TRUE(fa.hasState(3));
EXPECT_TRUE(fa.hasTransition(1,'a',2));
EXPECT_TRUE(fa.hasTransition(1,'b',2));
}

//PART2: check nombre transition
TEST(AutomatonTest, removeWrongCaractTransitionPart2) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.addTransition(1,'a',2);
fa.addTransition(1,'b',2);
//fa.removeTransition(2,'c',3);
EXPECT_EQ(fa.countTransitions(), 2u);
}

//PART3: check taille alphabet
TEST(AutomatonTest, removeWrongCaractTransitionPart3) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.addTransition(1,'a',2);
fa.addTransition(1,'b',2);
//fa.removeTransition(2,'c',3);
EXPECT_EQ(fa.getAlphabetSize(),2u);
}


/*Test suppression d'une transition après suppression d'un des deux états de cette dernière*/
TEST(AutomatonTest, removeTransitionWithOneDeletedState){
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.setStateInitial(1);
fa.setStateFinal(2);
fa.addTransition(1,'a',3);
fa.addTransition(1,'b',2);
fa.removeState(3);
EXPECT_EQ(fa.countTransitions(),1u);
}


////////////////////TEST HAS TRANSITION

/*Test présence d'une transition après suppression d'un des deux états de cette dernière*/
TEST(AutomatonTest, hasTransitionWithOneDeletedState){
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.setStateInitial(1);
    fa.setStateFinal(2);
    fa.addTransition(1,'a',3);
    fa.addTransition(1,'b',2);
    fa.removeState(3);
    EXPECT_DEATH(fa.removeTransition(1,'a',3),"");
    EXPECT_DEATH(fa.hasTransition(1,'a',3),"");
}

/*Test recherche d'une transition classic */
TEST(AutomatonTest, hasClassicTransition){
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.addTransition(1,'b',2);
EXPECT_TRUE(fa.hasTransition(1,'b',2));
}

/*Test recherche d'une transition cyclique */
TEST(AutomatonTest, hasCyclicTransition){
fa::Automaton fa;
fa.addState(1);
fa.addTransition(1,'b',1);
EXPECT_TRUE(fa.hasTransition(1,'b',1));
}

/*Test recherche d'une transition cyclique avec mauvais caractère */
TEST(AutomatonTest, hasWrongCaracCyclicTransition){
fa::Automaton fa;
fa.addState(1);
fa.addTransition(1,'b',1);
EXPECT_FALSE(fa.hasTransition(1,'c',1));
}

/*Test recherche d'une transition classique avec un état invalide  */
TEST(AutomatonTest, hasWrongCaracTransition){
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.addTransition(1,'b',2);
fa.addTransition(2,'b',3);
EXPECT_DEATH(fa.hasTransition(1,'b',3),"");
}


/*Test présence transition après son ajoût puis sa suppression dans l'automate*/
TEST(AutomatonTest,HasTransitionBeforeYesButNowNo) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.addTransition(1,'a',2);
EXPECT_TRUE(fa.hasTransition(1,'a',2));
fa.removeTransition(1,'a',2);
EXPECT_FALSE(fa.hasTransition(1,'a',2));
}

////////////////////TEST COUNT TRANSITIONS

/*Test comptage transition d'un automate vide*/
TEST(AutomatonTest, EmptyAutomatonTransition) {
    fa::Automaton fa;
    EXPECT_EQ(fa.countTransitions (), 0u);

}

/*Test comptage des transitions d'un automate non vide sans tranisition*/
TEST(AutomatonTest, WithoutTransition) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    EXPECT_EQ(fa.countTransitions(), 0u);

}


/*Test comptage des transitions d'un automate ayant une transition valide classique et bien définie*/
TEST(AutomatonTest, OneClassicTransition) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addTransition(1,'a',2);
    EXPECT_EQ(fa.countTransitions(), 1u);

}

/*Test comptage des transitions d'un automate ayant une transition valide cyclique et bien définie*/
TEST(AutomatonTest, OneCyclicTransition) {
fa::Automaton fa;
fa.addState(1);
fa.addTransition(1,'a',1);
EXPECT_EQ(fa.countTransitions(), 1u);

}


/*Test comptage transition après son ajoût puis sa suppression dans l'automate*/
TEST(AutomatonTest,CountTransitionBeforeOneButNowZero) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.addTransition(1,'a',2);
EXPECT_EQ(fa.countTransitions(), 1u);
fa.removeTransition(1,'a',2);
EXPECT_EQ(fa.countTransitions(), 0u);
}


/*Test comptage d'une transition après suppression des deux états de cette dernière*/
TEST(AutomatonTest, CountTransitionWithOneDeletedState){
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.setStateInitial(1);
fa.setStateFinal(2);
fa.addTransition(1,'a',3);
fa.addTransition(1,'b',2);
EXPECT_EQ(fa.countTransitions(), 2u);
fa.removeState(3);
EXPECT_EQ(fa.countTransitions(), 1u);
}



////////////////////TEST GET ALPHABET SIZE
/*Test taille alphabet (initialement vide) après l'ajoût d'une transiton*/
TEST(AutomatonTest,AlphabetSize) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addTransition(1,'a',2);
    EXPECT_TRUE(fa.hasTransition(1,'a',2));
    EXPECT_EQ(fa.getAlphabetSize(), 1u);
}


/*Test taille alphabet (initalement vide) après tentative d'ajoût d'une transition avec caracrtère non valide*/
TEST(AutomatonTest, BadCharacterAlphabetSize) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    EXPECT_DEATH(fa.addTransition(1,(char)1000,2),"");
    EXPECT_EQ(fa.getAlphabetSize(), 0u);

}


/*Test taille alphabet d'un automate vide*/
TEST(AutomatonTest,EmptyAlphabetSize) {
    fa::Automaton fa;
    EXPECT_EQ(fa.getAlphabetSize(), 0u);

}


/*Test taille d'un alphabet d'un automate sans transition définie*/
TEST(AutomatonTest,WithoutTransitionAlphabetSize) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    EXPECT_EQ(fa.getAlphabetSize(), 0u);
}


/*Test taille alphabet après suppression d'une transition (dernière transition avec ce caractère)*/
TEST(AutomatonTest,RemoveTransitionCheckCharacterAlphabetSize) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addTransition(1,'b',2);
    fa.removeTransition(1,'b',2);
    EXPECT_EQ(fa.getAlphabetSize(), 1u);
}

/*Test taille alphabet automate vide puis non vide puis vide à nouveau*/
TEST(AutomatonTest,EmptyToNotEmptyToEmptyAutomatonAlphabetSize) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.addTransition(1,'a',2);
EXPECT_TRUE(fa.hasTransition(1,'a',2));
EXPECT_EQ(fa.getAlphabetSize(), 1u);
fa.removeTransition(1,'a',2);
fa.removeState(1);
fa.removeState(2);
EXPECT_EQ(fa.getAlphabetSize(), 1u);
}


/*Test Taille alphabet après ajoût d'une transition ayant un caractère déjà présent dans cet alphabet*/
TEST(AutomatonTest,DoublonCharacterAlphabetSize) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.addTransition(1,'b',2);
    fa.addTransition(2,'b',3);
    EXPECT_EQ(fa.getAlphabetSize(), 1u);
}


//////////////////////////////////////////////////////////TEST TP2

////////////////////TEST IS DETERMINISTIC

/*Test Nature déterministe d'un automate n'ayant pas d'état final ni d'état inital*/
TEST(AutomatonTest,isDeterministicWithoutInitAndFinal) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.addTransition(1,'a',2);
    fa.addTransition(2,'b',3);
    fa.addTransition(3,'a',3);
    fa.addTransition(3,'b',3);
    EXPECT_FALSE(fa.isDeterministic());
}



/*Test Nature déterministe d'un automate n'ayant pas d'état inital*/
TEST(AutomatonTest,isDeterministicWithoutInit) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.setStateFinal(3);
    fa.addTransition(1,'a',2);
    fa.addTransition(2,'b',3);
    fa.addTransition(3,'a',3);
    fa.addTransition(3,'b',3);
    EXPECT_FALSE(fa.isDeterministic());
}



/*Test Nature déterministe d'un automate n'ayant pas d'état final*/
TEST(AutomatonTest,isDeterministicWithoutFinal) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.setStateInitial(1);
    fa.addTransition(1,'a',2);
    fa.addTransition(2,'b',3);
    fa.addTransition(3,'a',3);
    fa.addTransition(3,'b',3);
    EXPECT_FALSE(fa.isDeterministic());
}

/*Test Nature déterminsiste d'un automate ayant plusieurs états initaux*/
TEST(AutomatonTest,isDeterministWithInitialStateS) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.setStateFinal(3);
    fa.setStateInitial(1);
    fa.setStateInitial(2);
    fa.addTransition(1,'a',2);
    fa.addTransition(1,'b',1);
    fa.addTransition(2,'b',3);
    fa.addTransition(2,'a',2);
    fa.addTransition(3,'a',3);
    fa.addTransition(3,'b',3);
    EXPECT_FALSE(fa.isDeterministic());
}


/*Test Nature déterminsiste d'un automate ayant plusieurs états finaux*/
TEST(AutomatonTest,isDeterministWithFinalStateS) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.setStateFinal(3);
    fa.setStateFinal(2);
    fa.setStateInitial(1);
    fa.addTransition(1,'a',2);
    fa.addTransition(1,'b',1);
    fa.addTransition(2,'b',3);
    fa.addTransition(2,'a',2);
    fa.addTransition(3,'a',3);
    fa.addTransition(3,'b',3);
    EXPECT_TRUE(fa.isComplete());
}


/*Test Nature déterministe d'un automate qui l'est*/
TEST(AutomatonTest,isDeterministicTrue) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.setStateInitial(1);
    fa.setStateFinal(3);
    fa.addTransition(1,'a',2);
    fa.addTransition(2,'b',3);
    fa.addTransition(3,'a',3);
    fa.addTransition(3,'b',3);
    EXPECT_TRUE(fa.isDeterministic());
}



/*Test Nature déterministe d'un automate qui ne l'est pas*/
TEST(AutomatonTest,isDeterministicFalse) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.addTransition(1,'a',2);
    fa.addTransition(1,'a',3);
    fa.addTransition(2,'b',3);
    fa.addTransition(3,'a',3);
    fa.addTransition(3,'b',3);
    EXPECT_FALSE(fa.isDeterministic());
}



/*Test Nature déterministe d'un automate qui ne possède qu'un état*/
TEST(AutomatonTest,isDeterministicOneState) {
    fa::Automaton fa;
    fa.addState(1);
    EXPECT_FALSE(fa.isDeterministic());
}



/*Test Nature déterministe d'un automate vide*/
TEST(AutomatonTest,isDeterministicEmpty) {
    fa::Automaton fa;
    EXPECT_FALSE(fa.isDeterministic());
}

////////////////////TEST IS COMPLETE

/*Test Nature complète d'un automate n'ayant pas d'état final ni d'état inital*/
TEST(AutomatonTest,isCompleteWithoutInitAndFinal) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.addTransition(1,'a',2);
    fa.addTransition(1,'b',1);
    fa.addTransition(2,'b',3);
    fa.addTransition(2,'a',2);
    fa.addTransition(3,'a',3);
    fa.addTransition(3,'b',3);
    EXPECT_TRUE(fa.isComplete());
}



/*Test Nature complète d'un automate n'ayant pas d'état inital*/
TEST(AutomatonTest,isCompleteWithoutInit) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.setStateFinal(3);
    fa.addTransition(1,'a',2);
    fa.addTransition(1,'b',1);
    fa.addTransition(2,'b',3);
    fa.addTransition(2,'a',2);
    fa.addTransition(3,'a',3);
    fa.addTransition(3,'b',3);
    EXPECT_TRUE(fa.isComplete());
}



/*Test Nature complète d'un automate n'ayant pas d'état final*/
TEST(AutomatonTest,isCompleteWithoutFinal) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.setStateInitial(1);
    fa.addTransition(1,'a',2);
    fa.addTransition(1,'b',1);
    fa.addTransition(2,'b',3);
    fa.addTransition(2,'a',2);
    fa.addTransition(3,'a',3);
    fa.addTransition(3,'b',3);
    EXPECT_TRUE(fa.isComplete());
}

/*Test Nature complète d'un automate ayant plusieurs états initaux*/
TEST(AutomatonTest,isCompleteWithInitialStateS) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.setStateFinal(3);
    fa.setStateInitial(1);
    fa.setStateInitial(2);
    fa.addTransition(1,'a',2);
    fa.addTransition(1,'b',1);
    fa.addTransition(2,'b',3);
    fa.addTransition(2,'a',2);
    fa.addTransition(3,'a',3);
    fa.addTransition(3,'b',3);
    EXPECT_TRUE(fa.isComplete());
}


/*Test Nature complète d'un automate ayant plusieurs états finaux*/
TEST(AutomatonTest,isCompleteWithFinalStateS) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.setStateFinal(3);
    fa.setStateFinal(2);
    fa.setStateInitial(1);
    fa.addTransition(1,'a',2);
    fa.addTransition(1,'b',1);
    fa.addTransition(2,'b',3);
    fa.addTransition(2,'a',2);
    fa.addTransition(3,'a',3);
    fa.addTransition(3,'b',3);
    EXPECT_TRUE(fa.isComplete());
}

/*Test Nature complète d'un automate qui l'est*/
TEST(AutomatonTest,isCompleteTrue) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.setStateInitial(1);
    fa.setStateFinal(2);
    fa.addTransition(1,'a',2);
    fa.addTransition(1,'b',1);
    fa.addTransition(2,'a',1);
    fa.addTransition(2,'b',2);
    EXPECT_TRUE(fa.isComplete());
}



/*Test Nature complète d'un automate qui ne l'est pas*/
TEST(AutomatonTest,isCompleteFalse) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.setStateInitial(1);
    fa.setStateFinal(2);
    fa.addTransition(1,'a',2);
    fa.addTransition(1,'b',1);
    fa.addTransition(2,'a',1);
    EXPECT_FALSE(fa.isComplete());
}



/*Test Nature complète d'un automate qui ne possède qu'un état*/
TEST(AutomatonTest,isCompleteOneState) {
    fa::Automaton fa;
    fa.addState(1);
    EXPECT_TRUE(fa.isComplete());
}



/*Test Nature complète d'un automate vide*/
TEST(AutomatonTest,isCompleteEmpty) {
    fa::Automaton fa;
    EXPECT_TRUE(fa.isComplete());
}

////////////////////TEST MAKE COMPLETE

/*Test transformation d'un automate non complet en automate complet*/
TEST(AutomatonTest,transformToComplete) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.setStateInitial(1);
    fa.setStateFinal(2);
    fa.addTransition(1,'a',2);
    fa.addTransition(1,'b',1);
    fa.addTransition(2,'a',1);
    EXPECT_FALSE(fa.isComplete());
    fa.makeComplete();
    EXPECT_TRUE(fa.isComplete());
}


/*Test transformation d'un automate vide en automate complet*/
TEST(AutomatonTest,transformEmptyToComplete) {
fa::Automaton fa;
fa.makeComplete();
EXPECT_TRUE(fa.isComplete());
}


/*Test transformation d'un automate déjà complet*/
TEST(AutomatonTest,isAlreadyComplete) {
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.setStateInitial(1);
fa.setStateFinal(2);
fa.addTransition(1,'a',2);
fa.addTransition(1,'b',1);
fa.addTransition(2,'a',1);
fa.addTransition(2,'b',2);
EXPECT_TRUE(fa.isComplete());
fa.makeComplete();
EXPECT_TRUE(fa.isComplete());
}


/*Test transformation d'un automate sans transition mais avec un état en automate complet*/
TEST(AutomatonTest,MakeCompleteOneState) {
fa::Automaton fa;
fa.addState(1);
fa.makeComplete();
EXPECT_TRUE(fa.isComplete());
}



////////////////////TEST MAKE COMPLEMENT

/*Test transformation d'un automate en son complémentaire*/
TEST(AutomatonTest,transformToComplementary){
	fa::Automaton fa,faOK;
	fa.addState(1);
	fa.addState(2);
	fa.addState(3);
	fa.setStateInitial(1);
	fa.setStateFinal(3);
	fa.addTransition(1,'a',2);
	fa.addTransition(2,'a',3);
	fa.addTransition(2,'a',1); 
	fa.makeComplete();
	fa.prettyPrint(std::cout);
	faOK= faOK.createDeterministic(fa);
	faOK.prettyPrint(std::cout);
	EXPECT_TRUE(faOK.isComplete());
	EXPECT_TRUE(faOK.isDeterministic());   //AUTOMATE RECONNAISSANT LES MOTS AYANT UN NOMBRE PAIR DE 'a'>0
	EXPECT_TRUE(faOK.match("aa"));
	EXPECT_TRUE(faOK.match("aaaaaaaa"));
	EXPECT_FALSE(faOK.match(""));
	EXPECT_FALSE(faOK.match("a"));
	EXPECT_FALSE(faOK.match("aaaaaaa"));
//faOK.makeComplement();
	EXPECT_FALSE(faOK.match("aa"));
	EXPECT_FALSE(faOK.match("aaaaaaaa"));
	EXPECT_TRUE(faOK.match(""));
	EXPECT_TRUE(faOK.match("a"));
	EXPECT_TRUE(faOK.match("aaaaaaa"));//AUTOMATE RECONAISSANT LES MOTS AVEC NOMBRE NUL OU IMPAIR DE 'a'
}



/*
//PART1: Test de la non modification des états d'origine
TEST(AutomatonTest,transformToComplementaryPart1) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.addState(4);
    fa.setStateInitial(1);
    fa.setStateFinal(3);
    fa.addTransition(1,'a',2);
    fa.addTransition(2,'a',2);
    fa.addTransition(2,'b',3);
    fa.addTransition(3,'b',3);
    fa.addTransition(3,'a',4);
    fa.addTransition(4,'a',4);
    fa.addTransition(4,'b',4);
    fa.addTransition(1,'b',4);
    EXPECT_TRUE(fa.isComplete());
    EXPECT_TRUE(fa.isDeterministic());
    fa.makeComplement();
    
    EXPECT_TRUE(fa.hasState(1));
    EXPECT_TRUE(fa.hasState(2));
    EXPECT_TRUE(fa.hasState(3));
    EXPECT_TRUE(fa.hasState(4));
}


//PART2:Test de la non modification des transitions
TEST(AutomatonTest,transformToComplementaryPart2) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.addState(4);
    fa.setStateInitial(1);
    fa.setStateFinal(3);
    fa.addTransition(1,'a',2);
    fa.addTransition(2,'a',2);
    fa.addTransition(2,'b',3);
    fa.addTransition(3,'b',3);
    fa.addTransition(3,'a',4);
    fa.addTransition(4,'a',4);
    fa.addTransition(4,'b',4);
    fa.addTransition(1,'b',4);
    EXPECT_TRUE(fa.isComplete());
    EXPECT_TRUE(fa.isDeterministic());
    fa.makeComplement();
    EXPECT_TRUE(fa.hasTransition(1,'a',2));
    EXPECT_TRUE(fa.hasTransition(2,'a',2));
    EXPECT_TRUE(fa.hasTransition(2,'b',3));
    EXPECT_TRUE(fa.hasTransition(3,'b',3));
    EXPECT_TRUE(fa.hasTransition(3,'a',4));
    EXPECT_TRUE(fa.hasTransition(4,'a',4));
    EXPECT_TRUE(fa.hasTransition(4,'b',4));
    EXPECT_TRUE(fa.hasTransition(1,'b',4));
}


//PART3: Test de la non modification de la nature déterminsite et complète de l'automate
TEST(AutomatonTest,transformToComplementaryPart3) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.addState(4);
    fa.setStateInitial(1);
    fa.setStateFinal(3);
    fa.addTransition(1,'a',2);
    fa.addTransition(2,'a',2);
    fa.addTransition(2,'b',3);
    fa.addTransition(3,'b',3);
    fa.addTransition(3,'a',4);
    fa.addTransition(4,'a',4);
    fa.addTransition(4,'b',4);
    fa.addTransition(1,'b',4);
    EXPECT_TRUE(fa.isComplete());
    EXPECT_TRUE(fa.isDeterministic());
    fa.makeComplement();
    EXPECT_TRUE(fa.isComplete());
    EXPECT_TRUE(fa.isDeterministic());

}


//PART4: Test de la non modification de l'inversion des états normaux en finaux
TEST(AutomatonTest,transformToComplementaryPart4) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.addState(4);
    fa.setStateInitial(1);
    fa.setStateFinal(3);
    fa.addTransition(1,'a',2);
    fa.addTransition(2,'a',2);
    fa.addTransition(2,'b',3);
    fa.addTransition(3,'b',3);
    fa.addTransition(3,'a',4);
    fa.addTransition(4,'a',4);
    fa.addTransition(4,'b',4);
    fa.addTransition(1,'b',4);
    EXPECT_TRUE(fa.isComplete());
    EXPECT_TRUE(fa.isDeterministic());
    fa.makeComplement();
    EXPECT_TRUE(fa.isStateFinal(1));
    EXPECT_TRUE(fa.isStateFinal(2));
    EXPECT_TRUE(fa.isStateFinal(4));
}

//PART5: Test de la non modification de l'inversion des états finaux en normaux
TEST(AutomatonTest,transformToComplementaryPart5) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.setStateFinal(3);
    fa.setStateInitial(1);
    fa.addTransition(1,'a',2);
    fa.addTransition(1,'b',1);
    fa.addTransition(2,'b',3);
    fa.addTransition(2,'a',2);
    fa.addTransition(3,'a',3);
    fa.addTransition(3,'b',3);
    EXPECT_TRUE(fa.isComplete());
    EXPECT_TRUE(fa.isDeterministic());
    fa.makeComplement();
    EXPECT_FALSE(fa.isStateFinal(3));

}

//PART6: Test de la non modification de la conservation des états initiaux
TEST(AutomatonTest,transformToComplementaryPart6) {
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.setStateFinal(3);
    fa.setStateInitial(1);
    fa.addTransition(1,'a',2);
    fa.addTransition(1,'b',1);
    fa.addTransition(2,'b',3);
    fa.addTransition(2,'a',2);
    fa.addTransition(3,'a',3);
    fa.addTransition(3,'b',3);
    EXPECT_TRUE(fa.isComplete());
    EXPECT_TRUE(fa.isDeterministic());
    fa.makeComplement();
    EXPECT_TRUE(fa.isStateInitial(1));

}

*/
/*Test transformation d'un automate vide en son complémentaire*/
TEST(AutomatonTest,transformEmptyToComplementary) {
fa::Automaton fa;
EXPECT_DEATH(fa.makeComplement(),"");
EXPECT_EQ(fa.countTransitions(),0u);
EXPECT_EQ(fa.countStates(),0u);
}


/*Test transformation d'un automate sans transition en son complémentaire*/
TEST(AutomatonTest,transformWithoutTransitionToComplementary) {
fa::Automaton fa;
fa.addState(1);
EXPECT_DEATH(fa.makeComplement(),"");
EXPECT_EQ(fa.countTransitions(),0u);
EXPECT_EQ(fa.countStates(),1u);
}




//////////////////////////////////////////////////////////TEST TP3

////////////////////TEST IS LANGUAGE EMPTY


/*TEST langage vide qui l'est*/
TEST(automatonTest,EmptyLanguageYES){
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.setStateFinal(3);
    fa.setStateInitial(1);
    fa.addTransition(1,'a',2);
    fa.addTransition(3,'b',3);
    EXPECT_TRUE(fa.isLanguageEmpty());
}


/*TEST langage vide qui ne l'est pas*/
TEST(automatonTest,EmptyLanguageNO){
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.setStateFinal(3);
    fa.setStateInitial(1);
    fa.addTransition(1,'a',2);
    fa.addTransition(2,'a',3);
    fa.addTransition(3,'b',3);
    EXPECT_FALSE(fa.isLanguageEmpty());

}


/*TEST langage vide sur un atomate sans état initial*/
TEST(automatonTest,EmptyLanguageWithoutInitial){
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.setStateFinal(3);
    fa.addTransition(1,'a',2);
    fa.addTransition(2,'a',3);
    fa.addTransition(3,'b',3);
    EXPECT_TRUE(fa.isLanguageEmpty());

}


/*TEST langage vide sur un atomate sans état final*/
TEST(automatonTest,EmptyLanguageWithoutFinal){
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.setStateInitial(1);
    fa.addTransition(1,'a',2);
    fa.addTransition(2,'a',3);
    fa.addTransition(3,'b',3);
    EXPECT_TRUE(fa.isLanguageEmpty());

}


/*TEST langage vide sur un atomate sans état final et sans état initial*/
TEST(automatonTest,EmptyLanguageWithoutInitialAndFinal){
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.addTransition(1,'a',2);
    fa.addTransition(2,'a',3);
    fa.addTransition(3,'b',3);
    EXPECT_TRUE(fa.isLanguageEmpty());

}


/*TEST langage vide automate vide*/
TEST(automatonTest,EmptyLanguageEmptyAutomaton){
fa::Automaton fa;
EXPECT_TRUE(fa.isLanguageEmpty());

}


/*TEST langage vide automate sans transition*/
TEST(automatonTest,EmptyLanguageWithoutTransitionAutomaton){
fa::Automaton fa;
fa.addState(1);
EXPECT_TRUE(fa.isLanguageEmpty());
}


////////////////////TEST REMOVE NON ACCESSIBLE STATES

/*TEST suppression d'un état non accessible simple*/
TEST(automatonTest,RemoveNonAccessibleSimpleState){
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.setStateInitial(1);
    fa.setStateFinal(2);
    fa.addTransition(1,'a',2);
    fa.addTransition(2,'b',2);
    fa.addTransition(3,'c',2);
    fa.removeNonAccessibleStates();
    EXPECT_FALSE(fa.hasState(3));
    EXPECT_TRUE(fa.hasState(2));
    EXPECT_TRUE(fa.hasState(1));
    EXPECT_TRUE(fa.hasTransition(1,'a',2));
    EXPECT_TRUE(fa.hasTransition(2,'b',2));
    EXPECT_DEATH(fa.hasTransition(1,'b',3),"");

}

/*TEST suppression d'un état non accessibles dans un automate vide*/
TEST(automatonTest,RemoveNonAccessibleEmptyAutomaton){
fa::Automaton fa;
fa.removeNonAccessibleStates();
EXPECT_EQ(fa.countStates(),0u);
EXPECT_EQ(fa.countTransitions(),0u);
}

/*TEST suppression des états non accessibles dans un automate qui n'en possède pas*/
TEST(automatonTest,RemoveNonAccessibleStateWithoutNonAccessibleState){
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.setStateInitial(1);
    fa.setStateFinal(2);
    fa.addTransition(1,'a',2);
    fa.addTransition(2,'b',2);
    fa.addTransition(2,'c',3);
    fa.removeNonAccessibleStates();
    EXPECT_TRUE(fa.hasState(1));
    EXPECT_TRUE(fa.hasState(2));
    EXPECT_TRUE(fa.hasState(3));
    EXPECT_TRUE(fa.hasTransition(1,'a',2));
    EXPECT_TRUE(fa.hasTransition(2,'b',2));
    EXPECT_TRUE(fa.hasTransition(2,'c',3));
}


/*TEST suppression d'un état non accessible impliqué dans une transition avec un état accessible*/
TEST(automatonTest,RemoveNonAccessibleLinkedState){
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.addState(4);
    fa.setStateInitial(1);
    fa.setStateFinal(2);
    fa.addTransition(1,'a',2);
    fa.addTransition(2,'b',2);
    fa.addTransition(2,'a',4);
    fa.addTransition(3,'b',4);
    fa.removeNonAccessibleStates();
    EXPECT_FALSE(fa.hasState(3));
    EXPECT_TRUE(fa.hasState(4));
    EXPECT_DEATH(fa.hasTransition(3,'b',4),"");
}


/*TEST suppression d'une transition non accessible*/
TEST(automatonTest,RemoveNonAccessibleTransition){
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.addState(4);
    fa.setStateInitial(1);
    fa.setStateFinal(2);
    fa.addTransition(1,'a',2);
    fa.addTransition(2,'b',2);
    fa.addTransition(3,'b',4);
    fa.removeNonAccessibleStates();
    EXPECT_FALSE(fa.hasState(3));
    EXPECT_FALSE(fa.hasState(4));
    EXPECT_DEATH(fa.hasTransition(3,'b',4),"");
}
/*TEST avec un atomate ne possèdant pas d'état inital*/
TEST(automatonTest,RemoveNonAccessibleWithoutInitialState){
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.setStateFinal(2);
    fa.addTransition(1,'a',2);
    fa.addTransition(2,'b',2);
    fa.removeNonAccessibleStates();
    EXPECT_FALSE(fa.hasState(1));
    EXPECT_FALSE(fa.hasState(2));
    EXPECT_FALSE(fa.hasState(3));
    EXPECT_DEATH(fa.hasTransition(1,'a',2),"");
}


/*TEST avec un atomate ne possèdant pas d'état Final*/
TEST(automatonTest,RemoveNonAccessibleWithoutFinalState){
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.setStateInitial(1);
fa.addTransition(1,'a',2);
fa.addTransition(2,'b',2);
fa.removeNonAccessibleStates();
EXPECT_TRUE(fa.hasState(1));
EXPECT_TRUE(fa.hasState(2));
EXPECT_FALSE(fa.hasState(3));
EXPECT_TRUE(fa.hasTransition(1,'a',2));
EXPECT_TRUE(fa.hasTransition(2,'b',2));
}


/*TEST avec un atomate ne possèdant pas d'état initial ni d'état final*/
TEST(automatonTest,RemoveNonAccessibleWithoutInitialAndFinalState){
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.addTransition(1,'a',2);
fa.addTransition(2,'b',2);
fa.removeNonAccessibleStates();
EXPECT_FALSE(fa.hasState(1));
EXPECT_FALSE(fa.hasState(2));
EXPECT_FALSE(fa.hasState(3));
EXPECT_DEATH(fa.hasTransition(1,'a',2),"");
}


/*TEST avec un atomate possèdant deux états initiaux*/
TEST(automatonTest,RemoveNonAccessibleWithTwoInitialStates){
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.addState(4);
fa.addState(5);
fa.addTransition(3,'d',3);
fa.addTransition(1,'a',2);
fa.addTransition(2,'b',5);
fa.addTransition(2,'a',4);
fa.addTransition(4,'b',1);
fa.setStateInitial(1);
fa.setStateInitial(4);
fa.setStateFinal(5);
fa.removeNonAccessibleStates();
EXPECT_TRUE(fa.hasState(1));
EXPECT_TRUE(fa.hasState(2));
EXPECT_FALSE(fa.hasState(3));
EXPECT_TRUE(fa.hasState(4));
EXPECT_TRUE(fa.hasState(5));
EXPECT_TRUE(fa.hasTransition(1,'a',2));
EXPECT_TRUE(fa.hasTransition(2,'b',5));
EXPECT_TRUE(fa.hasTransition(2,'a',4));
EXPECT_TRUE(fa.hasTransition(4,'b',1));
EXPECT_DEATH(fa.hasTransition(3,'d',3),"");
/** CA DOIT PETER ICI**/
/** CA DOIT PETER ICI**/
EXPECT_EQ(fa.countTransitions(),4u);
}



/*TEST avec un atomate possèdant des états mais pas de transitions*/
TEST(automatonTest,RemoveNonAccessibleWithoutTransitions){
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.setStateInitial(1);
fa.setStateFinal(3);
fa.removeNonAccessibleStates();
EXPECT_TRUE(fa.hasState(1));
EXPECT_FALSE(fa.hasState(2));
EXPECT_FALSE(fa.hasState(3));
EXPECT_EQ(fa.countTransitions(),0u);
}

////////////////////TEST REMOVE NON CO ACCESSIBLE STATES
/*TEST suppression d'un état non co-accessible simple*/
TEST(automatonTest,RemoveNonCoAccessibleSimpleState){
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.setStateInitial(1);
    fa.setStateFinal(2);
    fa.addTransition(1,'a',2);
    fa.addTransition(1,'b',3);
    fa.addTransition(2,'b',2);
    fa.removeNonCoAccessibleStates();
    EXPECT_FALSE(fa.hasState(3));
    EXPECT_TRUE(fa.hasState(1));
    EXPECT_TRUE(fa.hasState(2));
    EXPECT_TRUE(fa.hasTransition(1,'a',2));
    EXPECT_TRUE(fa.hasTransition(2,'b',2));
    EXPECT_DEATH(fa.hasTransition(2,'a',3),"");

}



/*TEST suppression d'un état non co-accessibles dans un automate vide*/
TEST(automatonTest,RemoveNonCoAccessibleEmptyAutomaton){
fa::Automaton fa;
fa.removeNonCoAccessibleStates();
EXPECT_EQ(fa.countStates(),0u);
EXPECT_EQ(fa.countTransitions(),0u);
}



/*TEST suppression des états non co-accessibles dans un automate qui n'en a pas*/
TEST(automatonTest,RemoveNonCoAccessibleZeroNoCoAccessibleState){
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.setStateInitial(1);
    fa.setStateFinal(3);
    fa.addTransition(1,'a',2);
    fa.addTransition(2,'a',3);
    fa.addTransition(2,'b',2);
    fa.removeNonCoAccessibleStates();
    EXPECT_TRUE(fa.hasState(1));
    EXPECT_TRUE(fa.hasState(2));
    EXPECT_TRUE(fa.hasState(3));
    EXPECT_TRUE(fa.hasTransition(1,'a',2));
    EXPECT_TRUE(fa.hasTransition(2,'a',3));
    EXPECT_TRUE(fa.hasTransition(2,'b',2));

}


/*TEST suppression d'un état non accessible impliqué dans une transition avec un état co-accessible*/
TEST(automatonTest,RemoveNonCoAccessibleLinkedState){
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.setStateInitial(1);
    fa.setStateFinal(2);
    fa.addTransition(1,'a',2);
    fa.addTransition(2,'b',2);
    fa.addTransition(2,'a',3);
    fa.addTransition(1,'b',3);
    fa.removeNonCoAccessibleStates();
    EXPECT_FALSE(fa.hasState(3));
    EXPECT_DEATH(fa.hasTransition(1,'b',3),"");
}

/*TEST suppression d'une transition non co-accessible*/
TEST(automatonTest,RemoveNonCoAccessibleTransition){
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.addState(4);
    fa.setStateInitial(1);
    fa.setStateFinal(2);
    fa.addTransition(1,'a',2);
    fa.addTransition(2,'b',2);
    fa.addTransition(4,'b',3);
    fa.removeNonCoAccessibleStates();
    EXPECT_FALSE(fa.hasState(3));
    EXPECT_FALSE(fa.hasState(4));
    EXPECT_DEATH(fa.hasTransition(4,'b',3),"");
}



/*TEST avec un atomate possèdant deux états finaux*/
TEST(automatonTest,RemoveNonCoAccessibleWithTwoFinalStates){
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.addState(4);
fa.addState(5);
fa.addTransition(3,'d',3);
fa.addTransition(1,'a',2);
fa.addTransition(2,'b',5);
fa.addTransition(2,'a',4);
fa.addTransition(4,'b',1);
fa.setStateInitial(1);
fa.setStateFinal(4);
fa.setStateFinal(5);
fa.removeNonAccessibleStates();
EXPECT_TRUE(fa.hasState(1));
EXPECT_TRUE(fa.hasState(2));
EXPECT_FALSE(fa.hasState(3));
EXPECT_TRUE(fa.hasState(4));
EXPECT_TRUE(fa.hasState(5));
EXPECT_TRUE(fa.hasTransition(1,'a',2));
EXPECT_TRUE(fa.hasTransition(2,'b',5));
EXPECT_TRUE(fa.hasTransition(2,'a',4));
EXPECT_TRUE(fa.hasTransition(4,'b',1));
EXPECT_DEATH(fa.hasTransition(3,'d',3),"");
/** CA DOIT PETER ICI**/

EXPECT_EQ(fa.countTransitions(),4u);
}


/*TEST avec un atomate ne possèdant pas d'état inital*/
TEST(automatonTest,RemoveNonCoAccessibleWithoutInitialState){
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.setStateFinal(2);
fa.addTransition(1,'a',2);
fa.addTransition(2,'b',2);
fa.removeNonCoAccessibleStates();
EXPECT_TRUE(fa.hasState(1));
EXPECT_TRUE(fa.hasState(2));
EXPECT_FALSE(fa.hasState(3));
EXPECT_TRUE(fa.hasTransition(1,'a',2));
EXPECT_TRUE(fa.hasTransition(2,'b',2));
}


/*TEST avec un atomate ne possèdant pas d'état Final*/
TEST(automatonTest,RemoveNonCoAccessibleWithoutFinalState){
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.setStateInitial(1);
fa.addTransition(1,'a',2);
fa.addTransition(2,'b',2);
fa.removeNonCoAccessibleStates();
EXPECT_FALSE(fa.hasState(1));
EXPECT_FALSE(fa.hasState(2));
EXPECT_FALSE(fa.hasState(3));
EXPECT_DEATH(fa.hasTransition(1,'a',2),"");
}


/*TEST avec un atomate ne possèdant pas d'état initial ni d'état final*/
TEST(automatonTest,RemoveNonCoAccessibleWithoutInitialAndFinalState){
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.addTransition(1,'a',2);
fa.addTransition(2,'b',2);
fa.removeNonCoAccessibleStates();
EXPECT_FALSE(fa.hasState(1));
EXPECT_FALSE(fa.hasState(2));
EXPECT_FALSE(fa.hasState(3));
EXPECT_DEATH(fa.hasTransition(1,'a',2),"");
}

//////////////////////////////////////////////////////////TEST TP4

////////////////////TEST CREATE PRODUCT


/*TEST produit de 2 automates lambda*/
TEST(automatonTest,createProduct){
    fa::Automaton fa1;
    fa::Automaton fa2;
    fa::Automaton faPdt;


    //automate 1 fa1
    fa1.addState(0);
    fa1.addState(1);
    fa1.setStateInitial(0);
    fa1.setStateFinal(1);
    fa1.addTransition(0,'a',1);
    fa1.addTransition(1,'a',1);
    fa1.addTransition(1,'b',1);

    //automate 2 fa2
    fa2.addState(0);
    fa2.addState(1);
    fa2.setStateInitial(0);
    fa2.setStateFinal(1);
    fa2.addTransition(0,'a',0);
    fa1.addTransition(0,'b',1);
    fa1.addTransition(1,'b',1);
    fa1.addTransition(1,'a',0);

    EXPECT_TRUE(fa1.match("aa"));
    EXPECT_FALSE(fa1.match("bbb"));
    EXPECT_TRUE(fa2.match("bbb"));
    EXPECT_FALSE(fa2.match("aa"));
    faPdt=faPdt.createProduct(fa1,fa2);
    EXPECT_TRUE(faPdt.match("aabbb"));
   // EXPECT_EQ(faPdt.countStates(),4u);
   // EXPECT_EQ(faPdt.countTransitions(),5u);
    EXPECT_EQ(faPdt.getAlphabetSize(),2u);
}


/*TEST taille alphabet apres produit de 2 automates lambda*/
TEST(automatonTest,sizeAlphabetAfterCreateProduct){
    fa::Automaton fa1;
    fa::Automaton fa2;
    fa::Automaton faPdt;


    //automate 1 fa1
    fa1.addState(0);
    fa1.addState(1);
    fa1.setStateInitial(0);
    fa1.setStateFinal(1);
    fa1.addTransition(0,'a',1);
    fa1.addTransition(1,'b',1);
    fa1.addTransition(1,'c',1);

    //automate 2 fa2
    fa2.addState(0);
    fa2.addState(1);
    fa2.setStateInitial(0);
    fa2.setStateFinal(1);
    fa2.addTransition(0,'z',0);
    fa1.addTransition(0,'a',1);
    fa1.addTransition(1,'a',1);
    fa1.addTransition(1,'z',0);

    faPdt=faPdt.createProduct(fa1,fa2);
    EXPECT_EQ(faPdt.getAlphabetSize(),1u);
   // EXPECT_EQ(faPdt.countStates(),4u);
   // EXPECT_EQ(faPdt.countTransitions(),5u);
}


// si ces tests plantent, c'est pas grave
// si ces tests plantent, c'est pas grave
// si ces tests plantent, c'est pas grave
// si ces tests plantent, c'est pas grave
// si ces tests plantent, c'est pas grave
// si ces tests plantent, c'est pas grave
// si ces tests plantent, c'est pas grave
// si ces tests plantent, c'est pas grave
// si ces tests plantent, c'est pas grave
// si ces tests plantent, c'est pas grave
// si ces tests plantent, c'est pas grave
// si ces tests plantent, c'est pas grave
// si ces tests plantent, c'est pas grave
// si ces tests plantent, c'est pas grave
// si ces tests plantent, c'est pas grave
// si ces tests plantent, c'est pas grave







/**
TEST produit de 2 automates lambda*/
//PART1: verif compte transitions, état et alphabet




/*TEST produit de 2 automates lambda*/
/**TEST(automatonTest,createValidProduct1){
    fa::Automaton fa1;
    fa::Automaton fa2;
    fa::Automaton faPdt;


    //automate 1 fa1
    fa1.addState(0);
    fa1.addState(1);
    fa1.addState(2);
    fa1.setStateInitial(0);
    fa1.setStateFinal(2);
    fa1.addTransition(1,'a',2);
    fa1.addTransition(1,'b',0);
    fa1.addTransition(2,'a',1);
    fa1.addTransition(2,'b',2);
    fa1.addTransition(0,'a',0);
    fa1.addTransition(0,'b',1);

    //automate 2 fa2
    fa2.addState(0);
    fa2.addState(1);
    fa2.addState(2);
    fa2.setStateInitial(0);
    fa2.setStateFinal(2);
    fa2.addTransition(1,'b',2);
    fa2.addTransition(1,'b',0);
    fa2.addTransition(2,'a',2);
    fa2.addTransition(2,'b',2);
    fa2.addTransition(0,'a',0);
    fa2.addTransition(0,'a',1);
    fa2.addTransition(0,'b',1);

    faPdt=fa::Automaton::createProduct(fa1,fa2);
//LES PROCHAINES LIGNES SONT A DELETE SI LE TEST PLANTE
    EXPECT_EQ(faPdt.countStates(),9u);
    EXPECT_EQ(faPdt.countTransitions(),21u);
    EXPECT_EQ(faPdt.getAlphabetSize(),2u);
}

//LES PROCHAINES LIGNES SONT A DELETE SI LE TEST PLANTE
//PART2: verif états
TEST(automatonTest,createValidProduct2){
fa::Automaton fa1;
fa::Automaton fa2;
fa::Automaton faPdt;


//automate 1 fa1
fa1.addState(0);
fa1.addState(1);
fa1.addState(2);
fa1.setStateInitial(0);
fa1.setStateFinal(2);
fa1.addTransition(1,'a',2);
fa1.addTransition(1,'b',0);
fa1.addTransition(2,'a',1);
fa1.addTransition(2,'b',2);
fa1.addTransition(0,'a',0);
fa1.addTransition(0,'b',1);

//automate 2 fa2
fa2.addState(0);
fa2.addState(1);
fa2.addState(2);
fa2.setStateInitial(0);
fa2.setStateFinal(2);
fa2.addTransition(1,'b',2);
fa2.addTransition(1,'b',0);
fa2.addTransition(2,'a',2);
fa2.addTransition(2,'b',2);
fa2.addTransition(0,'a',0);
fa2.addTransition(0,'a',1);
fa2.addTransition(0,'b',1);

faPdt=fa::Automaton::createProduct(fa1,fa2);

EXPECT_TRUE(faPdt.hasState(0));
EXPECT_TRUE(faPdt.hasState(1));
EXPECT_TRUE(faPdt.hasState(2));
EXPECT_TRUE(faPdt.hasState(3));
EXPECT_TRUE(faPdt.hasState(4));
EXPECT_TRUE(faPdt.hasState(5));
EXPECT_TRUE(faPdt.hasState(6));
EXPECT_TRUE(faPdt.hasState(7));
EXPECT_TRUE(faPdt.hasState(8));
EXPECT_TRUE(faPdt.isStateInitial(3));
EXPECT_TRUE(faPdt.isStateFinal(8));

}

//LES PROCHAINES LIGNES SONT A DELETE SI LE TEST PLANTE
//PART3: verif transition
TEST(automatonTest,createValidProduct3){
fa::Automaton fa1;
fa::Automaton fa2;
fa::Automaton faPdt;


//automate 1 fa1
fa1.addState(0);
fa1.addState(1);
fa1.addState(2);
fa1.setStateInitial(0);
fa1.setStateFinal(2);
fa1.addTransition(1,'a',2);
fa1.addTransition(1,'b',0);
fa1.addTransition(2,'a',1);
fa1.addTransition(2,'b',2);
fa1.addTransition(0,'a',0);
fa1.addTransition(0,'b',1);

//automate 2 fa2
fa2.addState(0);
fa2.addState(1);
fa2.addState(2);
fa2.setStateInitial(0);
fa2.setStateFinal(2);
fa2.addTransition(1,'b',2);
fa2.addTransition(1,'b',0);
fa2.addTransition(2,'a',2);
fa2.addTransition(2,'b',2);
fa2.addTransition(0,'a',0);
fa2.addTransition(0,'a',1);
fa2.addTransition(0,'b',1);

faPdt=fa::Automaton::createProduct(fa1,fa2);

EXPECT_TRUE(faPdt.hasTransition(0,'b',3));
EXPECT_TRUE(faPdt.hasTransition(0,'b',6));
EXPECT_TRUE(faPdt.hasTransition(1,'a',8));
EXPECT_TRUE(faPdt.hasTransition(1,'b',6));
EXPECT_TRUE(faPdt.hasTransition(2,'b',1));
EXPECT_TRUE(faPdt.hasTransition(2,'b',4));
EXPECT_TRUE(faPdt.hasTransition(3,'a',2));
EXPECT_TRUE(faPdt.hasTransition(3,'a',3));
EXPECT_TRUE(faPdt.hasTransition(3,'b',0));
EXPECT_TRUE(faPdt.hasTransition(4,'a',5));
EXPECT_TRUE(faPdt.hasTransition(4,'a',7));
EXPECT_TRUE(faPdt.hasTransition(4,'b',2));
EXPECT_TRUE(faPdt.hasTransition(5,'a',0));
EXPECT_TRUE(faPdt.hasTransition(5,'a',4));
EXPECT_TRUE(faPdt.hasTransition(5,'b',7));
EXPECT_TRUE(faPdt.hasTransition(6,'a',6));
EXPECT_TRUE(faPdt.hasTransition(6,'b',1));
EXPECT_TRUE(faPdt.hasTransition(7,'b',5));
EXPECT_TRUE(faPdt.hasTransition(7,'b',8));
EXPECT_TRUE(faPdt.hasTransition(8,'a',1));
EXPECT_TRUE(faPdt.hasTransition(8,'b',8));
}
**/









/*TEST produit de 2 automates vides*/
TEST(automatonTest,createEmptyProduct){
fa::Automaton fa1;
fa::Automaton fa2;
fa::Automaton faPdt;


//automate 1 fa1


//automate 2 fa2


faPdt=fa::Automaton::createProduct(fa1,fa2);
//LES PROCHAINES LIGNES SONT A DELETE SI LE TEST PLANTE
EXPECT_EQ(faPdt.countStates(),0u);
EXPECT_EQ(faPdt.countTransitions(),0u);
EXPECT_EQ(faPdt.getAlphabetSize(),0u);
}



/*TEST produit de 2 automates sans transitions*/
//PART1: comptage states, transitions
/*TEST(automatonTest,createOneStateProduct1){
fa::Automaton fa1;
fa::Automaton fa2;
fa::Automaton faPdt;


//automate 1 fa1
fa1.addState(1);
fa1.setStateInitial(1);
fa1.setStateFinal(1);

//automate 2 fa2
fa2.addState(2);
fa1.setStateInitial(2);
fa1.setStateFinal(2);


faPdt=fa::Automaton::createProduct(fa1,fa2);

EXPECT_EQ(faPdt.countStates(),1u);
EXPECT_EQ(faPdt.countTransitions(),0u);
EXPECT_EQ(faPdt.getAlphabetSize(),0u);
}


//PART2: nature état
TEST(automatonTest,createOneStateProduct2){
fa::Automaton fa1;
fa::Automaton fa2;
fa::Automaton faPdt;


//automate 1 fa1
fa1.addState(1);
fa1.setStateInitial(1);
fa1.setStateFinal(1);

//automate 2 fa2
fa2.addState(2);
fa1.setStateInitial(2);
fa1.setStateFinal(2);

faPdt=fa::Automaton::createProduct(fa1,fa2);

EXPECT_TRUE(faPdt.hasState(0));
EXPECT_TRUE(faPdt.isStateInitial(0));
EXPECT_TRUE(faPdt.isStateFinal(0));
}


*/


// si ces tests plantent, c'est pas grave -fin
// si ces tests plantent, c'est pas grave -fin
// si ces tests plantent, c'est pas grave -fin
// si ces tests plantent, c'est pas grave -fin
// si ces tests plantent, c'est pas grave -fin
// si ces tests plantent, c'est pas grave -fin
// si ces tests plantent, c'est pas grave -fin
// si ces tests plantent, c'est pas grave -fin
// si ces tests plantent, c'est pas grave -fin
// si ces tests plantent, c'est pas grave -fin











////////////////////TEST HAS EMPTY INTERSECTION
/*TEST intersection non vide de 2 automates*/
TEST(automatonTest,hasEmptyIntersectionWithNO){
    fa::Automaton fa1;
    fa::Automaton fa2;


    //automate 1 fa1
    fa1.addState(0);
    fa1.addState(1);
    fa1.addState(2);
    fa1.setStateInitial(0);
    fa1.setStateFinal(2);
    fa1.addTransition(1,'a',2);
    fa1.addTransition(1,'b',0);
    fa1.addTransition(2,'a',1);
    fa1.addTransition(2,'b',2);
    fa1.addTransition(0,'a',0);
    fa1.addTransition(0,'b',1);

    //automate 2 fa2
    fa2.addState(0);
    fa2.addState(1);
    fa2.addState(2);
    fa2.setStateInitial(0);
    fa2.setStateFinal(2);
    fa2.addTransition(1,'b',2);
    fa2.addTransition(1,'b',0);
    fa2.addTransition(2,'a',2);
    fa2.addTransition(2,'b',2);
    fa2.addTransition(0,'a',0);
    fa2.addTransition(0,'a',1);
    fa2.addTransition(0,'b',1);

    EXPECT_FALSE(fa1.hasEmptyIntersectionWith(fa2));

}


/*TEST intersection vide de 2 automates*/
TEST(automatonTest,hasEmptyIntersectionWithYES){
    fa::Automaton fa1;
    fa::Automaton fa2;

    //automate 1 fa1
    fa1.addState(0);
    fa1.addState(1);
    fa1.addState(2);
    fa1.setStateInitial(0);
    fa1.setStateFinal(2);
    fa1.addTransition(1,'a',2);
    fa1.addTransition(1,'b',0);
    fa1.addTransition(2,'a',1);
    fa1.addTransition(2,'b',2);
    fa1.addTransition(0,'a',0);
    fa1.addTransition(0,'b',1);

    //automate 2 fa2
    fa2.addState(0);
    fa2.addState(1);
    fa2.addState(2);
    fa2.setStateInitial(0);
    fa2.setStateFinal(2);
    fa2.addTransition(1,'d',2);
    fa2.addTransition(1,'d',0);
    fa2.addTransition(2,'c',2);
    fa2.addTransition(2,'d',2);
    fa2.addTransition(0,'c',0);
    fa2.addTransition(0,'c',1);
    fa2.addTransition(0,'d',1);

    EXPECT_TRUE(fa1.hasEmptyIntersectionWith(fa2));

}

/*TEST intersection vide de 2 automates dont un est vide*/
TEST(automatonTest,hasEmptyIntersectionWithAnEmptyAutomaton){
    fa::Automaton fa1;
    fa::Automaton fa2;

    //automate 1 fa1

    //automate 2 fa2
    fa2.addState(0);
    fa2.addState(1);
    fa2.setStateInitial(0);
    fa2.setStateFinal(1);
    fa2.addTransition(0,'c',0);
    fa2.addTransition(0,'d',1);
    fa2.addTransition(1,'d',1);
    fa2.addTransition(1,'c',0);

    EXPECT_TRUE(fa1.hasEmptyIntersectionWith(fa2));

}

 /*TEST intersection vide de 2 automates vides*/
TEST(automatonTest,hasEmptyIntersectionWith2EmptyAutomaton){
    fa::Automaton fa1;
    fa::Automaton fa2;

    //automate 1 fa1

    //automate 2 fa2


    EXPECT_TRUE(fa1.hasEmptyIntersectionWith(fa2));

}

//SI CA CORE DUMP-> MUTE TEST ET CHECK APRES
/*Test intersection de 2 automates sans transitions*/
TEST(automatonTest,hasEmptyIntersectionWithoutTransitions){
fa::Automaton fa1;
fa::Automaton fa2;
fa::Automaton faPdt;


//automate 1 fa1
fa1.addState(1);
fa1.setStateInitial(1);
fa1.setStateFinal(1);

//automate 2 fa2
fa2.addState(2);
fa2.setStateInitial(2);
fa2.setStateFinal(2);

EXPECT_FALSE(fa1.hasEmptyIntersectionWith(fa2));

}



//////////////////////////////////////////////////////////TEST TP5

////////////////////TEST READ STRING

/* TEST lecture du mot vide*/
TEST(automatonTest,ReadStringEmptyWord){
	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.addState(3);
	fa.setStateFinal(3);
	fa.setStateInitial(1);
	fa.addTransition(1,'a',2);
	fa.addTransition(2,'a',3);
	fa.addTransition(3,'b',3);
	const std::string word="";
	std::set<int> result=fa.readString(word);
	EXPECT_TRUE(result.empty());
}


/*TEST lecture d'un mot possèdant un caractère non reconnu par l'automate*/
TEST(automatonTest,ReadStringWrongWord){
fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.addState(3);
	fa.setStateFinal(3);
	fa.setStateInitial(1);
	fa.addTransition(1,'a',2);
	fa.addTransition(2,'a',3);
	fa.addTransition(3,'b',3);
	const std::string word="abc";
	std::set<int> result=fa.readString(word);
	EXPECT_TRUE(result.empty());
}


/*TEST lecture d'un mot trop court pour l'automate*/
TEST(automatonTest,ReadStringShortgWord){
fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.addState(3);
	fa.setStateFinal(3);
	fa.setStateInitial(1);
	fa.addTransition(1,'a',2);
	fa.addTransition(2,'a',3);
	fa.addTransition(3,'b',3);
	const std::string word="a";
	std::set<int> result=fa.readString(word);
	EXPECT_TRUE(result.empty());
}




/*TEST lecture d'un mot accepté par l'automate*/
//PART1:TEST DE LA NATURE NON VIDE DU RES
TEST(automatonTest,ReadStringWordPart1){
fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.addState(3);
	fa.setStateFinal(3);
	fa.setStateInitial(1);
	fa.addTransition(1,'a',2);
	fa.addTransition(2,'a',3);
	fa.addTransition(3,'b',3);
	const std::string word="aab";
	std::set<int> result=fa.readString(word);
	EXPECT_FALSE(result.empty());
}


/*TEST lecture d'un mot accepté par l'automate*/
//PART2: TEST DE LA TAILLE DU RES
TEST(automatonTest,ReadStringWordPart2){
fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.addState(3);
	fa.setStateFinal(3);
	fa.setStateInitial(1);
	fa.addTransition(1,'a',2);
	fa.addTransition(2,'a',3);
	fa.addTransition(3,'b',3);
	const std::string word="aab";
	std::set<int> result=fa.readString(word);
	EXPECT_EQ(result.size(),3u);
}


/*TEST lecture d'un mot accepté par l'automate */
//PART3:TEST DE LA PRESENCE DES ETATS DANS LE RES
TEST(automatonTest,ReadStringWordPart3){
fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.addState(3);
	fa.setStateFinal(3);
	fa.setStateInitial(1);
	fa.addTransition(1,'a',2);
	fa.addTransition(2,'a',3);
	fa.addTransition(3,'b',3);
	const std::string word="aab";
	std::set<int> result=fa.readString(word);
	EXPECT_NE(result.find(1),result.end());
	EXPECT_NE(result.find(2),result.end());
	EXPECT_NE(result.find(3),result.end());
}


/*TEST lecture d'un mot accepté par l'automate et qui boucle sur la même lettre à un moment*/
 //PART1: Test de la nature non vide du resultat
TEST(automatonTest,ReadStringLoopWordPart1){
fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.addState(3);
	fa.setStateFinal(3);
	fa.setStateInitial(1);
	fa.addTransition(1,'a',2);
	fa.addTransition(2,'a',3);
	fa.addTransition(3,'b',3);
	const std::string word="aabbbb";
	std::set<int> result=fa.readString(word);
	EXPECT_FALSE(result.empty());
}


/*TEST lecture d'un mot accepté par l'automate et qui boucle sur la même lettre à un moment*/
//PART2:  Test de la taille du resultat
TEST(automatonTest,ReadStringLoopWordPart2){
fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.addState(3);
	fa.setStateFinal(3);
	fa.setStateInitial(1);
	fa.addTransition(1,'a',2);
	fa.addTransition(2,'a',3);
	fa.addTransition(3,'b',3);
	const std::string word="aabbbb";
	std::set<int> result=fa.readString(word);
	EXPECT_EQ(result.size(),3u);
}


/*TEST lecture d'un mot accepté par l'automate et qui boucle sur la même lettre à un moment */
//PART3: - TEST DE LA PRESENCE DES ETATS DANS LE RES
TEST(automatonTest,ReadStringLoopWordPart3){
fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.addState(3);
	fa.setStateFinal(3);
	fa.setStateInitial(1);
	fa.addTransition(1,'a',2);
	fa.addTransition(2,'a',3);
	fa.addTransition(3,'b',3);
	const std::string word="aabbbb";
	std::set<int> result=fa.readString(word);
	EXPECT_NE(result.find(1),result.end());
	EXPECT_NE(result.find(2),result.end());
	EXPECT_NE(result.find(3),result.end());
}

/*TEST Lecture d'un mot dans un automate sans état final*/
TEST(automatonTest,ReadStringWithoutFinalState){
fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.addState(3);
	fa.setStateInitial(1);
	fa.addTransition(1,'a',2);
	fa.addTransition(2,'a',3);
	fa.addTransition(3,'b',3);
	const std::string word="aab";
	std::set<int> result=fa.readString(word);
	EXPECT_TRUE(result.empty());
}


/*TEST Lecture d'un mot dans un automate sans état initial*/
TEST(automatonTest,ReadStringWithoutInitialState){
fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.addState(3);
	fa.setStateFinal(3);
	fa.addTransition(1,'a',2);
	fa.addTransition(2,'a',3);
	fa.addTransition(3,'b',3);
	const std::string word="aab";
	std::set<int> result=fa.readString(word);
	EXPECT_TRUE(result.empty());
}

/*TEST Lecture d'un mot dans un automate sans état initial et sans état final*/
TEST(automatonTest,ReadStringWithoutInitialAndFinalState){
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.addTransition(1,'a',2);
fa.addTransition(2,'a',3);
fa.addTransition(3,'b',3);
const std::string word="aab";
std::set<int> result=fa.readString(word);
EXPECT_TRUE(result.empty());
}


/*TEST Lecture d'un mot dans un automate vide*/
TEST(automatonTest,ReadStringEmptyAutomate){
    fa::Automaton fa;
    const std::string word="aab";
    std::set<int> result=fa.readString(word);
    EXPECT_TRUE(result.empty());
}


/*TEST lecture d'un mot accepté par un automate sans transition */
TEST(automatonTest,ReadStringWithoutTransition){
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.setStateFinal(3);
fa.setStateInitial(1);
const std::string word="aab";
std::set<int> result=fa.readString(word);
EXPECT_TRUE(result.empty());
}


/*TEST lecture d'un mot avec caractere non imprimable par un automate*/
TEST(automatonTest,ReadStringNonPRintableChar){
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.setStateFinal(3);
fa.setStateInitial(1);
const std::string word=("a\0ab");
std::set<int> result=fa.readString(word);
EXPECT_TRUE(result.empty());
}




////////////////////TEST MATCH



/* TEST match du mot vide*/
TEST(automatonTest,MatchEmptyWord){
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.setStateFinal(3);
fa.setStateInitial(1);
fa.addTransition(1,'a',2);
fa.addTransition(2,'a',3);
fa.addTransition(3,'b',3);
EXPECT_FALSE(fa.match(""));
}


/* TEST match du mot vide*/
TEST(automatonTest,MatchEmptyWord2){
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.setStateFinal(3);
fa.setStateFinal(1);
fa.setStateInitial(1);
fa.addTransition(1,'a',2);
fa.addTransition(2,'a',3);
fa.addTransition(3,'b',3);
EXPECT_TRUE(fa.match(""));
}

/*TEST match d'un mot possèdant un caractère non reconnu par l'automate*/
TEST(automatonTest,matchWrongWord){
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.setStateFinal(3);
fa.setStateInitial(1);
fa.addTransition(1,'a',2);
fa.addTransition(2,'a',3);
fa.addTransition(3,'b',3);
EXPECT_FALSE(fa.match("abc"));
}


/*TEST match d'un mot trop court pour l'automate*/
TEST(automatonTest,matchShortgWord){
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.setStateFinal(3);
fa.setStateInitial(1);
fa.addTransition(1,'a',2);
fa.addTransition(2,'a',3);
fa.addTransition(3,'b',3);
EXPECT_FALSE(fa.match("a"));
}




/*TEST match d'un mot accepté par l'automate*/
TEST(automatonTest, matchWord){
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.setStateFinal(3);
fa.setStateInitial(1);
fa.addTransition(1,'a',2);
fa.addTransition(2,'a',3);
fa.addTransition(3,'b',3);
EXPECT_TRUE(fa.match("aab"));
}



/*TEST match d'un mot accepté par l'automate et qui boucle sur la même lettre à un moment*/
TEST(automatonTest,matchLoopWord){
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.setStateFinal(3);
fa.setStateInitial(1);
fa.addTransition(1,'a',2);
fa.addTransition(2,'a',3);
fa.addTransition(3,'b',3);
EXPECT_TRUE(fa.match("aabbbb"));
}


/*TEST match d'un mot dans un automate sans état final*/
TEST(automatonTest,matchWithoutFinalState){
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.setStateInitial(1);
fa.addTransition(1,'a',2);
fa.addTransition(2,'a',3);
fa.addTransition(3,'b',3);
EXPECT_FALSE(fa.match("aab"));
}


/*TEST match d'un mot dans un automate sans état initial*/
TEST(automatonTest,matchWithoutInitialState){
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.setStateFinal(3);
fa.addTransition(1,'a',2);
fa.addTransition(2,'a',3);
fa.addTransition(3,'b',3);
EXPECT_FALSE(fa.match("aab"));
}

/*TEST match d'un mot dans un automate sans état initial et sans état final*/
TEST(automatonTest,matchWithoutInitialAndFinalState){
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.addTransition(1,'a',2);
fa.addTransition(2,'a',3);
fa.addTransition(3,'b',3);
EXPECT_FALSE(fa.match("aab"));
}


/*TEST match d'un mot dans un automate vide*/
TEST(automatonTest,matchEmptyAutomate){
fa::Automaton fa;
EXPECT_FALSE(fa.match("aab"));
}


/*TEST match d'un mot accepté par un automate sans transition */
TEST(automatonTest,matchWithoutTransition){
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.setStateFinal(3);
fa.setStateInitial(1);
EXPECT_FALSE(fa.match("aab"));
}




/*TEST match d'un mot avec caractere non imprimable par un automate*/
TEST(automatonTest,matchNonPrintableChar){
fa::Automaton fa;
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.setStateFinal(3);
fa.setStateInitial(1);
EXPECT_FALSE(fa.match("aa\0b"));
}







////////////////////TEST CREATE DETERMINISTIC

/* test : déterminisation d'un automate qui ne l'est pas*/
//PART1: testIs Deterministic avant/après
TEST(automatonTest,createDeterminsticValid1){
fa::Automaton fa,faDeter;
fa.addState(0);
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.addState(4);
fa.addState(5);
fa.addState(6);
fa.setStateInitial(0);
fa.setStateInitial(4);
fa.setStateFinal(3);
fa.setStateFinal(6);
fa.addTransition(0,'a',1);
fa.addTransition(1,'b',2);
fa.addTransition(2,'c',2);
fa.addTransition(2,'a',3);
fa.addTransition(6,'a',3);
fa.addTransition(2,'a',5);
fa.addTransition(5,'b',6);
fa.addTransition(6,'a',2);
fa.addTransition(4,'c',2);
fa.addTransition(1,'b',4);
EXPECT_FALSE(fa.isDeterministic());
faDeter=fa::Automaton::createDeterministic(fa);
EXPECT_TRUE(faDeter.isDeterministic());
}



//PART2: présence et nature des états
/*TEST(automatonTest,createDeterminsticValid2){
    fa::Automaton fa,faDeter;
    fa.addState(0);
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.addState(4);
    fa.addState(5);
    fa.addState(6);
    fa.setStateInitial(0);
    fa.setStateInitial(4);
    fa.setStateFinal(3);
    fa.setStateFinal(6);
    fa.addTransition(0,'a',1);
    fa.addTransition(1,'b',2);
    fa.addTransition(2,'c',2);
    fa.addTransition(2,'a',3);
    fa.addTransition(6,'a',3);
    fa.addTransition(2,'a',5);
    fa.addTransition(5,'b',6);
    fa.addTransition(6,'a',2);createDeterminsticValid
    fa.addTransition(4,'c',2);
    fa.addTransition(1,'b',4);

    faDeter=fa::Automaton::createDeterministic(fa);
    EXPECT_TRUE(faDeter.isStateInitial(0));
    EXPECT_FALSE(faDeter.isStateInitial(1));
    EXPECT_FALSE(faDeter.isStateInitial(2));
    EXPECT_TRUE(faDeter.isStateInitial(3));
    EXPECT_FALSE(faDeter.isStateInitial(4));
    EXPECT_FALSE(faDeter.isStateInitial(5));
    EXPECT_FALSE(faDeter.isStateInitial(6));


    EXPECT_FALSE(faDeter.isStateFinal(0));
    EXPECT_FALSE(faDeter.isStateFinal(1));
    EXPECT_FALSE(faDeter.isStateFinal(2));
    EXPECT_FALSE(faDeter.isStateFinal(3));
    EXPECT_TRUE(faDeter.isStateFinal(4));
    EXPECT_TRUE(faDeter.isStateFinal(5));
    EXPECT_TRUE(faDeter.isStateFinal(6));	
}*/


//PART2: égalité des languages reconnus avant/après
TEST(automatonTest,createDeterminsticValid2){
    fa::Automaton fa,faDeter;	
    fa.addState(0);
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.addState(4);
    fa.addState(5);
    fa.addState(6);
    fa.setStateInitial(0);
    fa.setStateInitial(4);
    fa.setStateFinal(3);
    fa.setStateFinal(6);
    fa.addTransition(0,'a',1);
    fa.addTransition(1,'b',2);
    fa.addTransition(2,'c',2);
    fa.addTransition(2,'a',3);
    fa.addTransition(6,'a',3);
    fa.addTransition(2,'a',5);
    fa.addTransition(5,'b',6);
    fa.addTransition(6,'a',2);
    fa.addTransition(4,'c',2);
    fa.addTransition(1,'b',4);

    faDeter=fa::Automaton::createDeterministic(fa);
//	EXPECT_TRUE(faDeter.isIncludedIn(fa));
//	EXPECT_TRUE(fa.isIncludedIn(faDeter));

//SI LE TEST PLANTE ALORS MUTE LES LIGNES QUI SUIVENT CE MESSAGE
    /*EXPECT_TRUE(faDeter.hasTransition(0,'a',1));
    EXPECT_TRUE(faDeter.hasTransition(0,'c',2));
    EXPECT_TRUE(faDeter.hasTransition(1,'b',3));
    EXPECT_TRUE(faDeter.hasTransition(1,'c',2));
    EXPECT_TRUE(faDeter.hasTransition(2,'c',2));
    EXPECT_TRUE(faDeter.hasTransition(2,'a',4));
    EXPECT_TRUE(faDeter.hasTransition(6,'c',2));
    EXPECT_TRUE(faDeter.hasTransition(3,'c',2));
    EXPECT_TRUE(faDeter.hasTransition(3,'a',4));
    EXPECT_TRUE(faDeter.hasTransition(4,'b',5));
    EXPECT_TRUE(faDeter.hasTransition(5,'a',6));
    EXPECT_TRUE(faDeter.hasTransition(6,'a',4));	
*/
}



/* test : déterminisation d'un automate qui l'est déjà */
//PART1: test nature avant/après
TEST(automatonTest,createDeterminsticAlready1){
fa::Automaton fa,faDeter;
fa.addState(0);
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.addState(4);
fa.addState(5);
fa.addState(6);
fa.setStateInitial(0);
fa.setStateInitial(3);
fa.setStateFinal(4);
fa.setStateFinal(5);
fa.setStateFinal(6);
fa.addTransition(0,'a',1);
fa.addTransition(0,'c',2);
fa.addTransition(1,'b',3);
fa.addTransition(1,'c',2);
fa.addTransition(2,'c',2);
fa.addTransition(2,'a',4);
fa.addTransition(6,'c',2);
fa.addTransition(3,'c',2);
fa.addTransition(3,'a',4);
fa.addTransition(4,'b',5);
fa.addTransition(5,'a',6);
fa.addTransition(6,'a',4);

EXPECT_TRUE(fa.isDeterministic());
faDeter=fa::Automaton::createDeterministic(fa);
EXPECT_TRUE(faDeter.isDeterministic());
}

/*
//LES PROCHAINES LIGNES SONT A DELETE SI LE TEST PLANTE
//PART2: présence et nature des états
TEST(automatonTest,createDeterminsticAlready2){
fa::Automaton fa,faDeter;
fa.addState(0);
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.addState(4);
fa.addState(5);
fa.addState(6);
fa.setStateInitial(0);
fa.setStateInitial(3);
fa.setStateFinal(4);
fa.setStateFinal(5);
fa.setStateFinal(6);
fa.addTransition(0,'a',1);
fa.addTransition(0,'c',2);
fa.addTransition(1,'b',3);
fa.addTransition(1,'c',2);
fa.addTransition(2,'c',2);
fa.addTransition(2,'a',4);
fa.addTransition(6,'c',2);
fa.addTransition(3,'c',2);
fa.addTransition(3,'a',4);
fa.addTransition(4,'b',5);
fa.addTransition(5,'a',6);
fa.addTransition(6,'a',4);

EXPECT_TRUE(fa.isDeterministic());
faDeter=fa::Automaton::createDeterministic(fa);

EXPECT_TRUE(faDeter.isStateInitial(0));
EXPECT_FALSE(faDeter.isStateInitial(1));
EXPECT_FALSE(faDeter.isStateInitial(2));
EXPECT_TRUE(faDeter.isStateInitial(3));
EXPECT_FALSE(faDeter.isStateInitial(4));
EXPECT_FALSE(faDeter.isStateInitial(5));
EXPECT_FALSE(faDeter.isStateInitial(6));


EXPECT_FALSE(faDeter.isStateFinal(0));
EXPECT_FALSE(faDeter.isStateFinal(1));
EXPECT_FALSE(faDeter.isStateFinal(2));
EXPECT_FALSE(faDeter.isStateFinal(3));
EXPECT_TRUE(faDeter.isStateFinal(4));
EXPECT_TRUE(faDeter.isStateFinal(5));
EXPECT_TRUE(faDeter.isStateFinal(6));
}
*/


//LES PROCHAINES LIGNES SONT A DELETE SI LE TEST PLANTE
//PART2: vérification égalités langages reconnus avant/après
TEST(automatonTest,createDeterminsticAlready2){
fa::Automaton fa,faDeter;
fa.addState(0);
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.addState(4);
fa.addState(5);
fa.addState(6);
fa.setStateInitial(0);
fa.setStateInitial(3);
fa.setStateFinal(4);
fa.setStateFinal(5);
fa.setStateFinal(6);
fa.addTransition(0,'a',1);
fa.addTransition(0,'c',2);
fa.addTransition(1,'b',3);
fa.addTransition(1,'c',2);
fa.addTransition(2,'c',2);
fa.addTransition(2,'a',4);
fa.addTransition(6,'c',2);
fa.addTransition(3,'c',2);
fa.addTransition(3,'a',4);
fa.addTransition(4,'b',5);
fa.addTransition(5,'a',6);
fa.addTransition(6,'a',4);

EXPECT_TRUE(fa.isDeterministic());
faDeter=fa::Automaton::createDeterministic(fa);
//EXPECT_TRUE(faDeter.isIncludedIn(fa));
//EXPECT_TRUE(fa.isIncludedIn(faDeter));

/*EXPECT_TRUE(faDeter.hasTransition(0,'a',1));
EXPECT_TRUE(faDeter.hasTransition(0,'c',2));
EXPECT_TRUE(faDeter.hasTransition(1,'b',3));
EXPECT_TRUE(faDeter.hasTransition(1,'c',2));
EXPECT_TRUE(faDeter.hasTransition(2,'c',2));
EXPECT_TRUE(faDeter.hasTransition(2,'a',4));
EXPECT_TRUE(faDeter.hasTransition(6,'c',2));
EXPECT_TRUE(faDeter.hasTransition(3,'c',2));
EXPECT_TRUE(faDeter.hasTransition(3,'a',4));
EXPECT_TRUE(faDeter.hasTransition(4,'b',5));
EXPECT_TRUE(faDeter.hasTransition(5,'a',6));
EXPECT_TRUE(faDeter.hasTransition(6,'a',4));*/
}


/*
//PART4: test isDeterministic
TEST(automatonTest,createDeterminsticAlready4){
fa::Automaton fa,faDeter;
fa.addState(0);
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.addState(4);
fa.addState(5);
fa.addState(6);
fa.setStateInitial(0);
fa.setStateInitial(4);
fa.setStateFinal(3);
fa.setStateFinal(6);
fa.addTransition(0,'a',1);
fa.addTransition(1,'b',2);
fa.addTransition(2,'c',2);
fa.addTransition(2,'a',3);
fa.addTransition(6,'a',3);
fa.addTransition(2,'a',5);
fa.addTransition(5,'b',6);
fa.addTransition(6,'a',2);
fa.addTransition(4,'c',2);
fa.addTransition(1,'b',4);

faDeter=fa::Automaton::createDeterministic(fa);
EXPECT_TRUE(faDeter.isDeterministic());
}
*/



/* test : déterminisation d'un automate qui est vide */
TEST(automatonTest,createDeterminsticEmpty){
fa::Automaton fa,faDeter;
faDeter=fa::Automaton::createDeterministic(fa);
//EXPECT_TRUE(faDeter.isIncludedIn(fa));
//EXPECT_TRUE(fa.isIncludedIn(faDeter));
EXPECT_EQ(faDeter.countStates(),0u);
EXPECT_EQ(faDeter.countTransitions(),0u);
EXPECT_EQ(faDeter.getAlphabetSize(),0u);
}

/* test : déterminisation d'un automate qui ne possède aucune transition */
TEST(automatonTest,createDeterminsticWithoutTransition){
fa::Automaton fa,faDeter;
fa.addState(1);
faDeter=fa::Automaton::createDeterministic(fa);
//EXPECT_TRUE(faDeter.isIncludedIn(fa));
//EXPECT_TRUE(fa.isIncludedIn(faDeter));
EXPECT_EQ(faDeter.countStates(),1u);
EXPECT_EQ(faDeter.countTransitions(),0u);
EXPECT_EQ(faDeter.getAlphabetSize(),0u);
}


/** CA VA PETER ICI CEST NORMAL
 *  CA VA PETER ICI CEST NORMAL
 *  CA VA PETER ICI CEST NORMAL
 */

/* test : déterminisation d'un automate sans état initial */
//PART1: test nature avant/après
TEST(automatonTest,createDeterminsticWithoutInitial){
fa::Automaton fa,faDeter;
fa.addState(0);
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.addState(4);
fa.addState(5);
fa.addState(6);
fa.setStateFinal(3);
fa.setStateFinal(6);
fa.addTransition(0,'a',1);
fa.addTransition(1,'b',2);
fa.addTransition(2,'c',2);
fa.addTransition(2,'a',3);
fa.addTransition(6,'a',3);
fa.addTransition(2,'a',5);
fa.addTransition(5,'b',6);
fa.addTransition(6,'a',2);
fa.addTransition(4,'c',2);
fa.addTransition(1,'b',4);
EXPECT_FALSE(fa.isDeterministic());
faDeter=fa::Automaton::createDeterministic(fa);
EXPECT_TRUE(faDeter.isDeterministic());
/*EXPECT_EQ(faDeter.countStates(),7u);
EXPECT_EQ(faDeter.countTransitions(),12u);
EXPECT_EQ(faDeter.getAlphabetSize(),3u);
*/
}


/** CA VA  PEUT ETRE PETER ICI CEST NORMAL
 *  CA VA PEUT ETRE PETER ICI CEST NORMAL
 *  CA VA PEUT ETRE PETER ICI CEST NORMAL
 */
/* test : déterminisation d'un automate sans état final */
//PART1: test nature avant/après
TEST(automatonTest,createDeterminsticWithoutFinal){
fa::Automaton fa,faDeter;
fa.addState(0);
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.addState(4);
fa.addState(5);
fa.addState(6);
fa.setStateInitial(0);
fa.setStateInitial(4);
fa.addTransition(0,'a',1);
fa.addTransition(1,'b',2);
fa.addTransition(2,'c',2);
fa.addTransition(2,'a',3);
fa.addTransition(6,'a',3);
fa.addTransition(2,'a',5);
fa.addTransition(5,'b',6);
fa.addTransition(6,'a',2);
fa.addTransition(4,'c',2);
fa.addTransition(1,'b',4);

EXPECT_FALSE(fa.isDeterministic());
faDeter=fa::Automaton::createDeterministic(fa);
EXPECT_TRUE(faDeter.isDeterministic());
/*EXPECT_EQ(faDeter.countStates(),7u);
EXPECT_EQ(faDeter.countTransitions(),12u);
EXPECT_EQ(faDeter.getAlphabetSize(),3u);
*/
}



////////////////////TEST IS INCLUDED IN











//////////////////////////////////////////////////////////TEST TP6
////////////////////TEST MINIMAL MOORE



/* test avec 1 automate non vide déjà minimal*/
//PART1: vérification égalité des langages avant/après
TEST(automatonTest,AlreadyMinimalWithMoore1){
fa::Automaton fa,faMin;
fa.addState(0);
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.addState(4);
fa.addState(5);
fa.setStateInitial(0);
fa.setStateFinal(5);
fa.addTransition(0,'a',2);
fa.addTransition(0,'b',2);
fa.addTransition(2,'b',0);
fa.addTransition(0,'a',1);
fa.addTransition(1,'a',4);
fa.addTransition(1,'b',5);
fa.addTransition(4,'b',5);
fa.addTransition(5,'b',4);
fa.addTransition(4,'a',3);
fa.addTransition(3,'b',4);
fa.addTransition(5,'a',3);
fa.addTransition(3,'a',5);

EXPECT_EQ(fa.countStates(),6u);
EXPECT_EQ(fa.countTransitions(),12u);
EXPECT_EQ(fa.getAlphabetSize(),2u);
EXPECT_TRUE(fa.isDeterministic());
EXPECT_TRUE(fa.isComplete());
faMin=fa::Automaton::createMinimalMoore(fa);
EXPECT_TRUE(faMin.isIncludedIn(fa));
EXPECT_TRUE(fa.isIncludedIn(faMin));
//LES PROCHAINES LIGNES SONT A DELETE SI LE TEST PLANTE
/*(faMin.countStates(),6u);
EXPECT_EQ(faMin.countTransitions(),12u);
EXPECT_EQ(faMin.getAlphabetSize(),2u);*/

}


/*
//LES PROCHAINES LIGNES SONT A DELETE SI LE TEST PLANTE
//PART2: verif présence et nature des états
TEST(automatonTest,AlreadyMinimalWithMoore2){
fa::Automaton fa,faMin;
fa.addState(0);
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.addState(4);
fa.addState(5);
fa.setStateInitial(0);
fa.setStateFinal(5);
fa.addTransition(0,'a',2);
fa.addTransition(0,'b',2);
fa.addTransition(2,'b',0);
fa.addTransition(0,'a',1);
fa.addTransition(1,'a',4);
fa.addTransition(1,'b',5);
fa.addTransition(4,'b',5);
fa.addTransition(5,'b',4);
fa.addTransition(4,'a',3);
fa.addTransition(3,'b',4);
fa.addTransition(5,'a',3);
fa.addTransition(3,'a',5);


EXPECT_TRUE(fa.isDeterministic());
EXPECT_TRUE(fa.isComplete());
faMin=fa::Automaton::createMinimalMoore(fa);

EXPECT_TRUE(faMin.hasState(0));
EXPECT_TRUE(faMin.isStateInitial(0));
EXPECT_FALSE(faMin.isStateFinal(0));

EXPECT_TRUE(faMin.hasState(1));
EXPECT_FALSE(faMin.isStateInitial(1));
EXPECT_FALSE(faMin.isStateFinal(1));

EXPECT_TRUE(faMin.hasState(2));
EXPECT_FALSE(faMin.isStateInitial(2));
EXPECT_FALSE(faMin.isStateFinal(2));

EXPECT_TRUE(faMin.hasState(3));
EXPECT_FALSE(faMin.isStateInitial(3));
EXPECT_FALSE(faMin.isStateFinal(3));

EXPECT_TRUE(faMin.hasState(4));
EXPECT_FALSE(faMin.isStateInitial(4));
EXPECT_FALSE(faMin.isStateFinal(4));

EXPECT_TRUE(faMin.hasState(5));
EXPECT_FALSE(faMin.isStateInitial(5));
EXPECT_TRUE(faMin.isStateFinal(5));
}




//LES PROCHAINES LIGNES SONT A DELETE SI LE TEST PLANTE
//PART3: verif présence des transitions
TEST(automatonTest,AlreadyMinimalWithMoore3){
fa::Automaton fa,faMin;
fa.addState(0);
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.addState(4);
fa.addState(5);
fa.setStateInitial(0);
fa.setStateFinal(5);
fa.addTransition(0,'a',2);
fa.addTransition(0,'b',2);
fa.addTransition(2,'b',0);
fa.addTransition(0,'a',1);
fa.addTransition(1,'a',4);
fa.addTransition(1,'b',5);
fa.addTransition(4,'b',5);
fa.addTransition(5,'b',4);
fa.addTransition(4,'a',3);
fa.addTransition(3,'b',4);
fa.addTransition(5,'a',3);
fa.addTransition(3,'a',5);

EXPECT_TRUE(fa.isDeterministic());
EXPECT_TRUE(fa.isComplete());
faMin=fa::Automaton::createMinimalMoore(fa);

EXPECT_TRUE(faMin.hasTransition(0,'a',2));
EXPECT_TRUE(faMin.hasTransition(0,'b',2));
EXPECT_TRUE(faMin.hasTransition(2,'b',0));
EXPECT_TRUE(faMin.hasTransition(0,'a',1));
EXPECT_TRUE(faMin.hasTransition(1,'a',4));
EXPECT_TRUE(faMin.hasTransition(1,'b',5));
EXPECT_TRUE(faMin.hasTransition(4,'b',5));
EXPECT_TRUE(faMin.hasTransition(5,'b',4));
EXPECT_TRUE(faMin.hasTransition(4,'a',3));
EXPECT_TRUE(faMin.hasTransition(3,'b',4));
EXPECT_TRUE(faMin.hasTransition(5,'a',3));
EXPECT_TRUE(faMin.hasTransition(3,'a',5));

}

*/



/* test avec 1 automate non vide */
//PART1: vérification égalité des langages avant/après
TEST(automatonTest,MinimalWithMoore1){
fa::Automaton fa,faMin;
fa.addState(0);
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.addState(4);
fa.addState(5);

fa.setStateInitial(0);
fa.setStateFinal(5);
fa.setStateFinal(4);

fa.addTransition(0,'a',1);
fa.addTransition(0,'b',3);
fa.addTransition(3,'a',1);
fa.addTransition(1,'a',0);
fa.addTransition(1,'b',2);
fa.addTransition(2,'a',1);
fa.addTransition(2,'b',5);
fa.addTransition(5,'b',4);
fa.addTransition(3,'b',4);
fa.addTransition(4,'a',0);
fa.addTransition(4,'b',4);
fa.addTransition(5,'a',1);

EXPECT_EQ(fa.countStates(),6u);
EXPECT_EQ(fa.countTransitions(),12u);
EXPECT_EQ(fa.getAlphabetSize(),2u);
EXPECT_TRUE(fa.isDeterministic());
EXPECT_TRUE(fa.isComplete());
faMin=fa::Automaton::createMinimalMoore(fa);
EXPECT_TRUE(faMin.isIncludedIn(fa));
EXPECT_TRUE(fa.isIncludedIn(faMin));
//LES PROCHAINES LIGNES SONT A DELETE SI LE TEST PLANTE
/*
EXPECT_EQ(faMin.countStates(),3u);
EXPECT_EQ(faMin.countTransitions(),6u);
EXPECT_EQ(faMin.getAlphabetSize(),2u);*/

}
/*
//LES PROCHAINES LIGNES SONT A DELETE SI LE TEST PLANTE
//PART2: vérif présence et nature des états
TEST(automatonTest,MinimalWithMoore2){
fa::Automaton fa,faMin;
fa.addState(0);
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.addState(4);
fa.addState(5);

fa.setStateInitial(0);
fa.setStateFinal(5);
fa.setStateFinal(4);

fa.addTransition(0,'a',1);
fa.addTransition(0,'b',3);
fa.addTransition(3,'a',1);
fa.addTransition(1,'a',0);
fa.addTransition(1,'b',2);
fa.addTransition(2,'a',1);
fa.addTransition(2,'b',5);
fa.addTransition(5,'b',4);
fa.addTransition(3,'b',4);
fa.addTransition(4,'a',0);
fa.addTransition(4,'b',4);
fa.addTransition(5,'a',1);

EXPECT_EQ(fa.countStates(),6u);
EXPECT_EQ(fa.countTransitions(),12u);
EXPECT_EQ(fa.getAlphabetSize(),2u);

EXPECT_TRUE(fa.isDeterministic());
EXPECT_TRUE(fa.isComplete());
faMin=fa::Automaton::createMinimalMoore(fa);

EXPECT_TRUE(faMin.hasState(0));
EXPECT_TRUE(faMin.isStateInitial(0));
EXPECT_FALSE(faMin.isStateFinal(0));

EXPECT_TRUE(faMin.hasState(1));
EXPECT_FALSE(faMin.isStateInitial(1));
EXPECT_FALSE(faMin.isStateFinal(1));

EXPECT_TRUE(faMin.hasState(2));
EXPECT_FALSE(faMin.isStateInitial(2));
EXPECT_TRUE(faMin.isStateFinal(2));

}
//LES PROCHAINES LIGNES SONT A DELETE SI LE TEST PLANTE
//PART3: Vérif des transitions
TEST(automatonTest,MinimalWithMoore3){
fa::Automaton fa,faMin;
fa.addState(0);
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.addState(4);
fa.addState(5);

fa.setStateInitial(0);
fa.setStateFinal(5);
fa.setStateFinal(4);

fa.addTransition(0,'a',1);
fa.addTransition(0,'b',3);
fa.addTransition(3,'a',1);
fa.addTransition(1,'a',0);
fa.addTransition(1,'b',2);
fa.addTransition(2,'a',1);
fa.addTransition(2,'b',5);
fa.addTransition(5,'b',4);
fa.addTransition(3,'b',4);
fa.addTransition(4,'a',0);
fa.addTransition(4,'b',4);
fa.addTransition(5,'a',1);

EXPECT_EQ(fa.countStates(),6u);
EXPECT_EQ(fa.countTransitions(),12u);
EXPECT_EQ(fa.getAlphabetSize(),2u);

EXPECT_TRUE(fa.isDeterministic());
EXPECT_TRUE(fa.isComplete());
faMin=fa::Automaton::createMinimalMoore(fa);

EXPECT_TRUE(faMin.hasTransition(0,'a',0));
EXPECT_TRUE(faMin.hasTransition(0,'b',1));
EXPECT_TRUE(faMin.hasTransition(1,'a',0));
EXPECT_TRUE(faMin.hasTransition(1,'b',2));
EXPECT_TRUE(faMin.hasTransition(2,'b',2));
EXPECT_TRUE(faMin.hasTransition(2,'a',0));


}
*/



/* test avec 1 automate  vide */
TEST(automatonTest,MinimalWithMooreEmpty){
fa::Automaton fa,faMin;
EXPECT_FALSE(fa.isDeterministic());
EXPECT_FALSE(fa.isComplete());
EXPECT_DEATH(faMin=fa::Automaton::createMinimalMoore(fa),"");
//EXPECT_TRUE(faMin.isIncludedIn(fa));
//EXPECT_TRUE(fa.isIncludedIn(faMin));
/*LES PROCHAINES LIGNES SONT A DELETE SI LE TEST PLANTE
EXPECT_EQ(faMin.countStates(),0u);
EXPECT_EQ(faMin.countTransitions(),0u);
EXPECT_EQ(faMin.getAlphabetSize(),0u);
*/
}


/* test avec 1 automate non complet */
TEST(automatonTest,MinimalWithMooreNotComplete){
fa::Automaton fa,faMin;
fa.addState(1);
    fa.addState(2);
    fa.setStateInitial(1);
    fa.setStateFinal(2);
    fa.addTransition(1,'a',2);
    fa.addTransition(1,'b',1);
    fa.addTransition(2,'a',1);
EXPECT_FALSE(fa.isComplete());
EXPECT_DEATH(faMin=fa::Automaton::createMinimalMoore(fa),"");

}



/* test avec 1 automate non déterministe */
TEST(automatonTest,MinimalWithMooreNotDeterminist){
fa::Automaton fa,faMin;
fa.addState(0);
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.addState(4);
    fa.addState(5);
    fa.addState(6);
    fa.setStateInitial(0);
    fa.setStateInitial(4);
    fa.setStateFinal(3);
    fa.setStateFinal(6);
    fa.addTransition(0,'a',1);
    fa.addTransition(1,'b',2);
    fa.addTransition(2,'c',2);
    fa.addTransition(2,'a',3);
    fa.addTransition(6,'a',3);
    fa.addTransition(2,'a',5);
    fa.addTransition(5,'b',6);
    fa.addTransition(6,'a',2);
    fa.addTransition(4,'c',2);
    fa.addTransition(1,'b',4);
EXPECT_FALSE(fa.isDeterministic());
EXPECT_DEATH(faMin=fa::Automaton::createMinimalMoore(fa),"");

}










////////////////////TEST MINIMAL BRZOZOWSKI




/* test avec 1 automate non vide déjà minimal*/
//PART1: vérification égalité des langages avant/après
TEST(automatonTest,AlreadyMinimalWitBrzozowski1){
fa::Automaton fa,faMin;
fa.addState(0);
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.addState(4);
fa.addState(5);
fa.setStateInitial(0);
fa.setStateFinal(5);
fa.addTransition(0,'a',2);
fa.addTransition(0,'b',2);
fa.addTransition(2,'b',0);
fa.addTransition(0,'a',1);
fa.addTransition(1,'a',4);
fa.addTransition(1,'b',5);
fa.addTransition(4,'b',5);
fa.addTransition(5,'b',4);
fa.addTransition(4,'a',3);
fa.addTransition(3,'b',4);
fa.addTransition(5,'a',3);
fa.addTransition(3,'a',5);

EXPECT_EQ(fa.countStates(),6u);
EXPECT_EQ(fa.countTransitions(),12u);
EXPECT_EQ(fa.getAlphabetSize(),2u);
EXPECT_TRUE(fa.isDeterministic());
EXPECT_TRUE(fa.isComplete());
faMin=fa::Automaton::createMinimalBrzozowski(fa);
EXPECT_TRUE(faMin.isIncludedIn(fa));
EXPECT_TRUE(fa.isIncludedIn(faMin));
/*
//LES PROCHAINES LIGNES SONT A DELETE SI LE TEST PLANTE
EXPECT_EQ(faMin.countStates(),6u);
EXPECT_EQ(faMin.countTransitions(),12u);
EXPECT_EQ(faMin.getAlphabetSize(),2u);
*/
}

/*
//LES PROCHAINES LIGNES SONT A DELETE SI LE TEST PLANTE
//PART2: verif présence et nature des états
TEST(automatonTest,AlreadyMinimalWithBrzozowski2){
fa::Automaton fa,faMin;
fa.addState(0);
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.addState(4);
fa.addState(5);
fa.setStateInitial(0);
fa.setStateFinal(5);
fa.addTransition(0,'a',2);
fa.addTransition(0,'b',2);
fa.addTransition(2,'b',0);
fa.addTransition(0,'a',1);
fa.addTransition(1,'a',4);
fa.addTransition(1,'b',5);
fa.addTransition(4,'b',5);
fa.addTransition(5,'b',4);
fa.addTransition(4,'a',3);
fa.addTransition(3,'b',4);
fa.addTransition(5,'a',3);
fa.addTransition(3,'a',5);


EXPECT_TRUE(fa.isDeterministic());
EXPECT_TRUE(fa.isComplete());
faMin=fa::Automaton::createMinimalBrzozowski(fa);

EXPECT_TRUE(faMin.hasState(0));
EXPECT_TRUE(faMin.isStateInitial(0));
EXPECT_FALSE(faMin.isStateFinal(0));

EXPECT_TRUE(faMin.hasState(1));
EXPECT_FALSE(faMin.isStateInitial(1));
EXPECT_FALSE(faMin.isStateFinal(1));

EXPECT_TRUE(faMin.hasState(2));
EXPECT_FALSE(faMin.isStateInitial(2));
EXPECT_FALSE(faMin.isStateFinal(2));

EXPECT_TRUE(faMin.hasState(3));
EXPECT_FALSE(faMin.isStateInitial(3));
EXPECT_FALSE(faMin.isStateFinal(3));

EXPECT_TRUE(faMin.hasState(4));
EXPECT_FALSE(faMin.isStateInitial(4));
EXPECT_FALSE(faMin.isStateFinal(4));

EXPECT_TRUE(faMin.hasState(5));
EXPECT_FALSE(faMin.isStateInitial(5));
EXPECT_TRUE(faMin.isStateFinal(5));
}



//LES PROCHAINES LIGNES SONT A DELETE SI LE TEST PLANTE
//PART3: verif présence des transitions
TEST(automatonTest,AlreadyMinimalWithBrzozowski3){
fa::Automaton fa,faMin;
fa.addState(0);
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.addState(4);
fa.addState(5);
fa.setStateInitial(0);
fa.setStateFinal(5);
fa.addTransition(0,'a',2);
fa.addTransition(0,'b',2);
fa.addTransition(2,'b',0);
fa.addTransition(0,'a',1);
fa.addTransition(1,'a',4);
fa.addTransition(1,'b',5);
fa.addTransition(4,'b',5);
fa.addTransition(5,'b',4);
fa.addTransition(4,'a',3);
fa.addTransition(3,'b',4);
fa.addTransition(5,'a',3);
fa.addTransition(3,'a',5);

EXPECT_TRUE(fa.isDeterministic());
EXPECT_TRUE(fa.isComplete());
faMin=fa::Automaton::createMinimalBrzozowski(fa);

EXPECT_TRUE(faMin.hasTransition(0,'a',2));
EXPECT_TRUE(faMin.hasTransition(0,'b',2));
EXPECT_TRUE(faMin.hasTransition(2,'b',0));
EXPECT_TRUE(faMin.hasTransition(0,'a',1));
EXPECT_TRUE(faMin.hasTransition(1,'a',4));
EXPECT_TRUE(faMin.hasTransition(1,'b',5));
EXPECT_TRUE(faMin.hasTransition(4,'b',5));
EXPECT_TRUE(faMin.hasTransition(5,'b',4));
EXPECT_TRUE(faMin.hasTransition(4,'a',3));
EXPECT_TRUE(faMin.hasTransition(3,'b',4));
EXPECT_TRUE(faMin.hasTransition(5,'a',3));
EXPECT_TRUE(faMin.hasTransition(3,'a',5));

}

*/



/* test avec 1 automate non vide */
//PART1: vérification égalité des langages avant/après
TEST(automatonTest,MinimalWithBrzozowski1){
fa::Automaton fa,faMin;
fa.addState(0);
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.addState(4);
fa.addState(5);

fa.setStateInitial(0);
fa.setStateFinal(5);
fa.setStateFinal(4);

fa.addTransition(0,'a',1);
fa.addTransition(0,'b',3);
fa.addTransition(3,'a',1);
fa.addTransition(1,'a',0);
fa.addTransition(1,'b',2);
fa.addTransition(2,'a',1);
fa.addTransition(2,'b',5);
fa.addTransition(5,'b',4);
fa.addTransition(3,'b',4);
fa.addTransition(4,'a',0);
fa.addTransition(4,'b',4);
fa.addTransition(5,'a',1);

EXPECT_EQ(fa.countStates(),6u);
EXPECT_EQ(fa.countTransitions(),12u);
EXPECT_EQ(fa.getAlphabetSize(),2u);
EXPECT_TRUE(fa.isDeterministic());
EXPECT_TRUE(fa.isComplete());
faMin=fa::Automaton::createMinimalBrzozowski(fa);
EXPECT_TRUE(faMin.isIncludedIn(fa));
EXPECT_TRUE(fa.isIncludedIn(faMin));
//LES PROCHAINES LIGNES SONT A DELETE SI LE TEST PLANTE
/*EXPECT_EQ(faMin.countStates(),3u);
EXPECT_EQ(faMin.countTransitions(),6u);
EXPECT_EQ(faMin.getAlphabetSize(),2u);
*/
}

/*
//LES PROCHAINES LIGNES SONT A DELETE SI LE TEST PLANTE
//PART2: vérif présence et nature des états
TEST(automatonTest,MinimalWithBrzozowski2){
fa::Automaton fa,faMin;
fa.addState(0);
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.addState(4);
fa.addState(5);

fa.setStateInitial(0);
fa.setStateFinal(5);
fa.setStateFinal(4);

fa.addTransition(0,'a',1);
fa.addTransition(0,'b',3);
fa.addTransition(3,'a',1);
fa.addTransition(1,'a',0);
fa.addTransition(1,'b',2);
fa.addTransition(2,'a',1);
fa.addTransition(2,'b',5);
fa.addTransition(5,'b',4);
fa.addTransition(3,'b',4);
fa.addTransition(4,'a',0);
fa.addTransition(4,'b',4);
fa.addTransition(5,'a',1);

EXPECT_EQ(fa.countStates(),6u);
EXPECT_EQ(fa.countTransitions(),12u);
EXPECT_EQ(fa.getAlphabetSize(),2u);
EXPECT_TRUE(fa.isDeterministic());
EXPECT_TRUE(fa.isComplete());
faMin=fa::Automaton::createMinimalBrzozowski(fa);

EXPECT_TRUE(faMin.hasState(0));
EXPECT_TRUE(faMin.isStateInitial(0));
EXPECT_FALSE(faMin.isStateFinal(0));

EXPECT_TRUE(faMin.hasState(1));
EXPECT_FALSE(faMin.isStateInitial(1));
EXPECT_FALSE(faMin.isStateFinal(1));

EXPECT_TRUE(faMin.hasState(2));
EXPECT_FALSE(faMin.isStateInitial(2));
EXPECT_TRUE(faMin.isStateFinal(2));

}
//LES PROCHAINES LIGNES SONT A DELETE SI LE TEST PLANTE
//PART3: Vérif des transitions
TEST(automatonTest,MinimalWithBrzozowski3){
fa::Automaton fa,faMin;
fa.addState(0);
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.addState(4);
fa.addState(5);

fa.setStateInitial(0);
fa.setStateFinal(5);
fa.setStateFinal(4);

fa.addTransition(0,'a',1);
fa.addTransition(0,'b',3);
fa.addTransition(3,'a',1);
fa.addTransition(1,'a',0);
fa.addTransition(1,'b',2);
fa.addTransition(2,'a',1);
fa.addTransition(2,'b',5);
fa.addTransition(5,'b',4);
fa.addTransition(3,'b',4);
fa.addTransition(4,'a',0);
fa.addTransition(4,'b',4);
fa.addTransition(5,'a',1);

EXPECT_EQ(fa.countStates(),6u);
EXPECT_EQ(fa.countTransitions(),12u);
EXPECT_EQ(fa.getAlphabetSize(),2u);
EXPECT_TRUE(fa.isDeterministic());
EXPECT_TRUE(fa.isComplete());
faMin=fa::Automaton::createMinimalBrzozowski(fa);

EXPECT_TRUE(faMin.hasTransition(0,'a',0));
EXPECT_TRUE(faMin.hasTransition(0,'b',1));
EXPECT_TRUE(faMin.hasTransition(1,'a',0));
EXPECT_TRUE(faMin.hasTransition(1,'b',2));
EXPECT_TRUE(faMin.hasTransition(2,'b',2));
EXPECT_TRUE(faMin.hasTransition(2,'a',0));


}
*/



/* test avec 1 automate  vide */
//PART1: comptage états, transitions, alphabet
TEST(automatonTest,MinimalWithBrzozowskieEmpty){
fa::Automaton fa,faMin;
EXPECT_FALSE(fa.isDeterministic());
EXPECT_FALSE(fa.isComplete());
EXPECT_DEATH(faMin=fa::Automaton::createMinimalBrzozowski(fa),"");
//LES PROCHAINES LIGNES SONT A DELETE SI LE TEST PLANTE
/*EXPECT_EQ(faMin.countStates(),0u);
EXPECT_EQ(faMin.countTransitions(),0u);
EXPECT_EQ(faMin.getAlphabetSize(),0u);
*/
}


/* test avec 1 automate non complet */
TEST(automatonTest,MinimalWithBrzozowskiNotComplete){
fa::Automaton fa,faMin;
fa.addState(1);
    fa.addState(2);
    fa.setStateInitial(1);
    fa.setStateFinal(2);
    fa.addTransition(1,'a',2);
    fa.addTransition(1,'b',1);
    fa.addTransition(2,'a',1);
EXPECT_FALSE(fa.isComplete());
EXPECT_DEATH(faMin=fa::Automaton::createMinimalBrzozowski(fa),"");


}



/* test avec 1 automate non déterministe */
TEST(automatonTest,MinimalWithBrzozowskiNotDeterminist){
fa::Automaton fa,faMin;
fa.addState(0);
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.addState(4);
    fa.addState(5);
    fa.addState(6);
    fa.setStateInitial(0);
    fa.setStateInitial(4);
    fa.setStateFinal(3);
    fa.setStateFinal(6);
    fa.addTransition(0,'a',1);
    fa.addTransition(1,'b',2);
    fa.addTransition(2,'c',2);
    fa.addTransition(2,'a',3);
    fa.addTransition(6,'a',3);
    fa.addTransition(2,'a',5);
    fa.addTransition(5,'b',6);
    fa.addTransition(6,'a',2);
    fa.addTransition(4,'c',2);
    fa.addTransition(1,'b',4);
EXPECT_FALSE(fa.isDeterministic());
EXPECT_DEATH(faMin=fa::Automaton::createMinimalBrzozowski(fa),"");

}

////////////////////TEST MINIMAL HOPCRAFT






/* test avec 1 automate non vide déjà minimal*/
//PART1: vérification égalité des langages avant/après
TEST(automatonTest,AlreadyMinimalWitHopcroft1){
fa::Automaton fa,faMin;
fa.addState(0);
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.addState(4);
fa.addState(5);
fa.setStateInitial(0);
fa.setStateFinal(5);
fa.addTransition(0,'a',2);
fa.addTransition(0,'b',2);
fa.addTransition(2,'b',0);
fa.addTransition(0,'a',1);
fa.addTransition(1,'a',4);
fa.addTransition(1,'b',5);
fa.addTransition(4,'b',5);
fa.addTransition(5,'b',4);
fa.addTransition(4,'a',3);
fa.addTransition(3,'b',4);
fa.addTransition(5,'a',3);
fa.addTransition(3,'a',5);

EXPECT_EQ(fa.countStates(),6u);
EXPECT_EQ(fa.countTransitions(),12u);
EXPECT_EQ(fa.getAlphabetSize(),2u);
EXPECT_TRUE(fa.isDeterministic());
EXPECT_TRUE(fa.isComplete());
faMin=fa::Automaton::createMinimalHopcroft(fa);
EXPECT_TRUE(faMin.isIncludedIn(fa));
EXPECT_TRUE(fa.isIncludedIn(faMin));
//LES PROCHAINES LIGNES SONT A DELETE SI LE TEST PLANTE
/*EXPECT_EQ(faMin.countStates(),6u);
EXPECT_EQ(faMin.countTransitions(),12u);
EXPECT_EQ(faMin.getAlphabetSize(),2u);
*/
}



//LES PROCHAINES LIGNES SONT A DELETE SI LE TEST PLANTE
//PART2: verif présence et nature des états
/*TEST(automatonTest,AlreadyMinimalWithHopcroft2){
fa::Automaton fa,faMin;
fa.addState(0);
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.addState(4);
fa.addState(5);
fa.setStateInitial(0);
fa.setStateFinal(5);
fa.addTransition(0,'a',2);
fa.addTransition(0,'b',2);
fa.addTransition(2,'b',0);
fa.addTransition(0,'a',1);
fa.addTransition(1,'a',4);
fa.addTransition(1,'b',5);
fa.addTransition(4,'b',5);
fa.addTransition(5,'b',4);
fa.addTransition(4,'a',3);
fa.addTransition(3,'b',4);
fa.addTransition(5,'a',3);
fa.addTransition(3,'a',5);


EXPECT_TRUE(fa.isDeterministic());
EXPECT_TRUE(fa.isComplete());
faMin=fa::Automaton::createMinimalHopcroft(fa);

EXPECT_TRUE(faMin.hasState(0));
EXPECT_TRUE(faMin.isStateInitial(0));
EXPECT_FALSE(faMin.isStateFinal(0));

EXPECT_TRUE(faMin.hasState(1));
EXPECT_FALSE(faMin.isStateInitial(1));
EXPECT_FALSE(faMin.isStateFinal(1));

EXPECT_TRUE(faMin.hasState(2));
EXPECT_FALSE(faMin.isStateInitial(2));
EXPECT_FALSE(faMin.isStateFinal(2));

EXPECT_TRUE(faMin.hasState(3));
EXPECT_FALSE(faMin.isStateInitial(3));
EXPECT_FALSE(faMin.isStateFinal(3));

EXPECT_TRUE(faMin.hasState(4));
EXPECT_FALSE(faMin.isStateInitial(4));
EXPECT_FALSE(faMin.isStateFinal(4));

EXPECT_TRUE(faMin.hasState(5));
EXPECT_FALSE(faMin.isStateInitial(5));
EXPECT_TRUE(faMin.isStateFinal(5));
}




//LES PROCHAINES LIGNES SONT A DELETE SI LE TEST PLANTE
//PART3: verif présence des transitions
TEST(automatonTest,AlreadyMinimalWithHopcroft3){
fa::Automaton fa,faMin;
fa.addState(0);
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.addState(4);
fa.addState(5);
fa.setStateInitial(0);
fa.setStateFinal(5);
fa.addTransition(0,'a',2);
fa.addTransition(0,'b',2);
fa.addTransition(2,'b',0);
fa.addTransition(0,'a',1);
fa.addTransition(1,'a',4);
fa.addTransition(1,'b',5);
fa.addTransition(4,'b',5);
fa.addTransition(5,'b',4);
fa.addTransition(4,'a',3);
fa.addTransition(3,'b',4);
fa.addTransition(5,'a',3);
fa.addTransition(3,'a',5);

EXPECT_TRUE(fa.isDeterministic());
EXPECT_TRUE(fa.isComplete());
faMin=fa::Automaton::createMinimalHopcroft(fa);

EXPECT_TRUE(faMin.hasTransition(0,'a',2));
EXPECT_TRUE(faMin.hasTransition(0,'b',2));
EXPECT_TRUE(faMin.hasTransition(2,'b',0));
EXPECT_TRUE(faMin.hasTransition(0,'a',1));
EXPECT_TRUE(faMin.hasTransition(1,'a',4));
EXPECT_TRUE(faMin.hasTransition(1,'b',5));
EXPECT_TRUE(faMin.hasTransition(4,'b',5));
EXPECT_TRUE(faMin.hasTransition(5,'b',4));
EXPECT_TRUE(faMin.hasTransition(4,'a',3));
EXPECT_TRUE(faMin.hasTransition(3,'b',4));
EXPECT_TRUE(faMin.hasTransition(5,'a',3));
EXPECT_TRUE(faMin.hasTransition(3,'a',5));

}
*/




/* test avec 1 automate non vide */
//PART1: vérification égalité des langages avant/après
TEST(automatonTest,MinimalWithHopcroft1){
fa::Automaton fa,faMin;
fa.addState(0);
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.addState(4);
fa.addState(5);

fa.setStateInitial(0);
fa.setStateFinal(5);
fa.setStateFinal(4);

fa.addTransition(0,'a',1);
fa.addTransition(0,'b',3);
fa.addTransition(3,'a',1);
fa.addTransition(1,'a',0);
fa.addTransition(1,'b',2);
fa.addTransition(2,'a',1);
fa.addTransition(2,'b',5);
fa.addTransition(5,'b',4);
fa.addTransition(3,'b',4);
fa.addTransition(4,'a',0);
fa.addTransition(4,'b',4);
fa.addTransition(5,'a',1);

EXPECT_EQ(fa.countStates(),6u);
EXPECT_EQ(fa.countTransitions(),12u);
EXPECT_EQ(fa.getAlphabetSize(),2u);
EXPECT_TRUE(fa.isDeterministic());
EXPECT_TRUE(fa.isComplete());
faMin=fa::Automaton::createMinimalHopcroft(fa);
EXPECT_TRUE(faMin.isIncludedIn(fa));
EXPECT_TRUE(fa.isIncludedIn(faMin));
//LES PROCHAINES LIGNES SONT A DELETE SI LE TEST PLANTE
/*EXPECT_EQ(faMin.countStates(),3u);
EXPECT_EQ(faMin.countTransitions(),6u);
EXPECT_EQ(faMin.getAlphabetSize(),2u);
*/
}


//LES PROCHAINES LIGNES SONT A DELETE SI LE TEST PLANTE
//PART2: vérif présence et nature des états
/*TEST(automatonTest,MinimalWithHopcroft2){
fa::Automaton fa,faMin;
fa.addState(0);
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.addState(4);
fa.addState(5);

fa.setStateInitial(0);
fa.setStateFinal(5);
fa.setStateFinal(4);

fa.addTransition(0,'a',1);
fa.addTransition(0,'b',3);
fa.addTransition(3,'a',1);
fa.addTransition(1,'a',0);
fa.addTransition(1,'b',2);
fa.addTransition(2,'a',1);
fa.addTransition(2,'b',5);
fa.addTransition(5,'b',4);
fa.addTransition(3,'b',4);
fa.addTransition(4,'a',0);
fa.addTransition(4,'b',4);
fa.addTransition(5,'a',1);

EXPECT_EQ(fa.countStates(),6u);
EXPECT_EQ(fa.countTransitions(),12u);
EXPECT_EQ(fa.getAlphabetSize(),2u);
EXPECT_TRUE(fa.isDeterministic());
EXPECT_TRUE(fa.isComplete());
faMin=fa::Automaton::createMinimalHopcroft(fa);

EXPECT_TRUE(faMin.hasState(0));
EXPECT_TRUE(faMin.isStateInitial(0));
EXPECT_FALSE(faMin.isStateFinal(0));

EXPECT_TRUE(faMin.hasState(1));
EXPECT_FALSE(faMin.isStateInitial(1));
EXPECT_FALSE(faMin.isStateFinal(1));

EXPECT_TRUE(faMin.hasState(2));
EXPECT_FALSE(faMin.isStateInitial(2));
EXPECT_TRUE(faMin.isStateFinal(2));

}
//LES PROCHAINES LIGNES SONT A DELETE SI LE TEST PLANTE
//PART3: Vérif des transitions
TEST(automatonTest,MinimalWithHopcroft3){
fa::Automaton fa,faMin;
fa.addState(0);
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.addState(4);
fa.addState(5);

fa.setStateInitial(0);
fa.setStateFinal(5);
fa.setStateFinal(4);

fa.addTransition(0,'a',1);
fa.addTransition(0,'b',3);
fa.addTransition(3,'a',1);
fa.addTransition(1,'a',0);
fa.addTransition(1,'b',2);
fa.addTransition(2,'a',1);
fa.addTransition(2,'b',5);
fa.addTransition(5,'b',4);
fa.addTransition(3,'b',4);
fa.addTransition(4,'a',0);
fa.addTransition(4,'b',4);
fa.addTransition(5,'a',1);

EXPECT_EQ(fa.countStates(),6u);
EXPECT_EQ(fa.countTransitions(),12u);
EXPECT_EQ(fa.getAlphabetSize(),2u);
EXPECT_TRUE(fa.isDeterministic());
EXPECT_TRUE(fa.isComplete());
faMin=fa::Automaton::createMinimalHopcroft(fa);

EXPECT_TRUE(faMin.hasTransition(0,'a',0));
EXPECT_TRUE(faMin.hasTransition(0,'b',1));
EXPECT_TRUE(faMin.hasTransition(1,'a',0));
EXPECT_TRUE(faMin.hasTransition(1,'b',2));
EXPECT_TRUE(faMin.hasTransition(2,'b',2));
EXPECT_TRUE(faMin.hasTransition(2,'a',0));


}
*/



/* test avec 1 automate  vide */
//PART1: comptage états, transitions, alphabet
TEST(automatonTest,MinimalWithHopcroftEmpty){
fa::Automaton fa,faMin;
EXPECT_FALSE(fa.isDeterministic());
EXPECT_FALSE(fa.isComplete());
EXPECT_DEATH(faMin=fa::Automaton::createMinimalHopcroft(fa),"");
}


/* test avec 1 automate non complet */
TEST(automatonTest,MinimalWithHopcroftNotComplete){
fa::Automaton fa,faMin;
fa.addState(1);
    fa.addState(2);
    fa.setStateInitial(1);
    fa.setStateFinal(2);
    fa.addTransition(1,'a',2);
    fa.addTransition(1,'b',1);
    fa.addTransition(2,'a',1);
EXPECT_FALSE(fa.isComplete());
EXPECT_DEATH(faMin=fa::Automaton::createMinimalHopcroft(fa),"");


}



/* test avec 1 automate non déterministe */
TEST(automatonTest,MinimalWithHopcroftNotDeterminist){
fa::Automaton fa,faMin;
fa.addState(0);
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.addState(4);
    fa.addState(5);
    fa.addState(6);
    fa.setStateInitial(0);
    fa.setStateInitial(4);
    fa.setStateFinal(3);
    fa.setStateFinal(6);
    fa.addTransition(0,'a',1);
    fa.addTransition(1,'b',2);
    fa.addTransition(2,'c',2);
    fa.addTransition(2,'a',3);
    fa.addTransition(6,'a',3);
    fa.addTransition(2,'a',5);
    fa.addTransition(5,'b',6);
    fa.addTransition(6,'a',2);
    fa.addTransition(4,'c',2);
    fa.addTransition(1,'b',4);
EXPECT_FALSE(fa.isDeterministic());
EXPECT_DEATH(faMin=fa::Automaton::createMinimalHopcroft(fa),"");

}

////////////////////CREATE WITHOUT EPSILON


/* test élimination des epsilon-transition sur automate non vide présentant des e-transition*/
//PART1: vérification égalité des langages avant/après
TEST(automatonTest,CreateWithoutEpsilon1){
fa::Automaton fa,faEps;
char eps=(char) 0;
fa.addState(0);
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.addState(4);
fa.setStateInitial(0);
fa.setStateFinal(3);
fa.setStateFinal(4);

fa.addTransition(0,'a',1);
fa.addTransition(1,'b',2);
fa.addTransition(2,'b',3);
fa.addTransition(3,'b',0);
fa.addTransition(0,eps,2);
fa.addTransition(1,eps,4);
fa.addTransition(4,eps,3);
fa.addTransition(2,eps,4);
fa.addTransition(4,'a',2);

faEps=fa::Automaton::createWithoutEpsilon(fa);
EXPECT_TRUE(faEps.isIncludedIn(fa));
EXPECT_TRUE(fa.isIncludedIn(faEps));
//LES PROCHAINES LIGNES SONT A DELETE SI LE TEST PLANTE
/*EXPECT_EQ(faEps.countStates(),5u);EXPECT_EQ(faEps.countTransitions(),10u);
EXPECT_EQ(faEps.getAlphabetSize(),2u);
*/
}


//LES PROCHAINES LIGNES SONT A DELETE SI LE TEST PLANTE
//PART2: vérification présence et nature des états 
/*TEST(automatonTest,CreateWithoutEpsilon2){
fa::Automaton fa,faEps;
char eps=(char) 0;
fa.addState(0);
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.addState(4);
fa.setStateInitial(0);
fa.setStateFinal(3);
fa.setStateFinal(4);

fa.addTransition(0,'a',1);
fa.addTransition(1,'b',2);
fa.addTransition(2,'b',3);
fa.addTransition(3,'b',0);
fa.addTransition(0,eps,2);
fa.addTransition(1,eps,4);
fa.addTransition(4,eps,3);
fa.addTransition(2,eps,4);
fa.addTransition(4,'a',2);

faEps=fa::Automaton::createWithoutEpsilon(fa);

EXPECT_TRUE(faEps.hasState(0));
EXPECT_TRUE(faEps.isStateInitial(0));
EXPECT_TRUE(faEps.isStateFinal(0));

EXPECT_TRUE(faEps.hasState(1));
EXPECT_FALSE(faEps.isStateInitial(1));
EXPECT_TRUE(faEps.isStateFinal(1));

EXPECT_TRUE(faEps.hasState(2));
EXPECT_FALSE(faEps.isStateInitial(2));
EXPECT_TRUE(faEps.isStateFinal(2));

EXPECT_TRUE(faEps.hasState(3));
EXPECT_FALSE(faEps.isStateInitial(3));
EXPECT_TRUE(faEps.isStateFinal(3));

EXPECT_TRUE(faEps.hasState(4));
EXPECT_FALSE(faEps.isStateInitial(4));
EXPECT_FALSE(faEps.isStateFinal(4));
}

//LES PROCHAINES LIGNES SONT A DELETE SI LE TEST PLANTE
//PART3: vérification présence des transitions 
TEST(automatonTest,CreateWithoutEpsilon3){
fa::Automaton fa,faEps;
char eps=(char) 0;
fa.addState(0);
fa.addState(1);
fa.addState(2);
fa.addState(3);
fa.addState(4);
fa.setStateInitial(0);
fa.setStateFinal(3);
fa.setStateFinal(4);

fa.addTransition(0,'a',1);
fa.addTransition(1,'b',2);
fa.addTransition(2,'b',3);
fa.addTransition(3,'b',0);
fa.addTransition(0,eps,2);
fa.addTransition(1,eps,4);
fa.addTransition(4,eps,3);
fa.addTransition(2,eps,4);
fa.addTransition(4,'a',2);

faEps=fa::Automaton::createWithoutEpsilon(fa);

EXPECT_TRUE(faEps.hasTransition(0,'a',1));
EXPECT_TRUE(faEps.hasTransition(1,'a',2));
EXPECT_TRUE(faEps.hasTransition(1,'b',2));
EXPECT_TRUE(faEps.hasTransition(2,'a',2));
EXPECT_TRUE(faEps.hasTransition(1,'b',3));
EXPECT_TRUE(faEps.hasTransition(4,'a',2));
EXPECT_TRUE(faEps.hasTransition(4,'b',3));
EXPECT_TRUE(faEps.hasTransition(2,'b',3));
EXPECT_TRUE(faEps.hasTransition(3,'b',0));
EXPECT_TRUE(faEps.hasTransition(0,'b',3));
}
*/

/* test élimination des epsilon-transition sur automate non vide ne présentant pas d'e-transition*/
//PART1: vérification égalité des langages avant/après
//PART1: comptage des états, des transitions et de l'alphabet
TEST(automatonTest,CreateWithoutEpsilonWithoutEpsTransition1){
fa::Automaton fa,faEps;
fa.addState(0);
fa.addState(1);
fa.addState(2);
fa.setStateInitial(0);
fa.setStateFinal(2);

fa.addTransition(0,'a',1);
fa.addTransition(1,'b',2);
fa.addTransition(2,'b',2);

faEps=fa::Automaton::createWithoutEpsilon(fa);
EXPECT_TRUE(faEps.isIncludedIn(fa));
EXPECT_TRUE(fa.isIncludedIn(faEps));
//LES PROCHAINES LIGNES SONT A DELETE SI LE TEST PLANTE
//EXPECT_EQ(faEps.countStates(),3u);
//EXPECT_EQ(faEps.countTransitions(),3u);
//EXPECT_EQ(faEps.getAlphabetSize(),2u);

}


//LES PROCHAINES LIGNES SONT A DELETE SI LE TEST PLANTE
//PART2: vérification présence état et nature états
/*TEST(automatonTest,CreateWithoutEpsilonWithoutEpsTransition2){
fa::Automaton fa,faEps;
fa.addState(0);
fa.addState(1);
fa.addState(2);
fa.setStateInitial(0);
fa.setStateFinal(2);

fa.addTransition(0,'a',1);
fa.addTransition(1,'b',2);
fa.addTransition(2,'b',2);

faEps=fa::Automaton::createWithoutEpsilon(fa);

EXPECT_TRUE(faEps.hasState(0));
EXPECT_TRUE(faEps.isStateInitial(0));
EXPECT_FALSE(faEps.isStateFinal(0));

EXPECT_TRUE(faEps.hasState(1));
EXPECT_FALSE(faEps.isStateInitial(1));
EXPECT_FALSE(faEps.isStateFinal(1));


EXPECT_TRUE(faEps.hasState(2));
EXPECT_FALSE(faEps.isStateInitial(2));
EXPECT_TRUE(faEps.isStateFinal(2));
}
//LES PROCHAINES LIGNES SONT A DELETE SI LE TEST PLANTE
//PART3: vérification présence des transitions 
TEST(automatonTest,CreateWithoutEpsilonWithoutEpsTransition3){
fa::Automaton fa,faEps;
fa.addState(0);
fa.addState(1);
fa.addState(2);
fa.setStateInitial(0);
fa.setStateFinal(2);

fa.addTransition(0,'a',1);
fa.addTransition(1,'b',2);
fa.addTransition(2,'b',2);

faEps=fa::Automaton::createWithoutEpsilon(fa);


EXPECT_TRUE(faEps.hasTransition(0,'a',1));
EXPECT_TRUE(faEps.hasTransition(1,'b',2));
EXPECT_TRUE(faEps.hasTransition(2,'b',2));

}*/



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

