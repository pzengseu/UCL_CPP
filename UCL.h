//
// Created by zp on 2016/12/12.
//

#ifndef UCL_UCL_H
#define UCL_UCL_H

#include <vector>
#include <map>
#include "property/UCLPropertyHead.h"
#include "property/UCLPropertySet.h"
//#include "code/UCLCode.h"
//#include "code/UCLCodeExtention.h"

class UCL{
private:
//    UCLCode uclCode;
//    UCLCodeExtention uclCodeExtention;
    UCLPropertyHead uclPropertyHead;
    map<int, UCLPropertySet> propertySets;

public:
    UCL()
    {
        uclPropertyHead = UCLPropertyHead();
        uclPropertyHead.setCategory(0x2);  //英文
        uclPropertyHead.setTotalLength();
    }
    virtual ~ UCL() {}

    //uclPropertyHead
    const UCLPropertyHead &getUclPropertyHead() const;
    void setUclPropertyHead(const UCLPropertyHead &uclPropertyHead);

    //propertySets
    const map<int, UCLPropertySet> &getPropertySets() const;
    void setPropertySets(const map<int, UCLPropertySet> &propertySets);

    //设置　删除属性集合
    bool setPropertySet(UCLPropertySet &propertySet);
    bool delPropertySet(uint8_t category);

    //设置uclProperthHead类别
    void setHeadCategory(uint8_t category);
    uint8_t getHeadCategory();
    //设置uclPropertyHead helper
    void setHeadHelper(uint8_t helper);
    uint8_t getHeadHelper();

    //根据propertySets生成uclPropertyHead的快速匹配
    uint16_t generateQuickMatcher();
    //根据propertySets生成uclPropertyHead的vPart
    string generateHeadVPart();

    //设置propertySets后必须调用的函数
    void setUCL();

    //获取第setPos集合的第propertyPos属性的vPart
    string getValue(int setPos, int propertyPos);

    //属性集合打包解包
    string packPropertySets();
    void unpackPropertySets(string properties);
};
#endif //UCL_UCL_H
