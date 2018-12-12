#include "class.h"

int main()
{
	//�������� �������� ������ (����. Reverse Polish notation, RPN)
	TQ P(100);//������� ��� polish ������
	TQ unP(100);//������� ��� ������� ������
	char c[100] = "2+3*(19-9)-5+3";

	if (StringGood(c) == false)
	{
		cout << "The string is written incorrectly" << endl;
		return 0;
	}

	TLex lex(unP);
	unP = lex.convert(c);//������������ ������ � �������
	cout << unP << endl;
	P = unP.RPN();//��������� � �������� ������
	cout << "RPN:" << P << endl;
	int result;
	result = P.GetResult();//������� �����
	cout << "result= " << result << endl;

	return 0;
}