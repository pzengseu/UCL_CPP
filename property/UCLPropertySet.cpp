//
// Created by zp on 12/17/16.
//
#include <bitset>
#include <cassert>
#include "UCLPropertySet.h"
#include "UCLPropertiesInfo.h"
#include "../UCL/UCL.h"

bool UCLPropertySet::setPropertyHead(UCLPropertyHead propertyHead)
{
    this->propertyHead = propertyHead;
}

const UCLPropertyHead& UCLPropertySet::getPropertyHead() const
{
    return propertyHead;
}

const map<int, UCLPropertyBase> &UCLPropertySet::getProperties() const {
    return properties;
}

void UCLPropertySet::setProperties(const map<int, UCLPropertyBase> &properties) {
    UCLPropertySet::properties = properties;
}

void UCLPropertySet::setHeadCategory(uint8_t category)
{
    propertyHead.setCategory(category);
}

uint8_t UCLPropertySet::getHeadCategory()
{
    return propertyHead.getCategory();
}

void UCLPropertySet::setHeadHelper(uint8_t helper)
{
    propertyHead.setHelper(helper);
}

uint8_t UCLPropertySet::getHeadHelper()
{
    return propertyHead.getHelper();
}

bool UCLPropertySet::setProperty(UCLPropertyBase property)
{
    properties[property.getCategory()] = property;
    setSet();
}

bool UCLPropertySet::delProperty(uint8_t category)
{
    properties.erase(category);
    setSet();
}

UCLPropertyBase UCLPropertySet::getProperty(uint8_t category)
{
    assert(properties.find(category) != properties.end());
    return properties[category];
}

void UCLPropertySet::setPropertyVPart(int pos, string value)
{
    assert(properties.find(pos)!=properties.end());
    properties[pos].setVPart(value);
    setSet();
}

string UCLPropertySet::getPropertyVPart(int pos)
{
//    assert(properties.find(pos)!=properties.end());
    return properties[pos].getVPart();
}

uint16_t UCLPropertySet::generateQuickMatcher()
{
    bitset<16> qmb;
    map<int, UCLPropertyBase >::iterator iter = properties.begin();
    for(; iter != properties.end(); iter++)
    {
        qmb.set(iter->first);
    }

    return qmb.to_ulong();

}

string UCLPropertySet::generateHeadVPart()
{
    bitset<16> qmb(propertyHead.getQuickMatcher());
    string value="";

    for(int i=0; i < 16; i++)
    {
        if(qmb.test(i))
        {
            value += properties[i].pack();
        }
    }

    return value;
}

void UCLPropertySet::setSet()
{
    propertyHead.setQuickMatcher(generateQuickMatcher());
    propertyHead.setVPart(generateHeadVPart());
    propertyHead.setQuickMatcher(generateQuickMatcher());
//    propertyHead.setTotalLength();
}

string UCLPropertySet::pack()
{
    return propertyHead.pack();
}

void UCLPropertySet::unpack(string propertySet)
{
    propertyHead.unpack(propertySet);
    bitset<16> bqm(propertyHead.getQuickMatcher());
    string headVPart = propertyHead.getVPart();
    uint32_t tmp = 0;
    for(int i=0; i < bqm.size(); i++)
    {
        if(bqm.test(i))        {
            //计算属性元素长度值字段字节数
            int lValueBytes = (int)(headVPart[1+tmp] >> 6) + 1;
            //取出长度值字段
            string lValue = headVPart.substr(2+tmp, lValueBytes);
            uint32_t lValueNum = 0;
            for(int j=0; j < lValue.size(); j++)
            {
                switch (j)
                {
                    case 0:
                        lValueNum = (0xffffff00 & lValueNum) | (lValue[j] & 0xff);
                        break;
                    case 1:
                        lValueNum = (0xffff00ff & lValueNum) | ((lValue[j] & 0xff)<<8);
                        break;
                    case 2:
                        lValueNum = (0xff00ffff & lValueNum) | ((lValue[j] & 0xff)<<16);
                        break;
                    case 3:
                        lValueNum = (0xff00ffff & lValueNum) | ((lValue[j] & 0xff)<<24);
                        break;
                }
            }
            string property = headVPart.substr(tmp, lValueNum);
            UCLPropertyBase pro;
            pro.unpack(property);
            properties[i] = pro;
            tmp += lValueNum;
        }
    }
}

void UCLPropertySet::showPropertySet()
{
    if (propertyHead.getCategory() == 1 || propertyHead.getCategory() == 15) {
        cout << "属性集合名: " << UPI.getPropertySetCategory(propertyHead.getCategory()) << endl;
        cout << "属性集类别: " << (int)propertyHead.getCategory() << "    属性个数: " << dec << (int)propertyHead.getSize() <<endl;
        map<int, UCLPropertyBase>::iterator property = properties.begin();
        for (; property != properties.end(); property++) {
            cout << "属性类别: "<<(int)property->second.getCategory()<<"    属性名: "
                 <<UPI.getPropertyCategroy(propertyHead.getCategory(), property->second.getCategory()) << endl;
            UPI.showProperty(propertyHead.getCategory(), property->second);
            cout << "------------------------------------" << endl;
        }
    }
    else
    {
        cout << "自定义属性集合" << endl;
        cout << "属性集类别: " << (int)propertyHead.getCategory() << "    属性个数: " << (int)propertyHead.getSize()<<endl;
        map<int, UCLPropertyBase>::iterator property = properties.begin();
        for (; property != properties.end(); property++) {
            cout << "属性类别和属性值: " << (int) property->second.getCategory() << "   "
                 << property->second.getVPart() << endl;
            cout << "------------------------------------" << endl;
        }
    }
}