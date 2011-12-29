#include <fstream>
#include <iostream>
#include <stack>
#include <queue>
#include <limits>
#include <map>
#include <iterator>

struct point {
   point(int _x = 0, int _y = 0) : x(_x), y(_y) {}

   point& operator = (const point &p) {
      this->x = p.x;
      this->y = p.y;

      return *this;
   }

   bool operator != (const point &p) const {
      return !(*this == p);
   }

   bool operator > (const point &p) const {
      return !(*this < p) && (*this != p);
   }

   bool operator == (const point &p) const {
      return (p.x == this->x && p.y == this->y);
   }

   bool operator < (const point &p) const {
      return (p.x < this->x && p.y < this->y);
   }

   int x;
   int y;
};

std::ostream& operator << (std::ostream &s, const point &p)
{
   return s << "(" << p.x << ", " << p.y << ")";
}

std::ostream& operator << (std::ostream &s, const std::pair<point, point> &p)
{
   return s << p.first << " -> " << p.second << std::endl;
}


struct maze_elem {
   char data;
   int  weight;
   bool visited;
};

const int   MAX_N             = 250;
int         N                 = 0;
bool        path_found        = false;
point       start;
point       finish;
maze_elem   A[MAX_N][MAX_N];

void read_data()
{
   std::ifstream in("INPUT.TXT");

   if (in.is_open()) {
      in >> N;

      for(int i = 0; i < N; ++i) {
         for(int j = 0; j < N; ++j) {
            A[i][j].weight = std::numeric_limits<int>::max();

            in >> A[i][j].data;

            switch (A[i][j].data) {
               case 'X':
                  finish = point(i, j);
                  break;
               case '@':
                  start  = point(i, j);
                  A[i][j].weight = 0;
                  A[i][j].visited = true;
                  break;
            }
         }
      }

      in.close();
   }
}

inline bool valid_coords(int x, int y)
{
   return (x >= 0 && x < N && 
           y >= 0 && y < N );
}

inline bool valid_data(int x, int y) 
{
   return (A[x][y].data != 'O');
}

std::vector<point> neighbours(const point &cur)
{
   const static point diffs[] = {
      point(-1, 0),
      point(0, -1),
      point(1, 0),
      point(0, 1)
   };
   const int K = sizeof(diffs) / sizeof(*diffs);

   std::vector<point> res;
   res.reserve(K);

   for(int i = 0; i < K; ++i) {
      int x = cur.x + diffs[i].x;
      int y = cur.y + diffs[i].y;

      if ( valid_coords(x, y) && valid_data(x, y) && !A[x][y].visited )
      {
         res.push_back(point(x, y));
      }
   }

   return res;
}

void find_shortest_path()
{
   std::map<point, point> previous;
   std::queue<point> s;
   s.push(start);

   while (!s.empty() && !path_found) {
      point cur = s.front();
      s.pop();

      std::vector<point> neighs = neighbours(cur);

      for(size_t i = 0; i < neighs.size(); ++i) {
         int &neigh_weight = A[neighs[i].x][neighs[i].y].weight;
         int &cur_weight   = A[cur.x][cur.y].weight;

         if (neigh_weight > cur_weight + 1) {
            neigh_weight = cur_weight + 1;
            previous[neighs[i]] = cur;
            s.push(neighs[i]);
         } 

         if (neighs[i] == finish) {
            path_found = true;
            break;
         }
      }

      A[cur.x][cur.y].visited = true;
   }

#if 0
   struct printer {
      void operator () (const std::pair<point, point> &p) const 
      {
         std::cout << "Key: " << p.first << "; Val: " << p.second;
      }
   };
   std::for_each(previous.begin(), previous.end(), printer());
#else
   std::copy(previous.begin(), previous.end(), std::ostream_iterator<std::pair<point, point> >(std::cout));
#endif
}

void set_visited(bool val)
{
   for(int i = 0; i < N; ++i) {
      for(int j = 0; j < N; ++j) {
         A[i][j].visited = val;
      }
   }
}

void draw_shortest_path()
{
   set_visited(false);

   bool at_end = false;
   std::stack<point> q;
   q.push(finish);

   while(!at_end) {
      point cur = q.top();

      A[cur.x][cur.y].visited = true;

      std::vector<point> ns = neighbours(cur);

      for(size_t i = 0; i < ns.size(); ++i) {
         if (ns[i] == start) {
            at_end = true;
            break;
         }

         if (A[ns[i].x][ns[i].y].weight == A[cur.x][cur.y].weight - 1) {
            q.push(ns[i]);
            break;
         }
      }
   }

   while (!q.empty()) {
      point p = q.top();
      q.pop();

      A[p.x][p.y].data = '+';
   }
}

void write_answer()
{
   std::ofstream out("OUTPUT.TXT");

   if (out.is_open()) {
      if (path_found) {
         draw_shortest_path();

         out << "Yes" << std::endl;

         for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
               out << A[i][j].data;
            }
            out << std::endl;
         }
      } else {   
         out << "No";
      }
   }
}

int main()
{
   read_data();
   find_shortest_path();
   write_answer();

   return 0;
}
