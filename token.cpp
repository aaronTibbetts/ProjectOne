#include "token.h"

string tkns [] = {"ID", "CHARACTER", "OPERATION", "EOS", "INVALID"};

//token constructor for empty
Token :: Token(){
    tokenType  = EOS;
    expression = "";
}

//token constructor for non empty tokens
Token :: Token(Tokens t, string exp){
    tokenType = t;
    expression = exp; 
}