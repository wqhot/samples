# faster-deploy

## 使用方法
1. 下载快速部署脚本。
    ubuntu服务器的命令行中执行以下命令进入\\$HOME/AscendProjects目录。

    **cd \\$HOME/AscendProjects**

    命令行中使用以下命令下载faster-deploy脚本及样例包。

    **git clone -b 1.32.0.0 https://gitee.com/ascend/samples.git**
    
    进入faster-deploy文件夹下。

    **cd /home/ascend/AscendProjectssamples/samples/commmon/faster-deploy**

2. 使用source命令执行faster-deploy脚本，命令示例如下:

    **source faster-deploy.sh**

3. 执行后，会自动检查当前ddk版本号.
如果安装了多个ddk，则需要选择对应版本号填入。
如安装了1.32.0.B080和1.31.T15.B150两个版本的DDK，当前需要部署B080的样例,填入方式如下：

    The currently installed ddk version numbers are as follows:

    1:1.32.0.B080

    2:1.31.T15.B150

    Several DDK are detected. Please input your DDK verison in this list(eg:1):1

4. 会要求输入用户密码，正常输入即可。

5. 选择需要下载的样例类型，python或者C++。

    The current community cases are categorized by programming language as follows

    1.python

    2.C++

    Please select the serial number of the case type you need to download(eg:1):2

6. 给出所有样例列表，填入下载的样例序号即可。
如需要下载sample-facedetection，填入方式如下：

    Current All sample and them number list:

    1.sample-facedetection

    2.sample-facialrecognition

    3.sample-videoanalysisperson

    4.sample-ascendcamera

    5.sample-classification

    6.sample-objectdetection

    7.sample-headposeestimation

    8.sample-colorization

    9.sample-carplaterecognition

    10.sample-segmentation

    11.sample-objectdetectionbyyolov3

    Please input your want download sample number in list(eg:1).:1

7. 等待下载即可。

## 注意事项
1. 由于脚本会配置环境变量，环境变量包含DDK版本信息，所以Mindstudio需要在使用新的DDK首次执行脚本后再打开，否则Mindstudio中无法读取最新的环境变量，从而样例运行失败。
2. 案例会下载在\\$HOME/AscendProjects目录下，下载成功后，请在Mindstudio中打开此目录下下载的相应应用。
3. 重复快速部署同一个案例，会自动删除上次部署的应用。