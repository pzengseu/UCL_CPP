#include <iostream>
#include <iomanip>
#include "property/UCLPropertyBase.h"
#include "property/UCLPropertyHead.h"
#include "property/SNPS.h"
#include "UCL.h"
#include <list>
using namespace std;

UCLPropertyBase testUCLPropertyBase();
void testUCLPropertyHead();

void testSNPSPhysicalElements();

int main() {
//    testUCLPropertyBase();
//    cout << "－－－－－－\n";
//    testUCLPropertyHead();
//    cout << "－－－－－－\n";
//    testSNPSPhysicalElements();
//    cout << "----------\n";

//    UCLPropertyBase base = testUCLPropertyBase();
//    UCL ucl;
//    ucl.generateSNPSSet();
//    map<int, UCLPropertySet> s = ucl.getPropertySets();
//    s[0].setHeadCategory(0x05);
//    cout << setbase(10) << s[0].getPropertyHead().getLPart();
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
    for(int i=0; i <= pack.size(); i++)
        cout << setbase(16) << (short)pack[i] << endl;

    UCLPropertyHead property2;
    property2.unpack(pack);
    cout << setbase(16) << (int)property2.getCategory() << ";";
    cout << setbase(16) << (int)property2.getHelper() << ";\nTPart: " << (int)property2.getTPart() << endl;
    cout << setbase(16) << "LPart: " << (int)property2.getLPart() << endl;
    cout << setbase(16) << property2.getVPart() << endl;

    return 0;
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