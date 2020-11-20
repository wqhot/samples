中文|[English](Readme_EN.md)

# 开发板环境依赖安装<a name="ZH-CN_TOPIC_0228768065"></a>

开发板环境依赖安装包括python、opencv、hiai库等。请按照以下步骤进行依赖安装

1.  在开发板的root用户下更换源。

    **vim /etc/apt/sources.list**

    把原有源更换为arm源，可用的国内arm源有中科大源和清华源等。

    >![](public_sys-resources/icon-note.gif) **说明：**   
    >arm源可参考[https://bbs.huaweicloud.com/forum/thread-37023-1-1.html](https://bbs.huaweicloud.com/forum/thread-37023-1-1.html)  

    源更新后，执行以下命令更新软件列表。

    **apt-get update**

2.  安装相关依赖，环境依赖分为python2和python3版本。当前python样例大多使用python2环境，如果有python3使用需求的可以按照[python3环境依赖安装](#li81699892817)进行安装。
    1.  Python2开发环境的依赖安装。
        1.  安装python2的依赖。

            ```
            apt-get install python-setuptools python-dev build-essential python-imaging
            ```

            ```
            pip install enum34==1.1.6 future==0.17.1 funcsigs==1.0.2 unique protobuf numpy
            ```

        2.  安装python2的hiai库。

            下载python2\_hiai\_install脚本到开发者板的/home/HwHiAiUser目录下，并以root用户执行该脚本。

            **bash python2\_hiai\_install.sh**

            安装后如[图1](#fig961803392713)所示，则为安装成功。

            **图 1**  hiai安装成功验证<a name="fig961803392713"></a>  
            ![](figures/hiai安装成功验证.png "hiai安装成功验证")

        3.  以root用户下开发者板的/home/HwHiAiUser目录下执行以下命令安装OpenCV Python库。

            **apt-get install python-opencv**

            安装后如[图2](#fig861883362717)所示，则为安装成功。

            **图 2**  opencv安装成功验证<a name="fig861883362717"></a>  
            ![](figures/opencv安装成功验证.png "opencv安装成功验证")

            >![](public_sys-resources/icon-note.gif) **说明：**   
            >-   pip install安装有报错“SSLError”时，请使用：pip install --trusted-host pypi.org --trusted-host files.pythonhosted.org numpy==1.11.2 enum34==1.1.6 future==0.17.1 funcsigs==1.0.2 unique protobuf 安装依赖，表示可信赖的主机解决问题。  
            >-   python2\_hiai\_install脚本下载路径：[https://gitee.com/HuaweiAscend/tools/blob/master/python2\_hiai\_install.sh](https://gitee.com/HuaweiAscend/tools/blob/master/python2_hiai_install.sh)  。  


    2.  <a name="li81699892817"></a>Python3开发环境的依赖安装。
        1.  安装python3的依赖。

            ```
            apt-get install python3-setuptools python3-dev build-essential python3-pip
            ```

            ```
            pip3 install enum34==1.1.6 future==0.17.1 funcsigs==1.0.2 unique protobuf numpy
            ```

        2.  安装python3的hiai库。

            下载python3\_hiai\_install脚本到开发板的/home/HwHiAiUser目录下，并以root用户执行该脚本。

            **bash python3\_hiai\_install.sh**

        3.  Python3安装OpenCV需要使用源码安装，安装步骤如下。

            在开发板者中以root用户在/home/HwHiAiUser目录下执行以下命令下载源码。

            -   执行如下命令下载OpenCV源码。

                **git clone  [https://github.com/opencv/opencv.git](https://github.com/opencv/opencv.git)**

            -   执行如下命令下载OpenCV的依赖。

                **git clone  [https://github.com/opencv/opencv\_contrib.git](https://github.com/opencv/opencv_contrib.git)**

            执行以下代码安装构建opencv的工具。

            ```
            apt-get install build-essential -y
            ```
            ```
            apt-get install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev libv4l-dev -y
            ```

            执行以下代码在opencv中构建环境。

            **cd opencv**

            **mkdir release**

            **cd release/**

            ```
            cmake -D BUILD_opencv_python3=YES -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local -D WITH_LIBV4L=ON -D OPENCV_EXTRA_MODULES=../../opencv_contrib/modules -D PYTHON3_LIBRARIES=/usr/lib/arm-linux-gnueabihf/libpython3.5m.so -D PYTHON3_NUMPY_INCLUDE_DIRS=/usr/local/lib/python3.5/dist-packages/numpy/core/include/ ..
            ```

            执行以下代码编译、安装并更新动态库。

            **make -j8**

            **make install**

            **ldconfig**

            >![](public_sys-resources/icon-note.gif) **说明：**   
            >-   pip3 install安装有报错“SSLError”时，请使用：pip3 install --trusted-host pypi.org --trusted-host files.pythonhosted.org numpy==1.11.2 enum34==1.1.6 future==0.17.1 funcsigs==1.0.2 unique protobuf 安装依赖，表示可信赖的主机解决问题。  
            >-   python3\_hiai\_install脚本下载路径：[https://gitee.com/HuaweiAscend/tools/blob/master/python3\_hiai\_install.sh](https://gitee.com/HuaweiAscend/tools/blob/master/python3_hiai_install.sh)  。  




