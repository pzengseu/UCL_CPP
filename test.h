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
    code_test.setPrecedence(15);
    code_test.setFlag(13);
    code_test.setParseRule(0xfff1);//ff1有效
    code_test.setSourOfCont(0xfffffff1);//ffffff1有效
    code_test.setCategory(255);
    code_test.setSubCategory(257);//0x01有效
    code_test.setTopic(0xffffff1);
    code_test.setTypeOfContent(254);
    code_test.setCopyAndLeng(252);
    code_test.setSecuEnerLeveCode(251);
    code_test.setTimeStamp(0x3ffffffffffff);
    code_test.setSerialNumber(0x3fffff);
    code_test.setReservedBytes(0xffffffffff);
    code_test.setVersion(3);//对于已经设置过的域重复设置

    ucl.setUclCode(code_test);

    UCLPropertySet snps;
    snps.setHeadCategory(0);
    UCLPropertyBase nr = GenerateProperty::generateSNPSNR("WuHan");
    snps.setProperty(nr);
    cout << "SNPS: \n";
    printPackString(snps.pack());

    UCLPropertySet cdps;
    cdps.setHeadCategory(1);
    UCLPropertyBase title = GenerateProperty::generateCDPSTitle("习近平：解决突出问题 推动六中全会精神落实处");
    cdps.setProperty(title);
//    cout << hex << cdps.generateQuickMatcher()<< "  " << cdps.getPropertyHead().getTotalLength() << endl;
    cout << "CDPS: \n";
    printPackString(cdps.pack());

    UCLPropertySet cgps;
    cgps.setHeadCategory(15);
    UCLPropertyBase sigUCL = GenerateProperty::generateCGPSSignatureUCL(3, "", 0);
    cgps.setProperty(sigUCL);
    cout << "CGPS: \n";
    printPackString(cgps.pack());

    ucl.setPropertySet(snps);
    ucl.setPropertySet(cdps);
    ucl.setPropertySet(cgps);
//    cout << hex << ucl.generateQuickMatcher()<< "  " << ucl.getUclPropertyHead().getTotalLength();
    cout << "propertySet: \n";
    printPackString(ucl.packPropertySets());
    cout << "UCLPackage: \n";
    printPackString(ucl.pack());
    ucl.showUCL();

    string ucl1 = ucl.pack();

    UCL ucl2;
    ucl2.unpack(ucl1);
    cout << "UCLPackage: \n";
    printPackString(ucl2.pack());
    ucl2.showUCL();
}

void testUCL()
{
    UCL ucl;
    UCLCode code_test;

    code_test.setVersion(1);
    code_test.setTypeOfMedia(9);
    code_test.setPrecedence(15);
    code_test.setFlag(13);
    code_test.setParseRule(0xfff1);//ff1有效
    code_test.setSourOfCont(0xfffffff1);//ffffff1有效
    code_test.setCategory(255);
    code_test.setSubCategory(257);//0x01有效
    code_test.setTopic(0xffffff1);
    code_test.setTypeOfContent(254);
    code_test.setCopyAndLeng(252);
    code_test.setSecuEnerLeveCode(251);
    code_test.setTimeStamp(0x3ffffffffffff);
    code_test.setSerialNumber(0x3fffff);
    code_test.setReservedBytes(0xffffffffff);
    code_test.setVersion(3);//对于已经设置过的域重复设置

    ucl.setUclCode(code_test);

    UCLPropertySet snps;
    snps.setHeadCategory(0);
    UCLPropertyBase nr = GenerateProperty::generateSNPSNR("WuHan");
    snps.setProperty(nr);
    cout << "SNPS: \n";
    printPackString(snps.pack());

    UCLPropertySet cdps = GenerateProperty::generateCDPS("SEU");
    UCLPropertyBase title = GenerateProperty::generateCDPSTitle("习近平：解决突出问题 推动六中全会精神落实处");
    UCLPropertyBase keywords = GenerateProperty::generateCDPSKeywords(3, "习近平;六中全会;中央党校");
    UCLPropertyBase author = GenerateProperty::generateCDPSAuthor(1, 1, "新华社:隗俊");
    UCLPropertyBase entity = GenerateProperty::generateCDPSEntity(1, "xjp");
    cdps.setProperty(title);
    cdps.setProperty(keywords);
    cdps.setProperty(author);
    cdps.setProperty(entity);
//    cout << hex << cdps.generateQuickMatcher()<< "  " << cdps.getPropertyHead().getTotalLength() << endl;

    cout << "CDPS: \n";
    printPackString(cdps.pack());

    CGPSRequired cr;
    cr.provenance = "www.sina.com";
    cr.proDes = 1;
    cr.security = "高";
    cr.secHelper = 0;
    cr.chain = "seu;thing";
    cr.chainCount = 2;
    cr.sigUCL = "";
    cr.sigU[0] = 3;
    cr.sigU[1] = 0;
    UCLPropertySet cgps = GenerateProperty::generateCGPS(cr);
    cout << "CGPS: \n";
    printPackString(cgps.pack());

    ucl.setPropertySet(snps);
    ucl.setPropertySet(cdps);
    ucl.setPropertySet(cgps);
//    cout << hex << ucl.generateQuickMatcher()<< "  " << ucl.getUclPropertyHead().getTotalLength();
    cout << "propertySet: \n";
    printPackString(ucl.packPropertySets());
    cout << "UCLPackage: \n";
    printPackString(ucl.pack());
    ucl.showUCL();

    string ucl1 = ucl.pack();
    //将ucl1写入文件
    fstream fout;
    fout.open("E:\\UCL_CPP\\hello.txt", ios::out);
    fout << ucl1;
    fout.close();
    //读取文件
    fstream fin("E:\\UCL_CPP\\hello.txt", ios::in);
    istreambuf_iterator<char>beg(fin), end;
    string uclS2(beg, end);

    UCL ucl2;
    ucl2.unpack(uclS2);
    cout << "UCLPackage: \n";
    printPackString(ucl2.pack());
    ucl2.showUCL();
}

UCLPropertySet testSetUnpack()
{
    UCLPropertyBase pe = GenerateProperty::generateSNPSPE(0xe, "我;爱;你");
    printPackString(pe.pack());

    UCLPropertyBase nr = GenerateProperty::generateSNPSNR("abc");
    printPackString(nr.pack());

    UCLPropertySet set0;
    set0.setHeadCategory(0x0);
    set0.setProperty(pe);
    set0.setProperty(nr);
    set0.setSet();
    printPackString(set0.pack());

    UCLPropertySet set1;
    set1.unpack(set0.pack());
    printPackString(set1.pack());
    return set1;
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

UCL testUCLPack()
{
    //SNPS
    UCLPropertyBase pe = GenerateProperty::generateSNPSPE(0xe, "我;爱;你");
    printPackString(pe.pack());

    UCLPropertyBase nr = GenerateProperty::generateSNPSNR("abc");
    printPackString(nr.pack());

    UCLPropertySet set0;
    set0.setHeadCategory(0x0);
    set0.setProperty(pe);
    set0.setProperty(nr);
    set0.setSet();
    printPackString(set0.pack());

    //CDPS
    UCLPropertyBase title = GenerateProperty::generateCDPSTitle("abc");
    printPackString(title.pack());

    UCLPropertyBase keywords = GenerateProperty::generateCDPSKeywords(3, "a;b;c");
    printPackString(keywords.pack());

    UCLPropertySet set1;
    set1.setHeadCategory(0x1);
    set1.setProperty(title);
    set1.setProperty(keywords);
    set1.setSet();
    printPackString(set1.pack());

    //CGPS
    UCLPropertyBase provenance = GenerateProperty::generateCGPSProvenance(0x2, "SEU");
    printPackString(provenance.pack());

    UCLPropertyBase contentId = GenerateProperty::generateCGPSContentid("/home/zp");
    printPackString(contentId.pack());

    UCLPropertySet set2;
    set2.setHeadCategory(15);
    set2.setProperty(provenance);
    set2.setProperty(contentId);
    set2.setSet();
    printPackString(set2.pack());

    UCL ucl;
    ucl.setPropertySet(set0);
    ucl.setPropertySet(set1);
    ucl.setPropertySet(set2);
    ucl.setUCL();
    printPackString(ucl.packPropertySets());

//    cout << ucl.getValue(0, 1) << endl;
//    map<int, UCLPropertySet> s = ucl.getPropertySets();
//    s[0].setHeadCategory(0x05);
//    cout << setbase(10) << s[0].getPropertyHead().getLPart();
    return ucl;
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
