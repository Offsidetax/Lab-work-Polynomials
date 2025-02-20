#pragma once
#include <iostream>
#include <string>
#include "stack.h"
#include <vector>
#include <map>

using namespace std;

inline bool isNumber(const std::string& str) {
	if (str.empty()) return false;

	for (size_t i = 0; i < str.length(); ++i) {
		if ((!isdigit(str[i])) && (str[i] != '.')) {
			return false;
		}
	}
	return true;
}

class Arithmetic_Expression {
	string infix;
	vector<string> postfix;
	vector<string> lexems;
	map<string, double> priority;
	map<string, double> operands;

	void Parse() {
		int i = 0;
		int bracketsNum = 0;
		int dotNum = 0;
		string curItem;

		while(i < infix.length()) {
			switch (infix[i]) {
			case '+': case '*': case '/':
				if ((i == infix.length() - 1) || (infix[i + 1] == '+') || (infix[i + 1] == '-') || (infix[i + 1] == '*') || (infix[i + 1] == '/')) {
					std::cout << "Incorrect input of operators!" << std::endl;
					throw "Incorrect input of operaators!";
				}
				curItem+=infix[i];	
				lexems.push_back(curItem);
				curItem.clear();
				i++;
				break;

			case '-': //Проверка унарный или бинарный минус
				curItem += infix[i];

				if ((i == 0) || (infix[i-1] == '(')) { //унарный
					lexems.push_back('u' + curItem);
				}
				else {
					lexems.push_back(curItem);
				}

				curItem.clear();
				i++;
				break;

			case '(':
				bracketsNum++;
				curItem += infix[i];
				lexems.push_back(curItem);
				curItem.clear();
				i++;
				break;

			case ')':
				if (bracketsNum == 0) {
					std::cout << "Incorrect input of brackets!" << std::endl;
					throw "Incorrect input of brackets!";
				}
				bracketsNum--;
				curItem += infix[i];
				lexems.push_back(curItem);
				curItem.clear();
				i++;
				break;

			case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': case '.':
				if (infix[i] == '.') curItem += '0'; //Добавляем 0 к десятичной записи числа, если его нет
				while (isdigit(infix[i]) || (infix[i] == '.')) {
					if (infix[i] == '.') dotNum++;
					curItem += infix[i];
					i++;
				}

				if (isalpha(infix[i])) {
					std::cout << "Incorrect variable input! (It can`t start with a number)" << std::endl;
					throw "Incorrect variable input! (It can`t start with a number)";
				}

				if ((dotNum > 1) || (infix[i - 1] == '.')) {
					std::cout << "Incorrect decimal number input!" << std::endl;
					throw "Incorrect decimal number input!";
				}
				dotNum = 0;
				lexems.push_back(curItem);
				curItem.clear();
				break;
			
			default:
				if (isalpha(infix[i])) {
					while ((isalpha(infix[i])) || (isdigit(infix[i]))){
						curItem += infix[i];
						i++;
					}
					lexems.push_back(curItem);
					curItem.clear();
					break;
				}
				else{
					std::cout << "Unknown symbol -> " << infix[i] << std::endl;
					throw "Unknown symbol";
				}
			}
		}
		if (bracketsNum != 0) {
			std::cout << "Incorrect input of brackets!" << std::endl;
			throw "Incorrect input of brackets!";
		}

	}

	void InfixToPostfix() {
		Parse();
		stack<string> st;
		string stackItem;
		int i = 0;

		while (i < lexems.size()) {
			if (lexems[i] == "(") {
				st.push(lexems[i]);
			}
			else if (lexems[i] == ")"){
				stackItem = st.top();
				st.pop();
				while (stackItem != "(") {
					postfix.push_back(stackItem);
					stackItem = st.top();
					st.pop();
				}
			}
			else if ((lexems[i] == "+") || (lexems[i] == "-") ||
				(lexems[i] == "*") || (lexems[i] == "/") || (lexems[i] == "u-")) {
				while (!st.empty()) {
					stackItem = st.top();
					st.pop();
					if (priority[lexems[i]] <= priority[stackItem])
						postfix.push_back(stackItem);
					else {
						st.push(stackItem);
						break;
					}
				}
				st.push(lexems[i]);
			}
			else {
				if (isNumber(lexems[i])) {
					operands.insert({ lexems[i], std::stod(lexems[i])});
				}
				else {
					operands.insert({ lexems[i], 0.0 });
				}
				postfix.push_back(lexems[i]);
			}	

			i++;
		}

		while (!st.empty()) {
			stackItem = st.top();
			st.pop();
			postfix.push_back(stackItem);
		}
	}

public:
	Arithmetic_Expression(string expression): infix(expression) {
		priority = { {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}, {"u-", 3} };
		InfixToPostfix();
	}

	string GetInfix() const {
		return infix;
	}

	vector<string> GetPostfix() const {
		return postfix;
	}

	vector<string> GetOperands() const {
		vector<string> op;
		for (auto& curItem : operands) {
			op.push_back(curItem.first);
		}
		return op;
	}

	double Calculate(const map<string, double>& values) {
		stack<double> st;
		int stSize = 0;
		double lOperand, rOperand;

		for (auto& val : values) {
			try {
				operands.at(val.first) = val.second;
			}
			catch (out_of_range &e) {};
		}

		for (int i = 0; i < postfix.size(); ++i) {
			string lexem = postfix[i];
			if (lexem == "+") {
				if (stSize<2) {
					std::cout << "Incorrect input!" << std::endl;
					throw "Incorrect input!";
				}

				rOperand = st.top();
				st.pop();
				lOperand = st.top();
				st.pop();
				stSize--;

				st.push(lOperand + rOperand);
			}
			else if (lexem == "-") {
				if (stSize < 2) {
					std::cout << "Incorrect input!" << std::endl;
					throw "Incorrect input!";
				}
				
				rOperand = st.top();
				st.pop();
				lOperand = st.top();
				st.pop();
				stSize--;

				st.push(lOperand - rOperand);
			}
			else if (lexem == "u-") {
				if (stSize == 0) {
					std::cout << "Incorrect input!" << std::endl;
					throw "Incorrect input!";
				}

				rOperand = st.top();
				st.pop();

				st.push((-1) * rOperand);
			}
			else if (lexem == "*") {
				if (stSize < 2) {
					std::cout << "Incorrect input!" << std::endl;
					throw "Incorrect input!";
				}

				rOperand = st.top();
				st.pop();
				lOperand = st.top();
				st.pop();
				stSize--;

				st.push(lOperand * rOperand);
			}
			else if (lexem == "/") {
				if (stSize < 2) {
					std::cout << "Incorrect input!" << std::endl;
					throw "Incorrect input!";
				}

				rOperand = st.top();
				st.pop();
				if (rOperand == 0) {
					std::cout << "Error! Division by zero!" << std::endl;
					throw "Incorrect input!";
				}
				lOperand = st.top();
				st.pop();
				stSize--;

				st.push(lOperand / rOperand);
			}
			else{
				stSize++;
				st.push(operands[lexem]);
			}
		}

	double res = st.top();
	st.pop();
	
	if (!st.empty()) {
		std::cout << "Incorrect expression! (Incorrect bracket input)" << std::endl;
		throw "Incorrect expression";
	}
	return res;
	}
};
/*
#pragma once
#include <utilities>

template <class TKey, class TValue>
class UnsortedTable {
	std::vector<std::pair<TKey, TValue>> data;

public:
	iterator insert(const TKey& key, const TValue& value); //можно вместо void возвращать итератор на вставленный элемент
	iterator erase(const TKey& key); //итератор на следующий после удаленного
	iterator find(const TKey& key);//итератор на  найденный элемент и на конец, если не найден

	TValue& operator[](const TKey& key); //dict[key]=10 не особо нужен оказывается

	class iterator {...}; //у других таблиц будет тот же интерфейс
};*/