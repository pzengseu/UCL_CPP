//
// Created by hp-6380 on 2016/12/5.
//

#ifndef UCL_V0_1_UCLCODE_H
#define UCL_V0_1_UCLCODE_H

#include <iostream>
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include "UCLFormatV2.h"

using std::string;

const uint16_t crcTable[16] =
        {
                0x0000, 0xCC01, 0xD801, 0x1400,
                0xF001, 0x3C00, 0x2800, 0xE401,
                0xA001, 0x6C00, 0x7800, 0xB401,
                0x5000, 0x9C01, 0x8801, 0x4400,
        };

class UCLCode
{
public:
    //构造函数
    UCLCode() {}

    //析构函数
    virtual ~UCLCode() {}

    void codeDisplay(const UCLCode &code) const;//显示所有域
    void showCode() const;//显示所有域

    //获取bit位、设置bit位
    uint64_t getBits(const uint8_t startByte, const uint8_t startBit, const uint8_t bitLength) const;
    bool setBits(const uint8_t startByte, const uint8_t startBit, const uint8_t bitLength, const uint64_t bitStream);

    /*
     * code部分打包、解包
     */
    string pack();
    bool unpack(string strCode);

    /*
     * get set接口
     */
    //version
    uint64_t getVersion() const;
    bool setVersion(const uint64_t version);//version 的低3位有效

    //type of media
    uint64_t getTypeOfMedia() const;
    bool setTypeOfMedia(const uint64_t typeOfMedia);

    //priority and policy
    uint64_t getPrioAndPoli() const;
    bool setPrioAndPoli(const uint64_t prioAndPoli);

    //flag
    uint64_t getFlag() const;
    bool setFlag(const uint64_t flag);

    //parse rule
    uint64_t getParseRule() const;
    bool setParseRule(const uint64_t parseRule);

    //source of content
    uint64_t getSourOfCont() const;
    bool setSourOfCont(const uint64_t sourOfCont);

    //category
    uint64_t getCategory() const;
    bool setCategory(const uint64_t category);

    //subcategory
    uint64_t getSubCategory() const;
    bool setSubCategory(const uint64_t subCategory);

    //topic
    uint64_t getTopic() const;
    bool setTopic(const uint64_t topic);

    //copyright and type of content
    uint64_t getCopyAndTypeOfCont() const;
    bool setCopyAndTypeOfCont(const uint64_t copyAndTypeOfCont);

    //security energy level code
    uint64_t getSecuEnerLeveCode() const;
    bool setSecuEnerLeveCode(const uint64_t secuEnerLeveCode);

    //language
    uint64_t getLanguage() const;
    bool setLanguage(const uint64_t language);

    //size of content
    uint64_t getSizeOfContent() const;
    bool setSizeOfContent(const uint64_t sizeOfContent);

    uint8_t getLengthRange(uint64_t sizeOfContent);
    //time stamp
    uint64_t getTimeStamp() const;
    bool setTimeStamp(const uint64_t timeStamp);

    //serial number
    uint64_t getSerialNumber() const;
    bool setSerialNumber(const uint64_t serialNumber);

    //multiplex bytes
    uint64_t getMultiplexBytes() const;
    bool setMultiplexBytes(const uint64_t multiplexBytes);

    //code check
    uint64_t getCodeCheck() const;
    bool setCodeCheck();//打包的时候会生成校验码

    uint16_t CRC16(uint8_t * message, uint16_t length) const;


private:
    uint8_t uclCode[CODE_BYTES] = {0};//初始化为全0，则未设置的域均为0
    uint8_t modifiedNums = 0;
};
#endif //UCL_V0_1_UCLCODE_H
