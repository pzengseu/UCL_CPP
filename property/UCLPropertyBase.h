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

class UCLPropertyBase{
protected:
    uint8_t tPart;
    uint64_t lPart;
    string vPart;

public:
    UCLPropertyBase()
    {
        tPart = 0;
        lPart = 0;
        vPart = "";
    }
    virtual ~UCLPropertyBase() {}

    //type
    virtual bool setTPart(uint8_t t);
    virtual uint8_t getTPart() const;

    //category, second type 4b
    virtual bool setCategory(uint8_t category);
    virtual uint8_t getCategory() const;

    //help, second type 4b
    virtual bool setHelp(uint8_t help=0);
    virtual uint8_t getHelp() const;

    //lPart
    virtual bool setLPart(const uint64_t lPart);
    virtual uint64_t getLPart() const;

    //return the number of lPart(bytes)
    virtual uint8_t getLPartBytesNum(int quickMatcherBytes=0) const;

    //lPartHead
    virtual bool setLPartHead(uint8_t lPartHead);
    virtual uint8_t getLPartHead() const ;

    //the bytes of lPartValue
    virtual bool setLPartValueBytesNum(uint8_t bytesNum);
    virtual uint8_t getLPartValueBytesNum() const ;

    //totalLength, the value of lPartValue
    virtual bool setTotalLength(int quickMatcherBytes=0);
    virtual uint32_t getTotalLength() const ;

    //vPart
    virtual const string &getVPart() const;
    virtual bool setVPart(const string &vPart);

    virtual uint32_t getVPartBytesNum() const ;
};
#endif //UCL_CPP_UCLPROPERTYBASE_H