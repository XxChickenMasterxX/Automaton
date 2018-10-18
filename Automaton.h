#include <iostream> // Inclure ceci pour utiliser des "std::string"
#include <set> // Inclure ceci pour utiliser des ensembles (voir la déclaration d'attribut "std::set<int> states;" ci-dessous par exemple)
#include <tuple>

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
		private:
			int from;
			char alpha;
			int to;		
    };

    class Automaton{
        public:
            // Ici, on place les signatures des méthodes de la classe Automaton, par exemple pour addState et removeState :
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
			void prettyPrint(std::ostream& os) const;
			bool isDeterministic() const;
			bool isComplete() const;
			void makeComplete();
			void makeComplement();

        private:
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

