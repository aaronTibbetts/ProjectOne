#ifndef SHUNING_h
#define SHUNTING_H
#include <string>
#include <stack>

using namespace std; 

int precedence(char op);
bool isOperand (char c);
string infixToPostfix(string infix);



#endif 