#!/bin/bash

main()
{
    echo "Deploying ascendcameraapp..."

    C31_flag=`find $HOME/AscendProjects -maxdepth 1 -name "sample-ascendcamera" 2> /dev/null`
    if [[ $C31_flag ]];then
        read -p "[INFO] The sample-ascendcamera already exists. Do you want to replace it? [Y/N]:" response
        if [ $response"z" = "Nz" ] || [ $response"z" = "nz" ]; then
            echo "Exit prepareing"
            return 1
        elif [ $response"z" = "Yz" ] || [ $response"z" = "yz" ] || [ $response"z" = "z" ]; then
            rm -rf $HOME/AscendProjects/sample-ascendcamera
            if [[ $? -ne 0 ]];then
                echo "[ERROR] Execute rm command failed. Please manually delete $HOME/AscendProjects/sample-ascendcamera director and re-execute this script."
                return 1
            fi
        else
            echo "[ERROR] Please input Y/N!"
            return 1
        fi
    fi

    mkdir $HOME/AscendProjects/sample-ascendcamera
    if [[ $? -ne 0 ]];then
        echo "[ERROR] Execute mkdir command failed. Please make sure you have the right permission."
        return 1
    fi

	cp -r $HOME/AscendProjects/samples/sample-ascendcamera $HOME/AscendProjects/
    if [[ $? -ne 0 ]];then
        echo "[ERROR] Git clone failed. Please check your network connection."
        return 1
    fi 
    echo "[INFO] Please follow the link from the compile step in Readme to continue running the case.(https://gitee.com/ascend/samples.git)"
}
main
