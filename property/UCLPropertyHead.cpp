//
// Created by zp on 12/14/16.
//

#include <cassert>
#include "UCLPropertyHead.h"

bool UCLPropertyHead::setSize(uint8_t size)
{
    //属性元素个数size-1为属性包的具体值
    assert(size<=16 && size > 0);
    size -= 1;
    lPart = (lPart & 0xffffffffffffffc3) | (size<<2);
    return true;
}

uint8_t UCLPropertyHead::getSize() const
{
    return ((lPart>>2) & 0xf) + 1;
}

bool UCLPropertyHead::setQuickMatcher(uint16_t quickM)
{
    uint64_t quickMatcher = quickM;
    //根据quickMatcher信息计算属性元素个数
    uint64_t temp = quickM;
    uint8_t size = 0;
    while(temp)
    {
        if(temp&0x1)
        {
            size++;
        }
        temp >>= 1;
    }
    setSize(size);

    //设置LPart　quickMatcher部分
    uint8_t lPartValueBytesNum = getLPartValueBytesNum();
    switch (lPartValueBytesNum)

    {
        case 1:
            lPart = (lPart & 0xffffffff0000ffff) | (quickMatcher<<16);
            break;
        case 2:
            lPart = (lPart & 0xffffff0000ffffff) | (quickMatcher<<24);
            break;
        case 3:
            lPart = (lPart & 0xffff0000ffffffff) | (quickMatcher<<32);
            break;
        case 4:
            lPart = (lPart & 0xff0000ffffffffff) | (quickMatcher<<40);
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
            quickMatcher = (lPart>>24) & 0xffff;
            break;
        case 3:
            quickMatcher = (lPart>>32) & 0xffff;
            break;
        case 4:
            quickMatcher = (lPart>>40) & 0xffff;
            break;
    }
    return quickMatcher;
}