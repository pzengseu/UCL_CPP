//
// Created by zp on 17-6-17.
//

#ifndef UCL_CPP_GENCDPSPROPERTY_H
#define UCL_CPP_GENCDPSPROPERTY_H

#include "UCLPropertyBase.h"

/**
 * CDPS, title, keywords, abstract, author, entity, Tag, copyright,  originality, file Description
 */
class GenCDPSProperty
{
public:
    //title
    static UCLPropertyBase genTitle(string vPart, uint8_t helper=0);

    //keywords
    static UCLPropertyBase genKeywords(uint8_t count, string vPart, uint8_t helper=0);

    //abstract
    static UCLPropertyBase genAbstract(string vPart, uint8_t helper=0);

    //author
    static UCLPropertyBase genAuthor(uint8_t persons, uint8_t companies, string vPart, uint8_t helper=0);

    //entity
    static UCLPropertyBase genEntity(uint8_t count, string vPart, uint8_t helper=0);

    //Tag
    static UCLPropertyBase genTag(uint8_t count, string vPart, uint8_t helper=0);

    //copyright
    static UCLPropertyBase genCopyright(string vPart, uint8_t helper=0);

    //originality
    static UCLPropertyBase genOriginality(string vPart, uint8_t helper=0);

    //file description
    static UCLPropertyBase genFileDescription(string vPart, uint8_t helper=0);

    //Related UCL
    static UCLPropertyBase genRelatedUCL(uint8_t count, string vPart, uint8_t helper=0);

    //Content Object
    static UCLPropertyBase genContObject(string vPart, uint8_t helper=0);
};
#endif //UCL_CPP_GENCDPSPROPERTY_H
