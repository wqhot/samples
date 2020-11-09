English|[中文](Readme.md)

**This case is only used for learning. It is not responsible for the effect and does not support commercial use.**

# People Detection<a name="EN-US_TOPIC_0232630318"></a>

Developers can deploy the application on the Atlas 200 DK or the AI acceleration cloud server to decode the local MP4 file or RTSP video streams, detect pedestrians, and human faces in video frames, predict their attributes, generate structured information, and send the structured information to the server for storage and display.

The applications in the current version branch adapt to  [DDK&RunTime](https://ascend.huawei.com/resources) **1.32.0.0 and later**.

## Prerequisites<a name="en-us_topic_0203223281_section137245294533"></a>

Before deploying this sample, ensure that:

-   Mind Studio  has been installed.
-   The Atlas 200 DK developer board has been connected to  Mind Studio, the cross compiler has been installed, the SD card has been prepared, and basic information has been configured.

## Software Preparation<a name="en-us_topic_0203223281_section8534138124114"></a>

Before running the sample, obtain the source code package and configure the environment as follows:

1.  <a name="en-us_topic_0203223281_li953280133816"></a>Obtain the source code package.
    1.  By downloading the package

        Download all the code in the repository at  [https://gitee.com/ascend/samples/tree/1.32.0.0/sample-videoanalysisperson/](https://gitee.com/ascend/samples/tree/1.32.0.0/sample-videoanalysisperson/)  to any directory on Ubuntu Server where Mind Studio is located as the Mind Studio installation user, for example,  _$HOME/AscendProjects/sample-videoanalysisperson_.

    2.  By running the  **git**  command

        Run the following command in the  **$HOME/AscendProjects**  directory to download code:

        **git clone -b 1.32.0.0 https://gitee.com/ascend/samples.git**
        
        **mv samples/common/sample-README/sample-videoanalysisperson ./**
        
2.  <a name="en-us_topic_0203223281_li5507119145914"></a>Obtain the source network model required by the application.

    Obtain the source network model and its weight file used in the application by referring to  [Table 1](#en-us_topic_0203223281_table1193115345597)  and save them to the same directory on Ubuntu Server where  Mind Studio  is located, for example,  **$HOME/models/videoanalysispersion**.

    **Table  1**  Models used in the people detection application

    <a name="en-us_topic_0203223281_table1193115345597"></a>
    <table><thead align="left"><tr id="en-us_topic_0203223281_row1187103505916"><th class="cellrowborder" valign="top" width="20.202020202020204%" id="mcps1.2.4.1.1"><p id="en-us_topic_0203223281_p887235105910"><a name="en-us_topic_0203223281_p887235105910"></a><a name="en-us_topic_0203223281_p887235105910"></a>Model Name</p>
    </th>
    <th class="cellrowborder" valign="top" width="24.242424242424242%" id="mcps1.2.4.1.2"><p id="en-us_topic_0203223281_p16877355598"><a name="en-us_topic_0203223281_p16877355598"></a><a name="en-us_topic_0203223281_p16877355598"></a>Description</p>
    </th>
    <th class="cellrowborder" valign="top" width="55.55555555555556%" id="mcps1.2.4.1.3"><p id="en-us_topic_0203223281_p18713511598"><a name="en-us_topic_0203223281_p18713511598"></a><a name="en-us_topic_0203223281_p18713511598"></a>Download Path</p>
    </th>
    </tr>
    </thead>
    <tbody><tr id="en-us_topic_0203223281_row3881635175910"><td class="cellrowborder" valign="top" width="20.202020202020204%" headers="mcps1.2.4.1.1 "><p id="en-us_topic_0203223281_p48863512592"><a name="en-us_topic_0203223281_p48863512592"></a><a name="en-us_topic_0203223281_p48863512592"></a>face_detection</p>
    </td>
    <td class="cellrowborder" valign="top" width="24.242424242424242%" headers="mcps1.2.4.1.2 "><p id="en-us_topic_0203223281_p688163513595"><a name="en-us_topic_0203223281_p688163513595"></a><a name="en-us_topic_0203223281_p688163513595"></a>Network model for face detection.</p>
    <p id="en-us_topic_0203223281_p1488735175914"><a name="en-us_topic_0203223281_p1488735175914"></a><a name="en-us_topic_0203223281_p1488735175914"></a>It is converted from the Caffe-based ResNet10-SSD300 model.</p>
    </td>
    <td class="cellrowborder" valign="top" width="55.55555555555556%" headers="mcps1.2.4.1.3 "><p id="en-us_topic_0203223281_p1588203519592"><a name="en-us_topic_0203223281_p1588203519592"></a><a name="en-us_topic_0203223281_p1588203519592"></a>Download the source network model file and its weight file by referring to<strong id="en-us_topic_0203223281_b1979216239548"><a name="en-us_topic_0203223281_b1979216239548"></a><a name="en-us_topic_0203223281_b1979216239548"></a> README.md</strong> at <a href="https://gitee.com/HuaweiAscend/models/tree/master/computer_vision/object_detect/face_detection" target="_blank" rel="noopener noreferrer">https://gitee.com/HuaweiAscend/models/tree/master/computer_vision/object_detect/face_detection</a>.</p>
    </td>
    </tr>
    <tr id="en-us_topic_0203223281_row98823585915"><td class="cellrowborder" valign="top" width="20.202020202020204%" headers="mcps1.2.4.1.1 "><p id="en-us_topic_0203223281_p1188103555919"><a name="en-us_topic_0203223281_p1188103555919"></a><a name="en-us_topic_0203223281_p1188103555919"></a>pedestrian</p>
    </td>
    <td class="cellrowborder" valign="top" width="24.242424242424242%" headers="mcps1.2.4.1.2 "><p id="en-us_topic_0203223281_p18889356598"><a name="en-us_topic_0203223281_p18889356598"></a><a name="en-us_topic_0203223281_p18889356598"></a>Network model for performing inference on human body features.</p>
    <p id="en-us_topic_0203223281_p48853545911"><a name="en-us_topic_0203223281_p48853545911"></a><a name="en-us_topic_0203223281_p48853545911"></a>It is a VeSPA model based on Caffe.</p>
    </td>
    <td class="cellrowborder" valign="top" width="55.55555555555556%" headers="mcps1.2.4.1.3 "><p id="en-us_topic_0203223281_p5881335145918"><a name="en-us_topic_0203223281_p5881335145918"></a><a name="en-us_topic_0203223281_p5881335145918"></a>Download the source network model file and its weight file by referring to<strong id="en-us_topic_0203223281_b8437103118543"><a name="en-us_topic_0203223281_b8437103118543"></a><a name="en-us_topic_0203223281_b8437103118543"></a> README.md</strong> at <a href="https://gitee.com/HuaweiAscend/models/tree/master/computer_vision/classification/pedestrian" target="_blank" rel="noopener noreferrer">https://gitee.com/HuaweiAscend/models/tree/master/computer_vision/classification/pedestrian</a>.</p>
    </td>
    </tr>
    <tr id="en-us_topic_0203223281_row388153512593"><td class="cellrowborder" valign="top" width="20.202020202020204%" headers="mcps1.2.4.1.1 "><p id="en-us_topic_0203223281_p188811350596"><a name="en-us_topic_0203223281_p188811350596"></a><a name="en-us_topic_0203223281_p188811350596"></a>inception_age</p>
    </td>
    <td class="cellrowborder" valign="top" width="24.242424242424242%" headers="mcps1.2.4.1.2 "><p id="en-us_topic_0203223281_p138803555914"><a name="en-us_topic_0203223281_p138803555914"></a><a name="en-us_topic_0203223281_p138803555914"></a>Network model for identifying the age.</p>
    <p id="en-us_topic_0203223281_p2882351595"><a name="en-us_topic_0203223281_p2882351595"></a><a name="en-us_topic_0203223281_p2882351595"></a>It is an Inception V3 model based on TensorFlow.</p>
    </td>
    <td class="cellrowborder" valign="top" width="55.55555555555556%" headers="mcps1.2.4.1.3 "><p id="en-us_topic_0203223281_p78813518594"><a name="en-us_topic_0203223281_p78813518594"></a><a name="en-us_topic_0203223281_p78813518594"></a>Download the PB model file of the source network by referring to <strong id="en-us_topic_0203223281_b12692191171114"><a name="en-us_topic_0203223281_b12692191171114"></a><a name="en-us_topic_0203223281_b12692191171114"></a>README.md</strong> at <a href="https://gitee.com/HuaweiAscend/models/tree/master/computer_vision/classification/inception_age" target="_blank" rel="noopener noreferrer">https://gitee.com/HuaweiAscend/models/tree/master/computer_vision/classification/inception_age</a>.</p>
    </td>
    </tr>
    <tr id="en-us_topic_0203223281_row1788163525912"><td class="cellrowborder" valign="top" width="20.202020202020204%" headers="mcps1.2.4.1.1 "><p id="en-us_topic_0203223281_p1788123518593"><a name="en-us_topic_0203223281_p1788123518593"></a><a name="en-us_topic_0203223281_p1788123518593"></a>inception_gender</p>
    </td>
    <td class="cellrowborder" valign="top" width="24.242424242424242%" headers="mcps1.2.4.1.2 "><p id="en-us_topic_0203223281_p10884353596"><a name="en-us_topic_0203223281_p10884353596"></a><a name="en-us_topic_0203223281_p10884353596"></a>Network model for identifying the gender.</p>
    <p id="en-us_topic_0203223281_p1388133595913"><a name="en-us_topic_0203223281_p1388133595913"></a><a name="en-us_topic_0203223281_p1388133595913"></a>It is an Inception V3 model based on TensorFlow.</p>
    </td>
    <td class="cellrowborder" valign="top" width="55.55555555555556%" headers="mcps1.2.4.1.3 "><p id="en-us_topic_0203223281_p1988103514599"><a name="en-us_topic_0203223281_p1988103514599"></a><a name="en-us_topic_0203223281_p1988103514599"></a>Download the PB model file of the source network by referring to <strong id="en-us_topic_0203223281_b0819154417137"><a name="en-us_topic_0203223281_b0819154417137"></a><a name="en-us_topic_0203223281_b0819154417137"></a>README.md</strong> at <a href="https://gitee.com/HuaweiAscend/models/tree/master/computer_vision/classification/inception_gender" target="_blank" rel="noopener noreferrer">https://gitee.com/HuaweiAscend/models/tree/master/computer_vision/classification/inception_gender</a>.</p>
    </td>
    </tr>
    <tr id="en-us_topic_0203223281_row19881135115914"><td class="cellrowborder" valign="top" width="20.202020202020204%" headers="mcps1.2.4.1.1 "><p id="en-us_topic_0203223281_p13881355593"><a name="en-us_topic_0203223281_p13881355593"></a><a name="en-us_topic_0203223281_p13881355593"></a>vgg_ssd</p>
    </td>
    <td class="cellrowborder" valign="top" width="24.242424242424242%" headers="mcps1.2.4.1.2 "><p id="en-us_topic_0203223281_p128819351596"><a name="en-us_topic_0203223281_p128819351596"></a><a name="en-us_topic_0203223281_p128819351596"></a>Network model for object detection.</p>
    <p id="en-us_topic_0203223281_p588153519599"><a name="en-us_topic_0203223281_p588153519599"></a><a name="en-us_topic_0203223281_p588153519599"></a>It is an SSD512 model based on Caffe.</p>
    <p id="en-us_topic_0203223281_p158813355590"><a name="en-us_topic_0203223281_p158813355590"></a><a name="en-us_topic_0203223281_p158813355590"></a></p>
    </td>
    <td class="cellrowborder" valign="top" width="55.55555555555556%" headers="mcps1.2.4.1.3 "><p id="en-us_topic_0203223281_p588183595913"><a name="en-us_topic_0203223281_p588183595913"></a><a name="en-us_topic_0203223281_p588183595913"></a>Download the source network model file and its weight file by referring to<strong id="en-us_topic_0203223281_b7786133617327"><a name="en-us_topic_0203223281_b7786133617327"></a><a name="en-us_topic_0203223281_b7786133617327"></a> README.md</strong> at <a href="https://gitee.com/HuaweiAscend/models/tree/master/computer_vision/object_detect/vgg_ssd" target="_blank" rel="noopener noreferrer">https://gitee.com/HuaweiAscend/models/tree/master/computer_vision/object_detect/vgg_ssd</a>.</p>
    </td>
    </tr>
    </tbody>
    </table>

3.  Log in to Ubuntu Server where Mind Studio is located as the Mind Studio installation user, confirm the current DDK version, and set the environment variables  **DDK\_HOME**,  **tools\_version**, and  **LD\_LIBRARY\_PATH**.
    1.  <a name="en-us_topic_0203223281_en-us_topic_0203223294_li61417158198"></a>Query the current DDK version.

        A DDK version can be queried by using either Mind Studio or the DDK software package.

        -   Using Mind Studio

            On the project page of Mind Studio, choose  **File \> Settings \> System Settings \> Ascend DDK**  to query the DDK version.

            **Figure  1**  Querying the DDK version<a name="en-us_topic_0203223281_en-us_topic_0203223294_fig17553193319118"></a>  
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
        >-   **_1.32.X.X_**  indicates the DDK version queried in  [a](#en-us_topic_0203223281_en-us_topic_0203223294_li61417158198). Set this parameter based on the query result, for example,  **1.32.0.B080**.  
        >-   If the environment variables have been added, skip this step.  

        Type  **:wq!**  to save settings and exit.

        Run the following command for the environment variable to take effect:

        **source \~/.bashrc**

4.  Convert the source network model to a model supported by the Ascend AI processor. A model can be converted either using Mind Studio or in CLI mode.
    -   Convert a model using Mind Studio.
        1.  Choose  **Tools \> Model Convert**  from the main menu of  Mind Studio.
        2.  On the  **Model Conversion**  page that is displayed, configure model conversion.
            -   Select the model file downloaded in  [Step 2](#en-us_topic_0203223281_li5507119145914)  for  **Model File**. The weight file is automatically matched and filled in  **Weight File**.
            -   Set  **Model Name**  to the model name in  [Table 1](#en-us_topic_0203223281_table1193115345597).
            -   During TensorFlow model conversion, you need to manually type the value of  **N**  for the input shape. Retain the default values for  **W**,  **H**, and  **C**.
            -   In the  **AIPP**  configuration of the pedestrian model, set  **Input Image Size**  to  **256**  and  **240**, respectively. In this sample, the value must be 128 x 16 aligned. Set  **Model Image Format**  to  **BGR888\_U8**.

                **Figure  2**  AIPP configuration for pedestrian model conversion<a name="en-us_topic_0203223281_fig15011753113814"></a>  
                ![](figures/aipp-configuration-for-pedestrian-model-conversion.png "aipp-configuration-for-pedestrian-model-conversion")

            -   Set the following parameters for inception\_age model conversion:
                -   The age\_inference model processes 10 images at a time. Therefore, you need to change  **N**  in the  **Nodes**  configuration to  **10**  during conversion.

                    **Figure  3**  Nodes configuration for inception\_age model conversion<a name="en-us_topic_0203223281_fig1336219448573"></a>  
                    ![](figures/nodes-configuration-for-inception_age-model-conversion.png "nodes-configuration-for-inception_age-model-conversion")

                -   In the  **AIPP**  configuration, set  **Input Image Size**  to  **256**  and  **240**, respectively. In this sample, the value must be 128 x 16 aligned. Set  **Model Image Format**  to  **BGR888\_U8**.

                    **Figure  4**  AIPP configuration for inception\_age model conversion<a name="en-us_topic_0203223281_fig334910264011"></a>  
                    ![](figures/aipp-configuration-for-inception_age-model-conversion.png "aipp-configuration-for-inception_age-model-conversion")

            -   Set the following parameters for inception\_gender model conversion:
                -   The gender\_inference model processes 10 images at a time. Therefore, you need to change  **N**  in the  **Nodes**  configuration to  **10**  during conversion.

                    **Figure  5**  Nodes configuration for inception\_gender model conversion<a name="en-us_topic_0203223281_fig1136210442579"></a>  
                    ![](figures/nodes-configuration-for-inception_gender-model-conversion.png "nodes-configuration-for-inception_gender-model-conversion")

                -   In the  **AIPP**  configuration, set  **Input Image Size**  to  **256**  and  **240**, respectively. In this sample, the value must be 128 x 16 aligned. Set  **Model Image Format**  to  **BGR888\_U8**.

                    ![](figures/en-us_image_0208265214.png)

            -   In the  **AIPP**  configuration of the face\_detection model, set  **Input Image Size**  to  **384**  and  **304**, respectively. In this sample, the value must be 128 x 16 aligned. Set  **Model Image Format**  to  **BGR888\_U8**.

                **Figure  6**  Parameter settings for face\_detection model conversion<a name="en-us_topic_0203223281_fig1336214415715"></a>  
                ![](figures/parameter-settings-for-face_detection-model-conversion.png "parameter-settings-for-face_detection-model-conversion")

                >![](public_sys-resources/icon-note.gif) **NOTE:**   
                >Unless otherwise specified, use the default values for other parameters.  


        3.  Click  **OK**  to start model conversion.

            During the conversion of the face\_detection and vgg\_ssd models, the following error will be reported.

            **Figure  7**  Model conversion error<a name="en-us_topic_0203223281_fig138681281084"></a>  
            ![](figures/model-conversion-error.png "model-conversion-error")

            Select  **SSDDetectionOutput**  from the  **Suggestion**  drop-down list box at the  **DetectionOutput**  layer and click  **Retry**.

            After successful conversion, an .om offline model is generated in the  **$HOME/modelzoo/XXX/device**  directory.

            >![](public_sys-resources/icon-note.gif) **NOTE:**   
            >-   For details about the descriptions of each step and parameters in model conversion, see "Model Conversion" in the  [Mind Studio User Guide](https://ascend.huawei.com/doc/mindstudio/).  
            >-   **XXX**  indicates the name of the model to be converted. For example,  **face\_detection.om**  is stored in  **$HOME/modelzoo/face\_detection/device**.  


    -   Convert a model in CLI mode.
        1.  Go to the folder for storing the original model as the Mind Studio installation user.

            **cd $HOME/models/videoanalysisperson**

        2.  Run the following command to convert the Caffe model using OMG:

            ```
            ${DDK_HOME}/uihost/bin/omg --output="./XXX" --model="./XXX.prototxt" --framework=0 --ddk_version=${tools_version} --weight="./XXX.caffemodel" --input_shape=`head -1 $HOME/AscendProjects/sample-videoanalysisperson/script/shape_XXX` --insert_op_conf=$HOME/AscendProjects/sample-videoanalysisperson/script/aipp_XXX.cfg --op_name_map=$HOME/AscendProjects/sample-videoanalysisperson/script/reassign_operators
            ```

            >![](public_sys-resources/icon-note.gif) **NOTE:**   
            >-   The files required by  **input\_shape**,  **insert\_op\_conf**, and  **op\_name\_map**  are stored in the  **sample-videoanalysisperson/script**  directory under the source code path. Configure the file paths based on the actual source code path.  
            >-   **XXX**  indicates the name of the Caffe model used in  [Table 1](#en-us_topic_0203223281_table1193115345597). Replace it with the actual name of the Caffe model to be converted. The  **op\_name\_map**  parameter is not required during  **pedestrian**  model conversion. If unnecessary parameters are not deleted, an error is reported during model conversion.  
            >-   For details about parameter descriptions, see "Model Conversion" in the  [Atlas 200 DK User Guide](https://ascend.huawei.com/doc/atlas200dk/).  

        3.  Run the following command to convert a TensorFlow model using OMG:

            ```
            ${DDK_HOME}/uihost/bin/omg --output="./XXX" --model="./XXX.pb" --framework=3 --ddk_version=${tools_version} --input_shape=`head -1 $HOME/AscendProjects/sample-videoanalysisperson/script/shape_XXX` --insert_op_conf=$HOME/AscendProjects/sample-videoanalysisperson/script/aipp_XXX.cfg
            ```

            >![](public_sys-resources/icon-note.gif) **NOTE:**   
            >-   **XXX**  indicates the name of the TensorFlow model used in  [Table 1](#en-us_topic_0203223281_table1193115345597). Replace it with the actual name of the TensorFlow model to be converted.  


5.  Upload the converted .om model file to the  **sample-videoanalysisperson/script**  directory in the source code path in  [Step 1](#en-us_topic_0203223281_li953280133816).

## Building a Project<a name="en-us_topic_0203223281_section1759513564117"></a>

1.  Open the project.

    Go to the directory that stores the decompressed installation package as the Mind Studio installation user in CLI mode, for example,  **$HOME/MindStudio-ubuntu/bin**. Run the following command to start Mind Studio:

    **./MindStudio.sh**

    Open the  **sample-videoanalysisperson**  project, as shown in  [Figure 8](#en-us_topic_0203223281_fig05481157171918).

    **Figure  8**  Opening the videoanalysisperson project<a name="en-us_topic_0203223281_fig05481157171918"></a>  
    ![](figures/opening-the-videoanalysisperson-project.png "opening-the-videoanalysisperson-project")

2.  Configure project information in the  **src/param\_configure.conf**  file.

    **Figure  9**  Configuration file path<a name="en-us_topic_0203223281_fig0391184062214"></a>  
    ![](figures/configuration-file-path.png "configuration-file-path")

    The default configurations of the configuration file are as follows:

    ```
    remote_host=192.168.1.2
    presenter_view_app_name=video
    video_path_of_host=/home/HwHiAiUser/person.mp4
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
    video_path_of_host=/home/HwHiAiUser/person.mp4
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

3.  Run the  **deploy.sh**  script to adjust configuration parameters and download and compile the third-party library. Open the  **Terminal**  window of Mind Studio. By default, the home directory of the code is used. Run the  **deploy.sh**  script in the background to deploy the environment, as shown in  [Figure 10](#en-us_topic_0203223281_fig581125810247).

    **Figure  10**  Running the deploy.sh script<a name="en-us_topic_0203223281_fig581125810247"></a>  
    ![](figures/running-the-deploy-sh-script.png "running-the-deploy-sh-script")

    >![](public_sys-resources/icon-note.gif) **NOTE:**   
    >-   During the first deployment, if no third-party library is used, the system automatically downloads and builds the third-party library, which may take a long time. The third-party library can be directly used for the subsequent build.  
    >-   During deployment, select the IP address of the host that communicates with the developer board. Generally, the IP address is that configured for the virtual NIC. If the IP address is in the same network segment as the IP address of the developer board, it is automatically selected for deployment. If they are not in the same network segment, you need to manually type the IP address of the host that communicates with the developer board to complete the deployment.  

4.  Start building. Open Mind Studio and choose  **Build \> Build \> Build-Configuration**  from the main menu. The  **build**  and  **run**  folders are generated in the directory, as shown in  [Figure 11](#en-us_topic_0203223281_fig1625447397).

    **Figure  11**  Build and files generated<a name="en-us_topic_0203223281_fig1625447397"></a>  
    

    ![](figures/en-us_image_0208267063.png)

    >![](public_sys-resources/icon-notice.gif) **NOTICE:**   
    >When you build a project for the first time,  **Build \> Build**  is unavailable. You need to choose  **Build \> Edit Build Configuration**  to set parameters before the build.  

5.  Start Presenter Server.

    Open the  **Terminal**  window of Mind Studio. By default, under the code path, run the following command to start the Presenter Server program of the people detection application on the server, as shown in  [Figure 12](#en-us_topic_0203223281_fig423515251067):

    **bash run\_present\_server.sh**

    **Figure  12**  Starting Presenter Server<a name="en-us_topic_0203223281_fig423515251067"></a>  
    ![](figures/starting-presenter-server.png "starting-presenter-server")

    -   When the message  **Please choose one to show the presenter in browser \(default: 127.0.0.1\):**  is displayed, type the IP address \(usually IP address for accessing  Mind Studio\) for accessing the Presenter Server service in the browser. 

        Select the IP address used by the browser to access the Presenter Server service in  **Current environment valid ip list**, as shown in  [Figure 13](#en-us_topic_0203223281_fig999812514814).

        **Figure  13**  Project deployment<a name="en-us_topic_0203223281_fig999812514814"></a>  
        ![](figures/project-deployment.png "project-deployment")

    -   When the message  **Please input an absolute path to storage video analysis data:**  is displayed, enter the absolute path for storing video analysis data in  Mind Studio. The  Mind Studio  user must have the read and write permissions. If the path does not exist, the script will automatically create it.

    [Figure 14](#en-us_topic_0203223281_fig69531305324)  shows that the Presenter Server service has been started successfully.

    **Figure  14**  Starting the Presenter Server process<a name="en-us_topic_0203223281_fig69531305324"></a>  
    ![](figures/starting-the-presenter-server-process.png "starting-the-presenter-server-process")

    Use the URL shown in the preceding figure to log in to Presenter Server \(only Google Chrome is supported\). The IP address is that typed in  [Figure 13](#en-us_topic_0203223281_fig999812514814)  and the default port number is  **7011**. The following figure indicates that Presenter Server has been started successfully.

    **Figure  15**  Home page<a name="en-us_topic_0203223281_fig64391558352"></a>  
    ![](figures/home-page.png "home-page")

    The following figure shows the IP address used by Presenter Server and  Mind Studio  to communicate with the Atlas 200 DK.

    **Figure  16**  IP address example<a name="en-us_topic_0203223281_fig1881532172010"></a>  
    ![](figures/ip-address-example.png "ip-address-example")

    -   The IP address of the Atlas 200 DK developer board is 192.168.1.2 \(connected in USB mode\).
    -   The IP address used by Presenter Server to communicate with the Atlas 200 DK is in the same network segment as the IP address of the Atlas 200 DK on the UI Host server, for example, 192.168.1.223.
    -   The following is an example of accessing the IP address of Presenter Server using a browser: 10.10.0.1, because Presenter Server and  Mind Studio  are deployed on the same server, the IP address is also the IP address for accessing the  Mind Studio  through the browser.

6.  Parse local videos and RTSP video streams using the people detection application.
    -   To parse a local video, upload the video file to the host.

        For example, upload the video file  **person.mp4**  to the  **/home/HwHiAiUser/**  directory on the host.

        >![](public_sys-resources/icon-note.gif) **NOTE:**   
        >H.264 and H.265 MP4 files are supported. If an MP4 file needs to be edited, you are advised to use FFmpeg. If a video file is edited by other tools, FFmpeg may fail to parse the file.  

    -   If only RTSP video streams need to be parsed, skip this step.


## Running<a name="en-us_topic_0203223281_section6245151616426"></a>

1.  Run the people detection application.

    On the toolbar of Mind Studio, click  **Run**  and choose  **Run \> Run 'sample-videoanalysisperson'**. As shown in  [Figure 17](#en-us_topic_0203223281_fig93931954162719), the executable application is running on the developer board.

    **Figure  17**  Application running<a name="en-us_topic_0203223281_fig93931954162719"></a>  
    

    ![](figures/sample-videoperson-running.png)

2.  Use the URL displayed upon the start of the Presenter Server service to log in to Presenter Server.

    >![](public_sys-resources/icon-note.gif) **NOTE:**   
    >Presenter Server of the people detection application can display a maximum of two  _presenter\_view\_app\_name_  values at a time.  

    The navigation tree on the left displays the app name and channel name of the video. The large image of the extracted video frame and the detected target small image are displayed in the middle. After you click the small image, the detailed inference result and score are displayed on the right.

    This application supports human body attribute detection, and facial attribute detection.

    -   Human body attributes include:

        Ages \(ages 16–30, 31–45, 46–60 as well as 61 and above\); Backpack; Carrying other; Casual lower; Casual upper; Formal lower; Hat; Jacket; Jeans; Leather Shoes; Logo; Short hair/Long hair; Male/Female; Messenger Bag; Muffler; No accessory; No carrying; Plaid; Plastic bags; Sandals; Shoes; Shorts; Short Sleeve; Skirt; Sneaker; Stripes; Sunglasses; Trousers; T-shirt; Upper other; V-Neck.

        In the detailed inference result display area on the video analysis interface,  **Age**,  **Male/Female**, and  **Short hair/Long hair**  are mandatory. Other attributes are displayed only when the confidence level is greater than 0.5.

    -   Facial attribute detection supports age and gender identification.


## Follow-up Operations<a name="en-us_topic_0203223281_section1092612277429"></a>

-   Stopping the people detection application

    After the video analysis is complete, the application automatically stops and exists, as shown in  [Figure 18](#en-us_topic_0203223281_fig853816815204).

    **Figure  18**  videoperson stopped<a name="en-us_topic_0203223281_fig853816815204"></a>  
    ![](figures/videoperson-stopped.png "videoperson-stopped")

-   Stopping the Presenter Server service

    The Presenter Server service is always in running state after being started. To stop the Presenter Server service of the people detection application, perform the following operations:

    Run the following command as the  Mind Studio  installation user to check the process of the Presenter Server service corresponding to the people detection application:

    **ps -ef | grep presenter | grep video\_analysis\_person**

    ```
    ascend@ascend-HP-ProDesk-600-G4-PCI-MT:~/sample-videoanalysisperson$ ps -ef | grep presenter | grep video_analysis_car
    ascend 3656 20313 0 15:10 pts/24?? 00:00:00 python3 presenterserver/presenter_server.py --app video_analysis_person
    ```

    In the preceding information,  _3656_  indicates the process ID of the Presenter Server service corresponding to the people detection application.

    To stop the service, run the following command:

    **kill -9** _3656_

-   **Precautions for restarting the people detection application**

    Before restarting the people detection application, ensure that any of the following conditions is met. Otherwise, an error is reported.

    1.  The content in the video parsing data storage path must have been cleared.

        For example, the path for storing video parsing data is  **$HOME/videoperson\_storage/video**, where  **$HOME/videoperson\_storage**  is configured when you start the Presenter Server service as pompt \("Please input an absolute path to storage video analysis data"\).  **video**  is the value of  **presenter\_view\_app\_name**  in the configuration file  **param\_configure.conf**.

        If this condition is met, you do not need to restart Presenter Server. Instead, choose  **Run \> Run** **'sample-videoanalysisperson'**  to run the application again.

    2.  If the video parsing storage path contains data that you want to keep, you can change the value of  **presenter\_view\_app\_name**  in the  **param\_configure.conf**  file, choose  **Build \> Rebuild**  again on Mind Studio, and then choose  **Run \> Run 'sample-videoanalysisperson'**.

        In the following figure, check out the value of  **presenter\_view\_app\_name**  in the  **param\_configure.conf**  file.

        ![](figures/人体检测的配置文件.png)

        If this condition is met, you do not need to restart Presenter Server.

    3.  If you restart Presenter Server and then run the vehicle detection application, change the path for storing video parsing data when restarting Presenter Server \(the path must be different from the previous storage path\).


