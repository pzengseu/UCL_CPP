//
// Created by zp on 12/17/16.
//
#include "UCLPropertySet.h"

bool UCLPropertySet::setPropertyHead(UCLPropertyHead propertyHead)
{
    this->propertyHead = propertyHead;
}

UCLPropertyHead& UCLPropertySet::getPropertyHead() const
{
    return propertyHead;
}

bool UCLPropertySet::setProperties(map<int, UCLPropertyBase &> properties)
{
    this->properties = properties;
}

map<int, UCLPropertyBase &> & UCLPropertySet::getProperties() const
{
    return properties;
}