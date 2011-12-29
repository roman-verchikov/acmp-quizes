#include <fstream>

#define INPUT "INPUT.TXT"
#define OUTPUT "OUTPUT.TXT"

#define RANGE_START -100
#define RANGE_END    100

#define IS_CUBIC_EQUATION_ROOT(A, B, C, D, x) \
    ( ((x == 0) ? (D) : ( (A)*(x)*(x) + (B)*(x) + (C) + (1.0*(D))/(x) ) ) == 0)

int main(void)
{
    int A = 0;
    int B = 0;
    int C = 0;
    int D = 0;

    std::ifstream in(INPUT);
    std::ofstream out(OUTPUT);

    if(in.is_open() && out.is_open()) {
        in >> A >> B >> C >> D;

        for(int x = RANGE_START; x < RANGE_END; ++x) {
            if(IS_CUBIC_EQUATION_ROOT(A, B, C, D, x)) {
                out << x << " ";
            }
        }
    }

    return 0;
}