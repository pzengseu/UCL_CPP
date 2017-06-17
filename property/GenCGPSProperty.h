//
// Created by zp on 17-6-17.
//

#ifndef UCL_CPP_GENCGPSPROPERTY_H
#define UCL_CPP_GENCGPSPROPERTY_H

#include "UCLPropertyBase.h"

/**
 *  CGPS, provenance, content id, propagation path, signature of content, security energy level information,
 *  chain of responibility, signature of UCL Package
 */
class GenCGPSProperty {
public:
    //provenance
    static UCLPropertyBase genProvenance(uint8_t des, string vPart, uint8_t helper=0);

    //content id
    static UCLPropertyBase genContId(string vPart, uint8_t helper=1);

    //propagation path
    static UCLPropertyBase genPropagation(uint8_t count, string vPart, uint8_t helper=0);

    //signature of content
    static UCLPropertyBase genContSig(string content, uint8_t alg, uint8_t helper=0);

    //security
    static UCLPropertyBase genSecEL(string vPart, uint8_t helper=0);

    //chain of responsibility
    static UCLPropertyBase genChainOfRes(uint8_t count, string vPart, uint8_t helper=0);

    //signature of UCL package
    static UCLPropertyBase genUCLSig(uint8_t alg, uint8_t helper=0);
};


#endif //UCL_CPP_GENCGPSPROPERTY_H
