#pragma once﻿
#include <iostream>
#include <vector>
using namespace std;

template <class T>

class stack {
	size_t stack_size;
	std::vector<T> data;
public:
	stack() {
		stack_size = 0;
	}
	
	stack(const stack& other) {
		data.clear();

		stack_size = other.stack_size;

		for (int i = 0; i < stack_size; ++i) {
			data.push_back(other.data[i]);
		}
	}

	~stack() {
		stack_size = 0;
		data.clear();
	}

	stack& operator=(const stack& other) {
		data.clear();

		stack_size = other.stack_size;

		for (int i = 0; i < stack_size; ++i) {
			data.push_back(other.data[i]);
		}

		return *this;
	}

	bool operator==(const stack& other) {
		if ((*this).stack_size != other.stack_size) {
			return 0;
		}

		for (int i = 0; i < stack_size; ++i) {
			if (data[i] != other.data[i]) 
				return 0;
		}
		return 1;
	}

	bool operator!=(const stack& other) {
		if ((*this).stack_size != other.stack_size) {
			return 1;
		}

		for (int i = 0; i < stack_size; ++i) {
			if (data[i] != other.data[i])
				return 1;
		}
		return 0;
	}

	void push(const T val) {
		data.push_back(val);
		stack_size += 1;
	}

	void pop() {
		if (stack_size < 1) throw "Can`t delete element from empty stack";
		data.pop_back();
		stack_size -= 1;
	}

	T& top(){
		if (stack_size < 1) throw "Can`t get top element from empty stack";
		return data[stack_size-1];
	}

	size_t size() const{
		return stack_size;
	}

	bool empty() const{
		return (stack_size==0);
	}

	
	friend istream& operator>>(istream& istr, const stack& s) {
		stack<T> temp = s;
		T current;

		for (int i = 0; i < s.size(); ++i) {
			istr >> temp.top();
			temp.pop();
		}

		return istr;
	}
	
	friend ostream& operator<<(ostream& ostr, const stack& s) {
		stack<T> temp = s;
		T current;

		for (int i = 0; i < s.size(); ++i) {
			ostr << temp.top() << " ";
			temp.pop();
		}
		std::cout << "\n";

		return ostr;
	}
};