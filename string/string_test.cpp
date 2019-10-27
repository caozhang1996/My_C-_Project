#include <iostream>
#include "string.h"
using namespace std;

ostream& operator << (ostream& os, const String& str)
{
    return os << str.get_c_str();
}

int main(int argc, char const *argv[])
{
    String s1;
    String s2("hello");
    s1 = s2;
    cout << s1 << endl;
    cout << s2 << endl;
    return 0;
}
