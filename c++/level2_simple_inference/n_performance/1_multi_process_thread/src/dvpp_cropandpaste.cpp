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

* File dvpp_process.cpp
* Description: handle dvpp process
*/

#include <iostream>
#include "acl/acl.h"
#include "utils.h"
#include "dvpp_cropandpaste.h"
using namespace std;

static int memcount = 0;

DvppCropAndPaste::DvppCropAndPaste(aclrtStream& stream, acldvppChannelDesc *dvppChannelDesc,
                    uint32_t lt_horz, uint32_t lt_vert,uint32_t rb_horz, uint32_t rb_vert)
: stream_(stream), dvppChannelDesc_(dvppChannelDesc),
vpcInputDesc_(nullptr), vpcOutputDesc_(nullptr),
vpcOutBufferDev_(nullptr),vpcOutBufferSize_(0){
    size_.width = rb_horz - lt_horz;
    size_.height = rb_vert - lt_vert;
    cout << "lt_vert = " << lt_vert << endl;
    cout << "lt_horz = " << lt_horz << endl;
    cout << "rb_vert = " << rb_vert << endl;
    cout << "rb_horz = " << rb_horz << endl;
    cout << "size_.width = " << size_.width << endl;
    cout << "size_.height = " << size_.height << endl;
    lt_horz_ = lt_horz;
    rb_horz_ = rb_horz;
    lt_vert_ = lt_vert;
    rb_vert_ = rb_vert;
}

DvppCropAndPaste::~DvppCropAndPaste()
{
    DestroyCropAndPasteResource();
}

Result DvppCropAndPaste::InitCropAndPasteInputDesc(ImageData& inputImage)
{
    originalImageWidth_ = inputImage.width;
    originalImageHeight_ = inputImage.height;
    uint32_t alignWidth = ALIGN_UP128(inputImage.width);
    uint32_t alignHeight = ALIGN_UP16(inputImage.height);
    if (alignWidth == 0 || alignHeight == 0) {
        ERROR_LOG("InitResizeInputDesc AlignmentHelper failed. image w %d, h %d, align w%d, h%d",
         inputImage.width, inputImage.height, alignWidth, alignHeight);
        return FAILED;
    }
    uint32_t inputBufferSize = YUV420SP_SIZE(alignWidth, alignHeight);
    vpcInputDesc_ = acldvppCreatePicDesc();
    if (vpcInputDesc_ == nullptr) {
        ERROR_LOG("acldvppCreatePicDesc vpcInputDesc_ failed");
        return FAILED;
    }

    acldvppSetPicDescData(vpcInputDesc_, inputImage.data.get()); //  JpegD . vpcResize
    acldvppSetPicDescFormat(vpcInputDesc_, format_);
    acldvppSetPicDescWidth(vpcInputDesc_, inputImage.width);
    acldvppSetPicDescHeight(vpcInputDesc_, inputImage.height);
    acldvppSetPicDescWidthStride(vpcInputDesc_, alignWidth);
    acldvppSetPicDescHeightStride(vpcInputDesc_, alignHeight);
    acldvppSetPicDescSize(vpcInputDesc_, inputBufferSize);
    return SUCCESS;
}

Result DvppCropAndPaste::InitCropAndPasteOutputDesc()
{
    int resizeOutWidth = size_.width;
    int resizeOutHeight = size_.height;
    int resizeOutWidthStride = ALIGN_UP16(resizeOutWidth);
    int resizeOutHeightStride = ALIGN_UP2(resizeOutHeight);
    cout << "resizeOutWidthStride = " << resizeOutWidthStride << endl;
    cout << "resizeOutHeightStride = " << resizeOutHeightStride << endl;
    if (resizeOutWidthStride == 0 || resizeOutHeightStride == 0) {
        ERROR_LOG("InitResizeOutputDesc AlignmentHelper failed");
        return FAILED;
    }

    vpcOutBufferSize_ = YUV420SP_SIZE(resizeOutWidthStride, resizeOutHeightStride);

    aclError aclRet = acldvppMalloc(&vpcOutBufferDev_, vpcOutBufferSize_);
    if (aclRet != ACL_ERROR_NONE) {
        ERROR_LOG("acldvppMalloc vpcOutBufferDev_ failed, aclRet = %d", aclRet);
        return FAILED;
    }
    memcount ++;
    //INFO_LOG("DvppCropAndPaste malloc RESIZEMALLOC\n");

    vpcOutputDesc_ = acldvppCreatePicDesc();
    if (vpcOutputDesc_ == nullptr) {
        ERROR_LOG("acldvppCreatePicDesc vpcOutputDesc_ failed");
        return FAILED;
    }
    acldvppSetPicDescData(vpcOutputDesc_, vpcOutBufferDev_);
    acldvppSetPicDescFormat(vpcOutputDesc_, format_);
    acldvppSetPicDescWidth(vpcOutputDesc_, resizeOutWidth);
    acldvppSetPicDescHeight(vpcOutputDesc_, resizeOutHeight);
    acldvppSetPicDescWidthStride(vpcOutputDesc_, resizeOutWidthStride);
    acldvppSetPicDescHeightStride(vpcOutputDesc_, resizeOutHeightStride);
    acldvppSetPicDescSize(vpcOutputDesc_, vpcOutBufferSize_);

    return SUCCESS;
}


// IN/OUT Desc
Result DvppCropAndPaste::InitCropAndPasteResource(ImageData& inputImage) {
    format_ = static_cast<acldvppPixelFormat>(PIXEL_FORMAT_YUV_SEMIPLANAR_420);
    if (SUCCESS != InitCropAndPasteInputDesc(inputImage)) {
        ERROR_LOG("InitCropAndPasteInputDesc failed");
        return FAILED;
    }

    if (SUCCESS != InitCropAndPasteOutputDesc()) {
        ERROR_LOG("InitCropAndPasteOutputDesc failed");
        return FAILED;
    }

    return SUCCESS;
}

#define SHARED_PRT_CROP_DVPP_BUF(buf) (shared_ptr<uint8_t>((uint8_t *)(buf), [](uint8_t* p) { memcount--; INFO_LOG("DvppCropAndPaste free RESIZEMALLOC memcount %d\n", memcount); acldvppFree(p); }))


Result DvppCropAndPaste::Process(ImageData& resizedImage, ImageData& srcImage)
{
    if (SUCCESS != InitCropAndPasteResource(srcImage)) {
        ERROR_LOG("Dvpp cropandpaste failed for init error");
        return FAILED;
    }

    // must even
    uint32_t cropLeftOffset = lt_horz_;
    // must even
    uint32_t cropTopOffset = lt_vert_;
    // must odd
    uint32_t cropRightOffset = rb_horz_;
    // must odd
    uint32_t cropBottomOffset = rb_vert_;

    cropArea_ = acldvppCreateRoiConfig(cropLeftOffset, cropRightOffset,
    cropTopOffset, cropBottomOffset);
    if (cropArea_ == nullptr) {
        ERROR_LOG("acldvppCreateRoiConfig cropArea_ failed");
        return FAILED;
    }

    // must even
    uint32_t pasteLeftOffset = 0;
    // must even
    uint32_t pasteTopOffset = 0;
    // must odd
    uint32_t pasteRightOffset = size_.width;
    // must odd
    uint32_t pasteBottomOffset = size_.height;

    pasteArea_ = acldvppCreateRoiConfig(pasteLeftOffset, pasteRightOffset,
    pasteTopOffset, pasteBottomOffset);
    if (pasteArea_ == nullptr) {
        ERROR_LOG("acldvppCreateRoiConfig pasteArea_ failed");
        return FAILED;
    }

    // crop and patse pic
    //TODO:
    aclError aclRet = acldvppVpcCropAndPasteAsync(dvppChannelDesc_, vpcInputDesc_,
    vpcOutputDesc_, cropArea_, pasteArea_, stream_);
    if (aclRet != ACL_ERROR_NONE) {
        ERROR_LOG("acldvppVpcCropAndPasteAsync failed, aclRet = %d", aclRet);
        return FAILED;
    }

    aclRet = aclrtSynchronizeStream(stream_);
    if (aclRet != ACL_ERROR_NONE) {
        ERROR_LOG("crop and paste aclrtSynchronizeStream failed, aclRet = %d", aclRet);
        return FAILED;
    }

    resizedImage.width = size_.width;
    resizedImage.height = size_.height;
    resizedImage.alignWidth = ALIGN_UP16(size_.width);
    resizedImage.alignHeight = ALIGN_UP2(size_.height);
    resizedImage.size = vpcOutBufferSize_;
    //resizedImage.data = SHARED_PRT_DVPP_BUF(vpcOutBufferDev_);
    resizedImage.data = SHARED_PRT_CROP_DVPP_BUF(vpcOutBufferDev_);

    DestroyCropAndPasteResource();

    return SUCCESS;
}

void DvppCropAndPaste::DestroyCropAndPasteResource()
{
    if (cropArea_ != nullptr) {
        (void)acldvppDestroyRoiConfig(cropArea_);
        cropArea_ = nullptr;
    }

    if (pasteArea_ != nullptr) {
        (void)acldvppDestroyRoiConfig(pasteArea_);
        pasteArea_ = nullptr;
    }

    if (vpcInputDesc_ != nullptr) {
        (void)acldvppDestroyPicDesc(vpcInputDesc_);
        vpcInputDesc_ = nullptr;
    }

    if (vpcOutputDesc_ != nullptr) {
        (void)acldvppDestroyPicDesc(vpcOutputDesc_);
        vpcOutputDesc_ = nullptr;
    }
}
