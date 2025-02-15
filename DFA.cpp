#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include "DFA.h"

//dfa constructor 
DFA::DFA(std::set<char> A,std::set<int> I, std::set<int> F){ 
    alphabet = A;
    initialStates = I;
    finalStates = F;
    Reset();
}

//resets dfa to inital state 
void DFA::Reset(){
    status = START;
    current_state = *initialStates.begin();
    accepted=false;
    lexeme.clear();
}
//addds transitions to the dfa 
void DFA::AddTransition( int src, int dst, char sym){
    Dtran[src][sym] = dst;
}
//gets the status of the dfa 
DFAstatus DFA :: GetStatus(){
    return status; 
}
//returns the accepted lexeme
std::string DFA :: GetAcceptedLexeme(){
    return accepted_lexeme;
}
//returns if the dfa has accepted 
bool DFA :: GetAccepted(){
    return accepted;
}

//move through the dfa 
void DFA::Move(char c){
    if (Dtran[current_state].find(c) != Dtran[current_state].end()){
        current_state = Dtran[current_state][c];
        lexeme += c;
        if (finalStates.count(current_state) > 0){
            status = ACCEPT;
            accepted = true;
            accepted_lexeme = lexeme;
        } else{
            status = POTENTIAL;
        } 
    }else{ 
        status = FAIL;
    }
}
//print out the dfa 
void DFA::Print(){
    std::cout << "DFA Transitions:\n";
    for (const auto& dfa_row : Dtran){
        std::cout << dfa_row.first << ":\t";
        for (const auto& transition : dfa_row.second){
            std::cout << transition.first << ": " << transition.second << " ";
        }
    std::cout << std::endl;
    }
}
//turns an nfa into a dfa

DFA DFA :: nfaToDfa(NFA nfaToConvert){
    set<int> eclosure = nfaToConvert.computeEClosure({0});
    set<char> alphabet = nfaToConvert.getAlphabet();

    map<int, map<char , set<int>>> nfaGraph = nfaToConvert.getGraph(); 

    DFA newDfa (alphabet, eclosure, nfaToConvert.getFinalStates());
    set<int> seenFinalStates;
    
    int count = 0;

       for(int i = 0; i < nfaGraph.size(); i++){
        eclosure = nfaToConvert.computeEClosure({i});
        for(const auto& state: eclosure){
            for(const auto& character: alphabet){   
                if((nfaGraph.find(state) != nfaGraph.end())){
                    map<char, set<int>> foundMapAtState = nfaGraph.at(state);
                        if(foundMapAtState.find(character) != foundMapAtState.end()){
                            int destination = *foundMapAtState.at(character).begin();
                            if(containsFinalState(seenFinalStates, destination) == false){
                                newDfa.AddTransition(count, destination ,character);
                                seenFinalStates.insert(destination);
                            } else if(seenFinalStates.size() == nfaToConvert.getFinalStates().size()){
                                    break;
                            }
                        }
                }   
            }
        }
        count++;
    }


   

    return newDfa;
}
//checks if the set of final states to see if the state we are about to add exists or not 
bool DFA :: containsFinalState(set<int> finalState, int destinationTocheck){
    for(int element: finalStates){
        if(element == destinationTocheck){
            return true;
        }
    }
    return false; 
}