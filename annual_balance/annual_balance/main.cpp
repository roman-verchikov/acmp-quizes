#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#define INPUT_FILE "INPUT.TXT"
#define OUTPUT_FILE "OUTPUT.TXT"


bool get_input(std::string &a, std::string &b);
void annual_balance(std::string &a, std::string &b);
void sort_max(std::string &s);
void sort_min(std::string &s);

int main(int argc, char **argv)
{
    std::string a;
    std::string b;

    if(get_input(a,b)) {
        annual_balance(a, b);
    }

    return 0;
}

bool get_input(std::string &a, std::string &b)
{
    const char *fname = INPUT_FILE;
    bool ret = false;

    std::ifstream ifs(fname);

    if(ifs.is_open()) {
        ifs >> a;
        ifs >> b;
        ifs.close();
        ret = true;
    }

    return ret;
}


void sort_max(std::string &s)
{
    for(int i = 0; i < s.size(); i++) {
        for(int j = i+1; j < s.size(); j++) {
            if(s[i] <= s[j] && s[i] != '-') std::swap(s[i], s[j]);            
        }
    }
}

void sort_min(std::string &s)
{
    for(int i = 0; i < s.size(); i++) {
        for(int j = i+1; j < s.size(); j++) {
            if(s[i] >= s[j]) std::swap(s[i], s[j]);
        }
    }

    if(s[0] == '0') {
        char min_val = '9';
        int min_val_pos = 1;

        for(int i = 1; i < s.size(); i++) {
            if(s[i] <= min_val && s[i] != '0') {
                min_val = s[i];
                min_val_pos = i;
            }
        }

        std::swap(s[0], s[min_val_pos]);
    }
}

void annual_balance(std::string &a, std::string &b)
{
    if(a[0] == '-') {
        sort_min(a);
    } else {
        sort_max(a);
    }

    if(b[0] == '-') {
        sort_max(b);
    } else {
        sort_min(b);
    }

    std::istringstream val1(a);
    std::istringstream val2(b);

    long int n_a = 0;
    long int n_b = 0;

    val1 >> n_a;
    val2 >> n_b;

    const char *out_fname = OUTPUT_FILE;
    std::ofstream ofs(out_fname);

    if(ofs.is_open()) {
        ofs << n_a - n_b;
    }
}