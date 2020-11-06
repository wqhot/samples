#!/bin/bash
script_path="$HOME/sample-fasterrcnndetection-python/model"
model_path="$HOME/sample-fasterrcnndetection-python/MyModel"
function download()
{
    model_name=$1
    License_OK=$2
    model_shape=`head -1 ${model_path}/shape_${model_name}`
    if [ ! -f "${script_path}/${model_name}.om" ];then
        download_url_caffemodel="https://obs-model-ascend.obs.cn-east-2.myhuaweicloud.com/fast_rcnn/${model_name}.caffemodel"
	    download_url_prototxt="https://obs-model-ascend.obs.cn-east-2.myhuaweicloud.com/fast_rcnn/${model_name}.prototxt"
        download_url_license="https://obs-model-ascend.obs.cn-east-2.myhuaweicloud.com/fast_rcnn/LICENSE"
        wget -O ${model_path}/${model_name}.caffemodel ${download_url_caffemodel} --no-check-certificate
	    wget -O ${model_path}/${model_name}.prototxt ${download_url_prototxt} --no-check-certificate
        if [[ ${License_OK} == "1" ]];then
            wget -O ${model_path}/LICENSEN_${model_name} ${download_url_license} --no-check-certificate
        fi
	    export SLOG_PRINT_TO_STDOUT=1 && export PATH=${PATH}:${DDK_HOME}/uihost/toolchains/ccec-linux/bin/ && export LD_LIBRARY_PATH=${DDK_HOME}/uihost/lib/ && export TVM_AICPU_LIBRARY_PATH=${DDK_HOME}/uihost/lib/:${DDK_HOME}/uihost/toolchains/ccec-linux/aicpu_lib && export TVM_AICPU_INCLUDE_PATH=${DDK_HOME}/include/inc/tensor_engine && export PYTHONPATH=${DDK_HOME}/site-packages && export TVM_AICPU_OS_SYSROOT=/usr/aarch64-linux-gnu && ${DDK_HOME}/uihost/bin/omg --output="${script_path}/${model_name}" --check_report=${model_path}/${model_name}_result.json --plugin_path= --model="${model_path}/${model_name}.prototxt" --framework=0 --ddk_version=${tools_version} --weight="${model_path}/${model_name}.caffemodel" --input_shape=${model_shape} --insert_op_conf=${model_path}/aipp_${model_name}.cfg
	    if [ $? -ne 0 ];then
            echo "ERROR: download failed, please check network connetction."
            return 1
        fi
    else
        echo "${script_path}/${model_name}.om exists, skip downloading."
    fi

    return 0
}

main()
{
    echo "fasterrcnndetectionpythonapp prepareing"

    C31_flag=`find $HOME -maxdepth 1 -name "sample-fasterrcnndetection-python" 2> /dev/null`
    if [[ $C31_flag ]];then
        read -p "[INFO] The sample-fasterrcnndetection-python is existence.Do you want to re-prepare ? [Y/N]: " response
        if [ $response"z" = "Nz" ] || [ $response"z" = "nz" ]; then
            echo "Exit prepareing"
            return 1
        elif [ $response"z" = "Yz" ] || [ $response"z" = "yz" ] || [ $response"z" = "z" ]; then
            echo "[INFO] Please manually delete $HOME/sample-fasterrcnndetection-python director and re-execute this script"
            return 1
        else
            echo "[ERROR] Please input Y/N!"
            return 1
        fi
    fi

    mkdir $HOME/sample-fasterrcnndetection-python
    if [[ $? -ne 0 ]];then
        echo "[ERROR] Execute mkdir command failed, Please check your environment"
        return 1
    fi

    git clone https://gitee.com/Atlas200DK/sample-fasterrcnndetection-python.git $HOME/sample-fasterrcnndetection-python
    if [[ $? -ne 0 ]];then
        echo "[ERROR] Clone faild, Please check your environment"
        return 1
    fi

    download "faster_rcnn"  "0"

}
main
