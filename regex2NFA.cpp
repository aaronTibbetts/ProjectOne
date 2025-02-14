#include "regex2NFA.h"
#include <stack>
using namespace std; 




void NFA :: print(){
    while(!stacks.empty()){
        state tmp = stacks.top();
        cout << tmp.name << "-> " << tmp.charToMoveOn << " " << tmp.nextStates[0];
        if(tmp.nextStates[1] != 999999){
            cout <<" "<<tmp.nextStates[1];
        }
        cout << endl;
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
            newState.nextStates[1] = 999999;
            stacks.push(newState);
            count++;
        } else if (regex[i] == '|'){
            state tmpStateTwo = stacks.top();
            stacks.pop();
            state tmpStateOne = stacks.top();
            stacks.pop();
            unionFunction(tmpStateOne, tmpStateTwo);
            count+=4;
        } else if (regex[i] == '.'){
            state tmpStateTwo = stacks.top();
            stacks.pop();
            state tmpStateOne = stacks.top();
            stacks.pop();
            concatFuntion(tmpStateOne, tmpStateTwo);
        } else if (regex[i] == '*'){
            state tmpState = stacks.top();
            stacks.pop();
            kleeneStarFunction(tmpState);
            count++;
        }
    }
}

void NFA :: unionFunction(state startState, state finalState){
    state newStartingState;
    newStartingState.charToMoveOn = '_';
    newStartingState.name = startState.name;
    newStartingState.stateType = EPSILON;

    startState.name = startState.nextStates[0];
    finalState.name = finalState.nextStates[0];

    newStartingState.nextStates[0] = startState.name;
    newStartingState.nextStates[1] = finalState.name;
    
    if(startState.nextStates[1] == 999999){
        startState.nextStates[0] = startState.nextStates[0] + 2;
    } else if(startState.nextStates[1] < startState.nextStates[0]){
         startState.nextStates[0] = startState.nextStates[0] + 1;
    } else {
        startState.nextStates[0] = startState.nextStates[1];
    }
    
     if(finalState.nextStates[1] == 999999){
        finalState.nextStates[0] = finalState.nextStates[0] + 2;
    } else if(finalState.nextStates[1] < finalState.nextStates[0]){
         finalState.nextStates[0] = finalState.nextStates[0] + 1;
    } else {
        finalState.nextStates[0] = finalState.nextStates[1];
    }

    state secondState;
    secondState.charToMoveOn = '_';
    secondState.name = startState.nextStates[0] + 2;
    secondState.stateType = EPSILON;
    secondState.nextStates[0] = finalState.nextStates[0] + 2;
    secondState.nextStates[1] = 999999;

    startState.nextStates[1] = secondState.name;
    finalState.nextStates[1] = secondState.name;

    stacks.push(newStartingState);
    stacks.push(startState);
    stacks.push(finalState);
    stacks.push(secondState);
   
}

void NFA :: concatFuntion(state stateOne, state stateTwo){
    //add new initial state, add e tran from new start to state one add each e tran from state one to state two
    
    state newState;
    newState.charToMoveOn = '_';
    newState.name = stateTwo.name;
    newState.stateType = EPSILON;
    newState.nextStates[0] = stateTwo.nextStates[0];
    newState.nextStates[1] = 999999;

    stateOne.nextStates[0] = stateTwo.name;


    stateTwo.name = newState.nextStates[0];

    if(stateTwo.nextStates[1] == 999999){
        stateTwo.nextStates[0]  = stateTwo.nextStates[0] + 1;
    } else {
        stateTwo.nextStates[0] = stateTwo.nextStates[1];
    }
    
    stacks.push(stateOne);
    stacks.push(newState); 
    stacks.push(stateTwo);
}

void NFA :: kleeneStarFunction(state stateOne){
    state newState;
    newState.charToMoveOn = '_';
    newState.name = stateOne.name;
    newState.stateType = EPSILON;

    stateOne.name = stateOne.nextStates[0];
    newState.nextStates[0] = stateOne.name;
    newState.nextStates[1] = 999999;


    if(stateOne.nextStates[1] == 999999){
        stateOne.nextStates[0] = stateOne.nextStates[0] + 1;
    } else {
        stateOne.nextStates[0] = stateOne.nextStates[1];
    }

    stateOne.nextStates[1] = newState.name;

    stacks.push(newState);
    stacks.push(stateOne);
    

}