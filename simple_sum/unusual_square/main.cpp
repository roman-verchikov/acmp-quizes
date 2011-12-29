#include <fstream>
#include <sstream>
#include <string>

std::string calc_square(int val)
{
    std::string tail = "25";
    std::ostringstream head;

    int head_n = val/10;

    if(head_n > 0) {
        int sq = head_n * (head_n+1); 
        head << sq;
    }

    return head.str() + tail;
}

int main(int argc, char **argv) 
{
    const char *in_fname = "INPUT.TXT";
    const char *out_fname = "OUTPUT.TXT";

    std::ifstream ifs(in_fname);
    int s_val = 0;

    if(ifs.is_open()) {
        ifs >> s_val;
        ifs.close();
    }

    std::ofstream ofs(out_fname);

    if(ofs.is_open()) {
        ofs << calc_square(s_val);
    }
}