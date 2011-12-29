/*
 * Лабиринт 
 * (Время: 1 сек. Память: 16 Мб Сложность: 57%) 
 * Открыв глаза, Принц Персии обнаружил, что находится на верхнем уровне
 * подземного лабиринта Джаффара. Лабиринт состоит из h уровней, расположенных
 * строго друг под другом. Каждый уровень представляет собой прямоугольную
 * площадку, разбитую на m х n участков. На некоторых участках стоят колонны,
 * поддерживающие потолок, на такие участки Принц заходить не может.
 * 
 * Принц может перемещаться с одного участка на другой свободный участок того
 * же уровня, так же он может проломить пол под собой и оказаться уровнем
 * нижнее (на самом нижнем уровне пол проломить нельзя). Любое перемещение
 * занимает у Принца 5 секунд.
 * 
 * На одном из участков нижнего уровня Принца ждет Принцесса. Помогите Принцу
 * найти Принцессу, потратив на это как можно меньше времени.
 * 
 * Входные данные
 * 
 * В первой строке входного файла INPUT.TXT содержатся натуральные числа h, m и
 * n — высота и горизонтальные размеры лабиринта (2 <= h, m, n <= 50). Далее во
 * входном файле приведены h блоков, описывающих уровни лабиринта в порядке от
 * верхнего к нижнему. Каждый блок содержит m строк, по n символов в каждой:
 * «.» обозначает свободный участок, «о» обозначает участок с колонной, «1»
 * обозначает свободный участок, в котором оказался Принц в начале своего
 * путешествия, «2» обозначает свободный участок, на котором томится Принцесса.
 * Символы «1» и «2» встречаются во входном файле ровно по одному разу: символ
 * «1» — в описании самого верхнего уровня, а символ «2» — в описании самого
 * нижнего. Соседние блоки разделены одной пустой строкой.
 * 
 * Выходные данные
 * 
 * В выходной файл OUTPUT.TXT выведите минимальное время в секундах,
 * необходимое Принцу, чтобы найти Принцессу. Поскольку добро всегда побеждает
 * Зло, гарантируется, что Принц может это сделать.
 **/

#include <stdio.h>
#include <string.h>
#include <queue>
#include <fstream>
#include <windows.h>

#define INPUT "INPUT.TXT"
#define OUTPUT "OUTPUT.TXT"

#define MAX_MAZE_SIZE     100
#define N                 MAX_MAZE_SIZE

#define INVALID_DISTANCE  0x7fffffff

#define START  '1'
#define FINISH '2'
#define COLUMN 'o'
#define FREE   '.'

typedef char input_matr_t;
typedef int  adj_matr_t;
typedef adj_matr_t distance_t;


//---------------------------------------------------------------------------
// Global data
input_matr_t input_matr[N][N][N]; // contains input data
adj_matr_t   adj_matr[N][N][N];   // contains distance from start to finish

int g_h = 0;
int g_m = 0;
int g_n = 0;

struct coords_t {
    int i;
    int j;
    int k;

    void set(int _i, int _j, int _k) {
        i = _i;
        j = _j;
        k = _k;
    }

    bool is_valid(void)const {
        return (i >= 0 && j >= 0 && k >= 0 && 
                i < g_h && j < g_m && k < g_n);
    }
};

coords_t g_start;
coords_t g_finish;

//---------------------------------------------------------------------------
// Functions

void generate_big_maze(int size)
{
    const int SIZE = size;
    const int TOTAL_SIZE = SIZE+1; // includes newline

    char *s = new char[TOTAL_SIZE];

    if(s) {
        memset(s, 0, SIZE*sizeof(*s));
        memset(s, '.', SIZE*sizeof(*s));
        s[SIZE] = '\n';

        char *block = new char [TOTAL_SIZE*SIZE];

        if(block) {
            for(int i = 0; i < SIZE; i++) {
                memcpy(block + i*TOTAL_SIZE, s, sizeof(*s)*TOTAL_SIZE);
            }

            std::ofstream out(INPUT);

            if(out.is_open()) {
                out << SIZE << " " << SIZE << " " << SIZE << std::endl;

                int START_POS = out.tellp();

                for(int i = 0; i < SIZE; i++) {
                    out.write(block, TOTAL_SIZE*SIZE);
                    out << std::endl;                    
                }

                int END_POS = static_cast<int>(out.tellp())-5;

                out.flush();

                out.seekp(START_POS, std::ios_base::beg);
                out << '1';
                out.seekp(END_POS, std::ios_base::beg);
                out << '2';
                out.flush();

                out.close();
            }

            delete [] block;
        }

        delete [] s;
    }
}

void get_input(void)
{
    memset(input_matr, 0, sizeof(input_matr_t)*N*N*N);    

    freopen(INPUT, "r", stdin);

    scanf("%d %d %d\n", &g_h, &g_m, &g_n);

    for(int i = 0; i < g_h; i++) {
        for(int j = 0; j < g_m; j++) {
            for(int k = 0; k < g_n; k++) {
                scanf("%c", &(input_matr[i][j][k]));

                adj_matr[i][j][k] = INVALID_DISTANCE;

                if(input_matr[i][j][k] == START) {
                    g_start.set(i,j,k);
                    adj_matr[i][j][k] = 0;
                } else if (input_matr[i][j][k] == FINISH) {
                    g_finish.set(i,j,k);
                }
            }
            scanf("\n");
        }
    }    
}

bool visited(const coords_t &c)
{
    return (adj_matr[c.i][c.j][c.k] != INVALID_DISTANCE);
}

distance_t get_distance(const coords_t &c)
{
    return adj_matr[c.i][c.j][c.k];
}

bool is_finish(const coords_t &c)
{
    return (input_matr[c.i][c.j][c.k] == FINISH);
}

void visit(const coords_t &c, distance_t distance) 
{
    adj_matr[c.i][c.j][c.k] = distance;
}

bool is_free(const coords_t &c)
{
    return (input_matr[c.i][c.j][c.k] != COLUMN);
}

coords_t *get_neighbours(const coords_t &c, int &num_coords)
{
    const int MAX_NEIGHBOURS = 5;
    static coords_t neigs[MAX_NEIGHBOURS];
    coords_t tmp_neigs[MAX_NEIGHBOURS];
    int i = 0;

    num_coords = 0;

    tmp_neigs[i++].set(c.i+1, c.j, c.k);
    tmp_neigs[i++].set(c.i, c.j+1, c.k);
    tmp_neigs[i++].set(c.i, c.j-1, c.k);
    tmp_neigs[i++].set(c.i, c.j, c.k-1);
    tmp_neigs[i++].set(c.i, c.j, c.k+1);

    for(int j = 0; j < MAX_NEIGHBOURS; j++) {
        if(tmp_neigs[j].is_valid() && !visited(tmp_neigs[j]) && is_free(tmp_neigs[j])) {
            neigs[num_coords++] = tmp_neigs[j];
        }
    }

    return neigs;
}

void solve(void)
{
    std::queue<coords_t> q;
    q.push(g_start);

    while(!q.empty()) {
        coords_t current_coord = q.front();
        q.pop();

        int num_coords = 0;
        //returns array of valid, unvisited neighbours
        coords_t *neighs = get_neighbours(current_coord, num_coords);
        for(int i = 0; i < num_coords; i++) {
            visit(neighs[i], get_distance(current_coord)+1); 
            q.push(neighs[i]);   

            if(is_finish(neighs[i])) {
                g_finish = neighs[i];
                return;
            }
        }
    }
}

void save_output(size_t maze_size, int time)
{
    std::ofstream out(OUTPUT, std::ios_base::app);

    if(out.is_open()) {
        out << adj_matr[g_finish.i][g_finish.j][g_finish.k]*5 << std::endl;
        out.flush();
        out.close();
    }
}

//---------------------------------------------------------------------------
// Main
int main()
{
    generate_big_maze(maze_size);

    get_input();
    solve();
    save_output();

    return 0;
}
