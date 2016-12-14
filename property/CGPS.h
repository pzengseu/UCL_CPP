//
// Created by zp on 2016/12/13.
//

//CGPS, Content Governance Properties Set
#ifndef UCL_CGPS_H
#define UCL_CGPS_H
#include "UCLPropertyBase.h"
#include <cstdint>

class CGPSProvenance:public UCLPropertyBase
{
public:
    //the category of provenance
    bool setCategory(uint8_t category=0x3);

    //the description of provenance
    bool setDescription(uint8_t des);
    uint8_t getDescription();
};
#endif //UCL_CGPS_H
