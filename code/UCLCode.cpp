//
// Created by hp-6380 on 2016/12/5.
//

#include "./header_file/UCLCode.h"
#include "./header_file/UCLFormatV2.h"
#include <iomanip>

using std::cout;
using std::setw;
using std::endl;
using std::setfill;


void UCLCode::codeDisplay(const UCLCode &code) const
{

    /*
    for (int i=0; i < 5; ++i)
    {
        char ch[9]="";
        std::cout << i << ":" << setw(8) << setfill('0') << itoa(code.uclCode[i], ch, 2) << std::endl;
    }
    */
    cout << setw(28) << "Version:" << code.getVersion() << "\n";
    cout << setw(28) << "Type of Media:" << code.getTypeOfMedia() << "\n";
    cout << setw(28) << "Precedence:" << code.getPrecedence() << "\n";
    cout << setw(28) << "Flag:" << code.getFlag() << "\n";
    cout << setw(28) << "Parse Rule:" << code.getParseRule() << "\n";
    cout << setw(28) << "Source of Content:" << code.getSourOfCont() << "\n";
    cout << setw(28) << "Category:" << code.getCategory() << "\n";
    cout << setw(28) << "Subcategory:" << code.getSubCategory() << "\n";
    cout << setw(28) << "Topic:" << code.getTopic() << "\n";
    cout << setw(28) << "Type of Content:" << code.getTypeOfContent() << "\n";
    cout << setw(28) << "Copyright and Length:" << code.getCopyAndLeng() << "\n";
    cout << setw(28) << "Security Energy Level Code:" << code.getSecuEnerLeveCode() << "\n";
    cout << setw(28) << "Time Stamp:" << code.getTimeStamp() << "\n";
    cout << setw(28) << "Serial Number:" << code.getSerialNumber() << "\n";
    cout << setw(28) << "Reserved Bytes:" << code.getReservedBytes() << "\n";
    cout << setw(28) << "Check Code:" << code.getCheckCode() << endl;
}

//根据给定的起始字节、起始位和长度获取uclCode的值
//According to the given byte, start bit and length get the value of uclCode
uint64_t UCLCode::getBits(const uint8_t startByte, const uint8_t startBit, const uint8_t bitLength) const
{
    uint8_t byteNum = 0;
    uint8_t byteNumCopy = 0;
    uint8_t index = 0;
    uint64_t out = 0;
    uint64_t maskCode = 0;

    index = startByte;
    maskCode = ~(~maskCode << bitLength); //高位被置0,低位为全1的掩码 如：version:07(8进制)
    byteNum = (bitLength / 8) + ((bitLength % 8) ? 1 : 0);
    if (startBit && (bitLength - (8 - startBit)) % 8 )//首尾均未字节对齐
    {
        ++byteNum;
    }
    byteNumCopy = byteNum;
    while (byteNum--)
    {
        out |= uclCode[index++];
        if (byteNum)
        {
            out <<= 8;
        }
    }
    //return out;
    out >>= (8 * byteNumCopy -bitLength - startBit);
    return out & maskCode;  //不是第0位开始且不是第7位结束时需要修正
}

//根据给定的起始字节、起始位和长度设置uclCode的值
bool UCLCode::setBits(const uint8_t startByte, const uint8_t startBit, const uint8_t bitLength, const uint64_t bitStream)
{
    uint8_t byteNum = 0;
    uint8_t temp = 0;
    uint8_t index = 0;
    uint64_t value = 0;
    uint64_t maskCode = 0;

    maskCode = ~ (~maskCode << bitLength); //高位被置0,低位为全1的掩码 如：version:07(8进制)
    value = bitStream & maskCode; //屏蔽高位,防止污染其他域
    byteNum = (bitLength / 8) + ((bitLength % 8) ? 1 : 0);
    if (startBit && (bitLength - (8 - startBit)) % 8 )//首尾均未字节对齐
    {
        ++byteNum;
    }
    index =startByte + (byteNum - 1);
    value <<= (8 * byteNum -bitLength - startBit);//末端字节对齐
    while (byteNum--)
    {
        temp = value & 255;
        uclCode[index--] |= temp;
        if (byteNum)
        {
            value >>= 8;
        }
    }
    return true;
}

//version
uint64_t UCLCode::getVersion() const
{
    /*
    std::bitset<VERSION_BIT_LENGTH> bitvec(0);  //全0的bitset bitvec:000
    bitvec.set();   //置位，bitset全1 bitvec:111
    uint64_t version = bitvec.to_ullong();  //高位被置0,低位为全1的屏蔽码 version:07(8进制)
    */
   /*
    uint64_t version;
    version = ~ (~0 << VERSION_BIT_LENGTH); //高位被置0,低位为全1的屏蔽码 version:07(8进制)

    return version &= getBits(VERSION_START_BYTE, VERSION_START_BIT, VERSION_BIT_LENGTH);
    */
    return getBits(VERSION_START_BYTE, VERSION_START_BIT, VERSION_BIT_LENGTH);
}

bool UCLCode::setVersion(const uint64_t version)
{
    return setBits(VERSION_START_BYTE, VERSION_START_BIT, VERSION_BIT_LENGTH, version);
}

//type of media
uint64_t UCLCode::getTypeOfMedia() const
{
    return getBits(TYPEOFMEDIA_START_BYTE, TYPEOFMEDIA_START_BIT, TYPEOFMEDIA_BIT_LENGTH);
}

bool UCLCode::setTypeOfMedia(const uint64_t typeOfMedia)
{
    return setBits(TYPEOFMEDIA_START_BYTE, TYPEOFMEDIA_START_BIT, TYPEOFMEDIA_BIT_LENGTH, typeOfMedia);
}

//precedence
uint64_t UCLCode::getPrecedence() const
{
    return getBits(PRECEDENCE_START_BYTE, PRECEDENCE_START_BIT, PRECEDENCE_BIT_LENGTH);
}

bool UCLCode::setPrecedence(const uint64_t precedence)
{
    return setBits(PRECEDENCE_START_BYTE, PRECEDENCE_START_BIT, PRECEDENCE_BIT_LENGTH, precedence);
}

//flag
uint64_t UCLCode::getFlag() const
{
    return getBits(FLAG_START_BYTE, FLAG_START_BIT, FLAG_BIT_LENGTH);
}

bool UCLCode::setFlag(const uint64_t flag)
{
    return setBits(FLAG_START_BYTE, FLAG_START_BIT, FLAG_BIT_LENGTH, flag);
}

//parse rule
uint64_t UCLCode::getParseRule() const
{
    return getBits(PARSERULE_START_BYTE, PARSERULE_START_BIT, PARSERULE_BIT_LENGTH);
}

bool UCLCode::setParseRule(const uint64_t parseRule)
{
    return setBits(PARSERULE_START_BYTE, PARSERULE_START_BIT, PARSERULE_BIT_LENGTH, parseRule);
}

//source of content
uint64_t UCLCode::getSourOfCont() const
{
    return getBits(SOUROFCONT_START_BYTE, SOUROFCONT_START_BIT, SOUROFCONT_BIT_LENGTH);
}

bool UCLCode::setSourOfCont(const uint64_t sourOfCont)
{
    return setBits(SOUROFCONT_START_BYTE, SOUROFCONT_START_BIT, SOUROFCONT_BIT_LENGTH, sourOfCont);
}

//category
uint64_t UCLCode::getCategory() const
{
    return getBits(CATEGORY_START_BYTE, CATEGORY_START_BIT, CATEGORY_BIT_LENGTH);
}

bool UCLCode::setCategory(const uint64_t category)
{
    return setBits(CATEGORY_START_BYTE, CATEGORY_START_BIT, CATEGORY_BIT_LENGTH, category);
}

//subcategory
uint64_t UCLCode::getSubCategory() const
{
    return getBits(SUBCATEGORY_START_BYTE, SUBCATEGORY_START_BIT, SUBCATEGORY_BIT_LENGTH);
}

bool UCLCode::setSubCategory(const uint64_t subCategory)
{
    return setBits(SUBCATEGORY_START_BYTE, SUBCATEGORY_START_BIT, SUBCATEGORY_BIT_LENGTH, subCategory);
}

//topic
uint64_t UCLCode::getTopic() const
{
    return getBits(TOPIC_START_BYTE, TOPIC_START_BIT, TOPIC_BIT_LENGTH);
}

bool UCLCode::setTopic(const uint64_t topic)
{
    return setBits(TOPIC_START_BYTE, TOPIC_START_BIT, TOPIC_BIT_LENGTH, topic);
}

//type of content
uint64_t UCLCode::getTypeOfContent() const
{
    return getBits(TYPEOFCONTENT_START_BYTE, TYPEOFCONTENT_START_BIT, TYPEOFCONTENT_BIT_LENGTH);
}

bool UCLCode::setTypeOfContent(const uint64_t typeOfContent)
{
    return setBits(TYPEOFCONTENT_START_BYTE, TYPEOFCONTENT_START_BIT, TYPEOFCONTENT_BIT_LENGTH, typeOfContent);
}

//copyright and length
uint64_t UCLCode::getCopyAndLeng() const
{
    return getBits(COPYANDLENG_START_BYTE, COPYANDLENG_START_BIT, COPYANDLENG_BIT_LENGTH);
}

bool UCLCode::setCopyAndLeng(const uint64_t copyAndLeng)
{
    return setBits(COPYANDLENG_START_BYTE, COPYANDLENG_START_BIT, COPYANDLENG_BIT_LENGTH, copyAndLeng);
}

//security energy level code
uint64_t UCLCode::getSecuEnerLeveCode() const
{
    return getBits(SECUENERLEVECODE_START_BYTE, SECUENERLEVECODE_START_BIT, SECUENERLEVECODE_BIT_LENGTH);
}

bool UCLCode::setSecuEnerLeveCode(const uint64_t secuEnerLeveCode)
{
    return setBits(SECUENERLEVECODE_START_BYTE, SECUENERLEVECODE_START_BIT, SECUENERLEVECODE_BIT_LENGTH, secuEnerLeveCode);
}

//time stamp
uint64_t UCLCode::getTimeStamp() const
{
    return getBits(TIMESTAMP_START_BYTE, TIMESTAMP_START_BIT, TIMESTAMP_BIT_LENGTH);
}

bool UCLCode::setTimeStamp(const uint64_t timeStamp)
{
    return setBits(TIMESTAMP_START_BYTE, TIMESTAMP_START_BIT, TIMESTAMP_BIT_LENGTH, timeStamp);
}

//serial number
uint64_t UCLCode::getSerialNumber() const
{
    return getBits(SERIALNUMBER_START_BYTE, SERIALNUMBER_START_BIT, SERIALNUMBER_BIT_LENGTH);
}

bool UCLCode::setSerialNumber(const uint64_t serialNumber)
{
    return setBits(SERIALNUMBER_START_BYTE, SERIALNUMBER_START_BIT, SERIALNUMBER_BIT_LENGTH, serialNumber);
}

//reserved bytes
uint64_t UCLCode::getReservedBytes() const
{
    return getBits(RESERVEDBYTES_START_BYTE, RESERVEDBYTES_START_BIT, RESERVEDBYTES_BIT_LENGTH);
}

bool UCLCode::setReservedBytes(const uint64_t reservedBytes)
{
    return setBits(RESERVEDBYTES_START_BYTE, RESERVEDBYTES_START_BIT, RESERVEDBYTES_BIT_LENGTH, reservedBytes);
}

//check code
uint64_t UCLCode::getCheckCode() const
{
    return getBits(CHECKCODE_START_BYTE, CHECKCODE_START_BIT, CHECKCODE_BIT_LENGTH);
}

bool UCLCode::setCheckCode(const uint64_t checkCode)
{
    return setBits(CHECKCODE_START_BYTE, CHECKCODE_START_BIT, CHECKCODE_BIT_LENGTH, checkCode);
}