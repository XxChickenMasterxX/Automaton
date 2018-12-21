#include "Automaton.h"

//-----------------------------------------
//-------------- Dot File -----------------
//-----------------------------------------
/*
    permet de crée un fichier .dot représentant l'automat
*/
void toDot(fa::Automaton fa){ 
    std::ofstream fichier("YourAutomaton.dot", std::ios::out | std::ios::trunc);
	if(fichier)
	{
	    fa.dotPrint(fichier);
	    std::cerr << "dot creation succed" << std::endl;
	}else
	    std::cerr << "fail create YourAutomaton.dot file " << std::endl;
	// pour convertir le .dot en fichier image
	// dans le terminal :
	//dot -Tpng -oGrapheTest.png GrapheTest.dot
}

//-----------------------------------------
//-------------- Manipulation -------------
//-----------------------------------------
void manipulateState(fa::Automaton *fa){
     int state;
    bool back=false;
    int choix =-1;
    while(!back){
        std::cout << "\n --- Manipulate State --- \n\tAdd lambda state press 1\n\tAdd initial state press 2\n\tAdd final state press 3\n\tRemove state press 4\n\tCount state press 5\n\tBack press 0"<< std::endl;
        while(!(std::cin >> choix)){
            std::cout << "\nerror, you must enter an Integer!\n\tYour choice : ";
        }
        switch(choix){
            case 1:
                
                 std::cout << " --- Add State --- \nTo add one state write the name of the state (the name must be an Integer)\n\tState name : ";
                while(!(std::cin >> state)){
                    std::cout << "error, the name must be an Integer\n\tState name : ";
                }
                fa->addState(state);
                break;
            case 2:
               
                 std::cout << " --- Add Initial State--- \nTo create or set an initial state write the name of the state (the name must be an Integer)\n\tState name : ";
                while(!(std::cin >> state)){
                    std::cout << "error, the name must be an Integer\n\tState name : ";
                }
                if(!fa->hasState(state)){
                    fa->addState(state);
                }
                fa->setStateInitial(state);
                break;
            case 3:
                
                 std::cout << " --- Add Final State--- \nTo create or set a final state write the name of the state (the name must be an Integer)\n\tState name : ";
                while(!(std::cin >> state)){
                    std::cout << "error, the name must be an Integer\n\tState name : ";
                }
                if(!fa->hasState(state)){
                    fa->addState(state);
                }
                fa->setStateFinal(state);
                break;
            case 4:
                
                 std::cout << " --- Remove State--- \nTo remove state (and his potential transition) write the name of the state (the name must be an Integer)\n\tState name : ";
                while(!(std::cin >> state)){
                    std::cout << "error, the name must be an Integer\n\tState name : ";
                }
                if(fa->hasState(state)){
                    fa->removeState(state);
                }
                break;
            case 5:
                
                 std::cout << " --- Count State--- \n\tTo count number of state(s)" << std::endl;
                std::cout << "number of state(s) " << fa->countStates() << std::endl;
                break;
            case 0:
                back = true;
                break;
            default:
                std::cout << "\nYour choice might be not implemented yet" << std::endl;
                break;
        }
    }
}
void manipulateAutomaton(fa::Automaton *fa){
    char alpha;
    int to;
    int from;
    bool back=false;
    bool verif=false;
    int choix =-1;
    while(!back){
        std::cout << "\n --- Manipulate Automaton --- \n\tManipulate state press 1\n\tAdd one transition press 2\n\tRemove one transition press 3\n\tMake your automaton determinitic press 4\n\tMake your automaton complete press 5\n\tMake the complement of your automaton press 6\n\tBack press 0"<< std::endl;
        while(!(std::cin >> choix)){
            std::cout << "\nerror, you must enter an Integer!\n\tYour choice : ";
        }
        switch(choix){
            case 1:
                
                 manipulateState(fa);
                break;
            case 2:
                
                 std::cout << "\n --- Add Transition --- \nTo add one transition write the name of the from state, then the character of your transition and then th name of the to state \n\tfrom State name : ";
                 while(!(std::cin >> from)){
                    std::cout << "\nerror, the name must be an Integer\n\tfrom State name : ";
                }
                 do{
                    while(!(std::cin >> alpha)){
                        std::cout << "\nerror, the character must be a character\n\tcharacter : ";
                    }
                    if(isprint(alpha) || alpha == '\0'){
                        std::cout << "\nerror, the character must be printable\n\tcharacter : ";
                        verif=true;
                    }
                 }while(verif);
                 while(!(std::cin >> to)){
                    std::cout << "\nerror, the name must be an Integer\n\tto State name : ";
                }
                fa->addTransition(to,alpha,from);
                break;
            case 3:
                
                 std::cout << "\n --- Remove Transition --- \nTo remove one transition write the name of the from state, then the character of your transition and then th name of the to state \n\tfrom State name : ";
                 while(!(std::cin >> from)){
                    std::cout << "\nerror, the name must be an Integer\n\tfrom State name : ";
                }
                 do{
                    while(!(std::cin >> alpha)){
                        std::cout << "\nerror, the character must be a character\n\tcharacter : ";
                    }
                    if(isprint(alpha) || alpha == '\0'){
                        std::cout << "\nerror, the character must be printable\n\tcharacter : ";
                        verif=true;
                    }
                 }while(verif);
                 while(!(std::cin >> to)){
                    std::cout << "\nerror, the name must be an Integer\n\tto State name : ";
                }
                if(fa->hasTransition(to,alpha,from))
                    fa->removeTransition(to,alpha,from);
                break;
            case 5:
                std::cout << "\n --- Make Deterministic ---" << std::endl;
                *fa=fa::Automaton::createDeterministic(*fa);
                break;
            case 6:
                std::cout << "\n --- Make Complete --- " << std::endl;
                fa->makeComplete();
                break;
            case 7:
                std::cout << "\n --- Make Complement --- " << std::endl;
                fa->makeComplement();
                break;
            case 0:
                back = true;
                break;
            default:
                std::cout << "\nYour choice might be not implemented yet" << std::endl;
                break;
        }
    }
}

//-----------------------------------------
//------------------ Check ----------------
//-----------------------------------------
void checkAutomaton(fa::Automaton fa){
//is language empty
//is included in 
    bool back=false;
    int state;
    int choix =-1;
    while(!back){
        std::cout << "\n --- Check Automaton --- \n\tIs state initial ? press 1\n\tIs state final ? press 2\n\tIs a determinitic automaton press 3\n\tIs automaton complete press 4\n\tIs an empty language press 5\n\tIs included in (not implemented yet)\n\tBack press 0"<< std::endl;
        while(!(std::cin >> choix)){
            std::cout << "\nerror, you must enter an Integer!\n\tYour choice : ";
        }
        switch(choix){
            case 1:
                 std::cout << "\n --- Is state initial ? ---\n\t Enter the name of the state:" << std::endl;
                 
                 while(!(std::cin >> state)){
                    std::cout << "\nerror, the name must be an Integer\n\t State name : ";
                }
                std::cout << "The state "<< state << (fa.isStateInitial(state) ? " is" : " is not") << " initial" << std::endl; 
                break;
            case 2:
                std::cout << "\n --- Is state final ? ---\n\t Enter the name of the state:" << std::endl;
                
                while(!(std::cin >> state)){
                    std::cout << "\nerror, the name must be an Integer\n\t State name : ";
                }
                std::cout << "The state "<< state << (fa.isStateFinal(state) ? " is" : " is not") << " final" << std::endl; 
                break;
            case 3:
                std::cout << "\n --- Deterministic Automaton ? ---" << std::endl;
                std::cout << "The automaton " << (fa.isDeterministic() ? " is" : " is not") << " deterministic" << std::endl;
                break;
            case 4:
                std::cout << "\n --- Complete Automaton ? ---" << std::endl;
                std::cout << "The automaton " << (fa.isComplete() ? " is" : " is not") << " complete" << std::endl;
                break;
            case 5:
                 std::cout << "\n --- Empty Language ? ---" << std::endl;
                std::cout << "The Language " << (fa.isLanguageEmpty() ? " is" : " is not") << " empty" << std::endl;
                break;
            case 0:
                back = true;
                break;
            default:
                std::cout << "\nYour choice might be not implemented yet" << std::endl;
                break;
        }

    }
}

int main(){
    fa::Automaton fa;
    bool exit=false;
    int choix =-1;
    while(!exit){
        std::cout << "\n --- Automaton Project --- \n\tManipulate automaton press 1\n\tCheck your automaton press 2\n\tPrint your automaton in terminal press 3\n\tCreate .dot file press 4\n\tClear automaton (not implemented)\n\tExit press 0"<< std::endl;
        std::cin >> choix;
        switch(choix){
            case 1:
                manipulateAutomaton(&fa);
                break;
            case 2:
                checkAutomaton(fa);
                break;
            case 3:
                std::cout << "\n --- print Automaton in terminal --- " << std::endl; 
                fa.prettyPrint(std::cout);
                break;
            case 4:
                char verifDot;
                std::cout << "\n --- Create .dot File --- \n\t Caution : the File is name YourAutomaton.dot\n\tlocate in automaton/build\n\tIt erase file with the same name\n\tContinue ? y or n" << std::endl;
                while(!(std::cin >> verifDot)){
                    std::cout << "You must press 'y' for yes or 'n' for no!" << std::endl;
                }
                
                if(verifDot=='y'){
                    toDot(fa);
                }else
                    std::cout << "dot creation cancelled" << std::endl;
                break;
            case 0:
                exit = true;
                break;
            default:
                std::cout << "\nYour choice might be not implemented yet" << std::endl;
                break;
        }
    }
	
    return 0;
}
