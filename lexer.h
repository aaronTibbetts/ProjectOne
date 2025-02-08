#ifndef LEXER_H
#define LEXER_H
#include <string>
#include <iostream>

using namespace std; 

class Lexer {
    public:
        Lexer(string input, char tokenTypes[]);
        string getToken(); 

    private:
        string userInput;
        char tokens [3];
        int position;
        
};
//constructor for lexer 
//getToken() function 
//input
#endif