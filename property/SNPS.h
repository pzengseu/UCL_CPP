//
// Created by zp on 2016/12/13.
//

//SNPS, System&Network Properties Set
#ifndef UCL_SNPS_H
#define UCL_SNPS_H

#include "UCLPropertyBase.h"
#include <stdint.h>

class SNPSPhysicalElements:public UCLPropertyBase{
public:
    //the category of physicalElements
    bool setCategory(uint8_t category=0x1);

    //the amount of phyiscalElements
    bool setAmountOfPhysicalElements(uint8_t amountOfPhysicalElements);
    uint8_t getAmountOfPhysicalElements() const;

    //quickmatcher
    bool setQuickMatcher(uint8_t quickerMatcher);
    uint16_t getFastMatch() const;
};
#endif //UCL_SNPS_H
