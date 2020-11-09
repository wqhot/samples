English|[中文](Readme.md)

**This case is only used for learning. It is not responsible for the effect and does not support commercial use.**

# Semantic Segmentation Network Application \(Python\)<a name="EN-US_TOPIC_0232637441"></a>

This application can run on the Atlas 200 DK to implement the inference function of the ERFNet network and output images with inference result.

The current application adapts to  [DDK&RunTime](https://ascend.huawei.com/resources)  of 1.3.0.0 as well as 1.32.0.0 and later versions.

## Prerequisites<a name="en-us_topic_0228757085_section137245294533"></a>

Before deploying this sample, ensure that:

-   Mind Studio  has been installed.

-   The Atlas 200 DK developer board has been connected to  Mind Studio, the SD card has been created, and the compilation environment has been configured.
-   The developer board is connected to the Internet over the USB port by default. The IP address of the developer board is  **192.168.1.2**.

## Software Preparation<a name="en-us_topic_0228757085_section8534138124114"></a>

Before running this application, obtain the source code package and configure the environment as follows.

1.  <a name="en-us_topic_0228757085_li953280133816"></a>Obtain the source code package.
    1.  By downloading the package

        Download all code in the repository at  [https://gitee.com/ascend/samples/tree/1.32.0.0/sample-segmentation-python](https://gitee.com/ascend/samples/tree/1.32.0.0/sample-segmentation-python)  to any directory on Ubuntu Server where  Mind Studio  is located as the  Mind Studio  installation user, for example,  **$HOME/sample-segmentation-python**.

    2.  By running the  **git**  command

        Run the following command in the  **$HOME/AscendProjects**  directory to download code:

        **git clone https://gitee.com/Atlas200DK/sample-segmentation-python.git**

2.  Obtain the network model required by the application.

    Refer to  [Table 1](#en-us_topic_0228757085_table1119094515272)  to obtain the source network model used in this application and the corresponding weight file. Save them to any directory of the Ubuntu server with  Mind Studio  installed, for example,  **$HOME/ascend/models/sample-segmentation-python**.

    **Table  1**  Models used in a semantic segmentation network application

    <a name="en-us_topic_0228757085_table1119094515272"></a>
    <table><thead align="left"><tr id="en-us_topic_0228757085_row677354502719"><th class="cellrowborder" valign="top" width="12.15%" id="mcps1.2.4.1.1"><p id="en-us_topic_0228757085_p167731845122717"><a name="en-us_topic_0228757085_p167731845122717"></a><a name="en-us_topic_0228757085_p167731845122717"></a>Model Name</p>
    </th>
    <th class="cellrowborder" valign="top" width="17.53%" id="mcps1.2.4.1.2"><p id="en-us_topic_0228757085_p277317459276"><a name="en-us_topic_0228757085_p277317459276"></a><a name="en-us_topic_0228757085_p277317459276"></a>Description</p>
    </th>
    <th class="cellrowborder" valign="top" width="70.32000000000001%" id="mcps1.2.4.1.3"><p id="en-us_topic_0228757085_p9773114512270"><a name="en-us_topic_0228757085_p9773114512270"></a><a name="en-us_topic_0228757085_p9773114512270"></a>Download Path</p>
    </th>
    </tr>
    </thead>
    <tbody><tr id="en-us_topic_0228757085_row3122314144215"><td class="cellrowborder" valign="top" width="12.15%" headers="mcps1.2.4.1.1 "><p id="en-us_topic_0228757085_p1910619166207"><a name="en-us_topic_0228757085_p1910619166207"></a><a name="en-us_topic_0228757085_p1910619166207"></a>ERFNet</p>
    </td>
    <td class="cellrowborder" valign="top" width="17.53%" headers="mcps1.2.4.1.2 "><p id="en-us_topic_0228757085_p2010681612020"><a name="en-us_topic_0228757085_p2010681612020"></a><a name="en-us_topic_0228757085_p2010681612020"></a>Semantic segmentation inference model.</p>
    <p id="en-us_topic_0228757085_p1710615162207"><a name="en-us_topic_0228757085_p1710615162207"></a><a name="en-us_topic_0228757085_p1710615162207"></a>It is an ERFNet model based on Caffe.</p>
    </td>
    <td class="cellrowborder" valign="top" width="70.32000000000001%" headers="mcps1.2.4.1.3 "><p id="en-us_topic_0228757085_p910617162206"><a name="en-us_topic_0228757085_p910617162206"></a><a name="en-us_topic_0228757085_p910617162206"></a>Download the source network model file and its weight file by referring to<strong id="en-us_topic_0228757085_b159782239917"><a name="en-us_topic_0228757085_b159782239917"></a><a name="en-us_topic_0228757085_b159782239917"></a> README.md</strong> at <a href="https://gitee.com/HuaweiAscend/models/tree/master/computer_vision/segmentation/erfnet" target="_blank" rel="noopener noreferrer">https://gitee.com/HuaweiAscend/models/tree/master/computer_vision/segmentation/erfnet</a>.</p>
    </td>
    </tr>
    </tbody>
    </table>

3.  Convert the source network model to a model supported by the Ascend AI processor.
    1.  Choose  **Tools \> Model Convert**  from the main menu of  Mind Studio.
    2.  On the  **Model Conversion**  page, set  **Model File**  and  **Weight File**  to the model file and weight file downloaded in  [1](#en-us_topic_0228757085_li953280133816), respectively.
        -   Set  **Model Name**  to the model name in  [Table 1](#en-us_topic_0228757085_table1119094515272).
        -   During ERFNet model conversion, set  **Model Image Format**  to  **BGR888\_U8**  and disable  **MeanLess**.
        -   Retain default values for other parameters.

    3.  Click  **OK**  to start model conversion.

        After a model of 1.1.0.0 or 1.3.0.0 version is successfully converted, a .om offline model is generated in the  **$HOME/tools/che/model-zoo/my-model/xxx**  directory.

        After a model of 1.31.0.0 or a later version is successfully converted, an .om offline model is generated in the  **$HOME/modelzoo/xxx/device/_xxx_.om**  directory.

    4.  Upload the converted .om model file to the  **sample-segmentation-python/segmentationapp/models**  directory under the source code path in  [Step 1](#en-us_topic_0228757085_li953280133816).


## Environment Deployment and Preparation<a name="en-us_topic_0228757085_section218113616146"></a>

1.  Copy the application code to the developer board.

    Go to the root directory of the semantic segmentation application \(python\) code as the  Mind Studio  installation user, for example,  **$HOME/sample-segmentation-python**, and run the following command to copy the application code to the developer board:

    **scp -r ../sample-segmentation-python/ HwHiAiUser@192.168.1.2:/home/HwHiAiUser/HIAI\_PROJECTS**

    Type the password of the developer board as prompted. The default password is  **Mind@123**, as shown in  [Figure 1](#en-us_topic_0228757085_en-us_topic_0219036254_fig1660453512014).

    **Figure  1**  Copying application code<a name="en-us_topic_0228757085_en-us_topic_0219036254_fig1660453512014"></a>  
    

    ![](figures/en-us_image_0228836881.png)

    Log in to the host side as the  **HwHiAiUser**  user in SSH mode on Ubuntu Server where  Mind Studio  is located.

    **ssh HwHiAiUser@192.168.1.2**

    Switch to the  **root**  user. The default password of the  **root**  user on the developer board is  **Mind@123**.

    **su root**

2.  Configure the network connection of the developer board.

    Configure the network connection of the Atlas DK developer board by referring to  [https://gitee.com/Atlas200DK/sample-README/tree/master/DK\_NetworkConnect](https://gitee.com/Atlas200DK/sample-README/tree/master/DK_NetworkConnect).

3.  Install the environment dependencies.

    Configure the environment dependency by referring to  [https://gitee.com/Atlas200DK/sample-README/tree/master/DK\_Environment](https://gitee.com/Atlas200DK/sample-README/tree/master/DK_Environment).


## Application Running<a name="en-us_topic_0228757085_section6245151616426"></a>

1.  Switch to the  **HwHiAiUser**  user and go to the directory where the semantic segmentation network application code is located.

    **su HwHiAiUser**

    **cd \~/HIAI\_PROJECTS/sample-segmentation-python/segmentationapp**

2.  Run the application.

    Run the  **segmentation.py**  script to print the inference result on the execution terminal.

    Command example:

    **python segmentation.py**

    [Figure 2](#en-us_topic_0228757085_fig1863053617417)  shows the inference result after the execution is successful.

    **Figure  2**  Successful inference<a name="en-us_topic_0228757085_fig1863053617417"></a>  
    

    ![](figures/en-us_image_0228757232.png)

3.  Query the execution result.

    The execution result is stored in  **Result**  of the current directory. You need to run the following command on the Atlas 200 DK to copy the result to the Ubuntu server to view the inference result image:

    **scp -r username@host\_ip:/home/username/HIAI\_PROJECTS/sample-classification-python/Result \~**

    -   **username**: user name of the developer board. The default value is  **HwHiAiUser**.
    -   **host\_ip**: IP address of the developer board. Generally, the IP address is  **192.168.1.2**  for USB connection and  **192.168.0.2**  for network cable connection.

    **Command example:**

    **scp -r HwHiAiUser@192.168.1.2:/home/HwHiAiUser/HIAI\_PROJECTS/sample-classification-python/Result \~**

    This command copies the inference result to the home directory of the Mind Studio installation user. You can view the inference result directly.


## Remarks<a name="en-us_topic_0228757085_section1092612277429"></a>

-   **The process of the semantic segmentation network application \(Python\) is as follows:**
    1.  Read a JPEG image from the  **cityimage**  directory.
    2.  Call OpenCV to resize the read JPEG image to 1024 x 512 and convert it to YUV420SP.
    3.  Send the converted YUV420SP image data to Matrix for inference. The demo uses the ERFNet network, and the inference result includes the confidence values of 19 categories for each pixel.
    4.  During post-processing, the category of the highest confidence value is used for each pixel, and pixels of the same category in the image are marked with the same color. A colored image is stored in the  **Result**  directory.

-   **The directory structure of the semantic segmentation application \(Python\) is described as follows:**
    -   **cityimage**: directory of input images
    -   **segmentation.py**: main program
    -   **jpegHandler.py: jpeg**: JPEG image processing, such as resizing and color space conversion \(CSC\)
    -   **models**: directory of model networks
    -   **Result**: directory of labeled images


