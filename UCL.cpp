//
// Created by zp on 12/17/16.
//

#include <map>
#include "property/UCLPropertyHead.h"
#include "UCL.h"

const UCLPropertyHead &UCL::getUclPropertyHead() const {
    return uclPropertyHead;
}

void UCL::setUclPropertyHead(const UCLPropertyHead &uclPropertyHead) {
    UCL::uclPropertyHead = uclPropertyHead;
}

void UCL::generateSNPSSet()
{
    UCLPropertySet snps;
    snps.setHeadCategory(0x0);
    snps.setMustToDo();
    propertySets.insert(make_pair(0, snps));
}

const map<int, UCLPropertySet> &UCL::getPropertySets() const {
    return propertySets;
}

void UCL::setPropertySets(const map<int, UCLPropertySet> &propertySets) {
    UCL::propertySets = propertySets;
}
