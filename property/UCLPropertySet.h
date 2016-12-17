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
        propertyHead.setQuickMatcherBytesNum(2);
        setMustToDo();
    }
    virtual ~UCLPropertySet() {}

    const UCLPropertyHead &getPropertyHead() const;
    bool setPropertyHead(UCLPropertyHead propertyHead);

    void setProperties(const map<int, UCLPropertyBase *> &properties);
    const map<int, UCLPropertyBase *> &getProperties() const;

    //设置properthHead类别
    void setHeadCategory(uint16_t category);

    //根据properties生成propertyHead的快速匹配
    uint16_t generateQuickMatcher();

    //设置properthHead属性净荷字段
    void setHeadValue();

    //初始化集合或设置properties必须调用的函数
    void setMustToDo();
};
#endif //UCL_CPP_UCLPROPERTYSET_H
