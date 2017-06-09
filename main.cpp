#include <iostream>
#include <iterator>
#include <list>
#include <bitset>
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

void testUCL()
{
    //UCLCode部分测试函数
    testUCLCodeEasy();

    //测试UCL打包解包
    testEasy();
}

vector<string> split(string str, string pattern)
{
    int pos;
    vector<string> result;
    str += pattern;
    int size = str.size();

    for(int i=0; i<size; i++)
    {
        pos=str.find(pattern,i);
        if(pos<size)
        {
            std::string s=str.substr(i,pos-i);
            result.push_back(s);
            i=pos+pattern.size()-1;
        }
    }
    return result;
}

int main()
{
    map<int, string> entity;
    entity[0] = "人";
    entity[1] = "时";
    entity[2] = "地";
    entity[3] = "事";
    entity[4] = "因";
    entity[5] = "其它";

    bitset<6> bqm(31);
    int es[bqm.count()];
    int j = 0;
    for (int i = 0; i < bqm.size(); i++)
    {
        if (bqm.test(i))
            es[j++] = i;
    }

    string str = "江苏省委\\r2017\\r金坛\\r培育计划\\r美丽;nice";
    vector<string> ev = split(str, "\\r");

    for (int i = 0; i < ev.size(); i++)
    {
        cout << entity[es[i]] << " : ";
        vector<string> evt = split(ev[i], ";");
        copy(evt.begin(), evt.end(), ostream_iterator<string>(cout, " "));
        cout << endl;
    }

    return 0;
}