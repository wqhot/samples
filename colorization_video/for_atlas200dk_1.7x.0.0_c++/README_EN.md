English|[中文](README_EN.md)

**This case is only used for learning. It is not responsible for the effect and does not support commercial use.**

# Video Colorization<a name="ZH-CN_TOPIC_0219122211"></a>

This application can run on the Atlas 200 DK to colorize black and white videos.

Before running this sample, obtain the source code package.

1. <a name="zh-cn_topic_0228757084_section8534138124114"></a>Obtain the source code package.
   
    **cd $HOME/AscendProjects**
   
    **wget https://c7xcode.obs.cn-north-4.myhuaweicloud.com/code_Ascend/colorization_video.zip**
   
    **unzip colorization_video.zip**
   
    > ![](public_sys-resources/icon-note.gif) NOTE 
    > - If the download using **wget** fails, run the following command to download the code:   
    **curl -OL https://c7xcode.obs.cn-north-4.myhuaweicloud.com/code_Ascend/colorization_video.zip**
    > - If the download using **curl** also fails, open the download link in a browser to download the code and manually upload it to the server.

2. <a name="zh-cn_topic_0219108795_li2074865610364"></a>Obtain the  model required by the application.
   
    Obtain the  model file（googlenet.prototxt） and weight file（googlenet.caffemodel） by referring to [Table 1 Model for a video colorization application](#zh-cn_topic_0219108795_table19942111763710) and store them to any directory of the Ubuntu server, for example, **$HOME/models/colorization_video.**
   
    **Table 1** Model for a video colorization application
   
    <a name="zh-cn_topic_0219108795_table19942111763710"></a>
   
    <table><thead align="left"><tr id="zh-cn_topic_0219108795_row611318123710"><th class="cellrowborder" valign="top" width="11.959999999999999%" id="mcps1.2.4.1.1"><p id="zh-cn_topic_0219108795_p81141820376"><a name="zh-cn_topic_0219108795_p81141820376"></a><a name="zh-cn_topic_0219108795_p81141820376"></a>Model name</p>
    </th>
    <th class="cellrowborder" valign="top" width="8.07%" id="mcps1.2.4.1.2"><p id="zh-cn_topic_0219108795_p13181823711"><a name="zh-cn_topic_0219108795_p13181823711"></a><a name="zh-cn_topic_0219108795_p13181823711"></a>Model description</p>
    </th>
    <th class="cellrowborder" valign="top" width="79.97%" id="mcps1.2.4.1.3"><p id="zh-cn_topic_0219108795_p1717182378"><a name="zh-cn_topic_0219108795_p1717182378"></a><a name="zh-cn_topic_0219108795_p1717182378"></a>Model download link</p>
    </th>
    </tr>
    </thead>
    <tbody><tr id="zh-cn_topic_0219108795_row1119187377"><td class="cellrowborder" valign="top" width="11.959999999999999%" headers="mcps1.2.4.1.1 "><p id="zh-cn_topic_0219108795_p4745165253920"><a name="zh-cn_topic_0219108795_p4745165253920"></a><a name="zh-cn_topic_0219108795_p4745165253920"></a>colorization</p>
    </td>
    <td class="cellrowborder" valign="top" width="8.07%" headers="mcps1.2.4.1.2 "><p id="zh-cn_topic_0219108795_p1874515218391"><a name="zh-cn_topic_0219108795_p1874515218391"></a><a name="zh-cn_topic_0219108795_p1874515218391"></a>Image colorization model</p>
    </td>
    <td class="cellrowborder" valign="top" width="79.97%" headers="mcps1.2.4.1.3 "><p id="zh-cn_topic_0219108795_p611318163718"><a name="zh-cn_topic_0219108795_p611318163718"></a><a name="zh-cn_topic_0219108795_p611318163718"></a>Download the  model file（googlenet.prototxt） and weight file（googlenet.caffemodel） by referring to README_en.md at <a href="https://gitee.com/HuaweiAscend/models/blob/master/computer_vision/object_detect/colorization/README_en.md" target="_blank" rel="noopener noreferrer">https://gitee.com/HuaweiAscend/models/blob/master/computer_vision/object_detect/colorization/README_en.md</a>. </p>
    </td>
    </tr>
    </tbody>
    </table>

3. Convert the original model to an offline model adapted to the Ascend AI Processor.
   
    1. Choose **Tools** \> **Model Converter** from the menu bar of Mind Studio.
    2. Configure the model conversion settings in the displayed **Model Converter** dialog box.
    3. Set the parameters by referring to the following figure.
      - Select the model file downloaded in [Step 2](#zh-cn_topic_0219108795_li2074865610364) in **Model File**, and **Weight File** is automatically filled in.
      - Disable **Image Pre-processing**.
   
    ![](figures/模型转换1.png "Model conversion 1")  
    ![](figures/模型转换2.png "Model conversion 2")  
    ![](figures/模型转换3.png "Model conversion 3")

5. Upload the converted model file (.om) to the **colorization_video/model** directory under the path of the source code downloaded in [Step 1](#zh-cn_topic_0228757084_section8534138124114).
   
   **cp \\$HOME/modelzoo/colorization/device/colorization.om \\$HOME/AscendProjects/colorization_video/model/**

## Environment Configuration

**Note: If OpenCV, Presenter Agent, and a cross compiler have been installed on the server, skip this step.**

- Install the compiler.  
  **sudo apt-get install -y g++\-aarch64-linux-gnu g++\-5-aarch64-linux-gnu**

- Install OpenCV.
  
    For details, see **https://gitee.com/ascend/common/blob/master/install_opencv/for_atlas200dk/README.md**.

- Install Presenter Agent  
    For details, see **https://gitee.com/ascend/common/blob/master/install_presenteragent/for_atlas200dk/README.md**.

## Build<a name="zh-cn_topic_0219108795_section3723145213347"></a>

1. Open the project.
   
    Go to the directory of the decompressed installation package as the Mind Studio installation user in CLI mode, for example, **$HOME/MindStudio-ubuntu/bin**. Launch Mind Studio.
   
    **./MindStudio.sh**
   
    Open the **colorization_video** project, as shown in [Figure 1 Opening the colorization_video project](#zh-cn_topic_0228461902_zh-cn_topic_0203223265_fig11106241192810).
   
    **Figure 1** Opening the colorization_video project<a name="zh-cn_topic_0228461902_zh-cn_topic_0203223265_fig11106241192810"></a>  
    ![](figures/打开colorization_video工程.png "Opening the colorization_video project") 

2. Change the IP address of Presenter Server.
   
    - Change the value of **presenter_server_ip** in **script/presentserver/display/config/config.conf** to the virtual NIC IP address of the Ubuntu server where Mind Studio is installed, as shown in [Figure 2 Modifying presenter_server_ip](#zh-cn_topic_0228461902_zh-cn_topic_0203223265_fig1110624110).
   
      **Figure 2** Modifying presenter_server_ip<a name="zh-cn_topic_0228461902_zh-cn_topic_0203223265_fig1110624110"></a>  
      ![](figures/presenter_server_ip.png "Modifying presenter_server_ip")
   
    - Change the value of **param.host_ip** in **src/colorize_process.cpp** to the virtual NIC IP address of the Ubuntu server where Mind Studio is installed, as shown in [Figure 3 Modifying param_host_ip](#zh-cn_topic_0228461902_zh-cn_topic_0203223265_fig11).
   
      **Figure 3** Modifying param_host_ip<a name="zh-cn_topic_0228461902_zh-cn_topic_0203223265_fig11"></a>  
      ![](figures/param_host_ip.png "Modifying param_host_ip")
   
    > ![](public_sys-resources/icon-note.gif) NOTE
    > - Run the **ifconfig** command to view the IP address of the virtual NIC.

3. Start the build. Choose **Build \> Edit Build Configuration** on the toolbar of Mind Studio.   
Set **Target OS** to **Centos7.6**, as shown in [Figure 4 Build configuration](#zh-cn_topic_0203223265_fig17414647130).
   
    **Figure 4** Build configuration<a name="zh-cn_topic_0203223265_fig17414647130"></a>  
    ![](figures/配置build.png "Build configuration")
   
    Click **Build \> Build \> Build Configuration**. The **build** and **out** folders are generated in the directory, as shown in [Figure 5 Build operations and generated files](#zh-cn_topic_0203223265_fig1741464713019).
   
    **Figure 5** Build operations and generated files<a name="zh-cn_topic_0203223265_fig1741464713019"></a>  
    ![](figures/编译操作及生成文件.png "Build operations and generated files")
   
    > ![](public_sys-resources/icon-notice.gif) NOTE   
    When you build a project for the first time, **Build \> Build** is unavailable. You need to choose **Build \> Edit Build Configuration** to set parameters before the build.

4. Start Presenter Server.
   
    Open the Terminal window of Mind Studio. Run the following command in the path where the application code is stored to start Presenter Server in the background, as shown in [Figure 6 Starting Presenter Server.](#zh-cn_topic_0228461904_zh-cn_topic_0203223294_fig423515251067)
   
    **python3 script/presenterserver/presenter_server.py --app=display &**
   
    **Figure 6** Starting Presenter Server <a name="zh-cn_topic_0228461904_zh-cn_topic_0203223294_fig423515251067"></a>  
    ![](figures/presentserver1.png)
   
    Presenter Server is started successfully, as shown in [Figure 7 Presenter Server started successfully](#zh-cn_topic_0228461904_zh-cn_topic_0203223294_fig423).   
    **Figure 7** Presenter Server started successfully<a name="zh-cn_topic_0228461904_zh-cn_topic_0203223294_fig423"></a>  
    ![](figures/presentserver2.png)

## Run<a name="zh-cn_topic_0219108795_section1620073406"></a>

1. Choose **Run \> Edit Configurations** from the toolbar of Mind Studio.   
    Add the run parameter **../data/black-white_video.mp4** (path of the input video) in **Command Arguments**, and click **Apply** and **OK** in sequence, as shown in [Figure 8 Run/Debug Configurations](#zh-cn_topic_0203223265_fig93931954162720).
   
    **Figure 8** Run/Debug Configurations<a name="zh-cn_topic_0203223265_fig93931954162720"></a>  
    ![](figures/配置run.png "Run/Debug Configurations")

2. Click **Run \> Run 'colorization_video’**. The executable file has been executed on the developer board, as shown in [Figure 9 Execution finished](#zh-cn_topic_0203223265_fig93931954162719).
   
    **Figure 9** Execution finished<a name="zh-cn_topic_0203223265_fig93931954162719"></a>  
    ![](figures/程序已执行示意图.png "Execution finished")

3. Use the URL displayed upon the start of Presenter Server service to log in to Presenter Server.
   
    Wait for Presenter Agent to transmit data to the server and click Refresh. When there is data, the icon in the Status column for the corresponding channel turns green, as shown in the following figure.
   
    **Figure 10** Presenter Server page<a  name="zh-cn_topic_0228461904_zh-cn_topic_0203223294_fig113691556202312"></a>  
    ![](figures/Presenter-Server界面.png "Presenter Server page")

4. Click a link in the View Name column, for example, **"video"** in the preceding figure to view the result.