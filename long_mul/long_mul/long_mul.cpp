#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

#define INPUT "INPUT.TXT"
#define OUTPUT "OUTPUT.TXT"

class LongInt {
public:
    LongInt(int n = 0) {
        fromInt(n);
    }

    LongInt(const std::string &s) {
        fromString(s.c_str(), s.length());
    }

    void fromString(const char *n, size_t len)
    {
        m_val.clear();

        while(static_cast<int>(len) > 0) {
            const size_t x = (len > RADIX_POW) ? 0 : RADIX_POW - len;
            const char *start_pos = n + ((RADIX_POW < len) ? len - RADIX_POW : 0);
            const size_t size = RADIX_POW - x;

            std::string sub_value(start_pos, size);
            std::istringstream ist(sub_value);
            type_t tmp = 0;

            ist >> tmp;
            m_val.push_back(tmp);

            len -= RADIX_POW;
        }
    }

    LongInt &operator *= (const LongInt &rhs) {
        if(rhs.m_val[0] == 0 && rhs.m_val.size() == 1 ||
            m_val[0] == 0 && m_val.size() == 1) {
                m_val.clear();
                m_val.push_back(0);
                return *this;
        }

        const int l_size = this->m_val.size();
        const int r_size = rhs.m_val.size();

        std::vector<type_t> local_ret(l_size + r_size, 0);

        for(int i = 0; i < r_size; i++) {
            int over = 0;

            for(int j = 0; j < l_size; j++) {
                int local_ret_index = i + j;
                type_t partial_sum = local_ret[local_ret_index] + m_val[j] * rhs.m_val[i] + over;
                
                local_ret[local_ret_index] = partial_sum % RADIX;

                over = partial_sum / RADIX;                
            }
            
            if(over > 0) {
                local_ret[i + l_size] = over;
            }
        }


        for(size_t i = local_ret.size(); i != 0 && local_ret[i-1] == 0; i--) {
            local_ret.erase(local_ret.begin() + i-1);
        }

        m_val = local_ret;

        return *this;
    }

    bool operator == (const int &n) const {
        return *this == LongInt(n);
    }

    bool operator != (const LongInt &rhs) const {
        if(rhs.m_val.size() != this->m_val.size()) {
            return true;
        } 
            
        for(size_t i = 0; i < m_val.size(); i++) {
            if(this->m_val[i] != rhs.m_val[i]) {
                return true;
            }
        }
        
        return false;
    }

    bool operator == (const LongInt &rhs) const {
        return !(*this != rhs);
    }

    size_t len(void)const {
        return m_val.size();
    }

    void fromInt(int n) 
    {
        do {
            m_val.push_back(n%RADIX);
            n /= RADIX;
        } while(n);
    }

    void saveTo(const char *fname) const {
        std::ofstream out(fname);

        if(out.is_open()) {
            out << toString();
            out.close();
        }
    }

    std::string toString(void) const {
        std::ostringstream ret;

        if(m_val.size()) ret << m_val[m_val.size()-1];

        // adds neccessary zeroes before value
        for(size_t i = m_val.size()-1; i != 0; i--) {
            int tmp = m_val[i-1];
            int tmp_radix = RADIX;
            while(((tmp_radix /= 10) != 0) && ((tmp / tmp_radix) == 0)) {                                
                ret << 0;
            }

            if(m_val[i-1] != 0) {
                ret << m_val[i-1];
            }
        }

        return ret.str();
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
        RADIX = 10000,
        RADIX_POW = 4
    };
    std::vector<type_t> m_val;
};



int main()
{
#if 1
    std::ifstream in(INPUT);
    if(in.is_open()) {
        std::string a;
        std::string b;

        in >> a;
        in >> b;

        in.close();

        LongInt x1(a);
        LongInt x2(b);

        x1 *= x2;

        x1.saveTo(OUTPUT);
    }

#else

    const int N_MAX = 10000;

    std::ofstream log("LOG.log");
    for(int i = 0; i < N_MAX; i++) {
        for(int j = i; j < N_MAX; j++) {
            LongInt a(i);
            LongInt b(j);

            if((a *= b) != (i*j)) {
                std::cout << i << "*" << j << " = " << a.toString() << std::endl;
            } else {
                log << i << "*" << j << "  OK" << std::endl;
            }
        }
    }

#endif

    return 0;
}
