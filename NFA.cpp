#include "NFA.h"
#include <iostream>
#include <set>


NFA :: NFA(set <char> a, int initial, set <int> final){
    alphabet = a;
    initialState = initial;
    finalStates = final;
}

set<char> NFA :: getAlphabet(){
    return alphabet;
}

set<int> NFA :: getFinalStates(){
    return finalStates;
}

int NFA :: getInitialState(){
    return initialState;
}


void NFA :: setInitialState(int state){
    initialState = state;
}

void NFA :: incrementFinalState(int amountToUpdate){
    set<int>::iterator itr;
    for(itr = finalStates.begin(); itr != finalStates.end(); itr++){
        int element = *itr + amountToUpdate;
        finalStates.erase(itr);
        finalStates.insert(element);
    }

}

void NFA :: setFinalState(int newState){
    set<int>::iterator itr = finalStates.begin();
    finalStates.erase(itr);
    finalStates.insert(newState);    
}

map <int, map<char, set <int>> > NFA :: getGraph(){
    return graph;
}

void NFA :: addTransition(int start, set<int> statesToGoTo, char symbol){
    graph[start][symbol] = statesToGoTo;
} 

void NFA ::setGraph(map <int, map<char, set <int>> > newGraph){
    graph = newGraph;
}

void NFA :: updateKeysAndValues(int updateAmount){
    map <int, map<char, set <int>> > newGraph;
    for(const auto& nfaRow : graph){
        map<char, set<int>> transitionsAndStates;
        for(const auto& transitions: nfaRow.second){
            set<int> statesToGoTo;
            for(int i:transitions.second){
                statesToGoTo.insert(i+updateAmount);
            }
            transitionsAndStates[transitions.first] = statesToGoTo;
        }
        newGraph[nfaRow.first+updateAmount] = transitionsAndStates;
    }
    graph = newGraph;
}

char NFA :: getSymbol(int key){
    const auto& i = graph.at(key); 
    const auto& foo = *i.begin();
    char symbol = foo.first;
    return symbol;
}

void NFA :: print(){
    std ::cout << "NFA Transitions: \n";
    for(const auto& nfaRow: graph){
        std ::cout << nfaRow.first << "\t";

        for(const auto& transition: nfaRow.second){
            std ::cout << transition.first<< ":{";
            for(int state: transition.second){
                std ::cout << state<< " ";
            }
            std ::cout << "}";
        }
        std ::cout << std ::endl;
    }
}

set<int> NFA :: computeEClosure (set<int> states){
    std::stack <int> dfsStack;
    std::set <int> eClousreSet = states;

    for(int state: states){
        dfsStack.push(state);
    }

    while(!dfsStack.empty()){
        int state = dfsStack.top();
        dfsStack.pop();

        if(graph[state].find('_') != graph[state].end()){
            for(int next_state: graph[state]['_']){
                if(eClousreSet.find(next_state) ==eClousreSet.end()){
                    eClousreSet.insert(next_state);
                    dfsStack.push(next_state);
                }
            }
        }
    }
    return eClousreSet; 

}
