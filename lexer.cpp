#include "lexer.h"
#include <iostream> 
#include <cstring>


using namespace std; 

int position = 0;

Lexer::Lexer(string input, char tokenTypes[]) {
    userInput = input; 
    for(int i = 0; i < 3; i++ ){
        tokens[i] = tokenTypes[i];
    }

}

string Lexer :: getToken(){
    while(position < userInput.length()){
        if(position == userInput.length()){
            return " ";
        }

        if(tokens[0] == userInput[position]){
            cout<<"token 1";
        } else if(tokens[1] == userInput[position]){
            cout<<"token 2";
        } else if(tokens[2] == userInput[position]){
            cout<<"token 3";
        } else {
            cout<< "Error";
        }
        position++;

    }
        return "all done ";

}