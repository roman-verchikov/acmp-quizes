#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#define INPUT "INPUT.TXT"
#define OUTPUT "OUTPUT.TXT"

typedef long int uint_t;

uint_t sum2(const uint_t &max) 
{
    return (1 + max)/2.0*max;
}

uint_t sum1(const uint_t &max) 
{
    if(max < 0) {
        return (1 - abs(max))/2.0 * abs(max);
    } else {
        return (1 + max)/2.0*max;
    }
}

uint_t sum3(const uint_t &n)
{
    uint_t sum = 0;

    if(n <= 0) {
        for(int i = 1; i >= n; i--) {
            sum += i;
        }
    } else {
        sum = sum2(n);
    }

    return sum;
}

void calc_sum(const uint_t &n) 
{
    std::ofstream ofs(OUTPUT);
    uint_t res = 0;

    if(ofs.is_open()) {
        res = sum3(n);
        ofs << res;
        ofs.close();
    }
}

bool get_input(uint_t &n)
{
    bool ret = false;

    std::ifstream ifs(INPUT);

    if(ifs.is_open()) {
        ifs >> n;
        ifs.close();
        ret = true;
    }

    return ret;
}

int main(int argc, char **argv)
{
    uint_t n = 0;

    if(get_input(n)) {
        calc_sum(n);
    }

    return 0;
}