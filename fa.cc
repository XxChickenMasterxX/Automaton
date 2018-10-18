#include "Automaton.h"

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
    // Automaton se situe dans le namespace "fa", pour accéder à la classe Automaton et créer un objet "automaton" de type Automaton, on écrit donc :
    fa::Automaton automaton;
/*   automaton.addState(1); // On ajoute l'état 1 à l'automate
    automaton.addState(2); // ...
    automaton.addState(3); // ...
    automaton.addState(1); // Notez que l'état 1 à déjà été ajouté à l'ensemble des états de l'automate (à l'attribut "states"). Puisque "states" est de type "std::set<int>", cet attribut se comporte comme un vrai ensemble (pas de doublons) : l'état 1 n'est donc pas de nouveau ajouté à l'ensemble des états de l'automate

	// Une fois arrivé ici, l'automate doit donc contenir 3 états :-)

	automaton.removeState(1);
    automaton.addState(1);
	std::cout << "Présence : " << automaton.hasState(1) << std::endl;

	automaton.setStateInitial(1);
	automaton.setStateInitial(2);

	automaton.addTransition(1,'a',1);
	automaton.addTransition(1,'a',2);
	automaton.addTransition(1,'b',3);

	std::cout << "Présence : " << automaton.hasTransition(1,'a',1) << std::endl;

	std::cout << "Il y a " << automaton.countTransitions() << " transitions" << std::endl;
	automaton.removeTransition(1,'a',1);

	std::cout << "Il y a " << automaton.getAlphabetSize() << " membre(s) dans l'alphabet" << std::endl;

	automaton.prettyPrint(std::cout);

	//test();

*/

  	automaton.addState(1); 
    automaton.addState(2); 
    automaton.addState(8);
	automaton.addState(5);

	automaton.setStateInitial(1);
	automaton.setStateFinal(2);
	automaton.addTransition(1,'a',2);
	automaton.addTransition(2,'b',1);
	automaton.addTransition(1,'b',2);
	automaton.addTransition(2,'a',1);
	automaton.prettyPrint(std::cout);
	std::cout << "Complet : " << automaton.isComplete() << std::endl;
	std::cout << "Déterministe : " << automaton.isDeterministic() << std::endl;
	automaton.makeComplete();
	std::cout << "Complet : " << automaton.isComplete() << std::endl;
	automaton.prettyPrint(std::cout);

//vérifier ordre transitions


    return 0;
}
