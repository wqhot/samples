/**
 * ============================================================================
 *
 * Copyright (C) 2018, Hisilicon Technologies Co., Ltd. All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   1 Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *
 *   2 Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *
 *   3 Neither the names of the copyright holders nor the names of the
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 * ============================================================================
 */

#include "general_post.h"

#include <unistd.h>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

#include "hiaiengine/log.h"
#include "opencv2/opencv.hpp"
#include "opencv2/imgcodecs/legacy/constants_c.h"
#include "opencv2/imgproc/types_c.h"
#include "tool_api.h"

using hiai::Engine;
using namespace std;

namespace {
// callback port (engine port begin with 0)
const uint32_t kSendDataPort = 0;

// sleep interval when queue full (unit:microseconds)
const __useconds_t kSleepInterval = 200000;

// topN result separator
// such as "idx1:value1,idx2:value2,idx3:value3"
const string kTopNIndexSeparator = ":";
const string kTopNValueSeparator = ",";
const string kFileSperator = "/";
// output image prefix
const string kOutputFilePrefix = "out_";
}
// namespace

// register custom data type
//HIAI_REGISTER_DATA_TYPE("EngineTrans", EngineTrans);

HIAI_StatusT GeneralPost::Init(
    const hiai::AIConfig &config,
    const vector<hiai::AIModelDescription> &model_desc) {
  // do noting
  return HIAI_OK;
}

bool GeneralPost::SendSentinel() {
  // can not discard when queue full
  HIAI_StatusT hiai_ret = HIAI_OK;
  shared_ptr<string> sentinel_msg(new (nothrow) string);
  do {
    hiai_ret = SendData(kSendDataPort, "string",
                        static_pointer_cast<void>(sentinel_msg));
    // when queue full, sleep
    if (hiai_ret == HIAI_QUEUE_FULL) {
      HIAI_ENGINE_LOG("queue full, sleep 200ms");
      usleep(kSleepInterval);
    }
  } while (hiai_ret == HIAI_QUEUE_FULL);

  // send failed
  if (hiai_ret != HIAI_OK) {
    HIAI_ENGINE_LOG(HIAI_ENGINE_RUN_ARGS_NOT_RIGHT,
                    "call SendData failed, err_code=%d", hiai_ret);
    return false;
  }
  return true;
}

HIAI_StatusT GeneralPost::ColorizationPostProcess(
    const std::shared_ptr<EngineTrans> &result) {
  string file_path = result->image_info.path;
  cout << "file_path = " <<file_path << endl;
  // check vector
  if (result->inference_res.empty()) {
    ERROR_LOG("Failed to deal file=%s. Reason: inference result empty.",
              file_path.c_str());
    return HIAI_ERROR;
  }

  // only need to get first one
  Output out = result->inference_res[0];

  int32_t size = out.size / sizeof(float);

  // get a channel and b channel result data
  cv::Mat mat_a(56, 56, CV_32FC1, const_cast<float *>((float *)out.data.get()));
  cv::Mat mat_b(56, 56, CV_32FC1, const_cast<float *>((float *)out.data.get()+size/2));

  // pull out L channel in original image
  cv::Mat mat = cv::imread(file_path, CV_LOAD_IMAGE_COLOR);
  mat.convertTo(mat,CV_32FC3);
  mat = 1.0*mat/255;
  cv::cvtColor(mat, mat, CV_BGR2Lab);
  std::vector<cv::Mat> channels;
  cv::split(mat, channels);

  // resize to match size of original image L
  int r = mat.rows;
  int c = mat.cols;
  cv::Mat mat_a_up(r,c,CV_32FC1);
  cv::Mat mat_b_up(r,c,CV_32FC1);
  cv::resize(mat_a, mat_a_up, cv::Size(c,r));
  cv::resize(mat_b, mat_b_up, cv::Size(c,r));

  // result Lab image
  cv::Mat newChannels[3] = {channels[0], mat_a_up, mat_b_up};
  cv::Mat resultImage;
  cv::merge(newChannels, 3, resultImage);

  //convert back to rgb
  cv::cvtColor(resultImage, resultImage, CV_Lab2BGR);

  // generate colorized image
  int pos = file_path.find_last_of(kFileSperator);
  string file_name(file_path.substr(pos + 1));
  cout << "file_name = " << file_name << endl;
  stringstream sstream;
  sstream.str("");
  sstream << result->console_params.output_path << kFileSperator
          << kOutputFilePrefix << file_name;

  string outputPath = sstream.str();
  resultImage = resultImage * 255;
  cv::imwrite(outputPath, resultImage);

  if (size <= 0) {
    ERROR_LOG("Failed to deal file=%s. Reason: inference result size=%d error.",
              file_path.c_str(), size);
    return HIAI_ERROR;
  }

  // transform results
  float *res = new (nothrow) float[size];
  if (res == nullptr) {
    ERROR_LOG("Failed to deal file=%s. Reason: new float array failed.",
              file_path.c_str());
    return HIAI_ERROR;
  }
  errno_t mem_ret = memcpy_s(res, sizeof(float) * size, out.data.get(),
                             out.size);
  if (mem_ret != EOK) {
    delete[] res;
    ERROR_LOG("Failed to deal file=%s. Reason: call memcpy_s failed.",
              file_path.c_str());
    return HIAI_ERROR;
  }

  delete[] res;
  //INFO_LOG("Success to deal file=%s.", file_path.c_str());
  //INFO_LOG("Top index and confidence:%s", top_n_str.c_str())
  return HIAI_OK;
}

HIAI_IMPL_ENGINE_PROCESS("general_post", GeneralPost, INPUT_SIZE) {
  HIAI_StatusT ret = HIAI_OK;

  // check arg0
  if (arg0 == nullptr) {
    ERROR_LOG("Failed to deal file=nothing. Reason: arg0 is empty.");
    return HIAI_ERROR;
  }

  // just send to callback function when finished
  shared_ptr<EngineTrans> result = static_pointer_cast<EngineTrans>(arg0);
  if (result->is_finished) {
    if (SendSentinel()) {
      return HIAI_OK;
    }
    ERROR_LOG("Failed to send finish data. Reason: SendData failed.");
    ERROR_LOG("Please stop this process manually.");
    return HIAI_ERROR;
  }

  // inference failed
  if (result->err_msg.error) {
    ERROR_LOG("%s", result->err_msg.err_msg.c_str());
    return HIAI_ERROR;
  }

  // arrange result
  return ColorizationPostProcess(result);
}
