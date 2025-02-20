#pragma once
#include <gtest.h>
#include <iostream>
#include "translator.h"

using namespace std;

bool StrIsNumber(const std::string& str) {
    if (str.empty()) return false;

    for (size_t i = 0; i < str.length(); ++i) {
        if ((!isdigit(str[i])) && (str[i] != '.')) {
            return false;
        }
    }
    return true;
}

int main(int argc, char** argv) {
    int mode = -1;

    cout << "Arithmetic translator \n" << "Type 0 to start tests or 1 to use the translator" << endl;
    while ((mode != 0) && (mode != 1)) {
        cin >> mode;
        if ((mode != 0) && (mode != 1)) cout << "There is no such mode" << endl;
    }

    if (mode == 0){ //Launch tests
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
    else  //Run the translator
    {
        cout << "Arithmetic translator supports variables and operations +,-,*,/,unary minus\n" << "Input expression without spaces\n" << "Input variable value after inputing the expression\n" << endl;
    //////////////////////INPUT EXPRESSION//////////////////////
        string input;
        cout << "Enter expression: \n";
        cin >> input;

        Arithmetic_Expression expr(input);
    ////////////////////////////////////////////////////////////

    //////////////////////RETURNING INFIX FORM//////////////////
        cout << expr.GetInfix() << endl;
    ////////////////////////////////////////////////////////////
    
    //////////////////////RETURNING POSTFIX FORM////////////////
        vector<string> postfix = expr.GetPostfix();
        for (int i = 0; i < postfix.size(); ++i) {
            cout << postfix[i];
        }
        cout << endl;
    ////////////////////////////////////////////////////////////

    //////////////////////GETTING OPERANDS VALUE////////////////
        vector<string> operands = expr.GetOperands();
        map<string, double> values;
        double val;

        for (const auto& op : operands) {
            if (!StrIsNumber(op)) {
                cout << "Input value of operand " << op << endl;
                cin >> val;
                values[op] = val;
        }
    }
    ////////////////////////////////////////////////////////////
     
    //////////////////////CALCULATING///////////////////////////
        cout<<"Answer: " << expr.Calculate(values) << endl;
    ////////////////////////////////////////////////////////////

        return 0;
    }
}
/*
int main() {
    cout << "Arithmetic translator supports variables and operations +,-,*,/,unary minus\n" << "Input expression without spaces\n" << "Input variable value after inputing the expression\n" << endl;

    while (true) {
        //////////////////////INPUT EXPRESSION//////////////////////
        string input;
        cout << "Enter expression: \n";
        cin >> input;

        Arithmetic_Expression expr(input);
        vector<string> postfix = expr.GetPostfix();
        ////////////////////////////////////////////////////////////
        

        //////////////////////GETTING OPERANDS VALUE////////////////
        vector<string> operands = expr.GetOperands();
        map<string, double> values;
        double val;

        for (const auto& op : operands) {
            if (!StrIsNumber(op)) {
                cout << "Input value of operand " << op << endl;
                cin >> val;
                values[op] = val;
            }
        }
        ////////////////////////////////////////////////////////////

        //////////////////////CALCULATING///////////////////////////
        cout << "Answer: " << expr.Calculate(values) << endl;
        ////////////////////////////////////////////////////////////
    }

    return 0;
}*/