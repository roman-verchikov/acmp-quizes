#include <fstream>
#include <stack>
#include <vector>
#include <algorithm>

#define INPUT "INPUT.TXT"
#define OUTPUT "OUTPUT.TXT"

class find_circles_class {
public:
    find_circles_class() : 
      is_tree(true) 
    {}

    ~find_circles_class() 
    {
        delete [] p_adj_matr;
    }

    void get_input(const char *file = INPUT)
    {
        std::ifstream in(file);

        if(in.is_open()) {
            in >> N;

            const int matr_size = N*N;
            p_adj_matr = new int [matr_size];

            for(int i = 0; i < matr_size; i++) {
                in >> p_adj_matr[i];
            }

            in.close();
        }
    }

    void solve(void)
    {
        is_tree = (has_no_cycles() && can_be_traversed()) ? true : false;
    }

    void save_output(const char *file = OUTPUT)
    {
        std::ofstream out(file);

        if(out.is_open()) {
            out << ((is_tree) ? "YES" : "NO");

            out.flush();
            out.close();
        }
    }
private:

    std::vector<int> get_neighbours(int cur_vertice, std::vector<int> &visited) const
    {
        std::vector<int> neigs;

        for(int i = 0; i < N; i++) {
            if(std::find(visited.begin(), visited.end(), i) == visited.end() && 
               p_adj_matr[cur_vertice*N+i] == 1) {
                neigs.push_back(i);
            }
        }

        return neigs;
    }

    bool can_be_traversed(void)
    {
        std::stack<int>  vertices;
        std::vector<int> visited;

        vertices.push(0);

        while(!vertices.empty()) {
            int cur_vertice = vertices.top();
            vertices.pop();

            visited.push_back(cur_vertice);

            std::vector<int> neighs = get_neighbours(cur_vertice, visited);

            for(std::vector<int>::const_iterator i = neighs.begin(); i != neighs.end(); ++i) {
                vertices.push(*i);
            } 
        }

        return (visited.size() == N);
    }

    bool has_no_cycles(void)
    {
        int num_edges = 0;

        for(int i = 0; i < N; i++) {        
            for(int j = i+1; j < N; j++) {
                if(p_adj_matr[i*N+j] == 1) {
                    num_edges++;
                }
            }
        }

        return (num_edges == N - 1);
    }

    int N;
    int *p_adj_matr;

    bool is_tree;
};

int main()
{
    find_circles_class fc;

    fc.get_input();
    fc.solve();
    fc.save_output();
}