//
// Created by zp on 12/17/16.
//
#include <bitset>
#include "UCLPropertySet.h"

bool UCLPropertySet::setPropertyHead(UCLPropertyHead propertyHead)
{
    this->propertyHead = propertyHead;
}

const UCLPropertyHead& UCLPropertySet::getPropertyHead() const
{
    return propertyHead;
}

const map<int, UCLPropertyBase *> &UCLPropertySet::getProperties() const {
    return properties;
}

void UCLPropertySet::setProperties(const map<int, UCLPropertyBase *> &properties) {
    UCLPropertySet::properties = properties;
}

void UCLPropertySet::setHeadCategory(uint8_t category)
{
    propertyHead.setCategory(category);
}

uint8_t UCLPropertySet::getHeadCategory()
{
    return propertyHead.getCategory();
}

void UCLPropertySet::setHeadHelper(uint8_t helper)
{
    propertyHead.setHelper(helper);
}

uint8_t UCLPropertySet::getHeadHelper()
{
    return propertyHead.getHelper();
}

bool UCLPropertySet::setProperty(UCLPropertyBase *property)
{
    properties[property->getCategory()] = property;
}

bool UCLPropertySet::delProperty(uint8_t category)
{
    properties.erase(category);
}

uint16_t UCLPropertySet::generateQuickMatcher()
{
    bitset<16> qmb;
    map<int, UCLPropertyBase *>::iterator iter = properties.begin();
    for(; iter != properties.end(); iter++)
    {
        qmb.set(iter->first);
    }

    return qmb.to_ulong();

}

string UCLPropertySet::generateHeadVPart()
{
    bitset<16> qmb(propertyHead.getQuickMatcher());
    string value="";

    for(int i=0; i < 16; i++)
    {
        if(qmb.test(i))
        {
            value += properties[i]->pack();
        }
    }

    return value;
}

void UCLPropertySet::setSet()
{
    propertyHead.setQuickMatcher(generateQuickMatcher());
    propertyHead.setVPart(generateHeadVPart());
    propertyHead.setTotalLength();
}

string UCLPropertySet::pack()
{
    return propertyHead.pack();
}

void UCLPropertySet::unpack(string properties) {}