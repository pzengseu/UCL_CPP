//
// Created by zp on 12/12/16.
//

#ifndef UCL_CPP_UCLPROPERTYSET_H
#define UCL_CPP_UCLPROPERTYSET_H

#include <vector>
#include <cstdint>
#include "UCLPropertyBase.h"
#include "UCLPropertyHead.h"
using namespace std;

class UCLPropertySet{
private:
    UCLPropertyHead propertyHead;
    vector<UCLPropertyBase &> properties;
public:
    UCLPropertyHead getPropertyHead() const;
    bool setPropertyHead(UCLPropertyHead propertyHead);

    vector<UCLPropertyBase &> getProperties() const;
    bool setProperties(vector<UCLPropertyBase &> properties);

    UCLPropertySet() {}
    virtual ~UCLPropertySet() {}
};
#endif //UCL_CPP_UCLPROPERTYSET_H
