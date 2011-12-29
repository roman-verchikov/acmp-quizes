#ifndef __LONGINT_H__
#define __LONGINT_H__

#include <vector>
#include <string>

class TLongInt {
public:
    TLongInt(int val = 0);
    TLongInt(const TLongInt &n);
    ~TLongInt();
    TLongInt(const std::string &fname);

    void readFrom(const std::string &fname);
    void writeTo(const std::string &fname)const;

    void print(void)const;

    bool operator != (const TLongInt &rhs)const;
    bool operator == (const TLongInt &rhs)const;
    bool operator <  (const TLongInt &rhs)const;
    bool operator >  (const TLongInt &rhs)const;
    bool operator <= (const TLongInt &rhs)const;
    bool operator >= (const TLongInt &rhs)const;

    TLongInt  operator +  (const TLongInt &rhs)const;
    TLongInt  operator -  (const TLongInt &rhs)const;
    TLongInt &operator += (const TLongInt &rhs);
    TLongInt &operator -= (const TLongInt &rhs);

    TLongInt  operator *  (const TLongInt &rhs)const;
    TLongInt  operator /  (const TLongInt &rhs)const;
    TLongInt &operator *= (const TLongInt &rhs);
    TLongInt &operator /= (const TLongInt &rhs);

private:
    typedef unsigned char type_t;

    std::vector<type_t> m_val;
    void expand(const size_t &rhs_size);

    enum {
        RADIX = 10,
        CHAR_TO_INT_FACTOR = 48
    };

    enum {
        POSITIVE,
        NEGATIVE,
        MAX_VAL
    } m_valType;
};

#endif //__LONGINT_H__