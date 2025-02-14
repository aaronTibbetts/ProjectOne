#include "shunting.h"

using namespace std; 

int precedence(char op){
    if (op == '*'){
        return 3;
    }

    if(op == '.'){
        return 2;
    }

    if (op == '|'){
        return 1;
    }

    return 0; 
}

bool isOperand(char c){
    return isalpha(c); 
}

string infixToPostfix(string infix){
    string postfix; 
    stack <char> stack;

    for (size_t i = 0; i <infix.size(); i++ ){
        char c = infix[i];

        if(isOperand(c)){
            postfix += c;
        } else if(c == '('){
            stack.push(c);
        } else if( c == ')'){
            while(!stack.empty() && stack.top() != '('){
                postfix += stack.top();
                stack.pop();
            }
            stack.pop();
        } else if (c == '|'){
            while(!stack.empty() && stack.top() != '(' && precedence(stack.top()) >= precedence(c)){
                postfix += stack.top();
                stack.pop();
            }
            stack.push(c);
        } else if( c == '*'){
            stack.push(c);
        } else if(c == '.'){
            while(!stack.empty() && stack.top() != '(' && precedence(stack.top()) >= precedence(c)){
                postfix += stack.top();
                stack.pop();
            }
            stack.push(c);
        }

    }
    while(!stack.empty()){
        postfix += stack.top();
        stack.pop();
    }

    return postfix;
}