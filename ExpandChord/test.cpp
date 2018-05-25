
#include <iostream>
#include <string>
#include "tst.h"
void static test(const char*e)
{
    using namespace std;
    
    cout << string(e) << endl;
}

void test()
{

    test("hello");

}
