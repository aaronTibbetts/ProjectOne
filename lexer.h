#ifndef LEXER_H
#define LEXER_H
#include "token.h"
#include <string>
#include <iostream>

using namespace std; 




class Lexer {
    public:
        Lexer(string input);
        Token getToken(); 

    private:
        string userInput;
        int position;
        
};
#endif