//
// Created by zp on 12/20/16.
//

#ifndef UCL_CPP_TEST_H
#define UCL_CPP_TEST_H

#include <iomanip>
#include <iostream>
#include "property/UCLPropertyHead.h"
#include "property/SNPS.h"

using namespace std;

void printPackString(string pack);

void printPackString(string pack)
{
    for(int i=0; i <= pack.size(); i++)
        cout << setbase(16) << (short)pack[i] << endl;
    cout << "------------\n";
}

void testUCLPack()
{
    SNPSPhysicalElements pe;
    pe.setVPart(u8"我;爱;你");
    pe.setLPartQuickMatcher(0x7);
    pe.setTotalLength();
    printPackString(pe.pack());

    UCLPropertySet set0;
    set0.setHeadCategory(0x0);
    set0.setProperty(&pe);
    set0.setSet();
    printPackString(set0.pack());

    UCL ucl;
    ucl.setPropertySet(set0);
    ucl.setUCL();
    printPackString(ucl.pack());

    cout << ucl.getValue(0, 2) << endl;
    map<int, UCLPropertySet> s = ucl.getPropertySets();
    s[0].setHeadCategory(0x05);
    cout << setbase(10) << s[0].getPropertyHead().getLPart();
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

void testSNPSPhysicalElements() {
    SNPSPhysicalElements property;
    property.setHelper(0x5);
//    propertyBase.setLPartHead(0xff);
    property.setLPartQuickMatcher(0x2a);
    property.setVPart("physical elements");
    property.setTotalLength();

    cout << setbase(16) << (int)property.getCategory() << ";";
    cout << setbase(16) << (int)property.getHelper() << ";\nTPart: " << (int)property.getTPart() << endl;
    cout << setbase(16) << "LPart: " << (int)property.getLPart() << endl; //142a
    cout << setbase(16) << property.getVPart() << endl;
    cout << (int)property.getSize() << endl;
    cout << (int)property.getLPartBytesNum() << endl;
}
#endif //UCL_CPP_TEST_H
