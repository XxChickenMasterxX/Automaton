#include "Automaton.h"

#include <cassert>

namespace fa {

std::ostream& operator<<(std::ostream& stream, const fa::Transition& transition){
	return stream << transition.getFrom() << " vers " << transition.getTo() << " avec le caractère " << transition.getAlpha(); 
}

void fa::Automaton::print(std::string s) const{
	if(ifPrint)
		std::cout << s << std::endl;
}

// Dans ce fichier, on place les DÉFINITIONS des méthodes de la class Automaton

// On reprend la signature de la fonction "addState" en rajoutant "fa::Automaton::" devant le nom de la méthode, ce qui donne :
void fa::Automaton::addState(int state){
    // Ici, on écrit le code pour ajouter un état à l'automate
    // La méthode "addState" doit naturellement ajouter un état à l'automate
    // On ajoute donc l'état "state" à l'ensemble des états de l'automate (donc à l'attribut "states"):
    states.insert(state);
    // Pour débugger plus facilement, vous pouvez afficher le nombre d'états dans l'automate après insertion :
    std::ostringstream oss;
    oss << "Après insertion de l'état " << state << ", l'automate possède " << states.size() << " état(s).";
    print(oss.str());
}

void fa::Automaton::removeState(int state){
	if(hasState(state)){
		states.erase(state);
		initialStates.erase(state);
		finalStates.erase(state);
		
		/**/
		if(transition.size()!=0){ 
			std::set<Transition>::iterator tr;
			for(tr = transition.begin() ; tr != transition.end() ; ++tr){
				if(tr->getFrom() == state || tr->getTo() == state){
					transition.erase(*tr);
				}
			}
		}
		std::ostringstream oss;
  	 	oss << "Après la suprression de l'état " << state << ", l'automate possède " << states.size() << " état(s).";
  	 	print(oss.str());
	}else{
		std::ostringstream oss;
		oss << "Etat non présent\n";
		print(oss.str());
	}	
	
}

bool fa::Automaton::hasState(int state) const{
	return states.find(state) != states.end();
}

std::size_t fa::Automaton::countStates() const{
	std::ostringstream oss;
	oss << "Il y a" << states.size() << "état(s).\n";
	print(oss.str());
	return states.size();
}

void fa::Automaton::setStateInitial(int state){
	if(hasState(state)){
		initialStates.insert(state);
	}else{
		std::ostringstream oss;
		oss << "Etat non présent\n";
		print(oss.str());
	}		
}

bool fa::Automaton::isStateInitial(int state) const{
	if(hasState(state)){
		if(initialStates.find(state) != initialStates.end()){
			return true;
		}
	return false;
	}else{
		std::ostringstream oss;
		oss << "Etat non présent\n";
		print(oss.str());
		return false;
	}	
}

void fa::Automaton::setStateFinal(int state){
	if(hasState(state)){
		finalStates.insert(state);
	}else{
		std::ostringstream oss;
		oss << "Etat non présent\n";
		print(oss.str());
	}		
}

bool fa::Automaton::isStateFinal(int state) const{
	if(hasState(state)){
		if(finalStates.find(state) != finalStates.end()){
			return true;
		}
	return false;
	}else{
		std::ostringstream oss;
		oss << "Etat non présent\n";
		print(oss.str());
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
	std::ostringstream oss;
	if(hasState(from) && hasState(to) && isprint(alpha)){
		Transition t(from, alpha, to);
		transition.insert(t);
		alphabet.insert(alpha);
		oss << "Insertion de la transition de l'état " << from << " vers l'état " << to << " avec comme lettre : " << alpha;
	}else{
		oss << "Un ou plusieurs états ne sont pas présents\n";
	}	
	print(oss.str());
}
	
bool fa::Automaton::hasTransition(int from, char alpha, int to) const{
	return transition.find(Transition(from, alpha, to)) != transition.end();
}

void fa::Automaton::removeTransition(int from, char alpha, int to){
	std::ostringstream oss;
	if(hasTransition(from, alpha, to)){
		transition.erase(Transition(from, alpha, to));
  	 	oss << "Après la suprression de la transition " << Transition(from, alpha, to) << ", l'automate possède " << transition.size() << " transition(s).";
	}else{
		oss << "Etat non présent\n";
	}	
	print(oss.str());
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
	
	os << "Initial states:" << std::endl << "\t";
	if(initialStates.empty()){
		os << "No initial states" << std::endl;
	}else{
		for(it = initialStates.begin() ; it != initialStates.end() ; ++it){
			os << *it << " ";
		}
		os << std::endl;
	}

	os << "Final states:" << std::endl << "\t";
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
		os << "\tNo Transitions" << std::endl;
	}else{
		for(it = states.begin() ; it != states.end() ; ++it){
		    os << "\tFor state " << *it << ":" << std::endl;
			for(let = alphabet.begin() ; let != alphabet.end() ; ++let){
				os << "\t\tFor letter " << *let << ": ";
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

void fa::Automaton::dotPrint(std::ostream& os) const{
// for use in terminal : dot -Tpng -oNOMFICHIER.png NOMFICHIER.dot
	std::set<int>::iterator it;	
	std::set<char>::iterator let;
	std::set<Transition>::iterator tr;
	//definition du graph
	os << "digraph {" << std::endl; // ouverture
	os << "node [shape=circle];" << std::endl;
	
	//etats initaux
	if(!initialStates.empty())
	{
		for(it = initialStates.begin() ; it != initialStates.end() ; ++it)
		{
		    os << "-" << *it << " [shape=point];" << std::endl;
			os << "-" << *it << " -> " << *it << "[weight=666];" << std::endl;
		}
	}

    //etats finaux
	if(!finalStates.empty())
	{
		for(it = finalStates.begin() ; it != finalStates.end() ; ++it)
		{
			os << *it << " [shape=doublecircle];" << std::endl;
		}
	}
    
    //transitions et etats neutres
	if(!transition.empty())
	{
		for(tr = transition.begin() ; tr != transition.end() ; ++tr)
		{
		    os << tr->getFrom() << " -> " << tr->getTo() << " [label=\"" << tr->getAlpha() << "\"];" << std::endl; // transitions
		}
	}
	os << "}" << std::endl; // fermeture du graph
}


bool fa::Automaton::isDeterministic() const{
	if(initialStates.size() != 1 || finalStates.empty()){
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
	//return findFinalState(*initialStates.begin());
}

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

	for(st = states.begin() ; st != states.end() ; ++st){	
		for(let = alphabet.begin() ; let != alphabet.end() ; ++let){
			for(tr = transition.begin() ; tr != transition.end() ; ++tr){
				if(*st != tr->getFrom()){//test si l'état de départ correspond à celui recherché
					break;
				}
				if(*let == tr->getAlpha() && *st == tr->getFrom()){//test si la transition part du bon etat avec la bonne lettre
					res = true;//Boolean pour éviter de rajouter plusieurs fois la meme transition
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

void fa::Automaton::makeComplement(){
	if(!isDeterministic() || !isComplete()){
		std::ostringstream oss;
		oss << "L'automate doit être complet et déterministe" ;
		print(oss.str());
		return;
	}

	std::set<int>::iterator st;

	for(st = states.begin() ; st != states.end() ; ++st){
		if(isStateFinal(*st)){
			finalStates.erase(*st);
		}else {
			setStateFinal(*st);			
		}
	}
}

bool fa::Automaton::isLanguageEmpty() const{
	if(initialStates.empty() || finalStates.empty()){
		return true;
	}

	std::set<int>::iterator st;
	
	for(st = initialStates.begin() ; st != initialStates.end() ; ++st){
		return !(findFinalState(*st));
	}

	return true;
}

bool fa::Automaton::findFinalState(int state) const{
	std::set<Transition>::iterator tr;
	for(tr = transition.begin() ; tr != transition.end() ; ++tr){
		if(tr->getFrom() == state){
			if(isStateFinal(tr->getTo())){
				return true;
			}else{
				if(tr->getFrom() != tr->getTo()){
					return findFinalState(tr->getTo());
				}
			}
		}
	}
	return false;
}

void fa::Automaton::removeNonAccessibleStates(){ // cas 
	std::set<int>::iterator st;
	std::set<int> test;
	for(st = states.begin() ; st != states.end() ; ++st){
		if(isStateInitial(*st)){
			continue;
		}
		if(!findInitialState(*st)){
			test.insert(*st);
		}
		
	}
	for(st = test.begin() ; st != test.end() ; ++st){
		removeState(*st);
	}
}

void fa::Automaton::removeNonCoAccessibleStates(){
	std::set<int>::iterator st;
	std::set<int> test;
	for(st = states.begin() ; st != states.end() ; ++st){
		if(isStateFinal(*st)){
			continue;
		}
		if(!findFinalState(*st)){
			test.insert(*st);
		}
	}
	for(st = test.begin() ; st != test.end() ; ++st){
		removeState(*st);
	}	
}

bool fa::Automaton::findInitialState(int state) const{
	std::set<Transition>::iterator tr;
	for(tr = transition.begin() ; tr != transition.end() ; ++tr){
		if(tr->getTo() == state){
			if(isStateInitial(tr->getFrom())){
				return true;
			}else{
				if(tr->getFrom() != tr->getTo()){
					return findInitialState(tr->getFrom());
				}
			}
		}
	}
	return false;
}

Automaton fa::Automaton::createProduct(const Automaton& lhs, const Automaton& rhs){
  	fa::Automaton res;
	if(lhs.initialStates.empty() || rhs.initialStates.empty() || lhs.finalStates.empty() || rhs.finalStates.empty()){
		return res;
	}		

	std::set<int>::iterator lhsSt;
	std::set<int>::iterator rhsSt;
	std::set<char>::iterator lt;
	std::set<char>::iterator lt2;
	std::set<int> lhsStates;
	std::set<int> rhsStates;
	std::list<std::list<int>> coupleList;
	std::list<int> couple;
	std::list<std::list<int>>::iterator cp;
	bool newCp = true;

	for(lt = lhs.alphabet.begin() ; lt != lhs.alphabet.end() ; ++lt){
		for(lt2 = rhs.alphabet.begin() ; lt2 != rhs.alphabet.end() ; ++lt2){
			if(*lt == *lt2){
				res.alphabet.insert(*lt);
				break;
			}	
		}
	}
	if(res.alphabet.empty()){
		return res;
	}
	
	for(lhsSt = lhs.initialStates.begin() ; lhsSt != lhs.initialStates.end() ; ++lhsSt){
		for(rhsSt = rhs.initialStates.begin() ; rhsSt != rhs.initialStates.end() ; ++rhsSt){
			couple.push_back(*lhsSt);
			couple.push_back(*rhsSt);
			for(cp = coupleList.begin() ; cp != coupleList.end() ; ++cp){
				if(*cp == couple){
					newCp = false;
					break;
				}
			}
			
			if(newCp){
				coupleList.push_back(couple);		
				int newState = res.states.size();
				res.addState(newState);
				res.setStateInitial(newState);
				if(lhs.isStateFinal(*lhsSt) && rhs.isStateFinal(*rhsSt)){
					res.setStateFinal(newState);
				}
				res.createProductRec(lhs, rhs, *rhsSt, *lhsSt, res, newState, coupleList);
			}
			newCp = true;
			couple.clear();		
		}
	}
	return res;
}

void fa::Automaton::createProductRec(const Automaton& lhs, const Automaton& rhs, int rhsState, int lhsState, Automaton& res, int fromState, std::list<std::list<int>> coupleList){

	std::set<char>::iterator alpha;
	std::set<int>::iterator lhsSt;
	std::set<int>::iterator rhsSt;
	std::set<int> newLhsStates;
	std::set<int> newRhsStates;
	std::set<Transition>::iterator tr;
	std::list<int> couple;
	std::list<std::list<int>>::iterator cp;
	bool newCp = true;
	int compteur = 0;
	
	for(alpha = res.alphabet.begin() ; alpha != res.alphabet.end() ; ++alpha){
		newRhsStates.clear();
		newLhsStates.clear();
	
		for(tr = rhs.transition.begin() ; tr != rhs.transition.end() ; ++tr){
			if(tr->getFrom() == rhsState && tr->getAlpha() == *alpha){
				newRhsStates.insert(tr->getTo());
			}			
		}
		if(newRhsStates.size() == 0){
			continue;
		}
		
		for(tr = lhs.transition.begin() ; tr != lhs.transition.end() ; ++tr){
			if(tr->getFrom() == lhsState && tr->getAlpha() == *alpha){
				newLhsStates.insert(tr->getTo());
			}			
		}
		if(newLhsStates.size() == 0){
			continue;
		}

		for(lhsSt = newLhsStates.begin() ; lhsSt != newLhsStates.end() ; ++lhsSt){
			for(rhsSt = newRhsStates.begin() ; rhsSt != newRhsStates.end() ; ++rhsSt){
				couple.push_back(*lhsSt);
				couple.push_back(*rhsSt);
				for(cp = coupleList.begin() ; cp != coupleList.end() ; ++cp){
					if(*cp == couple){
						newCp = false;
						break;
					}
					++compteur;
				}

				if(!newCp){
					res.addTransition(fromState, *alpha, compteur);	
				}
				if(newCp){
					int newState = res.states.size();
					res.addState(newState);
					res.addTransition(fromState, *alpha, newState);
					coupleList.push_back(couple);
					if(lhs.isStateFinal(*lhsSt) && rhs.isStateFinal(*rhsSt)){
						res.setStateFinal(newState);
					}
					if(lhs.isStateInitial(*lhsSt) && rhs.isStateInitial(*rhsSt)){
						res.setStateInitial(newState);
					}
					res.createProductRec(lhs, rhs, *rhsSt, *lhsSt, res, newState, coupleList);	
				}
				compteur = 0;
				newCp = true;
				couple.clear();
			}
		}				
	}

}

bool fa::Automaton::hasEmptyIntersectionWith(const Automaton& other) const{
	fa::Automaton newAutomaton = createProduct(other, (*this));
	return newAutomaton.isLanguageEmpty();
}


std::set<int> fa::Automaton::readString(const std::string& word) const{
	std::set<int> rambo;
	std::set<Transition>::iterator tr;
	bool hasTrans = false;
	
	if(!isDeterministic()){
		return rambo;
	}
 
 	int st = *initialStates.begin();
 	rambo.insert(st);
 
	for(size_t i = 0 ; i < word.size() ; ++i){		
		for(tr = transition.begin() ; tr != transition.end() ; ++tr){
			if(tr->getFrom() == st && tr->getAlpha() == word[i]){
				hasTrans = true;
				st = tr->getTo();
				rambo.insert(st);
				break;
			}
		}
		if(!hasTrans){
			rambo.clear();
			return rambo;
		}
	}
	if(!isStateFinal(st)){
		rambo.clear();		
	}
	return rambo;
}

bool fa::Automaton::match(const std::string& word) const{
	return !readString(word).empty();
}

Automaton fa::Automaton::createDeterministic(const Automaton& automaton){
	if(automaton.isDeterministic() || automaton.isLanguageEmpty()){
		return automaton;
	}
  	fa::Automaton res;
	std::set<int>::iterator st;
	std::set<char>::iterator alpha;
	std::list<std::set<int>> stateList;
	stateList.push_back(automaton.initialStates);
	res.addState(0);		
	res.setStateInitial(0);

	for(alpha = automaton.alphabet.begin() ; alpha != automaton.alphabet.end() ; ++alpha){ 
		res.alphabet.insert(*alpha);
	}
	for(st = automaton.initialStates.begin() ; st != automaton.initialStates.end() ; ++st){
		if(automaton.isStateFinal(*st)){
			res.setStateFinal(0);
			break;
		}
	}
	res.createDeterministicRec(automaton, automaton.initialStates, stateList, res, 0);
	return res;
}

void fa::Automaton::createDeterministicRec(const Automaton& automaton, std::set<int> currStates, std::list<std::set<int>> stateList, Automaton& res, int stateFrom){
	std::set<int>::iterator st;
	std::set<char>::iterator alpha;
	std::set<Transition>::iterator tr;
	std::set<int> newStates;
	std::list<std::set<int>>::iterator listSt;
	bool isListNew = true;
	bool isFinal = false;
	int cpt = 0;

	for(alpha = res.alphabet.begin() ; alpha != res.alphabet.end() ; ++alpha){
		for(st = currStates.begin() ; st != currStates.end() ; ++st){
			for(tr = automaton.transition.begin() ; tr != automaton.transition.end() ; ++tr){
				if(tr->getFrom() == *st && tr->getAlpha() == *alpha){
					newStates.insert(tr->getTo());
					if(automaton.isStateFinal(tr->getTo())){
						isFinal = true;
					}		
				}
			}
		}
		if(newStates.empty()){
			continue;
		}
		for(listSt = stateList.begin() ; listSt != stateList.end() ; ++listSt){
			if(*listSt == newStates){
				isListNew = false;
				break;
			}
			++cpt;
		}

		if(isListNew){
			stateList.push_back(newStates);
			int newState = res.states.size();
			res.addState(newState);
			if(isFinal){
				res.setStateFinal(newState);
				isFinal = false;
			}
			res.addTransition(stateFrom, *alpha, newState);
			createDeterministicRec(automaton, newStates, stateList, res, newState);
		}else{
			res.addTransition(stateFrom, *alpha, cpt);
			isListNew = true;	
		}
		cpt = 0;
	}		
}

bool fa::Automaton::isIncludedIn(const Automaton& other) const{
	fa::Automaton newAutomaton = other;
	newAutomaton.makeComplement();
	return createProduct((*this), newAutomaton).isLanguageEmpty();
}

Automaton fa::Automaton::createMinimalMoore(const Automaton& automaton){
	fa::Automaton curr = automaton;
	fa::Automaton res;
	std::pair<int,std::list<int>> statesWithClasse;
	std::list<std::pair<int,std::list<int>>> Congruence;
	std::list<std::pair<int,std::list<int>>>::iterator listSt;
	std::list<std::pair<int,std::list<int>>>::iterator sameSt;
	std::list<std::pair<int,std::list<int>>>::iterator sameSt2;
	std::list<std::list<std::pair<int,std::list<int>>>> listCongruence;
	std::list<std::list<std::pair<int,std::list<int>>>>::iterator cong;
	std::set<Transition>::iterator tr;
	std::set<char>::iterator alpha;
	std::set<int>::iterator st;
	std::list<int>::iterator stateParam;
	bool sameCongruence = false;
	bool uniqueCongruence = true;
	bool newClasse = true;
	int numClasse = 0;

	if(!curr.isDeterministic()){
		curr = createDeterministic(curr);
	} 
	if(!curr.isComplete()){
		curr.makeComplete();
	}

	for(alpha = automaton.alphabet.begin() ; alpha != automaton.alphabet.end() ; ++alpha){ 
		res.alphabet.insert(*alpha);
	}
	
	for(alpha = res.alphabet.begin() ; alpha != res.alphabet.end() ; ++alpha){
		for(st = curr.states.begin() ; st != curr.states.end() ; ++st){
			for(tr = automaton.transition.begin() ; tr != automaton.transition.end() ; ++tr){
				if(automaton.isStateFinal(tr->getFrom())){
					statesWithClasse.first = 1;
				}
				if(automaton.isStateFinal(tr->getTo())){
					statesWithClasse.second.push_back(2);
				}else{
					statesWithClasse.second.push_back(1);
				}
			}
		}	
	}

	Congruence.push_back(statesWithClasse);
	statesWithClasse.second.clear();
	
	while(!sameCongruence){
		uniqueCongruence = true;
		newClasse = true;
		numClasse = 0;
		for(tr = automaton.transition.begin() ; tr != automaton.transition.end() ; ++tr){
			statesWithClasse.second.push_back(tr->getTo());
					
				}
				for(listSt = Congruence.begin() ; listSt != Congruence.end() ; ++listSt){
					if(listSt->second == statesWithClasse.second){
						statesWithClasse.first = listSt->first;
						newClasse = false;
						break;
					}
				}
				if(newClasse){
					statesWithClasse.first = numClasse;
					++numClasse;
				} 
				Congruence.push_back(statesWithClasse);
				statesWithClasse.second.clear();

		for(sameSt = Congruence.begin() ; sameSt != Congruence.end() ; ++sameSt){
			for(sameSt2 = ++sameSt ; sameSt2 != Congruence.end() ; ++sameSt2){
				if(*sameSt == *sameSt2){
					uniqueCongruence == false;
				}					
			}
		}

		if(uniqueCongruence){
			break;
		}	
		
		for(cong = listCongruence.begin() ; cong != listCongruence.end() ; ++cong){
			if(*cong == Congruence){
				sameCongruence == true;
			}
		}
				
	}

	if(uniqueCongruence){
		return curr;
	}

	//Congruence = --listCongruence.end();
	/*for(listSt = Congruence.begin() ; listSt != Congruence.end() ; ++listSt){
		if(res.hasState(listSt->first)){
			continue;
		}
		res.addState(listSt->first));
		for(stateParam = listSt->first.begin() ; stateParam != listSt->first.end() ; ++stateParam){
			if(automaton.isStateInitial(*stateParam)){
				res.setStateInitial(listSt->first);
			}	
			if(automaton.isStateFinal(*stateParam)){
				res.setStateFinal(listSt->first);
			}
			
		}
		
	}*/
	res.alphabet = automaton.alphabet;
	return res;
}
	
}
