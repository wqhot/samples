中文|[English](Readme_EN.md)

**该案例仅仅用于学习，打通流程，不对效果负责，不支持商用。**

# 人脸检测（python）<a name="ZH-CN_TOPIC_0232620367"></a>

开发者可以将本application部署至Atlas 200DK上实现对摄像头数据的实时采集、并对视频中的人脸信息进行预测的功能。

当前分支中的应用适配**1.3.0.0**与**1.32.0.0及以上**版本的[DDK&RunTime](https://ascend.huawei.com/resources)。

## 前提条件<a name="zh-cn_topic_0228757088_section1524472882216"></a>

部署此Sample前，需要准备好以下环境：

-   已完成Mind Studio的安装。

-   已完成Atlas 200 DK开发者板与Mind Studio的连接，SD卡的制作、编译环境的配置等。
-   由于需要配置开发板联网，默认设置为USB连接，开发板地址为192.168.1.2

## 软件准备<a name="zh-cn_topic_0228757088_section772075917223"></a>

运行此应用前，需要按照此章节进行相关的环境配置并获取源码包。

1.  <a name="zh-cn_topic_0228757088_li953280133816"></a>获取源码包。
    1.  下载压缩包方式获取。

        将[https://gitee.com/Atlas200DK/sample-facedetection-python](https://gitee.com/Atlas200DK/sample-facedetection-python)仓中的代码以Mind Studio安装用户下载至Mind Studio所在Ubuntu服务器的任意目录，例如代码存放路径为：$HOME/sample-facedetection-python。

    2.  命令行使用git命令方式获取。

        在命令行中：$HOME/AscendProjects目录下执行以下命令下载代码。

        **git clone https://gitee.com/Atlas200DK/sample-facedetection-python.git**

2.  <a name="zh-cn_topic_0228757088_li12291771229"></a>获取此应用中所需要的网络模型。

    参考[表 人脸检测\(python\)使用模型](#zh-cn_topic_0228757088_table1119094515272)获取此应用中所用到的原始网络模型及其对应的权重文件，并将其存放到Mind Studio所在Ubuntu服务器的任意目录，例如：$HOME/ascend/models/facedetection-python。

    **表 1**  人脸检测\(python\)使用模型

    <a name="zh-cn_topic_0228757088_table1119094515272"></a>
    <table><thead align="left"><tr id="zh-cn_topic_0228757088_row677354502719"><th class="cellrowborder" valign="top" width="12.85%" id="mcps1.2.4.1.1"><p id="zh-cn_topic_0228757088_p167731845122717"><a name="zh-cn_topic_0228757088_p167731845122717"></a><a name="zh-cn_topic_0228757088_p167731845122717"></a>模型名称</p>
    </th>
    <th class="cellrowborder" valign="top" width="12.04%" id="mcps1.2.4.1.2"><p id="zh-cn_topic_0228757088_p277317459276"><a name="zh-cn_topic_0228757088_p277317459276"></a><a name="zh-cn_topic_0228757088_p277317459276"></a>模型说明</p>
    </th>
    <th class="cellrowborder" valign="top" width="75.11%" id="mcps1.2.4.1.3"><p id="zh-cn_topic_0228757088_p9773114512270"><a name="zh-cn_topic_0228757088_p9773114512270"></a><a name="zh-cn_topic_0228757088_p9773114512270"></a>模型下载路径</p>
    </th>
    </tr>
    </thead>
    <tbody><tr id="zh-cn_topic_0228757088_row3122314144215"><td class="cellrowborder" valign="top" width="12.85%" headers="mcps1.2.4.1.1 "><p id="zh-cn_topic_0228757088_p13106121801715"><a name="zh-cn_topic_0228757088_p13106121801715"></a><a name="zh-cn_topic_0228757088_p13106121801715"></a>face_detection_rgb</p>
    </td>
    <td class="cellrowborder" valign="top" width="12.04%" headers="mcps1.2.4.1.2 "><p id="zh-cn_topic_0228757088_p13106171831710"><a name="zh-cn_topic_0228757088_p13106171831710"></a><a name="zh-cn_topic_0228757088_p13106171831710"></a>人脸检测网络模型。</p>
    <p id="zh-cn_topic_0228757088_p18106718131714"><a name="zh-cn_topic_0228757088_p18106718131714"></a><a name="zh-cn_topic_0228757088_p18106718131714"></a>此模型是基于Caffe的Resnet10-SSD300模型转换后的网络模型。</p>
    </td>
    <td class="cellrowborder" valign="top" width="75.11%" headers="mcps1.2.4.1.3 "><p id="zh-cn_topic_0228757088_p110671813170"><a name="zh-cn_topic_0228757088_p110671813170"></a><a name="zh-cn_topic_0228757088_p110671813170"></a>请参考<a href="https://gitee.com/HuaweiAscend/models/tree/master/computer_vision/object_detect/face_detection" target="_blank" rel="noopener noreferrer">https://gitee.com/HuaweiAscend/models/tree/master/computer_vision/object_detect/face_detection</a>目录中README.md下载原始网络模型文件及其对应的权重文件。</p>
    </td>
    </tr>
    </tbody>
    </table>

3.  将原始网络模型转换为适配昇腾AI处理器的模型。
    1.  在Mind Studio操作界面的顶部菜单栏中选择“Tool \> Convert Model”，进入模型转换界面。
    2.  在弹出的**Convert Model**操作界面中，Model File与Weight File分别选择[步骤2](#zh-cn_topic_0228757088_li12291771229)中下载的模型文件和权重文件。
        -   **Model Name**填写为[表 人脸检测\(python\)使用模型](#zh-cn_topic_0228757088_table1119094515272)对应的**模型名称**。
        -   AIPP配置界面需要将**Input Image Format**修改为BGR888\_U8,关闭 **Model Image Format**。
        -   **其他保持默认值。**

    3.  单击OK开始转换模型。

        1.1.0.0和1.3.0.0版本模型转换成功后，后缀为.om的离线模型存放地址为：**$HOME/tools/che/model-zoo/my-model/xxx**。

        1.32.0.0及以上版本模型转换成功后，后缀为.om的离线模型存放地址为：**$HOME/modelzoo/xxx/device/xxx.om**。

    4.  将转换好的模型文件（.om文件）上传到[步骤1](#zh-cn_topic_0228757088_li953280133816)中源码所在路径下的“sample-facedetection-python/model”目录下。

4.  以Mind Studio安装用户登录Mind Studio所在Ubuntu服务器，并设置环境变量DDK\_HOME。

    **vim \~/.bashrc**

    1.  1.3.0.0版本执行如下命令在最后一行添加DDK\_HOME及LD\_LIBRARY\_PATH的环境变量。

        **export DDK\_HOME=$HOME/tools/che/ddk/ddk**

        **export LD\_LIBRARY\_PATH=$DDK\_HOME/uihost/lib**

    2.  1.32.0.0及以上版本执行如下命令在最后一行添加环境变量

        **export tools\_version=_1.32.X.X_**

        **export DDK\_HOME= \\$HOME/.mindstudio/huawei/ddk/\\$tools\_version/ddk**

        **export LD\_LIBRARY\_PATH= \\$DDK\_HOME/lib/x86\_64-linux-gcc5.4:\\$DDK\_HOME/uihost/lib**

    >![](public_sys-resources/icon-note.gif) **说明：**   
    >-   1.32.0.0及以上版本环境变量设置时1.32.X.X为DDK版本号，可以通过安装的DDK的包名获取，如DDK包的包名为Ascend\_DDK-1.32.0.B080-1.1.1-x86\_64.ubuntu16.04.tar.gz，则此DDK的版本号为1.32.0.B080。  
    >-   如果此环境变量已经添加，则此步骤可跳过。  

    输入:wq!保存退出。

    执行如下命令使环境变量生效。

    **source \~/.bashrc**


## 环境配置<a name="zh-cn_topic_0228757088_section1637464117139"></a>

**注：开发板上hiai库、opencv库、相关依赖已安装可跳过此步骤。**

1.  配置开发板联网。

    请参考[https://gitee.com/Atlas200DK/sample-README/tree/master/DK\_NetworkConnect](https://gitee.com/Atlas200DK/sample-README/tree/master/DK_NetworkConnect)  ，进行开发板网络连接配置。

2.  安装环境依赖（请安装python3相关依赖，当前此案例只适配python3）。

    请参考[https://gitee.com/Atlas200DK/sample-README/tree/master/DK\_Environment](https://gitee.com/Atlas200DK/sample-README/tree/master/DK_Environment)  ，进行环境依赖配置。


## 部署<a name="zh-cn_topic_0228757088_section7994174585917"></a>

1.  以Mind Studio安装用户进入facedetectionapp应用代码所在根目录，如：$HOME/sample-facedetection-python。
2.  修改face\_detection.conf中presenter\_server\_ip为当前ubuntu服务器上和atlas200dk开发板连接的网口ip，atlas200dk\_board\_ip为开发板上和ubuntu服务器连接的网口ip。

    如使用USB连接，开发板的USB网口ip为192.168.1.2，ubuntu服务器和开发板连接的虚拟网卡的网口ip为192.168.1.134，则配置文件内容如下所示：

    **presenter\_server\_ip=192.168.1.134**

    **presneter\_server\_port=7006**

    **atlas200dk\_board\_id=192.168.1.2**

    >![](public_sys-resources/icon-note.gif) **说明：**   
    >-   一般通过USB连接时，atlas200dk\_board\_ip为开发板的USB网口ip，默认为192.168.1.2。通过网口连接时，atlas200dk\_board\_ip为开发板的网络网口ip，默认为192.168.0.2。  

3.  应用代码拷贝到开发板。

    以Mind Studio安装用户进入语义分割网络应用\(python\)代码所在根目录，如：$HOME/sample-facedetection-python，执行以下命令将应用代码拷贝到开发板。

    **scp -r ../sample-facedetection-python/ HwHiAiUser@192.168.1.2:/home/HwHiAiUser/HIAI\_PROJECTS**

    提示password时输入开发板密码，开发板默认密码为**Mind@123**

4.  启动Presenter Server。

    执行如下命令在后台启动人脸检测python应用的Presenter Server主程序。

    **bash run\_presenter\_server.sh &**

    使用提示的URL登录Presenter Server。如下图所示，表示Presenter Server启动成功。

    **图 1**  主页显示<a name="zh-cn_topic_0228757088_fig64391558352"></a>  
    ![](figures/主页显示.png "主页显示")

    Presenter Server、Mind Studio与Atlas 200 DK之间通信使用的IP地址示例如下图所示：

    **图 2**  IP地址示例<a name="zh-cn_topic_0228757088_fig1881532172010"></a>  
    ![](figures/IP地址示例.png "IP地址示例")

    其中：

    -   Atlas 200 DK开发者板使用的IP地址为192.168.1.2（USB方式连接）。
    -   Presenter Server与Atlas 200 DK通信的IP地址为UI Host服务器中与Atlas 200 DK在同一网段的IP地址，例如：192.168.1.223。
    -   通过浏览器访问Presenter Server的IP地址本示例为：10.10.0.1，由于Presenter Server与Mind Studio部署在同一服务器，此IP地址也为通过浏览器访问Mind Studio的IP。


## 运行<a name="zh-cn_topic_0228757088_section551710297235"></a>

1.  在Mind Studio所在Ubuntu服务器中，以HwHiAiUser用户SSH登录到Host侧。

    **ssh HwHiAiUser@192.168.1.2**

    >![](public_sys-resources/icon-note.gif) **说明：**   
    >-   这里是以USB方式连接举例，此时ip为192.168.1.2。运行时请根据连接情况自行更换。  

2.  在HwHiAiUser用户下进入应用代码所在目录。

    **cd \~/HIAI\_PROJECTS/sample-facedetection-python**

3.  执行应用程序。

    **python3 main.py**

    >![](public_sys-resources/icon-note.gif) **说明：**   
    >- 可使用ctrl+c停止程序 
    >- 当前此案例只支持python3 

4.  使用启动Presenter Server服务时提示的URL登录 Presenter Server 网站。

    等待Presenter Agent传输数据给服务端，单击“Refresh“刷新，当有数据时相应的Channel 的Status变成绿色，如[图 Presenter Server界面](#zh-cn_topic_0228757088_fig113691556202312)所示。

    **图 3**  Presenter Server界面<a name="zh-cn_topic_0228757088_fig113691556202312"></a>  
    ![](figures/Presenter-Server界面.png "Presenter-Server界面")

    >![](public_sys-resources/icon-note.gif) **说明：**   
    >-   Presenter Server最多支持10路Channel同时显示，每个  _presenter\_view\_app\_name_  对应一路Channel。  
    >-   由于硬件的限制，每一路支持的最大帧率是20fps，受限于网络带宽的影响，帧率会自动适配为较低的帧率进行展示。  

5.  单击右侧对应的View Name链接，比如上图的“video”，查看结果。

## 后续处理<a name="zh-cn_topic_0228757088_section1092612277429"></a>

-   **停止Presenter Server服务**

    Presenter Server服务启动后会一直处于运行状态，若想停止人脸检测应用对应的Presenter Server服务，可执行如下操作。

    以Mind Studio安装用户在Mind Studio所在服务器中的命令行中执行如下命令查看人脸检测应用对应的Presenter Server服务的进程。

    **ps -ef | grep presenter | grep face\_detection**

    ```
    ascend@ascend-HP-ProDesk-600-G4-PCI-MT:~/sample-facedetection-python$ ps -ef | grep presenter | grep face_detection
    ascend    7701  1615  0 14:21 pts/8    00:00:00 python3 presenterserver/presenter_server.py --app face_detection
    ```

    如上所示  _7701_  即为人脸检测应用对应的Presenter Server服务的进程ID。

    若想停止此服务，执行如下命令：

    **kill -9** _7701_


