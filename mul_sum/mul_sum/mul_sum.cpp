#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include <windows.h>

#define INPUT  "INPUT.TXT"
#define OUTPUT "OUTPUT.TXT"

template<class T>
bool ge(const T &n1, const T &n2) 
{
    return (n1 >= n2);
}

template<class T>
bool eq(const T &n1, const T &n2) 
{
    return (n1 == n2);
}

template<class T>
bool cmp_arrays(const std::vector<T> &ar1, 
                const std::vector<T> &ar2, 
                bool (*f)(const T&, const T&))
{
    typedef std::vector<T>::const_reverse_iterator RIT;

    for(RIT i = ar1.rbegin(), j = ar2.rbegin();
        i != ar1.rend() && j != ar2.rend(); ++i, ++j) {
            if(!f(*i, *j)) return false;
    }

    return true;
}

class big_num_t {
public:
    big_num_t(int n = 0) 
    {
        do {
            m_int_data.push_back(n % BN_BASE);
        } while(n /= BN_BASE);
    }

    big_num_t(const char *file) 
    {
        from_file(file);
    }

    void from_file(const char *file)
    {
        std::string   in_data;
        std::ifstream in(file);

        if(in.is_open()) {
            in >> in_data;
            in.close();

            m_int_data.clear();

            int data_left = static_cast<int>(in_data.length());

            do {
                int data_start = (data_left >= BN_NUM_DIGITS) ? data_left-BN_NUM_DIGITS : 0;
                int num_bytes  = (data_left >= BN_NUM_DIGITS) ? BN_NUM_DIGITS : data_left;

                std::stringstream ost(in_data.substr(data_start, num_bytes));                

                m_int_data.push_back(0);
                ost >> m_int_data.back();

            } while((data_left -= BN_NUM_DIGITS) > 0);
        }
    }

    big_num_t digits_product(void) const 
    {
        big_num_t res(1);

        for(size_t i = 0; i < m_int_data.size(); i++) {
            res *= m_int_data[i];
        }

        return res;
    }

    big_num_t& operator += (const big_num_t &n)
    {        
        const size_t greater_len = max(n.m_int_data.size(), m_int_data.size());
        internal_t carry = 0;

        // add required space to hold sum
        if(n.m_int_data.size() != m_int_data.size()) {
            size_t to_add = greater_len - m_int_data.size();
            for(size_t i = 0; i < to_add; i++) {
                m_int_data.push_back(0);
            }
        }

        for(size_t i = 0; i < greater_len; i++) {
            internal_t lhs = m_int_data[i];
            internal_t rhs = (n.m_int_data.size() > i) ? n.m_int_data[i] : 0;

            int partial_sum = (lhs + rhs + carry);

            m_int_data[i] = partial_sum % BN_BASE;
            carry = partial_sum / BN_BASE;
        }

        if(carry) {
            m_int_data.push_back(carry);
        }

        return (*this);
    }

    big_num_t& operator ++ (int)
    {
        return ((*this) += 1);
    }


    big_num_t& operator ++ (void)
    {
        return ((*this) += 1);
    }

    big_num_t& operator *= (const big_num_t &n)
    {
        if((n.m_int_data[0] == 0 && n.m_int_data.size() == 1) ||
            (m_int_data[0] == 0 && m_int_data.size() == 1)) {
                m_int_data.clear();
                m_int_data.push_back(0);
                return *this;
        }

        typedef std::vector<internal_t> AR;
        typedef std::vector<internal_t>::const_iterator CIT;
        typedef std::vector<internal_t>::iterator IT;

        const AR &lhs = this->m_int_data;
        const AR &rhs = n.m_int_data;

        const size_t l_size = m_int_data.size();
        const size_t r_size = n.m_int_data.size();

        AR local_ret(l_size + r_size, 0);
        int i = 0;

        for(CIT lhs_it = lhs.begin(); lhs_it != lhs.end(); ++lhs_it, i++) {
            int carry = 0;
            IT local_ret_it = local_ret.begin() + i;

            for(CIT rhs_it = rhs.begin(); rhs_it != rhs.end(); ++rhs_it) {
                int product = (*local_ret_it) + (*lhs_it)*(*rhs_it) + carry;

                *local_ret_it = product % BN_BASE;
                carry = product / BN_BASE;

                local_ret_it++;
            }

            if(carry) {
                *local_ret_it = carry;
            }
        }

        if(local_ret.back() == 0) {
            m_int_data.assign(local_ret.begin(), local_ret.end()-1);
        } else {
            m_int_data = local_ret;
        }

        return (*this);
    }

    bool operator < (const big_num_t &n) const 
    {
        if(this->m_int_data.size() == n.m_int_data.size()) {
            if(cmp_arrays(this->m_int_data, n.m_int_data, ge<internal_t>)) {
                return false;
            }
        } else if(this->m_int_data.size() > n.m_int_data.size()) {
            return false;
        } 

        return true;
    }

    bool operator != (const big_num_t &n) const 
    {
        if(this->m_int_data.size() == n.m_int_data.size()) {
            if(cmp_arrays(this->m_int_data, n.m_int_data, eq<internal_t>)) {
                return false;
            } 
        } 

        return true;
    }

    bool operator == (const big_num_t &n) const
    {
        return (!(*this != n));
    }

    bool operator <= (const big_num_t &n) const 
    {
        return ( ((*this) < n) || ((*this) == n));
    }

    void save_to(const char *file) const
    {
        std::ofstream out(file);

        if(out.is_open()) {
            typedef std::vector<internal_t>::const_reverse_iterator IT;

            for(IT it = m_int_data.rbegin(); it != m_int_data.rend(); ++it) {
                out << *it;
            }

            out.flush();
            out.close();
        }
    }

private:
    enum {
        BN_BASE = 1000,
        BN_NUM_DIGITS = 4
    };

    typedef int internal_t;

    std::vector<internal_t> m_int_data;
};

big_num_t factorial(const big_num_t &bn)
{
    big_num_t res(1);

    for(big_num_t i = 2; i <= bn; ++i) {
        res *= i;
    }

    return res;
}

void sum_of_products(const big_num_t &bn)
{
    
}

int main()
{
    big_num_t n(INPUT);

    DWORD start = ::GetTickCount();
    factorial(n);
    DWORD end = ::GetTickCount();

    std::ofstream out(OUTPUT);
    if(out.is_open()) {
        out << end - start;
    }

    return 0;
}