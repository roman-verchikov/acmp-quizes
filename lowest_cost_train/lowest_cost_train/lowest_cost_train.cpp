#include <fstream>
#include <iterator>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

typedef unsigned int type_t;

#define INPUT "INPUT.TXT"
#define OUTPUT "OUTPUT.TXT"

int main()
{
    size_t N = 0;
    type_t min_cost = numeric_limits<type_t>::max(); 
    queue<type_t> distances;

    ifstream in(INPUT);

    if(in.is_open())
    {
        type_t compare_with = numeric_limits<type_t>::max();

        in >> N;

        while (in)
        {
        }
    }    

    return 0;
}