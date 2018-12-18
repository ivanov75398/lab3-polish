#pragma once

#include <iostream>
#include <string>
#include <conio.h>
#include <stdio.h>

using namespace std;

class TValue {

public:
	TValue() {}
	virtual int prior() = 0;
	virtual int GetPrior() = 0;
	virtual void print(ostream &os) = 0;
	virtual bool operator ==(const TValue & b) { return true; };
	friend ostream & operator <<(ostream &os, TValue &v);
	virtual operator int() const = 0;
};

class Top : public TValue {
	char c;
public:
	Top(char _c) { c = _c; }
	void print(ostream &os) { os << c; }
	operator int() const { return 100; }

	bool operator ==(const Top & b)
	{
		if (c == b.c)
		{
			return true;
		}
		return false;
	}
	int prior()
	{
		if (c == '(')
		{
			return 0;
		}
		if (c == ')')
		{
			return 1;
		}
		if (c == '+' || c == '-')
		{
			return 2;
		}
		if (c == '*' || c == '/')
		{
			return 3;
		}
	}
	int GetPrior()
	{
		if (c == '+')
		{
			return 1;
		}
		if (c == '-')
		{
			return 2;
		}
		if (c == '*')
		{
			return 3;
		}
		if (c == '/')
		{
			return 4;
		}
	}
};

class Tint : public TValue {
	int v;
public:
	Tint(int _v) { v = _v; }
	int prior() { return -1; }
	int GetPrior() { return -2; }
	void print(ostream &os) { os << v; }
	operator int() const { return v; }

	bool operator ==(const Tint & b)
	{
		if (v == b.v)
		{
			return true;
		}
		return false;
	}
};

class stack {
	int Size;
	int Index;
	TValue **mem;
public:
	stack() {};
	stack(int _Size);
	stack(const stack &b);
	TValue * ReturnVal() { return mem[Index]; }
	int GetSize() { return Index + 1; }
	void push(TValue *val);
	TValue * pop();
	void clean() { Index = -1; }
	stack &operator=(const stack &b);
	bool stackFull();
	bool stackEmpty();
	friend ostream& operator<<(ostream &os, const stack &v);
};

class TQ {
	TValue **mem;
	int size, top, end;
public:
	TQ() {};
	TQ(int _size);
	TQ(const TQ &b);
	bool isempty();
	bool isfull();
	int GetSize() { return size; }
	int GetTop() { return top; }
	int GetEnd() { return end; }
	int GetResult();
	TQ RPN();
	void push(TValue *a);
	TValue *pop();
	TValue *& operator [](int index);
	friend ostream & operator<<(ostream &os, const TQ &v);
};

class TLex {
	//TQ turn;
	std::string s;
public:
	//TLex(TQ _turn) { turn = _turn; }
	int pos(char *s, char c);
	TQ &convert(char *str);
};

class Polish: public TQ {
public:
	int RPN(TQ tq);
	int GetResult(TQ tq);
};

int function_pos(char *s, char c);
bool StringGood(char *string);