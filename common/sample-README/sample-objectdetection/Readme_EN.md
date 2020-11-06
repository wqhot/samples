English|[中文](Readme.md)

**This case is only used for learning. It is not responsible for the effect and does not support commercial use.**

# Faster R-CNN Detection Network Application<a name="EN-US_TOPIC_0232633467"></a>

This application can run on the Atlas 200 DK or the AI acceleration cloud server to implement the inference function by using Faster R-CNN object detection network.

The applications in the current version branch adapt to  [DDK&RunTime](https://ascend.huawei.com/resources) **1.32.0.0 and later**.

## Prerequisites<a name="en-us_topic_0203223280_section137245294533"></a>

Before deploying this sample, ensure that:

-   Mind Studio  has been installed.
-   The Atlas 200 DK developer board has been connected to  Mind Studio, the cross compiler has been installed, the SD card has been prepared, and basic information has been configured.

## Software Preparation<a name="en-us_topic_0203223280_section181111827718"></a>

Before running the sample, obtain the source code package and configure the environment as follows:

1.  <a name="en-us_topic_0203223280_li953280133816"></a>Obtain the source code package.
    1.  By downloading the package

        Download the code in the  [https://gitee.com/Atlas200DK/sample-objectdetection/tree/1.3x.0.0/](https://gitee.com/Atlas200DK/sample-objectdetection/tree/1.3x.0.0/)  repository to any directory on the Ubuntu server where Mind Studio is located as the Mind Studio installation user. The two files must be stored in the same directory. For example, the code can be stored in  **$HOME/AscendProjects/sample-objectdetection**.

    2.  By running the  **git**  command

        Run the following command in the  **$HOME/AscendProjects**  directory to download code:

        **git clone https://gitee.com/Atlas200DK/sample-objectdetection.git --branch 1.3x.0.0**

2.  <a name="en-us_topic_0203223280_li2074865610364"></a>Obtain the source network model required by the application.

    Obtain the source network model and its weight file used in the application by referring to  [Table 1](#en-us_topic_0203223280_table19942111763710)  and save them to the same directory on Ubuntu Server where  Mind Studio  is located, for example,  **$HOME/models/faster\_rcnn**.

    **Table  1**  Models used in the detection network application

    <a name="en-us_topic_0203223280_table19942111763710"></a>
    <table><thead align="left"><tr id="en-us_topic_0203223280_row611318123710"><th class="cellrowborder" valign="top" width="23%" id="mcps1.2.4.1.1"><p id="en-us_topic_0203223280_p81141820376"><a name="en-us_topic_0203223280_p81141820376"></a><a name="en-us_topic_0203223280_p81141820376"></a>Model Name</p>
    </th>
    <th class="cellrowborder" valign="top" width="22%" id="mcps1.2.4.1.2"><p id="en-us_topic_0203223280_p13181823711"><a name="en-us_topic_0203223280_p13181823711"></a><a name="en-us_topic_0203223280_p13181823711"></a>Description</p>
    </th>
    <th class="cellrowborder" valign="top" width="55.00000000000001%" id="mcps1.2.4.1.3"><p id="en-us_topic_0203223280_p1717182378"><a name="en-us_topic_0203223280_p1717182378"></a><a name="en-us_topic_0203223280_p1717182378"></a>Download Path</p>
    </th>
    </tr>
    </thead>
    <tbody><tr id="en-us_topic_0203223280_row1119187377"><td class="cellrowborder" valign="top" width="23%" headers="mcps1.2.4.1.1 "><p id="en-us_topic_0203223280_p7118189378"><a name="en-us_topic_0203223280_p7118189378"></a><a name="en-us_topic_0203223280_p7118189378"></a>faster_rcnn</p>
    </td>
    <td class="cellrowborder" valign="top" width="22%" headers="mcps1.2.4.1.2 "><p id="en-us_topic_0203223280_p151818183718"><a name="en-us_topic_0203223280_p151818183718"></a><a name="en-us_topic_0203223280_p151818183718"></a>Network model for object detection.</p>
    <p id="en-us_topic_0203223280_p11121816373"><a name="en-us_topic_0203223280_p11121816373"></a><a name="en-us_topic_0203223280_p11121816373"></a>It is a Faster R-CNN model based on Caffe.</p>
    </td>
    <td class="cellrowborder" valign="top" width="55.00000000000001%" headers="mcps1.2.4.1.3 "><p id="en-us_topic_0203223280_p611318163718"><a name="en-us_topic_0203223280_p611318163718"></a><a name="en-us_topic_0203223280_p611318163718"></a>Download the source network model file and its weight file by referring to<strong id="en-us_topic_0203223280_b92198409144"><a name="en-us_topic_0203223280_b92198409144"></a><a name="en-us_topic_0203223280_b92198409144"></a> README.md</strong> at <a href="https://gitee.com/HuaweiAscend/models/tree/master/computer_vision/object_detect/faster_rcnn" target="_blank" rel="noopener noreferrer">https://gitee.com/HuaweiAscend/models/tree/master/computer_vision/object_detect/faster_rcnn</a>.</p>
    </td>
    </tr>
    </tbody>
    </table>

3.  Log in to Ubuntu Server where Mind Studio is located as the Mind Studio installation user, confirm the current DDK version, and set the environment variables  **DDK\_HOME**,  **tools\_version**, and  **LD\_LIBRARY\_PATH**.
    1.  <a name="en-us_topic_0203223280_en-us_topic_0203223294_li61417158198"></a>Query the current DDK version.

        A DDK version can be queried by using either Mind Studio or the DDK software package.

        -   Using Mind Studio

            On the project page of Mind Studio, choose  **File \> Settings \> System Settings \> Ascend DDK**  to query the DDK version.

            **Figure  1**  Querying the DDK version<a name="en-us_topic_0203223280_en-us_topic_0203223294_fig17553193319118"></a>  
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
        >-   **_1.32.X.X_**  indicates the DDK version queried in  [a](#en-us_topic_0203223280_en-us_topic_0203223294_li61417158198). Set this parameter based on the query result, for example,  **1.32.0.B080**.  
        >-   If the environment variables have been added, skip this step.  

        Type  **:wq!**  to save settings and exit.

        Run the following command for the environment variable to take effect:

        **source \~/.bashrc**

4.  Convert the source network model to a model supported by the Ascend AI processor.
    1.  Choose  **Tools \> Model Convert**  from the main menu of  Mind Studio.
    2.  On the  **Model Conversion**  page that is displayed, configure model conversion.
        -   Select the model file downloaded in  [Step 2](#en-us_topic_0203223280_li2074865610364)  for  **Model File**. The weight file is automatically matched and filled in  **Weight File**.
        -   Set  **Model Name**  to the model name  **faster\_rcnn**  in  [Table 1](#en-us_topic_0203223280_table19942111763710).

            ![](figures/en-us_image_0208249689.png)

        -   In the  **Nodes**  configuration, retain the default value for  **Input Node:data**. For  **Input Node:im\_info**, type  **1**  and  **3**  in sequence.

            ![](figures/en-us_image_0208252722.png)

        -   In the  **AIPP**  configuration, set  **Input Image Size**  to  **896**  and  **608**, respectively. The values must be 128 x 16 aligned. Set  **Model Image Format**  to  **BGR888\_U8**  and use the default values for other parameters.

            ![](figures/en-us_image_0208252809.png)

    3.  Click  **Finish**  to start model conversion.

        After successful conversion, an .om offline model is generated in the  **$HOME/modelzoo/faster\_rcnn/device**  directory.

5.  Upload the converted .om model file to the  **sample\_objectdetection/script**  directory under the source code path in  [Step 1](#en-us_topic_0203223280_li953280133816).

## Build<a name="en-us_topic_0203223280_section3723145213347"></a>

1.  Open the project.

    Go to the directory that stores the decompressed installation package as the Mind Studio installation user in CLI mode, for example,  **$HOME/MindStudio-ubuntu/bin**. Run the following command to start Mind Studio:

    **./MindStudio.sh**

    Open the  **sample\_objectdetection**  project, as shown in  [Figure 2](#en-us_topic_0203223280_fig05481157171918).

    **Figure  2**  Opening the objectdetection project<a name="en-us_topic_0203223280_fig05481157171918"></a>  
    

    ![](figures/en-us_image_0208253269.png)

2.  Configure project information in the  **src/param\_configure.conf**  file.

    **Figure  3**  Configuration file path<a name="en-us_topic_0203223280_fig0391184062214"></a>  
    ![](figures/configuration-file-path.png "configuration-file-path")

    The default configurations of the configuration file are as follows:

    ```
    remote_host=192.168.1.2
    ```

    **remote\_host**: IP address of the Atlas 200 DK developer board

    >![](public_sys-resources/icon-note.gif) **NOTE:**   
    >-   Do not use double quotation marks \(""\) during parameter settings.  
    >-   Modify the default configurations as required.  

3.  Run the  **deploy.sh**  script to adjust configuration parameters and download and compile the third-party library. Open the  **Terminal**  window of Mind Studio. By default, the home directory of the code is used. Run the  **deploy.sh**  script in the background to deploy the environment, as shown in  [Figure 4](#en-us_topic_0203223280_fig1224920422716).

    **Figure  4**  Running the deploy.sh script<a name="en-us_topic_0203223280_fig1224920422716"></a>  
    ![](figures/running-the-deploy-sh-script.png "running-the-deploy-sh-script")

    >![](public_sys-resources/icon-note.gif) **NOTE:**   
    >-   During the first deployment, if no third-party library is used, the system automatically downloads and builds the third-party library, which may take a long time. The third-party library can be directly used for the subsequent build.  
    >-   During deployment, select the IP address of the host that communicates with the developer board. Generally, the IP address is the IP address configured for the virtual NIC. If the IP address is in the same network segment as the IP address of the developer board, it is automatically selected for deployment. If they are not in the same network segment, you need to manually type the IP address of the host that communicates with the Atlas DK to complete the deployment.  

4.  Start building. Open Mind Studio and choose  **Build \> Build \> Build-Configuration**  from the main menu. The  **build**  and  **run**  folders are generated in the directory, as shown in  [Figure 5](#en-us_topic_0203223280_fig19291111318376).

    **Figure  5**  Build and file generation<a name="en-us_topic_0203223280_fig19291111318376"></a>  
    ![](figures/build-and-file-generation.png "build-and-file-generation")

    Notes:

    When you build a project for the first time,  **Build \> Build**  is unavailable. You need to choose  **Build \> Edit Build Configuration**  to set parameters before the build.

    ![](figures/build_configuration.png)

5.  Upload the images to be inferred to any directory of the  **HwHiAiUser**  user on the host side.

    The image requirements are as follows:

    -   Format: jpg, png, and bmp
    -   Width of the input image: an integer ranging from 16px to 4096px
    -   Height of the input image: an integer ranging from 16px to 4096px


## Run<a name="en-us_topic_0203223280_section1620073406"></a>

1.  On the toolbar of Mind Studio, click  **Run**  and choose  **Run \> Run 'sample-objectdetection'**. As shown in  [Figure 6](#en-us_topic_0203223280_fig18918132273612), the executable application is running on the developer board.

    **Figure  6**  Running application<a name="en-us_topic_0203223280_fig18918132273612"></a>  
    ![](figures/running-application.png "running-application")

    You can ignore the error information reported during the execution because Mind Studio cannot transfer parameters for an executable application. In the preceding steps, the executable application and dependent library files are deployed to the developer board. You need to log in to the developer board in SSH mode and manually execute the files in the corresponding directory. For details, see the following steps.

2.  Log in to the host side as the  **HwHiAiUser**  user in SSH mode on Ubuntu Server where  Mind Studio  is located.

    **ssh HwHiAiUser@**_host\_ip_

    For the Atlas 200 DK, the default value of  _**host\_ip**_  is  **192.168.1.2**  \(USB connection mode\) or  **192.168.0.2**  \(NIC connection mode\).

3.  Go to the path of the executable file of Faster R-CNN detection application.

    Command example:

    **cd \~/HIAI\_PROJECTS/workspace\_mind\_studio/sample\_objectdetection\__XXXXX_/out**

    >![](public_sys-resources/icon-note.gif) **NOTE:**   
    >-   In this path,  _**xxxxx **_in** sample\_objectdetection\__xxxxx_**  is a combination of letters and digits generated randomly each time the application is built.  

4.  Run the application.

    Run the  **run\_object\_detection\_faster\_rcnn.py**  script to save the images which are generated by inference to the specified path.

    Command example:

    **python3 run\_object\_detection\_faster\_rcnn.py -w  _800_  -h  _600_  -i  _./example.jpg_  -o  _./out_  -c  _21_**

    -   **-w/model\_width**: width of the input image of a model. The value is an integer ranging from 16 to 4096.
    -   **-h/model\_height**: height of the input image of a model. The value is an integer ranging from 16 to 4096.
    -   **-i/input\_path**: directory or path of the input image. You can enter multiple paths.
    -   **-o/output\_path**: directory for storing the output image. The default setting is the current directory.
    -   **-c/output\_categories**: number of Faster R-CNN detection categories \(including the background\). The value is an integer ranging from 2 to 32. The default value is  **21**.

5.  For other parameters, run the  **python3 run\_object\_detection\_faster\_rcnn.py --help**  command. For details, see the help information.

- 这里是列表文本