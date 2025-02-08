#include "regex2NFA.h"
#include <stack>
using namespace std; 




void NFA :: print(){
    while(!stacks.empty()){
        state tmp = stacks.top();
        cout << tmp.name << "-> " << tmp.charToMoveOn << " " << tmp.nextStates[0] << " " << tmp.nextStates[1]<< endl;
        stacks.pop();
    }
}

void NFA :: reToNfa(string regex){
    stack<state> stateStacks;
    for (int i = 0; i < regex.length(); i++){
        if(isalpha(regex[i])){
            state newState;
            newState.charToMoveOn = regex[i];
            newState.name = i;
            newState.stateType = IMPORTANT;
            newState.nextStates[0] = i+1;
            newState.nextStates[1] = NULL;
            stacks.push(newState);
        } else if (regex[i] == '|'){
            state tmpStateOne = stacks.top();
            stacks.pop();
            state tmpStateTwo = stacks.top();
            stacks.pop();
            unionFunction(tmpStateOne, tmpStateTwo);
        }
    }
}

void NFA :: unionFunction(state startState, state finalState){
    state newStartingState;
    newStartingState.charToMoveOn = '_';
    newStartingState.name = 0;
    newStartingState.stateType = EPSILON;
    
    //create a function to update the names of the states and the next states
    finalState.name = 1;
    startState.name = 3;

    finalState.nextStates[0] = 2;
    startState.nextStates[0] = 4;

    newStartingState.nextStates[0] = finalState.name;
    newStartingState.nextStates[1] = startState.name;

    stacks.push(newStartingState);
    stacks.push(finalState);
    stacks.push(startState);
}