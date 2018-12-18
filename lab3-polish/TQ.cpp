#include "class.h"

TQ::TQ(int _size)
{
	size = _size;
	if (size <= 0) { throw - 3; }
	mem = new TValue*[size];
	if (mem == NULL) { throw - 4; }
	end = size - 1;
	top = 0;
}

bool TQ::isempty()
{
	return (top == (end + 1) % size);
}

bool TQ::isfull()
{
	return (top == (end + 2) % size);
}

void TQ::push(TValue *a)
{
	if (isfull()) { throw - 5; }
	end = (end + 1) % size;
	mem[end] = a;
}


TValue *TQ::pop()
{
	if (isempty()) { throw - 6; }
	TValue *a = mem[top];
	top = (top + 1) % size;
	return a;
}

TQ::TQ(const TQ &b)
{
	size = b.size;
	top = b.top;
	end = b.end;
	mem = new TValue*[size];
	int i = top;
	while (i != (end + 1) % size)
	{
		mem[i] = b.mem[i];
		i = (i + 1) % size;
	}
}

ostream & operator<<(ostream &os, const TQ &v)
{
	for (int i = 0; i < (v.end + 1) % v.size; i++)
	{
		cout << *(v.mem[i]);
	}
	return os;
}

TValue *& TQ::operator [](int index)
{
	return mem[index];
}