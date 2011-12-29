#include <iostream> 
#include <cassert> 
#include <functional> 
#include <vector> 
#include <algorithm> 

using namespace std;

// has exact type of clone() we need
class A {
    public:
        A() : a__(0) {}

        A* clone() const 
        {
            return a__;
        }

    private:
        A *a__;
};

// doesn't have clone() 
class B {
public:
    B() {}
};


class D : public A
{

};

template <class T>
class HasClone {
public:
    HasClone() {
        constraints();
    }

private:
    static void constraints()
    {
        T* (T::*test)() const = &T::clone;
        test;
    }
};

// Checks whether T has T* T::clone() const function defined.
template <class T>
class C : HasClone<T> {
    public:
        C() { cout << "C()" << endl; }
        ~C() { cout << "~C()" << endl; }
};

int main()
{
    C<A> ca;
    C<D> cd;
    //C<B> cb;

    return 0;
}

