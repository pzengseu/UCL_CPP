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
    map<int, string> propertyHeadMap;
    map<int, string> propertySetCategoryMap;
    map<int, map<int, string>> propertyCategoryMap;

    map<int, string> signatureMap;
    map<int, string> hash;
public:
    UCLPropertiesInfo();

    void initPropertyHeadMap();
    string getPropertyLangType(int type);

    void initPropertySetCategoryMap();
    string getPropertySetCategory(int type);

    void initPropertyCategroyMap();
    string getPropertyCategroy(int categroy, int proCategory);

    void initAlgorithm();

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
};



#endif //UCL_CPP_UCLPROPERTIESINFO_H
