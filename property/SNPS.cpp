//
// Created by zp on 12/14/16.
//

#include <cassert>
#include "SNPS.h"

//PhysicalElements
SNPSPhysicalElements::SNPSPhysicalElements()
{
    setCategory(0x1);
}

bool SNPSPhysicalElements::setCategory(uint8_t category)
{
    assert(category==0x01);
    UCLPropertyBase::setCategory(category);
    return true;
}

uint8_t SNPSPhysicalElements::getSize() const
{
    uint8_t quickMatcher = lPart & 0x3f;
    uint8_t size = 0;
    while(quickMatcher)
    {
        if(quickMatcher&0x1)
        {
            size++;
        }
        quickMatcher >>= 1;
    }
    return size;
}

bool SNPSPhysicalElements::setLPartQuickMatcher(uint8_t quickMatcher)
{
    assert(quickMatcher<=0x3f);
    lPart = (lPart & 0xffffffffffffffc0) | quickMatcher;
    return true;
}

uint16_t SNPSPhysicalElements::getLPartQuickMatcher() const
{
    return lPart & 0x3f;
}

//Nominated Receiver
SNPSNominatedReceiver::SNPSNominatedReceiver()
{
    setCategory(0x2);
}

bool SNPSNominatedReceiver::setCategory(uint8_t category)
{
    assert(category==0x2);
    UCLPropertyBase::setCategory(category);
    return true;
}