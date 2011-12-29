#include <fstream>
#include <string>

#define INPUT "INPUT.TXT"
#define OUTPUT "OUTPUT.TXT"

int main(int argc, char **argv)
{
    std::ifstream in(INPUT);

    if(in.is_open()) {
        char c1, c2, dash;
        int n1, n2;

        in >> c1 >> n1 >> dash >> c2 >> n2;

        std::ofstream out(OUTPUT);

        if(out.is_open()) {
            if(c1 < 'A' || c1 > 'H' || c2 < 'A' || c2 > 'H' || 
               n1 > 8 || n2 > 8 || n1 < 1 || n2 < 1 || dash != '-') {
                out << "ERROR";
            } else {
                if( ((abs(c1 - c2) == 2) && (abs(n1 - n2) == 1)) ||
                    ((abs(c1 - c2) == 1) && (abs(n1 - n2) == 2))) {
                    out << "YES";
                } else {
                    out << "NO";
                }
            }

            out.close();
        }
        in.close();
    }

    return 0;
}