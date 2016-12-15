#include <iostream>
#include <iomanip>
#include "property/UCLPropertyBase.h"
#include "property/UCLPropertyHead.h"
#include "property/SNPS.h"
using namespace std;

void testUCLPropertyBase();
void testUCLPropertyHead();

void testSNPSPhysicalElements();

int main() {
    testUCLPropertyBase();
    cout << "－－－－－－\n";
    testUCLPropertyHead();
    cout << "－－－－－－\n";
    testSNPSPhysicalElements();
    return 0;
}
void testUCLPropertyBase()
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
    property.setCategory(0x1);
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