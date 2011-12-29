#include "LongInt.h"

#include <fstream>
#include <iostream>
#include <valarray>
#include <sstream>

TLongInt::TLongInt(int val)
{
    while(val != 0) {
        m_val.push_back(val%RADIX);
        val /= RADIX;
    }

    m_valType = (val < 0) ? NEGATIVE : POSITIVE;
}

TLongInt::TLongInt(const TLongInt &n)
{
    this->m_val = n.m_val;
}

TLongInt::TLongInt(const std::string &fname)
{
    readFrom(fname);
}

TLongInt::~TLongInt()
{}

void TLongInt::readFrom(const std::string &fname)
{
    std::ifstream ifs(fname.c_str());
    std::string buf;

    if(ifs.is_open()) {
        ifs >> buf;

        ifs.close();

        m_valType = (buf[0] == '-') ? NEGATIVE : POSITIVE;
        int start = (buf[0] == '-') ? 1 : 0;

        for(size_t i = buf.length(); i != start; i--) {
            m_val.push_back(buf[i-1] - CHAR_TO_INT_FACTOR);
        }
    }
}

void TLongInt::writeTo(const std::string &fname)const
{
    std::ofstream ofs(fname.c_str());

    if(ofs.is_open()) {
        ofs.close();
    }
}

bool TLongInt::operator != (const TLongInt &rhs)const
{
   return !(*this == rhs);
}

bool TLongInt::operator == (const TLongInt &rhs)const
{
    bool ret = false;

    if(rhs.m_val.size() == this->m_val.size() && rhs.m_valType == this->m_valType) {
        int cnt = 0;

        for(size_t i = 0; i < this->m_val.size(); i++) {
            if(rhs.m_val[i] != this->m_val[i]) break;
            else cnt++;
        }

        if(cnt == m_val.size()) ret = true;
    }

    return ret; 
}

bool TLongInt::operator <  (const TLongInt &rhs)const
{
    // TODO: Add signed comparison

    if(this->m_val.size() < rhs.m_val.size()) return true;
    else if (this->m_val.size() > rhs.m_val.size()) return false;
    else { // sizes are equal
        for(size_t i = m_val.size(); i != 0; i--) {
            if(this->m_val[i-1] < rhs.m_val[i-1]) return true;
        }
    }

    return false;
}

bool TLongInt::operator >  (const TLongInt &rhs)const
{
    return ((*this != rhs) && !(*this < rhs));
}

bool TLongInt::operator <= (const TLongInt &rhs)const
{
    return ((*this < rhs) || (*this == rhs));
}

bool TLongInt::operator >= (const TLongInt &rhs)const
{
    return ((*this > rhs) || (*this == rhs));
}

TLongInt  TLongInt::operator +  (const TLongInt &rhs)const
{
    TLongInt ret = *this;
    return ret += rhs;
}

TLongInt  TLongInt::operator -  (const TLongInt &rhs)const
{
    TLongInt ret = *this;
    return ret -= rhs;
}

TLongInt &TLongInt::operator += (const TLongInt &rhs)
{
    expand(rhs.m_val.size());

    type_t over = 0;
    for(size_t i = 0; i < this->m_val.size(); i++) {
        type_t rh_value = (i >= rhs.m_val.size()) ? 0 : rhs.m_val[i];
        type_t sum = (this->m_val[i] + rh_value + over);
        this->m_val[i] = sum % RADIX;        
        over = sum / RADIX;
    }

    if(over) m_val.push_back(over);

    return *this;
}

TLongInt &TLongInt::operator -= (const TLongInt &rhs)
{
    return *this;

}

TLongInt  TLongInt::operator *  (const TLongInt &rhs)const
{
    TLongInt ret = *this;
    return ret *= rhs;

}

TLongInt  TLongInt::operator /  (const TLongInt &rhs)const
{
    TLongInt ret = *this;
    return ret *= rhs;

}

TLongInt &TLongInt::operator *= (const TLongInt &rhs)
{
    type_t over = 0;
    std::vector<type_t> tmp(this->m_val.size()+rhs.m_val.size(), 0);

    for(size_t i = 0; i < rhs.m_val.size(); i++) {
        for(size_t j = 0; j < this->m_val.size(); j++) {
            type_t tmp_sum = (tmp[j+i*(rhs.m_val.size()-1)] + rhs.m_val[i] * this->m_val[j] + over);
            tmp[j+i*(rhs.m_val.size()-1)] = (tmp_sum) % RADIX;
            over = tmp_sum / RADIX;
        }        

        tmp[(this->m_val.size()-1)+i*(rhs.m_val.size()-1)] = over;
        over = 0;
    }

    if(over > 0) tmp[tmp.size()-1] = over;

    // removes zeros int the beggining of value
    for(size_t i = tmp.size()-1; i != 0 && tmp[i] == 0; i--) {
        tmp.erase(tmp.begin()+i);
    }

    m_val = tmp;

    return *this;
}

TLongInt &TLongInt::operator /= (const TLongInt &rhs)
{
    return *this;

}

void TLongInt::print(void)const
{
    for(size_t i = m_val.size(); i != 0; i--) {
        std::cout << static_cast<int>(m_val[i-1]);
    }
}


void TLongInt::expand(const size_t &rhs_size)
{
    int diff = static_cast<int>(this->m_val.size()) - static_cast<int>(rhs_size);
    if(diff < 0) {
        for(int i = 0; i < diff; i++) {
            m_val.push_back(0);
        }
    }
}
