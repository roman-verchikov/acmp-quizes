/*
 * Стрелки
 * (Время: 1 сек. Память: 16 Мб Сложность: 20%)
 * Задана последовательность, состоящая только из символов ‘>’, 
 * ‘<’ и ‘-‘. Требуется найти количество стрел, которые спрятаны 
 * в этой последовательности. Стрелы – это подстроки вида ‘>>-->’ 
 * и ‘<--<<’.
 * 
 * Входные данные
 * 
 * В первой строке входного файла INPUT.TXT записана строка, 
 * состоящая из символов ‘>’, ‘<’ и ‘-‘ (без пробелов). Строка 
 * состоит не более, чем из 250 символов.
 * 
 * Выходные данные
 * 
 * В единственную строку выходного файла OUTPUT.TXT нужно вывести 
 * искомое количество стрелок.
 * */

#include <fstream>
#include <cstring>

#define INPUT "INPUT.TXT"
#define OUTPUT "OUTPUT.TXT"

size_t num_of_arrows(const char *s)
{
    const char *arrows[] = {
        ">>-->",
        "<--<<"
    };

    const size_t arrow_len = strlen(*arrows);
    const size_t num_arrows = sizeof(arrows)/sizeof(*arrows);

    size_t n = 0;
    size_t len = strlen(s);

    for(size_t i = 0; i < len; i++) {
        for(size_t k = 0; k < num_arrows; k++) {
            const char *p1 = arrows[k];
            const char *p2 = s+i;

            while(*p1 && *p2 && (*p1 == *p2)) {
                p1++;
                p2++;
            }

            if(p1 == arrows[k] + arrow_len) {
                n++;
            }
        }
    }

    return n;
}

int main()
{
    const int MAX_INPUT = 255;
    std::ifstream in(INPUT);
    char input[MAX_INPUT];

    memset(input, 0x0, sizeof(input));

    if(in.is_open()) {
        in >> input;

        in.close();

        std::ofstream out(OUTPUT);

        if(out.is_open()) {
            out << num_of_arrows(input);
            out.close();
        }
    }

    return 0;
}