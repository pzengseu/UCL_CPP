//
// Created by zp on 2016/12/12.
//

#ifndef UCL_UCL_H
#define UCL_UCL_H

#include <vector>
#include "property/UCLPropertyHead.h"
#include "property/UCLPropertySet.h"
#include "code/UCLCode.h"
#include "code/UCLCodeExtention.h"

class UCL{
private:
    UCLCode uclCode;
    UCLCodeExtention uclCodeExtention;
    UCLPropertyHead uclPropertyHead;
    vector<UCLPropertySet &> propertySets;
};
#endif //UCL_UCL_H
