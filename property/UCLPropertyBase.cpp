//
// Created by zp on 12/13/16.
//
#include "UCLPropertyBase.h"
#include <cassert>
#include <bitset>
#include <cmath>

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

bool UCLPropertyBase::setHelper(uint8_t help)
{
    assert(help<16);
    tPart = (tPart & 0x0f) | (help << 4);
    return true;
}

uint8_t UCLPropertyBase::getHelper() const
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

uint8_t UCLPropertyBase::getLPartBytesNum() const
{
    return LPARTHEAD_BYTESNUM + getLPartValueBytesNum() + getQuickMatcherBytesNum();
}

bool UCLPropertyBase::setLPartHead(uint8_t lPartHead)
{
    lPart = (lPart & 0xffffffffffffff00) | lPartHead;
    return true;
}

bool UCLPropertyBase::setLPartHead(uint8_t start, uint8_t end, uint8_t head)
{
    assert(start>=0 && start <= 7 && end>=0 && end<=7 && start < end);
    assert(head < pow(2.0, end-start+1));
    bitset<64> bLH(lPart);
    for(int i = start; i <= end; i++)
    {
        bLH.reset(i);
    }
    lPart = bLH.to_ulong();
    head <<= start;
    lPart = lPart | head;
}

uint8_t UCLPropertyBase::getLPartHead() const
{
    return lPart & 0xff;
}

uint8_t UCLPropertyBase::getLPartHead(uint8_t start, uint8_t end)
{
    assert(start>=0 && start <= 7 && end>=0 && end<=7 && start < end);
    uint8_t lH = (uint8_t)(lPart >> start);
    bitset<8> bLH(lH);
    for(int i=(end-start+1); i < 8; i++)
    {
        bLH.reset(i);
    }
    return (uint8_t)bLH.to_ulong();
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

bool UCLPropertyBase::setTotalLength()
{
    uint64_t totalLength = TPAER_BYTESNUM + LPARTHEAD_BYTESNUM + getQuickMatcherBytesNum() + getVPartBytesNum();
    assert((totalLength + LPARTVALUE_BYTES_MAX)<=UINT32_MAX);
    if((totalLength + LPARTVALUE_BYTES_MIN) <= UINT8_MAX)
    {
        setLPartValueBytesNum(1);
        lPart = (lPart & 0xffffffffffff00ff) | ((totalLength + LPARTVALUE_BYTES_MIN)<<8);
    }
    else if ((totalLength + LPARTVALUE_BYTES_MIN) > UINT8_MAX && (totalLength + 2*LPARTVALUE_BYTES_MIN) <= UINT16_MAX)
    {
        setLPartValueBytesNum(2);
        lPart = (lPart & 0xffffffffff0000ff) | ((totalLength + 2*LPARTVALUE_BYTES_MIN)<<8);
    }
    else if ((totalLength + 2*LPARTVALUE_BYTES_MIN) > UINT16_MAX && (totalLength + 3*LPARTVALUE_BYTES_MIN) <= 0xffffff)
    {
        setLPartValueBytesNum(3);
        lPart = (lPart & 0xffffffff000000ff) | ((totalLength + 3*LPARTVALUE_BYTES_MIN)<<8);
    }
    else if ((totalLength + 3*LPARTVALUE_BYTES_MIN) > 0xffffff && (totalLength + LPARTVALUE_BYTES_MAX) <= UINT32_MAX)
    {
        setLPartValueBytesNum(4);
        lPart = (lPart & 0xffffff00000000ff) | ((totalLength + LPARTVALUE_BYTES_MAX)<<8);
    }

    return true;
}

uint32_t UCLPropertyBase::getTotalLength() const
{
    return TPAER_BYTESNUM + getLPartBytesNum() + getVPartBytesNum();
}

//vPart
const string &UCLPropertyBase::getVPart() const {
    return vPart;
}

bool UCLPropertyBase::setVPart(const string &vPart) {
    UCLPropertyBase::vPart = vPart;
    setTotalLength();
    return true;
}

uint32_t UCLPropertyBase::getVPartBytesNum() const
{
    return vPart.size();
}

uint8_t UCLPropertyBase::getQuickMatcherBytesNum() const {
    return quickMatcherBytesNum;
}

void UCLPropertyBase::setQuickMatcherBytesNum(uint8_t quickMatcherBytesNum) {
    assert(quickMatcherBytesNum==2);  //quickMatcher字节数固定为２
    UCLPropertyBase::quickMatcherBytesNum = quickMatcherBytesNum;
}

string UCLPropertyBase::pack()
{
    string property;
    property.push_back(tPart);

    int n = getLPartBytesNum();
    for(int i=0; i < n; i++)
    {
        property.push_back((lPart>>(i*8) & 0xff));
    }
    property += vPart;

    return property;
}

void UCLPropertyBase::unpack(string property) 
{
    //tPart
    tPart = property[0];
    
    //lPart
    lPart = (lPart & 0xffffffffffffff00) | property[1];
    int  lPartValueBytesNum = getLPartValueBytesNum();
    uint64_t quickMatcher = 0;
    quickMatcher = (quickMatcher & 0xff00) | property[TPAER_BYTESNUM + LPARTHEAD_BYTESNUM + lPartValueBytesNum];
    quickMatcher = (quickMatcher & 0x00ff) | ((uint16_t)property[TPAER_BYTESNUM +  LPARTHEAD_BYTESNUM + lPartValueBytesNum + 1]<<8);

    switch (lPartValueBytesNum-1)
    {
        case 0:
            lPart = (lPart & 0xffffffffffff00ff) | (property.size() << 8);
            lPart = (lPart & 0xffffffff0000ffff) | (quickMatcher << 16);
            break;
        case 1:
            lPart = (lPart & 0xffffffffff0000ff) | (property.size() << 8);
            lPart = (lPart & 0xffffff0000ffffff) | (quickMatcher << 24);
            break;
        case 2:
            lPart = (lPart & 0xffffffff000000ff) | (property.size() << 8);
            lPart = (lPart & 0xffff0000ffffffff) | (quickMatcher << 32);
            break;
        case 3:
            lPart = (lPart & 0xffffff00000000ff) | (property.size() << 8);
            lPart = (lPart & 0xff0000ffffffffff) | (quickMatcher << 40);
            break;
    }

    //vPart
    vPart = property.substr(TPAER_BYTESNUM + LPARTHEAD_BYTESNUM + lPartValueBytesNum + getQuickMatcherBytesNum());
}

void UCLPropertyBase::setProperty(uint8_t category, uint8_t helper, string vPart)
{
    assert(helper < 16);
    setCategory(category);
    setHelper(helper);
    setVPart(vPart);
}