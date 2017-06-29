# 图片拼接器Linux64_Qt_Demo使用说明
## 一、目录结构介绍
 - stitcher_demo```主目录```
    - images```待拼接图片```
    - include```拼接器的头文件```
    - lib```拼接器的库```
    - qt_stitcher_demo```拼接器的QtDemo工程```
## 二、如何在自己的Qt工程中使用拼接器
### 1、配置Qt工程的pro文件
在自己Qt工程的.pro文件中，根据注释介绍，添加如下代码：
``` bash
INCLUDEPATH += /usr/local/include/opencv #opencv的头文件目录
LIBS += -lopencv_core \
-lopencv_imgproc \
-lopencv_highgui \ #前三个为opencv基本的3个库，接口传递的mat类型和最后demo中显示结果需要用到opencv这3个库，根据自己工程增删
../lib/libstitcher.so #这个库就是拼接器的库
```
这个LIBS选项可以填-lXXX（系统默认路径找库）、相对路径、绝对路径，只要使编译器可以找到要用的库就行
### 2、编写代码
（1）引用头文件
``` c++
#include "../include/stitcher.h"
```
（2）实例化拼接器，调用拼接方法
``` C++
Stitcher m_sticher;
Mat result = m_sticher.stichImg(full_img);
```
拼接方法参数为 待拼接图片（Mat类型）的 容器，返回一个拼接完成的Mat类型
