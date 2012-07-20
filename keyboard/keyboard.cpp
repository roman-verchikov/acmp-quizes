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

#include <fstream>
#include <string>

using namespace std;

char next_char_on_keyboard(char given_char) 
{
	string keyboard("qwertyuiopasdfghjklzxcvbnm");
	size_t char_pos = keyboard.find(given_char);

	return keyboard[ (char_pos+1) % keyboard.length()];
}

int main()
{
	char in_char;

	ifstream in("INPUT.TXT");
	in >> in_char;

	ofstream out("OUTPUT.TXT");
	out << next_char_on_keyboard(in_char);

	return 0;
}
