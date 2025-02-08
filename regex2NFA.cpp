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
    int count = 0;
    for (int i = 0; i < regex.length(); i++){
        if(isalpha(regex[i])){
            state newState;
            newState.charToMoveOn = regex[i];
            newState.name = count;
            newState.stateType = IMPORTANT;
            newState.nextStates[0] = count+1;
            newState.nextStates[1] = NULL;
            stacks.push(newState);
            count ++;
        } else if (regex[i] == '|'){
            state tmpStateOne = stacks.top();
            stacks.pop();
            state tmpStateTwo = stacks.top();
            stacks.pop();
            unionFunction(tmpStateOne, tmpStateTwo);
        } else if (regex[i] == '.'){
            state tmpStateOne = stacks.top();
            stacks.pop();
            state tmpStateTwo = stacks.top();
            stacks.pop();
            concatFuntion(tmpStateOne, tmpStateTwo);
        } else if (regex[i] == '*'){

        }
    }
}

void NFA :: unionFunction(state startState, state finalState){
    state newStartingState;
    newStartingState.charToMoveOn = '_';
    newStartingState.name = finalState.name;
    newStartingState.stateType = EPSILON;
    
    //create a function to update the names of the states and the next states
    finalState.name = finalState.nextStates[0];
    startState.name = startState.nextStates[0];

    if(finalState.nextStates[1] == NULL){
        finalState.nextStates[1] = finalState.nextStates[0] + 2;
    } else {
            finalState.nextStates[1] = finalState.nextStates[1] + 1;

    }

    if(startState.nextStates[1] == NULL){
        startState.nextStates[1] = startState.nextStates[0] + 2;
    } else {
            startState.nextStates[1] = startState.nextStates[1] + 1;

    }

    newStartingState.nextStates[0] = finalState.name;
    newStartingState.nextStates[1] = startState.name;

    stacks.push(newStartingState);
    stacks.push(finalState);
    stacks.push(startState);
    
}

void NFA :: concatFuntion(state stateOne, state stateTwo){
    state newState;
    newState.charToMoveOn = '_';
    newState.name = stateOne.name + 1;
    newState.stateType = EPSILON;
    newState.nextStates[0] = stateTwo.name;

    stateOne.nextStates[0] = newState.name;
    stacks.push(stateOne);
    stacks.push(newState);
    stacks.push(stateTwo);
}

void NFA :: kleeneStarFunction(state stateOne){

}