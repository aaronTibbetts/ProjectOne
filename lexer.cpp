#include "lexer.h"
#include <iostream> 
#include <cstring>


using namespace std; 


//lexer constructor
Lexer::Lexer(string input) {
    userInput = input; 
    position = 0;

}
//goes through first input of tokens and generates each token name and expression
Token Lexer :: getToken(){
    while(position < userInput.size()){
        char charToLook = userInput[position];

        if(userInput[position]  == '#'){
            return Token(EOS, "");
        }

        if(charToLook == 't'){
            string tokenName;
            while((position < userInput.size()) && userInput[position] != ' '){
                tokenName += userInput[position++]; 
            }
            return Token(ID, tokenName);

        } else if(isalpha(charToLook) || charToLook == '(' ){
            string regex;
            while((position < userInput.size()) && userInput[position] != ' '){
                regex += userInput[position++];
            }
            return Token(REGEX, regex);
        } else if(charToLook == ' ' || charToLook == ','){
            //do nothing 
        } else {
            return Token(INVALID, "");
        }
        position++;

    }
}
