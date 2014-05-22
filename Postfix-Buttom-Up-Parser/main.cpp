//
//  main.cpp
//  Postfix-Buttom-Up-Parser
//
//  Created by Markus Klemm on 22.05.14.
//  Copyright (c) 2014 net.markusklemm. All rights reserved.
//

#include <iostream>
#include <string>
#include <stack>
#include <cassert>
#include <cstdio>

using namespace std;

int pf_bu_parser(const string &expression)
{
    stack<int> stack;
    
    for (auto exprit = expression.cbegin(); exprit != expression.cend(); exprit++) {
        if (isnumber(*exprit)) {
            //shift
            const string c = {*exprit};
            stack.push(stol(c, nullptr, 10));
        } else if (*exprit == '+' && stack.size() >= 2) //4* reduce
        {
            const int add1 = stack.top(); stack.pop();
            const int add2 = stack.top(); stack.pop();
            stack.push(add1 + add2);
        } else if (*exprit == '-' && stack.size() >= 2)
        {
            const int sub = stack.top(); stack.pop();
            const int min = stack.top(); stack.pop();
            stack.push(sub - min);
        } else if (*exprit == '*' && stack.size() >= 2)
        {
            const int prod1 = stack.top(); stack.pop();
            const int prod2 = stack.top(); stack.pop();
            stack.push(prod1*prod2);
        } else if (*exprit == '/' && stack.size() >= 2)
        {
            const int divid = stack.top(); stack.pop();
            const int divis = stack.top(); stack.pop();
            stack.push(divid / divis);
        }
        
    }
    
    if (stack.size() != 1) {
        //error
        cerr << "Parser Error" << endl;
        exit(EXIT_FAILURE);
    }
    return stack.top();
}

int main(int argc, const char * argv[])
{
    const string input = {"123+*2+"};
    assert(pf_bu_parser(input) == 7);
    
    cout << "Enter postfix expression to calculate: ";
    
    string in;
    cin >> in;
    cout << pf_bu_parser(in) << endl;
    
    return 0;
}

