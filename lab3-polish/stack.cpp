#include "class.h"

stack::stack(int _Size)
{
	Size = _Size;
	mem = new TValue*[Size];
	Index = -1;
}

stack::stack(const stack &b)
{
	Size = b.Size;
	Index = b.Index;
	mem = new TValue*[Size];
	for (int i = 0; i < Index; i++)
	{
		mem[i] = b.mem[i];
	}
}

void stack::push(TValue* val)
{
	if (stackFull()) { throw - 1; }
	Index++;
	mem[Index] = val;
}

TValue* stack::pop()
{
	if (stackEmpty()) { throw - 2; }
	Index--;
	return mem[Index + 1];
}

bool stack::stackFull()
{
	return (Index == Size - 1);
}

bool stack::stackEmpty()
{
	return Index == -1;
}

stack &stack::operator=(const stack &b)
{
	if (this == &b) return *this;
	delete[]mem;
	Size = b.Size;
	Index = b.Index;
	mem = new TValue*[Size];
	for (int i = 0; i < Index; i++)
	{
		mem[i] = b.mem[i];
	}
	return *this;
}

ostream& operator<<(ostream &os, const stack &v)
{
	for (int i = 0; i < v.Index + 1; i++)
	{
		os << *(v.mem[i]);
	}
	return os;
}