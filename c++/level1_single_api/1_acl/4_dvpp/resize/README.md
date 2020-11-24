## resize样例

**本样例只针对教学使用，禁止一切商业活动！**

**运行本样例前，请确认已安装好20.0.0及以上版本的环境，且已根据文档使用Mindstudio运行过自带样例。如需命令行方式运行请移步[CI命令行编译样例]()**。

**样例运行过程中，有任何问题，请直接在本仓中提issue，我们会及时解决，谢谢！**

### 样例介绍

功能：调用dvpp的resize接口，实现图像裁剪功能。

样例输入：原始YUV图片。

样例输出：缩放后的YUV图片。

### 工程准备

1. 非root用户命令行中执行以下命令下载源码仓。

   **cd $HOME**

   **git clone https://gitee.com/ascend/samples.git**

2. 打开Mindstudio。
   
   **cd $HOME/Mindstudio-ubuntu/bin**

   **./Mindstudio.sh**

3. 在Mindstudio右上角点击 **File->Open...** ,选择resize样例并打开。
   
   ![](https://images.gitee.com/uploads/images/2020/1110/120608_2a4aed4b_5395865.png "resize.png")
   

### 样例编译
 
在Mindstudio右上角点击 **Build->Edit Build Configuration...** ,进行编译配置。    
   
- 使用产品为200DK开发者板，选择 **Target Architecture为aarch64**。
   
- 使用产品为300加速卡（ai1s云端推理环境），选择 **Target Architecture为x86_64**。
   
选择完成后点击**Build**开始编译,编译完成后，会在工程中生成**build和out**文件夹。

### 样例运行

1. 在Mindstudio右上角点击 **Run->Edit Configurations...** ,进行运行配置。   

   **Target Host Ip** 选择为已经配置好的运行环境ip地址。一般USB方式连接的200DK为192.168.1.2，ai1s云端推理环境为公网ip地址。   

   **Command Arguments** 填写为：**../data/wood_rabbit_1024_1068_nv12.yuv 1024 1068 ./output/output.yuv 224 224**。

   参数填写完成后，点击右下角的**Apply**，再点击**OK**。
​    
    ![](https://images.gitee.com/uploads/images/2020/1106/160652_6146f6a4_5395865.gif "icon-note.gif") **说明：**  
    > - 如果**Target Host Ip**没有取值，请点击后面的加号图标，自行配置运行环境。   
    > - **Command Arguments**参数值../data/input.yuv w h output.yuv w h（w、h分别为照片宽度和高度），输入图片可自行上传，裁剪位置也可以自行修改。

2. 在Mindstudio右上角点击 **Run->Run 'resize'** ,运行样例。

    运行过程中，会将开发环境中的**data、out、model**文件夹上传到运行环境。并使用**adc**工具执行编译出来的**run.sh**脚本。
    

### 查看结果

运行完成后，会在本地开发环境的**out**文件夹下得到相应的回传文件**output.yuv**，他是根据resize的宽度高度生成的yuv420文件。