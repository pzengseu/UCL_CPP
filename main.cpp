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
    testUCLPropertyHead();
    testSNPSPhysicalElements();
    return 0;
}
void testUCLPropertyBase()
{
    UCLPropertyBase propertyBase;
    propertyBase.setCategory(0xe);
    propertyBase.setHelp(0x5);
//    propertyBase.setLPartHead(0xff);
    propertyBase.setVPart("world");
    propertyBase.setTotalLength();

    cout<<setbase(16)<<(int)propertyBase.getCategory()<<";";
    cout<<setbase(16)<<(int)propertyBase.getHelp()<<";"<<(int)propertyBase.getTPart()<<endl;
    cout<<setbase(16)<<(int)propertyBase.getLPart()<<endl;
    cout<<setbase(16)<<propertyBase.getVPart()<<endl;
}

void testUCLPropertyHead()
{
    UCLPropertyHead property;
    property.setCategory(0xe);
    property.setHelp(0x5);
//    propertyBase.setLPartHead(0xff);
    property.setQuickMatcherBytesNum(2);
    property.setQuickMatcher(0x23fa);
    property.setVPart("world");
    property.setTotalLength();

    cout<<setbase(16)<<(int)property.getCategory()<<";";
    cout<<setbase(16)<<(int)property.getHelp()<<";"<<(int)property.getTPart()<<endl;
    cout<<setbase(16)<<(int)property.getLPart()<<endl;
    cout<<setbase(16)<<property.getVPart()<<endl;
    cout<<(int)property.getLPartBytesNum();
}

void testSNPSPhysicalElements() {
    SNPSPhysicalElements property;
    property.setCategory(0x1);
    property.setHelp(0x5);
//    propertyBase.setLPartHead(0xff);
    property.setQuickMatcherBytesNum(1);
    property.setQuickMatcher(0xfa);
    property.setVPart("world");
    property.setTotalLength();

    cout<<setbase(16)<<(int)property.getCategory()<<";";
    cout<<setbase(16)<<(int)property.getHelp()<<";"<<(int)property.getTPart()<<endl;
    cout<<setbase(16)<<(int)property.getLPart()<<endl;
    cout<<setbase(16)<<property.getVPart()<<endl;
}
