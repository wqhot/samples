#!/bin/bash
Download_C31sample()
{
    clear
    echo "The current community cases are categorized by programming language as follows"
    echo "1.python"
    echo "2.C++"
    read -p "Please select the serial number of the case type you need to download(eg:1):" typeofSample
    if [[ $typeofSample == "1" ]];then
        echo "Current samples and corresponding numbers:"
        echo "1.sample-headposeestimation-python"
        
        
        
        echo "2.sample-segmentation-python"
        
        read -p "Please input the number of sample you want to download(eg:1):" NumberofSample
        if [[ $NumberofSample == "1" ]];then
            bash ./C32/headposeestimationpythonC32.sh
  
        elif [[ $NumberofSample == "2" ]];then
            bash ./C32/segmentationpythonC32.sh
    
        else
            echo "[ERROR] Input Error!"
            return 1
        fi
        echo "[Info] Python case, no compilation steps"
    elif [[ $typeofSample == "2" ]];then
        echo "Current samples and corresponding numbers:"
        echo "1.sample-facedetection"
        echo "2.sample-facialrecognition"
        echo "3.sample-videoanalysisperson"
        
        echo "4.sample-ascendcamera"
        echo "5.sample-classification"
        echo "6.sample-objectdetection"
        
      
        echo "7.sample-colorization"
        echo "8.sample-carplaterecognition"
       
       
    
        echo "9.sample-objectdetectionbyyolov3"
       

        read -p "Please input the number of sample you want to download(eg:1):" NumberofSample
        if [[ $NumberofSample == "1" ]];then
            bash ./C32/facedetectionC32.sh
        elif [[ $NumberofSample == "2" ]];then
            bash ./C32/facialrecognitionC32.sh
        elif [[ $NumberofSample == "3" ]];then
            bash ./C32/videoanalysispersonC32.sh
        
        elif [[ $NumberofSample == "4" ]];then
            bash ./C32/ascendcameraC32.sh
        elif [[ $NumberofSample == "5" ]];then
            bash ./C32/classificationC32.sh
        elif [[ $NumberofSample == "6" ]];then
            bash ./C32/objectdetectionC32.sh
        
    
        elif [[ $NumberofSample == "7" ]];then
            bash ./C32/colorizationC32.sh
        elif [[ $NumberofSample == "8" ]];then
            bash ./C32/carplaterecognitionC32.sh
    
        elif [[ $NumberofSample == "9" ]];then
            bash ./C32/objectdetectionbyyolov3C32.sh
       
        else 
            echo "[ERROR] Input Error!"
            return 1
        fi
        echo "[INFO] The environment variables are set in the script. If this is your first download, please reopen the terminal and start Mind Studio, other the environment variables will not take effect."
    else
        echo "[ERROR] Input Error!"
    fi
}

Download_C30sample()
{
    clear
    echo "The current community cases are categorized by programming language as follows"
    echo "1.python"
    echo "2.C++"
    read -p "Please select the serial number of the case type you need to download(eg:1):" typeofSample
    if [[ $typeofSample == "1" ]];then
        echo "1.sample-headposeestimation-python"
        echo "2.sample-facedetection-python"
        echo "3.sample-classification-python"
        echo "4.sample-crowdcounting-python"
        echo "5.sample-segmentation-python"
        echo "6.sample-fasterrcnndetection-python"
        read -p "Please input your want download sample number in list(eg:1).:" NumberofSample
        if [[ $NumberofSample == "1" ]];then
            bash ./C30/headposeestimationpythonC30.sh
        elif [[ $NumberofSample == "2" ]];then
            bash ./C30/facedetectionpythonC30.sh
        elif [[ $NumberofSample == "3" ]];then
            bash ./C30/classificationpythonC30.sh
        elif [[ $NumberofSample == "4" ]];then
            bash ./C30/crowdcountingpythonC30.sh
        elif [[ $NumberofSample == "5" ]];then
            bash ./C30/segmentationpythonC30.sh
        elif [[ $NumberofSample == "6" ]];then
            bash ./C30/fasterrcnndetectionpythonC30.sh
        else
            echo "[ERROR] Input Error!"
        fi
    elif [[ $typeofSample == "2" ]];then
        echo "Current All sample and them number list:"
        echo "1.sample-facedetection"
        echo "2.sample-facialrecognition"
        echo "3.sample-videoanalysisperson"
        echo "4.sample-videoanalysiscar"
        echo "5.sample-ascendcamera"
        echo "6.sample-classification"
        echo "7.sample-objectdetection"
        echo "8.sample-faceantispoofing"
        echo "9.sample-peppapigdetection"
        echo "10.sample-colorization"
        echo "11.sample-carplaterecognition"
        echo "12.sample-segmentation"
        echo "13.sample-crowdcounting"
        echo "14.sample-faceemotion"
        echo "15.sample-objectdetectionbyyolov3"
        read -p "Please input your want download sample number in list(eg:1).:" NumberofSample
        if [[ $NumberofSample == "1" ]];then
            bash ./C30/facedetectionC30.sh
        elif [[ $NumberofSample == "2" ]];then
            bash ./C30/facialrecognitionC30.sh
        elif [[ $NumberofSample == "3" ]];then
            bash ./C30/videoanalysispersonC30.sh
        elif [[ $NumberofSample == "4" ]];then
            bash ./C30/videoanalysiscarC30.sh
        elif [[ $NumberofSample == "5" ]];then
            bash ./C30/ascendcameraC30.sh
        elif [[ $NumberofSample == "6" ]];then
            bash ./C30/classificationC30.sh
        elif [[ $NumberofSample == "7" ]];then
            bash ./C30/objectdetectionC30.sh
        elif [[ $NumberofSample == "8" ]];then
            bash ./C30/faceantispoofingC30.sh
        elif [[ $NumberofSample == "9" ]];then
            bash ./C30/peppapigdetectionC30.sh
        elif [[ $NumberofSample == "10" ]];then
            bash ./C30/colorizationC30.sh
        elif [[ $NumberofSample == "11" ]];then
            bash ./C30/carplaterecognitionC30.sh
        elif [[ $NumberofSample == "12" ]];then
            bash ./C30/segmentationC30.sh
        elif [[ $NumberofSample == "13" ]];then
            bash ./C30/crowdcountingC30.sh
        elif [[ $NumberofSample == "14" ]];then
            bash ./C30/faceemotionC30.sh
        elif [[ $NumberofSample == "15" ]];then
            bash ./C30/objectdetectionbyyolov3C30.sh
        else
            echo "[ERROR] Input Error!"
        fi
    else
        echo "[ERROR] Input Error!"
    fi

}

main()
{
    echo "faster-deploy start"
    number=0

    ddk_flag=`find $HOME/tools/che/ddk/ddk -maxdepth 1 -name "ddk_info" 2> /dev/null`
    if [[ $ddk_flag ]];then
        Version="C30"
    else
        all_ddk_path=`find $HOME/.mindstudio/huawei/ddk/ -maxdepth 1 -name "*.*.*.*" 2> /dev/null`
        if [[ $all_ddk_path ]];then
            Version="C31"
            echo "The currently installed ddk version numbers are as follows:"
            for ddk_path in ${all_ddk_path}
            do
                ((number=number+1))
                DDK_VERSIONS[$number]=`basename ${ddk_path}`
                echo "$number:${DDK_VERSIONS[$number]}"
            done
        else
            echo "[ERROR]Please install DDK first"
            return 1
        fi
    fi
    if [[ $number -ge 2 ]];then
        read -p "Several DDK are detected. Please input your DDK verison in this list(eg:1):" DDK_VERSION_NUM
        if [[ ! $DDK_VERSION_NUM ]]; then
            echo "[ERROR] Input empty,please input ddk-verison(eg:1)"
            return 1
        else
            if [ "$DDK_VERSION_NUM" -gt 0 ] 2>/dev/null ; then
                DDK_VERSION=${DDK_VERSIONS[$DDK_VERSION_NUM]}
            else
                echo "[ERROR] Input ddk-version Error,Please check your input"
                return 1
            fi
        fi
    elif [[ $number -eq 1 ]];then
        DDK_VERSION=${DDK_VERSIONS[1]}
    fi

    sudo apt-get update
    if [[ $? -ne 0 ]];then
        echo "[ERROR] Please make sure you are connected to the Internet and check the source in /etc/apt/sources.list is available."
        return 1
    fi

    git --version
    if [[ $? -ne 0 ]];then
        echo "[INFO] Installing git..."
        sudo apt-get install git
        if [[ $? -ne 0 ]];then
            echo "[ERROR] Failed to install git, please install git manually"
            return 1
        fi
    fi

    if [[ $Version == "C31" ]]; then
        AscendProjects_flag=`find $HOME -maxdepth 1 -name "AscendProjects" 2> /dev/null`
        if [[ ! $AscendProjects_flag ]];then
            mkdir $HOME/AscendProjects
            if [[ $? -ne 0 ]];then
                echo "[ERROR] mkdir failed. Please make sure you have the right permission"
                return 1
            fi
        fi
        
        grep -Fx "export tools_version=$DDK_VERSION" $HOME/.bashrc >/dev/null 2>&1
        if [ $? -ne 0 ];then
            echo "export tools_version=$DDK_VERSION" >> $HOME/.bashrc
            echo "export DDK_HOME=\$HOME/.mindstudio/huawei/ddk/\$tools_version/ddk" >> $HOME/.bashrc
            echo "export LD_LIBRARY_PATH=\$DDK_HOME/lib/x86_64-linux-gcc5.4:\$DDK_HOME/uihost/lib" >> $HOME/.bashrc
            echo "export PATH=\$PATH:\$DDK_HOME/uihost/bin" >> $HOME/.bashrc
        fi
        grep -Fx "export DDK_HOME=\$HOME/.mindstudio/huawei/ddk/\$tools_version/ddk" $HOME/.bashrc >/dev/null 2>&1
        if [ $? -ne 0 ];then
            echo "export DDK_HOME=\$HOME/.mindstudio/huawei/ddk/\$tools_version/ddk" >> $HOME/.bashrc
        fi
        grep -Fx "export LD_LIBRARY_PATH=\$DDK_HOME/lib/x86_64-linux-gcc5.4:\$DDK_HOME/uihost/lib" $HOME/.bashrc >/dev/null 2>&1
        if [ $? -ne 0 ];then
            echo "export LD_LIBRARY_PATH=\$DDK_HOME/lib/x86_64-linux-gcc5.4:\$DDK_HOME/uihost/lib" >> $HOME/.bashrc
        fi
        grep -Fx "export PATH=\$PATH:\$DDK_HOME/uihost/bin" $HOME/.bashrc >/dev/null 2>&1
        if [ $? -ne 0 ];then
            echo "export PATH=\$PATH:\$DDK_HOME/uihost/bin" >> $HOME/.bashrc
        fi
        source $HOME/.bashrc

        Download_C31sample
        
    else
        grep -Fx "export DDK_HOME=\$HOME/tools/che/ddk/ddk" $HOME/.bashrc >/dev/null 2>&1
        if [ $? -ne 0 ];then
            echo "export DDK_HOME=\$HOME/tools/che/ddk/ddk" >> $HOME/.bashrc
        fi
        grep -Fx "export LD_LIBRARY_PATH=\$DDK_HOME/uihost/lib" $HOME/.bashrc >/dev/null 2>&1
        if [ $? -ne 0 ];then
            echo "export LD_LIBRARY_PATH=\$DDK_HOME/uihost/lib" >> $HOME/.bashrc
        fi
        grep -Fx "export PATH=\$PATH:\$DDK_HOME/uihost/bin" $HOME/.bashrc >/dev/null 2>&1
        if [ $? -ne 0 ];then
            echo "export PATH=\$PATH:\$DDK_HOME/uihost/bin" >> $HOME/.bashrc
        fi
        
        Download_C30sample
    fi
    echo "[INFO] Finish to deploy. APP directory in $HOME/AscendProjects/"
}
main
