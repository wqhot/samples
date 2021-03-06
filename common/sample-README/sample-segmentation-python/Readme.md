中文|[English](Readme_EN.md)

**该案例仅仅用于学习，打通流程，不对效果负责，不支持商用。**

# 语义分割网络应用（Python）<a name="ZH-CN_TOPIC_0232330083"></a>

本Application支持运行在Atlas 200 DK上，实现了erfnet网络的推理功能并输出带有推理结果的图片。

当前分支中的应用适配**1.3.0.0**与**1.32.0.0及以上**版本的[DDK&RunTime](https://ascend.huawei.com/resources)。

## 前提条件<a name="zh-cn_topic_0228757085_section137245294533"></a>

部署此Sample前，需要准备好以下环境：

-   已完成Mind Studio的安装。

-   已完成Atlas 200 DK开发者板与Mind Studio的连接，SD卡的制作、编译环境的配置等。
-   由于需要配置开发板联网，默认设置为USB连接，开发板地址为192.168.1.2

## 软件准备<a name="zh-cn_topic_0228757085_section8534138124114"></a>

运行此应用前，需要按照此章节进行相关的环境配置并获取源码包。

1.  <a name="zh-cn_topic_0228757085_li953280133816"></a>获取源码包。
    1.  下载压缩包方式获取。

        将[https://gitee.com/ascend/samples/tree/1.32.0.0/sample-segmentation-python](https://gitee.com/ascend/samples/tree/1.32.0.0/sample-segmentation-python)仓中的代码以Mind Studio安装用户下载至Mind Studio所在Ubuntu服务器的任意目录，例如代码存放路径为：$HOME/sample-segmentation-python。

    2.  命令行使用git命令方式获取。

        在命令行中：$HOME/AscendProjects目录下执行以下命令下载代码。

        **git clone -b 1.32.0.0 https://gitee.com/ascend/samples.git**
        
        **mv samples/sample-segmentation-python ./**
        
2.  获取此应用中所需要的网络模型。

    参考[表 语义分割网络应用\(python\)使用模型](#zh-cn_topic_0228757085_table1119094515272)获取此应用中所用到的原始网络模型及其对应的权重文件，并将其存放到Mind Studio所在Ubuntu服务器的任意目录，例如：$HOME/ascend/models/sample-segmentation-python。

    **表 1**  语义分割网络应用\(python\)使用模型

    <a name="zh-cn_topic_0228757085_table1119094515272"></a>
    <table><thead align="left"><tr id="zh-cn_topic_0228757085_row677354502719"><th class="cellrowborder" valign="top" width="12.15%" id="mcps1.2.4.1.1"><p id="zh-cn_topic_0228757085_p167731845122717"><a name="zh-cn_topic_0228757085_p167731845122717"></a><a name="zh-cn_topic_0228757085_p167731845122717"></a>模型名称</p>
    </th>
    <th class="cellrowborder" valign="top" width="17.53%" id="mcps1.2.4.1.2"><p id="zh-cn_topic_0228757085_p277317459276"><a name="zh-cn_topic_0228757085_p277317459276"></a><a name="zh-cn_topic_0228757085_p277317459276"></a>模型说明</p>
    </th>
    <th class="cellrowborder" valign="top" width="70.32000000000001%" id="mcps1.2.4.1.3"><p id="zh-cn_topic_0228757085_p9773114512270"><a name="zh-cn_topic_0228757085_p9773114512270"></a><a name="zh-cn_topic_0228757085_p9773114512270"></a>模型下载路径</p>
    </th>
    </tr>
    </thead>
    <tbody><tr id="zh-cn_topic_0228757085_row3122314144215"><td class="cellrowborder" valign="top" width="12.15%" headers="mcps1.2.4.1.1 "><p id="zh-cn_topic_0228757085_p1910619166207"><a name="zh-cn_topic_0228757085_p1910619166207"></a><a name="zh-cn_topic_0228757085_p1910619166207"></a>erfnet</p>
    </td>
    <td class="cellrowborder" valign="top" width="17.53%" headers="mcps1.2.4.1.2 "><p id="zh-cn_topic_0228757085_p2010681612020"><a name="zh-cn_topic_0228757085_p2010681612020"></a><a name="zh-cn_topic_0228757085_p2010681612020"></a>图片语义分割推理模型。</p>
    <p id="zh-cn_topic_0228757085_p1710615162207"><a name="zh-cn_topic_0228757085_p1710615162207"></a><a name="zh-cn_topic_0228757085_p1710615162207"></a>是基于Caffe的erfnet模型。</p>
    </td>
    <td class="cellrowborder" valign="top" width="70.32000000000001%" headers="mcps1.2.4.1.3 "><p id="zh-cn_topic_0228757085_p910617162206"><a name="zh-cn_topic_0228757085_p910617162206"></a><a name="zh-cn_topic_0228757085_p910617162206"></a>请参考<a href="https://gitee.com/HuaweiAscend/models/tree/master/computer_vision/segmentation/erfnet" target="_blank" rel="noopener noreferrer">https://gitee.com/HuaweiAscend/models/tree/master/computer_vision/segmentation/erfnet</a>目录中README.md下载原始网络模型文件及其对应的权重文件。</p>
    </td>
    </tr>
    </tbody>
    </table>

3.  将原始网络模型转换为适配昇腾AI处理器的模型。
    1.  在Mind Studio操作界面的顶部菜单栏中选择**Tools \> Model Convert**，进入模型转换界面。
    2.  在弹出的**Model Conversion**操作界面中，Model File与Weight File分别选择[步骤1](#zh-cn_topic_0228757085_li953280133816)中下载的模型文件和权重文件。
        -   **Model Name**填写为[表 语义分割网络应用\(python\)使用模型](#zh-cn_topic_0228757085_table1119094515272)中对应的**模型名称**。
        -   erfnet模型转换时中AIPP配置中的**Model Image Format**  选择BGR888\_U8，关闭MeanLess选项
        -   其他参数保持默认值。

    3.  单击OK开始转换模型。

        1.1.0.0和1.3.0.0版本模型转换成功后，后缀为.om的离线模型存放地址为：**$HOME/tools/che/model-zoo/my-model/xxx**。

        1.32.0.0及以上版本模型转换成功后，后缀为.om的离线模型存放地址为：**$HOME/modelzoo/xxx/device/xxx.om**。

    4.  将转换好的模型文件（.om文件）上传到[步骤1](#zh-cn_topic_0228757085_li953280133816)中源码所在路径下的“sample-segmentation-python/segmentationapp/models”目录下。


## 环境部署与准备<a name="zh-cn_topic_0228757085_section218113616146"></a>

1.  应用代码拷贝到开发板。

    以Mind Studio安装用户进入语义分割网络应用\(python\)代码所在根目录，如：$HOME/sample-segmentation-python，执行以下命令将应用代码拷贝到开发板。

    **scp -r ../sample-segmentation-python/ HwHiAiUser@192.168.1.2:/home/HwHiAiUser/HIAI\_PROJECTS**

    提示password时输入开发板密码，开发板默认密码为**Mind@123**，如[图 应用代码拷贝](#zh-cn_topic_0228757085_zh-cn_topic_0219036254_fig1660453512014)。

    **图 1** **应用代码拷贝**<a name="zh-cn_topic_0228757085_zh-cn_topic_0219036254_fig1660453512014"></a>  
    

    ![](figures/zh-cn_image_0228836881.png)

    在Mind Studio所在Ubuntu服务器中，以HwHiAiUser用户SSH登录到Host侧。

    **ssh HwHiAiUser@192.168.1.2**

    切换到root用户，开发板中root用户默认密码为**Mind@123**。

    **su root**

2.  配置开发板联网。

    请参考[https://gitee.com/ascend/samples/tree/1.32.0.0/common/sample-README/DK_NetworkConnect](https://gitee.com/ascend/samples/tree/1.32.0.0/common/sample-README/DK_NetworkConnect)  ，进行开发板网络连接配置。

3.  安装环境依赖。

    请参考[https://gitee.com/ascend/samples/tree/1.32.0.0/common/sample-README/DK_Environment](https://gitee.com/ascend/samples/tree/1.32.0.0/common/sample-README/DK_Environment)  ，进行环境依赖配置。


## 程序运行<a name="zh-cn_topic_0228757085_section6245151616426"></a>

1.  切换HwHiAiUser用户，并进入语义分割网络应用代码所在目录。

    **su HwHiAiUser**

    **cd \~/HIAI\_PROJECTS/sample-segmentation-python/segmentationapp**

2.  执行应用程序。

    执行**segmentation.py**脚本会将推理结果在执行终端直接打印显示。

    命令示例如下所示：

    **python segmentation.py**

    执行成功后效果如[图 推理成功示意图](#zh-cn_topic_0228757085_fig1863053617417)所示。

    **图 2**  推理成功示意图<a name="zh-cn_topic_0228757085_fig1863053617417"></a>  
    

    ![](figures/zh-cn_image_0228757232.png)

3.  执行结果查看。

    执行结果保存在当前目录下的Result目录下，需要在Atlas200DK中用以下命令将结果拷贝到Ubuntu服务器中查看推理结果图片。

    **scp -r username@host\_ip:/home/username/HIAI\_PROJECTS/sample-classification-python/Result \~**

    -   username：开发板用户﻿名，默认为HwHiAiUser。
    -   host\_ip：开发板ip，USB连接一般为192.168.1.2.网线连接时一般为192.168.0.2。

    **命令示例：**

    **scp -r HwHiAiUser@192.168.1.2:/home/HwHiAiUser/HIAI\_PROJECTS/sample-classification-python/Result \~**

    该命令会把推理结果拷贝到Mindstudio安装用户的家目录中，可以直接查看。


## 相关说明<a name="zh-cn_topic_0228757085_section1092612277429"></a>

-   **语义分割网络应用（Python）的流程说明如下**：
    1.  从cityimage目录下读取jpeg图片。
    2.  将读取的jpeg图片调用opencv resize到1024\*512，并转换成YUV420SP。
    3.  将转换后的YUV420SP图片数据送入Matrix进行推理。demo采用的是erfnet网络，推理结果是每个像素点的19个分类的置信度
    4.  后处理阶段，每个像素点选取最高置信度的分类，在图片上对同种分类进行涂色。涂色后图片存放在Result目录下。

-   **语义分割网络应用（Python）的文件架构说明如下**：
    -   cityimage：存放输入图片
    -   segmentation.py：主程序
    -   jpegHandler.py：jpeg图片处理，如resize、色域转换等
    -   models：存放模型网络
    -   Result：存放标注后的图片


