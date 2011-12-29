#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

#define N_MAX 100
#define WALL '@'
#define FREE ' '

int N, M;
char char_field[N_MAX * N_MAX];
int field[N_MAX*N_MAX];

enum direction_t {
    LEFT,
    UP,
    RIGHT,
    DOWN,
    NUM_DIRECTIONS,
    DEFAULT_DIRECTION = DOWN
};

struct point_t {
    int x;
    int y;

    point_t(int _x = 0, int _y = 0) : x(_x), y(_y) {}

    point_t(const point_t &pt) {
        x = pt.x;
        y = pt.y;
    }

    bool operator == (const point_t &pt) const {
        return (this->x == pt.x) && 
               (this->y == pt.y);
    }

    bool operator != (const point_t &pt) const {
        return !(*this == pt);
    }

    point_t operator + (const point_t &rhs) const
    {
        return point_t(this->x + rhs.x, this->y + rhs.y);
    }
    
    point_t &operator += (const direction_t &dir) {
        switch (dir) {
            case DOWN:
                ++y;
                break;
            case UP:
                --y;
                break;
            case LEFT:
                --x;
                break;
            case RIGHT:
                ++x;
                break;
        }

        return *this;
    }

    point_t operator + (const direction_t &dir) {
        point_t sum(*this);

        sum += dir;

        return sum;
    }
};

int field_index(const point_t &pt) 
{
    return (pt.x + M * pt.y);
}

bool is_ok(const point_t &pt) 
{
    return ((pt.x >= 1) && 
            (pt.y >= 1) && 
            (pt.x <= M-2) &&
            (pt.y <= N-2) &&
            (field[field_index(pt)] != numeric_limits<int>::max()));
}

vector<point_t> neighs(const point_t &pt, direction_t cur_direction) 
{
    for(int i = 1; i < NUM_DIRECTIONS; ++i) {
        point_t next(pt);
        next += (direction_t)i;

        if (is_ok(next)) {
            if (
        }
    }   

    return v;
} 

point_t next(const point_t &pt) 
{
    point_t next_pt;

    vector<point_t> neighbours = neighs(pt);
    vector<point_t> maxes;
    maxes.reserve(neighbours.size());

    for(unsigned int i = 0; i < neighs.size(); ++i) {
    }

    return next_pt;
}

void visited(const point_t &pt) 
{
    field[field_index(pt)]++;
}

int num_moves()
{
    int n = 0;
    direction_t cur_direction = DEFAULT_DIRECTION;
    point_t cur_pt(1, 1);
    point_t end_pt(M-2, N-2);

    while (cur_pt != end_pt) {
        visited(cur_pt);
        cur_pt = next(cur_pt);
        ++n;
    }

    return n;
}

int main()
{
    ifstream in("INPUT.TXT");

    if(in.is_open()) {
        in >> N >> M;

        for(int i = 0; i < N; ++i) {
            char newline;
            in.read(&newline, 1);
            in.read(char_field + i*M, M);

            for(int j = 0; j < M; ++j) {
                int index = i*M+j;
                switch(char_field[index]) {
                    case WALL:
                        field[index] = numeric_limits<int>::max();
                        break;
                    case FREE:
                        field[index] = 0;
                        break;    
                }
            }
        }

        in.close();

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                cout << char_field[i*M+j];
            }
            cout << endl;
        }
    }

    return 0;
}
    
