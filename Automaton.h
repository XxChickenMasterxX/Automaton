#include <iostream> // Inclure ceci pour utiliser des "std::string"
#include <sstream>
#include <set> // Inclure ceci pour utiliser des ensembles (voir la déclaration d'attribut "std::set<int> states;" ci-dessous par exemple)
#include <tuple>
#include <list>
#include <iomanip>
#include <assert.h>

namespace fa{

    class Transition{
		public:
			Transition(int from, char alpha, int to);
			bool operator<(const Transition& t) const{
				return std::tie(from, alpha, to) < std::tie(t.from, t.alpha, t.to);
			}
			int getFrom() const;
			char getAlpha() const;
			int getTo() const;
			void setFrom(int st);
			void setTo(int st);
		private:
			int from;
			char alpha;
			int to;		
    };

    class Automaton{
        public:
			void print(const std::string s) const;
			bool findFinalState(int state) const;
			bool findInitialState(int state) const;
			void createProductRec(const Automaton& lhs, const Automaton& rhs, int rhsState, int lhsState, Automaton& res, int fromState, std::list<std::list<int>> coupleList);
			void createDeterministicRec(const Automaton& automaton, std::set<int> currStates, std::list<std::set<int>> stateList, Automaton& res, int stateFrom);
			static Automaton sortStates(const Automaton& automaton);
/************************************************************************/

            void addState(int state);
            void removeState(int state);
			bool hasState(int state) const;
			std::size_t countStates() const;
			void setStateInitial(int state);
			bool isStateInitial(int state) const;
			void setStateFinal(int state);
			bool isStateFinal(int state) const;
			void addTransition(int from, char alpha, int to);
			bool hasTransition(int from, char alpha, int to) const;
			void removeTransition(int from, char alpha, int to);
			std::size_t countTransitions() const;
			std::size_t getAlphabetSize() const;
			void dotPrint(std::ostream& os) const;
			void prettyPrint(std::ostream& os) const;
			bool isDeterministic() const;
			bool isComplete() const;
			void makeComplete();
			void makeComplement();
			bool isLanguageEmpty() const;
			void removeNonAccessibleStates();
			void removeNonCoAccessibleStates();
			static Automaton createProduct(const Automaton& lhs, const Automaton& rhs);
			bool hasEmptyIntersectionWith(const Automaton& other) const;
			std::set<int> readString(const std::string& word) const;
			bool match(const std::string& word) const;
			static Automaton createDeterministic(const Automaton& automaton);
			bool isIncludedIn(const Automaton& other) const;
			static Automaton createMinimalMoore(const Automaton& automaton);
			static Automaton createMinimalBrzozowski(const Automaton& automaton);
			static Automaton createMinimalHopcroft(const Automaton& automaton);
			static Automaton createWithoutEpsilon(const Automaton& automaton);

        private:
        	bool ifPrint=false;
            std::string name;
			std::set<int> states; 
             // L'ensemble des états de l'automate
            std::set<int> initialStates; // L'ensemble des états initiaux de l'automate
            std::set<int> finalStates; // L'ensemble des états initiaux de l'automate
			std::set<Transition> transition;        
			std::set<char> alphabet;    
			// Autres déclaration d'attributs (par exemple les transitions, pour lesquelles je vous conseille de créer une autre classe "Transition")...
    };

    // A vous de coder cette classe en prenant exemple sur la classe Automaton

};

