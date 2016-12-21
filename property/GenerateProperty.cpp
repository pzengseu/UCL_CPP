#include <cstdint>
#include <cassert>
#include "UCLPropertyBase.h"
#include "GenerateProperty.h"

//
// Created by zp on 12/21/16.
//

void GenerateProperty::setProperty(UCLPropertyBase &property, uint8_t category, uint8_t helper, string vPart)
{
    assert(helper < 16);
    property.setCategory(category);
    property.setHelper(helper);
    property.setVPart(vPart);
    property.setTotalLength();
}

//SNPS
UCLPropertyBase GenerateProperty::generateSNPSPE(uint8_t quickMatcher, string vPart, uint8_t helper)
{
    UCLPropertyBase pe;

    assert(quickMatcher<=0x3f);
    pe.setLPartHead(0, 5, quickMatcher);

    setProperty(pe, 0x1, helper, vPart);
    return pe;
}

UCLPropertyBase GenerateProperty::generateSNPSNR(string vPart, uint8_t helper)
{
    UCLPropertyBase nr;
    setProperty(nr, 0x2, helper, vPart);

    return nr;
}

//CDPS
UCLPropertyBase GenerateProperty::generateCDPSTitle(string vPart, uint8_t helper)
{
    UCLPropertyBase title;
    setProperty(title, 0x1, helper, vPart);

    return title;
}

UCLPropertyBase GenerateProperty::generateCDPSKeywords(uint8_t count, string vPart, uint8_t helper)
{
    assert(count <= 16 && count > 0);
    UCLPropertyBase keywords;
    keywords.setLPartHead(2, 5, count-1);

    setProperty(keywords, 0x2, helper, vPart);
    return keywords;
}

UCLPropertyBase GenerateProperty::generateCDPSAbstract(string vPart, uint8_t helper)
{
    UCLPropertyBase abstract;
    setProperty(abstract, 0x3, helper, vPart);

    return abstract;
}

UCLPropertyBase GenerateProperty::generateCDPSAuthor(uint8_t persons, uint8_t companies, string vPart, uint8_t helper)
{
    persons = persons>7?7:persons;
    companies = companies>7?7:companies;

    UCLPropertyBase author;
    author.setLPartHead(0, 2, persons);
    author.setLPartHead(3, 5, companies);

    setProperty(author, 4, helper, vPart);
    return author;
}

UCLPropertyBase GenerateProperty::generateCDPSEntity(uint8_t count, string vPart, uint8_t helper)
{
    assert(count <= 16 && count > 0);

    UCLPropertyBase entity;
    entity.setLPartHead(2, 5, count-1);
    setProperty(entity, 5, helper, vPart);

    return entity;
}

UCLPropertyBase GenerateProperty::generateCDPSCopyright(string vPart, uint8_t helper)
{
    UCLPropertyBase copyright;
    setProperty(copyright, 6, helper, vPart);

    return copyright;
}

UCLPropertyBase GenerateProperty::generateCDPSOriginality(string vPart, uint8_t helper)
{
    UCLPropertyBase originality;
    setProperty(originality, 7, helper, vPart);

    return originality;
}

UCLPropertyBase GenerateProperty::generateCDPSFileDescription(string vPart, uint8_t helper)
{
    UCLPropertyBase file;
    setProperty(file, 8, helper, vPart);

    return file;
}



//CGPS
UCLPropertyBase GenerateProperty::generateCGPSProvenance(uint8_t des, string vPart, uint8_t helper)
{
    assert(des < 8);
    UCLPropertyBase provenance;
    provenance.setLPartHead(3, 5, des);
    setProperty(provenance, 0x3, helper, vPart);

    return  provenance;
}

UCLPropertyBase GenerateProperty::generateCGPSContentid(string vPart, uint8_t helper)
{
    UCLPropertyBase contentid;
    setProperty(contentid, 0x4, helper, vPart);

    return contentid;
}

UCLPropertyBase GenerateProperty::generateCGPSPropagation(uint8_t count, string vPart, uint8_t helper)
{
    assert(count <=16 && count > 0);

    UCLPropertyBase propagation;
    propagation.setLPartHead(3, 5, count-1);

    setProperty(propagation, 5, helper, vPart);

    return propagation;
}

UCLPropertyBase GenerateProperty::generateCGPSSignatureContent(uint8_t alg, string vPart, uint8_t helper)
{
    assert(helper < 5);
    assert(alg < 5);

    UCLPropertyBase signature;
    signature.setLPartHead(3, 5, alg);
    setProperty(signature, 12, helper, vPart);

    return signature;
}

UCLPropertyBase GenerateProperty::generateCGPSSecurity(string vPart, uint8_t helper)
{
    assert(helper == 0 || helper == 1 || helper == 2 || helper == 14);

    UCLPropertyBase security;
    setProperty(security, 13, helper, vPart);

    return security;
}

UCLPropertyBase GenerateProperty::generateCGPSChain(uint8_t count, string vPart, uint8_t helper)
{
    assert(count <= 8 && count >=1);

    UCLPropertyBase chain;
    chain.setLPartHead(3, 5, count-1);
    setProperty(chain, 14, helper, vPart);

    return chain;
}

UCLPropertyBase GenerateProperty::generateCGPSSignatureUCL(uint8_t alg, string vPart, uint8_t helper)
{
    assert(helper < 5);
    assert(alg < 5);

    UCLPropertyBase signature;
    signature.setLPartHead(3, 5, alg);
    setProperty(signature, 15, helper, vPart);

    return signature;
}

//生成必选集合
UCLPropertySet GenerateProperty::generateCDPS(string title)
{
    UCLPropertySet cdps;
    cdps.setHeadCategory(0);

    UCLPropertyBase titlePro = generateCDPSTitle(title);
    cdps.setProperty(titlePro);
    cdps.setSet();

    return cdps;
}

UCLPropertySet GenerateProperty::generateCGPS(CGPSRequired required)
{
    UCLPropertySet cgps;
    cgps.setHeadCategory(15);

    UCLPropertyBase provenance = generateCGPSProvenance(required.proDes, required.provenance);
    cgps.setProperty(provenance);

    UCLPropertyBase security = generateCGPSSecurity(required.security, required.secHelper);
    cgps.setProperty(security);

    UCLPropertyBase chain = generateCGPSChain(required.chainCount, required.chain);
    cgps.setProperty(chain);

    UCLPropertyBase sigUCL = generateCGPSSignatureUCL(required.sigU[0], required.sigUCL, required.sigU[1]);
    cgps.setProperty(sigUCL);

    cgps.setSet();
    return cgps;
}