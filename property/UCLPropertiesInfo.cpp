//
// Created by zp on 17-6-8.
//

#include <vector>
#include <sstream>
#include <iterator>
#include <bitset>
#include "UCLPropertiesInfo.h"
#include "../code/header_file/UCLCode.h"
#include "../UCL.h"

UCLPropertiesInfo::UCLPropertiesInfo()
{
    initPropertyHeadMap();
    initPropertySetCategoryMap();
    initPropertyCategroyMap();

    initInfo();
}

vector<string> UCLPropertiesInfo::split(string str, string pattern)
{
    int pos;
    vector<string> result;
    str += pattern;
    int size = str.size();

    for(int i=0; i<size; i++)
    {
        pos=str.find(pattern,i);
        if(pos<size)
        {
            std::string s=str.substr(i,pos-i);
            result.push_back(s);
            i=pos+pattern.size()-1;
        }
    }
    return result;
}

void UCLPropertiesInfo::initPropertyHeadMap()
{
    propertyHeadMap[0] = "保留";
    propertyHeadMap[1] = "中文";
    propertyHeadMap[2] = "英文";
    propertyHeadMap[3] = "法文";
    propertyHeadMap[4] = "俄文";
    propertyHeadMap[5] = "阿拉伯文";
    propertyHeadMap[6] = "西班牙文";
    propertyHeadMap[7] = "葡萄牙文";
    propertyHeadMap[8] = "德文";
    propertyHeadMap[9] = "日文";
    // 10-14暂未定义
    propertyHeadMap[15] = "其它语种";
}

string UCLPropertiesInfo::getPropertyLangType(int type)
{
    if (propertyHeadMap.find(type) == propertyHeadMap.end())
        return "自定义类型";
    else return propertyHeadMap[type];
}

void UCLPropertiesInfo::initPropertySetCategoryMap()
{
    // 0的属性集合保留，2～14属性集合未定义
    propertySetCategoryMap[1] = "内容描述属性集合";
    propertySetCategoryMap[15] = "内容管理属性集合";
}

string UCLPropertiesInfo::getPropertySetCategory(int type)
{
    if (propertySetCategoryMap.find(type) == propertySetCategoryMap.end())
        return "自定义集合";
    else
        return propertySetCategoryMap[type];
}

void UCLPropertiesInfo::initPropertyCategroyMap()
{
    map<int, string> cdps;
    cdps[1] = "内容标题";
    cdps[2] = "内容关键词";
    cdps[3] = "内容摘要";
    cdps[4] = "内容作者";
    cdps[5] = "内容实体";
    cdps[6] = "内容标记";
    cdps[7] = "版权信息";
    cdps[8] = "原创声明";
    cdps[9] = "文件信息";
    cdps[14] = "关联UCL";
    cdps[15] = "内容对象";
    propertyCategoryMap[1] = cdps;

    map<int, string> cgps;
    cgps[3] = "内容出处";
    cgps[4] = "内容ID";
    cgps[5] = "传播路径";
    cgps[12] = "内容数字签名";
    cgps[13] = "安全能级信息";
    cgps[14] = "内容责任链";
    cgps[15] = "全UCL包数字签名";
    propertyCategoryMap[15] = cgps;
}

string UCLPropertiesInfo::getPropertyCategroy(int categroy, int proCategory)
{
    return propertyCategoryMap[categroy][proCategory];
}


void UCLPropertiesInfo::initInfo()
{
    entity[0] = "人";
    entity[1] = "时";
    entity[2] = "地";
    entity[3] = "事";
    entity[4] = "因";
    entity[5] = "其它";

    promap[1] = "网址或域名";
    promap[2] = "机构名";
    promap[3] = "应用相关";

    contentIdRulemap[1] = "URI";
    contentIdRulemap[2] = "DOI";
    contentIdRulemap[3] = "ISBN";
    contentIdRulemap[4] = "ISRC";

    seliMap[0] = "自行标定";
    seliMap[1] = "第一级内容提供商认证";
    seliMap[2] = "第二级内容提供商认证";
    seliMap[14] = "权威内容中心认证";

    signatureMap[0] = "未对内容对象进行数字签名";
    signatureMap[1] = "RSA";
    signatureMap[2] = "ECDSA";
    signatureMap[3] = "DSA";
    signatureMap[4] = "ECC";
    signatureMap[5] = "HMAC";

    hash[1] = "CRC32";
    hash[2] = "MD5";
    hash[3] = "SHA-256";
    hash[4] = "SHA-512";
}

void UCLPropertiesInfo::showProperty(int category, UCLPropertyBase propertyBase)
{
    if (category == 1)
    {
        switch (propertyBase.getCategory())
        {
            case 1:
            case 3:
            case 7:
            case 8:
            case 15:
                showPropertyBase(propertyBase);
                break;
            case 2:
                showCDPSKeywords(propertyBase);
                break;
            case 4:
                showCDPSAuthor(propertyBase);
                break;
            case 5:
                showCDPSEntity(propertyBase);
                break;
            case 6:
                showCDPSTag(propertyBase);
                break;
            case 9:
                showCDPSFileInfo(propertyBase);
                break;
            case 14:
                showCDPSRelatedUCL(propertyBase);
                break;
            default:
                cout << "****自定义属性****" << endl;
        }
    }
    if (category == 15)
    {
        switch (propertyBase.getCategory())
        {
            case 3:
                showCGPSProvenance(propertyBase);
                break;
            case 4:
                showCGPSContentId(propertyBase);
                break;
            case 5:
                showCGPSPropagationPath(propertyBase);
                break;
            case 12:
                showCGPSSignatureContent(propertyBase);
                break;
            case 13:
                showCGPSSELI(propertyBase);
                break;
            case 14:
                showCGPSChainRespons(propertyBase);
                break;
            case 15:
                showCGPSSignatureUP(propertyBase);
                break;
            default:
                cout << "****自定义属性****" << endl;
        }
    }
}

/*
 * 包括：
 * CDPS:
 * 1 Title
 * 3 Abstract
 * 7 CopyRight
 * 8 Originality
 * 15 content object
 */
void UCLPropertiesInfo::showPropertyBase(UCLPropertyBase propertyBase)
{
    cout << "属性值: "<<propertyBase.getVPart() << endl;
}

//CDPS, Keywords
void UCLPropertiesInfo::showCDPSKeywords(UCLPropertyBase keywords)
{
    int count = keywords.getLPartHead(3, 5) + 1;
    if (count <=7)
    {
        cout << "关键词数量: " << count << endl;
    }
    else
    {
        cout << "关键词数量超过7个" << endl;
    }

    cout << "关键词: ";
    vector<string> key = split(keywords.getVPart(), ";");

    copy(key.begin(), key.end(), ostream_iterator<string>(cout, " "));
    cout << endl;
}

//CDPS, author
void UCLPropertiesInfo::showCDPSAuthor(UCLPropertyBase author)
{
    int authorCount = author.getLPartHead(0, 2);
    int comCount = author.getLPartHead(3, 5);
    if (authorCount < 7)
    {
        cout << "作者数量: " << authorCount << "    ";
    }
    else
    {
        cout << "作者数量超过6个   ";
    }

    if (comCount < 7)
    {
        cout << "公司数量: " << comCount << endl;
    }
    else
    {
        cout << "公司数量超过七个" << endl;
    }

    cout << "作者 ----- 公司" << endl;
    vector<string> res = split(author.getVPart(), "\\r");

    for(int i = 0; i < res.size(); i++)
    {
        string tmp = res[i];
        vector<string> tr = split(tmp, ":");
        for(int j = 0; j < tr.size(); j++)
        {
            vector<string> ac = split(tr[j], ";");
            copy(ac.begin(), ac.end(), ostream_iterator<string>(cout, " "));
            if (j != tr.size() - 1)
                cout << "----- ";
        }
        cout << endl;
    }
}

//CDPS, entity
void UCLPropertiesInfo::showCDPSEntity(UCLPropertyBase ent)
{
    bitset<6> bqm(31);
    int es[bqm.count()];
    int j = 0;
    for (int i = 0; i < bqm.size(); i++)
    {
        if (bqm.test(i))
            es[j++] = i;
    }

    vector<string> ev = split(ent.getVPart(), "\\r");

    for (int i = 0; i < ev.size(); i++)
    {
        cout << entity[es[i]] << " : ";
        vector<string> evt = split(ev[i], ";");
        copy(evt.begin(), evt.end(), ostream_iterator<string>(cout, " "));
        cout << endl;
    }
}

//CDPS, tag
void UCLPropertiesInfo::showCDPSTag(UCLPropertyBase tag)
{
    int count = tag.getLPartHead(3, 5) + 1;
    if (count <=7)
    {
        cout << "标记数量: " << count << endl;
    }
    else
    {
        cout << "标记数量超过7个" << endl;
    }

    cout << "内容标记: ";
    vector<string> key = split(tag.getVPart(), ";");

    copy(key.begin(), key.end(), ostream_iterator<string>(cout, " "));
    cout << endl;
}

//CDPS, fileInfo
void UCLPropertiesInfo::showCDPSFileInfo(UCLPropertyBase fileInfo)
{
    vector<string> file = split(fileInfo.getVPart(), ";");
    cout << "文件信息: ";
    copy(file.begin(), file.end(), ostream_iterator<string>(cout, " "));
    cout << endl;
}

//CDPS, relatedUCL
void UCLPropertiesInfo::showCDPSRelatedUCL(UCLPropertyBase relatedUCL)
{
    int count = relatedUCL.getLPartHead(3, 5) + 1;
    if (count <=7)
    {
        cout << "关联UCL数量: " << count << endl;
    }
    else
    {
        cout << "关联UCL数量超过7个" << endl;
    }

    cout << "--------------------------关联UCL开始-----------------------------" << endl;
    //暂未考虑Code扩展
    string rus = relatedUCL.getVPart();
    int pos = 0;
    while (pos < rus.size())
    {
        string code = rus.substr(pos, 32);
        pos += 32;
        UCLCode uc;
        uc.unpack(code);
        if ((uc.getFlag() & 0x2) == 0)
        {
            cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
            uc.showCode();
            cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
        }
        else
        {
            uint8_t lh = rus[pos + 1];
            int propertyLenBytes = ((lh >> 6) & 0x3) + 1;
            string lValue = rus.substr(pos + 2, propertyLenBytes);
            int len = 0;
            switch (propertyLenBytes)
            {
                case 1:
                    len = (0xff & lValue[0]);
                    break;
                case 2:
                    len = (0xff & lValue[0]) +(0xff00 & (lValue[1] << 8));
                    break;
                case 3:
                    len = (0xff & lValue[0]) +(0xff00 & (lValue[1] << 8)) +
                          (0xff0000 & (lValue[2] << 16));
                    break;
                case 4:
                    len = (0xff & lValue[0]) +(0xff00 & (lValue[1] << 8)) +
                            (0xff0000 & (lValue[2] << 16)) + (0xff000000 & (lValue[3] << 24));
                    break;
            }
            string ucls = code + rus.substr(pos, len);
            UCL ucl;
            ucl.unpack(ucls);

            cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
            ucl.showUCL();
            cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
            pos += len;
        }
    }

    cout << "--------------------------关联UCL结束-----------------------------" << endl;
}

//CGPS, provenance
void UCLPropertiesInfo::showCGPSProvenance(UCLPropertyBase provenance)
{
    cout << "内容出处描述形式:  " << promap[provenance.getLPartHead(3, 5)] << endl;
    cout << "内容出处: " << provenance.getVPart() << endl;
}

//CGPS, content id
void UCLPropertiesInfo::showCGPSContentId(UCLPropertyBase content)
{
    cout << "内容ID解析规则: " << contentIdRulemap[content.getHelper()] << endl;
    cout << "详细内容ID信息: " << content.getVPart() << endl;
}

//CGPS, Propagation path
void UCLPropertiesInfo::showCGPSPropagationPath(UCLPropertyBase propagationPath)
{
    int count = propagationPath.getLPartHead(2, 5) + 1;
    if (count <=15)
    {
        cout << "传播路径长度: " << count << endl;
    }
    else
    {
        cout << "传播路径长度超过15" << endl;
    }

    cout << "传播路径: ";
    vector<string> key = split(propagationPath.getVPart(), ";");

    copy(key.begin(), key.end(), ostream_iterator<string>(cout, " "));
    cout << endl;
}

//CGPS, Signature of Content
void UCLPropertiesInfo::showCGPSSignatureContent(UCLPropertyBase sigContent)
{
    cout << "数字摘要算法: " << hash[sigContent.getLPartHead(2, 5)];
    cout << "   数字签名算法: " << signatureMap[sigContent.getHelper()] << endl;
    cout << "摘要或签名信息: " << sigContent.getVPart() << endl;
}

//CGPS, Security Energy Level Information
void UCLPropertiesInfo::showCGPSSELI(UCLPropertyBase seli)
{
    cout << "安全能级信息的认证等级: " << seliMap[seli.getHelper()] << endl;
    cout << "安全能级详细信息: " << seli.getVPart() << endl;
}

//CGPS, Chain of Responsibility
void UCLPropertiesInfo::showCGPSChainRespons(UCLPropertyBase cr)
{
    int count = cr.getLPartHead(2, 5) + 1;
    if (count <= 15)
    {
        cout << "责任主体数量: " << count << endl;
    }
    else
    {
        cout << "责任主体数量超过15个" << endl;
    }

    cout << "责任主体详细信息: ";
    vector<string> key = split(cr.getVPart(), ";");

    copy(key.begin(), key.end(), ostream_iterator<string>(cout, " "));
    cout << endl;
}

//CGPS, Signature of UCL Package
void UCLPropertiesInfo::showCGPSSignatureUP(UCLPropertyBase sup)
{
    cout << "数字摘要算法: " << hash[sup.getLPartHead(2, 5)];
    cout << "   数字签名算法: " << signatureMap[sup.getHelper()] << endl;
    cout << "摘要或签名信息: " << sup.getVPart() << endl;
}