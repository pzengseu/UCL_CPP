//
// Created by hp-6380 on 2016/12/5.
//

#ifndef UCL_V0_1_UCLCODEEXTENSION_H
#define UCL_V0_1_UCLCODEEXTENSION_H

#include <stdint-gcc.h>
#include <string>
#include<vector>
using std::vector;
using std::string;

class UCLCodeExtension
{
public:
    uint64_t getFieldNumbrs();
    bool setFieldNumbers();

    uint16_t getStartBit(uint64_t serialNumber);    //通过域的序号获取对应域的起始位
    bool setStartBit(); //

    uint16_t getFieldLength(uint64_t serialNumber);
    bool setFieldLength();

    uint64_t getValue(uint64_t serialNumber);
    bool setValue(uint64_t serialNumber, uint64_t bitStream);
private:
    uint64_t length; //扩展总位数（不包括4位长度域）
    uint64_t fieldNumbers; //扩展域个数
    vector<int> fieldLength; //各个域的位长数组（需动态分配内存）指针
    vector<int> startBit; //各个域的起始位数组（需动态分配内存）指针
    string *data; //填充内容
};
#endif //UCL_V0_1_UCLCODEEXTENSION_H
