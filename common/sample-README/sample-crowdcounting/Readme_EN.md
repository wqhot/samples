English|[中文](Readme.md)

**This case is only used for learning. It is not responsible for the effect and does not support commercial use.**

# Dense Crowd Counting<a name="EN-US_TOPIC_0232634535"></a>

Developers can deploy this application on the Atlas 200 DK or the AI acceleration cloud server to decode local MP4 files or RTSP video streams, predict the number of people in the crowd images, and send the result to the Presenter Server for storage and display.

The applications in the current version branch adapt to  [DDK&RunTime](https://ascend.huawei.com/resources) **1.32.0.0 and later**.

## Prerequisites<a name="en-us_topic_0219059426_section137245294533"></a>

Before deploying this sample, ensure that:

-   Mind Studio  has been installed.
-   The Atlas 200 DK developer board has been connected to  Mind Studio, the cross compiler has been installed, the SD card has been prepared, and basic information has been configured.

## Software Preparation<a name="en-us_topic_0219059426_section8534138124114"></a>

Before running the sample, obtain the source code package and configure the environment as follows:

1.  <a name="en-us_topic_0219059426_li953280133816"></a>Obtain the source code package.
    1.  By downloading the package

        Download all the code in the repository at  [https://gitee.com/Atlas200DK/sample-crowdcounting/tree/1.3x.0.0/](https://gitee.com/Atlas200DK/sample-crowdcounting/tree/1.3x.0.0/)  to any directory on Ubuntu Server where Mind Studio is located as the Mind Studio installation user, for example,  **$HOME/AscendProjects/sample-crowdcounting**.

    2.  By running the  **git**  command

        Run the following command in the  **$HOME/AscendProjects**  directory to download code:

        **git clone https://gitee.com/Atlas200DK/sample-crowdcounting.git --branch 1.3x.0.0**

2.  <a name="en-us_topic_0219059426_li8221184418455"></a>Obtain the source network model required by the application.

    Obtain the source network model used in the application by referring to  [Table 1](#en-us_topic_0219059426_table117203103464)  and save the model to any directory on Ubuntu Server where  Mind Studio  is located, for example:  **$HOME/models/crowdcounting**.

    **Table  1**  Model used in the crowd counting application

    <a name="en-us_topic_0219059426_table117203103464"></a>
    <table><thead align="left"><tr id="en-us_topic_0219059426_row4859191074617"><th class="cellrowborder" valign="top" width="17%" id="mcps1.2.4.1.1"><p id="en-us_topic_0219059426_p18859111074613"><a name="en-us_topic_0219059426_p18859111074613"></a><a name="en-us_topic_0219059426_p18859111074613"></a>Model Name</p>
    </th>
    <th class="cellrowborder" valign="top" width="18%" id="mcps1.2.4.1.2"><p id="en-us_topic_0219059426_p17859171013469"><a name="en-us_topic_0219059426_p17859171013469"></a><a name="en-us_topic_0219059426_p17859171013469"></a>Description</p>
    </th>
    <th class="cellrowborder" valign="top" width="65%" id="mcps1.2.4.1.3"><p id="en-us_topic_0219059426_p1385991094614"><a name="en-us_topic_0219059426_p1385991094614"></a><a name="en-us_topic_0219059426_p1385991094614"></a>Download Path</p>
    </th>
    </tr>
    </thead>
    <tbody><tr id="en-us_topic_0219059426_row88591310124617"><td class="cellrowborder" valign="top" width="17%" headers="mcps1.2.4.1.1 "><p id="en-us_topic_0219059426_p13106121801715"><a name="en-us_topic_0219059426_p13106121801715"></a><a name="en-us_topic_0219059426_p13106121801715"></a>crowd_counting</p>
    </td>
    <td class="cellrowborder" valign="top" width="18%" headers="mcps1.2.4.1.2 "><p id="en-us_topic_0219059426_p13106171831710"><a name="en-us_topic_0219059426_p13106171831710"></a><a name="en-us_topic_0219059426_p13106171831710"></a>Dense crowd counting network model</p>
    </td>
    <td class="cellrowborder" valign="top" width="65%" headers="mcps1.2.4.1.3 "><p id="en-us_topic_0219059426_p110671813170"><a name="en-us_topic_0219059426_p110671813170"></a><a name="en-us_topic_0219059426_p110671813170"></a>Download the model file of the source network by referring to <strong id="en-us_topic_0219059426_b0819154417137"><a name="en-us_topic_0219059426_b0819154417137"></a><a name="en-us_topic_0219059426_b0819154417137"></a>README.md</strong> at <a href="https://gitee.com/HuaweiAscend/models/tree/master/computer_vision/object_detect/crowd_counting" target="_blank" rel="noopener noreferrer">https://gitee.com/HuaweiAscend/models/tree/master/computer_vision/object_detect/crowd_counting</a>.</p>
    </td>
    </tr>
    </tbody>
    </table>

3.  Log in to Ubuntu Server where Mind Studio is located as the Mind Studio installation user, confirm the current DDK version, and set the environment variables  **DDK\_HOME**,  **tools\_version**, and  **LD\_LIBRARY\_PATH**.
    1.  <a name="en-us_topic_0219059426_en-us_topic_0203223294_li61417158198"></a>Query the current DDK version.

        A DDK version can be queried by using either Mind Studio or the DDK software package.

        -   Using Mind Studio

            On the project page of Mind Studio, choose  **File \> Settings \> System Settings \> Ascend DDK**  to query the DDK version.

            **Figure  1**  Querying the DDK version<a name="en-us_topic_0219059426_en-us_topic_0203223294_fig17553193319118"></a>  
            ![](figures/querying-the-ddk-version.png "querying-the-ddk-version")

            The displayed  **DDK Version**  is the current DDK version, for example,  **1.32.0.B080**.

        -   Using the DDK software package

            Obtain the DDK version based on the DDK package name.

            DDK package name format:  **Ascend\_DDK-\{software version\}-\{interface version\}-x86\_64.ubuntu16.04.tar.gz**

            _Software version_  indicates the DDK software version.

            For example:

            If the DDK package name is  **Ascend\_DDK-1.32.0.B080-1.1.1-x86\_64.ubuntu16.04.tar.gz**, the DDK version is  **1.32.0.B080**.

    2.  Set environment variables.

        **vim \~/.bashrc**

        Run the following commands to add the environment variables  **DDK\_HOME**  and  **LD\_LIBRARY\_PATH**  to the last line:

        **export tools\_version=_1.32.X.X_**

        **export DDK\_HOME=$HOME/.mindstudio/huawei/ddk/_1.32.X.X_/ddk**

        **export LD\_LIBRARY\_PATH=$DDK\_HOME/lib/x86\_64-linux-gcc5.4**

        >![](public_sys-resources/icon-note.gif) **NOTE:**   
        >-   **_1.32.X.X_**  indicates the DDK version queried in  [a](#en-us_topic_0219059426_en-us_topic_0203223294_li61417158198). Set this parameter based on the query result, for example,  **1.32.0.B080**.  
        >-   If the environment variables have been added, skip this step.  

        Type  **:wq!**  to save settings and exit.

        Run the following command for the environment variable to take effect:

        **source \~/.bashrc**

4.  Convert the source network model to a model supported by the Ascend AI processor.
    1.  Choose  **Tools \> Model Convert**  from the main menu of  Mind Studio.
    2.  On the  **Model Conversion**  page that is displayed, configure model conversion.
        -   Select the model file downloaded in  [Step 2](#en-us_topic_0219059426_li8221184418455)  for  **Model File**.
        -   Set  **Model Name**  to the model name in  [Table 1](#en-us_topic_0219059426_table117203103464).
        -   [Figure 2](#en-us_topic_0219059426_fig8912228135419)  shows the non-default configuration during the crowd\_counting model conversion.
        -   Retain the default values for other parameters.

            **Figure  2**  crowd\_counting model conversion<a name="en-us_topic_0219059426_fig8912228135419"></a>  
            

            ![](figures/en-us_image_0219068294.png)

            ![](figures/en-us_image_0219068655.png)

    3.  Click  **OK**  to start model conversion.

        After successful conversion, an .om offline model is generated in the  **$HOME/modelzoo/crowd\_counting/device**  directory.

        >![](public_sys-resources/icon-note.gif) **NOTE:**   
        >-   For details about the descriptions of each step and parameters in model conversion, see "Model Conversion" in the  [Mind Studio User Guide](https://ascend.huawei.com/doc/mindstudio/).  


5.  Upload the converted .om model file to the  **sample-crowdcounting/script**  directory in the source code path in  [Step 1](#en-us_topic_0219059426_li953280133816).

## Build<a name="en-us_topic_0219059426_section1759513564117"></a>

1.  Open the project.

    Go to the directory that stores the decompressed installation package as the Mind Studio installation user in CLI mode, for example,  **$HOME/MindStudio-ubuntu/bin**. Run the following command to start Mind Studio:

    **./MindStudio.sh**

    Open the  **sample-crowdcounting**  project.

2.  Configure project information in the  **src/param\_configure.conf**  file.

    **Figure  3**  Configuration file path<a name="en-us_topic_0219059426_fig1557065718252"></a>  
    

    ![](figures/en-us_image_0219071560.png)

    The default configurations of the configuration file are as follows:

    ```
    remote_host=192.168.1.2
    presenter_view_app_name=video
    video_path_of_host=/home/HwHiAiUser/car.mp4
    rtsp_video_stream=
    ```

    -   **remote\_host**: IP address of the Atlas 200 DK developer board
    -   **presenter\_view\_app\_name**: value of  **View Name**  on the  **Presenter Server**  page, which must be unique. The value consists of 3 to 20 characters and supports only uppercase letters, lowercase letters, digits, and underscores \(\_\).
    -   **video\_path\_of\_host**: absolute path of a video file on the host side
    -   **rtsp\_video\_stream**: URL of RTSP video streams

    Sample of video file configuration:

    ```
    remote_host=192.168.1.2
    presenter_view_app_name=video
    video_path_of_host=/home/HwHiAiUser/car.mp4
    rtsp_video_stream=
    ```

    Sample of RTSP video stream configuration:

    ```
    remote_host=192.168.1.2
    presenter_view_app_name=video
    video_path_of_host=
    rtsp_video_stream=rtsp://192.168.2.37:554/cam/realmonitor?channel=1&subtype=0
    ```

    >![](public_sys-resources/icon-note.gif) **NOTE:**   
    >-   **remote\_host**  and  **presenter\_view\_app\_name**  must be set. Otherwise, the build fails.  
    >-   Do not use double quotation marks \(""\) during parameter settings.  
    >-   Either  **video\_path\_of\_host**  or  **rtsp\_video\_stream**  must be set.  
    >-   Currently, RTSP video streams support only the  **rtsp://ip:port/path**  format. To use URLs in other formats, you need to delete the** IsValidRtsp**  function from the  **video\_decode.cpp**  file or configure the  **IsValidRtsp**  function to directly return  **true**  to skip regular expression matching.  
    >-   The RTSP stream URL provided in this sample cannot be directly used. If RTSP streams are required, create RTSP streams locally either using LIVE555 or other methods, which must support playback in the VLC. Type the URL of the RTSP video streams in the configuration file.  
    >-   Modify the default configurations as required.  

3.  Run the  **deploy.sh**  script to adjust configuration parameters and download and compile the third-party library. Open the  **Terminal**  window of Mind Studio. By default, the home directory of the code is used. Run the  **deploy.sh**  script in the background to deploy the environment, as shown in  [Figure 4](#en-us_topic_0219059426_fig202009167369).

    **Figure  4**  Running the deploy.sh script<a name="en-us_topic_0219059426_fig202009167369"></a>  
    ![](figures/running-the-deploy-sh-script.png "running-the-deploy-sh-script")

    >![](public_sys-resources/icon-note.gif) **NOTE:**   
    >-   During the first deployment, if no third-party library is used, the system automatically downloads and builds the third-party library, which may take a long time. The third-party library can be directly used for the subsequent build.  
    >-   During deployment, select the IP address of the host that communicates with the developer board. Generally, the IP address is that configured for the virtual NIC. If the IP address is in the same network segment as the IP address of the developer board, it is automatically selected for deployment. If they are not in the same network segment, you need to manually type the IP address of the host that communicates with the developer board to complete the deployment.  

4.  Start building. Open Mind Studio and choose  **Build \> Build \> Build-Configuration**  from the main menu. The  **build**  and  **run**  folders are generated in the directory.

    >![](public_sys-resources/icon-notice.gif) **NOTICE:**   
    >When you build a project for the first time,  **Build \> Build**  is unavailable. You need to choose  **Build \> Edit Build Configuration**  to set parameters before the build.  

5.  Start Presenter Server.

    Open the  **Terminal**  window of Mind Studio. Under the code path, run the following command to start the Presenter Server program of the license crowd counting application on the server, as shown in  [Figure 5](#en-us_topic_0219059426_fig102142024389).

    **bash run\_present\_server.sh**

    **Figure  5**  Starting Presenter Server<a name="en-us_topic_0219059426_fig102142024389"></a>  
    

    ![](figures/en-us_image_0219072221.png)

    -   When the message  **Please choose one to show the presenter in browser\(default: 127.0.0.1\):**  is displayed, type the IP address \(usually IP address for accessing  Mind Studio\) used for accessing the Presenter Server service in the browser.

        Select the IP address used by the browser to access the Presenter Server service in  **Current environment valid ip list**  and type the path for storing video analysis data, as shown in  [Figure 6](#en-us_topic_0219059426_fig73590910118).

        **Figure  6**  Project deployment<a name="en-us_topic_0219059426_fig73590910118"></a>  
        

        ![](figures/en-us_image_0219072532.png)

    [Figure 7](#en-us_topic_0219059426_fig19953175965417)  shows that the Presenter Server service has been started successfully.

    **Figure  7**  Starting the Presenter Server process<a name="en-us_topic_0219059426_fig19953175965417"></a>  
    

    ![](figures/en-us_image_0219072725.png)

    Use the URL shown in the preceding figure to log in to Presenter Server \(only Google Chrome is supported\). The IP address is that typed in  [Figure 6](#en-us_topic_0219059426_fig73590910118)  and the default port number is  **7007**. The following figure indicates that Presenter Server has been started successfully.

    **Figure  8**  Home page<a name="en-us_topic_0219059426_fig129539592546"></a>  
    ![](figures/home-page.png "home-page")

    The following figure shows the IP address used by Presenter Server and  Mind Studio  to communicate with the Atlas 200 DK.

    **Figure  9**  IP address example<a name="en-us_topic_0219059426_fig195318596543"></a>  
    ![](figures/ip-address-example.png "ip-address-example")

    -   The IP address of the Atlas 200 DK developer board is  **192.168.1.2**  \(connected in USB mode\).
    -   The IP address used by Presenter Server to communicate with the Atlas 200 DK is in the same network segment as the IP address of the Atlas 200 DK on the UI Host server, for example,  **192.168.1.223**.
    -   The following describes how to access the IP address \(such as  **10.10.0.1**\) of Presenter Server using a browser. Because Presenter Server and  Mind Studio  are deployed on the same server, you can access  Mind Studio  through the browser using the same IP address.

6.  The crowd counting application can parse local videos and RTSP video streams.
    -   To parse a local video, upload the video file to the host.

        For example, upload the video file  **crowd.mp4**  to the  **/home/HwHiAiUser/**  directory on the host.

        >![](public_sys-resources/icon-note.gif) **NOTE:**   
        >H.264 and H.265 MP4 files are supported. If an MP4 file needs to be edited, you are advised to use FFmpeg. If a video file is edited by other tools, FFmpeg may fail to parse the file.  

    -   If only RTSP video streams need to be parsed, skip this step.


## Run<a name="en-us_topic_0219059426_section6245151616426"></a>

1.  Run the crowd counting application.

    On the toolbar of Mind Studio, click  **Run**  and choose  **Run \> Run 'sample-crowdcounting'**. As shown in  [Figure 10](#en-us_topic_0219059426_fig12953163061713), the executable application is running on the developer board.

    **Figure  10**  Application running<a name="en-us_topic_0219059426_fig12953163061713"></a>  
    

    ![](figures/en-us_image_0219073392.png)

2.  Use the URL displayed upon the start of the Presenter Server service to log in to Presenter Server.

    Wait for Presenter Agent to transmit data to the server. Click  **Refresh**. When there is data, the icon in the  **Status**  column for the corresponding channel changes to green, as shown in  [Figure 11](#en-us_topic_0219059426_fig69382913311).

    **Figure  11**  Presenter Server page<a name="en-us_topic_0219059426_fig69382913311"></a>  
    ![](figures/presenter-server-page.png "presenter-server-page")

    >![](public_sys-resources/icon-note.gif) **NOTE:**   
    >-   For the crowd counting application, Presenter Server supports a maximum of 10 channels at the same time \(each  _presenter\_view\_app\_name_  parameter corresponds to a channel\).  
    >-   Due to hardware limitations, each channel supports a maximum frame rate of 20 fps. A lower frame rate is automatically used when the network bandwidth is low.  

3.  Click a link in the  **View Name**  column, for example,  **video**  in the preceding figure, and view the result.

## Follow-up Operations<a name="en-us_topic_0219059426_section1092612277429"></a>

-   Stopping the crowd counting application

    The crowd counting application is running continually after being executed. To stop it, perform the following operation:

    Click the stop button to stop the crowd counting application. As shown in  [Figure 12](#en-us_topic_0219059426_fig464152917203), the crowd counting application has stopped running.

    **Figure  12**  Stopping the crowd counting application<a name="en-us_topic_0219059426_fig464152917203"></a>  
    

    ![](figures/en-us_image_0219075771.png)

-   **Stopping the Presenter Server service**

    The Presenter Server service is always in running state after being started. To stop the Presenter Server service of the crowd counting application, perform the following operations:

    On the server with  Mind Studio  installed, run the following command as the  Mind Studio  installation user to check the process of the Presenter Server service corresponding to the crowd counting application:

    **ps -ef | grep presenter | grep crowd\_counting**

    ```
    ascend@ascend-HP-ProDesk-600-G4-PCI-MT:~/sample-crowdcounting$ ps -ef | grep presenter | grep crowd_counting 
     ascend    7701  1615  0 14:21 pts/8    00:00:00 python3 presenterserver/presenter_server.py --app crowd_counting
    ```

    In the preceding information,  _7701_  indicates the process ID of the Presenter Server service for the crowd counting application.

    To stop the service, run the following command:

    **kill -9** _7701_


