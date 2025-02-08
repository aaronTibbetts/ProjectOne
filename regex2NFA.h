#ifndef REGEX2NFA_H
#define REGEX2NFA_H
#include <string>
#include <stack>
#include <list>
#include <iostream>

using namespace std;

enum typesOfStates{
    IMPORTANT,
    EPSILON 
};

struct state{
    int name;
    typesOfStates stateType;
    char charToMoveOn;
    int nextStates[2];
};

class NFA{
    public:
    stack <state> stacks;
    void print();
    void reToNfa(string re);
    void unionFunction(state startState, state finalState);
    void concatFuntion(state startState, state stateTwo);
    void kleeneStarFunction(state startState);
    void updateNames(state stateOne, state stateTwo); 
};





#endif 
