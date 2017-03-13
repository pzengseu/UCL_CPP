# 使用指南
1. 建立UCL对象
UCL ucl；

2. 添加UCLCode对象
UCLCode uclCode;
然后使用UCLCode中的setXXX方法设置UCLCode中各个域的值。
ucl.setUclCode(uclCode); //设置uclCode部分

4、新建标准属性
UCLPropertyBase nr = GenerateProperty::generateSNPSNR("WuHan");
利用GenerateProperty中方法新建标准属性

5、自定义属性
UCLPropertyBase nr;
GenerateProperty::setProperty(nr, 0x2, 0, " ");
即新建了属性nr，可参考GenerateProerty类。

6.添加属性集合
UCLPropertySet snps;
snps.setHeadCategory(0);
UCLPropertyBase nr = GenerateProperty::generateSNPSNR("WuHan");
snps.setProperty(nr);
ucl.setPropertySet(snps);
首先新建集合对象，然后调用setHeadCategory方法设置集合类别。
在属性集合上添加属性，最后设置ucl属性集合。

7.打包
因为打包时会生成摘要字段，解包会检查数字摘要，所以必须添加编号15属性集及其编号15属性。
UCLPropertySet cgps;
cgps.setHeadCategory(15);
UCLPropertyBase sigUCL = GenerateProperty::generateCGPSSignatureUCL(3, "", 0);
cgps.setProperty(sigUCL);
ucl.setProperty(cgps);
string uclS = ucl.pack();
将UCL数据报打包成二进制流，并存储在string对象中。

8.解包
UCL ucl2;
ucl2.unpack(uclS);
将uclS数据流解包成ucl对象，这样可以提取出数据流中各个字段的值。

## 参考test.h中testEasy()方法。


