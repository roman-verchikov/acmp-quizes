#include <fstream>
#include <vector>
#include <stack>
#include <list>

using namespace std;

int N, M;

struct node {
   list<node*> others;
   int index;
};

vector<node> graph;

void read_input()
{
   ifstream in("INPUT.TXT");

   if (in.is_open()) {
      in >> N >> M;


   }
}

int main()
{
   read_input();
   solve();
   save_answer();

   return 0;
}
