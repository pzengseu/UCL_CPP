//
// Created by zp on 17-6-17.
//

#include <assert.h>
#include "GenCGPSProperty.h"
#include "../UCL/UCL.h"

UCLPropertyBase GenCGPSProperty::genProvenance(uint8_t des, string vPart, uint8_t helper)
{
    assert(des < 8);
    UCLPropertyBase provenance;
    provenance.setLPartHead(3, 5, des);
    provenance.setProperty(0x3, helper, vPart);

    return  provenance;
}

UCLPropertyBase GenCGPSProperty::genContId(string vPart, uint8_t helper)
{
    UCLPropertyBase contentid;
    contentid.setProperty(0x4, helper, vPart);

    return contentid;
}

UCLPropertyBase GenCGPSProperty::genPropagation(uint8_t count, string vPart, uint8_t helper)
{
    assert(count > 0);
    if (count > 15) count = 16;

    UCLPropertyBase propagation;
    propagation.setLPartHead(2, 5, count-1);

    propagation.setProperty(5, helper, vPart);

    return propagation;
}

UCLPropertyBase GenCGPSProperty::genContSig(string content, uint8_t alg, uint8_t helper)
{
    assert(helper <= 5);
    assert(alg < 5);

    UCLPropertyBase signature;
    signature.setLPartHead(2, 5, alg);

    string hash = UCL::genHash(alg, content);
    string signCont = UCL::genSig(helper, hash);
    signature.setProperty(12, helper, signCont);

    return signature;
}

UCLPropertyBase GenCGPSProperty::genSecEL(string vPart, uint8_t helper)
{
    assert(helper == 0 || helper == 1 || helper == 2 || helper == 14);

    UCLPropertyBase security;
    security.setProperty(13, helper, vPart);

    return security;
}

UCLPropertyBase GenCGPSProperty::genChainOfRes(uint8_t count, string vPart, uint8_t helper)
{
    assert(count >=1);
    if (count > 15) count = 16;

    UCLPropertyBase chain;
    chain.setLPartHead(2, 5, count-1);
    chain.setProperty(14, helper, vPart);

    return chain;
}

UCLPropertyBase GenCGPSProperty::genUCLSig(uint8_t alg, uint8_t helper)
{
    assert(helper <= 5);
    assert(alg < 5);

    UCLPropertyBase signature;
    signature.setLPartHead(2, 5, alg);
    signature.setProperty(15, helper, "");

    return signature;
}
