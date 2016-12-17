//
// Created by zp on 12/12/16.
//

#ifndef UCL_CPP_UCLPROPERTYSET_H
#define UCL_CPP_UCLPROPERTYSET_H

#include <vector>
#include <map>
#include <cstdint>
#include "UCLPropertyBase.h"
#include "UCLPropertyHead.h"
using namespace std;

class UCLPropertySet{
private:
    UCLPropertyHead propertyHead;
    map<int, UCLPropertyBase &>properties;
public:
    UCLPropertyHead &getPropertyHead() const;
    bool setPropertyHead(UCLPropertyHead propertyHead);

    map<int, UCLPropertyBase &> &getProperties() const;
    bool setProperties(map<int, UCLPropertyBase &> properties);

    UCLPropertySet() {}
    virtual ~UCLPropertySet() {}
};
#endif //UCL_CPP_UCLPROPERTYSET_H
