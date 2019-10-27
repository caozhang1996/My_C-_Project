#include <iostream>
#include "complex.h"
using namespace std;

/*
    "<<"操作符重载
    complex c1(2, 1);
    cout << conj(c1);   => (2, -1)
    cout << c << conj(c1);  => (2, 1)(2, -1)
*/
template<typename T>
ostream& operator << (ostream& os, const complex<T>& x)    //cout是ostream类的对象
{
    return os << '(' << real(x) << ',' << imag(x) << ')';
}

int main(int argc, char const *argv[])
{
    complex<int> c1(2, 1);
    complex<int> c2(3, 4);
    
    cout << c1 << endl;
    cout << c2 << endl;
    
    cout << c1+c2 << endl;
    cout << c1-c2 << endl;
    cout << c1*c2 << endl;
    cout << c1 / 2 << endl;
    
    cout << conj(c1) << endl;
    cout << norm(c1) << endl;
    cout << polar(10, 4) << endl;
    
    cout << (c1 += c2) << endl;
    
    cout << (c1 == c2) << endl;
    cout << (c1 != c2) << endl;
    cout << +c2 << endl;
    cout << -c2 << endl;
    
    cout << (c2 - 2) << endl;
    cout << (5 + c2) << endl;

    cout << "\n\n-------for double--------\n";
    complex<double> c3(2.52, 3.41);
    complex<double> c4(4.1, 7.2);

    cout << c3 + c4<< endl;
    cout << c3 * c4<< endl;
    cout << c3 / 2.0 << endl;
}
