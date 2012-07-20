// http://acmp.ru/index.asp?main=task&id_task=163
// Уравнение для 5 класса!
// (Время: 1 сек. Память: 16 Мб Сложность: 25%)
// Уравнение для пятиклассников представляет собой строку длиной 5 символов. 
// Второй символ строки является либо знаком '+' (плюс) либо '-' (минус), 
// четвёртый символ — знак '=' (равно). Из первого, третьего и пятого символов 
// ровно два являются цифрами из диапазона от 0 до 9, и один — буквой x,
// обозначающей неизвестное.

// Требуется написать программу, которая позволит решить данное уравнение 
// относительно x.

// Входные данные

// Входной файл INPUT.TXT состоит из одной строки, в которой записано уравнение.

// Выходные данные

// В выходной файл OUTPUT.TXT выведите целое число — значение x.

#include <fstream>
#include <iostream>
#include <string>
#include <utility>

#define TEST_RUN

#define OP_MINUS '-'
#define OP_PLUS '+'

using namespace std;

int evaluate_equation(const string &equation)
{
	int result = 0;
	char operation = equation[1];
	char op1 = equation[0];
	char op2 = equation[2];
	char y = equation[4];

	switch(operation) {
		case OP_MINUS:
			if (op1 == 'x') {
				result = op2 + y - 2*'0';
			} else if (op2 == 'x') {
				result = op1 - y;
			}
			break;
		case OP_PLUS:
			result = (y - ((op1 == 'x') ? op2 : op1));
			break;
	}

	return result;
}

void tests() 
{
	const pair<string, int> tests[] = {
		pair<string, int>("x+5=7", 2),
		pair<string, int>("9-x=1", 8),
		pair<string, int>("x-3=2", 5),
		pair<string, int>("x-0=2", 2),
		pair<string, int>("3+x=6", 3)
	};

	for (const auto& test : tests) {
		int out = evaluate_equation(test.first);

		cout << test.first << ": " << ((out == test.second) ? "PASS" : "FAIL") << " ";
		cout << test.second << " : " << out << endl;
	}
}

void release()
{
	ifstream in("INPUT.TXT");
	string equation;
	getline(in, equation);

	ofstream out("OUTPUT.TXT");
	out << evaluate_equation(equation);
}

int main()
{
#ifdef TEST_RUN
	tests();
#else
	release();
#endif

	return 0;
}
