//
// Created by zp on 12/12/16.
//

#ifndef UCL_CPP_UCLPROPERTYBASE_H
#define UCL_CPP_UCLPROPERTYBASE_H

#include <iostream>
#include <cstdint>
#include <string>
using namespace std;

const uint8_t TPAER_BYTESNUM = 1;
const uint8_t LPARTHEAD_BYTESNUM = 1;

const uint8_t LPARTVALUE_BYTES_MIN = 1;
const uint8_t LPARTVALUE_BYTES_MAX = 4;

class UCLPropertyBase{
protected:
    uint8_t tPart;
    uint64_t lPart;
    string vPart;

    uint8_t quickMatcherBytesNum;
public:
    UCLPropertyBase()
    {
        tPart = 0;
        lPart = 0;
        vPart = "";
        quickMatcherBytesNum = 0;  //该数据成员专为UCLPropertyHead类设计,为了更好的setTotalLength,getTotalLength
    }
    virtual ~UCLPropertyBase() {}

    uint8_t getQuickMatcherBytesNum() const;
    void setQuickMatcherBytesNum(uint8_t quickMatcherBytesNum=2);

    //type
    virtual bool setTPart(uint8_t t);
    virtual uint8_t getTPart() const;

    //category, second type 4b
    virtual bool setCategory(uint8_t category);
    virtual uint8_t getCategory() const;

    //help, second type 4b
    virtual bool setHelper(uint8_t help=0);
    virtual uint8_t getHelper() const;

    //lPart
    virtual bool setLPart(const uint64_t lPart);
    virtual uint64_t getLPart() const;

    //return the number of lPart(bytes)
    virtual uint8_t getLPartBytesNum() const;

    //lPartHead
    virtual bool setLPartHead(uint8_t lPartHead);
    virtual bool setLPartHead(uint8_t start, uint8_t end, uint8_t head);
    virtual uint8_t getLPartHead() const ;
    virtual uint8_t getLPartHead(uint8_t start, uint8_t end);

    //the bytes of lPartValue
    virtual bool setLPartValueBytesNum(uint8_t bytesNum);
    virtual uint8_t getLPartValueBytesNum() const ;

    //totalLength, the value of lPartValue
    virtual bool setTotalLength();
    virtual uint32_t getTotalLength() const ;

    //vPart
    virtual const string &getVPart() const;
    virtual bool setVPart(const string &vPart);

    virtual uint32_t getVPartBytesNum() const ;

    //打包解包单个属性
    string pack();
    void unpack(string property);

    //简化category, helper和vPart部分的设置
    void setProperty(uint8_t category, uint8_t helper, string vPart);
};
#endif //UCL_CPP_UCLPROPERTYBASE_H