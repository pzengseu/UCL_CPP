# 使用指南
1. 建立UCL对象
```
UCL ucl；
```

2. 添加UCLCode对象
```
UCLCode uclCode;
```
然后使用UCLCode中的setXXX方法设置UCLCode中各个域的值。
```
ucl.setUclCode(uclCode); //设置uclCode部分
```

3. 自定义属性
```
UCLPropertyBase nr;
GenerateProperty::setProperty(nr, 0x2, 0, " ");
```
即新建了属性nr，可参考GenerateProerty类。

4. 创建固有属性集合-CDPS
```
UCLPropertySet cdps;
cdps.setHeadCategory(1);
UCLPropertyBase title = GenerateProperty::generateCDPSTitle("江苏今年起实施“12311”计划 培育百个农业特色镇");
UCLPropertyBase keywords = GenerateProperty::generateCDPSKeywords(3, "江苏;乡村;国家");
UCLPropertyBase abstract = GenerateProperty::generateCDPSAbstract("省农委日前在金坛召开全省创意休闲农业工作推进会，决定从今年起实施“12311”创意休闲农业省级特色品牌培育计划");
UCLPropertyBase author = GenerateProperty::generateCDPSAuthor(2, 2, "邹建丰:新华日报\\r微博;博客:新浪");
UCLPropertyBase entity = GenerateProperty::generateCDPSEntity(31, "江苏省委\\r2017\\r金坛\\r培育计划\\r美丽");
UCLPropertyBase tag = GenerateProperty::generateCDPSTag(2, "美丽;乡村");
UCLPropertyBase copyright = GenerateProperty::generateCDPSCopyright("新华日报");
UCLPropertyBase origin = GenerateProperty::generateCDPSOriginality("皱建丰");
UCLPropertyBase file = GenerateProperty::generateCDPSFileDescription("文本;10M");
UCLPropertyBase related = GenerateProperty::generateCDPSRelatedUCL(3, "ucl1;ucl2;ucl3");
UCLPropertyBase content = GenerateProperty::generateCDPSContentObject("江苏今年起实施“12311”计划, 全省创意休闲农业工作推进会");
cdps.setProperty(title);
cdps.setProperty(keywords);
cdps.setProperty(abstract);
cdps.setProperty(author);
cdps.setProperty(entity);
cdps.setProperty(tag);
cdps.setProperty(copyright);
cdps.setProperty(origin);
cdps.setProperty(file);
cdps.setProperty(related);
cdps.setProperty(content);

ucl.setPropertySet(cdps);
```
- 首先新建集合对象;
- 然后调用setHeadCategory方法设置集合类别;
- 创建固有属性或自定义属性;
- 将属性添加到属性集合中。
- 将属性集合添加到UCL中。

5. 创建固有属性集合-CGPS
```
UCLPropertySet cgps;
cgps.setHeadCategory(15);
UCLPropertyBase pro = GenerateProperty::generateCGPSProvenance(1, "http://jiangsu.sina.com.cn/news/b/2017-05-31/detail-ifyfqqyh9080015.shtml");
cgps.setProperty(pro);
UCLPropertyBase contentid = GenerateProperty::generateCGPSContentid("sina");
cgps.setProperty(contentid);
UCLPropertyBase prog = GenerateProperty::generateCGPSPropagation(2, "baidu;sina");
cgps.setProperty(prog);
UCLPropertyBase sigCon = GenerateProperty::generateCGPSSignatureContent("江苏今年起实施“12311”计划, 全省创意休闲农业工作推进会", 3, 0);
cgps.setProperty(sigCon);
UCLPropertyBase security = GenerateProperty::generateCGPSSecurity("重要");
cgps.setProperty(security);
UCLPropertyBase chain = GenerateProperty::generateCGPSChain(2, "sian;seu");
cgps.setProperty(chain);
UCLPropertyBase sigUCL = GenerateProperty::generateCGPSSignatureUCL(3, 0);
cgps.setProperty(sigUCL);

ucl.setPropertySet(cgps);
```

6. 打包解包
```
string ucl1 = ucl.pack();

UCL ucl2;
ucl2.unpack(ucl1);
```
- 打包ucl对象成string对象；
- 将string对象解包成ucl对象，从而可以获取每个字段值。

#### 参考test.h中testEasy()方法, 运行输出如下。
```
CDPS: 
01-68-fd-01-fe-c3-01-00-45-e6-b1-9f-e8-8b-8f-e4-bb-8a-e5-b9-b4-e8-b5-b7-e5-ae-9e-e6-96-bd-e2-80-9c-31-32-33-31-31-e2-80-9d-e8-ae-a1-e5-88-92-20-e5-9f-b9-e8-82-b2-e7-99-be-e4-b8-aa-e5-86-9c-e4-b8-9a-e7-89-b9-e8-89-b2-e9-95-87-02-10-17-e6-b1-9f-e8-8b-8f-3b-e4-b9-a1-e6-9d-91-3b-e5-9b-bd-e5-ae-b6-03-00-9e-e7-9c-81-e5-86-9c-e5-a7-94-e6-97-a5-e5-89-8d-e5-9c-a8-e9-87-91-e5-9d-9b-e5-8f-ac-e5-bc-80-e5-85-a8-e7-9c-81-e5-88-9b-e6-84-8f-e4-bc-91-e9-97-b2-e5-86-9c-e4-b8-9a-e5-b7-a5-e4-bd-9c-e6-8e-a8-e8-bf-9b-e4-bc-9a-ef-bc-8c-e5-86-b3-e5-ae-9a-e4-bb-8e-e4-bb-8a-e5-b9-b4-e8-b5-b7-e5-ae-9e-e6-96-bd-e2-80-9c-31-32-33-31-31-e2-80-9d-e5-88-9b-e6-84-8f-e4-bc-91-e9-97-b2-e5-86-9c-e4-b8-9a-e7-9c-81-e7-ba-a7-e7-89-b9-e8-89-b2-e5-93-81-e7-89-8c-e5-9f-b9-e8-82-b2-e8-ae-a1-e5-88-92-04-12-2f-e9-82-b9-e5-bb-ba-e4-b8-b0-3a-e6-96-b0-e5-8d-8e-e6-97-a5-e6-8a-a5-5c-72-e5-be-ae-e5-8d-9a-3b-e5-8d-9a-e5-ae-a2-3a-e6-96-b0-e6-b5-aa-05-1f-33-e6-b1-9f-e8-8b-8f-e7-9c-81-e5-a7-94-5c-72-32-30-31-37-5c-72-e9-87-91-e5-9d-9b-5c-72-e5-9f-b9-e8-82-b2-e8-ae-a1-e5-88-92-5c-72-e7-be-8e-e4-b8-bd-06-08-10-e7-be-8e-e4-b8-bd-3b-e4-b9-a1-e6-9d-91-07-00-0f-e6-96-b0-e5-8d-8e-e6-97-a5-e6-8a-a5-08-00-0c-e7-9a-b1-e5-bb-ba-e4-b8-b0-09-00-0d-e6-96-87-e6-9c-ac-3b-31-30-4d-0e-10-11-75-63-6c-31-3b-75-63-6c-32-3b-75-63-6c-33-0f-00-52-e6-b1-9f-e8-8b-8f-e4-bb-8a-e5-b9-b4-e8-b5-b7-e5-ae-9e-e6-96-bd-e2-80-9c-31-32-33-31-31-e2-80-9d-e8-ae-a1-e5-88-92-2c-20-e5-85-a8-e7-9c-81-e5-88-9b-e6-84-8f-e4-bc-91-e9-97-b2-e5-86-9c-e4-b8-9a-e5-b7-a5-e4-bd-9c-e6-8e-a8-e8-bf-9b-e4-bc-9a-00-
------------
CGPS: 
0f-18-bf-38-f0-03-08-4c-68-74-74-70-3a-2f-2f-6a-69-61-6e-67-73-75-2e-73-69-6e-61-2e-63-6f-6d-2e-63-6e-2f-6e-65-77-73-2f-62-2f-32-30-31-37-2d-30-35-2d-33-31-2f-64-65-74-61-69-6c-2d-69-66-79-66-71-71-79-68-39-30-38-30-30-31-35-2e-73-68-74-6d-6c-04-00-07-73-69-6e-61-05-04-0d-62-61-69-64-75-3b-73-69-6e-61-0c-0c-43-37-36-66-39-62-39-31-62-65-37-30-30-65-30-64-31-38-61-30-63-63-35-63-65-38-65-61-36-64-65-39-36-65-38-65-37-34-34-66-38-36-62-63-39-31-39-31-37-30-34-65-35-37-31-61-30-31-63-37-66-65-35-62-65-0d-00-09-e9-87-8d-e8-a6-81-0e-04-0b-73-69-61-6e-3b-73-65-75-0f-0c-03-00-
------------
propertySet: 
02-44-c2-02-02-80-01-68-fd-01-fe-c3-01-00-45-e6-b1-9f-e8-8b-8f-e4-bb-8a-e5-b9-b4-e8-b5-b7-e5-ae-9e-e6-96-bd-e2-80-9c-31-32-33-31-31-e2-80-9d-e8-ae-a1-e5-88-92-20-e5-9f-b9-e8-82-b2-e7-99-be-e4-b8-aa-e5-86-9c-e4-b8-9a-e7-89-b9-e8-89-b2-e9-95-87-02-10-17-e6-b1-9f-e8-8b-8f-3b-e4-b9-a1-e6-9d-91-3b-e5-9b-bd-e5-ae-b6-03-00-9e-e7-9c-81-e5-86-9c-e5-a7-94-e6-97-a5-e5-89-8d-e5-9c-a8-e9-87-91-e5-9d-9b-e5-8f-ac-e5-bc-80-e5-85-a8-e7-9c-81-e5-88-9b-e6-84-8f-e4-bc-91-e9-97-b2-e5-86-9c-e4-b8-9a-e5-b7-a5-e4-bd-9c-e6-8e-a8-e8-bf-9b-e4-bc-9a-ef-bc-8c-e5-86-b3-e5-ae-9a-e4-bb-8e-e4-bb-8a-e5-b9-b4-e8-b5-b7-e5-ae-9e-e6-96-bd-e2-80-9c-31-32-33-31-31-e2-80-9d-e5-88-9b-e6-84-8f-e4-bc-91-e9-97-b2-e5-86-9c-e4-b8-9a-e7-9c-81-e7-ba-a7-e7-89-b9-e8-89-b2-e5-93-81-e7-89-8c-e5-9f-b9-e8-82-b2-e8-ae-a1-e5-88-92-04-12-2f-e9-82-b9-e5-bb-ba-e4-b8-b0-3a-e6-96-b0-e5-8d-8e-e6-97-a5-e6-8a-a5-5c-72-e5-be-ae-e5-8d-9a-3b-e5-8d-9a-e5-ae-a2-3a-e6-96-b0-e6-b5-aa-05-1f-33-e6-b1-9f-e8-8b-8f-e7-9c-81-e5-a7-94-5c-72-32-30-31-37-5c-72-e9-87-91-e5-9d-9b-5c-72-e5-9f-b9-e8-82-b2-e8-ae-a1-e5-88-92-5c-72-e7-be-8e-e4-b8-bd-06-08-10-e7-be-8e-e4-b8-bd-3b-e4-b9-a1-e6-9d-91-07-00-0f-e6-96-b0-e5-8d-8e-e6-97-a5-e6-8a-a5-08-00-0c-e7-9a-b1-e5-bb-ba-e4-b8-b0-09-00-0d-e6-96-87-e6-9c-ac-3b-31-30-4d-0e-10-11-75-63-6c-31-3b-75-63-6c-32-3b-75-63-6c-33-0f-00-52-e6-b1-9f-e8-8b-8f-e4-bb-8a-e5-b9-b4-e8-b5-b7-e5-ae-9e-e6-96-bd-e2-80-9c-31-32-33-31-31-e2-80-9d-e8-ae-a1-e5-88-92-2c-20-e5-85-a8-e7-9c-81-e5-88-9b-e6-84-8f-e4-bc-91-e9-97-b2-e5-86-9c-e4-b8-9a-e5-b7-a5-e4-bd-9c-e6-8e-a8-e8-bf-9b-e4-bc-9a-0f-18-bf-38-f0-03-08-4c-68-74-74-70-3a-2f-2f-6a-69-61-6e-67-73-75-2e-73-69-6e-61-2e-63-6f-6d-2e-63-6e-2f-6e-65-77-73-2f-62-2f-32-30-31-37-2d-30-35-2d-33-31-2f-64-65-74-61-69-6c-2d-69-66-79-66-71-71-79-68-39-30-38-30-30-31-35-2e-73-68-74-6d-6c-04-00-07-73-69-6e-61-05-04-0d-62-61-69-64-75-3b-73-69-6e-61-0c-0c-43-37-36-66-39-62-39-31-62-65-37-30-30-65-30-64-31-38-61-30-63-63-35-63-65-38-65-61-36-64-65-39-36-65-38-65-37-34-34-66-38-36-62-63-39-31-39-31-37-30-34-65-35-37-31-61-30-31-63-37-66-65-35-62-65-0d-00-09-e9-87-8d-e8-a6-81-0e-04-0b-73-69-61-6e-3b-73-65-75-0f-0c-03-00-
------------
UCLPackage: 
69-fd-ff-1f-ff-ff-f1-ff-01-0f-ff-ff-f1-fe-fc-fb-ff-ff-ff-ff-ff-ff-ff-ff-ff-ff-ff-ff-ff-ff-67-55-02-44-02-03-02-80-01-68-fd-01-fe-c3-01-00-45-e6-b1-9f-e8-8b-8f-e4-bb-8a-e5-b9-b4-e8-b5-b7-e5-ae-9e-e6-96-bd-e2-80-9c-31-32-33-31-31-e2-80-9d-e8-ae-a1-e5-88-92-20-e5-9f-b9-e8-82-b2-e7-99-be-e4-b8-aa-e5-86-9c-e4-b8-9a-e7-89-b9-e8-89-b2-e9-95-87-02-10-17-e6-b1-9f-e8-8b-8f-3b-e4-b9-a1-e6-9d-91-3b-e5-9b-bd-e5-ae-b6-03-00-9e-e7-9c-81-e5-86-9c-e5-a7-94-e6-97-a5-e5-89-8d-e5-9c-a8-e9-87-91-e5-9d-9b-e5-8f-ac-e5-bc-80-e5-85-a8-e7-9c-81-e5-88-9b-e6-84-8f-e4-bc-91-e9-97-b2-e5-86-9c-e4-b8-9a-e5-b7-a5-e4-bd-9c-e6-8e-a8-e8-bf-9b-e4-bc-9a-ef-bc-8c-e5-86-b3-e5-ae-9a-e4-bb-8e-e4-bb-8a-e5-b9-b4-e8-b5-b7-e5-ae-9e-e6-96-bd-e2-80-9c-31-32-33-31-31-e2-80-9d-e5-88-9b-e6-84-8f-e4-bc-91-e9-97-b2-e5-86-9c-e4-b8-9a-e7-9c-81-e7-ba-a7-e7-89-b9-e8-89-b2-e5-93-81-e7-89-8c-e5-9f-b9-e8-82-b2-e8-ae-a1-e5-88-92-04-12-2f-e9-82-b9-e5-bb-ba-e4-b8-b0-3a-e6-96-b0-e5-8d-8e-e6-97-a5-e6-8a-a5-5c-72-e5-be-ae-e5-8d-9a-3b-e5-8d-9a-e5-ae-a2-3a-e6-96-b0-e6-b5-aa-05-1f-33-e6-b1-9f-e8-8b-8f-e7-9c-81-e5-a7-94-5c-72-32-30-31-37-5c-72-e9-87-91-e5-9d-9b-5c-72-e5-9f-b9-e8-82-b2-e8-ae-a1-e5-88-92-5c-72-e7-be-8e-e4-b8-bd-06-08-10-e7-be-8e-e4-b8-bd-3b-e4-b9-a1-e6-9d-91-07-00-0f-e6-96-b0-e5-8d-8e-e6-97-a5-e6-8a-a5-08-00-0c-e7-9a-b1-e5-bb-ba-e4-b8-b0-09-00-0d-e6-96-87-e6-9c-ac-3b-31-30-4d-0e-10-11-75-63-6c-31-3b-75-63-6c-32-3b-75-63-6c-33-0f-00-52-e6-b1-9f-e8-8b-8f-e4-bb-8a-e5-b9-b4-e8-b5-b7-e5-ae-9e-e6-96-bd-e2-80-9c-31-32-33-31-31-e2-80-9d-e8-ae-a1-e5-88-92-2c-20-e5-85-a8-e7-9c-81-e5-88-9b-e6-84-8f-e4-bc-91-e9-97-b2-e5-86-9c-e4-b8-9a-e5-b7-a5-e4-bd-9c-e6-8e-a8-e8-bf-9b-e4-bc-9a-0f-18-ff-38-f0-03-08-4c-68-74-74-70-3a-2f-2f-6a-69-61-6e-67-73-75-2e-73-69-6e-61-2e-63-6f-6d-2e-63-6e-2f-6e-65-77-73-2f-62-2f-32-30-31-37-2d-30-35-2d-33-31-2f-64-65-74-61-69-6c-2d-69-66-79-66-71-71-79-68-39-30-38-30-30-31-35-2e-73-68-74-6d-6c-04-00-07-73-69-6e-61-05-04-0d-62-61-69-64-75-3b-73-69-6e-61-0c-0c-43-37-36-66-39-62-39-31-62-65-37-30-30-65-30-64-31-38-61-30-63-63-35-63-65-38-65-61-36-64-65-39-36-65-38-65-37-34-34-66-38-36-62-63-39-31-39-31-37-30-34-65-35-37-31-61-30-31-63-37-66-65-35-62-65-0d-00-09-e9-87-8d-e8-a6-81-0e-04-0b-73-69-61-6e-3b-73-65-75-0f-0c-43-61-63-39-32-63-32-66-38-30-65-66-66-35-36-34-64-30-64-35-66-62-66-63-33-64-37-37-61-37-31-38-38-64-61-63-64-62-61-63-66-31-33-63-61-65-31-32-37-33-61-36-34-64-34-62-61-31-65-36-37-33-66-33-66-00-
------------
The size of propertySet:2
The category of propertySet: 1
The category and value of property: 1   江苏今年起实施“12311”计划 培育百个农业特色镇
The category and value of property: 2   江苏;乡村;国家
The category and value of property: 3   省农委日前在金坛召开全省创意休闲农业工作推进会，决定从今年起实施“12311”创意休闲农业省级特色品牌培育计划
The category and value of property: 4   邹建丰:新华日报\r微博;博客:新浪
The category and value of property: 5   江苏省委\r2017\r金坛\r培育计划\r美丽
The category and value of property: 6   美丽;乡村
The category and value of property: 7   新华日报
The category and value of property: 8   皱建丰
The category and value of property: 9   文本;10M
The category and value of property: e   ucl1;ucl2;ucl3
The category and value of property: f   江苏今年起实施“12311”计划, 全省创意休闲农业工作推进会
The category of propertySet: f
The category and value of property: 3   http://jiangsu.sina.com.cn/news/b/2017-05-31/detail-ifyfqqyh9080015.shtml
The category and value of property: 4   sina
The category and value of property: 5   baidu;sina
The category and value of property: c   76f9b91be700e0d18a0cc5ce8ea6de96e8e744f86bc9191704e571a01c7fe5be
The category and value of property: d   重要
The category and value of property: e   sian;seu
The category and value of property: f   ac92c2f80eff564d0d5fbfc3d77a7188dacdbacf13cae1273a64d4ba1e673f3f
UCLPackage: 
69-fd-ff-1f-ff-ff-f1-ff-01-0f-ff-ff-f1-fe-fc-fb-ff-ff-ff-ff-ff-ff-ff-ff-ff-ff-ff-ff-ff-ff-67-55-02-44-02-03-02-80-01-68-fd-01-fe-c3-01-00-45-e6-b1-9f-e8-8b-8f-e4-bb-8a-e5-b9-b4-e8-b5-b7-e5-ae-9e-e6-96-bd-e2-80-9c-31-32-33-31-31-e2-80-9d-e8-ae-a1-e5-88-92-20-e5-9f-b9-e8-82-b2-e7-99-be-e4-b8-aa-e5-86-9c-e4-b8-9a-e7-89-b9-e8-89-b2-e9-95-87-02-10-17-e6-b1-9f-e8-8b-8f-3b-e4-b9-a1-e6-9d-91-3b-e5-9b-bd-e5-ae-b6-03-00-9e-e7-9c-81-e5-86-9c-e5-a7-94-e6-97-a5-e5-89-8d-e5-9c-a8-e9-87-91-e5-9d-9b-e5-8f-ac-e5-bc-80-e5-85-a8-e7-9c-81-e5-88-9b-e6-84-8f-e4-bc-91-e9-97-b2-e5-86-9c-e4-b8-9a-e5-b7-a5-e4-bd-9c-e6-8e-a8-e8-bf-9b-e4-bc-9a-ef-bc-8c-e5-86-b3-e5-ae-9a-e4-bb-8e-e4-bb-8a-e5-b9-b4-e8-b5-b7-e5-ae-9e-e6-96-bd-e2-80-9c-31-32-33-31-31-e2-80-9d-e5-88-9b-e6-84-8f-e4-bc-91-e9-97-b2-e5-86-9c-e4-b8-9a-e7-9c-81-e7-ba-a7-e7-89-b9-e8-89-b2-e5-93-81-e7-89-8c-e5-9f-b9-e8-82-b2-e8-ae-a1-e5-88-92-04-12-2f-e9-82-b9-e5-bb-ba-e4-b8-b0-3a-e6-96-b0-e5-8d-8e-e6-97-a5-e6-8a-a5-5c-72-e5-be-ae-e5-8d-9a-3b-e5-8d-9a-e5-ae-a2-3a-e6-96-b0-e6-b5-aa-05-1f-33-e6-b1-9f-e8-8b-8f-e7-9c-81-e5-a7-94-5c-72-32-30-31-37-5c-72-e9-87-91-e5-9d-9b-5c-72-e5-9f-b9-e8-82-b2-e8-ae-a1-e5-88-92-5c-72-e7-be-8e-e4-b8-bd-06-08-10-e7-be-8e-e4-b8-bd-3b-e4-b9-a1-e6-9d-91-07-00-0f-e6-96-b0-e5-8d-8e-e6-97-a5-e6-8a-a5-08-00-0c-e7-9a-b1-e5-bb-ba-e4-b8-b0-09-00-0d-e6-96-87-e6-9c-ac-3b-31-30-4d-0e-10-11-75-63-6c-31-3b-75-63-6c-32-3b-75-63-6c-33-0f-00-52-e6-b1-9f-e8-8b-8f-e4-bb-8a-e5-b9-b4-e8-b5-b7-e5-ae-9e-e6-96-bd-e2-80-9c-31-32-33-31-31-e2-80-9d-e8-ae-a1-e5-88-92-2c-20-e5-85-a8-e7-9c-81-e5-88-9b-e6-84-8f-e4-bc-91-e9-97-b2-e5-86-9c-e4-b8-9a-e5-b7-a5-e4-bd-9c-e6-8e-a8-e8-bf-9b-e4-bc-9a-0f-18-ff-38-f0-03-08-4c-68-74-74-70-3a-2f-2f-6a-69-61-6e-67-73-75-2e-73-69-6e-61-2e-63-6f-6d-2e-63-6e-2f-6e-65-77-73-2f-62-2f-32-30-31-37-2d-30-35-2d-33-31-2f-64-65-74-61-69-6c-2d-69-66-79-66-71-71-79-68-39-30-38-30-30-31-35-2e-73-68-74-6d-6c-04-00-07-73-69-6e-61-05-04-0d-62-61-69-64-75-3b-73-69-6e-61-0c-0c-43-37-36-66-39-62-39-31-62-65-37-30-30-65-30-64-31-38-61-30-63-63-35-63-65-38-65-61-36-64-65-39-36-65-38-65-37-34-34-66-38-36-62-63-39-31-39-31-37-30-34-65-35-37-31-61-30-31-63-37-66-65-35-62-65-0d-00-09-e9-87-8d-e8-a6-81-0e-04-0b-73-69-61-6e-3b-73-65-75-0f-0c-43-61-63-39-32-63-32-66-38-30-65-66-66-35-36-34-64-30-64-35-66-62-66-63-33-64-37-37-61-37-31-38-38-64-61-63-64-62-61-63-66-31-33-63-61-65-31-32-37-33-61-36-34-64-34-62-61-31-65-36-37-33-66-33-66-00-
------------
The size of propertySet:2
The category of propertySet: 1
The category and value of property: 1   江苏今年起实施“12311”计划 培育百个农业特色镇
The category and value of property: 2   江苏;乡村;国家
The category and value of property: 3   省农委日前在金坛召开全省创意休闲农业工作推进会，决定从今年起实施“12311”创意休闲农业省级特色品牌培育计划
The category and value of property: 4   邹建丰:新华日报\r微博;博客:新浪
The category and value of property: 5   江苏省委\r2017\r金坛\r培育计划\r美丽
The category and value of property: 6   美丽;乡村
The category and value of property: 7   新华日报
The category and value of property: 8   皱建丰
The category and value of property: 9   文本;10M
The category and value of property: e   ucl1;ucl2;ucl3
The category and value of property: f   江苏今年起实施“12311”计划, 全省创意休闲农业工作推进会
The category of propertySet: f
The category and value of property: 3   http://jiangsu.sina.com.cn/news/b/2017-05-31/detail-ifyfqqyh9080015.shtml
The category and value of property: 4   sina
The category and value of property: 5   baidu;sina
The category and value of property: c   76f9b91be700e0d18a0cc5ce8ea6de96e8e744f86bc9191704e571a01c7fe5be
The category and value of property: d   重要
The category and value of property: e   sian;seu
The category and value of property: f   ac92c2f80eff564d0d5fbfc3d77a7188dacdbacf13cae1273a64d4ba1e673f3f

Process finished with exit code 0
```


