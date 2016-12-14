//
// Created by zp on 12/14/16.
//

#include <cassert>
#include "UCLPropertyHead.h"

bool UCLPropertyHead::setSize(uint8_t size)
{
    assert(size<16);
    lPart = lPart & (0xffffffffffffffc3 | (size<<2));
    return true;
}

uint8_t UCLPropertyHead::getSize() const
{
    return (lPart>>2) & 0xf;
}

bool UCLPropertyHead::setQuickMatcher(uint16_t quickMatcher)
{
    uint8_t lPartValueBytesNum = getLPartValueBytesNum();
    switch (lPartValueBytesNum)
    {
        case 1:
            lPart = lPart & (0xffffffff0000ffff | (quickMatcher<<16));
            break;
        case 2:
            lPart = lPart & (0xffffff0000ffffff | (quickMatcher<<16));
            break;
        case 3:
            lPart = lPart & (0xffff0000ffffffff | (quickMatcher<<16));
            break;
        case 4:
            lPart = lPart & (0xff0000ffffffffff | (quickMatcher<<16));
            break;
    }
    return true;
}

uint16_t UCLPropertyHead::getQuickMatcher() const
{
    uint8_t lPartValueBytesNum = getLPartValueBytesNum();
    uint16_t quickMatcher;
    switch (lPartValueBytesNum)
    {
        case 1:
            quickMatcher = (lPart>>16) & 0xffff;
            break;
        case 2:
            quickMatcher = (lPart>>24) & 0xffffff;
            break;
        case 3:
            quickMatcher = (lPart>>32) & 0xffffffff;
            break;
        case 4:
            quickMatcher = (lPart>>40) & 0xffffffffff;
            break;
    }
    return quickMatcher;
}