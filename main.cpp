#include <iostream>
#include <string>
#include "lexer.h"
#include "shunting.h"
#include "regex2NFA.h"

using namespace std; 

int main (){
    NFA graph;
    string RE = "ab|";
    graph.reToNfa(RE);
    graph.print();
}