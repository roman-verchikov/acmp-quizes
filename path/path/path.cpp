/*
 * Путь
 * (Время: 1 сек. Память: 16 Мб Сложность: 40%) 
 * В неориентированном графе требуется найти длину кратчайшего пути между двумя
 * вершинами.
 * 
 * Входные данные
 * 
 * Во входном файле INPUT.TXT записано сначала число N - количество вершин в графе
 * (1<=N<=100). Затем записана матрица смежности (0 обозначает отсутствие ребра, 1
 * - наличие ребра). Затем записаны номера двух вершин - начальной и конечной.
 * 
 * Выходные данные
 * 
 * В выходной файл OUTPUT.TXT выведите длину кратчайшего пути. Если пути не
 * существует, выведите одно число -1.
 */


#include <queue>
#include <algorithm>
#include <vector>
#include <fstream>

#define INPUT "INPUT.TXT"
#define OUTPUT "OUTPUT.TXT"

int N = 0;

int *adj_matr = 0;  // adjacent matrix
int  start    = 0;  // start point
int  finish   = 0;  // end point 
int  len      = 0;  // shortest path length

bool path_exists = false;

void get_input(void)
{
    std::ifstream in(INPUT);

    if(in.is_open()) {
        in >> N;

        adj_matr = new int [N*N];

        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                in >> adj_matr[i*N+j];
            }
        }

        in >> start >> finish;

        // we're counting from zero:
        start--; finish--;

        in.close();
    }
}

void calc_shortest_path(void)
{
    std::queue<int> vertices;
    std::vector<int> visited;
    std::vector<int> path_len(N, 0);

    vertices.push(start);
    visited.push_back(start);

    while(!vertices.empty()) { 
        int cur_vertex = vertices.front();
        vertices.pop();

        int cur_len = path_len[cur_vertex];

        if(cur_vertex == finish) {
            len = cur_len;
            path_exists = true;
            return;
        }

        for(int i = 0; i < N; i++) {
            bool not_visited = (std::find(visited.begin(), visited.end(), i) == visited.end());

            if( not_visited && adj_matr[cur_vertex*N+i]) {
                visited.push_back(i);
                vertices.push(i);
                path_len[i] = cur_len + 1;
            }
        }
    }

    delete [] adj_matr;
}

void save_answer(void)
{
    std::ofstream out(OUTPUT);

    if(out.is_open()) {
        if(path_exists) {
            out << len;
        } else {
            out << -1;
        }
        out.close();
    }
}

int main(void)
{
    get_input();
    calc_shortest_path();
    save_answer();

    return 0;
}
