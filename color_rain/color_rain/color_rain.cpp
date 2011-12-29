/*
 * Цветной дождь
 * (Время: 1 сек. Память: 16 Мб Сложность: 26%)
 * В Банановой республике очень много холмов, соединенных мостами. 
 * На химическом заводе произошла авария, в результате чего испарилось 
 * экспериментальное удобрение "зован". На следующий день выпал цветной 
 * дождь, причем он прошел только над холмами. В некоторых местах падали 
 * красные капли, в некоторых - синие, а в остальных - зеленые, в результате 
 * чего холмы стали соответствующего цвета. Президенту Банановой республики 
 * это понравилось, но ему захотелось покрасить мосты между вершинами холмов 
 * так, чтобы мосты были покрашены в цвет холмов, которые они соединяют. 
 * К сожалению, если холмы разного цвета, то покрасить мост таким образом 
 * не удастся. Посчитайте количество таких "плохих" мостов.
 * 
 * Входные данные
 * 
 * В файле INPUT.TXT в первой строке записано N (0 < N <= 100) - число холмов. 
 * Далее идет матрица смежности, описывающая наличие мостов между холмами 
 * (1-мост есть, 0-нет). Предпоследняя строка пустая, а в последней строке 
 * записано N чисел, обозначающих цвет холмов: 1 - красный; 2 - синий; 3 - зеленый.
 * 
 * Выходные данные
 * 
 * В файл OUTPUT.TXT вывести количество "плохих" мостов.
 * */

#include <fstream>
#include <vector>

#define INPUT "INPUT.TXT"
#define OUTPUT "OUTPUT.TXT"

int main(int argc, char **argv)
{
    std::ifstream in(INPUT);

    if(in.is_open()) {
        int N = 0;
        std::vector<int> hills_adj_matrix;
        std::vector<int> hill_colors;

        in >> N;

        hills_adj_matrix.assign(N*N, 0);
        hill_colors.assign(N, 0);

        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                in >> hills_adj_matrix[i*N+j];
            }
        }

        for(int i = 0; i < N; i++) {
            in >> hill_colors[i];
        }

        in.close();

        int cnt = 0;
        for(int i = 0; i < N; i++) {
            for(int j = i; j < N; j++) {
                if( (hills_adj_matrix[i*N+j] == 1) && 
                    (hill_colors[i] != hill_colors[j]) ) {
                    cnt++;
                }
            }
        }

        std::ofstream out(OUTPUT);
        if(out.is_open()) {
            out << cnt;
            out.close();
        }
    }

    return 0;
}
