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

* File sample_process.h
* Description: handle acl resource
*/
#pragma once

#include <opencv2/opencv.hpp>
#include "opencv2/imgcodecs/legacy/constants_c.h"
#include "opencv2/imgproc/types_c.h"

#include "utils.h"
#include "acl/acl.h"
#include "model_process.h"
#include <memory>
#include "ascenddk/presenter/agent/presenter_channel.h"

using namespace std;
using namespace ascend::presenter;

/**
* ObjectDetect
*/
class ObjectDetect {
public:
    ObjectDetect(const char* modelPath, uint32_t modelWidth,
    uint32_t modelHeight);
    ~ObjectDetect();
    //Inference initialization
    Result Init();
    //Inference frame picture preprocessing
    Result Preprocess(cv::Mat& frame);
    //Inference frame picture
    Result Inference(aclmdlDataset*& inferenceOutput);
    //Inference output post-processing
    Result Postprocess(cv::Mat& frame, aclmdlDataset* modelOutput);
    
private:
    //Initialize acl resources
    Result InitResource();
    //Load the inference model
    Result InitModel(const char* omModelPath);
    Result CreateModelInputdDataset();
    //Establish a connection with the presenter server
    Result OpenPresenterChannel();
    //Obtain data from model inference output aclmdlDataset to local
    void* GetInferenceOutputItem(uint32_t& itemDataSize,
    aclmdlDataset* inferenceOutput,
    uint32_t idx);
    //Serialize the frame image into a data stream
    void EncodeImage(vector<uint8_t>& encodeImg, cv::Mat& origImg);
    Result SendImage(std::vector<DetectionResult>& detectionResults,
                     cv::Mat& frame);
    //Release requested resources
    void DestroyResource();

private:
    int32_t deviceId_;  //Device id, default is 0
    ModelProcess model_; //Inference model example

    const char* modelPath_; //Offline model file path
    uint32_t modelWidth_;   //Input width required by the model
    uint32_t modelHeight_;  //Model requires high input
    uint32_t imageDataSize_; //Model input data size
    void*    imageDataBuf_;      //Model input data cache
    uint32_t imageInfoSize_;
    void*    imageInfoBuf_;
    aclrtRunMode runMode_;   //Operating mode, that is, the current application is running on atlas200dk or AI1

    Channel* channel_;  //Channel connected to the presenter server
    bool isInited_;     //Initialization flag to prevent the inference instance from being initialized multiple times
};
