#include "Automaton.h"
#include <fstream>

void test(){
	fa::Automaton automaton;
    automaton.addState(0);
    automaton.addState(1);
    automaton.addState(2); 
    automaton.addState(3);
    automaton.addState(4);

	automaton.setStateInitial(0);
	automaton.setStateInitial(1);

	automaton.setStateFinal(1);
	automaton.setStateFinal(4);

	automaton.addTransition(0,'a',1);
	automaton.addTransition(0,'a',2);
	automaton.addTransition(0,'a',3);
	automaton.addTransition(1,'b',3);
	automaton.addTransition(2,'a',3);
	automaton.addTransition(2,'b',4);
	automaton.addTransition(3,'a',3);
	automaton.addTransition(3,'b',4);
	automaton.addTransition(4,'a',4);

	automaton.prettyPrint(std::cout);
}

int main(){
   
    fa::Automaton automaton;

  	automaton.addState(1); 
    automaton.addState(2);

	automaton.setStateInitial(1);
	automaton.setStateFinal(2);
	automaton.addTransition(1,'a',2);
	automaton.addTransition(2,'b',1);
	
	std::ofstream fichier("GrapheTest.dot", std::ios::out | std::ios::trunc);
	if(fichier)
	{
	    automaton.dotPrint(fichier);
	}else
	    std::cerr << "fail open ! " << std::endl;
	
	// pour convertir le .dot en fichier image
	// dans le terminal :
	
	//dot -Tpng -oGrapheTest.png GrapheTest.dot
	

    return 0;
}
