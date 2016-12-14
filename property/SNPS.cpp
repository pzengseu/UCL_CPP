//
// Created by zp on 12/14/16.
//

#include <cassert>
#include "SNPS.h"

//PhysicalElements
bool SNPSPhysicalElements::setCategory(uint8_t category)
{
    assert(category==0x01);
    UCLPropertyBase::setCategory(category);
    return true;
}

bool SNPSPhysicalElements::setSizeOfPhysicalElements(uint8_t size)
{
    assert(size<16);
    lPart = (lPart & 0xffffffffffffffc3) | (size<<2);
    return true;
}

uint8_t SNPSPhysicalElements::getSizeOfPhysicalElements() const
{
    return (lPart>>2) & 0xf;
}

bool SNPSPhysicalElements::setQuickMatcher(uint8_t quickMatcher)
{
    uint8_t lPartValueBytesNum = getLPartValueBytesNum();
    switch (lPartValueBytesNum)
    {
        case 1:
            lPart = (lPart & 0xffffffffff00ffff) | (quickMatcher<<16);
            break;
        case 2:
            lPart = (lPart & 0xffffffff00ffffff) | (quickMatcher<<24);
            break;
        case 3:
            lPart = (lPart & 0xffffff00ffffffff) | (quickMatcher<<32);
            break;
        case 4:
            lPart = (lPart & 0xffff00ffffffffff) | (quickMatcher<<40);
            break;
    }
    return true;
}

uint16_t SNPSPhysicalElements::getQuickMatcher() const
{
    uint8_t lPartValueBytesNum = getLPartValueBytesNum();
    uint16_t quickMatcher;
    switch (lPartValueBytesNum)
    {
        case 1:
            quickMatcher = (lPart>>16) & 0xff;
            break;
        case 2:
            quickMatcher = (lPart>>24) & 0xff;
            break;
        case 3:
            quickMatcher = (lPart>>32) & 0xff;
            break;
        case 4:
            quickMatcher = (lPart>>40) & 0xff;
            break;
    }
    return quickMatcher;
}

//Nominated Receiver
bool SNPSNominatedReceiver::setCategory(uint8_t category)
{
    assert(category==0x2);
    UCLPropertyBase::setCategory(category);
    return true;
}