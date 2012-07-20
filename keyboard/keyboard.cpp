// Клавиатура
// (Время: 1 сек. Память: 16 Мб Сложность: 11%)
// Для данной буквы латинского алфавита нужно вывести справа стоящую букву на 
// стандартной клавиатуре. При этом клавиатура замкнута, т.е. справа от буквы 
// «p» стоит буква «a», от буквы «l» стоит буква «z», а от буквы «m» — буква 
// «q».

// Входные данные

// Входной файл INPUT.TXT содержит один символ — маленькую букву латинского 
// алфавита.

// Выходные данные

// В выходной файл OUTPUT.TXT следует вывести букву стоящую справа от заданной 
// буквы, с учетом замкнутости клавиатуры.

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <utility>


#define RUN_TESTS


using namespace std;

char next_char_on_keyboard(char given_char) 
{
	string keyboard("qwertyuiopasdfghjklzxcvbnm");
	size_t char_pos = keyboard.find(given_char);

	return keyboard[ (char_pos+1) % keyboard.length()];
}

void tests()
{
	pair<char, char> test_data[] = {
		pair<char, char>('q', 'w'),
		pair<char, char>('l', 'z'),
		pair<char, char>('m', 'q'),
		pair<char, char>('p', 'a')
	};

	for (auto& test : test_data) {
		char out = next_char_on_keyboard(test.first);

		cout << ((out == test.second) ? "SUCCEEDED" : "FAILED") << endl;
	}
}

int main()
{
#ifdef RUN_TESTS
	tests();	
#else
	ifstream in('INPUT.TXT');
	in >> in_char;

	ofstream out('OUTPUT.TXT');
	out << next_char_on_keyboard(in_char);
#endif

	return 0;
}