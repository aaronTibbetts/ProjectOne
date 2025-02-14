#include "token.h"

string tkns [] = {"ID", "CHARACTER", "OPERATION", "EOS", "INVALID"};


Token :: Token(){
    tokenType  = EOS;
    expression = "";
}


Token :: Token(Tokens t, string exp){
    tokenType = t;
    expression = exp; 
}