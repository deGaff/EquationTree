//
// Created by d3Gaff on 30.03.2022.
//

#include <stack>
#include <exception>
#include "EquationParser.h"
//TODO all todos "FIX" in this file are there to show dumb ideas

struct element { //TODO FIX
    union val {
        double d;
        char oper;
    };
    element(double d) : is_val(true) {
        value.d = d;
    }
    element(char oper) : is_val(false) {
        value.oper = oper;
    }
    bool is_val;
    val value;
    operator bool() {return is_val;}
};


auto ParseExpression(std::istream& str) {
    using namespace Equation;

    std::stack<char> op_stack;
    std::stack<element> rpn;
    char symbol;
    while(str && (symbol = str.peek()) != EOF && symbol != '\n') {
        if(std::isdigit(symbol)) {
            double digit; //TODO FIX
            str >> digit;
            rpn.push(digit);
            continue;
        }
        //TODO POSTFIX (!) & PREFIX (sin()) OPERATIONS GO HERE
        if(symbol == '(') {
            str >> symbol;
            op_stack.push(symbol);
        }
        if(symbol == ')' ) {
            str >> symbol;
            while(op_stack.top() != '(' && !op_stack.empty()) {
                rpn.push(op_stack.top());
                op_stack.pop();
            }
            if(op_stack.empty()) throw std::invalid_argument("amount of opening and closing brackets is unequal");
        }
        if(auto it = priorities.find(symbol); it!=priorities.end()) {
            str >> symbol;
            while(priorities.find(op_stack.top())->second >= it->second && !op_stack.empty()) {
                rpn.push(op_stack.top());
                op_stack.pop();
            }
            op_stack.push(symbol);
        }
        throw std::invalid_argument("unknown element");
    }
    while(!op_stack.empty()) {
        rpn.push(op_stack.top());
        op_stack.pop();
    }
    //TODO MAKE TREE FROM rpn
}