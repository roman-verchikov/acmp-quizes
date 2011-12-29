#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#define INPUT "INPUT.TXT"
#define OUTPUT "OUTPUT.TXT"


class LongInt {
public:
    LongInt(int n = 0) 
    {
        fromInt(n);
    }
    
    void fromFile(const char *fname) 
    {
        std::ifstream in(fname);

        if(in.is_open()) {
            std::string buf;

            in >> buf;
            in.close();

            fromString(buf.c_str(), buf.length());
        }
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

    void fromInt(int n) 
    {
        while(n) {
            m_val.push_back(n % RADIX);
            n /= RADIX;
        }
    }

    void saveTo(const char *fname) 
    {
        std::ofstream out(fname);

        if(out.is_open()) {
            out << m_val.back();

            for(size_t i = m_val.size()-1; i != 0; i--) {
                type_t value = m_val[i-1];
                type_t local_radix = RADIX/10;

                while( (value / local_radix == 0) && ((local_radix /= 10) > 0)) {
                    out << 0;
                }

                out << value;
            }

            out.close();
        }
    }

    bool operator == (const LongInt &rhs) const 
    {
        if(rhs.m_val.size() != m_val.size()) return false;
        
        for(size_t i = 0; i < m_val.size(); i++) {
            if(m_val[i] != rhs.m_val[i]) return false;
        }

        return true;
    }

    bool operator != (const LongInt &rhs) const 
    {
        return !(*this == rhs);
    }

    bool operator < (const LongInt &rhs) const 
    {
        if(this->m_val.size() < rhs.m_val.size()) return true;
        if(this->m_val.size() > rhs.m_val.size()) return false;

        for(size_t i = m_val.size(); i != 0; i--) {
            if(m_val[i-1] < rhs.m_val[i-1]) return true;
        }

        return false;
    }

    bool operator > (const LongInt &rhs) const 
    {
        return !(*this < rhs) && (*this != rhs);
    }

    bool operator <= (const LongInt &rhs) const 
    {
        return (*this < rhs) || (*this == rhs);
    }

    bool operator >= (const LongInt &rhs) const 
    {
        return (*this > rhs) || (*this == rhs);
    }

    LongInt operator + (const LongInt &rhs) const
    {
        LongInt ret = *this;
        return ret += rhs;
    }

    LongInt &operator += (const LongInt &rhs) 
    {
        const int size = std::max(this->m_val.size(), rhs.m_val.size());

        type_t over = 0;

        for(int i = 0; i < size; i++) {
            type_t r_val = 0;
            if(this->m_val.size() <= i) {
                m_val.push_back(0);
            }
            if(rhs.m_val.size() > i) {
                r_val = rhs.m_val[i];
            }

            type_t tmp_sum = m_val[i] + r_val + over;

            m_val[i] = tmp_sum % RADIX;

            over = tmp_sum / RADIX;
        }
        
        if(over > 0) m_val.push_back(over);

        // remove leading zeroes
        
        for(size_t i = m_val.size(); 
            (m_val.size() != 1) && 
            (i != 0) && 
            (m_val[i-1] == 0); 
            i--) 
        {
            m_val.erase(m_val.begin()+i-1);
        }

        return *this;
    }

private:
    enum {
        RADIX = 1000000000,   // 10 ^ 8
        RADIX_POW = 9
    };

    typedef int type_t;
    std::vector<type_t> m_val;
};


int main()
{
#if 0
    std::ifstream in(INPUT);

    if(in.is_open()) {
        std::string x;
        std::string y;

        in >> x >> y;

        in.close();

        LongInt a;
        LongInt b;

        a.fromString(x.c_str(), x.length());
        b.fromString(y.c_str(), y.length());

        a+=b;
        a.saveTo(OUTPUT);
    }
#else

    std::ifstream in(INPUT);

    if(in.is_open()) {
        std::vector<std::string> input(3);

        in >> input[0] >> input[1] >> input[2];

        in.close();

        std::vector<LongInt> values(3);

        for(size_t i = 0; i < values.size(); i++) {
            values[i].fromString(input[i].c_str(), input[i].length());
        }

        LongInt max = values[0];
        for(size_t i = 1; i < values.size(); i++) {
            if(values[i] > max) max = values[i];
        }
        
        max.saveTo(OUTPUT);
    }

#endif

    return 0;
}