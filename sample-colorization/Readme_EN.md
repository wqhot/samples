English|[中文](Readme.md)

**This case is only used for learning. It is not responsible for the effect and does not support commercial use.**

# Black and White Image Colorization<a name="EN-US_TOPIC_0232649438"></a>

This application runs on the Atlas 200 DK to automatically color black and white images.

The applications in the current version branch adapt to  [DDK&RunTime](https://ascend.huawei.com/resources) **1.32.0.0 and later**.

## Prerequisites<a name="en-us_topic_0228461725_section137245294533"></a>

Before deploying this sample, ensure that:

-   Mind Studio  has been installed.
-   The Atlas 200 DK developer board has been connected to  Mind Studio, the cross compiler has been installed, the SD card has been prepared, and basic information has been configured.

## Deployment<a name="en-us_topic_0228461725_section412811285117"></a>

You can use either of the following methods:

1.  Quick deployment: visit  [https://gitee.com/ascend/samples/tree/1.32.0.0/common/faster-deploy](https://gitee.com/ascend/samples/tree/1.32.0.0/common/faster-deploy).

    >![](public_sys-resources/icon-note.gif) **NOTE:**   
    >-   The quick deployment script can be used to deploy multiple samples rapidly. Select  **colorization**.  
    >-   The quick deployment script automatically completes code download, model conversion, and environment variable configuration. To learn about the detailed deployment process, go to  [2. Common deployment](#en-us_topic_0228461725_li3208251440).  

2.  <a name="en-us_topic_0228461725_li3208251440"></a>Common deployment: visit  [https://gitee.com/ascend/samples/tree/1.32.0.0/common/sample-README/sample-colorization](https://gitee.com/ascend/samples/tree/1.32.0.0/common/sample-README/sample-colorization).

    >![](public_sys-resources/icon-note.gif) **NOTE:**   
    >-   In this deployment mode, you need to manually download code, convert models, and configure environment variables.  


## Build<a name="en-us_topic_0228461725_section3723145213347"></a>

1.  Open the project.

    Go to the directory that stores the decompressed installation package as the Mind Studio installation user in CLI mode, for example,  **$HOME/MindStudio-ubuntu/bin**. Run the following command to start Mind Studio:

    **./MindStudio.sh**

    Open the  **sample\_colorization**  project, as shown in  [Figure 1](#en-us_topic_0228461725_en-us_topic_0219108795_fig05481157171918).

    **Figure  1**  Opening the sample\_colorization project<a name="en-us_topic_0228461725_en-us_topic_0219108795_fig05481157171918"></a>  
    

    ![](figures/en-us_image_0219108999.png)

2.  Configure project information in the  **src/param\_configure.conf**  file.

    **Figure  2**  Configuration file path<a name="en-us_topic_0228461725_en-us_topic_0219108795_fig0391184062214"></a>  
    ![](figures/configuration-file-path.png "configuration-file-path")

    The default configurations of the configuration file are as follows:

    ```
    remote_host=192.168.1.2
    ```

    **remote\_host**: IP address of the Atlas 200 DK developer board

    >![](public_sys-resources/icon-note.gif) **NOTE:**   
    >-   Do not use double quotation marks \(""\) during parameter settings.  
    >-   Modify the default configurations as required.  

3.  Run the  **deploy.sh**  script to adjust configuration parameters and download and compile the third-party library. Open the  **Terminal**  window of Mind Studio. By default, the home directory of the code is used. Run the  **deploy.sh**  script in the background to deploy the environment, as shown in  [Figure 3](#en-us_topic_0228461725_en-us_topic_0219108795_fig63536151461).

    **Figure  3**  Running the deploy.sh script<a name="en-us_topic_0228461725_en-us_topic_0219108795_fig63536151461"></a>  
    ![](figures/running-the-deploy-sh-script.png "running-the-deploy-sh-script")

    >![](public_sys-resources/icon-note.gif) **NOTE:**   
    >-   During the first deployment, if no third-party library is used, the system automatically downloads and builds the third-party library, which may take a long time. The third-party library can be directly used for the subsequent build.  
    >-   During deployment, select the IP address of the host that communicates with the developer board. Generally, the IP address is the IP address configured for the virtual NIC. If the IP address is in the same network segment as the IP address of the developer board, it is automatically selected for deployment. If they are not in the same network segment, you need to manually type the IP address of the host that communicates with the Atlas DK to complete the deployment.  

4.  Start building. Open Mind Studio and choose  **Build \> Build \> Build-Configuration**  from the main menu. The  **build**  and  **run**  folders are generated in the directory.

    >![](public_sys-resources/icon-notice.gif) **NOTICE:**   
    >When you build a project for the first time,  **Build \> Build**  is unavailable. You need to choose  **Build \> Edit Build Configuration**  to set parameters before the build.  

5.  Upload the images to be colored to any directory of the  **HwHiAiUser**  user on the host side.

## Run<a name="en-us_topic_0228461725_section1620073406"></a>

1.  On the toolbar of Mind Studio, click  **Run**  and choose  **Run \> Run 'sample-colorization'**. As shown in  [Figure 4](#en-us_topic_0228461725_en-us_topic_0219108795_fig18918132273612), the executable application is running on the developer board.

    **Figure  4**  Running application<a name="en-us_topic_0228461725_en-us_topic_0219108795_fig18918132273612"></a>  
    ![](figures/running-application.png "running-application")

    You can ignore the error information reported during the execution because Mind Studio cannot transfer parameters for an executable application. In the preceding steps, the executable application and dependent library files are deployed to the developer board. You need to log in to the developer board in SSH mode and manually execute the files in the corresponding directory. For details, see the following steps.

2.  Log in to the host side as the  **HwHiAiUser**  user in SSH mode on Ubuntu Server where  Mind Studio  is located.

    **ssh HwHiAiUser@**_host\_ip_

    For the Atlas 200 DK, the default value of  _**host\_ip**_  is  **192.168.1.2**  \(USB connection mode\) or  **192.168.0.2**  \(NIC connection mode\).

3.  Go to the path of the executable file of the black and white image colorization application.

    Command example:

    **cd \~/HIAI\_PROJECTS/workspace\_mind\_studio/sample-colorization\__xxxxx_/out**

    >![](public_sys-resources/icon-note.gif) **NOTE:**   
    >-   In this path,  _**xxxxx **_in** sample-colorization\__xxxxx_**  is a combination of letters and digits generated randomly each time the application is built.  

4.  Run the application.

    Run the  **run\_colorization.py**  script to save the images which are generated by inference to the specified path.

    Command example:

    **python3 run\_colorization.py -i \~/example.jpg -o ./out/**

    -   **-i**: path of the input image. The value can be a directory, indicating that all images in the current directory are used as input. The value can also be used to specify an image.
    -   **-o**: path for storing the colored images.

