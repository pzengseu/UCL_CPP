//
// Created by zp on 17-6-10.
//
#include <assert.h>
#include "test.h"
#include "../property/GenCDPSProperty.h"
#include "../property/GenCGPSProperty.h"
#include "digSignNo.h"

void testCommand()
{
    cout << "\n========== UCL test begin==========\n";
    UCL ucl;

    UCLCode code_test;

    code_test.setVersion(1);
    code_test.setTypeOfMedia(9);
    code_test.setPrioAndPoli(15);
    code_test.setFlag(50); //00110010
    code_test.setParseRule(0xfff1);//ff1有效
    code_test.setSourOfCont(0xfffffff1);//ffffff1有效
    code_test.setCategory(255);
    code_test.setSubCategory(257);//0x01有效
    code_test.setTopic(0xffffff1);
    code_test.setCopyAndTypeOfCont(254);
    code_test.setSecuEnerLeveCode(251);
    code_test.setLanguage(253);
    code_test.setSizeOfContent(31);
    code_test.setTimeStamp(0x3fffffffff9f9);
    /*
     * serinal number and multiplex bytes test cases
     * 0xCff1f3 - 0x8fffff31; 0x8f1f - 0x1f3f5f7f9f; 0x4f - 0x1f3f5f7f9f48; 0xf - 0x1f3f5f7f9f48
     */
    code_test.setSerialNumber(0x4f);
    code_test.setMultiplexBytes(0x1f3f5f7f9f48);

    code_test.setVersion(3);//对于已经设置过的域重复设置

    ucl.setUclCode(code_test);

    cout << "\n##############测试属性##############\n\n";
    UCLPropertySet cdps = generateCDPS();
    ucl.setPropertySet(cdps);

    UCLPropertySet cgps = generateCGPS();
    ucl.setPropertySet(cgps);

    /*
     * 测试关联UCL
     */
    string rstr = "";

    UCLCode rCode = code_test;
    rCode.setFlag(0);
    rstr += rCode.pack();

    UCL rUCL = generateRUCL();
    rstr += rUCL.pack();

    UCLPropertyBase related = GenCDPSProperty::genRelatedUCL(2, rstr);
    ucl.setProperty(1, related);

//    cout << "\n##############测试打包##############\n\n";
    cout << "--------------UCLPackage-------------- \n";
//    assert(ucl.pack() == ucl.pack());
    printPackString(ucl.pack());
    cout << "--------------显示UCL各部分关键信息--------------\n";
    ucl.showUCL();

    cout << "\n##############测试解包##############\n\n";
    UCL ucl2;
    ucl2.unpack(ucl.pack());
    cout << "--------------UCLPackage--------------\n";
    printPackString(ucl2.pack());
    cout << "--------------解包后UCL各部分关键信息--------------\n";
    ucl2.showUCL();

    cout << "========== UCL test end==========\n";

//    printPackString(ucl.pack());
//    printPackString(ucl2.pack());
}

void printPackString(string pack)
{
    for(int i=0; i < pack.size(); i++) {
        cout << setw(2) << setfill('0') << hex << ((uint16_t)pack[i] & 0xff) << "-";
    }
    cout << "\n\n";
}

UCLPropertySet generateCDPS()
{
    UCLPropertySet cdps;
    cdps.setHeadCategory(1);
    UCLPropertyBase title = GenCDPSProperty::genTitle("江苏今年起实施“12311”计划 培育百个农业特色镇");
    UCLPropertyBase keywords = GenCDPSProperty::genKeywords(3, "江苏;乡村;国家");
    UCLPropertyBase abstract = GenCDPSProperty::genAbstract("省农委日前在金坛召开全省创意休闲农业工作推进会，决定从今年起实施“12311”创意休闲农业省级特色品牌培育计划");
    UCLPropertyBase author = GenCDPSProperty::genAuthor(3, 2, "邹建丰:新华日报\\r张三;李四:新浪");
    UCLPropertyBase entity = GenCDPSProperty::genEntity(31, "江苏省委\\r2017\\r金坛\\r培育计划\\r美丽;nice");
    UCLPropertyBase tag = GenCDPSProperty::genTag(2, "美丽;乡村");
    UCLPropertyBase copyright = GenCDPSProperty::genCopyright("新华日报");
    UCLPropertyBase origin = GenCDPSProperty::genOriginality("皱建丰");
    UCLPropertyBase file = GenCDPSProperty::genFileDescription("文本;10M");
    UCLPropertyBase content = GenCDPSProperty::genContObject("江苏今年起实施“12311”计划, 全省创意休闲农业工作推进会");
    cdps.setProperty(title);
    cdps.setProperty(keywords);
    cdps.setProperty(abstract);
    cdps.setProperty(author);
    cdps.setProperty(entity);
    cdps.setProperty(tag);
    cdps.setProperty(copyright);
    cdps.setProperty(origin);
    cdps.setProperty(file);
    cdps.setProperty(content);

    return cdps;
}

UCLPropertySet generateCGPS()
{
    UCLPropertySet cgps;
    cgps.setHeadCategory(15);
    UCLPropertyBase pro = GenCGPSProperty::genProvenance(1, "http://jiangsu.sina.com.cn/news/b/2017-05-31/detail-ifyfqqyh9080015.shtml");
    cgps.setProperty(pro);
    UCLPropertyBase contentid = GenCGPSProperty::genContId("sina");
    cgps.setProperty(contentid);
    UCLPropertyBase prog = GenCGPSProperty::genPropagation(2, "baidu;sina");
    cgps.setProperty(prog);
    UCLPropertyBase sigCon = GenCGPSProperty::genContSig("江苏今年起实施“12311”计划, 全省创意休闲农业工作推进会", 2, 0);
    cgps.setProperty(sigCon);
    UCLPropertyBase security = GenCGPSProperty::genSecEL("重要");
    cgps.setProperty(security);
    UCLPropertyBase chain = GenCGPSProperty::genChainOfRes(2, "sian;seu");
    cgps.setProperty(chain);
    UCLPropertyBase sigUCL = GenCGPSProperty::genUCLSig(SHA_512, DSA);
    cgps.setProperty(sigUCL);

    return cgps;
}
UCLPropertySet generatePersonalPropertySet()
{
    UCLPropertySet personal;
    personal.setHeadCategory(10);

    UCLPropertyBase name;
    name.setProperty(1, 1, "曾朋");
    personal.setProperty(name);

    UCLPropertyBase school;
    school.setProperty(2, 1, "SEU");
    personal.setProperty(school);

    return personal;
}

UCL generateRUCL()
{
    UCL ucl;

    UCLCode code_test;

    code_test.setVersion(1);
    code_test.setTypeOfMedia(9);
    code_test.setPrioAndPoli(15);
    code_test.setFlag(2); //00000010
    code_test.setParseRule(0xfff1);//ff1有效
    code_test.setSourOfCont(0xfffffff1);//ffffff1有效
    code_test.setCategory(255);
    code_test.setSubCategory(257);//0x01有效
    code_test.setTopic(0xffffff1);
    code_test.setCopyAndTypeOfCont(254);
    code_test.setSecuEnerLeveCode(251);
    code_test.setLanguage(253);
    code_test.setSizeOfContent(31);
    code_test.setTimeStamp(0x3fffffffff9f9);
    /*
     * serinal number and multiplex bytes test cases
     * 0xCff1f3 - 0x8fffff31; 0x8f1f - 0x1f3f5f7f9f; 0x4f - 0x1f3f5f7f9f48; 0xf - 0x1f3f5f7f9f48
     */
    code_test.setSerialNumber(0x4f);
    code_test.setMultiplexBytes(0x1f3f5f7f9f48);

    code_test.setVersion(3);//对于已经设置过的域重复设置

    ucl.setUclCode(code_test);

    UCLPropertySet cdps;
    cdps.setHeadCategory(1);
    UCLPropertyBase title = GenerateProperty::generateCDPSTitle("江苏今年起实施“12311”计划 培育百个农业特色镇");
    cdps.setProperty(title);

//    cout << hex << cdps.generateQuickMatcher()<< "  " << cdps.getPropertyHead().getTotalLength() << endl;
//    cout << "--------------CDPS-------------- \n";
//    printPackString(cdps.pack());

    ucl.setPropertySet(cdps);

    UCLPropertySet cgps;
    cgps.setHeadCategory(15);
    UCLPropertyBase pro = GenerateProperty::generateCGPSProvenance(1, "http://jiangsu.sina.com.cn/news/b/2017-05-31/detail-ifyfqqyh9080015.shtml");
    cgps.setProperty(pro);
    UCLPropertyBase chain = GenerateProperty::generateCGPSChain(2, "sian;seu");
    cgps.setProperty(chain);
    UCLPropertyBase sigUCL = GenerateProperty::generateCGPSSignatureUCL(1, 0);
    cgps.setProperty(sigUCL);
//    cout << "--------------CGPS-------------- \n";
//    printPackString(cgps.pack());

    ucl.setPropertySet(cgps);

    UCLPropertySet personal = generatePersonalPropertySet();
    ucl.setPropertySet(personal);

    return ucl;
}