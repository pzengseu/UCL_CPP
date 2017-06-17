//
// Created by zp on 12/21/16.
//
/**
 * @deprecated
 * GenerateProperty.h生成标准UCL定义的属性和必选属性集合，自定义属性或属性集合可参考该类自定义实现
 */
#ifndef UCL_CPP2_GENERATEPROPERTY_H
#define UCL_CPP2_GENERATEPROPERTY_H

#include "UCLPropertyBase.h"
#include "UCLPropertySet.h"

//生成CGPS集合必选元素所需变量
//struct CGPSRequired
//{
//    string provenance;
//    uint8_t proDes;
//    string security;
//    uint8_t secHelper;
//    string chain;
//    int8_t chainCount;
//    string sigUCL;
//    uint8_t sigU[2];
//};

//根据每个属性的不同,生成相应属性
class GenerateProperty
{
public:
    static void setProperty(UCLPropertyBase &property, uint8_t category, uint8_t help, string vPart);
    /*
     * SNPS, PhysicalElements, Receiver, the set had been deleted
     */
    //PhysicalElements
//    static UCLPropertyBase generateSNPSPE(uint8_t quickMatcher, string vPart, uint8_t helper=0);
//
//    //Nominated Receiver
//    static UCLPropertyBase generateSNPSNR(string vPart, uint8_t helper=0);

    /*
     * CDPS, title, keywords, abstract, author, entity, Tag, copyright,  originality, file Description
     */
    //title
    static UCLPropertyBase generateCDPSTitle(string vPart, uint8_t helper=0);

    //keywords
    static UCLPropertyBase generateCDPSKeywords(uint8_t count, string vPart, uint8_t helper=0);

    //abstract
    static UCLPropertyBase generateCDPSAbstract(string vPart, uint8_t helper=0);

    //author
    static UCLPropertyBase generateCDPSAuthor(uint8_t persons, uint8_t companies, string vPart, uint8_t helper=0);

    //entity
    static UCLPropertyBase generateCDPSEntity(uint8_t count, string vPart, uint8_t helper=0);

    //Tag
    static UCLPropertyBase generateCDPSTag(uint8_t count, string vPart, uint8_t helper=0);

    //copyright
    static UCLPropertyBase generateCDPSCopyright(string vPart, uint8_t helper=0);

    //originality
    static UCLPropertyBase generateCDPSOriginality(string vPart, uint8_t helper=0);

    //file description
    static UCLPropertyBase generateCDPSFileDescription(string vPart, uint8_t helper=0);

    //Related UCL
    static UCLPropertyBase generateCDPSRelatedUCL(uint8_t count, string vPart, uint8_t helper=0);

    //Content Object
    static UCLPropertyBase generateCDPSContentObject(string vPart, uint8_t helper=0);

    /*
     * CGPS, provenance, content id, propagation path, signature of content, security energy level information,
     *       chain of responibility, signature of UCL Package
     */
    //provenance
    static UCLPropertyBase generateCGPSProvenance(uint8_t des, string vPart, uint8_t helper=0);

    //content id
    static UCLPropertyBase generateCGPSContentid(string vPart, uint8_t helper=1);

    //propagation path
    static UCLPropertyBase generateCGPSPropagation(uint8_t count, string vPart, uint8_t helper=0);

    //signature of content
    static UCLPropertyBase generateCGPSSignatureContent(string content, uint8_t alg, uint8_t helper=0);

    //security
    static UCLPropertyBase generateCGPSSecurity(string vPart, uint8_t helper=0);

    //chain of responsibility
    static UCLPropertyBase generateCGPSChain(uint8_t count, string vPart, uint8_t helper=0);

    //signature of UCL package
    static UCLPropertyBase generateCGPSSignatureUCL(uint8_t alg, uint8_t helper=0);

    //生成必选集合
//    static UCLPropertySet generateCDPS(string title);
//    static UCLPropertySet generateCGPS(CGPSRequired required);
};
#endif //UCL_CPP2_GENERATEPROPERTY_H
