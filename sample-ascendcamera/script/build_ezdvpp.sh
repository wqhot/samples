#!/bin/bash

script_path="$( cd "$(dirname ${BASH_SOURCE})" ; pwd -P )"
remote_host=$1
ezdvpp_version="1.2.0"
DEVICE_LIB_PATH="${HOME}/ascend_ddk/device/lib"
AGENT_PATH="${HOME}/ascend_ddk"
SAMPLES_PATH="${HOME}/AscendProjects/samples/common"

. ${script_path}/func_util.sh
function download_code()
{
    if [ -d ${AGENT_PATH}/ezdvpp ];then
        echo "EZdvpp code if found..."
        return 0
    else
        echo "remove ezdvpp code..."
		cp -rf ${SAMPLES_PATH}/sdk-ezdvpp ${AGENT_PATH}
       
		mkdir -p ${AGENT_PATH}/ezdvpp
		mv ${AGENT_PATH}/sdk-ezdvpp/* ${AGENT_PATH}/ezdvpp
		rm -rf ${AGENT_PATH}/sdk-ezdvpp
		
		if [[ $? -ne 0 ]];then
            echo "ERROR: remove failed, please check "${HOME}/ascend/AscendProjects/samples" file ."
            return 1
        fi
    fi
	   
    return 0
}

function build_ezdvpp()
{
    echo "Build ezdvpp..."
    if [ -e "${AGENT_PATH}/ezdvpp/out/libascend_ezdvpp.so" ];then
        echo "EZdvpp so is found.."
        return 0
    fi

    ezdvpp_path=`find $DDK_HOME/../RC -maxdepth 3 -name "libDvpp_api.so" 2> /dev/null`
    if [[ ! ${ezdvpp_path} ]];then
        echo "[ERROR]libDvpp so can not found"
    fi
    ezdvpp_dir_path=`dirname $ezdvpp_path`
    export NPU_DEV_LIB=${ezdvpp_dir_path}
    
    make clean -C ${AGENT_PATH}/ezdvpp 1>/dev/null
    if [[ $? -ne 0 ]];then
        echo "ERROR: compile ezdvpp failed, please check the env."
        return 1
    fi

    make install -C ${AGENT_PATH}/ezdvpp 1>/dev/null
    if [[ $? -ne 0 ]];then
        echo "ERROR: compile ezdvpp failed, please check the env."
        return 1
    fi
}

main()
{
    #download code
    download_code
    if [[ $? -ne 0 ]];then
        return 1
    fi
    build_ezdvpp
    if [[ $? -ne 0 ]];then
        return 1
    fi
    echo "Finish to Build ezdvpp."
		
    echo "Start to deploy ezdvpp"
    upload_file "${DEVICE_LIB_PATH}/libascend_ezdvpp.so" "~/HIAI_PROJECTS/ascend_lib"
    if [ $? -ne 0 ];then
        return 1
    fi
    echo "Finish to deploy ezdvpp"
    return 0
}
main


