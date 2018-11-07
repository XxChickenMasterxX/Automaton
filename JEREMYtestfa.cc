#include <iostream>
#include <iomanip>

#include "gtest/gtest.h"

#include "Automaton.h"




//////////////////////////////////////////////////////////TEST TP1

/*Test comptage transitions, states et taille alphabet pour un automaton vide*/
TEST(AutomatonTest, Empty) {
	fa::Automaton fa;
  	EXPECT_EQ(fa.countStates(), 0u);
	EXPECT_EQ(fa.countTransitions(), 0u);
	EXPECT_EQ(fa.getAlphabetSize(),0u);
}



/*Test ajout d'un état valide*/
TEST(AutomatonTest, AddState) {
	fa::Automaton fa;
	int state=1;
	fa.addState(state);
	EXPECT_EQ(fa.countStates(), 1u);
}



/*Test suppression d'un état valide*/
TEST(AutomatonTest, RemoveState) {
	fa::Automaton fa;
	int state=1;
	fa.addState(state);
	fa.removeState(state);
	EXPECT_EQ(fa.countStates(), 0u);
}

/*Test suppression des transitions utilisant un état supprimé auparavant*/
TEST(AutomatonTest, RemoveStateAndTransition1) {
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
	EXPECT_EQ(fa.hasTransition(1,'a',2),false);
}



TEST(AutomatonTest, RemoveStateAndTransition2) {
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
	EXPECT_EQ(fa.hasTransition(2,'b',3),true);
}



/*Test comptage transitions pour un automaton non vide*/
TEST(AutomatonTest, HasStateYes) {
	fa::Automaton fa;
	int state=1;
	fa.addState(state);
	EXPECT_EQ(fa.hasState(state), true);
}



/*Test recherche d'un état absent de l'automate*/
TEST(AutomatonTest, HasStateNo) {
	fa::Automaton fa;
	int state=1;
	int notAState=2;
	fa.addState(state);
	EXPECT_EQ(fa.hasState(notAState), false);
}





/*Test recherche d'un état après ajout puis suppression de ce dernier*/
TEST(AutomatonTest, HasStateBeforeYesButNowNo) {
	fa::Automaton fa;
	int state=1;
	fa.addState(state);
	EXPECT_EQ(fa.hasState(state), true);
	fa.removeState(state);
	EXPECT_EQ(fa.hasState(state), false);

}



/*Test recherche d'un état présent mais pas défini comme initial*/
TEST(AutomatonTest, 0InitialState) {
	fa::Automaton fa;
	int state=1;
	fa.addState(state);
	EXPECT_EQ(fa.isStateInitial(state), false);

}



/*Test recherche d'un état présent et défini comme état initial*/
TEST(AutomatonTest, 1InitialState) {
	fa::Automaton fa;
	int state=1;
	fa.addState(state);
	fa.setStateInitial(state);
	EXPECT_EQ(fa.isStateInitial(state), true);

}



/* Test ajout d'un état intial pas présent dans la liste des états de l'automate*/
TEST(AutomatonTest, NotAnInitialState) {
	fa::Automaton fa;
	int state=1;
	int notAState=2;
	fa.addState(state);
	fa.setStateInitial(notAState);
	EXPECT_EQ(fa.isStateInitial(state), false);

}



/*Test recherche état initial après ajour puis suppression de ce dernier*/
TEST(AutomatonTest, HasInitialStateBeforeYesButNowNo) {
	fa::Automaton fa;
	int state=1;
	fa.addState(state);
	fa.setStateInitial(state);
	EXPECT_EQ(fa.isStateInitial(state), true);
	fa.removeState(state);
	EXPECT_EQ(fa.isStateInitial(state), false);

}



/*Test recherche état final d'un état présent mais pas défini comme état finak*/
TEST(AutomatonTest, 0FinalState) {
	fa::Automaton fa;
	int state=1;
	fa.addState(state);
	EXPECT_EQ(fa.isStateFinal(state), false);

}



/*Test recherche d'un état inital présent et défini comme état initial*/
TEST(AutomatonTest, 1FinalState) {
	fa::Automaton fa;
	int state=1;
	fa.addState(state);
	fa.setStateFinal(state);
	EXPECT_EQ(fa.isStateFinal(state), true);

}




/*Test recherche état final d'un état défini comme final mais absent de la liste des états de l'automate*/
TEST(AutomatonTest, NotAnFinalState) {
	fa::Automaton fa;
	int state=1;
	int notAState=2;
	fa.addState(state);
	fa.setStateFinal(notAState);
	EXPECT_EQ(fa.isStateFinal(state), false);

}



/*Test présence d'un état fina après son ajout puis sa suppression*/
TEST(AutomatonTest, HasFinalStateBeforeYesButNowNo) {
	fa::Automaton fa;
	int state=1;
	fa.addState(state);
	fa.setStateFinal(state);
	EXPECT_EQ(fa.isStateFinal(state), true);
	fa.removeState(state);
	

}



/*Test comptage transition d'un automate vide*/
TEST(AutomatonTest, EmptyTransition) {
	fa::Automaton fa;
	EXPECT_EQ(fa.countTransitions (), 0u);

}



/*Test comptage des transitions d'un automate non vide sans tranisition*/
TEST(AutomatonTest, Transition) {
	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	EXPECT_EQ(fa.countTransitions(), 0u);

}



/*Test comptage des transitions d'un automate ayant une transition valide et bien définie*/
TEST(AutomatonTest, 1Transition) {
	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.addTransition(1,'a',2);
	EXPECT_EQ(fa.countTransitions(), 1u);

}



/*Test présence d'une transition ayant un caractère invalide (npn imprimable)*/ 
TEST(AutomatonTest, BadCharacterTransition) {
	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.addTransition(1,(char)1000,2);
	EXPECT_EQ(fa.countTransitions(), 0u);

}



/*Test suppression d'une transition valide et existante dans l'automate*/
TEST(AutomatonTest, removeTransition) {
	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.addTransition(1,'a',2);
	fa.removeTransition(1,'a',2);
	EXPECT_EQ(fa.countTransitions(), 0u);
	EXPECT_EQ(fa.hasState(1), true);
	EXPECT_EQ(fa.hasState(2), true);
//	EXPECT_EQ(fa.hasCharacter('a'), true);
}



/*Test suppression d'une transition valide et existante dans l'automate entre un état initial et et un étét final*/
TEST(AutomatonTest, removeTransitionInitialFinal) {
	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.setStateInitial(1);
	fa.setStateFinal(2);
	fa.addTransition(1,'a',2);
	fa.removeTransition(1,'a',2);
	EXPECT_EQ(fa.countTransitions(), 0u);
	EXPECT_EQ(fa.hasState(1), true);
	EXPECT_EQ(fa.hasState(2), true);
	EXPECT_EQ(fa.isStateInitial(1), true);
//	EXPECT_EQ(fa.isStateFinal(2), true);
//	EXPECT_EQ(fa.hasCharacter('a'), true);
}




/*Test suppression d'une transiiton valide et existante dans l'automate*/
TEST(AutomatonTest, removeNotATransition) {
	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.addTransition(1,'b',2);
	fa.removeTransition(1,'c',2);
	EXPECT_EQ(fa.countTransitions(), 1u);
	EXPECT_EQ(fa.hasState(1), true);
	EXPECT_EQ(fa.hasState(2), true);
	//EXPECT_EQ(fa.hasCharacter('b'), true);
	//EXPECT_EQ(fa.hasCharacter('c'),false);

}



/*Test présence d'un transition valide et bien définie*/
TEST(AutomatonTest, HasATransition) {
	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.addTransition(1,'b',2);
	EXPECT_EQ(fa.hasTransition(1,'b',2), true);

}



/*Test recherche d'une transition non définie dans l'automate*/
TEST(AutomatonTest, HasNotATransition) {
	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.addTransition(1,'b',2);
	EXPECT_EQ(fa.hasTransition(1,'a',2), false);

}



/*Test ajout successif de la même transition 2 fois*/
TEST(AutomatonTest, DoublonTransition) {
	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.addTransition(1,'b',2);
	fa.addTransition(1,'b',2);
	EXPECT_EQ(fa.countTransitions(),1u);

}



/*Test présence transifiton après son ajoûr puis sa suppression dans l'automate*/
TEST(AutomatonTest,HasTransitionBeforeYesButNowNo) {
	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.addTransition(1,'a',2);
	EXPECT_EQ(fa.hasTransition(1,'a',2), true);
	fa.removeTransition(1,'a',2);
	EXPECT_EQ(fa.hasTransition(1,'a',2), false);

}



/*Test taille alphabet (initialement vide) après l'ajoût d'une transiton*/
TEST(AutomatonTest,AlphabetSize1) {
	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.addTransition(1,'a',2);
	EXPECT_EQ(fa.hasTransition(1,'a',2), true);
	EXPECT_EQ(fa.getAlphabetSize(), 1u);
	

}



/*Test taille alphabet (initalement vide) après tentative d'ajoût d'une transition avec caracrtère non valide*/
TEST(AutomatonTest, BadCharacterAlphabetSize) {
	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.addTransition(1,(char)1000,2);
	EXPECT_EQ(fa.getAlphabetSize(), 0u);

}



/*Test taille alphabet d'un automate vide*/
TEST(AutomatonTest,EmptyAlphabetSize1) {
	fa::Automaton fa;
	EXPECT_EQ(fa.getAlphabetSize(), 0u);
	
}




/*Test taille d'un alphabet d'un automate sans transition définie*/
TEST(AutomatonTest,0TransitionAlphabetSize) {
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



/*Test Taille alphabet après ajoût d'une transition ayant un caractère déjà présent dans cet alphabet*/
TEST(AutomatonTest,DoublonBadCharacterAlphabetSize) {
	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.addState(3);
	fa.addTransition(1,'b',2);
	fa.addTransition(2,'b',3);
	EXPECT_EQ(fa.getAlphabetSize(), 1u);
}


//////////////////////////////////////////////////////////TEST TP2


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
	EXPECT_EQ(fa.isDeterministic(), false);
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
	EXPECT_EQ(fa.isDeterministic(), false);
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
	EXPECT_EQ(fa.isDeterministic(), false);
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
	EXPECT_EQ(fa.isDeterministic(), false);
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
	EXPECT_EQ(fa.isComplete(), true);
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
	EXPECT_EQ(fa.isDeterministic(), true);
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
	EXPECT_EQ(fa.isDeterministic(), false);
}



/*Test Nature déterministe d'un automate qui ne possède qu'un état*/
TEST(AutomatonTest,isDeterministicOneState) {
	fa::Automaton fa;
	fa.addState(1);
	EXPECT_EQ(fa.isDeterministic(), false);
}



/*Test Nature déterministe d'un automate vide*/
TEST(AutomatonTest,isDeterministicEmpty) {
	fa::Automaton fa;
	EXPECT_EQ(fa.isDeterministic(), false);
}



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
	EXPECT_EQ(fa.isComplete(), true);
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
	EXPECT_EQ(fa.isComplete(), true);
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
	EXPECT_EQ(fa.isComplete(), true);
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
	EXPECT_EQ(fa.isComplete(), true);
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
	EXPECT_EQ(fa.isComplete(), true);
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
	EXPECT_EQ(fa.isComplete(), true);
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
	EXPECT_EQ(fa.isComplete(), false);
}



/*Test Nature complète d'un automate qui ne possède qu'un état*/
TEST(AutomatonTest,isCompleteOneState) {
	fa::Automaton fa;
	fa.addState(1);
	EXPECT_EQ(fa.isComplete(), true);
}



/*Test Nature complète d'un automate vide*/
TEST(AutomatonTest,isCompleteEmpty) {
	fa::Automaton fa;
	EXPECT_EQ(fa.isComplete(), true);
}



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
	EXPECT_EQ(fa.isComplete(), false);
	fa.makeComplete();
	EXPECT_EQ(fa.isComplete(), true);
}




/*Test transformation d'un automate en son complémentaire*/
TEST(AutomatonTest,transformToComplementaryPart1) {
	/*Test de la non modification des états d'origine */
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
	EXPECT_EQ(fa.isComplete(), true);
	EXPECT_EQ(fa.isDeterministic(), true);
	fa.makeComplement();
	EXPECT_EQ(fa.hasState(1),true);
	EXPECT_EQ(fa.hasState(2),true);
	EXPECT_EQ(fa.hasState(3),true);
	EXPECT_EQ(fa.hasState(4),true);
}



TEST(AutomatonTest,transformToComplementaryPart2) {
	/*Test de la non modification des transitions */
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
	EXPECT_EQ(fa.isComplete(), true);
	EXPECT_EQ(fa.isDeterministic(), true);
	fa.makeComplement();
	EXPECT_EQ(fa.hasTransition(1,'a',2),true);
	EXPECT_EQ(fa.hasTransition(2,'a',2),true);
	EXPECT_EQ(fa.hasTransition(2,'b',3),true);
	EXPECT_EQ(fa.hasTransition(3,'b',3),true);
	EXPECT_EQ(fa.hasTransition(3,'a',4),true);
	EXPECT_EQ(fa.hasTransition(4,'a',4),true);
	EXPECT_EQ(fa.hasTransition(4,'b',4),true);
	EXPECT_EQ(fa.hasTransition(1,'b',4),true);
}



TEST(AutomatonTest,transformToComplementaryPart3) {
	/*Test de la non modification de la nature déterminsite et complète de l'automate*/
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
	EXPECT_EQ(fa.isComplete(), true);
	EXPECT_EQ(fa.isDeterministic(), true);
	fa.makeComplement();
	EXPECT_EQ(fa.isComplete(), true);
	EXPECT_EQ(fa.isDeterministic(), true);
	
}



TEST(AutomatonTest,transformToComplementaryPart4) {
	/*Test de la non modification de l'inversion des états normaux en finaux*/
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
	EXPECT_EQ(fa.isComplete(), true);
	EXPECT_EQ(fa.isDeterministic(), true);
	fa.makeComplement();
	EXPECT_EQ(fa.isStateFinal(1),true);
	EXPECT_EQ(fa.isStateFinal(2),true);
	EXPECT_EQ(fa.isStateFinal(4),true);	
}


TEST(AutomatonTest,transformToComplementaryPart5) {
	/*Test de la non modification de l'inversion des états finaux en normaux*/
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
	EXPECT_EQ(fa.isComplete(), true);
	EXPECT_EQ(fa.isDeterministic(), true);
	fa.makeComplement();
	EXPECT_EQ(fa.isStateFinal(3), false);
	
}

TEST(AutomatonTest,transformToComplementaryPart6) {
	/*Test de la non modification de la conservation des états initiaux*/
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
	EXPECT_EQ(fa.isComplete(), true);
	EXPECT_EQ(fa.isDeterministic(), true);
	fa.makeComplement();
	EXPECT_EQ(fa.isStateInitial(1), true);
	
}



//////////////////////////////////////////////////////////TEST TP3

TEST(automatonTest,EmptyLanguageYES){
	/*TEST langage vide qui l'est*/
	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.addState(3);
	fa.setStateFinal(3);
	fa.setStateInitial(1);
	fa.addTransition(1,'a',2);
	fa.addTransition(3,'b',3);
	EXPECT_EQ(fa.isLanguageEmpty(), true);
	

}



TEST(automatonTest,EmptyLanguageNO){
	/*TEST langage vide qui ne l'est pas*/
	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.addState(3);
	fa.setStateFinal(3);
	fa.setStateInitial(1);
	fa.addTransition(1,'a',2);
	fa.addTransition(2,'a',3);
	fa.addTransition(3,'b',3);
	EXPECT_EQ(fa.isLanguageEmpty(), false);

}



TEST(automatonTest,EmptyLanguageWithoutInitial){
	/*TEST langage vide sur un atomate sans état initial*/
	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.addState(3);
	fa.setStateFinal(3);
	fa.addTransition(1,'a',2);
	fa.addTransition(2,'a',3);
	fa.addTransition(3,'b',3);
	EXPECT_EQ(fa.isLanguageEmpty(), true);

}



TEST(automatonTest,EmptyLanguageWithoutFinal){
	/*TEST langage vide sur un atomate sans état final*/
	fa::Automaton fa;
	fa.addState(1);
	fa.addState(2);
	fa.addState(3);
	fa.setStateInitial(1);
	fa.addTransition(1,'a',2);
	fa.addTransition(2,'a',3);
	fa.addTransition(3,'b',3);
	EXPECT_EQ(fa.isLanguageEmpty(), true);

}



TEST(automatonTest,RemoveNonAccessibleSimpleState){
	/*TEST suppression d'un état non accessible simple*/
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
	EXPECT_EQ(fa.hasState(3),false);
	


}





//////////////////////////////////////////////////////////TEST TP5






int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
 return RUN_ALL_TESTS();
}

