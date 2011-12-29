// Алгоритм Дейкстры 
// (Время: 1 сек. Память: 16 Мб Сложность: 47%) 
// Дан ориентированный взвешенный граф. Для него вам необходимо найти кратчайшее
// расстояние от вершины S до вершины F.
// 
// Входные данные
// 
// В первой строке входного файла INPUT.TXT записаны три числа: N, S и F (1 <= N
// <= 100; 1 <= S, F <= N), где N - количество вершин графа. В следующих N строках
// записаны по N чисел - матрица смежности графа, где число в i-ой строке j-ом
// столбце соответствует ребру из i в j: -1 означает отсутствие ребра между
// вершинами, а любое неотрицательное целое число (от 0 до 100) - наличие ребра
// данного веса . На главной диагонали матрицы всегда записаны нули.
// 
// Выходные данные
// 
// В выходной файл OUTPUT.TXT необходимо вывести искомое расстояние или -1, если
// пути между указанными вершинами не существует.
//
// http://acmp.ru/?main=task&id_task=132
//

#include <fstream>
#include <deque>
#include <algorithm>
#include <iterator>
#include <limits>

const int MAX_N = 100;

int   A[MAX_N * MAX_N];
int   dist[MAX_N];

int   N, S, F;
bool  path_found = false;

using namespace std;

inline int index(int i, int j)
{
   return ((i * N) + j);
}

void read_input()
{
   ifstream in("INPUT.TXT");

   if (in.is_open()) {
      in >> N >> S >> F;

      --S;
      --F;

      istream_iterator<int> begin(in);
      istream_iterator<int> end;

      copy(begin, end, A);
      fill(dist, dist + sizeof(dist)/sizeof(*dist), numeric_limits<int>::max());
      dist[S] = 0;
   }
}

void find_shortest_path()
{
   deque<int> Q;
   Q.push_back(S);

   while (!Q.empty()) {
      int cur = Q.front();
      if (dist[cur] == numeric_limits<int>::max()) {
         break;
      }
      Q.pop_front();

      if (cur == F) {
         path_found = true;
      }

      for (int i = 0; i < N; ++i) {
         if (i != cur && A[index(cur, i)] >= 0) {
            int alt = A[index(cur, i)] + dist[cur];

            if (alt < dist[i]) {
               dist[i] = alt;
               Q.push_back(i);
            }
         }
      }

      sort(Q.begin(), Q.end());
   }
}

void save_answer()
{
   ofstream out("OUTPUT.TXT");

   if (out.is_open()) {
      out << ((path_found) ? dist[F] : -1);
   }
}


int main()
{
   read_input();
   find_shortest_path();
   save_answer();

   return 0;
}
