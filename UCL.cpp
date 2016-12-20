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
    uclPropertyHead.setTotalLength();
}

string UCL::getValue(int setPos, int propertyPos)
{
    assert(propertySets.find(setPos)!=propertySets.end());
    map<int, UCLPropertyBase *> properties = propertySets[setPos].getProperties();
    assert(properties.find(propertyPos)!=properties.end());
    return properties[propertyPos]->getVPart();
}

string UCL::pack()
{
    return uclPropertyHead.pack();
}

void UCL::unpack(string properties) {}