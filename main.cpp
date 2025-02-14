#include <iostream>
#include <string>
#include <vector>
#include "lexer.h"
//#include "shunting.h"
//#include "regex2NFA.h"

using namespace std; 

int main (){
    string input;
    getline(cin, input);
    Lexer lexer(input);

    Token token;

    vector <Token> tokenNames; 
    vector <Token> regexs;

    while((token = lexer.getToken()).tokenType != EOS){
        if(token.tokenType == ID){
            tokenNames.push_back(token);
        } else if(token.tokenType == REGEX){
            regexs.push_back(token);
        }

    }

    return 0;
}