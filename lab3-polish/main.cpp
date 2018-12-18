#include "class.h"

int main()
{
	//Обратная польская запись (англ. Reverse Polish notation, RPN)

	TQ unP(100);//Очередь для обычной записи
	char c[100] = "2+3*(19-9)-5+3";

	if (StringGood(c) == false)
	{
		cout << "The string is written incorrectly" << endl;
		return 0;
	}

	TLex lex;
	unP = lex.convert(c);//Конвертируем строку в очередь
	cout << unP << endl;
	Polish P;
	int res;
	res = P.RPN(unP); 
	cout << "result: " << res << endl;

	return 0;
}