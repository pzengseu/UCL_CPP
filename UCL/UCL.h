//
// Created by zp on 2016/12/12.
//

#ifndef UCL_UCL_H
#define UCL_UCL_H

#include <vector>
#include <map>
#include "../property/UCLPropertyHead.h"
#include "../property/UCLPropertySet.h"
#include "../code/header_file/UCLCode.h"
#include "../code/header_file/UCLCodeExtension.h"
#include "../property/UCLPropertiesInfo.h"

static UCLPropertiesInfo UPI = UCLPropertiesInfo();
class UCL{
private:
    UCLCode uclCode;
    UCLCodeExtension uclCodeExtension;
    UCLPropertyHead uclPropertyHead;
    map<int, UCLPropertySet> propertySets;

public:
    UCL()
    {
        uclCode = UCLCode();
        uclCodeExtension = UCLCodeExtension();
        uclPropertyHead = UCLPropertyHead();
        uclPropertyHead.setCategory(0x1);  //中文
        uclPropertyHead.setTotalLength();
    }
    virtual ~ UCL() {}

    /*
     * UCLCode
     */
    const UCLCode &getUclCode() const;
    void setUclCode(const UCLCode &uclCode);

    const UCLCodeExtension &getUclCodeExtention() const;
    void setUclCodeExtention(const UCLCodeExtension &uclCodeExtention);

    /*
     * property
     */
    //uclPropertyHead
    void updatePropertyLength();
    const UCLPropertyHead &getUclPropertyHead() const;
    void setUclPropertyHead(const UCLPropertyHead &uclPropertyHead);

    //propertySets
    const map<int, UCLPropertySet> &getPropertySets() const;
    void setPropertySets(const map<int, UCLPropertySet> &propertySets);

    //设置　删除属性集合
    bool setPropertySet(UCLPropertySet &propertySet);
    bool delPropertySet(uint8_t category);

    //设置 删除属性
    bool setProperty(int setPos, UCLPropertyBase &property);
    bool delProperty(int setPos, int propertyPos);
    UCLPropertyBase getProperty(int setPos, int propertyPos);

    //获取第setPos集合的第propertyPos属性的vPart
    string getValue(int setPos, int propertyPos);
    //设置第setPos集合的第propertyPos属性的vPart
    void setValue(int setPos, int propertyPos, string value);

    //判断数字签名类型
    uint8_t initSignature(int helper,int alg);
    //设置uclProperthHead类别
    void setHeadCategory(uint8_t category);
    uint8_t getHeadCategory();
    //设置uclPropertyHead helper
    void setHeadHelper(uint8_t helper);
    uint8_t getHeadHelper();

    //根据propertySets生成uclPropertyHead的快速匹配
    uint16_t generateQuickMatcher();
    //根据propertySets生成uclPropertyHead的vPart
    string generateHeadVPart();

    //获取UCL总长度（code和property）
    bool setUCLTotalLength();
    //属性集合有变需调用该函数
    void setUCL();

    //属性集合打包解包
    string packPropertySets();
    void unpackPropertySets(string properties);

    //UCL　Package打包解包，UCL扩展部分暂无考虑
    string pack();
    void unpack(string ucl);
    //检验UCL包数字签名
    bool checkUCL();
    //打印UCL各部分
    void showUCL();

    //生成hash值
    static string genHash(int alg, string temp);
    //数字签名值
    static string genSig(int helper, const string &originalData);
    static bool sigVerify(int helper, const string &originData,const string &signData);
};
#endif //UCL_UCL_H
