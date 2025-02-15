#ifndef DFA_H
#define DFA_H
#include <set>
#include <map>
#include <string>
#include "NFA.h"


enum DFAstatus {
    START, 
    FAIL, 
    POTENTIAL, 
    ACCEPT
};

class DFA{
public:
    DFA() {}
    DFA(std::set<char> A, std::set<int> I, std::set<int> F);
    void Reset();
    void AddTransition( int src, int dst, char sym);
    void Move( char c);
    DFAstatus GetStatus();
    std::string GetAcceptedLexeme();
    bool GetAccepted();
    void Print();
    DFA nfaToDfa (NFA nfaToConvert);
    bool containsFinalState(set<int> f, int finalStates);
private:
    std::map< int, std::map<char, int> > Dtran;
    DFAstatus status;
    int current_state;
    bool accepted;
    std::string lexeme;
    std::string accepted_lexeme;
    std::set<char> alphabet; // set of input symbols in the alphabet
    char epsilon = '_'; // epsilon is represented by '_'
    std::set<int> initialStates; // initial state of the DFA
    std:: set<int> finalStates; // final states of the DFA
};
#endif
