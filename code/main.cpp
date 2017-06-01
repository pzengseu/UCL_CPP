#include <iostream>
#include <bitset>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include "header_file/UCLCode.h"

using  namespace std;

const string sline(100,'*');

//以16进制形式输出Code
void showCodeHex(string s)
{
    cout << "UCLCode:\n";
    for (auto c : s)
    {
        cout << setw(2) << setfill('0') << hex <<((uint16_t)c & 255) << ":";
    }
    cout << setfill(' ') << dec << endl;
}
/*code部分get set方法测试*/
void test_code()
{
    UCLCode code_test;

    cout << "new a UCLCode:\n";

    code_test.codeDisplay(code_test);
    cout << sline << '\n';

    code_test.setVersion(1);
    code_test.setTypeOfMedia(9);
    code_test.setPrioAndPoli(15);
    code_test.setFlag(13);
    code_test.setParseRule(0xfff1);//ff1有效
    code_test.setSourOfCont(0xfffffff1);//ffffff1有效
    code_test.setCategory(255);
    code_test.setSubCategory(257);//0x01有效
    code_test.setTopic(0xffffff1);
    code_test.setCopyAndTypeOfCont(254);
    code_test.setSecuEnerLeveCode(251);
    code_test.setLanguage(253);
    code_test.setSizeOfContent(31);
    code_test.setTimeStamp(0x3fffffffff9f9);
    /*
     * serinal number and multiplex bytes test cases
     * 0xCff1f3 - 0x8fffff31; 0x8f1f - 0x1f3f5f7f9f; 0x4f - 0x1f3f5f7f9f48; 0xf - 0x1f3f5f7f9f48
     */
    code_test.setSerialNumber(0x4f);
    code_test.setMultiplexBytes(0x1f3f5f7f9f48);

    code_test.setVersion(3);//对于已经设置过的域重复设置
    //code_test.setVersion(1);

    //code_test.setCheckCode();//最后设置校验码

    string s = code_test.pack(); //打包测试,自动生成校验码

    showCodeHex(s);
    cout << sline << '\n';
    code_test.showCode();

}

//解包测试
void test_unpack()
{
    UCLCode code_test;
    string s(32,'a');
    cout << "unpack test:\n";
    cout << sline << '\n';
    cout << "string:" << s <<'\n';

    code_test.unpack(s);
    string s2 = code_test.pack();
    cout << sline << '\n';
    showCodeHex(s2);
    code_test.showCode();
}
int main() {

    test_code();
    test_unpack();
    return 0;
}