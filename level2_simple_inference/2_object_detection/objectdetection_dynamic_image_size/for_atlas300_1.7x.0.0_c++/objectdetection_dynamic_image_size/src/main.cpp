/**
* Copyright 2020 Huawei Technologies Co., Ltd
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at

* http://www.apache.org/licenses/LICENSE-2.0

* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.

* File main.cpp
* Description: dvpp sample main func
*/

#include <iostream>
#include <stdlib.h>
#include <dirent.h>
#include <vector>
#include <map>

#include "object_detect.h"
#include "utils.h"
using namespace std;

namespace {
uint32_t kModelWidth = 512;
uint32_t kModelHeight = 512;
map <uint32_t, uint32_t> resizeWidthHeight = {
    {416,416},
    {512,512}
};


const char* kModelPath = "../model/faster_rcnn.om";
}

int main(int argc, char *argv[]) {
    //Check the input during application execution, which requires the input of picture directory parameters
    if((argc < 2) || (argv[1] == nullptr)) {
        ERROR_LOG("Please input: ./main <image_dir>");
        return FAILED;
    }
    /*The target detection object is instantiated, the parameter is the classification model path, and the 
	width and height of the model input are required*/
    ObjectDetect detect(kModelPath, kModelWidth, kModelHeight);
    //Initializes the ACL resources, models, and memory for categorizing inferences
    Result ret = detect.Init();
    if (ret != SUCCESS) {
        ERROR_LOG("ObjectDetect Init resource failed");
        return FAILED;
    }

    //Gets the file names of all images in the image directory
    string inputImageDir = string(argv[1]);
    vector<string> fileVec;
    Utils::GetAllFiles(inputImageDir, fileVec);
    if (fileVec.empty()) {
        ERROR_LOG("Failed to deal all empty path=%s.", inputImageDir.c_str());
        return FAILED;
    }

    //Reasoning picture by picture
    ImageData image;
    for (string imageFile : fileVec) {
        static auto it = resizeWidthHeight.begin();

        Utils::ReadImageFile(image, imageFile);
        if (image.data == nullptr) {
            ERROR_LOG("Read image %s failed", imageFile.c_str());
            return FAILED;
        }

        //Preprocessing image: read the image and scale the image to the required size of the model input
        ImageData resizedImage;
        Result ret = detect.Preprocess(resizedImage, image, it->first, it->second);
        if (ret != SUCCESS) {
            ERROR_LOG("Read file %s failed, continue to read next",
                      imageFile.c_str());                
            continue;
        }
        //The preprocessed images are fed into model reasoning and the reasoning results are obtained
        aclmdlDataset* inferenceOutput = nullptr;
        ret = detect.Inference(inferenceOutput, resizedImage);
        if ((ret != SUCCESS) || (inferenceOutput == nullptr)) {
            ERROR_LOG("Inference model inference output data failed");
            return FAILED;
        }
        //Analyze the inference output and mark the inference object type and position on the picture
        ret = detect.Postprocess(image, inferenceOutput, imageFile);
        if (ret != SUCCESS) {
            ERROR_LOG("Process model inference output data failed");
            return FAILED;
        }
        it++;
    }

    INFO_LOG("Execute sample success");
    return SUCCESS;
}
