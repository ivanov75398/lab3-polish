#include "class.h"

int main()
{
	//Обратная польская запись (англ. Reverse Polish notation, RPN)
	TQ P(100);//Очередь для polish записи
	TQ unP(100);//Очередь для обычной записи
	char c[100] = "2+3*(19-9)-5+3";

	if (StringGood(c) == false)
	{
		cout << "The string is written incorrectly" << endl;
		return 0;
	}

	TLex lex(unP);
	unP = lex.convert(c);//Конвертируем строку в очередь
	cout << unP << endl;
	P = unP.RPN();//Переводим в польскую запись
	cout << "RPN:" << P << endl;
	int result;
	result = P.GetResult();//Находим ответ
	cout << "result= " << result << endl;

	return 0;
}