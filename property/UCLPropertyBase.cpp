//
// Created by zp on 12/13/16.
//
#include "UCLPropertyBase.h"
#include <cassert>

//tPart
bool UCLPropertyBase::setTPart(uint8_t t)
{
    tPart = t;
    return true;
}

uint8_t UCLPropertyBase::getTPart() const
{
    return tPart;
}

bool UCLPropertyBase::setCategory(uint8_t category)
{
    assert(category<16);
    tPart = (tPart & 0xf0) | category;
    return true;
}

uint8_t UCLPropertyBase::getCategory() const
{
    return (tPart & 0x0f);
}

bool UCLPropertyBase::setHelp(uint8_t help)
{
    assert(help<16);
    tPart = (tPart & 0x0f) | (help << 4);
    return true;
}

uint8_t UCLPropertyBase::getHelp() const
{
    uint8_t help = tPart >> 4;
    return help;
}

//lPart
bool UCLPropertyBase::setLPart(const uint64_t lPart)
{
    UCLPropertyBase::lPart = lPart;
    return true;
}

uint64_t UCLPropertyBase::getLPart() const
{
    return lPart;
}

uint8_t UCLPropertyBase::getLPartBytesNum(int quickMatcherBytes) const
{
    return LPARTHEAD_BYTESNUM + getLPartValueBytesNum() + quickMatcherBytes;
}

bool UCLPropertyBase::setLPartHead(uint8_t lPartHead)
{
    lPart = (lPart & 0xffffffffffffff00) | lPartHead;
    return true;
}

uint8_t UCLPropertyBase::getLPartHead() const
{
    return lPart & 0xff;
}

bool UCLPropertyBase::setLPartValueBytesNum(uint8_t bytesNum)
{
    assert(bytesNum>=1&&bytesNum<=4);
    lPart = (lPart & 0xffffffffffffff3f) | ((bytesNum - 1)<<6);
    return true;
}

uint8_t UCLPropertyBase::getLPartValueBytesNum() const
{
    return ((lPart>>6) & 0x3) + 1;
}

bool UCLPropertyBase::setTotalLength(int quickMatcherBytes)
{
    uint64_t totalLength = TPAER_BYTESNUM + 7 + getVPartBytesNum();
    cout<<"totalLength="<<totalLength<<endl;
    assert(totalLength<=UINT32_MAX);
    if(totalLength <= UINT8_MAX)
    {
        setLPartValueBytesNum(1);
        lPart = (lPart & 0xffffffffffff00ff) | (totalLength<<8);
    }
    else if (totalLength > UINT8_MAX && totalLength <= UINT16_MAX)
    {
        setLPartValueBytesNum(2);
        lPart = (lPart & 0xffffffffff0000ff) | (totalLength<<8);
    }
    else if (totalLength > UINT16_MAX && totalLength <= 0xffffff)
    {
        setLPartValueBytesNum(3);
        lPart = (lPart & 0xffffffff000000ff) | (totalLength<<8);
    }
    else if (totalLength > 0xffffff && totalLength <= UINT32_MAX)
    {
        setLPartValueBytesNum(4);
        lPart = (lPart & 0xffffff00000000ff) | (totalLength<<8);
    }
    return true;
}

uint32_t UCLPropertyBase::getTotalLength() const
{
    return 8 + getVPartBytesNum();
}

//vPart
const string &UCLPropertyBase::getVPart() const {
    return vPart;
}

bool UCLPropertyBase::setVPart(const string &vPart) {
    UCLPropertyBase::vPart = vPart;
    return true;
}

uint32_t UCLPropertyBase::getVPartBytesNum() const
{
    return vPart.size();
}
