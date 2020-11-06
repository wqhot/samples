#!/bin/bash

main()
{
    echo "Deploying facedetectionapp..."

    C31_flag=`find $HOME/AscendProjects -maxdepth 1 -name "sample-facedetection" 2> /dev/null`
    if [[ $C31_flag ]];then
        read -p "[INFO] The sample-facedetection already exists. Do you want to replace it? [Y/N]:" response
        if [ $response"z" = "Nz" ] || [ $response"z" = "nz" ]; then
            echo "Exit prepareing"
            return 1
        elif [ $response"z" = "Yz" ] || [ $response"z" = "yz" ] || [ $response"z" = "z" ]; then
            rm -rf $HOME/AscendProjects/sample-facedetection
            if [[ $? -ne 0 ]];then
                echo "[ERROR] Execute rm command failed. Please manually delete $HOME/AscendProjects/sample-facedetection director and re-execute this script."
                return 1
            fi
        else
            echo "[ERROR] Please input Y/N!"
            return 1
        fi
    fi

    mkdir $HOME/AscendProjects/sample-facedetection
    if [[ $? -ne 0 ]];then
        echo "[ERROR] Execute mkdir command failed. Please make sure you have the right permission."
        return 1
    fi

    git clone https://gitee.com/Atlas200DK/sample-facedetection.git $HOME/AscendProjects/sample-facedetection --branch 1.3x.0.0
    if [[ $? -ne 0 ]];then
        echo "[ERROR] Git clone failed. Please check your network connection."
        return 1
    fi


    if [ ! -f "$HOME/AscendProjects/sample-facedetection/script/face_detction.om" ];then
	model_shape=`head -1 $HOME/AscendProjects/sample-facedetection/MyModel/shape_face_detection`
        download_url_caffemodel="https://obs-model-ascend.obs.cn-east-2.myhuaweicloud.com/face_detection/face_detection.caffemodel"
        download_url_prototxt="https://obs-model-ascend.obs.cn-east-2.myhuaweicloud.com/face_detection/face_detection.prototxt"
        download_url_license="https://obs-model-ascend.obs.cn-east-2.myhuaweicloud.com/face_detection/LICENSE"
        wget -O $HOME/AscendProjects/sample-facedetection/MyModel/face_detection.caffemodel ${download_url_caffemodel} --no-check-certificate
        wget -O $HOME/AscendProjects/sample-facedetection/MyModel/face_detection.prototxt ${download_url_prototxt} --no-check-certificate
        wget -O $HOME/AscendProjects/sample-facedetection/MyModel/LICENSE ${download_url_license} --no-check-certificate
        export SLOG_PRINT_TO_STDOUT=1 && export PATH=${PATH}:${DDK_HOME}/uihost/toolchains/ccec-linux/bin/ && export LD_LIBRARY_PATH=${DDK_HOME}/uihost/lib/ && export TVM_AICPU_LIBRARY_PATH=${DDK_HOME}/uihost/lib/:${DDK_HOME}/uihost/toolchains/ccec-linux/aicpu_lib && export TVM_AICPU_INCLUDE_PATH=${DDK_HOME}/include/inc/tensor_engine && export PYTHONPATH=${DDK_HOME}/site-packages && export TVM_AICPU_OS_SYSROOT=/usr/aarch64-linux-gnu && ${DDK_HOME}/uihost/bin/omg --output="$HOME/AscendProjects/sample-facedetection/script/face_detection" --check_report=$HOME/AscendProjects/sample-facedetection/MyModel/face_detection_result.json --plugin_path= --model="$HOME/AscendProjects/sample-facedetection/MyModel/face_detection.prototxt" --framework=0 --ddk_version=${tools_version} --weight="$HOME/AscendProjects/sample-facedetection/MyModel/face_detection.caffemodel" --input_shape=${model_shape} --insert_op_conf=$HOME/AscendProjects/sample-facedetection/MyModel/aipp_face_detection.cfg --op_name_map=$HOME/AscendProjects/sample-facedetection/MyModel/reassign_operators
        if [ $? -ne 0 ];then
            echo "[ERROR] Download failed. Please check your network connection."
            return 1
        fi
    else
        echo "face_detection.om exists, skip downloading."
    fi

    echo "[INFO] Please follow the link from the 编译 step in Readme to continue running the case.(https://gitee.com/Atlas200DK/sample-facedetection/tree/1.3x.0.0/)"
}
main
