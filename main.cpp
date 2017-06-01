#include <iostream>
#include "test.h"
#include "testUCLCode.h"

using namespace std;

void testUCLCodeEasy()
{
    cout << "========== UCL Code test begin==========\n";
    test_code();
    test_unpack();
    cout << "========== UCL Code test end  ==========\n";
}

int main()
{
    testUCLCodeEasy();//UCLCode部分测试函数

    //测试UCL打包解包
    testEasy();
    //  cin.get();
    return 0;
}