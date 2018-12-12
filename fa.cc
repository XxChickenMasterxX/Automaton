#include "Automaton.h"
#include <fstream>

void test(){
	fa::Automaton fa;
    fa.addState(0);
	fa.setStateInitial(0);
	fa.addState(1);
	fa.addState(2);
	fa.addState(3);
	fa.setStateFinal(3);
	fa.addState(4);
	fa.setStateFinal(4);
	fa.addState(5);
	
	fa.addTransition(0,'a',1);
	fa.addTransition(0,'b',2);
	fa.addTransition(1,'a',3);
	fa.addTransition(1,'b',2);
	fa.addTransition(2,'b',4);
	fa.addTransition(2,'a',1);
	fa.addTransition(3,'a',4);
	fa.addTransition(3,'b',5);
	fa.addTransition(4,'a',3);
	fa.addTransition(4,'b',5);
	fa.addTransition(5,'a',5);
	fa.addTransition(5,'b',5);
	
	fa::Automaton fm;
	fm = fm.createMinimalMoore(fa);

	fm.prettyPrint(std::cout);
}

int main(){
   
    fa::Automaton automaton;

  	automaton.addState(1); 
    automaton.addState(2);

	automaton.setStateInitial(1);
	automaton.setStateFinal(2);
	automaton.addTransition(1,'a',2);
	automaton.addTransition(2,'b',1);
	test();
	/*
	std::ofstream fichier("GrapheTest.dot", std::ios::out | std::ios::trunc);
	if(fichier)
	{
	    automaton.dotPrint(fichier);
	}else
	    std::cerr << "fail open ! " << std::endl;*/
	
	// pour convertir le .dot en fichier image
	// dans le terminal :
	
	//dot -Tpng -oGrapheTest.png GrapheTest.dot
	

    return 0;
}
