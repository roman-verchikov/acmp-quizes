/*
 * Один конь 
 * (Время: 1 сек. Память: 16 Мб Сложность: 43%) 
 * На шахматной доске NxN в клетке (x1,y1) стоит голодный шахматный конь. Он
 * хочет попасть в клетку (x2,y2), где растет вкусная шахматная трава. Какое
 * наименьшее количество ходов он должен для этого сделать?
 * 
 * Входные данные
 * 
 * Входной файл INPUT.TXT содержит пять чисел: N, x1, y1, x2, y2 (5 <= N <= 20,
 * 1 <= x1, y1, x2, y2 <= N). Левая верхняя клетка доски имеет координаты
 * (1,1), правая нижняя - (N,N).
 * 
 * Выходные данные
 * 
 * В выходной файл OUTPUT.TXT необходимо вывести наименьшее число ходов коня.
 *
 * */


#include <fstream>
#include <queue>
#include <vector>

#define INPUT "INPUT.TXT"
#define OUTPUT "OUTPUT.TXT"

int N = 0; // field size

struct coords_t {
    int x;
    int y;

    coords_t(int x_ = 0, int y_ = 0) : x(x_), y(y_), path_len(0) {}

    coords_t operator + (const coords_t &c) const {
        coords_t ret;

        ret.x = x + c.x;
        ret.y = y + c.y;

        return ret;
    }

    void set_path_len(int val) 
    {
        path_len = val;
    }

    int get_path_len(void)const
    {
        return path_len;
    }

    bool operator == (const coords_t &c) const {
        return ((this->x == c.x) && (this->y == c.y));
    }

private:
    int path_len;
};
typedef std::vector<coords_t>::const_iterator CIT;

coords_t start;
coords_t finish;

bool g_found_path = false;
int min_path_len = 0;

void get_input(void)
{
    std::ifstream in(INPUT);

    if(in.is_open()) {
        in >> N;

        in >> start.x >> start.y;
        in >> finish.x >> finish.y;

        start.x--;
        start.y--;
        finish.x--;
        finish.y--;

        in.close();
    }
}

std::vector<coords_t> get_valid_neighbours(const coords_t &c)
{
    const static coords_t possible_deltas[] = {
        coords_t( 1,  2),
        coords_t( 1, -2),
        coords_t( 2,  1),
        coords_t( 2, -1),
        coords_t(-1,  2),
        coords_t(-1, -2),
        coords_t(-2,  1),
        coords_t(-2, -1)
    };

    const static size_t MAX_KNIGHT_MOVES = sizeof(possible_deltas)/sizeof(*possible_deltas); 

    static std::vector<coords_t> visited;
    std::vector<coords_t> out;

    for(CIT i = visited.begin(); i != visited.end(); ++i) {
        if(c == *i) return out;
    }

    visited.push_back(c);

    for(int i = 0; i < MAX_KNIGHT_MOVES; i++) {
        coords_t to_add = c + possible_deltas[i];

        if((to_add.x >= 0 && to_add.x < N) && 
           (to_add.y >= 0 && to_add.y < N) &&
           (std::find(visited.begin(), visited.end(), to_add) == visited.end())) {
                out.push_back(to_add);
        }
    }
    
    return out;    
}

void calc_shortest_path(void)
{
    std::queue<coords_t> vertices;
    vertices.push(start);

    while(!vertices.empty()) {
        coords_t cur_coord = vertices.front();
        vertices.pop();

        int cur_len = cur_coord.get_path_len();

        if(cur_coord == finish) {
            g_found_path = true;
            min_path_len = cur_len;
            return;
        }

        std::vector<coords_t> neighbours = get_valid_neighbours(cur_coord);

        for(CIT i = neighbours.begin(); i != neighbours.end(); ++i) {
            vertices.push(*i);

            vertices.back().set_path_len(cur_len + 1);
        }
    }
}

void save_result(void)
{
    std::ofstream out(OUTPUT);

    if(out.is_open()) {
        if(g_found_path) {
            out << min_path_len;
        } else {
            out << "Path not found";
        }

        out.close();
    }
}

int main()
{
    get_input();
    calc_shortest_path();
    save_result();

    return 0;
}
