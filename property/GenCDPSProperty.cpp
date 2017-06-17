//
// Created by zp on 17-6-17.
//

#include <assert.h>
#include "UCLPropertyBase.h"
#include "GenCDPSProperty.h"

UCLPropertyBase GenCDPSProperty::genTitle(string vPart, uint8_t helper)
{
    UCLPropertyBase title;
    title.setProperty(0x1, helper, vPart);

    return title;
}

/*
第一子分量，长度头部字节，它的 0 ～ 7 位含义如下：
第 0 ～ 2 位保留，含义暂未定义；
第 3 ～ 5 位，其值加 1 表示内容关键词个数，一般不超过 5 个， 111 表示超过 7 个；
第 6 ～ 7 位，其值加 1 表示长度值子分量所占字节数， 10、 11 为非法取值                                                                                                                                                                                  
 */
UCLPropertyBase GenCDPSProperty::genKeywords(uint8_t count, string vPart, uint8_t helper)
{
    assert(count > 0);
    if (count > 7) count = 8;
    UCLPropertyBase keywords;
    keywords.setLPartHead(3, 5, count-1);

    keywords.setProperty(0x2, helper, vPart);
    return keywords;
}

UCLPropertyBase GenCDPSProperty::genAbstract(string vPart, uint8_t helper)
{
    UCLPropertyBase abstract;
    abstract.setProperty(0x3, helper, vPart);

    return abstract;
}
/*
第一子分量，长度头部字节，它的 0 ～ 7 位含义如下：
第 0 ～ 2 位，其值表示作者人数， 111 表示超过 6 个；
第 3 ～ 5 位，其值表示作者单位个数， 111 表示超过 6 个；
第 6 ～ 7 位，其值加 1 表示长度值子分量所占字节数， 10、 11 为非法取值。                                                                                                                                                                                  
 */
UCLPropertyBase GenCDPSProperty::genAuthor(uint8_t persons, uint8_t companies, string vPart, uint8_t helper)
{
    assert(persons>=0 && companies>=0);
    persons = persons>7?7:persons;
    companies = companies>7?7:companies;

    UCLPropertyBase author;
    author.setLPartHead(0, 2, persons);
    author.setLPartHead(3, 5, companies);

    author.setProperty(0x4, helper, vPart);
    return author;
}

/*
第一子分量，长度头部字节，它的 0 ～ 7 位含义如下：
第 0 ～ 5 位，表示速配信息，快速指示具体包含有哪些内容实体，
若其中的第 X 位（0 ≤ X ≤ 5）取 1，表示后续有类别号为 X 的内容实体；
若其中的第 X 位（0 ≤ X ≤ 5）取 0，表示后续无类别号为 X 的内容实体。
第 6 ～ 7 位，其值加 1 表示长度值子分量所占字节数， 10、 11 为非法取值。                                                                                                                                                                                                                                     
 */
UCLPropertyBase GenCDPSProperty::genEntity(uint8_t quickMatch, string vPart, uint8_t helper)
{
    assert(quickMatch >= 0 && quickMatch <= 63);

    UCLPropertyBase entity;
    entity.setLPartHead(0, 5, quickMatch);
    entity.setProperty(0x5, helper, vPart);

    return entity;
}

/*
第一子分量，长度头部字节，它的 0 ～ 7 位含义如下：
第 0 ～ 2 位保留，含义暂未定义；
第 3 ～ 5 位，其值加 1 表示内容标记的个数，一般不超过 5 个， 111 表示超过 7 个；
第 6 ～ 7 位，其值加 1 表示长度值子分量所占字节数， 10、 11 为非法取值。                                                                                                                                                                                   
 */
UCLPropertyBase GenCDPSProperty::genTag(uint8_t count, string vPart, uint8_t helper)
{
    assert(count >=1);
    if (count > 7) count = 8;

    UCLPropertyBase tag;
    tag.setLPartHead(3, 5, count - 1);
    tag.setProperty(6, helper, vPart);

    return tag;
}

UCLPropertyBase GenCDPSProperty::genCopyright(string vPart, uint8_t helper)
{
    UCLPropertyBase copyright;
    copyright.setProperty(7, helper, vPart);

    return copyright;
}

UCLPropertyBase GenCDPSProperty::genOriginality(string vPart, uint8_t helper)
{
    UCLPropertyBase originality;
    originality.setProperty(8, helper, vPart);

    return originality;
}

UCLPropertyBase GenCDPSProperty::genFileDescription(string vPart, uint8_t helper)
{
    UCLPropertyBase file;
    file.setProperty(9, helper, vPart);

    return file;
}

/*
第一子分量，长度头部字节，它的 0 ～ 7 位含义如下：
第 0 ～ 2 位保留，含义暂未定义；
第 3 ～ 5 位，其值加 1 表示 UCL 的个数， 111 表示超过 7 个；
第 6 ～ 7 位，其值加 1 表示长度值子分量所占字节数， 10、 11 为非法取值。                                                                                                                                                                          
 */
UCLPropertyBase GenCDPSProperty::genRelatedUCL(uint8_t count, string vPart, uint8_t helper)
{
    assert(count >=1);
    if (count > 7) count = 8;

    UCLPropertyBase relatedUCL;
    relatedUCL.setLPartHead(3, 5, count - 1);
    relatedUCL.setProperty(14, helper, vPart);

    return relatedUCL;
}

UCLPropertyBase GenCDPSProperty::genContObject(string vPart, uint8_t helper)
{
    UCLPropertyBase contentObject;
    contentObject.setProperty(15, helper, vPart);

    return contentObject;
}
