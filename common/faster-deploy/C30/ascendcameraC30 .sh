#!/bin/bash
main()
{
    echo "ascendcameraapp prepareing"

    C31_flag=`find $HOME -maxdepth 1 -name "sample-ascendcamera" 2> /dev/null`
    if [[ $C31_flag ]];then
        read -p "[INFO] The sample-ascendcamera is existence.Do you want to re-prepare ? [Y/N]: " response
        if [ $response"z" = "Nz" ] || [ $response"z" = "nz" ]; then
            echo "Exit prepareing"
            return 1
        elif [ $response"z" = "Yz" ] || [ $response"z" = "yz" ] || [ $response"z" = "z" ]; then
            echo "[INFO] Please manually delete $HOME/sample-ascendcamera director and re-execute this script"
            return 1
        else
            echo "[ERROR] Please input Y/N!"
            return 1
        fi
    fi

    mkdir $HOME/sample-ascendcamera
    if [[ $? -ne 0 ]];then
        echo "[ERROR] Execute mkdir command failed, Please check your environment"
        return 1
    fi

    git clone https://gitee.com/Atlas200DK/sample-ascendcamera.git $HOME/sample-ascendcamera
    if [[ $? -ne 0 ]];then
        echo "[ERROR] Clone faild, Please check your environment"
        return 1
    fi
}
main
