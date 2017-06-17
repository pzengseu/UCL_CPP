# UCL控制台使用教程
1. 建立UCL对象
```
UCL ucl；
```

2. 添加UCLCode对象
```
UCLCode uclCode;
```
然后使用UCLCode中的setXXX方法设置UCLCode中各个域的值（code check会根据需要自动生成）。
```
//所有参数均为uint64_t
code_test.setVersion(1);
code_test.setTypeOfMedia(9);
code_test.setPrioAndPoli(15);
code_test.setFlag(50); //00100010
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
```

3. 自定义属性
```
UCLPropertyBase nr;
nr.setProperty(nr, 0x2, 0, " ");
```
即新建了属性nr，可参考GenerateProerty类。

4. 创建固有属性集合-CDPS
```
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
UCLPropertyBase sigUCL = GenCGPSProperty::genUCLSig(3, 0);
cgps.setProperty(sigUCL);
ucl.setPropertySet(cgps);
```

6. 自定义personal属性集合
```
UCLPropertySet personal;
personal.setHeadCategory(10);

UCLPropertyBase name;
name.setProperty(1, 1, "曾朋");
personal.setProperty(name);

UCLPropertyBase school;
school.setProperty(2, 1, "SEU");
personal.setProperty(school);
```

7. UCL中增加关联UCL
```
string rstr = "";

UCLCode rCode = code_test;
rCode.setFlag(0);
rstr += rCode.pack();

UCL rUCL = generateRUCL();
rstr += rUCL.pack();

UCLPropertyBase related = GenCDPSProperty::genRelatedUCL(2, rstr);
ucl.setProperty(1, related);
```

8. 打包解包
```
ucl.pack()  //自动生成摘要字段,并返回打包的string流

UCL ucl2;
ucl2.unpack(ucl.pack());  
```
- 自动生成摘要字段, 打包ucl对象成string对象；
- 将string对象解包成ucl对象, 从而可以获取每个字段值。

#### UCL控制台例子testEasy(), 输出如下。
```
/home/zp/UCL_CPP/cmake-build-debug/UCL_CPP

========== UCL test begin==========

##############测试属性##############

--------------UCLPackage-------------- 
69-0f-32-ff-1f-ff-ff-f1-ff-01-0f-ff-ff-f1-fe-fb-fd-ff-ff-ff-ff-f9-f9-4f-1f-3f-5f-7f-9f-48-93-7a-01-44-e4-03-02-80-01-68-ff-02-fe-c3-01-00-45-e6-b1-9f-e8-8b-8f-e4-bb-8a-e5-b9-b4-e8-b5-b7-e5-ae-9e-e6-96-bd-e2-80-9c-31-32-33-31-31-e2-80-9d-e8-ae-a1-e5-88-92-20-e5-9f-b9-e8-82-b2-e7-99-be-e4-b8-aa-e5-86-9c-e4-b8-9a-e7-89-b9-e8-89-b2-e9-95-87-02-10-17-e6-b1-9f-e8-8b-8f-3b-e4-b9-a1-e6-9d-91-3b-e5-9b-bd-e5-ae-b6-03-00-9e-e7-9c-81-e5-86-9c-e5-a7-94-e6-97-a5-e5-89-8d-e5-9c-a8-e9-87-91-e5-9d-9b-e5-8f-ac-e5-bc-80-e5-85-a8-e7-9c-81-e5-88-9b-e6-84-8f-e4-bc-91-e9-97-b2-e5-86-9c-e4-b8-9a-e5-b7-a5-e4-bd-9c-e6-8e-a8-e8-bf-9b-e4-bc-9a-ef-bc-8c-e5-86-b3-e5-ae-9a-e4-bb-8e-e4-bb-8a-e5-b9-b4-e8-b5-b7-e5-ae-9e-e6-96-bd-e2-80-9c-31-32-33-31-31-e2-80-9d-e5-88-9b-e6-84-8f-e4-bc-91-e9-97-b2-e5-86-9c-e4-b8-9a-e7-9c-81-e7-ba-a7-e7-89-b9-e8-89-b2-e5-93-81-e7-89-8c-e5-9f-b9-e8-82-b2-e8-ae-a1-e5-88-92-04-13-2f-e9-82-b9-e5-bb-ba-e4-b8-b0-3a-e6-96-b0-e5-8d-8e-e6-97-a5-e6-8a-a5-5c-72-e5-bc-a0-e4-b8-89-3b-e6-9d-8e-e5-9b-9b-3a-e6-96-b0-e6-b5-aa-05-1f-38-e6-b1-9f-e8-8b-8f-e7-9c-81-e5-a7-94-5c-72-32-30-31-37-5c-72-e9-87-91-e5-9d-9b-5c-72-e5-9f-b9-e8-82-b2-e8-ae-a1-e5-88-92-5c-72-e7-be-8e-e4-b8-bd-3b-6e-69-63-65-06-08-10-e7-be-8e-e4-b8-bd-3b-e4-b9-a1-e6-9d-91-07-00-0f-e6-96-b0-e5-8d-8e-e6-97-a5-e6-8a-a5-08-00-0c-e7-9a-b1-e5-bb-ba-e4-b8-b0-09-00-0d-e6-96-87-e6-9c-ac-3b-31-30-4d-0e-48-0e-01-69-0f-00-ff-1f-ff-ff-f1-ff-01-0f-ff-ff-f1-fe-fb-fd-ff-ff-ff-ff-f9-f9-4f-1f-3f-5f-7f-9f-48-13-0e-69-0f-02-ff-1f-ff-ff-f1-ff-01-0f-ff-ff-f1-fe-fb-fd-ff-ff-ff-ff-f9-f9-4f-1f-3f-5f-7f-9f-48-53-0b-01-08-ca-02-84-01-00-4a-02-00-01-00-45-e6-b1-9f-e8-8b-8f-e4-bb-8a-e5-b9-b4-e8-b5-b7-e5-ae-9e-e6-96-bd-e2-80-9c-31-32-33-31-31-e2-80-9d-e8-ae-a1-e5-88-92-20-e5-9f-b9-e8-82-b2-e7-99-be-e4-b8-aa-e5-86-9c-e4-b8-9a-e7-89-b9-e8-89-b2-e9-95-87-0a-04-14-06-00-11-00-09-e6-9b-be-e6-9c-8b-12-00-06-53-45-55-0f-08-67-08-c0-03-08-4c-68-74-74-70-3a-2f-2f-6a-69-61-6e-67-73-75-2e-73-69-6e-61-2e-63-6f-6d-2e-63-6e-2f-6e-65-77-73-2f-62-2f-32-30-31-37-2d-30-35-2d-33-31-2f-64-65-74-61-69-6c-2d-69-66-79-66-71-71-79-68-39-30-38-30-30-31-35-2e-73-68-74-6d-6c-0e-04-0b-73-69-61-6e-3b-73-65-75-0f-04-0b-35-32-35-65-32-62-33-66-0f-00-52-e6-b1-9f-e8-8b-8f-e4-bb-8a-e5-b9-b4-e8-b5-b7-e5-ae-9e-e6-96-bd-e2-80-9c-31-32-33-31-31-e2-80-9d-e8-ae-a1-e5-88-92-2c-20-e5-85-a8-e7-9c-81-e5-88-9b-e6-84-8f-e4-bc-91-e9-97-b2-e5-86-9c-e4-b8-9a-e5-b7-a5-e4-bd-9c-e6-8e-a8-e8-bf-9b-e4-bc-9a-0f-18-df-38-f0-03-08-4c-68-74-74-70-3a-2f-2f-6a-69-61-6e-67-73-75-2e-73-69-6e-61-2e-63-6f-6d-2e-63-6e-2f-6e-65-77-73-2f-62-2f-32-30-31-37-2d-30-35-2d-33-31-2f-64-65-74-61-69-6c-2d-69-66-79-66-71-71-79-68-39-30-38-30-30-31-35-2e-73-68-74-6d-6c-14-00-07-73-69-6e-61-05-04-0d-62-61-69-64-75-3b-73-69-6e-61-0c-08-23-32-34-37-36-34-36-30-30-32-39-36-31-33-39-37-38-33-35-37-35-64-38-32-34-34-66-30-64-34-66-37-30-0d-00-09-e9-87-8d-e8-a6-81-0e-04-0b-73-69-61-6e-3b-73-65-75-0f-0c-43-39-36-39-63-33-37-32-37-63-32-38-65-36-35-35-33-35-36-65-36-39-39-61-35-36-35-35-64-33-32-30-32-33-35-33-61-32-32-31-38-66-65-31-66-34-66-36-65-36-61-35-63-30-62-31-62-33-31-34-39-64-62-64-35-

--------------显示UCL各部分关键信息--------------
                        Version:3
                  Type of Media:9
                  Prio and Poli:f
                           Flag:32
                     Parse Rule:ff1
              Source of Content:ffffff1
                       Category:ff
                    Subcategory:1
                          Topic:ffffff1
     Copyright and Type of Cont:fe
     Security Energy Level Code:fb
                       Language:fd
                Size of Content:1f
                     Time Stamp:7fffffff9f9
                  Serial Number:4f
                Multiplex Bytes:1f3f5f7f9f48
                     Code Check:937a
--------------属性部分----------------
元语言类型: 中文
属性集个数: 2
--------------具体属性集----------------
**************************
属性集合名: 内容描述属性集合
属性集类别: 1    属性个数: 11
属性类别: 1    属性名: 内容标题
属性值: 江苏今年起实施“12311”计划 培育百个农业特色镇
------------------------------------
属性类别: 2    属性名: 内容关键词
关键词数量: 3
关键词: 江苏 乡村 国家 
------------------------------------
属性类别: 3    属性名: 内容摘要
属性值: 省农委日前在金坛召开全省创意休闲农业工作推进会，决定从今年起实施“12311”创意休闲农业省级特色品牌培育计划
------------------------------------
属性类别: 4    属性名: 内容作者
作者数量: 3    公司数量: 2
作者 ----- 公司
邹建丰 ----- 新华日报 
张三 李四 ----- 新浪 
------------------------------------
属性类别: 5    属性名: 内容实体
实体类别数量: 5
人 : 江苏省委 
时 : 2017 
地 : 金坛 
事 : 培育计划 
因 : 美丽 nice 
------------------------------------
属性类别: 6    属性名: 内容标记
标记数量: 2
内容标记: 美丽 乡村 
------------------------------------
属性类别: 7    属性名: 版权信息
属性值: 新华日报
------------------------------------
属性类别: 8    属性名: 原创声明
属性值: 皱建丰
------------------------------------
属性类别: 9    属性名: 文件信息
文件信息: 文本 10M 
------------------------------------
属性类别: 14    属性名: 关联UCL
关联UCL数量: 2
--------------------------关联UCL开始-----------------------------
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
                        Version:3
                  Type of Media:9
                  Prio and Poli:15
                           Flag:0
                     Parse Rule:4081
              Source of Content:268435441
                       Category:255
                    Subcategory:1
                          Topic:268435441
     Copyright and Type of Cont:254
     Security Energy Level Code:251
                       Language:253
                Size of Content:31
                     Time Stamp:8796093020665
                  Serial Number:79
                Multiplex Bytes:34357045600072
                     Code Check:4878
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
                        Version:3
                  Type of Media:9
                  Prio and Poli:15
                           Flag:2
                     Parse Rule:4081
              Source of Content:268435441
                       Category:255
                    Subcategory:1
                          Topic:268435441
     Copyright and Type of Cont:254
     Security Energy Level Code:251
                       Language:253
                Size of Content:31
                     Time Stamp:8796093020665
                  Serial Number:79
                Multiplex Bytes:34357045600072
                     Code Check:21259
--------------属性部分----------------
元语言类型: 中文
属性集个数: 3
--------------具体属性集----------------
**************************
属性集合名: 内容描述属性集合
属性集类别: 1    属性个数: 1
属性类别: 1    属性名: 内容标题
属性值: 江苏今年起实施“12311”计划 培育百个农业特色镇
------------------------------------
**************************
自定义属性集合
属性集类别: 10    属性个数: 2
属性类别和属性值: 1   曾朋
------------------------------------
属性类别和属性值: 2   SEU
------------------------------------
**************************
属性集合名: 内容管理属性集合
属性集类别: 15    属性个数: 3
属性类别: 3    属性名: 内容出处
内容出处描述形式:  网址或域名
内容出处: http://jiangsu.sina.com.cn/news/b/2017-05-31/detail-ifyfqqyh9080015.shtml
------------------------------------
属性类别: 14    属性名: 内容责任链
责任主体数量: 2
责任主体详细信息: sian seu 
------------------------------------
属性类别: 15    属性名: 全UCL包数字签名
数字摘要算法: CRC32   数字签名算法: 未对内容对象进行数字签名
摘要或签名信息: 525e2b3f
------------------------------------
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
--------------------------关联UCL结束-----------------------------
------------------------------------
属性类别: 15    属性名: 内容对象
属性值: 江苏今年起实施“12311”计划, 全省创意休闲农业工作推进会
------------------------------------
**************************
属性集合名: 内容管理属性集合
属性集类别: 15    属性个数: 7
属性类别: 3    属性名: 内容出处
内容出处描述形式:  网址或域名
内容出处: http://jiangsu.sina.com.cn/news/b/2017-05-31/detail-ifyfqqyh9080015.shtml
------------------------------------
属性类别: 4    属性名: 内容ID
内容ID解析规则: URI
详细内容ID信息: sina
------------------------------------
属性类别: 5    属性名: 传播路径
传播路径长度: 2
传播路径: baidu sina 
------------------------------------
属性类别: 12    属性名: 内容数字签名
数字摘要算法: MD5   数字签名算法: 未对内容对象进行数字签名
摘要或签名信息: 24764600296139783575d8244f0d4f70
------------------------------------
属性类别: 13    属性名: 安全能级信息
安全能级信息的认证等级: 自行标定
安全能级详细信息: 重要
------------------------------------
属性类别: 14    属性名: 内容责任链
责任主体数量: 2
责任主体详细信息: sian seu 
------------------------------------
属性类别: 15    属性名: 全UCL包数字签名
数字摘要算法: SHA-256   数字签名算法: 未对内容对象进行数字签名
摘要或签名信息: 969c3727c28e655356e699a5655d3202353a2218fe1f4f6e6a5c0b1b3149dbd5
------------------------------------

##############测试解包##############

--------------UCLPackage--------------
69-0f-32-ff-1f-ff-ff-f1-ff-01-0f-ff-ff-f1-fe-fb-fd-ff-ff-ff-ff-f9-f9-4f-1f-3f-5f-7f-9f-48-93-7a-01-44-e4-03-02-80-01-68-ff-02-fe-c3-01-00-45-e6-b1-9f-e8-8b-8f-e4-bb-8a-e5-b9-b4-e8-b5-b7-e5-ae-9e-e6-96-bd-e2-80-9c-31-32-33-31-31-e2-80-9d-e8-ae-a1-e5-88-92-20-e5-9f-b9-e8-82-b2-e7-99-be-e4-b8-aa-e5-86-9c-e4-b8-9a-e7-89-b9-e8-89-b2-e9-95-87-02-10-17-e6-b1-9f-e8-8b-8f-3b-e4-b9-a1-e6-9d-91-3b-e5-9b-bd-e5-ae-b6-03-00-9e-e7-9c-81-e5-86-9c-e5-a7-94-e6-97-a5-e5-89-8d-e5-9c-a8-e9-87-91-e5-9d-9b-e5-8f-ac-e5-bc-80-e5-85-a8-e7-9c-81-e5-88-9b-e6-84-8f-e4-bc-91-e9-97-b2-e5-86-9c-e4-b8-9a-e5-b7-a5-e4-bd-9c-e6-8e-a8-e8-bf-9b-e4-bc-9a-ef-bc-8c-e5-86-b3-e5-ae-9a-e4-bb-8e-e4-bb-8a-e5-b9-b4-e8-b5-b7-e5-ae-9e-e6-96-bd-e2-80-9c-31-32-33-31-31-e2-80-9d-e5-88-9b-e6-84-8f-e4-bc-91-e9-97-b2-e5-86-9c-e4-b8-9a-e7-9c-81-e7-ba-a7-e7-89-b9-e8-89-b2-e5-93-81-e7-89-8c-e5-9f-b9-e8-82-b2-e8-ae-a1-e5-88-92-04-13-2f-e9-82-b9-e5-bb-ba-e4-b8-b0-3a-e6-96-b0-e5-8d-8e-e6-97-a5-e6-8a-a5-5c-72-e5-bc-a0-e4-b8-89-3b-e6-9d-8e-e5-9b-9b-3a-e6-96-b0-e6-b5-aa-05-1f-38-e6-b1-9f-e8-8b-8f-e7-9c-81-e5-a7-94-5c-72-32-30-31-37-5c-72-e9-87-91-e5-9d-9b-5c-72-e5-9f-b9-e8-82-b2-e8-ae-a1-e5-88-92-5c-72-e7-be-8e-e4-b8-bd-3b-6e-69-63-65-06-08-10-e7-be-8e-e4-b8-bd-3b-e4-b9-a1-e6-9d-91-07-00-0f-e6-96-b0-e5-8d-8e-e6-97-a5-e6-8a-a5-08-00-0c-e7-9a-b1-e5-bb-ba-e4-b8-b0-09-00-0d-e6-96-87-e6-9c-ac-3b-31-30-4d-0e-48-0e-01-69-0f-00-ff-1f-ff-ff-f1-ff-01-0f-ff-ff-f1-fe-fb-fd-ff-ff-ff-ff-f9-f9-4f-1f-3f-5f-7f-9f-48-13-0e-69-0f-02-ff-1f-ff-ff-f1-ff-01-0f-ff-ff-f1-fe-fb-fd-ff-ff-ff-ff-f9-f9-4f-1f-3f-5f-7f-9f-48-53-0b-01-08-ca-02-84-01-00-4a-02-00-01-00-45-e6-b1-9f-e8-8b-8f-e4-bb-8a-e5-b9-b4-e8-b5-b7-e5-ae-9e-e6-96-bd-e2-80-9c-31-32-33-31-31-e2-80-9d-e8-ae-a1-e5-88-92-20-e5-9f-b9-e8-82-b2-e7-99-be-e4-b8-aa-e5-86-9c-e4-b8-9a-e7-89-b9-e8-89-b2-e9-95-87-0a-04-14-06-00-11-00-09-e6-9b-be-e6-9c-8b-12-00-06-53-45-55-0f-08-67-08-c0-03-08-4c-68-74-74-70-3a-2f-2f-6a-69-61-6e-67-73-75-2e-73-69-6e-61-2e-63-6f-6d-2e-63-6e-2f-6e-65-77-73-2f-62-2f-32-30-31-37-2d-30-35-2d-33-31-2f-64-65-74-61-69-6c-2d-69-66-79-66-71-71-79-68-39-30-38-30-30-31-35-2e-73-68-74-6d-6c-0e-04-0b-73-69-61-6e-3b-73-65-75-0f-04-0b-35-32-35-65-32-62-33-66-0f-00-52-e6-b1-9f-e8-8b-8f-e4-bb-8a-e5-b9-b4-e8-b5-b7-e5-ae-9e-e6-96-bd-e2-80-9c-31-32-33-31-31-e2-80-9d-e8-ae-a1-e5-88-92-2c-20-e5-85-a8-e7-9c-81-e5-88-9b-e6-84-8f-e4-bc-91-e9-97-b2-e5-86-9c-e4-b8-9a-e5-b7-a5-e4-bd-9c-e6-8e-a8-e8-bf-9b-e4-bc-9a-0f-18-df-38-f0-03-08-4c-68-74-74-70-3a-2f-2f-6a-69-61-6e-67-73-75-2e-73-69-6e-61-2e-63-6f-6d-2e-63-6e-2f-6e-65-77-73-2f-62-2f-32-30-31-37-2d-30-35-2d-33-31-2f-64-65-74-61-69-6c-2d-69-66-79-66-71-71-79-68-39-30-38-30-30-31-35-2e-73-68-74-6d-6c-14-00-07-73-69-6e-61-05-04-0d-62-61-69-64-75-3b-73-69-6e-61-0c-08-23-32-34-37-36-34-36-30-30-32-39-36-31-33-39-37-38-33-35-37-35-64-38-32-34-34-66-30-64-34-66-37-30-0d-00-09-e9-87-8d-e8-a6-81-0e-04-0b-73-69-61-6e-3b-73-65-75-0f-0c-43-39-36-39-63-33-37-32-37-63-32-38-65-36-35-35-33-35-36-65-36-39-39-61-35-36-35-35-64-33-32-30-32-33-35-33-61-32-32-31-38-66-65-31-66-34-66-36-65-36-61-35-63-30-62-31-62-33-31-34-39-64-62-64-35-

--------------解包后UCL各部分关键信息--------------
                        Version:3
                  Type of Media:9
                  Prio and Poli:f
                           Flag:32
                     Parse Rule:ff1
              Source of Content:ffffff1
                       Category:ff
                    Subcategory:1
                          Topic:ffffff1
     Copyright and Type of Cont:fe
     Security Energy Level Code:fb
                       Language:fd
                Size of Content:1f
                     Time Stamp:7fffffff9f9
                  Serial Number:4f
                Multiplex Bytes:1f3f5f7f9f48
                     Code Check:937a
--------------属性部分----------------
元语言类型: 中文
属性集个数: 2
--------------具体属性集----------------
**************************
属性集合名: 内容描述属性集合
属性集类别: 1    属性个数: 11
属性类别: 1    属性名: 内容标题
属性值: 江苏今年起实施“12311”计划 培育百个农业特色镇
------------------------------------
属性类别: 2    属性名: 内容关键词
关键词数量: 3
关键词: 江苏 乡村 国家 
------------------------------------
属性类别: 3    属性名: 内容摘要
属性值: 省农委日前在金坛召开全省创意休闲农业工作推进会，决定从今年起实施“12311”创意休闲农业省级特色品牌培育计划
------------------------------------
属性类别: 4    属性名: 内容作者
作者数量: 3    公司数量: 2
作者 ----- 公司
邹建丰 ----- 新华日报 
张三 李四 ----- 新浪 
------------------------------------
属性类别: 5    属性名: 内容实体
实体类别数量: 5
人 : 江苏省委 
时 : 2017 
地 : 金坛 
事 : 培育计划 
因 : 美丽 nice 
------------------------------------
属性类别: 6    属性名: 内容标记
标记数量: 2
内容标记: 美丽 乡村 
------------------------------------
属性类别: 7    属性名: 版权信息
属性值: 新华日报
------------------------------------
属性类别: 8    属性名: 原创声明
属性值: 皱建丰
------------------------------------
属性类别: 9    属性名: 文件信息
文件信息: 文本 10M 
------------------------------------
属性类别: 14    属性名: 关联UCL
关联UCL数量: 2
--------------------------关联UCL开始-----------------------------
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
                        Version:3
                  Type of Media:9
                  Prio and Poli:15
                           Flag:0
                     Parse Rule:4081
              Source of Content:268435441
                       Category:255
                    Subcategory:1
                          Topic:268435441
     Copyright and Type of Cont:254
     Security Energy Level Code:251
                       Language:253
                Size of Content:31
                     Time Stamp:8796093020665
                  Serial Number:79
                Multiplex Bytes:34357045600072
                     Code Check:4878
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
                        Version:3
                  Type of Media:9
                  Prio and Poli:15
                           Flag:2
                     Parse Rule:4081
              Source of Content:268435441
                       Category:255
                    Subcategory:1
                          Topic:268435441
     Copyright and Type of Cont:254
     Security Energy Level Code:251
                       Language:253
                Size of Content:31
                     Time Stamp:8796093020665
                  Serial Number:79
                Multiplex Bytes:34357045600072
                     Code Check:21259
--------------属性部分----------------
元语言类型: 中文
属性集个数: 3
--------------具体属性集----------------
**************************
属性集合名: 内容描述属性集合
属性集类别: 1    属性个数: 1
属性类别: 1    属性名: 内容标题
属性值: 江苏今年起实施“12311”计划 培育百个农业特色镇
------------------------------------
**************************
自定义属性集合
属性集类别: 10    属性个数: 2
属性类别和属性值: 1   曾朋
------------------------------------
属性类别和属性值: 2   SEU
------------------------------------
**************************
属性集合名: 内容管理属性集合
属性集类别: 15    属性个数: 3
属性类别: 3    属性名: 内容出处
内容出处描述形式:  网址或域名
内容出处: http://jiangsu.sina.com.cn/news/b/2017-05-31/detail-ifyfqqyh9080015.shtml
------------------------------------
属性类别: 14    属性名: 内容责任链
责任主体数量: 2
责任主体详细信息: sian seu 
------------------------------------
属性类别: 15    属性名: 全UCL包数字签名
数字摘要算法: CRC32   数字签名算法: 未对内容对象进行数字签名
摘要或签名信息: 525e2b3f
------------------------------------
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
--------------------------关联UCL结束-----------------------------
------------------------------------
属性类别: 15    属性名: 内容对象
属性值: 江苏今年起实施“12311”计划, 全省创意休闲农业工作推进会
------------------------------------
**************************
属性集合名: 内容管理属性集合
属性集类别: 15    属性个数: 7
属性类别: 3    属性名: 内容出处
内容出处描述形式:  网址或域名
内容出处: http://jiangsu.sina.com.cn/news/b/2017-05-31/detail-ifyfqqyh9080015.shtml
------------------------------------
属性类别: 4    属性名: 内容ID
内容ID解析规则: URI
详细内容ID信息: sina
------------------------------------
属性类别: 5    属性名: 传播路径
传播路径长度: 2
传播路径: baidu sina 
------------------------------------
属性类别: 12    属性名: 内容数字签名
数字摘要算法: MD5   数字签名算法: 未对内容对象进行数字签名
摘要或签名信息: 24764600296139783575d8244f0d4f70
------------------------------------
属性类别: 13    属性名: 安全能级信息
安全能级信息的认证等级: 自行标定
安全能级详细信息: 重要
------------------------------------
属性类别: 14    属性名: 内容责任链
责任主体数量: 2
责任主体详细信息: sian seu 
------------------------------------
属性类别: 15    属性名: 全UCL包数字签名
数字摘要算法: SHA-256   数字签名算法: 未对内容对象进行数字签名
摘要或签名信息: 969c3727c28e655356e699a5655d3202353a2218fe1f4f6e6a5c0b1b3149dbd5
------------------------------------
========== UCL test end==========

Process finished with exit code 0

```


