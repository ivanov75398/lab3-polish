#include "class.h"

//TValue;

ostream & operator <<(ostream &os, TValue &v)
{
	v.print(os);
	return os;
}

// Polish;

int Polish::GetResult(TQ tq)
{
	int size = tq.GetSize();
	int top = tq.GetTop();
	int end = tq.GetEnd();
	stack temp(size);
	TValue* a = new Tint(1);
	TValue* b = new Tint(2);
	int i = top;
	while (i != (end + 1) % size)
	{
		if (tq[i]->prior() == -1) //если число
		{
			temp.push(tq[i]);

		}
		else
		{
			if (tq[i]->GetPrior() == 1) //если +
			{
				a = temp.pop();
				b = temp.pop();
				int A(*a);
				int B(*b);
				temp.push(new Tint(A + B));
			}
			if (tq[i]->GetPrior() == 2) //если -
			{
				a = temp.pop();
				b = temp.pop();
				int A(*a);
				int B(*b);
				temp.push(new Tint(B - A));
			}
			if (tq[i]->GetPrior() == 3) //если *
			{
				a = temp.pop();
				b = temp.pop();
				int A(*a);
				int B(*b);
				temp.push(new Tint(A * B));
			}
			if (tq[i]->GetPrior() == 4) //если деление
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

int Polish::RPN(TQ tq)
{
	int size = tq.GetSize();
	int top = tq.GetTop();
	int end = tq.GetEnd();
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
		if (tq[i]->prior() == -1)
		{
			res.push(tq[i]);
		}
		else
		{
			if (Op.stackEmpty())
			{
				Op.push(tq[i]);
			}
			else
			{
				if (tq[i]->prior() == 0)
				{
					Op.push(tq[i]);
				}
				if (tq[i]->prior() == 1)
				{
					while ((Op.ReturnVal())->prior() != 0)
					{
						res.push(Op.pop());
					}
					Op.pop();
				}
				if (tq[i]->prior() == 2)
				{
					if ((Op.ReturnVal())->prior() >= 2)
					{
						while ((Op.stackEmpty() != true) && (((Op.ReturnVal())->prior() >= 2) == true))
						{
							res.push(Op.pop());
						}
						Op.push(tq[i]);
					}
					if ((Op.ReturnVal())->prior() == 0)
					{
						Op.push(tq[i]);
					}
				}
				if (tq[i]->prior() == 3)
				{
					if ((Op.ReturnVal())->prior() == 3)
					{
						res.push(Op.pop());
						Op.push(tq[i]);
					}
					if ((Op.ReturnVal())->prior() < 3)
					{
						Op.push(tq[i]);
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
	cout << "polish: " << res << endl;
	int otvet;
	otvet = GetResult(res);
	return otvet;
}

// Other;

int function_pos(char *s, char c)
{
	int i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			return i;
		}
		i++;
	}
	return -1;
}
bool StringGood(char *string)
{
	int i = 0;
	int cnt = 0;//Счетчик для скобок
	char c1[] = "+-*/()";
	char c2[] = "+-*/";
	char sk1 = '(';
	char sk2 = ')';
	if (i == 0)
	{
		if (function_pos(c2, string[i]) >= 0)
		{
			return false;
		}
	}
	while (string[i] != '\0')
	{
		if (string[i] == ')')
		{
			cnt--;
			if (cnt < 0)
			{
				return false;
			}
		}
		if (i > 0)
		{
			if (((string[i] >= '0') && (string[i] <= '9')) && string[i - 1] == sk2)
			{
				return false;
			}
		}
		if (i > 0)
		{
			if ((function_pos(c2, string[i]) >= 0) && string[i - 1] == sk1)
			{
				return false;
			}
		}
		if (i > 0)
		{
			if ((function_pos(c2, string[i]) >= 0) && string[i + 1] == sk2)
			{
				return false;
			}
		}
		if (string[i + 1] != '\0')
		{
			if (((string[i] >= '0') && (string[i] <= '9')) && string[i + 1] == sk1)
			{
				return false;
			}
		}
		if (i > 0)
		{
			if ((function_pos(c2, string[i]) >= 0) && (function_pos(c2, string[i - 1]) >= 0))
			{
				return false;
			}
		}
		if (string[i] == '(')
		{
			cnt++;
		}
		if ((((string[i] >= '0') && (string[i] <= '9')) || (function_pos(c1, string[i]) >= 0)) == false)
		{
			return false;
		}
		i++;
	}
	i--;
	if (function_pos(c2, string[i]) >= 0)
	{
		return false;
	}
	if (cnt > 0)
	{
		return false;
	}
	return true;
}