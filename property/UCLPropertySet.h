//
// Created by zp on 12/12/16.
//

#ifndef UCL_CPP_UCLPROPERTYSET_H
#define UCL_CPP_UCLPROPERTYSET_H

#include <vector>
#include <map>
#include <cstdint>
#include "UCLPropertyBase.h"
#include "UCLPropertyHead.h"
using namespace std;

class UCLPropertySet{
private:
    UCLPropertyHead propertyHead;
    map<int, UCLPropertyBase>properties;
public:
    UCLPropertySet()
    {
        propertyHead = UCLPropertyHead();
        propertyHead.setTotalLength();
    }
    virtual ~UCLPropertySet() {}

    const UCLPropertyHead &getPropertyHead() const;
    bool setPropertyHead(UCLPropertyHead propertyHead);

    const map<int, UCLPropertyBase> &getProperties() const;
    void setProperties(const map<int, UCLPropertyBase> &properties);

    //设置properthHead类别
    void setHeadCategory(uint8_t category);
    uint8_t getHeadCategory();
    //设置propertyHead helper
    void setHeadHelper(uint8_t helper);
    uint8_t getHeadHelper();

    //设置属性 删除属性
    bool setProperty(UCLPropertyBase property);
    bool delProperty(uint8_t category);
    UCLPropertyBase getProperty(uint8_t category);

    //设置属性值
    string getPropertyVPart(int pos);
    void setPropertyVPart(int pos, string value);

    //根据properties生成propertyHead的快速匹配
    uint16_t generateQuickMatcher();
    //根据properties生成propertyHead的vPart
    string generateHeadVPart();

    //properties有变必须调用该函数
    void setSet();

    //属性集合打包解包
    string pack();
    void unpack(string propertySet);

    //显示属性集合
    void showPropertySet();
};
#endif //UCL_CPP_UCLPROPERTYSET_H
