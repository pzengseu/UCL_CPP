//
// Created by zp on 12/17/16.
//

#include <map>
#include <bitset>
#include <cassert>
#include "property/UCLPropertyHead.h"
#include "UCL.h"

const UCLPropertyHead &UCL::getUclPropertyHead() const {
    return uclPropertyHead;
}

void UCL::setUclPropertyHead(const UCLPropertyHead &uclPropertyHead) {
    UCL::uclPropertyHead = uclPropertyHead;
}

const map<int, UCLPropertySet> &UCL::getPropertySets() const {
    return propertySets;
}

void UCL::setPropertySets(const map<int, UCLPropertySet> &propertySets) {
    UCL::propertySets = propertySets;
}

bool UCL::setPropertySet(UCLPropertySet &propertySet)
{
    propertySets[propertySet.getHeadCategory()] = propertySet;
    setUCL();
}

bool UCL::delPropertySet(uint8_t category)
{
    propertySets.erase(category);
}

void UCL::setHeadCategory(uint8_t category)
{
    uclPropertyHead.setCategory(category);
}

uint8_t UCL::getHeadCategory()
{
    return uclPropertyHead.getCategory();
}

void UCL::setHeadHelper(uint8_t helper)
{
    uclPropertyHead.setHelper(helper);
}

uint8_t UCL::getHeadHelper()
{
    return uclPropertyHead.getHelper();
}

uint16_t UCL::generateQuickMatcher()
{
    bitset<16> qmb;
    map<int, UCLPropertySet>::iterator iter = propertySets.begin();
    for(; iter != propertySets.end(); iter++)
    {
        qmb.set(iter->first);
    }

    return qmb.to_ulong();
}

string UCL::generateHeadVPart()
{
    bitset<16> qmb(uclPropertyHead.getQuickMatcher());
    string value;

    for(int i=0; i < 16; i++)
    {
        if(qmb.test(i))
        {
            value += propertySets[i].pack();
        }
    }

    return value;
}

void UCL::setUCL()
{
    uclPropertyHead.setQuickMatcher(generateQuickMatcher());
    uclPropertyHead.setVPart(generateHeadVPart());
//    uclPropertyHead.setTotalLength();
}

string UCL::getValue(int setPos, int propertyPos)
{
    assert(propertySets.find(setPos)!=propertySets.end());
    return propertySets[setPos].getPropertyVPart(propertyPos);
//    map<int, UCLPropertyBase> properties = propertySets[setPos].getProperties();
//    assert(properties.find(propertyPos)!=properties.end());
//    return properties[propertyPos].getVPart();
}

void UCL::setValue(int setPos, int propertyPos, string value)
{
    assert(propertySets.find(setPos)!=propertySets.end());
    propertySets[setPos].setPropertyVPart(propertyPos, value);
    setUCL();
}

string UCL::packPropertySets()
{
    return uclPropertyHead.pack();
}

void UCL::unpackPropertySets(string properties)
{
    uclPropertyHead.unpack(properties);
    bitset<16> bqm(uclPropertyHead.getQuickMatcher());
    string headVPart = uclPropertyHead.getVPart();
    uint32_t tmp = 0;
    for(int i=0; i < bqm.size(); i++)
    {
        if(bqm.test(i))
        {
            //计算属性集合头部属性长度值字段字节数
            int lValueBytes = (int)(headVPart[1+tmp] >> 6) + 1;
            //取出长度值字段
            string lValue = headVPart.substr(2+tmp, lValueBytes);
            uint32_t lValueNum = 0;
            for(int j=0; j < lValue.size(); j++)
            {
                switch (j)
                {
                    case 0:
                        lValueNum = (0xffffff00 & lValueNum) | lValue[j];
                        break;
                    case 1:
                        lValueNum = (0xffff00ff & lValueNum) | (lValue[j]<<8);
                        break;
                    case 2:
                        lValueNum = (0xff00ffff & lValueNum) | (lValue[j]<<16);
                        break;
                    case 3:
                        lValueNum = (0xff00ffff & lValueNum) | (lValue[j]<<24);
                        break;
                }
            }
            string propertySet = headVPart.substr(tmp, lValueNum);
            UCLPropertySet proSet;
            proSet.unpack(propertySet);
            propertySets[i] = proSet;
            tmp += lValueNum;
        }
    }
}

//string UCL::pack()
//{
//    return uclCode.pack() + uclCodeExtension.pack() + packPropertySets();
//}
//
//void UCL::unpack(string ucl)
//{
//    //UCLCode
//    string sUCLCode = ucl.substr(0, 32);
//    uclCode.unpack(sUCLCode);
//
//    //UCLCodeExt
//    int uclCodeExt = 0;
//    if((uclCode.getFlag() & 0x1))
//    {
//        uclCodeExt = ucl[32] & 0xf;
//    };
//    string sUCLCodeExt = ucl.substr(32, uclCodeExt * 16);
//    uclCodeExtension.unpack(sUCLCodeExt);
//
//    //UCLProperty
//    unpackPropertySets(ucl.substr(32 + uclCodeExt * 16));
//}
//
void UCL::showUCL()
{
//    uclCode.codeDisplay();
//    uclCodeExtension.showCodeExt();

    cout << "属性集合个数:" << (int)uclPropertyHead.getSize() << endl;
    map<int, UCLPropertySet>::iterator proSet = propertySets.begin();
    for(; proSet!=propertySets.end(); proSet++)
    {
        proSet->second.showPropertySet();
    }
}

/*
 * UCLCode and extension
 */
const UCLCode &UCL::getUclCode() const {
    return uclCode;
}

void UCL::setUclCode(const UCLCode &uclCode) {
    UCL::uclCode = uclCode;
}

const UCLCodeExtension &UCL::getUclCodeExtention() const {
    return uclCodeExtension;
}

void UCL::setUclCodeExtention(const UCLCodeExtension &uclCodeExtention) {
    UCL::uclCodeExtension = uclCodeExtention;
}
