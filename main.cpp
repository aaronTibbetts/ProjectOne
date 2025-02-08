#include <iostream>
#include <string>
#include "lexer.h"
#include "shunting.h"
#include "regex2NFA.h"

using namespace std; 

int main (){
    NFA graph;
    string RE = "((a)*).(a)";
    string postFix = infixToPostfix(RE);
    cout << infixToPostfix(RE);

    graph.reToNfa(postFix);
    graph.print();
}