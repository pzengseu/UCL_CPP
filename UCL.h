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
    }
    virtual ~ UCL() {}

    //uclPropertyHead
    const UCLPropertyHead &getUclPropertyHead() const;
    void setUclPropertyHead(const UCLPropertyHead &uclPropertyHead);

    //propertySets
    const map<int, UCLPropertySet> &getPropertySets() const;
    void setPropertySets(const map<int, UCLPropertySet> &propertySets);

    //propertySets中插入基本SNPS集合
    void generateSNPSSet();
};
#endif //UCL_UCL_H
