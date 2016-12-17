//
// Created by zp on 12/17/16.
//
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

void UCLPropertySet::setHeadCategory(uint16_t category)
{
    propertyHead.setCategory(category);
}

void UCLPropertySet::setMustToDo()
{
//    propertyHead.setQuickMatcher(generateQuickMatcher());
//    setHeadValue();
    propertyHead.setTotalLength();
}