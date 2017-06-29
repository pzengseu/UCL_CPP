//
// Created by zp on 12/17/16.
//

#include <map>
#include <bitset>
#include <cassert>
#include "../property/UCLPropertyHead.h"
#include "UCL.h"
#include "../tools/digestUtils/UCLMD5.h"
#include "../tools/digestUtils/UCLCRC32.h"
#include "../tools/digestUtils/UCLSHA_256.h"
#include "../tools/digestUtils/UCLSHA_512.h"
#include "../tools/signatureUtils/UCLRSA.h"
#include "test.h"

const UCLPropertyHead &UCL::getUclPropertyHead() const {
    return uclPropertyHead;
}

void UCL::setUclPropertyHead(const UCLPropertyHead &uclPropertyHead) {
    UCL::uclPropertyHead = uclPropertyHead;
}

const map<int, UCLPropertySet> &UCL::getPropertySets() const {
    return propertySets;
}

void UCL::setPropertySets(const map<int, UCLPropertySet> &propertySets) {
    UCL::propertySets = propertySets;
}

bool UCL::setPropertySet(UCLPropertySet &propertySet)
{
    propertySets[propertySet.getHeadCategory()] = propertySet;
    setUCL();
}

bool UCL::delPropertySet(uint8_t category)
{
    propertySets.erase(category);
}

void UCL::setHeadCategory(uint8_t category)
{
    uclPropertyHead.setCategory(category);
}

uint8_t UCL::getHeadCategory()
{
    return uclPropertyHead.getCategory();
}

void UCL::setHeadHelper(uint8_t helper)
{
    uclPropertyHead.setHelper(helper);
}

uint8_t UCL::getHeadHelper()
{
    return uclPropertyHead.getHelper();
}

uint16_t UCL::generateQuickMatcher()
{
    bitset<16> qmb;
    map<int, UCLPropertySet>::iterator iter = propertySets.begin();
    for(; iter != propertySets.end(); iter++)
    {
        qmb.set(iter->first);
    }

    return qmb.to_ulong();
}

string UCL::generateHeadVPart()
{
    bitset<16> qmb(uclPropertyHead.getQuickMatcher());
    string value;

    for(int i=0; i < 16; i++)
    {
        if(qmb.test(i))
        {
            value += propertySets[i].pack();
        }
    }

    return value;
}

void UCL::setUCL()
{
    /*
     * VPart会影响QuickMatcher位置,QuickMatcher位置也会影响VPart
     * generateQuickMatcher()根据propertySets生成quickMatcher
     * generateHeadVPart()根据quickMatcher生成vPart
     * vPart的设置会影响quickMatcher的位置
    */
    uclPropertyHead.setQuickMatcher(generateQuickMatcher());
    uclPropertyHead.setVPart(generateHeadVPart());
    uclPropertyHead.setQuickMatcher(generateQuickMatcher());
//    uclPropertyHead.setTotalLength();
}

bool UCL::setProperty(int setPos, UCLPropertyBase &property)
{
    propertySets[setPos].setProperty(property);
    setUCL();
}

bool UCL::delProperty(int setPos, int propertyPos)
{
    assert(propertySets.find(setPos) != propertySets.end());
    propertySets[setPos].delProperty(propertyPos);
    setUCL();
}

UCLPropertyBase UCL::getProperty(int setPos, int propertyPos)
{
    assert(propertySets.find(setPos) != propertySets.end());
    return propertySets[setPos].getProperty(propertyPos);
}

string UCL::getValue(int setPos, int propertyPos)
{
    assert(propertySets.find(setPos)!=propertySets.end());
    return propertySets[setPos].getPropertyVPart(propertyPos);
//    map<int, UCLPropertyBase> properties = propertySets[setPos].getProperties();
//    assert(properties.find(propertyPos)!=properties.end());
//    return properties[propertyPos].getVPart();
}

void UCL::setValue(int setPos, int propertyPos, string value)
{
    assert(propertySets.find(setPos)!=propertySets.end());
    propertySets[setPos].setPropertyVPart(propertyPos, value);
    setUCL();
}

string UCL::packPropertySets()
{
    return uclPropertyHead.pack();
}

void UCL::unpackPropertySets(string properties)
{
    uclPropertyHead.unpack(properties);
    bitset<16> bqm(uclPropertyHead.getQuickMatcher());
    string headVPart = uclPropertyHead.getVPart();
    uint32_t tmp = 0;
    for(int i=0; i < bqm.size(); i++)
    {
        if(bqm.test(i))
        {
            //计算属性集合头部属性长度值字段字节数
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
            string propertySet = headVPart.substr(tmp, lValueNum);
            UCLPropertySet proSet;
            proSet.unpack(propertySet);
            propertySets[i] = proSet;
            tmp += lValueNum;
        }
    }
}

string UCL::pack()
{
    map<int, UCLPropertyBase> ps = propertySets[15].getProperties();
    UCLPropertyBase sigUCLP = ps[15];

    int helper = sigUCLP.getHelper();
    int alg = sigUCLP.getLPartHead(2, 5);

    setValue(15, 15, "");
    string temp = uclCode.pack() /*+ uclCodeExtension.pack()*/ + packPropertySets();

    // 对于数字签名算法此处应该先生成hash值，然后私钥加密
    string hash = genHash(alg, temp);   //生成摘要
    string uclSigTemp = genSig(helper, hash);  //私钥加密摘要

    setValue(15, 15, uclSigTemp);

    return uclCode.pack() /*+ uclCodeExtension.pack()*/ + packPropertySets();
}

void UCL::unpack(string ucl)
{
    //UCLCode
    string sUCLCode = ucl.substr(0, 32);
    uclCode.unpack(sUCLCode);

    //UCLCodeExt
//    int uclCodeExt = 0;
//    if((uclCode.getFlag() & 0x1))
//    {
//        uclCodeExt = ucl[32] & 0xf;
//    };
//    string sUCLCodeExt = ucl.substr(32, uclCodeExt * 16);
//    uclCodeExtension.unpack(sUCLCodeExt);

    //UCLProperty
    unpackPropertySets(ucl.substr(32));

    assert(checkUCL());
}
bool UCL::checkUCL()
{
    map<int, UCLPropertyBase> ps = propertySets[15].getProperties();
    UCLPropertyBase sigUCLP = ps[15];

    string uclSig = getValue(15, 15);
    setValue(15, 15, "");
    string originUCL = uclCode.pack() /*+ uclCodeExtension.pack()*/ + packPropertySets();

    int helper = sigUCLP.getHelper();
    int alg = sigUCLP.getLPartHead(2, 5);
    //生成原始hash值
    string hashFromOriginUCL = genHash(alg, originUCL);
    //给定原始数据和签名后的数据,进行验证
    bool res = verify(helper,hashFromOriginUCL,uclSig);

    setValue(15, 15, uclSig);

    return res;
}

string UCL::genHash(int alg, string temp)
{
    string hash;

    switch(alg)
    {
        case 1: //CRC32
            hash = crc32(temp);
            break;
        case 2: //MD5
            hash = MD5(temp).toString();
            break;
        case 3: //SHA-256
            hash = sha256(temp);
            break;
        case 4: //SHA-512
            hash = sha512(temp);
            break;
        default: break;
    }

    return hash;
}

string UCL::genSig(int helper, string originalData)
{
    string signData = originalData;
    switch(helper)
    {
        case 0:
            break;
        case 1: //RSA
            signData = UCLRSA::RSASign(originalData);
            break;
        case 2:
            //ECDSA
            break;
        case 3:
            //DSA
            break;
        case 4:
            //ECC
            break;
        default: break;
    }
    return signData;
}

/**
 * @deprecated
 * @param helper
 * @param s
 * @return
 */
bool UCL::verify(int helper, const string &originalData, const string &signData)
{
    bool res = true;
    switch(helper)
    {
        case 0:
            break;
        case 1:  //RSA
            res = UCLRSA::RSAVerify(originalData,signData);
            break;
        case 2:
            //ECDSA
            break;
        case 3:
            //DSA
            break;
        case 4:
            //ECC
            break;
        default: break;
    }
    return res;
}

void UCL::showUCL()
{
    uclCode.showCode();
//    uclCodeExtension.showCodeExt();

    cout << "--------------属性部分----------------" << endl;
    cout << "元语言类型: " << UPI.getPropertyLangType(uclPropertyHead.getCategory()) << endl;
    cout << "属性集个数: " << (int)uclPropertyHead.getSize() << endl;
    cout << "--------------具体属性集----------------" << endl;
    map<int, UCLPropertySet>::iterator proSet = propertySets.begin();
    for(; proSet!=propertySets.end(); proSet++)
    {
        cout << "**************************" << endl;
        proSet->second.showPropertySet();
    }
}

/*
 * UCLCode and extension
 */
const UCLCode &UCL::getUclCode() const {
    return uclCode;
}

void UCL::setUclCode(const UCLCode &uclCode) {
    UCL::uclCode = uclCode;
}

const UCLCodeExtension &UCL::getUclCodeExtention() const {
    return uclCodeExtension;
}

void UCL::setUclCodeExtention(const UCLCodeExtension &uclCodeExtention) {
    UCL::uclCodeExtension = uclCodeExtention;
}
