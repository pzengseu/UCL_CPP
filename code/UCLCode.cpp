//
// Created by Oneway on 2016/12/5.
// Modified by Oneway on 2017/6/1.
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
    int width = 32;
    cout << setfill(' ') << setw(width) << "Version:" << code.getVersion() << "\n";
    cout << setfill(' ') << setw(width) << "Type of Media:" << code.getTypeOfMedia() << "\n";
    cout << setfill(' ') << setw(width) << "Prio and Poli:" << code.getPrioAndPoli() << "\n";
    cout << setfill(' ') << setw(width) << "Flag:" << code.getFlag() << "\n";
    cout << setfill(' ') << setw(width) << "Parse Rule:" << code.getParseRule() << "\n";
    cout << setfill(' ') << setw(width) << "Source of Content:" << code.getSourOfCont() << "\n";
    cout << setfill(' ') << setw(width) << "Category:" << code.getCategory() << "\n";
    cout << setfill(' ') << setw(width) << "Subcategory:" << code.getSubCategory() << "\n";
    cout << setfill(' ') << setw(width) << "Topic:" << code.getTopic() << "\n";
    cout << setfill(' ') << setw(width) << "Copyright and Type of Cont:" << code.getCopyAndTypeOfCont() << "\n";
    cout << setfill(' ') << setw(width) << "Security Energy Level Code:" << code.getSecuEnerLeveCode() << "\n";
    cout << setfill(' ') << setw(width) << "Language:" << code.getLanguage() << "\n";
    cout << setfill(' ') << setw(width) << "Size of Content:" << code.getSizeOfContent() << "\n";
    cout << setfill(' ') << setw(width) << "Time Stamp:" << code.getTimeStamp() << "\n";
    cout << setfill(' ') << setw(width) << "Serial Number:" << code.getSerialNumber() << "\n";
    cout << setfill(' ') << setw(width) << "Multiplex Bytes:" << code.getMultiplexBytes() << "\n";
    cout << setfill(' ') << setw(width) << "Code Check:" << code.getCodeCheck() << endl;
}

void UCLCode::showCode() const
{
    int width = 32;
    cout << setfill(' ') << setw(width) << "Version:" << getVersion() << "\n";
    cout << setfill(' ') << setw(width) << "Type of Media:" << getTypeOfMedia() << "\n";
    cout << setfill(' ') << setw(width) << "Prio and Poli:" << getPrioAndPoli() << "\n";
    cout << setfill(' ') << setw(width) << "Flag:" << getFlag() << "\n";
    cout << setfill(' ') << setw(width) << "Parse Rule:" << getParseRule() << "\n";
    cout << setfill(' ') << setw(width) << "Source of Content:" << getSourOfCont() << "\n";
    cout << setfill(' ') << setw(width) << "Category:" << getCategory() << "\n";
    cout << setfill(' ') << setw(width) << "Subcategory:" << getSubCategory() << "\n";
    cout << setfill(' ') << setw(width) << "Topic:" << getTopic() << "\n";
    cout << setfill(' ') << setw(width) << "Copyright and Type of Cont:" << getCopyAndTypeOfCont() << "\n";
    cout << setfill(' ') << setw(width) << "Security Energy Level Code:" << getSecuEnerLeveCode() << "\n";
    cout << setfill(' ') << setw(width) << "Language:" << getLanguage() << "\n";
    cout << setfill(' ') << setw(width) << "Size of Content:" << getSizeOfContent() << "\n";
    cout << setfill(' ') << setw(width) << "Time Stamp:" << getTimeStamp() << "\n";
    cout << setfill(' ') << setw(width) << "Serial Number:" << getSerialNumber() << "\n";
    cout << setfill(' ') << setw(width) << "Multiplex Bytes:" << getMultiplexBytes() << "\n";
    cout << setfill(' ') << setw(width) << "Code Check:" << getCodeCheck() << endl;
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

    ++modifiedNums;//记录code改变次数
    maskCode = ~ (~maskCode << bitLength); //高位被置0,低位为全1的掩码 如：version:0000 0111
    value = bitStream & maskCode; //屏蔽高位,防止污染其他域
    byteNum = (bitLength / 8) + ((bitLength % 8) ? 1 : 0);
    if (startBit && (bitLength - (8 - startBit)) % 8 )//首尾均未字节对齐
    {
        ++byteNum;
    }
    index =startByte + (byteNum - 1);
    value <<= (8 * byteNum -bitLength - startBit);//末端字节对齐
    maskCode = ~(maskCode << (8 * byteNum -bitLength - startBit));//末端字节对齐，需要设置的bit位为0，其余位为1，如：vrsion:1111 1000
    while (byteNum--)
    {
        temp = maskCode & 255;//每次取低8位
        uclCode[index] &= temp;//先将待设置的位复位（置0）
        temp = value & 255;//每次取低8位
        uclCode[index--] |= temp;//设置相应位，下标递减
        maskCode >>= 8;
        value >>= 8;
    }
    return true;
}

/*
 * code部分打包、解包
 */
string UCLCode::pack()
{
    if (modifiedNums)//打包之前首先检查是否生成最新的校验码
    {
        setCodeCheck();
    }
    /*
    char ch[CODE_BYTES] = {'\0'};
    for (int i =0; i < CODE_BYTES; ++i)
    {
        ch[i] = uclCode[i];
    }
    string s(ch,CODE_BYTES);
    */
    string s((char *)uclCode, CODE_BYTES);//使用无符号数组初始化字符串
    return s;
}

//可考虑增加校验字段验证
bool UCLCode::unpack(string strCode)
{
    if (strCode.size() != CODE_BYTES)
    {
        return false;
    }
    for (int i =0; i < CODE_BYTES; ++i)
    {
        uclCode[i] = static_cast<uint8_t >(strCode[i]);
    }
    return true;
}

//version
uint64_t UCLCode::getVersion() const
{
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

//priority and policy
uint64_t UCLCode::getPrioAndPoli() const
{
    return getBits(PRIOANDPOLI_START_BYTE, PRIOANDPOLI_START_BIT, PRIOANDPOLI_BIT_LENGTH);
}

bool UCLCode::setPrioAndPoli(const uint64_t prioAndPoli)
{
    return setBits(PRIOANDPOLI_START_BYTE, PRIOANDPOLI_START_BIT, PRIOANDPOLI_BIT_LENGTH, prioAndPoli);
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

//copyright and type of content
uint64_t UCLCode::getCopyAndTypeOfCont() const
{
    return getBits(COPYANDTYPEOFCONT_START_BYTE, COPYANDTYPEOFCONT_START_BIT, COPYANDTYPEOFCONT_BIT_LENGTH);
}

bool UCLCode::setCopyAndTypeOfCont(const uint64_t copyAndTypeOfCont)
{
    return setBits(COPYANDTYPEOFCONT_START_BYTE, COPYANDTYPEOFCONT_START_BIT, COPYANDTYPEOFCONT_BIT_LENGTH, copyAndTypeOfCont);
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

//language
uint64_t UCLCode::getLanguage() const
{
    return getBits(LANGUAGE_START_BYTE, LANGUAGE_START_BIT, LANGUAGE_BIT_LENGTH);
}

bool UCLCode::setLanguage(const uint64_t language)
{
    return setBits(LANGUAGE_START_BYTE, LANGUAGE_START_BIT,LANGUAGE_BIT_LENGTH, language);
}

//size of content
uint64_t UCLCode::getSizeOfContent() const
{
    return getBits(SIZEOFCONTENT_START_BYTE, SIZEOFCONTENT_START_BIT, SIZEOFCONTENT_BIT_LENGTH);
}

bool UCLCode::setSizeOfContent(const uint64_t sizeOfContent)
{
    uint8_t lengthRange=0, maxLengthUnit=0, sizes=0;
    //判断sizeOfContent长度
    if(sizeOfContent<1024)
    {
        //B
        lengthRange = getLengthRange(sizeOfContent);
        maxLengthUnit=0;
    }
    else if(sizeOfContent>=1024&&(sizeOfContent/1024)<1024)
    {
        //KB
        lengthRange = getLengthRange(sizeOfContent/1024);
        maxLengthUnit=1;
    }
    else if((sizeOfContent/1024)>=1024&&(sizeOfContent/1024/1024)<1024)
    {
        //MB
        lengthRange = getLengthRange(sizeOfContent/1024/1024);
        maxLengthUnit=2;
    }
    else if((sizeOfContent/1024/1024)>=1024&&(sizeOfContent/1024/1024/1024)<1024)
    {
        //GB
        lengthRange = getLengthRange(sizeOfContent/1024/1024/1024);
        maxLengthUnit=3;
    }
    sizes=(maxLengthUnit<<3)|lengthRange;
    return setBits(SIZEOFCONTENT_START_BYTE, SIZEOFCONTENT_START_BIT, SIZEOFCONTENT_BIT_LENGTH, sizes);
}

uint8_t UCLCode::getLengthRange(uint64_t sizeOfContent)
{
    if(sizeOfContent<4)
        return 0;
    else if(sizeOfContent>=4&&sizeOfContent<16)
        return 1;
    else if(sizeOfContent>=16&&sizeOfContent<64)
        return 2;
    else if(sizeOfContent>=64&&sizeOfContent<128)
        return 3;
    else if(sizeOfContent>=128&&sizeOfContent<256)
        return 4;
    else if(sizeOfContent>=256&&sizeOfContent<512)
        return 5;
    else if(sizeOfContent>=512&&sizeOfContent<768)
        return 6;
    else if(sizeOfContent>=768&&sizeOfContent<1024)
        return 7;
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
    uint64_t lengthField = getBits(SERIALNUMBER_START_BYTE, SERIALNUMBER_START_BIT, 2);//前两位标识域的长度
    uint64_t  lengOfSeriNumb = (lengthField <= 0x01) ? 8 : (lengthField << 3);//00-8b, 01-8b, 10-16b, 11-24b
    if(lengOfSeriNumb > SERIALNUMBER_MAX_LENGTH)
    {
        lengOfSeriNumb = SERIALNUMBER_DEFAULT_LENGTH;
    }
    return getBits(SERIALNUMBER_START_BYTE, SERIALNUMBER_START_BIT, lengOfSeriNumb);
}

bool UCLCode::setSerialNumber(const uint64_t serialNumber)
{
    uint8_t lengOfSeriNumb = SERIALNUMBER_DEFAULT_LENGTH;
    if(serialNumber & 0x800000)
    {
        lengOfSeriNumb = 24;
    }
    else if(serialNumber & 0x8000)
    {
        lengOfSeriNumb = 16;
    }
    return setBits(SERIALNUMBER_START_BYTE, SERIALNUMBER_START_BIT, lengOfSeriNumb, serialNumber);
}

//multiplex bytes
uint64_t UCLCode::getMultiplexBytes() const
{
    //首先获取serial number的长度
    uint64_t lengthField = getBits(SERIALNUMBER_START_BYTE, SERIALNUMBER_START_BIT, 2);//前两位标识域的长度
    uint64_t lengOfSeriNumb = (lengthField <= 0x01) ? 8 : (lengthField << 3);//00-1B, 01-1B, 10-2B, 11-3B
    if(lengthField > SERIALNUMBER_MAX_LENGTH)
    {
        lengOfSeriNumb = 8;
    }

    uint8_t startByte = SERIALNUMBER_START_BYTE + lengOfSeriNumb / 8;
    uint8_t bitLength = (MULTIPLEX_END_BYTE - startByte) << 3;
    if(bitLength > MULTIPLEXBYTES_MAX_LENGTH)
    {
        bitLength = 32;
    }
    return getBits(startByte, MULTIPLEXBYTES_START_BIT, bitLength);
}

bool UCLCode::setMultiplexBytes(const uint64_t multiplexBytes)
{
    //首先获取serial number的长度
    uint64_t lengthField = getBits(SERIALNUMBER_START_BYTE, SERIALNUMBER_START_BIT, 2);//前两位标识域的长度
    uint64_t lengOfSeriNumb = (lengthField <= 0x01) ? 8 : (lengthField << 3);//00-1B, 01-1B, 10-2B, 11-3B
    if(lengthField > SERIALNUMBER_MAX_LENGTH)
    {
        lengOfSeriNumb = 8;
    }

    uint8_t startByte = SERIALNUMBER_START_BYTE + lengOfSeriNumb / 8;
    uint8_t bitLength = (MULTIPLEX_END_BYTE - startByte) << 3;
    if(bitLength > MULTIPLEXBYTES_MAX_LENGTH)
    {
        bitLength = 32;
    }
    return setBits(startByte, MULTIPLEXBYTES_START_BIT, bitLength, multiplexBytes);
}

//code check
uint64_t UCLCode::getCodeCheck() const
{
    return getBits(CODECHECK_START_BYTE, CODECHECK_START_BIT, CODECHECK_BIT_LENGTH);
}

bool UCLCode::setCodeCheck()
{
    uint16_t checkCode = CRC16(uclCode, CODE_BYTES - (CODECHECK_BIT_LENGTH / 8));
    bool setResult = setBits(CODECHECK_START_BYTE, CODECHECK_START_BIT, CODECHECK_BIT_LENGTH, checkCode);
    if (setResult)
    {
        modifiedNums = 0;//设置校验码成功后则将修改次数置0
        return true;
    }else
    {
        return false;
    }
}
/*
 * 计算CRC16校验码
 * message是需要生成校验码的code部分的数组指针
 * length是code长度减去2字节
 */
uint16_t UCLCode::CRC16(uint8_t * message, uint16_t length) const
{
    uint16_t result = 0xFFFF;
    uint8_t temp;
    for (uint16_t i = 0; i < length; i++)
    {
        temp = *message++;
        result = crcTable[(temp ^ result) & 15] ^ (result >> 4);
        result = crcTable[((temp >> 4) ^ result) & 15] ^ (result >> 4);
    }
    return result;
}