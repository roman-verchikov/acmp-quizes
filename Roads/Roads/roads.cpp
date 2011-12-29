#include <fstream>

#define INPUT "INPUT.TXT"
#define OUTPUT "OUTPUT.TXT"

int main()
{
    std::ifstream in(INPUT);

    if(in.is_open()) {
        size_t N = 0;
        size_t cnt = 0;
        int val = 0;

        in >> N;

        for(size_t i = 0; i < N*N; i++) {
            in >> val;
            if(val == 1) cnt++;
        }

        in.close();

        std::ofstream out(OUTPUT);
        if(out.is_open()) {
            out << cnt/2;
            out.close();
        }
    }

    return 0;    
}