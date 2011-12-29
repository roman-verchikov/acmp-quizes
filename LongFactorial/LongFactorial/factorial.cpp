#include <fstream>
#include <iostream>
#include <vector>

#define INPUT "INPUT.TXT"
#define OUTPUT "OUTPUT.TXT"

class LongInt {
public:
    LongInt(int n = 0) {
        fromInt(n);
    }

    LongInt &operator *= (const LongInt &rhs) {
        std::vector<type_t> local_ret(this->len() + rhs.len(), 0);

        const int l_size = this->m_val.size();
        const int r_size = rhs.m_val.size();

        int over = 0;

        for(int i = 0; i < r_size; i++) {
            for(int j = 0; j < l_size; j++) {
                int local_ret_index = i*(r_size-1) + j;
                type_t partial_sum = local_ret[local_ret_index] + m_val[j] * rhs.m_val[i] + over;
                
                local_ret[local_ret_index] = partial_sum % RADIX;

                over = partial_sum / RADIX;                
            }
            
            if(over > 0) {
                local_ret[i*(r_size-1) + l_size] = over;
            }

            over = 0;
        }


        for(size_t i = local_ret.size(); i != 0 && local_ret[i-1] == 0; i--) {
            local_ret.erase(local_ret.begin() + i-1);
        }

        m_val = local_ret;

        return *this;
    }

    size_t len(void)const {
        return m_val.size();
    }

    void fromInt(int n) 
    {
        while(n) {
            m_val.push_back(n%RADIX);
            n /= RADIX;
        }
    }

    void saveTo(const char *fname) const {
        std::ofstream out(fname);

        if(out.is_open()) {
            if(m_val.size()) out << m_val[m_val.size()-1];

            for(size_t i = m_val.size()-1; i != 0; i--) {
                int tmp = m_val[i-1];
                int tmp_radix = RADIX/10;
                while(tmp_radix && ((tmp /= tmp_radix) == 0)) {                                
                    tmp_radix /= 10;
                    out << 0;
                }

                out << m_val[i-1];
            }
            out.close();
        }
    }

    void print(void) const {
        for(size_t i = m_val.size(); i != 0; i++) {
            std::cout << m_val[i-1];
        }
         std::cout << std::endl;
    }

private:
    typedef int type_t;
    enum {
        RADIX = 10000
    };
    std::vector<type_t> m_val;
};

void factorial(int n)
{
    LongInt fact = 1;

    for(int i = 2; i <= n; i++) {
        fact *= i;
    }

    fact.saveTo(OUTPUT);
}

int main()
{
    std::ifstream in(INPUT);
    if(in.is_open()) {
        int n = 0;

        in >> n;
        in.close();

        factorial(n);
    }

    return 0;
}