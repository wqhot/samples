## crop

**本样例只针对教学使用，禁止一切商业活动**

### 样例介绍

功能：调用dvpp的crop接口，实现图像裁剪功能。

样例输入：原始YUV图片。

样例输出：裁剪后的YUV图片。

### 软件准备
**以下所有操作都是在开发环境中进行的**

1. 非root用户命令行中执行以下命令下载源码仓。

   **cd $HOME**

   **git clone https://gitee.com/ascend/samples.git**

2. 打开Mindstudio。
   
   **cd $HOME/Mindstudio-ubuntu/bin**

   **./Mindstudio.sh**

3. 在Mindstudio右上角点击 **File->Open...** ,打开crop样例。
   
   
   

### 编译代码
 
1、在命令行输入：    
**export DDK_PATH=/home/HwHiAiUser/Ascend/ascend-toolkit/20.0.0.RC1/acllib_centos7.6.x86_64 && export NPU_HOST_LIB=/home/HwHiAiUser/Ascend/ascend-toolkit/20.0.0.RC1/acllib_centos7.6.x86_64/acllib/lib64/stub**

2、切换到“cropandpaste”目录，创建目录用于存放编译文件

**cd cropandpaste**

第一次需要 到build目录执行cmake生成编译文件

创建的目录为“build/intermediates/host”。

**mkdir -p build/intermediates/host**

第一次需要 到build目录执行cmake生成编译文件

**cd build/intermediates/host**

**cmake ../../../src -DCMAKE_CXX_COMPILER=g++ -DCMAKE_SKIP_RPATH=TRUE**

### 代码执行

1、到out目录执行脚本生成把输入图片抠图贴图后生成yuv文档在cropandpaste/out目录

**cd ../../../out**   
**pip3 install pillow**   
**bash runcropandpaste.sh**



### 查看结果

1、out目录有一个output.yuv，他是根据resize的宽度高度生成的yuv420文件。