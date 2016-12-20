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
    map<int, UCLPropertyBase *>properties;
public:
    UCLPropertySet()
    {
        propertyHead = UCLPropertyHead();
        setSet();
    }
    virtual ~UCLPropertySet() {}

    const UCLPropertyHead &getPropertyHead() const;
    bool setPropertyHead(UCLPropertyHead propertyHead);

    void setProperties(const map<int, UCLPropertyBase *> &properties);
    const map<int, UCLPropertyBase *> &getProperties() const;

    //设置properthHead类别
    void setHeadCategory(uint8_t category);
    uint8_t getHeadCategory();
    //设置propertyHead helper
    void setHeadHelper(uint8_t helper);
    uint8_t getHeadHelper();

    //设置属性 删除属性
    bool setProperty(UCLPropertyBase *property);
    bool delProperty(uint8_t category);

    //根据properties生成propertyHead的快速匹配
    uint16_t generateQuickMatcher();
    //根据properties生成propertyHead的vPart
    string generateHeadVPart();

    //初始化集合或设置properties后必须调用的函数
    void setSet();

    //属性集合打包解包
    string pack();
    void unpack(string properties);
};
#endif //UCL_CPP_UCLPROPERTYSET_H
