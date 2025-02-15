#include "NFA.h"
#include <iostream>
#include <set>

//NFA constructor 
NFA :: NFA(set <char> a, int initial, set <int> final){
    alphabet = a;
    initialState = initial;
    finalStates = final;
}
//returns alphabet
set<char> NFA :: getAlphabet(){
    return alphabet;
}
//returns final states
set<int> NFA :: getFinalStates(){
    return finalStates;
}
//returns initial states
int NFA :: getInitialState(){
    return initialState;
}

//sets initial state to a new initial state
void NFA :: setInitialState(int state){
    initialState = state;
}
//updates all the final states by a specified amount
void NFA :: incrementFinalState(int amountToUpdate){
    set<int>::iterator itr;
    for(itr = finalStates.begin(); itr != finalStates.end(); itr++){
        int element = *itr + amountToUpdate;
        finalStates.erase(itr);
        finalStates.insert(element);
    }

}



//sets a new state to a specifed state 
void NFA :: setFinalState(int newState){
    set<int>::iterator itr = finalStates.begin();
    finalStates.erase(itr);
    finalStates.insert(newState);    
}
//sets finalstates to a set of new final states
void NFA :: finalSet(set<int>finalStateSet){
    finalStates = finalStateSet;
}
//gets the graph
map <int, map<char, set <int>> > NFA :: getGraph(){
    return graph;
}
//adds transition to graph
void NFA :: addTransition(int start, set<int> statesToGoTo, char symbol){
    graph[start][symbol] = statesToGoTo;
} 
//sets graph to new graph
void NFA ::setGraph(map <int, map<char, set <int>> > newGraph){
    graph = newGraph;
}
//sets alphabet to new alphabet
void NFA :: setAlphabet(set<char> newAlphabet){
    alphabet = newAlphabet;
}
//updates all keys and values in the graph
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
//returns the symbol a transition uses to go to a next state
char NFA :: getSymbol(int key){
    const auto& i = graph.at(key); 
    const auto& foo = *i.begin();
    char symbol = foo.first;
    return symbol;
}
//returns the set of all destination states by a specifed state
set<int> NFA :: getDestinationState(int key){
    const auto& symbolKey = graph.at(key);
    const auto& s = *symbolKey.begin();
    const auto& d = s.second;
    return d;
}
//prints out the nfa
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
//computes e clousre of a specifed state
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

//takes a RE and turns it into an nfa
NFA NFA ::reToNfa(std::string regex){
    std:: stack<NFA> nfaStack;
    std:: stack<char> seenSymbols;
    std :: stack<char> seenOperands; 
    std:: set<int> allFinalStates;
    int count = 0;
    for (int i = 0; i < regex.length(); i++){
        
        char regexChar = regex[i];

        if(isalpha(regex[i])){
            std:: set<char> alphabet;
            alphabet.insert(regexChar);
            set<int> finalStates;
            finalStates.insert(count+1);
            NFA tmp(alphabet, count, finalStates);       
            tmp.addTransition(count,finalStates, regexChar);
            nfaStack.push(tmp);
            seenSymbols.push(regexChar);
            allFinalStates.insert(count+1);
            count+=2; 
        } else if (regex[i] == '|'){
            NFA nfaTwo = nfaStack.top();
            nfaStack.pop();
            NFA nfaOne = nfaStack.top();
            nfaStack.pop();
            NFA newNFA = unionFunction(nfaOne,nfaTwo,seenSymbols, count);
            nfaStack.push(newNFA);
            seenOperands.push(regexChar);
            set<int>::iterator itr;
            for(itr = allFinalStates.begin(); itr != allFinalStates.end(); itr++){
                int element = *itr + 1;
                allFinalStates.erase(itr);
                allFinalStates.insert(element);
            }
            count+=2; 
        } else if (regex[i] == '.'){
            NFA nfaTwo = nfaStack.top();
            nfaStack.pop();
            NFA nfaOne = nfaStack.top();
            nfaStack.pop();
            NFA newNFA = concatFuntion(nfaOne, nfaTwo, seenOperands, count);
            nfaStack.push(newNFA);
            seenOperands.push(regexChar);
            allFinalStates.clear();
            allFinalStates.insert(count-2);
            count --;
        } else if (regex[i] == '*'){
            NFA nfaOne = nfaStack.top();
            nfaStack.pop();
            NFA newNFA = kleeneStarFunction(nfaOne, seenSymbols,count);
            nfaStack.push(newNFA);
            seenOperands.push(regexChar);

            count += 2;
        }
    }
    NFA topOfNFA = nfaStack.top();
    topOfNFA.finalSet(allFinalStates);
    return topOfNFA;
}

NFA NFA :: unionFunction(NFA &nfaOne, NFA nfaTwo, std::stack<char> seenSymbols, int &count){
    set<char> alphabetOne = nfaOne.getAlphabet();
    set<char> alpahbetTwo = nfaTwo.getAlphabet();
    set<char> newAlphabet;
    newAlphabet.insert(alphabetOne.begin(), alphabetOne.end());
    newAlphabet.insert(alpahbetTwo.begin(), alpahbetTwo.end()); 

    set<int> newFinalState = {count +1};

    NFA unionNFA (newAlphabet,nfaOne.getInitialState(),newFinalState);

    nfaOne.setInitialState(nfaOne.getInitialState() +1);
    nfaTwo.setInitialState(nfaTwo.getInitialState() + 1);

    nfaOne.incrementFinalState(1);
    nfaTwo.incrementFinalState(1);

    char nfaTwoSymbol = seenSymbols.top();
    seenSymbols.pop();
    char nfaOneSymbol = seenSymbols.top();
    seenSymbols.pop(); 

    unionNFA.addTransition(unionNFA.getInitialState(),{nfaOne.getInitialState(),nfaTwo.getInitialState()}, '_'); 
    unionNFA.addTransition(nfaOne.getInitialState(), nfaOne.getFinalStates(), nfaOneSymbol); 
    unionNFA.addTransition(nfaTwo.getInitialState(), nfaTwo.getFinalStates(), nfaTwoSymbol); 
    unionNFA.addTransition(count-2, newFinalState, '_'); 
    unionNFA.addTransition(count, newFinalState, '_'); 
    
    return unionNFA;
    
}

NFA NFA ::concatFuntion(NFA &nfaOne, NFA nfaTwo, std::stack<char> operands,int &count){
    set<char> nfaOneAlphabet = nfaOne.getAlphabet();
    set<char> nfaTwoAlphabet = nfaTwo.getAlphabet();
    nfaOneAlphabet.insert(nfaTwoAlphabet.begin(), nfaTwoAlphabet.end());
    nfaOne.setAlphabet(nfaOneAlphabet);

    char symbol = nfaTwo.getSymbol(nfaTwo.getInitialState());

    nfaTwo.updateKeysAndValues(-1);
    set<int> nfaTwoFinalStates = nfaTwo.getFinalStates();
    set<int> nfaOneFinalStates = nfaTwo.getFinalStates();

    map<int,  map <char,set<int>>> nfaTwoGraph = nfaTwo.getGraph();
    map<int,  map <char,set<int>>> nfaOneGraph = nfaOne.getGraph();

    nfaOneGraph.insert(nfaTwoGraph.begin(), nfaTwoGraph.end());
    nfaOne.setGraph(nfaOneGraph);
    
    nfaOneFinalStates.insert(nfaTwoFinalStates.begin(), nfaTwoFinalStates.end());

    nfaOne.setFinalState(*nfaTwo.getFinalStates().begin()-1);

    return nfaOne;
   

}

NFA NFA ::kleeneStarFunction(NFA &nfaOne, std:: stack<char> symbols,int &count){
    nfaOne.incrementFinalState(2);
    set<int> nfaOneFinalStates = nfaOne.getFinalStates();
    char symbol = symbols.top();
    symbols.pop();
    nfaOneFinalStates.insert(nfaOne.getInitialState()+1);

    nfaOne.updateKeysAndValues(1);
    nfaOne.addTransition(nfaOne.getInitialState(),nfaOneFinalStates, '_'); 
    nfaOne.addTransition(count,{count+1, nfaOne.getInitialState()+1}, '_'); 

    
    return nfaOne;
}

