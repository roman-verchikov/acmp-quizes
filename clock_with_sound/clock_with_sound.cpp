// http://acmp.ru/index.asp?main=task&id_task=253
// Часы с боем
// (Время: 1 сек. Память: 16 Мб Сложность: 25%)
// Старинные часы бьют каждые полчаса. Причем в начале каждого часа они бьют
// столько раз, сколько сейчас часов (по 1 разу – в час ночи и в час дня, по 2
// раза – в два часа ночи в два часа дня и т.д., в полночь и в полдень они
// бьют, соответственно, по 12 раз). И еще 1 раз они бьют в середине каждого
// часа.

// Дан промежуток времени (известно, что прошло строго меньше 24 часов).
// Напишите программу, определяющую, сколько ударов сделали часы за это время.

// Входные данные

// В первой строке входного файла INPUT.TXT записан начальный момент времени,
// во второй строке — конечный. Моменты времени задаются двумя целыми числами,
// разделяющимися пробелом. Первое число задает часы (от 0 до 23), второе —
// минуты (от 1 до 59, при этом оно не равно 30).

// Выходные данные

// В выходной файл OUTPUT.TXT выведите одно число — сколько ударов сделали часы
// за этот отрезок времени.

// Примеры

//+--+---------+-----------+
//|№ |INPUT.TXT|OUTPUT.TXT |
//+--+---------+-----------+
//|1 |5 20     |           |
//|  |10 25    |45         |
//+--+---------+-----------+
//|2 |10 25    |           |
//|  |5 20     |135        |
//+--+---------+-----------+
//|3 |5 2      |           |
//|  |5 21     |0          |
//+--+---------+-----------+

#include <fstream>
#include <iostream>

#define RUN_TESTS

using namespace std;

int get_num_chimes(int start_hour, int start_minute, int end_hour, int end_minute)
{
    int num_chimes = 0;
    int start_time = start_hour * 60 + start_minute;
    int end_time = end_hour * 60 + end_minute;

    int MAX_TIME = 24*60;

    for (; start_time != end_time; start_time = (start_time + 1) % MAX_TIME) {
        int cur_minutes = start_time % 60;
        int cur_hours = start_time / 60 % 12;

        cur_hours = (cur_hours == 0) ? 12 : cur_hours;

        switch (cur_minutes) {
            case 30: ++num_chimes; break;
            case 0: num_chimes += cur_hours; break;
        }
    }

    return num_chimes;
}

void tests() {
    struct {
        int start_hour;
        int start_min;
        int end_hour;
        int end_min;

        int expected_chimes;
    } test_cases [] = {
        {5, 20, 10, 25, 45},
        {10, 25, 5, 20, 135},
        {23, 59, 0, 31, 13},
        {23, 59, 1, 29, 14},
        {5, 2, 5, 25, 0}
    };

    for(auto &test : test_cases) {
        int res = get_num_chimes(test.start_hour, test.start_min, test.end_hour, test.end_min);

        cout << test.start_hour << ":" << test.start_min << " - ";
        cout << test.end_hour << ":" << test.end_min;
        if (res == test.expected_chimes) {
            cout << "\tPASS" << endl;
        } else {
            cout << "\tFAIL: expected " << test.expected_chimes << ", got " << res << endl;
        }
    
    }
}

int main()
{
#ifdef RUN_TESTS
    tests();
#else
    int start_hour, start_minute, end_hour, end_minute;

    ifstream in("INPUT.TXT");
    in >> start_hour >> start_minute >> end_hour >> end_minute;
    in.close();


    ofstream out("OUTPUT.TXT");
    out << get_num_chimes(start_hour, start_minute, end_hour, end_minute);
#endif

    return 0;
}
