# ͼƬƴ����Win_x64_Java_Demoʹ��˵��
##  һ��Demo����Ҫ�� Ŀ¼�ṹ ����
- stitcher``` ���̸�Ŀ¼```
    - Common``` �������̵Ĺ���Ŀ¼���������ô��롢���������⡢������Դ��```
        - images```��ƴ�ӵ�ͼƬ```
        - opencv2.4.9```opencv2.4.9ͷ�ļ������ӿ�```
    - stitcher_win_x64_sdk```win_x64��SDK��Ŀ¼```
        - lib```win_x64_Release�汾�� ƴ���� ��̬���ӿ�```
        - java_stitcher_demo```ƴ������Java_Demo```
## ����������Լ���Java������ʹ��ƴ����
> ��Ϊ��DemoΪEclipse������Java���̣������������þ���EclipseΪ��������IDEԭ����ͬ��
### 1������Eclipse��������
��Ϊ��Demo�Ĵ�������û���漰OpenCV�Ĳ��֣�����OpenCV�������ڶ�̬���ӿ��У��������ǲ���Ҫ����OpenCV��Java�İ���ֻ��Ҫ�޸ĺû�����������֤Java�ܵ��õ�ƴ�����Ķ�̬���ӿ⣬ƴ�������ҵ�OpenCV�Ķ�̬���ӿ���С�

Windows Ȼ������˳������ DLL��
- ��1����ǰ���̵Ŀ�ִ��ģ�����ڵ�Ŀ¼��
- ��2����ǰĿ¼��
- ��3��Windows ϵͳĿ¼�� GetSystemDirectory ����������Ŀ¼��·����
- ��4��Windows Ŀ¼�� GetWindowsDirectory ����������Ŀ¼��·����
- ��5��PATH �����������г���Ŀ¼��

����ֻ������һ��Demo������û�б�Ҫȥ�޸�ϵͳ�������������ǿ��Խ� ƴ�ӵĶ�̬���ӿ�λ�� �� OpenCV�Ķ�̬���ӿ�λ�� ��ӵ�IDE��Path�У�ֻ�ڴ�Demo����Ч��

�����Ҽ�->Run As->Run Configurations->Java Application->your project_name->Environment��ǩ
�ڱ�ǩҳ�е��```Select...```��ť��ѡ��```Path```,���OK��
�ڱ�ǩҳ��ѡ��```Path```�����```Edit...```��ť����Value��������������·����
``` path
..\lib;..\..\Common\opencv2.4.9\build\x64\vc12\bin;
```
> ������·������ ��̬���ӿ� ��·��

Applay->Run

success!
### 2������ ��д
#### ��1���ӿ�ʵ��
�½�һ��Interface���������£�
```java
import com.sun.jna.Library;
import com.sun.jna.Native;

public interface Stitcher extends Library{
	Stitcher instanceDll  = (Stitcher)Native.loadLibrary("stitcher_win_lib_project",Stitcher.class);  
	public int stichImg_by_path(String[] path,int size);
}

```
#### ��2���ӿڵ���
���ýӿڴ������£�
``` java
Stitcher.instanceDll.stichImg_by_path(path,size);
```
�βΣ�String[]��ƴ��ͼƬ·���б�intͼƬ������

����ֵ��int�Ƿ�ִ�гɹ����ɹ�����0

ִ�н��������Demo��Ŀ¼�µ�result.jpg�С�
