#include <fstream>
#include <stdio.h>

using namespace std;

// Greatest common divisor
int gcd(int m, int n)
{
    int _gcd = 1;
    int _m = min(m,n);

    for(int i = 1; i <= _m; ++i) { 
        if ( !(m % i) && !(n%i) ) {
            _gcd = i;
        }
    }

    return _gcd;
}

// Least common multiple
int lcm(int m, int n) 
{
    return abs(m * n) / gcd(m, n);
}

int main() 
{
    ifstream in("INPUT.TXT");

    if(in.is_open()) {
        int m, n;

        in >> m >> n;

        in.close();

        ofstream out("OUTPUT.TXT");
        if(out.is_open()) {
            out << lcm(m,n);
            out.flush();
            out.close();
        }
    }

    return 0;
}
