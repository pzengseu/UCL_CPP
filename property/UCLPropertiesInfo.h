//
// Created by zp on 17-6-8.
//

#ifndef UCL_CPP_UCLPROPERTIESINFO_H
#define UCL_CPP_UCLPROPERTIESINFO_H

#include <string>
#include <map>
#include "UCLPropertyBase.h"

using namespace std;

class UCLPropertiesInfo
{
private:
    //受控映射表
    map<int, string> propertyHeadMap;
    map<int, string> propertySetCategoryMap;
    map<int, map<int, string>> propertyCategoryMap;

    map<int, string> entity;
    map<int, string> promap; //provenance
    map<int, string> contentIdRulemap;
    map<int, string> seliMap;

    map<int, string> signatureMap;
    map<int, string> hash;
public:
    UCLPropertiesInfo();

    void initPropertyHeadMap();
    string getPropertyLangType(int type);

    //属性集合映射
    void initPropertySetCategoryMap();
    string getPropertySetCategory(int type);

    //属性映射
    void initPropertyCategroyMap();
    string getPropertyCategroy(int categroy, int proCategory);

    //初始化属性部分受控映射表
    void initInfo();

    vector<string> split(string str, string pattern);

    void showProperty(int category, UCLPropertyBase propertyBase);
    void showPropertyBase(UCLPropertyBase propertyBase);
    void showCDPSKeywords(UCLPropertyBase keywords);
    void showCDPSAuthor(UCLPropertyBase author);
    void showCDPSEntity(UCLPropertyBase entity);
    void showCDPSTag(UCLPropertyBase tag);
    void showCDPSFileInfo(UCLPropertyBase fileInfo);
    void showCDPSRelatedUCL(UCLPropertyBase relatedUCL);

    void showCGPSProvenance(UCLPropertyBase provenance);
    void showCGPSContentId(UCLPropertyBase content);
    void showCGPSPropagationPath(UCLPropertyBase propagationPath);
    void showCGPSSignatureContent(UCLPropertyBase sigContent);
    void showCGPSSELI(UCLPropertyBase seli);
    void showCGPSChainRespons(UCLPropertyBase cr);
    void showCGPSSignatureUP(UCLPropertyBase sup);
};



#endif //UCL_CPP_UCLPROPERTIESINFO_H
