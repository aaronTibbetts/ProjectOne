#ifndef REGEX2NFA_H
#define REGEX2NFA_H
#include <string>
#include <stack>
#include <list>
#include <iostream>
#include "NFA.h"

using std:: string;
using std:: stack;
    
    void print();
    NFA reToNfa(string re);
    NFA unionFunction(NFA &nfaOne, NFA nfaTwo, stack<char>symbols);
    NFA concatFuntion(NFA &nfaOne, NFA nfaTwo, stack<char> symbols);
    NFA kleeneStarFunction(NFA &nfaOne, stack<char> symbols);




#endif 
