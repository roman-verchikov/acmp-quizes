/*
 * Скачки (Время: 1 сек. Память: 16 Мб Сложность: 32%) Иван Иванович любит ходить
 * на скачки, надеясь на них заработать кругленькую сумму. Ему приглянулась лошадь
 * с номером K, и он решил проверить, сможет ли она выиграть у всех остальных
 * лошадей. Иван Иванович раздобыл информацию, в которой для некоторых пар лошадей
 * сообщается, какая из этих лошадей быстрее. Также он узнал, что у всех лошадей
 * разные скорости.
 * 
 * Требуется написать программу, которая поможет Ивану Ивановичу точно определить
 * может ли выиграть выбранная им лошадь.
 * 
 * Входные данные
 * 
 * Входной файл INPUT.TXT содержит в первой строке два целых числа N (1 <= N <=
 * 100) и K (1 <= K <= N), где N – количество лошадей, принимающих участие в
 * скачках, K – номер лошади, на которую хочет сделать ставку Иван Иванович.
 * Следующие строки содержат по два числа X и Y (1 <= X, Y <= N), обозначающие,
 * что лошадь с номером X быстрее лошади с номером Y. Пары X и Y не повторяются.
 * Набор данных завершается строкой, содержащей единственный ноль. Эту строку
 * обрабатывать не надо.
 * 
 * Гарантируется, что информация, раздобытая Иваном Ивановичем, корректна.
 * 
 * Выходные данные
 * 
 * Выходной файл OUTPUT.TXT должен содержать слово «Yes», если Иван Иванович
 * уверен в своем выигрыше и «No» в противном случае.
 *
 * */


#include <fstream>
#include <vector>
#include <map>
#include <list>

#define INPUT "INPUT.TXT"
#define OUTPUT "OUTPUT.TXT"

class node {
public:
    node(int n) : nr(n), marked(false) {}

    bool path_to(int n) const
    {
        for(std::vector<const node*>::const_iterator i = to.begin();
            i != to.end(); ++i) {
                if((*i)->nr == n) return true;
                else if((*i)->path_to(n)) return true;
        }

        return false;
    }

    void add_path(const node *nd) {
        for(size_t i = 0; i != to.size(); i++) {
            if(nd->nr == to[i]->nr) return;
        }
        to.push_back(nd);
    }

    bool is_marked(void)const
    {
        return marked;
    }

    void mark(void)const
    {
        // very ugly...
        const_cast<node*>(this)->marked = true;
    }

    int get_nr(void) const {
        return nr;
    }

public:
    int nr;
    bool marked;

    std::vector<const node*> to;
};

class graph {
public:
    graph(int n) {
        for(int i = 1; i <= n; i++) {
            nodes.push_back(node(i));
        }

        visited.assign(n,false);
    }

    void traverse(int from) 
    {
        visited[from-1] = true;
        for(size_t i = 0; i != nodes[from-1].to.size(); i++) {
            traverse(nodes[from-1].to[i]->nr);
        }
    }

    void bfs_traverse(int from)
    {
        std::list<int> q;

        q.push_back(from);

        while(!q.empty() && !visited_all_nodes()) {

            int cur_node = q.front();
            q.pop_front();
            visited[cur_node-1] = true;

            for(size_t i = 0; i != nodes[cur_node-1].to.size(); i++) {
                if(!nodes[cur_node-1].to[i]->is_marked()) {
                    q.push_back(nodes[cur_node-1].to[i]->nr);
                    nodes[cur_node-1].to[i]->mark();
                }
            }
        }
    }

    bool visited_all_nodes(void)const {
        for(size_t i = 0; i != visited.size(); i++) {
            if(visited[i] != true) return false;
        }

        return true;
    }

    void add_path(int from, int to) {
        nodes[from-1].add_path(&(nodes[to-1]));
    }   

    bool path_exists(int from, int to) const
    {
        return nodes[from-1].path_to(to);
    }

private:
    std::vector<node> nodes;

    std::vector<bool> visited;
};

int main()
{
    std::ifstream in(INPUT);

    if(in.is_open()) {
        int N = 0;
        int K = 0;
        int better = 0;
        int worse = 0;

        in >> N >> K;

        graph G(N);

        while(1) {
            in >> better >> worse;

            if(better != 0) {
                G.add_path(better, worse);
            } else {
                break;
            }
        }

        in.close();

        //G.traverse(K);
        G.bfs_traverse(K);

        std::ofstream out(OUTPUT);

        if(out.is_open()) {
            out << ((G.visited_all_nodes()) ? "Yes" : "No");
            out.close();
        }
    }

    return 0;
}
