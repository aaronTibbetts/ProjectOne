#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <iostream>

using namespace std; 

enum Tokens{
    ID,
    REGEX,
    EOS,
    INVALID
};

extern string tkns [];

class Token{
    public: 
        Token(Tokens t, string ex);
        Token();
        Tokens tokenType;
        string expression; 
};

#endif