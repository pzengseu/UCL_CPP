# 使用指南
1. 建立UCL对象
UCL ucl；

2. 添加UCLCode对象
UCLCode uclCode;
然后使用UCLCode中的setXXX方法设置UCLCode中各个域的值。
ucl.setUclCode(uclCode); //设置uclCode部分

3. 添加属性集合
UCLPropertySet snps;
UCLPropertyBase nr = GenerateProperty::generateSNPSNR("WuHan");
snps.setProperty(nr);
ucl.setPropertySet(snps);
首先新建集合对象，可利用GenerateProperty生成标准UCL定义的属性或属性集合。
在属性集合上添加属性，最后设置ucl属性集合。

4. 打包
string uclS = ucl.pack();
将UCL数据报打包成二进制流，并存储在string对象中。

5. 解包
UCL ucl2;
ucl2.unpack(uclS);
将uclS数据流解包成ucl对象，这样可以提取出数据流中各个字段的值。

## 参考test.h中testUCL（）方法。


