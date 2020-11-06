#!/bin/bash

script_path="$HOME/AscendProjects/sample-crowdcounting/script"
model_path="$HOME/AscendProjects/sample-crowdcounting/MyModel"

function download()
{
    model_name=$1
    License_OK=$2
    model_shape=`head -1 ${model_path}/shape_${model_name}`
    if [ ! -f "${script_path}/${model_name}.om" ];then
        download_url_license="https://obs-model-ascend.obs.cn-east-2.myhuaweicloud.com/${model_name}/LICENSE"
        if [[ ${License_OK} == "1" ]];then
            wget -O ${model_path}/LICENSEN_${model_name} ${download_url_license} --no-check-certificate
        fi

        download_url_pb="https://obs-model-ascend.obs.cn-east-2.myhuaweicloud.com/${model_name}/${model_name}.pb"
        wget -O ${model_path}/${model_name}.pb ${download_url_pb} --no-check-certificate

	export SLOG_PRINT_TO_STDOUT=1 && export PATH=${PATH}:${DDK_HOME}/uihost/toolchains/ccec-linux/bin/ && export LD_LIBRARY_PATH=${DDK_HOME}/uihost/lib/ && export TVM_AICPU_LIBRARY_PATH=${DDK_HOME}/uihost/lib/:${DDK_HOME}/uihost/toolchains/ccec-linux/aicpu_lib && export TVM_AICPU_INCLUDE_PATH=${DDK_HOME}/include/inc/tensor_engine && export PYTHONPATH=${DDK_HOME}/site-packages && export TVM_AICPU_OS_SYSROOT=/usr/aarch64-linux-gnu && ${DDK_HOME}/uihost/bin/omg --output="${script_path}/${model_name}" --check_report=${model_path}/${model_name}_result.json --plugin_path= --model="${model_path}/${model_name}.pb" --framework=3 --ddk_version=${tools_version} --input_shape=${model_shape} --insert_op_conf=${model_path}/aipp_${model_name}.cfg
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
    echo "Deploying crowdcountingapp..."

    C31_flag=`find $HOME/AscendProjects -maxdepth 1 -name "sample-crowdcounting" 2> /dev/null`
    if [[ $C31_flag ]];then
        read -p "[INFO] The sample-crowdcounting already exists. Do you want to replace it? [Y/N]:" response
        if [ $response"z" = "Nz" ] || [ $response"z" = "nz" ]; then
            echo "Exit prepareing"
            return 1
        elif [ $response"z" = "Yz" ] || [ $response"z" = "yz" ] || [ $response"z" = "z" ]; then
            rm -rf $HOME/AscendProjects/sample-crowdcounting
            if [[ $? -ne 0 ]];then
                echo "[ERROR] Execute rm command failed. Please manually delete $HOME/AscendProjects/sample-crowdcounting director and re-execute this script."
                return 1
            fi
        else
            echo "[ERROR] Please input Y/N!"
            return 1
        fi
    fi

    mkdir $HOME/AscendProjects/sample-crowdcounting
    if [[ $? -ne 0 ]];then
        echo "[ERROR] Execute mkdir command failed. Please make sure you have the right permission."
        return 1
    fi

    git clone https://gitee.com/Atlas200DK/sample-crowdcounting.git $HOME/AscendProjects/sample-crowdcounting --branch 1.3x.0.0
    if [[ $? -ne 0 ]];then
        echo "[ERROR] Git clone failed. Please check your network connection."
        return 1
    fi

    download "crowd_counting" "0"

    echo "[INFO] Please follow the link from the 编译 step in Readme to continue running the case.(https://gitee.com/Atlas200DK/sample-crowdcounting/tree/1.3x.0.0/)"
}
main
