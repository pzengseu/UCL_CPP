#include <iostream>
#include <bitset>
#include <stdio.h>
#include <stdlib.h>
#include "header_file/UCLCode.h"

using  namespace std;

int reloa(int a, string s)
//重载
{
    cout <<"a:" << a <<" s:" << s  << endl;
}
void reloa(string s, int a)
{
    cout <<"s:" << s <<" a:" << a << endl;
}


unsigned setbits(unsigned x, int p, int n, unsigned y)
{
    return (x & ((~0 << (p + 1)) | (~(~0 << (p + 1 - n))))) | ((y & ~(~0 << n)) << (p + 1 - n));
}

int test_set(void)
{
    unsigned i;
    unsigned j;
    unsigned k;
    int p;
    int n;

    for(i = 0; i < 3000; i += 511)
    {
        for(j = 0; j < 100; j += 37)
        {
            for(p = 0; p < 16; p++)
            {
                for(n = 1; n <= p + 1; n++)
                {
                    k = setbits(i, p, n, j);
                    printf("setbits(%u, %d, %d, %u) = %u\n", i, p, n, j, k);
                }
            }
        }
    }
    return 0;
}

/*code部分get set方法测试*/
void test_version()
{
    UCLCode code_test;
    // code_test.setUclCode();
    code_test.setVersion(0xbbfb);

    cout << "version:" << code_test.getVersion() << endl;
}
void test_code()
{
    UCLCode code_test;
    code_test.setVersion(7);
    code_test.setTypeOfMedia(9);
    code_test.setPrecedence(15);
    code_test.setFlag(13);
    code_test.setParseRule(0xfff1);//ff1有效
    code_test.setSourOfCont(0xfffffff1);//ffffff1有效
    code_test.setCategory(255);
    code_test.setSubCategory(257);//0x01有效
    code_test.setTopic(0xffffff1);
    code_test.setTypeOfContent(254);
    code_test.setCopyAndLeng(252);
    code_test.setSecuEnerLeveCode(251);
    code_test.setTimeStamp(0x3ffffffffffff);
    code_test.setSerialNumber(0x3fffff);
    code_test.setCheckCode(10101);

    code_test.codeDisplay(code_test);
}
void test_error()
{
    UCLCode code_test;
    code_test.setSerialNumber(0xffffff);
    code_test.setTopic(0xffffffff);
    code_test.setTimeStamp(0x3ffffffffffff);
    cout << "top:" << code_test.getTopic() << " ";
    cout << "ts:" << code_test.getTimeStamp() << " ";

    cout << "sn:" << code_test.getSerialNumber() << " ";
    cout << "rb:" << code_test.getReservedBytes() << " ";
    cout << "cc:" << code_test.getCheckCode() << " ";
}
int main() {
    /*
    reloa(1, "222");
    reloa("333", 2);
    std::cout << "Hello, World!" << std::endl;
    std::cout << "hh" << -5 % 8 <<"aa" <<std::endl;
    uint64_t a = 033;
    uint32_t b = 077777777;
    uint32_t c = (a | b);
    bitset<65> bits(c);
    cout << "cc" << c << "dd" << endl;
    cout << "bits" <<bits << endl;
    cout << "count" <<  .count() <<endl;
    //test_set();
    a=0;
    bitset<65> setb (setbits(a,63,8,0377 ));
    cout << "setb:" << setb;
    */
    //test_version();

    test_code();
    //test_error();
    return 0;
}