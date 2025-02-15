#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include "lexer.h"
#include "shunting.h"
#include "DFA.h"

int main (){
    string tokens;
    string input;
    getline(cin, tokens);
    getline(cin,input);
    

    Lexer lexer(tokens);

    Token token;

    vector <Token> tokenNames; 
    vector <string> regexs;
    map <string, DFA> dfaList;
    vector<string> errorTokens;
    stack <DFA> acceptedDFA;
    stack <string> acceptedTokens;

    NFA test({}, 0, {});
    DFA dfaTest({} ,{},{});
    int position = 0;
    string builtString;


    //builds the tokens out and seperates the names from their expressions
    while((token = lexer.getToken()).tokenType != EOS){
        if(token.tokenType == ID){
            tokenNames.push_back(token);
        } else if(token.tokenType == REGEX){
            regexs.push_back(token.expression);
        }
    }
    //builds the nfa and dfa out 
    try {
        for(int i = 0; i < regexs.size(); i++){
            string postfix = infixToPostfix(regexs[i]);
            if(postfix.back() == '*'){ //if it generates eplsion grab each token and store in a vector 
                errorTokens.push_back(tokenNames[i].expression);
            }
            NFA newNFA = test.reToNfa(postfix);
            

            DFA newDFA = dfaTest.nfaToDfa(newNFA);
            string tokenName = tokenNames[i].expression;
            dfaList.insert(std::pair<string, DFA>(tokenName, newDFA));
        }
        if(errorTokens.size() > 0){ // if tokens generate eplsion throw an error 
            throw(errorTokens);
        }
    }
    catch(vector<string> wrongTokens){
        cout << "EPSILON IS NOT A TOKEN ";
        for(const auto& i : wrongTokens){
            cout << i <<" ";
        }  
        return 0;
    } 
    
    //put all dfa keys in queue 
    set <string> qTokenNames;
    for(const auto& k: dfaList){
        qTokenNames.insert(k.first);
    }
  
    for(int i = 1; i<input.length()-1; i++){ //start at first char
        for(const auto& k: dfaList){ //run each dfa
            if (qTokenNames.count(k.first) == 1) {
                if (input[i] == ' ' && dfaList[k.first].GetStatus() == ACCEPT) {
                    // found a match
                    cout << *qTokenNames.begin() << dfaList[*qTokenNames.begin()].GetAcceptedLexeme() << endl;
                    for(const auto& l : dfaList){
                        dfaList[l.first].Reset();
                        qTokenNames.insert(l.first);
                    }
                    break;
                }
                dfaList[k.first].Move(input[i]);

                // check if dfa failed
                // if failed pop it
                // 
                if(dfaList[k.first].GetStatus() == FAIL){
                    if (qTokenNames.size() > 1) {
                        qTokenNames.erase(k.first);
                    } else {
                        // found a match
                        if(dfaList[k.first].GetAcceptedLexeme() != ""){
                            cout << k.first << dfaList[k.first].GetAcceptedLexeme() << endl;
                            for(const auto& l : dfaList){
                                dfaList[l.first].Reset();
                                qTokenNames.insert(l.first);
                            }
                            // print and do the reset thing
                            break;
                        }
                       
                    }
                } else if (dfaList[k.first].GetStatus() == ACCEPT && i == input.length() - 2) {
                    // found a match
                    cout << *qTokenNames.begin() << dfaList[*qTokenNames.begin()].GetAcceptedLexeme() << endl;
                    for(const auto& l : dfaList){
                        dfaList[l.first].Reset();
                        qTokenNames.insert(l.first);
                    }
                    break;
                }
            }
        }
       
    }
    return 0;
}
