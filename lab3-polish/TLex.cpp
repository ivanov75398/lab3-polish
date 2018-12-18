#include "class.h"

int TLex::pos(char *s, char c)
{
	int i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c) return i;
		i++;
	}
	return -1;
}

TQ & TLex::convert(char * str)
{
	TQ turn(100);
	std::string s;
	int st = 0;
	int i = 0;
	char c;
	char op[] = "+-*/()";
	while (str[i] != '\0')
	{
		c = str[i];
		i++;
		if (st == 0)
		{
			if (c == ' ') {}
			if (pos(op, c) >= 0)
			{
				turn.push(new Top(c));
			}
			if ((c >= '0') && (c <= '9'))
			{
				s = c;
				st = 1;
			}
			continue;
		}
		if (st == 1)
		{
			if ((c >= '0') && (c <= '9'))
			{
				s += c;
			}
			if (c == ' ')
			{
				turn.push(new Tint(atoi(s.c_str())));
				st = 0;
			}
			if (pos(op, c) >= 0)
			{
				turn.push(new Tint(atoi(s.c_str())));
				turn.push(new Top(c));
				st = 0;
			}
		}
	}
	if (st == 1)
	{
		turn.push(new Tint(atoi(s.c_str())));
	}
	return turn;
}