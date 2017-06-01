//
// Created by zp on 12/12/16.
//

#ifndef UCL_CPP_UCLPROPERTYHEAD_H
#define UCL_CPP_UCLPROPERTYHEAD_H

#include "UCLPropertyBase.h"
#include <cstdint>

//the head of UCLProperty
class UCLPropertyHead:public  UCLPropertyBase{
public:
    UCLPropertyHead()
    {
        setQuickMatcherBytesNum(2);
    }
    virtual ~UCLPropertyHead() {}

    //number of UCLPropertySet
    bool setSize(uint8_t size);
    uint8_t getSize() const;

    bool setQuickMatcher(uint16_t quickM);
    uint16_t getQuickMatcher() const;
};
#endif //UCL_CPP_UCLPROPERTYHEAD_H
