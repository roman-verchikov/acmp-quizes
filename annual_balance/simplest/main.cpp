#include <fstream>

#define INPUT "INPUT.TXT"
#define OUTPUT "OUTPUT.TXT"

int main(int argc, char **argv) 
{
    const char *in_fname = INPUT;
    const char *out_fname = OUTPUT;

    long int a = 0;
    long int b = 0;

    std::ifstream ifs(in_fname);

    if(ifs.is_open()) {
        ifs >> a >> b;
        ifs.close();
    }

    std::ofstream ofs(out_fname);

    if(ofs.is_open()) {
        ofs << a+b;
        ofs.close();
    }

    return 0;   
}