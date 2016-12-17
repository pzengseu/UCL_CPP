//
// Created by zp on 2016/12/13.
//

//SNPS, System&Network Properties Set
#ifndef UCL_SNPS_H
#define UCL_SNPS_H

#include "UCLPropertyBase.h"
#include <stdint.h>

//PhysicalElements
class SNPSPhysicalElements:public UCLPropertyBase{
public:
    //构造函数里设置固定类别
    SNPSPhysicalElements();

    //the category of physicalElements
    bool setCategory(uint8_t category=0x1);

    //取消物理要素速配信息子分量，将长度值子分量０－５位当做速配信息
    //the size of phyiscalElements
    uint8_t getSize() const;

    //quickmatcher
    bool setLPartQuickMatcher(uint8_t quickMatcher);
    uint16_t getLPartQuickMatcher() const;
};

//Nominated Receiver
class SNPSNominatedReceiver:public UCLPropertyBase{
public:
    SNPSNominatedReceiver();

    //the category of Nominated Receiver
    bool setCategory(uint8_t category=0x2);
};
#endif //UCL_SNPS_H
