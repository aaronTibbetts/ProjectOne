#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include "DFA.h"

DFA::DFA(std::set<char> A,std::set<int> I, std::set<int> F){ 
    alphabet = A;
    initialStates = I;
    finalStates = F;
    Reset();
}


void DFA::Reset(){
    status = START;
    current_state = *initialStates.begin();
    accepted=false;
    lexeme.clear();
}

void DFA::AddTransition( int src, int dst, char sym){
    Dtran[src][sym] = dst;
}

DFAstatus DFA :: GetStatus(){
    return status; 
}

std::string DFA :: GetAcceptedLexeme(){
    return accepted_lexeme;
}

bool DFA :: GetAccepted(){
    return accepted;
}

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
//---------------------------------------------------------------------------------
// print the DFA
//---------------------------------------------------------------------------------
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
