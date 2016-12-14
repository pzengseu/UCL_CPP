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
    //the category of physicalElements
    bool setCategory(uint8_t category=0x1);

    //the size of phyiscalElements
    bool setSizeOfPhysicalElements(uint8_t size);
    uint8_t getSizeOfPhysicalElements() const;

    //quickmatcher
    bool setQuickMatcher(uint8_t quickMatcher);
    uint16_t getQuickMatcher() const;
};

//Nominated Receiver
class SNPSNominatedReceiver:public UCLPropertyBase{
public:
    //the category of Nominated Receiver
    bool setCategory(uint8_t category=0x2);
};
#endif //UCL_SNPS_H
