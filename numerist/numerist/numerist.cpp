#include <fstream>
#include <string>

#define INPUT "INPUT.TXT"
#define OUTPUT "OUTPUT.TXT"

class numerist {
public:
    numerist(const char *in_file = INPUT) 
    : num_conversions(0)      
    {
        get_data_from_file(in_file);
    }

    void get_data_from_file(const char *in_file)
    {
        std::ifstream in(INPUT);

        if(in.is_open()) {
            in >> result;
            in.close();
        } 
    }

    void solve(void)
    {
        while(result.length() != 1) {
            std::string tmp = "0";

            for(size_t i = 0; i < result.length(); i++) {
                tmp = sum(tmp, result[i]);
            }

            result = tmp;

            num_conversions++;
        }
    }

    std::string& sum(std::string &s, char c)
    {
        std::string &res = s;
        size_t i = res.length()-1;
        char over = 0;

        do {
            char _sum = (res[i] - ZERO) + (c - ZERO);
            char last = _sum % BASE + ZERO;

            over = _sum / BASE;
            c = over + ZERO;
        
            res[i--] = last;
 
            if(i == -1 && over) {
                res.insert((size_t)0, (size_t)1, (char)(over + ZERO));                
                break;
            }
        } while(over); 

        return res;
    }

    void save_solution(const char *out_file = OUTPUT)
    {
        std::ofstream out(out_file);

        if(out.is_open()) {
            out << result << " " << num_conversions;
            out.close();
        }
    }

private:
    std::string result;
    int num_conversions;

    enum {
        BASE = 10,
        ZERO = '0'
    };
};

int main()
{
    numerist obj;

    obj.solve();
    obj.save_solution();

    return 0;
}