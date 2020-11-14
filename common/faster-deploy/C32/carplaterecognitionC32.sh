#!/bin/bash

script_path="$HOME/AscendProjects/sample-carplaterecognition/script"
model_path="$HOME/AscendProjects/sample-carplaterecognition/MyModel"

function download()
{
    model_name=$1
    License_OK=$2
    model_shape=`head -1 ${model_path}/shape_${model_name}`
    if [ ! -f "${script_path}/${model_name}.om" ];then
        download_url_caffemodel="https://obs-model-ascend.obs.cn-east-2.myhuaweicloud.com/${model_name}/${model_name}.caffemodel"
	download_url_prototxt="https://obs-model-ascend.obs.cn-east-2.myhuaweicloud.com/${model_name}/${model_name}.prototxt"
        download_url_license="https://obs-model-ascend.obs.cn-east-2.myhuaweicloud.com/${model_name}/LICENSE"
        wget -O ${model_path}/${model_name}.caffemodel ${download_url_caffemodel} --no-check-certificate
	wget -O ${model_path}/${model_name}.prototxt ${download_url_prototxt} --no-check-certificate
        if [[ ${License_OK} == "1" ]];then
            wget -O ${model_path}/LICENSEN_${model_name} ${download_url_license} --no-check-certificate
        fi

	if [ ${model_name} == "vgg_ssd" -o ${model_name} == "car_plate_detection" ];then
		export SLOG_PRINT_TO_STDOUT=1 && export PATH=${PATH}:${DDK_HOME}/uihost/toolchains/ccec-linux/bin/ && export LD_LIBRARY_PATH=${DDK_HOME}/uihost/lib/ && export TVM_AICPU_LIBRARY_PATH=${DDK_HOME}/uihost/lib/:${DDK_HOME}/uihost/toolchains/ccec-linux/aicpu_lib && export TVM_AICPU_INCLUDE_PATH=${DDK_HOME}/include/inc/tensor_engine && export PYTHONPATH=${DDK_HOME}/site-packages && export TVM_AICPU_OS_SYSROOT=/usr/aarch64-linux-gnu && ${DDK_HOME}/uihost/bin/omg --output="${script_path}/${model_name}" --check_report=${model_path}/${model_name}_result.json --plugin_path= --model="${model_path}/${model_name}.prototxt" --framework=0 --ddk_version=${tools_version} --weight="${model_path}/${model_name}.caffemodel" --input_shape=${model_shape} --insert_op_conf=${model_path}/aipp_${model_name}.cfg --op_name_map=${model_path}/reassign_operators
        else
		export SLOG_PRINT_TO_STDOUT=1 && export PATH=${PATH}:${DDK_HOME}/uihost/toolchains/ccec-linux/bin/ && export LD_LIBRARY_PATH=${DDK_HOME}/uihost/lib/ && export TVM_AICPU_LIBRARY_PATH=${DDK_HOME}/uihost/lib/:${DDK_HOME}/uihost/toolchains/ccec-linux/aicpu_lib && export TVM_AICPU_INCLUDE_PATH=${DDK_HOME}/include/inc/tensor_engine && export PYTHONPATH=${DDK_HOME}/site-packages && export TVM_AICPU_OS_SYSROOT=/usr/aarch64-linux-gnu && ${DDK_HOME}/uihost/bin/omg --output="${script_path}/${model_name}" --check_report=${model_path}/${model_name}_result.json --plugin_path= --model="${model_path}/${model_name}.prototxt" --framework=0 --ddk_version=${tools_version} --weight="${model_path}/${model_name}.caffemodel" --input_shape=${model_shape} --insert_op_conf=${model_path}/aipp_${model_name}.cfg
	fi
	if [ $? -ne 0 ];then
            echo "[ERROR] Download failed. Please check your network connection."
            return 1
        fi
    else
        echo "${script_path}/${model_name}.om exists, skip downloading."
    fi

    return 0
}

main()
{
    echo "Deploying carplaterecognitionapp..."

    C31_flag=`find $HOME/AscendProjects -maxdepth 1 -name "sample-carplaterecognition" 2> /dev/null`
    if [[ $C31_flag ]];then
        read -p "[INFO] The sample-carplaterecognition already exists. Do you want to replace it? [Y/N]:" response
        if [ $response"z" = "Nz" ] || [ $response"z" = "nz" ]; then
            echo "Exit prepareing"
            return 1
        elif [ $response"z" = "Yz" ] || [ $response"z" = "yz" ] || [ $response"z" = "z" ]; then
            rm -rf $HOME/AscendProjects/sample-carplaterecognition
            if [[ $? -ne 0 ]];then
                echo "[ERROR] Execute rm command failed. Please manually delete $HOME/AscendProjects/sample-carplaterecognition director and re-execute this script."
                return 1
            fi
        else
            echo "[ERROR] Please input Y/N!"
            return 1
        fi
    fi

    mkdir $HOME/AscendProjects/sample-carplaterecognition
    if [[ $? -ne 0 ]];then
        echo "[ERROR] Execute mkdir command failed. Please make sure you have the right permission."
        return 1
    fi  

    
	mv $HOME/AscendProjects/samples/sample-carplaterecognition $HOME/AscendProjects/
    if [[ $? -ne 0 ]];then
        echo "[ERROR] Git clone failed. Please check your network connection."
        return 1
    fi

    download "car_plate_detection" "1"
    download "car_plate_recognition" "1"
    download "vgg_ssd" "1"

    echo "[INFO] Please follow the link from the compile step in Readme to continue running the case.(https://gitee.com/ascend/samples.git)"
}
main
