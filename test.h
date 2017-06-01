//
// Created by zp on 12/20/16.
//

#ifndef UCL_CPP_TEST_H
#define UCL_CPP_TEST_H

#include <iomanip>
#include <fstream>
#include <iostream>
#include "property/UCLPropertyHead.h"
#include "property/UCLPropertySet.h"
#include "UCL.h"
#include "property/GenerateProperty.h"
#include <sstream>
#include "property/GenerateProperty.h"

using namespace std;
void printPackString(string pack);

void testEasy()
{
    UCL ucl;
    UCLCode code_test;

    code_test.setVersion(1);
    code_test.setTypeOfMedia(9);
    code_test.setPrioAndPoli(15);
    code_test.setFlag(13);
    code_test.setParseRule(0xfff1);//ff1有效
    code_test.setSourOfCont(0xfffffff1);//ffffff1有效
    code_test.setCategory(255);
    code_test.setSubCategory(257);//0x01有效
    code_test.setTopic(0xffffff1);
    code_test.setCopyAndTypeOfCont(254);
    code_test.setSecuEnerLeveCode(251);
    code_test.setLanguage(253);
    code_test.setSizeOfContent(31);
    code_test.setTimeStamp(0x3fffffffff9f9);
    /*
     * serinal number and multiplex bytes test cases
     * 0xCff1f3 - 0x8fffff31; 0x8f1f - 0x1f3f5f7f9f; 0x4f - 0x1f3f5f7f9f48; 0xf - 0x1f3f5f7f9f48
     */
    code_test.setSerialNumber(0x4f);
    code_test.setMultiplexBytes(0x1f3f5f7f9f48);

    code_test.setVersion(3);//对于已经设置过的域重复设置

    ucl.setUclCode(code_test);

//    UCLPropertySet snps;
//    snps.setHeadCategory(0);
//    UCLPropertyBase nr = GenerateProperty::generateSNPSNR("WuHan");
//    snps.setProperty(nr);
//    cout << "SNPS: \n";
//    printPackString(snps.pack());

    UCLPropertySet cdps;
    cdps.setHeadCategory(1);
    UCLPropertyBase title = GenerateProperty::generateCDPSTitle("江苏今年起实施“12311”计划 培育百个农业特色镇");
    UCLPropertyBase keywords = GenerateProperty::generateCDPSKeywords(3, "江苏;乡村;国家");
    UCLPropertyBase abstract = GenerateProperty::generateCDPSAbstract("省农委日前在金坛召开全省创意休闲农业工作推进会，决定从今年起实施“12311”创意休闲农业省级特色品牌培育计划");
    UCLPropertyBase author = GenerateProperty::generateCDPSAuthor(2, 2, "邹建丰:新华日报\\r微博;博客:新浪");
    UCLPropertyBase entity = GenerateProperty::generateCDPSEntity(31, "江苏省委\\r2017\\r金坛\\r培育计划\\r美丽");
    UCLPropertyBase tag = GenerateProperty::generateCDPSTag(2, "美丽;乡村");
    UCLPropertyBase copyright = GenerateProperty::generateCDPSCopyright("新华日报");
    UCLPropertyBase origin = GenerateProperty::generateCDPSOriginality("皱建丰");
    UCLPropertyBase file = GenerateProperty::generateCDPSFileDescription("文本;10M");
    UCLPropertyBase related = GenerateProperty::generateCDPSRelatedUCL(3, "ucl1;ucl2;ucl3");
    UCLPropertyBase content = GenerateProperty::generateCDPSContentObject("江苏今年起实施“12311”计划, 全省创意休闲农业工作推进会");
    cdps.setProperty(title);
    cdps.setProperty(keywords);
    cdps.setProperty(abstract);
    cdps.setProperty(author);
    cdps.setProperty(entity);
    cdps.setProperty(tag);
    cdps.setProperty(copyright);
    cdps.setProperty(origin);
    cdps.setProperty(file);
    cdps.setProperty(related);
    cdps.setProperty(content);
//    cout << hex << cdps.generateQuickMatcher()<< "  " << cdps.getPropertyHead().getTotalLength() << endl;
    cout << "CDPS: \n";
    printPackString(cdps.pack());

    ucl.setPropertySet(cdps);

    UCLPropertySet cgps;
    cgps.setHeadCategory(15);
    UCLPropertyBase pro = GenerateProperty::generateCGPSProvenance(1, "http://jiangsu.sina.com.cn/news/b/2017-05-31/detail-ifyfqqyh9080015.shtml");
    cgps.setProperty(pro);
    UCLPropertyBase contentid = GenerateProperty::generateCGPSContentid("sina");
    cgps.setProperty(contentid);
    UCLPropertyBase prog = GenerateProperty::generateCGPSPropagation(2, "baidu;sina");
    cgps.setProperty(prog);
    UCLPropertyBase sigCon = GenerateProperty::generateCGPSSignatureContent("江苏今年起实施“12311”计划, 全省创意休闲农业工作推进会", 3, 0);
    cgps.setProperty(sigCon);
    UCLPropertyBase security = GenerateProperty::generateCGPSSecurity("重要");
    cgps.setProperty(security);
    UCLPropertyBase chain = GenerateProperty::generateCGPSChain(2, "sian;seu");
    cgps.setProperty(chain);
    UCLPropertyBase sigUCL = GenerateProperty::generateCGPSSignatureUCL(3, 0);
    cgps.setProperty(sigUCL);
    cout << "CGPS: \n";
    printPackString(cgps.pack());

    ucl.setPropertySet(cgps);
//    cout << hex << ucl.generateQuickMatcher()<< "  " << ucl.getUclPropertyHead().getTotalLength();
    cout << "propertySet: \n";
    printPackString(ucl.packPropertySets());
    cout << "UCLPackage: \n";
    printPackString(ucl.pack());
    ucl.getUclCode().showCode();
    ucl.showUCL();

    string ucl1 = ucl.pack();

    UCL ucl2;
    ucl2.unpack(ucl1);
    cout << "UCLPackage: \n";
    printPackString(ucl2.pack());
    ucl2.getUclCode().showCode();
    ucl2.showUCL();
}

void printPackString(string pack)
{
//    ostringstream ostr;
    for(int i=0; i <= pack.size(); i++) {
//        ostr<<hex << (uint16_t)pack[i] << "-";
        cout << setw(2) << setfill('0') << hex << ((uint16_t)pack[i] & 0xff) << "-";

    }
//    string s=ostr.str();
//    cout<<"UCL:"<<s<<endl;
//    cout<<"MD5:"<<getMD5(s);
    cout << "\n------------\n";
}

void testPropertyPack()
{
    UCLPropertyHead property;
    property.setCategory(0x1);
    property.setHelper(0xa);
    property.setLPartHead(0x21);
    property.setQuickMatcherBytesNum();
    property.setQuickMatcher(0x23ab);
    cout << setbase(16) << (int)property.getQuickMatcher() << endl;
    property.setVPart(u8"abc");
    property.setTotalLength();

    cout << setbase(16) << (int)property.getCategory() << ";";
    cout << setbase(16) << (int)property.getHelper() << ";\nTPart: " << (int)property.getTPart() << endl;
    cout << setbase(16) << "LPart: " << (int)property.getLPart() << endl;
    cout << setbase(16) << property.getVPart() << endl;
    cout << "pack----------\n";
    string pack = property.pack();
//    for(int i=0; i <= pack.size(); i++)
//        cout << setbase(16) << (short)pack[i] << endl;

    UCLPropertyHead property2;
    property2.unpack(pack);
    cout << setbase(16) << (int)property2.getCategory() << ";";
    cout << setbase(16) << (int)property2.getHelper() << ";\nTPart: " << (int)property2.getTPart() << endl;
    cout << setbase(16) << "LPart: " << (int)property2.getLPart() << endl;
    cout << setbase(16) << property2.getVPart() << endl;
}

UCLPropertyBase testUCLPropertyBase()
{
    UCLPropertyBase propertyBase;
    propertyBase.setCategory(0xe);
    propertyBase.setHelper(0x5);
//    propertyBase.setLPartHead(0xff);
    propertyBase.setVPart("Base");
    propertyBase.setTotalLength();

    cout << setbase(16) << (int)propertyBase.getCategory() << ";";
    cout << setbase(16) << (int)propertyBase.getHelper() << ";\nTPart: " << (int)propertyBase.getTPart() << endl;
    cout << setbase(16) << "LPart: " << (int)propertyBase.getLPart() << endl; //700
    cout << setbase(16) << propertyBase.getVPart() << endl;

    return propertyBase;
}

void testUCLPropertyHead()
{
    UCLPropertyHead property;
    property.setCategory(0xe);
    property.setHelper(0x5);
//    propertyBase.setLPartHead(0xff);
    property.setQuickMatcherBytesNum(2);
    property.setQuickMatcher(0x23fa);
    property.setVPart("Head");
    property.setTotalLength();

    cout << setbase(16) << (int)property.getCategory() << ";";
    cout << setbase(16) << (int)property.getHelper() << ";\nTPart: " << (int)property.getTPart() << endl;
    cout << setbase(16) << "LPart: " << (int)property.getLPart() << endl; //23fa0924
    cout << setbase(16) << property.getVPart() << endl;
    cout<<(int)property.getSize()<<endl;
}
#endif //UCL_CPP_TEST_H
