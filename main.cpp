#include <iostream>
#include <string>
#include <vector>
#include "lexer.h"
#include "shunting.h"
#include "DFA.h"
#include "regex2NFA.h"

int main (){
    string input;
    input = "t1 (a|b)*.(c|d), #"; 
    //, t2 a*.a , t3 (a|b)*.c*.c #";
    //getline(cin, input);
    Lexer lexer(input);

    Token token;

    vector <Token> tokenNames; 
    vector <string> regexs;

    while((token = lexer.getToken()).tokenType != EOS){
        if(token.tokenType == ID){
            tokenNames.push_back(token);
        } else if(token.tokenType == REGEX){
            regexs.push_back(token.expression);
        }
    }

    for(int i = 0; i < regexs.size(); i++){
        string postfix = infixToPostfix(regexs[i]);
        reToNfa(postfix).print();
    }
    

    


   /* std::set <char> testAlp = { 'a', 'b'};
    std::set <int> testInitialState = {1,3};
    std::set <int> testFinalStates = {5};
    
    NFA testNFA(testAlp, 0, testFinalStates);
    testNFA.addTransition(0,testInitialState, '_');
    testNFA.addTransition(1,{2},'a');
    testNFA.addTransition(3,{4},'b');
    testNFA.addTransition(2,testFinalStates,'_');
    testNFA.addTransition(4,testFinalStates,'_');
    testNFA.print();
    set<int> ecset =testNFA.computeEClosure({0});

    for(const auto& element: ecset ){
        cout << element << " ";
        cout<< endl;
    }
    */
    /*
    DFA testDfa (testAlp, testInitialState,testFinalStates);
    testDfa.AddTransition(0,1,'a');
    testDfa.AddTransition(1,2,'b');
    //testDfa.Print();
    
    testDfa.Move('a');
    cout << testDfa.GetStatus();
    testDfa.Move('b');
    cout<< testDfa.GetStatus();
   */


    return 0;
}