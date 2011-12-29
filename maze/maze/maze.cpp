#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <iostream>

#include <windows.h>

#define INPUT "INPUT.TXT"
#define OUTPUT "OUTPUT.TXT"

using std::vector;

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

class maze_solver {
public:
    maze_solver(const char *file_name = INPUT) : steps(0), found_path(false) {
        from_file(file_name);
    }

    void from_file(const char *file_name) {
        std::ifstream in(file_name);

        if(in.is_open()) {
            in >> h >> m >> n;
            
            adj_matr.assign(h, vector<vector<char> >());

            for(int i = 0; i < h; i++) {                
                adj_matr[i].assign(m, vector<char>());
                for(int j = 0; j < m; j++) {
                    adj_matr[i][j].assign(n, '\0'); 
                    for(int k = 0; k < n; k++) {
                        in >> adj_matr[i][j][k];

                        if(adj_matr[i][j][k] == START) {
                            m_start.set(k, j, i);
                        } else if (adj_matr[i][j][k] == END) {
                            m_end.set(k, j, i);
                        } 
                    }
                }
            }

            in.close();
        }
    }

    void solve(void)
    {
        DWORD start = GetTickCount();
        reach_end();
        DWORD end = GetTickCount();
        m_totalTime = end-start;
       // construct_shortest_path();
    }

    void reach_end(void)
    {
        std::queue<coords_t> q;
        q.push(m_start);

        while(!q.empty()) {
            coords_t cur = q.front();
            q.pop();

            adj_matr[cur.z][cur.y][cur.x] = cur.get_steps_away();

            if(cur == m_end) {
                found_path = true;
                break;
            }

            coords_t *neighbour = get_neighbours(cur);
            while(*neighbour != invalid_coords()) {
                if(coords_ok(*neighbour) && not_visited(*neighbour) && is_free(*neighbour)) {
                    neighbour->set_steps_away(cur.get_steps_away()+1);

                    visited_nodes.push_back(*neighbour);

                    q.push(*neighbour);
                }
                neighbour++;
            }
        }
    }

    void construct_shortest_path(void)
    {
        std::vector<coords_t> path;
        int min_path = invalid_coord_value();
        coords_t cur = m_end;

        while(min_path != 0) {
            coords_t *neigh = get_neighbours(cur);
            coords_t *nearest_neighbour = neigh;

            while(*neigh != invalid_coords()) {
                int steps_away = adj_matr[neigh->z][neigh->y][neigh->x];

                if(coords_ok(*neigh) && ready_for_path(*neigh) && 
                   (min_path > steps_away)) {
                    min_path = steps_away;
                    nearest_neighbour = neigh;
                }

                neigh++;
            }
            path.push_back(*nearest_neighbour);
            cur = *nearest_neighbour;
        }

        steps = path.size();
    }

    void save_to_file(const char *out_file = OUTPUT) const
    {
        std::ofstream out(out_file);

        if(out.is_open()) {
            out << adj_matr[m_end.z][m_end.y][m_end.x] * 5 << std::endl;
            out << m_totalTime << " ms";
            out.close();
        }
    }

private:

    int m;  // y-size
    int n;  // x-size
    int h;  // z-size

    DWORD m_totalTime;

    int steps;
    bool found_path;


    struct coords_t {
        int x;
        int y;
        int z;

        int steps_away;

        coords_t(int _x = 0, int _y = 0, int _z = 0) : x(_x), y(_y), z(_z), steps_away(0) {}

        void set(int _x, int _y, int _z) {
            x = _x;
            y = _y;
            z = _z;
        }

        bool operator == (const coords_t &rhs) const
        {
            return ((x == rhs.x) && (y == rhs.y) && (z == rhs.z));
        }

        bool operator != (const coords_t &rhs) const 
        {
            return !(*this == rhs);
        }

        void inc_steps(void)
        {
            steps_away++;
        }

        void set_steps_away(int val) 
        {
            steps_away = val;
        }

        int get_steps_away(void)const
        {
            return steps_away;
        }
    } m_start, m_end;

    enum maze_data_t {
        START  = '1',
        COLUMN = 'o',
        FREE   = '.',
        END    = '2',
        MAZE_LAST = 0xffff
    };

    bool coords_ok(int x, int y, int z) const
    {
        return ((x >= 0) && (y >= 0) && (z >= 0) && 
                (x < n) && (y < m) && (z < h));
    }

    bool ready_for_path(const coords_t &c)const
    {
        return ((adj_matr[c.z][c.y][c.x] != START) && 
                (adj_matr[c.z][c.y][c.x] != END) && 
                (adj_matr[c.z][c.y][c.x] != FREE) && 
                (adj_matr[c.z][c.y][c.x] != COLUMN));
    }

    bool coords_ok(const coords_t &c) const
    {
        return ((c.x >= 0) && (c.y >= 0) && (c.z >= 0) && 
                (c.x < n) && (c.y < m) && (c.z < h));
    }

    bool is_free(const coords_t &c) const 
    {
        return (adj_matr[c.z][c.y][c.x] == FREE || adj_matr[c.z][c.y][c.x] == END);
    }

    inline int invalid_coord_value(void)const
    {
        return 0x7FFFFFFF;
    }

    inline coords_t invalid_coords(void)const
    {
        const int INVALID_COORD_VALUE = invalid_coord_value();

        return coords_t(INVALID_COORD_VALUE, INVALID_COORD_VALUE, INVALID_COORD_VALUE);
    }

    // user has to free pointer when no longer in use
    coords_t* get_neighbours(const coords_t &c) const
    {
        const int MAX_NEIGHBOURS = 6;
        static coords_t tmp_neighbours[MAX_NEIGHBOURS];
        int i = 0;

        tmp_neighbours[i++].set(c.x-1, c.y, c.z);
        tmp_neighbours[i++].set(c.x, c.y-1, c.z);
        tmp_neighbours[i++].set(c.x+1, c.y, c.z);
        tmp_neighbours[i++].set(c.x, c.y+1, c.z);
        //tmp_neighbours[4].set(c.x, c.y, c.z-1);
        tmp_neighbours[i++].set(c.x, c.y, c.z+1);
        tmp_neighbours[i++] = invalid_coords();

        return tmp_neighbours;
    }

    bool not_visited(const coords_t &c) const
    {
        for(size_t i = 0; i < visited_nodes.size(); i++) {
            if(visited_nodes[i] == c) return false;
        }

        return true;
    }

    vector<vector<vector<char> > > adj_matr;
    vector<coords_t> visited_nodes;
};

int main()
{
    generate_big_maze(30);

    maze_solver ms;

    ms.solve();
    ms.save_to_file();

    return 0;
}