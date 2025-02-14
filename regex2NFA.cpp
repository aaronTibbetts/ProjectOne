#include "regex2NFA.h"
#include <stack>

int count = 0;


NFA reToNfa(string regex){
    std:: stack<NFA> nfaStack;
    std:: stack<char> seenSymbols;
    std :: stack<char> seenOperands; 
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
            count+=2; 

        } else if (regex[i] == '|'){
            NFA nfaTwo = nfaStack.top();
            nfaStack.pop();
            NFA nfaOne = nfaStack.top();
            nfaStack.pop();
            NFA newNFA = unionFunction(nfaOne,nfaTwo,seenSymbols);
            nfaStack.push(newNFA);
            seenOperands.push(regexChar);
            count+=2; 
        } else if (regex[i] == '.'){
            NFA nfaTwo = nfaStack.top();
            nfaStack.pop();
            NFA nfaOne = nfaStack.top();
            nfaStack.pop();
            NFA newNFA = concatFuntion(nfaOne, nfaTwo, seenOperands);
            nfaStack.push(newNFA);
            seenOperands.push(regexChar);
            count --;
        } else if (regex[i] == '*'){
            NFA nfaOne = nfaStack.top();
            nfaStack.pop();
            NFA newNFA = kleeneStarFunction(nfaOne, seenSymbols);
            nfaStack.push(newNFA);
            seenOperands.push(regexChar);
            count += 2;
        }
    }
    return nfaStack.top();
}

NFA unionFunction(NFA &nfaOne, NFA nfaTwo, std::stack<char> seenSymbols){
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

    unionNFA.addTransition(unionNFA.getInitialState(),{nfaOne.getInitialState(),nfaTwo.getInitialState()}, '_'); //set start state's transitions by _
    unionNFA.addTransition(nfaOne.getInitialState(), nfaOne.getFinalStates(), nfaOneSymbol); // 1->2 a
    unionNFA.addTransition(nfaTwo.getInitialState(), nfaTwo.getFinalStates(), nfaTwoSymbol); //3->4 b
    unionNFA.addTransition(count-2, newFinalState, '_'); //2->5 _
    unionNFA.addTransition(count, newFinalState, '_'); //4->5 _
    
    return unionNFA;
    
}

NFA concatFuntion(NFA &nfaOne, NFA nfaTwo, std::stack<char> operands){
    set<char> nfaOneAlphabet = nfaOne.getAlphabet();
    set<char> nfaTwoAlphabet = nfaTwo.getAlphabet();
    nfaOneAlphabet.insert(nfaTwoAlphabet.begin(), nfaTwoAlphabet.end());

    char symbol = nfaTwo.getSymbol(nfaTwo.getInitialState());
    //char secondSymbol = operands.top();


   
    //nfaOne.addTransition(*nfaOne.getFinalStates().begin(), {nfaTwo.getInitialState()},symbol );

    nfaTwo.updateKeysAndValues(-1);

    map<int,  map <char,set<int>>> nfaTwoGraph = nfaTwo.getGraph();
    map<int,  map <char,set<int>>> nfaOneGraph = nfaOne.getGraph();

    nfaOneGraph.insert(nfaTwoGraph.begin(), nfaTwoGraph.end());
    nfaOne.setGraph(nfaOneGraph);
    
    nfaOne.setFinalState(*nfaTwo.getFinalStates().begin()-1);

    return nfaOne;
   

}

NFA kleeneStarFunction(NFA &nfaOne, stack<char> symbols){
    nfaOne.incrementFinalState(2);
    set<int> nfaOneFinalStates = nfaOne.getFinalStates();
    char symbol = symbols.top();
    symbols.pop();
    nfaOneFinalStates.insert(nfaOne.getInitialState()+1);

    nfaOne.updateKeysAndValues(1);
    nfaOne.addTransition(nfaOne.getInitialState(),nfaOneFinalStates, '_'); // 0->1 _
    nfaOne.addTransition(count,{count+1, nfaOne.getInitialState()+1}, '_'); //6->7 and 1 

    
    return nfaOne;
}
