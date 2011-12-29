#include <fstream>

#define INPUT "INPUT.TXT"
#define OUTPUT "OUTPUT.TXT"

int main()
{
    int N = 0;
    int K = 0;
    int M = 0;

    std::ifstream in(INPUT);

    if(in.is_open()) {
        in >> N >> M >> K;
        in.close();

        const int NO = -1;
        int ret = NO;

        if(N >= M) {
            ret = 1;
        } else if(N <= K) {
            ret = NO;
        } else {
            ret = (M-K-1)/(N-K)+1;
        }

        std::ofstream out(OUTPUT);

        if(out.is_open()) {
            if(ret == NO) {
                out << "NO";
            } else {
                out << ret;
            }
            out.flush();
            out.close();
        }
    }

    return 0;
}