//
// Created by zp on 12/14/16.
//

#include <cassert>
#include "CDPS.h"

bool CDPSAuthor::setCategory(uint8_t category)
{
    assert(category==0x01);
    UCLPropertyBase::setCategory(category);
    return true;
}
