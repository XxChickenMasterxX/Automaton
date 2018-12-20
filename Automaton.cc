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

void fa::Automaton::addState(int state){
	assert(hasState(state) != true);
    states.insert(state);
}

void fa::Automaton::removeState(int state){
	assert(hasState(state) != false);
	states.erase(state);
	initialStates.erase(state);
	finalStates.erase(state);
		
	if(transition.size()!=0){ 
		std::set<Transition>::iterator tr;
		for(tr = transition.begin() ; tr != transition.end() ; ++tr){
			if(tr->getFrom() == state || tr->getTo() == state){
				transition.erase(*tr);
			}
		}
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
	assert(hasState(state) != false);
	initialStates.insert(state);		
}

bool fa::Automaton::isStateInitial(int state) const{
	assert(hasState(state) != false);
	if(initialStates.find(state) != initialStates.end()){
			return true;
	}
	return false;
}

void fa::Automaton::setStateFinal(int state){
	assert(hasState(state) != false);
	finalStates.insert(state);
}

bool fa::Automaton::isStateFinal(int state) const{
	assert(hasState(state) != false);
	if(finalStates.find(state) != finalStates.end()){
		return true;
	}
	return false;
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
	assert(hasState(from) != false);
	assert(hasState(to) != false);
	assert(isprint(alpha) || alpha == '\0');
	Transition t(from, alpha, to);
	transition.insert(t);
	alphabet.insert(alpha);
}
	
bool fa::Automaton::hasTransition(int from, char alpha, int to) const{
	assert(hasState(from) != false);
	assert(hasState(to) != false);
	//assert(isprint(alpha) || alpha == '\0');
	return transition.find(Transition(from, alpha, to)) != transition.end();
}

void fa::Automaton::removeTransition(int from, char alpha, int to){
	assert(hasTransition(from,alpha,to));
	
	transition.erase(Transition(from, alpha, to));
	
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
	std::set<Transition>::iterator tr;
	//definition du graph
	os << "digraph {" << std::endl; // ouverture
	os << "node [shape=circle]\nrankdir=LR;" << std::endl;
	
	//etats initaux
	if(!initialStates.empty())
	{
		for(it = initialStates.begin() ; it != initialStates.end() ; ++it)
		{
		    os << "-" << *it << " [shape=point];" << std::endl;
			os << "-" << *it << " -> " << *it << ";" << std::endl;
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
	if(initialStates.size() != 1){
		return false;
	}
	if(isStateFinal(*initialStates.begin())){
		return true;
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
	std::list<std::pair<int,char>> listValues;
	return true;
	//return findFinalState(*initialStates.begin(), listValues);
}

bool fa::Automaton::isComplete() const{
	std::set<Transition>::iterator tr;
	std::set<int>::iterator st;
	std::set<char>::iterator let;
	bool comp = false;	

	for(st = states.begin() ; st != states.end() ; ++st){
		for(let = alphabet.begin() ; let != alphabet.end() ; ++let){
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

	assert((*this).isDeterministic() != false);
	assert((*this).isComplete() != false);
	
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
		std::list<std::pair<int,char>> listValues;
		if(findFinalState(*st,listValues)){
			return false;
		}			
	}

	return true;
}

bool fa::Automaton::findFinalState(int state,std::list<std::pair<int,char>> listValues) const{
	std::set<Transition>::iterator tr;
	std::list<std::pair<int,char>>::iterator verif;
	bool unique = true;
	for(tr = transition.begin() ; tr != transition.end() ; ++tr){
		if(tr->getFrom() == state){
			if(isStateFinal(tr->getTo())){
				return true;
			}else{
				if(tr->getFrom() != tr->getTo()){
					for(verif = listValues.begin() ; verif != listValues.end() ; ++verif){
						if(verif->first == tr->getFrom() && verif->second == tr->getAlpha()){
							unique = false;
						}
					}
					if(unique){
						std::pair<int,char> newVal;
						newVal.first = tr->getFrom();
						newVal.second = tr->getAlpha();
						listValues.push_back(newVal);				
						return findFinalState(tr->getTo(),listValues);
					}
					unique = false;
				}
			}
		}
	}
	return false;
}

void fa::Automaton::removeNonAccessibleStates(){ // cas 
	std::set<int>::iterator st;
	std::set<int> test;
	std::list<std::pair<int,char>> listValues;
	for(st = states.begin() ; st != states.end() ; ++st){
		if(isStateInitial(*st)){
			continue;
		}
		if(!findInitialState(*st, listValues)){
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
	std::list<std::pair<int,char>> listValues;
	for(st = states.begin() ; st != states.end() ; ++st){
		if(isStateFinal(*st)){
			continue;
		}
		if(!findFinalState(*st, listValues)){
			test.insert(*st);
		}
	}
	for(st = test.begin() ; st != test.end() ; ++st){
		removeState(*st);
	}	
}

bool fa::Automaton::findInitialState(int state, std::list<std::pair<int,char>> listValues) const{
	std::set<Transition>::iterator tr;
	std::list<std::pair<int,char>>::iterator verif;
	bool unique = true;
	for(tr = transition.begin() ; tr != transition.end() ; ++tr){
		if(tr->getTo() == state){
			if(isStateInitial(tr->getFrom())){
				return true;
			}else{
				if(tr->getFrom() != tr->getTo()){
					for(verif = listValues.begin() ; verif != listValues.end() ; ++verif){
						if(verif->first == tr->getFrom() && verif->second == tr->getAlpha()){
							unique = false;
						}
					}
					if(unique){
						std::pair<int,char> newVal;
						newVal.first = tr->getFrom();
						newVal.second = tr->getAlpha();
						listValues.push_back(newVal);				
						return findInitialState(tr->getFrom(),listValues);
					}
					unique = false;
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
	std::set<int> path;
	std::set<Transition>::iterator tr;	
 
 	int st = *initialStates.begin();
 	path = readStringRec(word, st, 0, path);
	if(!path.empty()){
		path.insert(st);
	}
	return path;
}

std::set<int> fa::Automaton::readStringRec(const std::string& word, int st, size_t pos, std::set<int> path) const{
	std::set<Transition>::iterator tr;
	for(tr = transition.begin() ; tr != transition.end() ; ++tr){
		if(tr->getFrom() == st && tr->getAlpha() == word[pos]){
			if(pos == word.size() - 1 && isStateFinal(tr->getTo())){
				path.insert(tr->getTo());
				return path;	
			}
			path = readStringRec(word, tr->getTo(), ++pos, path);
			if(!path.empty()){
				path.insert(tr->getFrom());
				return path;
			}
		}		
	}
	return path;
		

}	

bool fa::Automaton::match(const std::string& word) const{
	if(word == ""){
		return true;
	}
	return !(readString(word).empty());
}

fa::Automaton fa::Automaton::createDeterministic(const Automaton& automaton){
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
	fa::Automaton curr = sortStates(automaton);
	fa::Automaton res;
	std::pair<std::pair<int,int>,std::list<int>> statesWithClasse;
	std::list<std::pair<std::pair<int,int>,std::list<int>>> Congruence;
	std::list<std::pair<std::pair<int,int>,std::list<int>>>::iterator listSt;
	std::list<std::list<std::pair<std::pair<int,int>,std::list<int>>>> listCongruence;
	std::list<std::list<std::pair<std::pair<int,int>,std::list<int>>>>::iterator cong;
	std::set<Transition>::iterator tr;
	std::set<char>::iterator alpha;
	std::set<int>::iterator st;
	std::list<int> verifSameCong;
	std::list<int> verifSameCong2;	
	bool sameCongruence = false;
	bool alreadyMinimal = false;
	bool newClasse;
	size_t numClasse = 1;
	std::list<int>::iterator states;
    
	assert(curr.isDeterministic() != false);
	assert(curr.isComplete() != false);

	res.alphabet = curr.alphabet;

	for(st = curr.states.begin() ; st != curr.states.end() ; ++st){
		newClasse = true;
		statesWithClasse.first.first = 1;
		statesWithClasse.first.second = *st;
		for(alpha = curr.alphabet.begin() ; alpha != curr.alphabet.end() ; ++alpha){ 
			for(tr = curr.transition.begin() ; tr != curr.transition.end() ; ++tr){
				if(*alpha == tr->getAlpha() && *st == tr->getFrom()){
					if(curr.isStateFinal(tr->getTo())){
						statesWithClasse.second.push_back(2);
					}else{
						statesWithClasse.second.push_back(1);
					}
				}
			}
		}
	

		for(listSt = Congruence.begin() ; listSt != Congruence.end() ; ++listSt){
			if(statesWithClasse.second == listSt->second){
				statesWithClasse.first.first = listSt->first.first;
				newClasse = false;
				break;
			}
		}
			
		if(newClasse){
			statesWithClasse.first.first = numClasse;
			++numClasse;
		}
			

		Congruence.push_back(statesWithClasse);
		statesWithClasse.second.clear();
	}

	listCongruence.push_back(Congruence);
	while(!sameCongruence){
		numClasse = 1;
		Congruence.clear();
		newClasse = true;
		int x = 1;

		for(st = curr.states.begin() ; st != curr.states.end() ; ++st){	
			statesWithClasse.first.first = numClasse;
			statesWithClasse.first.second = *st;	
			for(alpha = curr.alphabet.begin() ; alpha != curr.alphabet.end() ; ++alpha){
				for(tr = curr.transition.begin() ; tr != curr.transition.end() ; ++tr){
					if(*alpha == tr->getAlpha() && *st == tr->getFrom()){
						for(cong = --listCongruence.end() ; cong != listCongruence.end() ; ++cong){
							for(listSt = std::next((*cong).begin(),tr->getTo()) ; listSt != (*cong).end() ; ++listSt){//Maraboutage de haut niveau
								statesWithClasse.second.push_back(listSt->first.first);
								break;
							}
						}
					}
				}
			}
			

			for(listSt = Congruence.begin() ; listSt != Congruence.end() ; ++listSt){
				if(statesWithClasse.second == listSt->second){
					statesWithClasse.first.first = listSt->first.first;
					newClasse = false;
					break;
				}
			}

			if(newClasse){
				statesWithClasse.first.first = numClasse;
				++numClasse;
				
			}
			newClasse = true;
			++x;
			Congruence.push_back(statesWithClasse);
			statesWithClasse.second.clear();	
		}
		

		if(numClasse == res.states.size()){
			alreadyMinimal = true;
			break;	
		}
	
		for(cong = --listCongruence.end() ; cong != listCongruence.end() ; ++cong){
			for(listSt = (*cong).begin() ; listSt != (*cong).end() ; ++listSt){
				verifSameCong.push_back(listSt->first.first);
			}
		}
		
		for(listSt = Congruence.begin() ; listSt != Congruence.end() ; ++listSt){
			verifSameCong2.push_back(listSt->first.first);
		}

		if(verifSameCong == verifSameCong2){
			sameCongruence = true;
		}
		verifSameCong.clear();
		verifSameCong2.clear();
		listCongruence.push_back(Congruence);

	}

	if(alreadyMinimal){
		return automaton;
	}


	for(size_t i = 1 ; i < numClasse ; ++i){
		res.addState(i);
	}

	for(cong = --listCongruence.end() ; cong != listCongruence.end() ; ++cong){
		for(listSt = (*cong).begin() ; listSt != (*cong).end() ; ++listSt){
			if(curr.isStateInitial(listSt->first.second)){
				res.setStateInitial(listSt->first.first);
			}
			if(curr.isStateFinal(listSt->first.second)){
				res.setStateFinal(listSt->first.first);
			}
		}
	}

	int stateCurr = 0;

	for(cong = --listCongruence.end() ; cong != listCongruence.end() ; ++cong){
		for(listSt = (*cong).begin() ; listSt != (*cong).end() ; ++listSt){
			if(stateCurr < listSt->first.first){
				++stateCurr;
				alpha = res.alphabet.begin();
				states = listSt->second.begin();
				while(alpha != res.alphabet.end()){
					res.addTransition(stateCurr,*alpha,*states);	
					++alpha;
					++states;			
				}	
			}					
		}
	}

	return res;
}

Automaton fa::Automaton::sortStates(const Automaton& automaton){
	std::set<Transition>::iterator tr;
	std::set<int>::iterator st;
	Automaton res;

	for(st = automaton.states.begin() ; st != automaton.states.end() ; ++st){
		int newState = res.states.size();
		res.addState(newState);

		if(automaton.isStateInitial(*st)){
			res.setStateInitial(newState);
		}

		if(automaton.isStateFinal(*st)){
			res.setStateFinal(newState);
		}
	}

	for(tr = automaton.transition.begin() ; tr != automaton.transition.end() ; ++tr){
		int from = std::distance(automaton.states.begin(), automaton.states.find(tr->getFrom()));
		int to = std::distance(automaton.states.begin(), automaton.states.find(tr->getTo()));
		res.addTransition(from,tr->getAlpha(),to);				
	}
		
	return res;
}

void fa::Transition::setFrom(int st){
	from = st;
}

void fa::Transition::setTo(int st){
	to = st;	
}

Automaton fa::Automaton::createMinimalBrzozowski(const Automaton& automaton){
    fa::Automaton curr = sortStates(automaton);
	assert(curr.isDeterministic() != false);
	assert(curr.isComplete() != false);
    fa::Automaton res;
    return res;
}
    
Automaton fa::Automaton::createMinimalHopcroft(const Automaton& automaton){
    fa::Automaton curr = sortStates(automaton);
	assert(curr.isDeterministic() != false);
	assert(curr.isComplete() != false);
    fa::Automaton res;
    return res;
}

Automaton fa::Automaton::createWithoutEpsilon(const Automaton& automaton){
	std::set<Transition>::iterator tr;
	std::set<int>::iterator st;
	std::set<char>::iterator alpha;
	Automaton res = automaton;
	
	for(tr = res.transition.begin() ; tr != res.transition.end() ; ++tr){
		
		if(tr->getAlpha() == '\0'){
			res.removeTransition(tr->getFrom(),tr->getAlpha(),tr->getTo());
			res = res.createWithoutEpsilonRec(res, tr->getFrom(), tr->getTo());
			if(res.countTransitions() > 0){ 
				tr = res.transition.begin();
			}
		}	
	}
	 
	
	return res;
}

Automaton fa::Automaton::createWithoutEpsilonRec(const Automaton& automaton, int from, int to){
	std::set<Transition>::iterator tr;
	Automaton res = automaton;

	for(tr = res.transition.begin() ; tr != res.transition.end() ; ++tr){
		if(tr->getFrom() == to){
			if(tr->getAlpha() == '\0'){
				res = res.createWithoutEpsilonRec(res, from, tr->getTo());
			}else{
				res.addTransition(from, tr->getAlpha(), tr->getTo());
				if(res.isStateFinal(tr->getTo())){
					res.setStateFinal(from);
				}
			}
		}
	}
			
	return res;
}
}
