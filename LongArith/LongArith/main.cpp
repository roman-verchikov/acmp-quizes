#include <iostream>
#include "LongInt.h"

void factorial(const int N)
{
    TLongInt res(1);

    for(int i = 1; i <= N; i++) {
        res *= i;
    }

    res.print();
    std::cout << std::endl;
}

int main()
{
    std::string fname = "long_int.txt";



    //TLongInt m(10);

    //TLongInt res = n*m;
    //res.print();
    //std::cout << std::endl;

    //for(int i = 0; i < 10; i++) {
    //    res *= 10;
    //    res.print();
    //    std::cout << std::endl;
    //}

    factorial(13);

    return 0;
}