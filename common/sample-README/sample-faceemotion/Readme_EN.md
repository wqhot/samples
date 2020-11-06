English|[中文](Readme.md)

**This case is only used for learning. It is not responsible for the effect and does not support commercial use.**

# Facial Expression Recognition<a name="EN-US_TOPIC_0232635770"></a>

Developers can deploy this application on the Atlas 200 DK to predict seven types of facial expressions in videos, including anger, disgust, fear, happy, sad, surprised, and normal.

The applications in the current version branch adapt to  [DDK&RunTime](https://ascend.huawei.com/resources) **1.32.0.0 and later**.

## Prerequisites<a name="en-us_topic_0219102918_section137245294533"></a>

Before deploying this sample, ensure that:

-   Mind Studio  has been installed.
-   The Atlas 200 DK developer board has been connected to  Mind Studio, the cross compiler has been installed, the SD card has been prepared, and basic information has been configured.

## Software Preparation<a name="en-us_topic_0219102918_section081240125311"></a>

Before running this sample, obtain the source code package, configure the environment, and prepare a model file as follows:

1.  <a name="en-us_topic_0219102918_li953280133816"></a>Obtain the source code package.
    1.  By downloading the package

        Download all the code in the repository at  [https://gitee.com/Atlas200DK/sample-faceemotion/tree/1.3x.0.0/](https://gitee.com/Atlas200DK/sample-faceemotion/tree/1.3x.0.0/)  to any directory on Ubuntu Server where Mind Studio is located as the Mind Studio installation user, for example,  **$HOME/AscendProjects/sample-faceemotion**.

    2.  By running the  **git**  command

        Run the following command in the  **$HOME/AscendProjects**  directory to download code:

        **git clone https://gitee.com/Atlas200DK/sample-faceemotion.git --branch 1.3x.0.0**

2.  <a name="en-us_topic_0219102918_li1365682471610"></a>Obtain the source network model required by the application.

    Obtain the source network model and its weight file used in the application by referring to  [Table 1](#en-us_topic_0219102918_table144841813177)  and save them to the same directory on Ubuntu Server where  Mind Studio  is located, for example,  **$HOME/models/faceemotion**.

    **Table  1**  Models used in the face emotion application

    <a name="en-us_topic_0219102918_table144841813177"></a>
    <table><thead align="left"><tr id="en-us_topic_0219102918_row161061318181712"><th class="cellrowborder" valign="top" width="20%" id="mcps1.2.4.1.1"><p id="en-us_topic_0219102918_p1410671814173"><a name="en-us_topic_0219102918_p1410671814173"></a><a name="en-us_topic_0219102918_p1410671814173"></a>Model Name</p>
    </th>
    <th class="cellrowborder" valign="top" width="20%" id="mcps1.2.4.1.2"><p id="en-us_topic_0219102918_p1106118121716"><a name="en-us_topic_0219102918_p1106118121716"></a><a name="en-us_topic_0219102918_p1106118121716"></a>Description</p>
    </th>
    <th class="cellrowborder" valign="top" width="60%" id="mcps1.2.4.1.3"><p id="en-us_topic_0219102918_p14106218121710"><a name="en-us_topic_0219102918_p14106218121710"></a><a name="en-us_topic_0219102918_p14106218121710"></a>Download Path</p>
    </th>
    </tr>
    </thead>
    <tbody><tr id="en-us_topic_0219102918_row1710661814171"><td class="cellrowborder" valign="top" width="20%" headers="mcps1.2.4.1.1 "><p id="en-us_topic_0219102918_p0737128131720"><a name="en-us_topic_0219102918_p0737128131720"></a><a name="en-us_topic_0219102918_p0737128131720"></a>face_detection</p>
    </td>
    <td class="cellrowborder" valign="top" width="20%" headers="mcps1.2.4.1.2 "><p id="en-us_topic_0219102918_p12737172817172"><a name="en-us_topic_0219102918_p12737172817172"></a><a name="en-us_topic_0219102918_p12737172817172"></a>Network model for face detection.</p>
    <p id="en-us_topic_0219102918_p6737102815173"><a name="en-us_topic_0219102918_p6737102815173"></a><a name="en-us_topic_0219102918_p6737102815173"></a>It is converted from the Caffe-based ResNet10-SSD300 model.</p>
    </td>
    <td class="cellrowborder" valign="top" width="60%" headers="mcps1.2.4.1.3 "><p id="en-us_topic_0219102918_p147371628111713"><a name="en-us_topic_0219102918_p147371628111713"></a><a name="en-us_topic_0219102918_p147371628111713"></a>Download the source network model file and its weight file by referring to <strong id="en-us_topic_0219102918_b18529261791"><a name="en-us_topic_0219102918_b18529261791"></a><a name="en-us_topic_0219102918_b18529261791"></a>README.md</strong> at <a href="https://gitee.com/HuaweiAscend/models/tree/master/computer_vision/object_detect/face_detection" target="_blank" rel="noopener noreferrer">https://gitee.com/HuaweiAscend/models/tree/master/computer_vision/object_detect/face_detection</a>.</p>
    </td>
    </tr>
    <tr id="en-us_topic_0219102918_row20991341914"><td class="cellrowborder" valign="top" width="20%" headers="mcps1.2.4.1.1 "><p id="en-us_topic_0219102918_p177378282173"><a name="en-us_topic_0219102918_p177378282173"></a><a name="en-us_topic_0219102918_p177378282173"></a>Face_emotion</p>
    </td>
    <td class="cellrowborder" valign="top" width="20%" headers="mcps1.2.4.1.2 "><p id="en-us_topic_0219102918_p19737192811710"><a name="en-us_topic_0219102918_p19737192811710"></a><a name="en-us_topic_0219102918_p19737192811710"></a>Network model for facial expression recognition. It is converted from a Caffe-based model.</p>
    </td>
    <td class="cellrowborder" valign="top" width="60%" headers="mcps1.2.4.1.3 "><p id="en-us_topic_0219102918_p963916373173"><a name="en-us_topic_0219102918_p963916373173"></a><a name="en-us_topic_0219102918_p963916373173"></a>Download the source network model file and its weight file by referring to <strong id="en-us_topic_0219102918_b11136714151914"><a name="en-us_topic_0219102918_b11136714151914"></a><a name="en-us_topic_0219102918_b11136714151914"></a>README.md</strong> at <a href="https://gitee.com/HuaweiAscend/models/tree/master/computer_vision/object_detect/face_emotion" target="_blank" rel="noopener noreferrer">https://gitee.com/HuaweiAscend/models/tree/master/computer_vision/object_detect/face_emotion</a>.</p>
    </td>
    </tr>
    </tbody>
    </table>

3.  Log in to Ubuntu Server where Mind Studio is located as the Mind Studio installation user, confirm the current DDK version, and set the environment variables  **DDK\_HOME**,  **tools\_version**, and  **LD\_LIBRARY\_PATH**.
    1.  <a name="en-us_topic_0219102918_li61417158198"></a>Query the current DDK version.

        A DDK version can be queried by using either Mind Studio or the DDK software package.

        -   Using Mind Studio

            On the project page of Mind Studio, choose  **File \> Settings \> System Settings \> Ascend DDK**  to query the DDK version.

            **Figure  1**  Querying the DDK version<a name="en-us_topic_0219102918_fig17553193319118"></a>  
            ![](figures/querying-the-ddk-version.png "querying-the-ddk-version")

            The displayed  **DDK Version**  is the current DDK version, for example,  **1.32.0.B080**.

        -   Using the DDK software package

            Obtain the DDK version based on the DDK package name.

            DDK package name format:  **Ascend\_DDK-\{**_software version_**\}-\{**_interface version_**\}-x86\_64.ubuntu16.04.tar.gz**

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
        >-   **_1.32.X.X_**  indicates the DDK version queried in  [a](#en-us_topic_0219102918_li61417158198). Set this parameter based on the query result, for example,  **1.32.0.B080**.  
        >-   If the environment variables have been added, skip this step.  

        Type  **:wq!**  to save settings and exit.

        Run the following command for the environment variable to take effect:

        **source \~/.bashrc**

4.  Convert the source network model to a model supported by the Ascend AI processor.
    -   Convert a model using Mind Studio.
        1.  Choose  **Tools \> Model Convert**  from the main menu of Mind Studio.
        2.  On the  **Model Conversion**  page that is displayed, configure model conversion.
            -   Select the model file downloaded in  [Step 2](#en-us_topic_0219102918_li1365682471610)  for  **Model File**. The weight file is automatically matched and filled in  **Weight File**.
            -   Set  **Model Name**  to the model name in  [Table 1](#en-us_topic_0219102918_table144841813177).
                1.  In the  **AIPP **configuration of the face\_detection model, set  **Input Image Size**  to  **384 **and  **304**, respectively and  **Model Image Format**  to  **BGR888\_U8**. Retain the default values for other parameters.
                2.  AIPP must be disabled on the  **AIPP **configuration page of the face\_emotion model. Retain the default values for other parameters.

        3.  During the conversion, the error information occurs with the face\_detection model, as shown in  [Figure 2](#en-us_topic_0219102918_fig2865313121718).

            **Figure  2**  Model conversion error<a name="en-us_topic_0219102918_fig2865313121718"></a>  
            

            ![](figures/model_facedetection_coversionfailed.png)

            Select  **SSDDetectionOutput**  from the  **Suggestion**  drop-down list box at the  **DetectionOutput**  layer and click  **Retry**.

            After successful conversion, an .om offline model is generated in the  **$HOME/modelzoo/xxx/device**  directory.

            >![](public_sys-resources/icon-note.gif) **NOTE:**   
            >For details about the descriptions of each step and parameters in model conversion, see "Model Conversion" in the  [Mind Studio User Guide](https://ascend.huawei.com/doc/mindstudio/).  


5.  Upload the converted .om model file to the  **faceemotion/script**  directory under the source code path in  [Step 1](#en-us_topic_0219102918_li953280133816).

## Build<a name="en-us_topic_0219102918_section7994174585917"></a>

1.  Open the project.

    Go to the directory that stores the decompressed installation package as the Mind Studio installation user in CLI mode, for example,  **$HOME/MindStudio-ubuntu/bin**. Run the following command to start Mind Studio:

    **./MindStudio.sh**

    Open the  **sample-faceemotion**  project.

2.  Configure project information in the  **src/param\_configure.conf**  file.

    For details, see  [Figure 3](#en-us_topic_0219102918_fig0391184062214).

    **Figure  3**  Configuration file<a name="en-us_topic_0219102918_fig0391184062214"></a>  
    

    ![](figures/en-us_image_0219104978.jpg)

    The default configurations of the configuration file are as follows:

    ```
    remote_host=192.168.1.2
    data_source=Channel-1
    presenter_view_app_name=video
    ```

    -   **remote\_host**: IP address of the Atlas 200 DK developer board
    -   **data\_source**: camera channel. The value can be  **Channel-1**  or  **Channel-2**. For details, see "Viewing the Channel to Which a Camera Belongs" in  [Atlas 200 DK User Guide](https://ascend.huawei.com/doc/Atlas200DK/).
    -   **presenter\_view\_app\_name**: value of  **View Name**  on the  **Presenter Server**  page, which must be unique. The value consists of at least one character and supports only uppercase letters, lowercase letters, digits, and underscores \(\_\).

    >![](public_sys-resources/icon-note.gif) **NOTE:**   
    >-   All the three parameters must be set. Otherwise, the build fails.  
    >-   Do not use double quotation marks \(""\) during parameter settings.  
    >-   Modify the default configurations as required.  

3.  Run the  **deploy.sh**  script to adjust configuration parameters and download and compile the third-party library. Open the  **Terminal**  window of Mind Studio. By default, the home directory of the code is used. Run the  **deploy.sh**  script in the background to deploy the environment, as shown in  [Figure 4](#en-us_topic_0219102918_fig1733142811452).

    **Figure  4**  Running the deploy.sh script<a name="en-us_topic_0219102918_fig1733142811452"></a>  
    ![](figures/running-the-deploy-sh-script.png "running-the-deploy-sh-script")

    >![](public_sys-resources/icon-note.gif) **NOTE:**   
    >-   During the first deployment, if no third-party library is used, the system automatically downloads and builds the third-party library, which may take a long time. The third-party library can be directly used for the subsequent build.  
    >-   During deployment, select the IP address of the host that communicates with the developer board. Generally, the IP address is that configured for the virtual NIC. If the IP address is in the same network segment as the IP address of the developer board, it is automatically selected for deployment. If they are not in the same network segment, you need to manually type the IP address of the host that communicates with the developer board to complete the deployment.  

4.  Start building. Open Mind Studio and choose  **Build \> Build \> Build-Configuration**  from the main menu. The  **build**  and  **run**  folders are generated in the directory.

    >![](public_sys-resources/icon-notice.gif) **NOTICE:**   
    >When you build a project for the first time,  **Build \> Build**  is unavailable. You need to choose  **Build \> Edit Build Configuration**  to set parameters before the build.  

5.  Start Presenter Server.

    Open the  **Terminal**  window of Mind Studio. By default, under the code path, run the following command to start the Presenter Server program of the face emotion application on the server:

    **bash run\_present\_server.sh**

    When the message  **Please choose one to show the presenter in browser\(default: 127.0.0.1\):**  is displayed, type the IP address \(usually IP address for accessing Mind Studio\) used for accessing the Presenter Server service in the browser.

    Select the IP address used by the browser to access the Presenter Server service in  **Current environment valid ip list**, as shown in  [Figure 5](#en-us_topic_0219102918_fig999812514814).

    **Figure  5**  Project deployment<a name="en-us_topic_0219102918_fig999812514814"></a>  
    

    ![](figures/en-us_image_0219105391.jpg)

    [Figure 6](#en-us_topic_0219102918_fig69531305324)  shows that the Presenter Server service has been started successfully.

    **Figure  6**  Starting the Presenter Server process<a name="en-us_topic_0219102918_fig69531305324"></a>  
    

    ![](figures/en-us_image_0219105392.jpg)

    Use the URL shown in the preceding figure to log in to Presenter Server. The IP address is that typed in  [Figure 5](#en-us_topic_0219102918_fig999812514814)  and the default port number is  **7007**. The following figure indicates that Presenter Server has been started successfully.

    **Figure  7**  Home page<a name="en-us_topic_0219102918_fig64391558352"></a>  
    ![](figures/home-page.png "home-page")

    The following figure shows the IP address used by Presenter Server and  Mind Studio  to communicate with the Atlas 200 DK.

    **Figure  8**  IP address example<a name="en-us_topic_0219102918_fig1881532172010"></a>  
    ![](figures/ip-address-example.png "ip-address-example")

    In the preceding figure:

    -   The IP address of the Atlas 200 DK developer board is  **192.168.1.2**  \(connected in USB mode\).
    -   The IP address used by Presenter Server to communicate with the Atlas 200 DK is in the same network segment as the IP address of the Atlas 200 DK on the UI Host server, for example,  **192.168.1.223**.
    -   The following describes how to access the IP address \(such as  **10.10.0.1**\) of Presenter Server using a browser. Because Presenter Server and  Mind Studio  are deployed on the same server, you can access  Mind Studio  through the browser using the same IP address. 


## Run<a name="en-us_topic_0219102918_section551710297235"></a>

1.  Run the face emotion application.

    On the toolbar of Mind Studio, click  **Run**  and choose  **Run \> Run 'sample-faceemotion'**. As shown in  [Figure 9](#en-us_topic_0219102918_fig93931954162719), the executable application is running on the developer board.

    **Figure  9**  Application running sample<a name="en-us_topic_0219102918_fig93931954162719"></a>  
    

    ![](figures/en-us_image_0219105741.jpg)

2.  Use the URL displayed upon the start of the Presenter Server service to log in to Presenter Server.

    Wait for Presenter Agent to transmit data to the server. Click  **Refresh**. When there is data, the icon in the  **Status**  column for the corresponding channel changes to green, as shown in  [Figure 10](#en-us_topic_0219102918_fig113691556202312).

    **Figure  10**  Presenter Server page<a name="en-us_topic_0219102918_fig113691556202312"></a>  
    ![](figures/presenter-server-page.png "presenter-server-page")

    >![](public_sys-resources/icon-note.gif) **NOTE:**   
    >-   For the face emotion application, Presenter Server supports a maximum of 10 channels at the same time \(each  _presenter\_view\_app\_name_  parameter corresponds to a channel\).  
    >-   Due to hardware limitations, each channel supports a maximum frame rate of 20 fps. A lower frame rate is automatically used when the network bandwidth is low.  

3.  Click a link in the  **View Name**  column, for example,  **video**  in the preceding figure, and view the result.

## Follow-up Operations<a name="en-us_topic_0219102918_section177619345260"></a>

-   Stopping the face emotion application

    The face emotion application is running continually after being executed. To stop it, perform the following operation:

    Click the stop button to stop the face emotion application.  [Figure 11](#en-us_topic_0219102918_fig2182182518112)  shows that the face emotion application has been stopped.

    **Figure  11**  Stopped face emotion application<a name="en-us_topic_0219102918_fig2182182518112"></a>  
    

    ![](figures/en-us_image_0219102951.gif)

-   Stopping the Presenter Server service

    The Presenter Server service is always in running state after being started. To stop the Presenter Server service of the face emotion application, perform the following operations:

    On the server with  Mind Studio  installed, run the following command as the  Mind Studio  installation user to check the process of the Presenter Server service corresponding to the face emotion application:

    **ps -ef | grep presenter | grep faceemotion**

    ```
    ascend@ascend-HP-ProDesk-600-G4-PCI-MT:~/sample-faceemotion$ ps -ef | grep presenter | grep faceemotion
     ascend    7701  1615  0 14:21 pts/8    00:00:00 python3 presenterserver/presenter_server.py --app face_emotion
    ```

    In the preceding information,  _7701_  indicates the process ID of the Presenter Server service for the face emotion application.

    To stop the service, run the following command:

    **kill -9** _7701_


