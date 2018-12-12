#include "class.h"

//TValue;

ostream & operator <<(ostream &os, TValue &v)
{
	v.print(os);
	return os;
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