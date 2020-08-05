中文|[English](Readme_EN.md)

#  检测网络应用视频版（C++）<a name="ZH-CN_TOPIC_0219122211"></a>

本Application支持运行在Atlas 200 DK，实现了对yolov3目标检测网络的推理功能。 


## 软件准备<a name="zh-cn_topic_0219108795_section181111827718"></a>

运行此Sample前，需要按照此章节获取源码包。

1.  <a name="zh-cn_topic_0228757084_section8534138124114"></a>获取源码包。

    **cd $HOME/AscendProjects**    

    **wget https://c7xcode.obs.cn-north-4.myhuaweicloud.com/code_Ascend/objectdetection_video.zip** 
  
    **unzip objectdetection_video.zip**    
    
    >![](public_sys-resources/icon-note.gif) **说明：**   
    >- 如果使用wget下载失败，可使用如下命令下载代码。  
    **curl -OL https://c7xcode.obs.cn-north-4.myhuaweicloud.com/code_Ascend/objectdetection_video.zip** 
    >- 如果curl也下载失败，可复制下载链接到浏览器，手动上传至服务器。
    
2.  <a name="zh-cn_topic_0219108795_li2074865610364"></a>获取此应用中所需要的原始网络模型。    
 
     -  下载原始网络模型及权重文件至ubuntu服务器任意目录，如:$HOME/yolov3。

        **mkdir -p $HOME/yolov3**

        **wget -P $HOME/yolov3 https://c7xcode.obs.cn-north-4.myhuaweicloud.com/models/yolov3/yolov3.caffemodel** 
 
        **wget -P $HOME/yolov3 https://c7xcode.obs.cn-north-4.myhuaweicloud.com/models/yolov3/yolov3.prototxt**

        **wget -P $HOME/yolov3 https://c7xcode.obs.myhuaweicloud.com/models/yolov3/aipp_bgr.cfg** 
        >![](public_sys-resources/icon-note.gif) **说明：**   
        >- yolov3原始模型网络： https://github.com/maxuehao/YOLOV3/blob/master/yolov3_res18.prototxt 
        >- yolov3原始网络LICENSE地址： https://github.com/maxuehao/caffe/blob/master/LICENSE
        >- C7x对prototxt文件有修改要求，按照[SSD网络模型prototxt修改](https://support.huaweicloud.com/usermanual-mindstudioc73/atlasmindstudio_02_0114.html)文档对prototxt文件进行修改。这里已经修改完成，直接执行以上命令下载即可。

3.  将原始网络模型转换为适配昇腾AI处理器的模型。  

    1.  设置环境变量
        
        命令行中输入以下命令设置环境变量。

        **cd \$HOME/yolov3**
        
        **export install_path=\$HOME/Ascend/ascend-toolkit/20.0.RC1/x86_64-linux_gcc7.3.0**  

        **export PATH=/usr/local/python3.7.5/bin:\\${install_path}/atc/ccec_compiler/bin:\\${install_path}/atc/bin:\\$PATH**  

        **export PYTHONPATH=\\${install_path}/atc/python/site-packages/te:\\${install_path}/atc/python/site-packages/topi:\\$PYTHONPATH**  

        **export LD_LIBRARY_PATH=\\${install_path}/atc/lib64:\\$LD_LIBRARY_PATH**  

        **export ASCEND_OPP_PATH=\\${install_path}/opp**  

    2.  执行以下命令转换模型。

        **atc --model=yolov3.prototxt --weight=yolov3.caffemodel --framework=0 --output=yolov3 --soc_version=Ascend310 --insert_op_conf=aipp_bgr.cfg**
    
4.  将转换好的模型文件（.om文件）上传到[步骤1](#zh-cn_topic_0219108795_li953280133816)中源码所在路径下的“**objectdetection_video/model**”目录下。
    
    **cp ./yolov3.om \$HOME/AscendProjects/objectdetection_video/model/**
    

## 环境配置   

**注：服务器上已安装OpenCV、PresentAgent、交叉编译工具可跳过此步骤。**  
    
- 安装编译工具  
  **sudo apt-get install -y g++\-aarch64-linux-gnu g++\-5-aarch64-linux-gnu** 

- 安装OpenCV 
      
    请参考 **https://gitee.com/ascend/common/blob/master/install_opencv/for_atlas200dk/README.md**   

- 安装PresenterAgent   
    请参考 **https://gitee.com/ascend/common/blob/master/install_presenteragent/for_atlas200dk/README.md**  

## 编译<a name="zh-cn_topic_0219108795_section3723145213347"></a>

1.  打开对应的工程。

    以Mind Studio安装用户在命令行进入安装包解压后的“MindStudio-ubuntu/bin”目录，如：$HOME/MindStudio-ubuntu/bin。执行如下命令启动Mind Studio。

    **./MindStudio.sh**

    启动成功后，打开**objectdetection_video**工程，如[图 打开objectdetection-video工程](#zh-cn_topic_0228461902_zh-cn_topic_0203223265_fig11106241192810)所示。

    **图 1**  打开objectdetection-video工程<a name="zh-cn_topic_0228461902_zh-cn_topic_0203223265_fig11106241192810"></a>  
    ![](figures/打开objectdetection_video工程.png "打开objectdetection-video工程")

2.  修改Presenter Server的ip。  
    -  将**script/presentserver/display/config/config.conf**中的**presenter_server_ip**修改为Mind Studio所在Ubuntu服务器的虚拟网卡的ip地址，如[图 presenter_server_ip](#zh-cn_topic_0228461902_zh-cn_topic_0203223265_fig1110624110)所示。

      **图 2**  修改presenter_server_ip<a name="zh-cn_topic_0228461902_zh-cn_topic_0203223265_fig1110624110"></a>  
      ![](figures/presenter_server_ip.png "修改presenter_server_ip")      
    -  将**src/sample_process.cpp**中的 **param.host_ip** 修改为Mind Studio所在Ubuntu服务器的虚拟网卡的ip地址，如[图 param_host_ip](#zh-cn_topic_0228461902_zh-cn_topic_0203223265_fig11)所示。

      **图 3**  修改param_host_ip<a name="zh-cn_topic_0228461902_zh-cn_topic_0203223265_fig11"></a>  
      ![](figures/param_host_ip.png "修改param_host_ip")    

    >![](public_sys-resources/icon-note.gif) **说明：**    
    >-  虚拟网卡的ip地址请通过ifconfig命令查看。    
3.  开始编译，打开Mind Studio工具，在工具栏中点击**Build \> Edit Build Configuration**。  
    选择**Target OS** 为**Centos7.6**，如[图 配置编译](#zh-cn_topic_0203223265_fig17414647130)所示。

    **图 4**  配置编译<a name="zh-cn_topic_0203223265_fig17414647130"></a>  
    ![](figures/配置build.png "配置编译")  
    
    之后点击**Build \> Build \> Build Configuration**，如[图 编译操作及生成文件](#zh-cn_topic_0203223265_fig1741464713019)所示，会在目录下生成build和out文件夹。

    **图 5**  编译操作及生成文件<a name="zh-cn_topic_0203223265_fig1741464713019"></a>  
    ![](figures/编译操作及生成文件.png "编译操作及生成文件")

    >![](public_sys-resources/icon-notice.gif) **须知：**   
    >首次编译工程时，**Build \> Build**为灰色不可点击状态。需要点击**Build \> Edit Build Configuration**，配置编译参数后再进行编译。  

4.  启动Presenter Server。

    打开Mind Studio工具的Terminal，在应用代码存放路径下，执行如下命令在后台启动objectdetection-video应用的Presenter Server主程序。如[图 启动PresenterServer](#zh-cn_topic_0228461904_zh-cn_topic_0203223294_fig423515251067)所示。

    **python3 script/presenterserver/presenter_server.py --app=display &**

    **图 6**  启动PresenterServer<a name="zh-cn_topic_0228461904_zh-cn_topic_0203223294_fig423515251067"></a>  
    ![](figures/presentserver1.png)
   
  
    如[图 启动PresenterServer](#zh-cn_topic_0228461904_zh-cn_topic_0203223294_fig423)所示，表示presenter_server的服务启动成功。  
    **图 7**  启动PresenterServer<a name="zh-cn_topic_0228461904_zh-cn_topic_0203223294_fig423"></a>    
    ![](figures/presentserver2.png)

## 运行<a name="zh-cn_topic_0219108795_section1620073406"></a>
1.  在Mind Studio工具的工具栏中找到Run按钮，单击  **Run \> Edit Configurations**。  
    在Command Arguments 中添加运行参数 **../data/detection.mp4**（输入视频的路径），之后分别点击Apply、OK。如[图 配置运行](#zh-cn_topic_0203223265_fig93931954162720)所示。   

    **图 8**  配置运行<a name="zh-cn_topic_0203223265_fig93931954162720"></a>   
    ![](figures/配置run.png "配置运行")
 
2.  单击  **Run \> Run 'objectdetection_video'**，如[图 程序已执行示意图](#zh-cn_topic_0203223265_fig93931954162719)所示，可执行程序已经在开发者板执行。  

    **图 9**  程序已执行示意图<a name="zh-cn_topic_0203223265_fig93931954162719"></a>  
    ![](figures/程序已执行示意图.png "程序已执行示意图")  
3.  使用启动Presenter Server服务时提示的URL登录 Presenter Server 网站。

    等待Presenter Agent传输数据给服务端，单击“Refresh“刷新，当有数据时相应的Channel 的Status变成绿色，如下图所示。

    **图 10**  Presenter Server界面<a name="zh-cn_topic_0228461904_zh-cn_topic_0203223294_fig113691556202312"></a>  
    ![](figures/Presenter-Server界面.png "Presenter-Server界面") 

4.  单击右侧对应的View Name链接，比如上图的“video”，查看结果。




