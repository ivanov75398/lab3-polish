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

TQ TQ::RPN()
{
	TQ res(size);
	stack Op(size);
	TValue * temp1 = new Top('+');
	TValue * temp2 = new Top('-');
	TValue * temp3 = new Top('*');
	TValue * temp4 = new Top('/');
	TValue * temp5 = new Top('(');
	TValue * temp6 = new Top(')');
	int i = top;
	while (i != (end + 1) % size)
	{
		if ((mem[i]->prior() == -1))
		{
			res.push(mem[i]);
		}
		else
		{
			if (Op.stackEmpty())
			{
				Op.push(mem[i]);
			}
			else
			{
				if (mem[i]->prior() == 0)
				{
					Op.push(mem[i]);
				}
				if (mem[i]->prior() == 1)
				{
					while ((Op.ReturnVal())->prior() != 0)
					{
						res.push(Op.pop());
					}
					Op.pop();
				}
				if (mem[i]->prior() == 2)
				{
					if ((Op.ReturnVal())->prior() >= 2)
					{
						while ((Op.stackEmpty() != true) && (((Op.ReturnVal())->prior() >= 2) == true))
						{
							res.push(Op.pop());
						}
						Op.push(mem[i]);
					}
					if ((Op.ReturnVal())->prior() == 0)
					{
						Op.push(mem[i]);
					}
				}
				if (mem[i]->prior() == 3)
				{
					if ((Op.ReturnVal())->prior() == 3)
					{
						res.push(Op.pop());
						Op.push(mem[i]);
					}
					if ((Op.ReturnVal())->prior() < 3)
					{
						Op.push(mem[i]);
					}
				}
			}
		}
		i++;
	}
	while (Op.stackEmpty() == false)
	{
		res.push(Op.pop());
	}
	return res;
}

int TQ::GetResult()
{
	stack temp(size);
	TValue* a = new Tint(1);
	TValue* b = new Tint(2);
	int i = top;
	while (i != (end + 1) % size)
	{
		if (mem[i]->prior() == -1) //если число
		{
			temp.push(mem[i]);

		}
		else
		{
			if (mem[i]->GetPrior() == 1) //если +
			{
				a = temp.pop();
				b = temp.pop();
				int A(*a);
				int B(*b);
				temp.push(new Tint(A + B));
			}
			if (mem[i]->GetPrior() == 2) //если -
			{
				a = temp.pop();
				b = temp.pop();
				int A(*a);
				int B(*b);
				temp.push(new Tint(B - A));
			}
			if (mem[i]->GetPrior() == 3) //если *
			{
				a = temp.pop();
				b = temp.pop();
				int A(*a);
				int B(*b);
				temp.push(new Tint(A * B));
			}
			if (mem[i]->GetPrior() == 4) //если деление
			{
				a = temp.pop();
				b = temp.pop();
				int A(*a);
				int B(*b);
				temp.push(new Tint(B / A));
			}
		}
		i++;
	}
	TValue* res = new Tint(1);
	res = temp.pop();
	int RES(*res);
	return RES;
}