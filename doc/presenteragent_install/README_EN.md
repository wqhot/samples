English|[中文](README.md)

# Installing Presenter Agent<a name="ZH-CN_TOPIC_0228768065"></a>
1.  Download the Presenter Agent package.    
    **cd $HOME**  
    **wget https://c7xcode.obs.cn-north-4.myhuaweicloud.com/presenteragent/presenteragent.zip --no-check-certificate**  
    **unzip presenteragent.zip** 
2.  Install the autoconf, automake, and libtool dependencies.  
    **sudo apt-get install autoconf automake libtool python3-pip**
3.  Install python packages.  
    **python3 -m pip install pip --user**  
    **python3 -m pip install --upgrade pip --user**    
    **python3 -m pip install tornado==5.1.0 protobuf==3.5.1 numpy==1.14.2 --user**  
    **python3.7.5 -m pip install tornado==5.1.0 --user** 
4.  Install Protobuf. (Run the following commands in sequence. Because cross compilation is required, you need to compile Protobuf twice.)  
    **git clone -b 3.8.x https://gitee.com/mirrors/protobufsource.git protobuf**  
    **cd protobuf**    
    **./autogen.sh**  
    **bash configure**  
    **make -j8**  
    **sudo make install**  
    **make distclean**  
    **./configure --build=x86_64-linux-gnu --host=aarch64-linux-gnu --with-protoc=protoc**  
    **make -j8**  
    **sudo make install**    
    **su root**  
    **ldconfig**
5.  Compile and install Presenter Agent.  
    Switch to the common user.  
    **exit**    
    
    Set the following environment variable.  
    **export DDK_PATH=$HOME/Ascend/ascend-toolkit/X.X.X/acllib_centos7.6.aarch64**   
    >![](public_sys-resources/icon-note.gif) **说明：**  
        **Replace X.X.X with the actual version of the Ascend Toolkit. 
For example, if the Toolkit is named Ascend-Toolkit-20.0.RC1-x86_64-linux_gcc7.3.0.run, the Toolkit version is 20.0.RC1.**   

    Install Presenter Agent.  
    **cd $HOME/presenteragent/**    
    **make -j8**   
    **make install**  
    
    Upload the compiled .so file to the Atlas 200 DK.  
    **scp $HOME/ascend_ddk/arm/lib/libpresenteragent.so HwHiAiUser@192.168.1.2:/home/HwHiAiUser**    
    **ssh HwHiAiUser@192.168.1.2**   
    **cp /home/HwHiAiUser/libpresenteragent.so /home/HwHiAiUser/ascend_ddk/arm/lib**  

6.  Add environment variables. (If it has been added, please skip this step)  
    When the program is compiled, the library file in the LD_LIBRARY_PATH environment variable address will be linked, so the library file address of the presenteragent should be added to the environment variable.  
    **vi ~/.bashrc**  
    
    Add at the end  
    **export LD_LIBRARY_PATH=/home/HwHiAiUser/Ascend/acllib/lib64:/home/HwHiAiUser/ascend_ddk/arm/lib**
    ![](figures/bashrc.png "")   
    
    Execute the following command to make the environment variable take effect.  
    **source ~/.bashrc**