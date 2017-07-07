# 图片拼接器Java接口工程使用说明
##  一、接口工程 所需要的 目录结构 介绍
- stitcher``` 项目根目录```
    - Common``` 整个项目的共用目录，包括共用代码、共用依赖库、共用资源等```
        - images```待拼接的图片```
        - opencv2.4.9```opencv2.4.9链接库```
    - stitcher_win_x64_sdk```win_x64的SDK根目录```markdown-scroll-syncmarkdown-scroll-sync
        - lib```win_x64_Release版本的 拼接器 动态链接库```
        - java_stitcher_demo```拼接器的Java_Demo```
## 二、如何在自己的Java工程中使用拼接器
> 因为此Demo为Eclipse建立的Java工程，所以所有配置均以Eclipse为例，其他IDE原理相同。
### 1、配置Eclipse环境变量
因为此Demo的代码中中没有涉及OpenCV的部分，所有OpenCV操作都在动态链接库中，所以我们不需要引用OpenCV中Java的包，只需要修改好环境变量，保证Java能调用到拼接器的动态链接库，拼接器能找到OpenCV的动态链接库就行。

Windows 然后按下列顺序搜索 DLL：
- （1）当前进程的可执行模块所在的目录。
- （2）当前目录。
- （3）Windows 系统目录。 GetSystemDirectory 函数检索此目录的路径。
- （4）Windows 目录。 GetWindowsDirectory 函数检索此目录的路径。
- （5）PATH 环境变量中列出的目录。

我们只是运行一个Demo，所以没有必要去修改系统环境变量，我们可以将 拼接的动态链接库位置 和 OpenCV的动态链接库位置 添加到IDE的Path中，只在此Demo中生效。

工程右键->Run As->Run Configurations->Java Application->your project_name->Environment标签
在标签页中点击```Select...```按钮，选择```Path```,点击OK。
在标签页中选择```Path```，点解```Edit...```按钮，在Value后面添加如下相对路径：
``` path
..\lib;..\..\Common\opencv2.4.9\build\x64\vc12\bin;
```
> 这两个路径就是 动态链接库 的路径

Applay->Run

success!
### 2、代码 编写
#### （1）接口实现
新建一个Interface，代码如下：
```java
import com.sun.jna.Library;
import com.sun.jna.Native;

public interface Stitcher extends Library{
	Stitcher instanceDll  = (Stitcher)Native.loadLibrary("stitcher_win_lib_project",Stitcher.class);
	public int stichImg_by_path(String[] path,int size);
}

```
#### （2）接口调用
调用接口代码如下：
``` java
Stitcher.instanceDll.stichImg_by_path(path,size);
```
形参：String[]待拼接图片路径列表，int图片总数。

返回值：int是否执行成功，成功返回0

执行结果保存在Demo根目录下的result.jpg中。
