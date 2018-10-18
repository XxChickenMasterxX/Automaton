#include "Automaton.h"

#include <cassert>

namespace fa {

std::ostream& operator<<(std::ostream& stream, const fa::Transition& transition){
	return stream << transition.getFrom() << " vers " << transition.getTo() << " avec le caractère " << transition.getAlpha(); 
}

// Dans ce fichier, on place les DÉFINITIONS des méthodes de la class Automaton

// On reprend la signature de la fonction "addState" en rajoutant "fa::Automaton::" devant le nom de la méthode, ce qui donne :
void fa::Automaton::addState(int state){
    // Ici, on écrit le code pour ajouter un état à l'automate
    // La méthode "addState" doit naturellement ajouter un état à l'automate
    // On ajoute donc l'état "state" à l'ensemble des états de l'automate (donc à l'attribut "states"):
    states.insert(state);
    // Pour débugger plus facilement, vous pouvez afficher le nombre d'états dans l'automate après insertion :
    std::cout << "Après insertion de l'état " << state << ", l'automate possède " << states.size() << " état(s)." << std::endl;
}

void fa::Automaton::removeState(int state){
	if(hasState(state)){
		states.erase(state);
		initialStates.erase(state);
		finalStates.erase(state);
  	 	std::cout << "Après la suprression de l'état " << state << ", l'automate possède " << states.size() << " état(s)." << std::endl;
	}else{
		std::cout << "Etat non présent\n";
	}	
}

bool fa::Automaton::hasState(int state) const{
	return states.find(state) != states.end();
}

std::size_t fa::Automaton::countStates() const{
	std::cout << "Il y a" << states.size() << "état(s).\n";
	return states.size();
}

void fa::Automaton::setStateInitial(int state){
	if(hasState(state)){
		initialStates.insert(state);
	}else{
		std::cout << "Etat non présent\n";
	}		
}

bool fa::Automaton::isStateInitial(int state) const{
	if(hasState(state)){
		if(initialStates.find(state) != initialStates.end()){
			return true;
		}
	return false;
	}else{
		std::cout << "Etat non présent\n";
		return false;
	}	
}

void fa::Automaton::setStateFinal(int state){
	if(hasState(state)){
		finalStates.insert(state);
	}else{
		std::cout << "Etat non présent\n";
	}		
}

bool fa::Automaton::isStateFinal(int state) const{
	if(hasState(state)){
		if(finalStates.find(state) != finalStates.end()){
			return true;
		}
	return false;
	}else{
		std::cout << "Etat non présent\n";
		return false;
	}	
}

int fa::Transition::getFrom() const{
	return from;
}
		
char fa::Transition::getAlpha() const{
	return alpha;
}

int fa::Transition::getTo() const{
	return to;
}

fa::Transition::Transition(int from, char alpha, int to){
	this->from = from;
	this->alpha = alpha;
	this->to = to;
}

void fa::Automaton::addTransition(int from, char alpha, int to){
	if(hasState(from) && hasState(to)){
		Transition t(from, alpha, to);
		transition.insert(t);
		alphabet.insert(alpha);
		std::cout << "Insertion de la transition de l'état " << from << " vers l'état " << to << " avec comme lettre : " << alpha << std::endl;
	}else{
		std::cout << "Un ou plusieurs états ne sont pas présents\n";
	}	
}
	
bool fa::Automaton::hasTransition(int from, char alpha, int to) const{
	return transition.find(Transition(from, alpha, to)) != transition.end();
}

void fa::Automaton::removeTransition(int from, char alpha, int to){
	if(hasTransition(from, alpha, to)){
		transition.erase(Transition(from, alpha, to));
  	 	std::cout << "Après la suprression de la transition " << Transition(from, alpha, to) << ", l'automate possède " << transition.size() << " transition(s)." << std::endl;
	}else{
		std::cout << "Etat non présent\n";
	}	
}

std::size_t fa::Automaton::countTransitions() const{
	return transition.size(); 
}

std::size_t fa::Automaton::getAlphabetSize() const{
	return alphabet.size();
}

void fa::Automaton::prettyPrint(std::ostream& os) const{

	std::set<int>::iterator it;	
	std::set<char>::iterator let;
	std::set<Transition>::iterator tr;
	
	os << "Initial states:" << std::endl << "	";
	if(initialStates.empty()){
		os << "No initial states" << std::endl;
	}else{
		for(it = initialStates.begin() ; it != initialStates.end() ; ++it){
			os << *it << " ";
		}
		os << std::endl;
	}

	os << "Final states:" << std::endl << "	";
	if(finalStates.empty()){
		os << "No final states" << std::endl;	
	}else{
		for(it = finalStates.begin() ; it != finalStates.end() ; ++it){
			os << *it << " ";
		}
		os << std::endl;
	}

	os << "Transitions:" << std::endl;
	if(transition.empty()){
		os << "No Transitions" << std::endl;
	}else{
		for(it = states.begin() ; it != states.end() ; ++it){
		os << "	For state " << *it << ":" << std::endl;
			for(let = alphabet.begin() ; let != alphabet.end() ; ++let){
				os << "		For letter " << *let << ": ";
					for(tr = transition.begin() ; tr != transition.end() ; ++tr){
						if(tr->getFrom() == *it && tr->getAlpha() == *let){
							os << tr->getTo() << " ";
						}
					}
				os << std::endl;
			}
		}
	}		
}

bool fa::Automaton::isDeterministic() const{
	if(initialStates.size() != 1 && finalStates.empty()){
		return false;
	}
	//test si il n'y a pas d'ambiguité lors d'une transition
	std::set<Transition>::iterator tr;
	std::set<int>::iterator st;
	std::set<char>::iterator let;
	bool det = false;	
	

	for(st = states.begin() ; st != states.end() ; ++st){	
		for(let = alphabet.begin() ; let != alphabet.end() ; ++let){
			for(tr = transition.begin() ; tr != transition.end() ; ++tr){
				if(*let == tr->getAlpha() && *st == tr->getFrom()){ 
					if(det == true){
						return false;
					}
					det = true;
				}
			}
			det = false;
		}
	}

	return true;
}

/*std::set<Transition> fa::Automaton::findStateTransition (int state){
	std::set<Transition>:: stateTransitions;
	std::set<Transition>::iterator tr;
	
	for(tr = transition.begin() ; tr != transition.end) ; tr++){
		if(*tr.getFrom() == state){
			stateTransitions.add(transition.find(*tr);
		}
	}	
	
	return stateTransitions;
}*/

bool fa::Automaton::isComplete() const{
	std::set<Transition>::iterator tr;
	std::set<int>::iterator st;
	std::set<char>::iterator let;
	bool comp = false;	

	for(st = states.begin() ; st != states.end() ; ++st){
		for(let = alphabet.begin() ; let != alphabet.end() ; ++let){
			//Optimiser transition avec un find	
			for(tr = transition.begin() ; tr != transition.end() ; ++tr){
				if(*let == tr->getAlpha() && *st == tr->getFrom()){
					comp = true;
				}
			}
			if(!comp){
				return false;
			}
			comp = false;
		}
	}
	return true;
}

void fa::Automaton::makeComplete() {
	if(isComplete()){
		return;
	}

	std::set<int>::iterator st = states.end();
	std::set<char>::iterator let;
	std::set<Transition>::iterator tr;
	bool res = false;
	--st;
	int max = *st + 1;
	
	addState(max);

	for(st = finalStates.begin() ; st != finalStates.end() ; ++st){
		for(let = alphabet.begin() ; let != alphabet.end() ; ++let){
			addTransition(*st,*let,max);
		}
	}

	for(st = states.begin() ; st != states.end() ; ++st){
		if(isStateFinal(*st))
			continue;	
		for(let = alphabet.begin() ; let != alphabet.end() ; ++let){
			for(tr = transition.begin() ; tr != transition.end() ; ++tr){
				if(*st != tr->getFrom()){
					break;
				}
				if(*let == tr->getAlpha() && *st == tr->getFrom()){
					res = true;
					break;
				}					
			}
			if(res){
				res = false;
				continue;				
			}
			addTransition(*st,*let,max);			
		}
	}

	
	
	
}
}
