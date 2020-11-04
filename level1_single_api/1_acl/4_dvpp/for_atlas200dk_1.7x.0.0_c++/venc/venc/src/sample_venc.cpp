#include <cstdio>
#include <stdlib.h>

#include "acl/acl.h"
#include "acl/ops/acl_dvpp.h"
#include "sample_venc.h"
#include "utils.h"
#include "camera.h"
using namespace std;

const uint32_t inputWidth_ = 704;
const uint32_t inputHeight_ = 576;
const uint32_t cameraFps_ = 15;

int32_t deviceId_ = 0;
aclrtContext context_;
aclrtStream stream_;
pthread_t threadId_;
FILE *outFileFp_;

acldvppPixelFormat format_ = PIXEL_FORMAT_YUV_SEMIPLANAR_420; // 1：YUV420 semi-planner（nv12）; 2：YVU420 semi-planner（nv21）

/* 0：H265 main level
 * 1：H264 baseline level
 * 2：H264 main level
 * 3：H264 high level
 */
int32_t enType_ = 0;

aclvencChannelDesc *vencChannelDesc_;
aclvencFrameConfig *vencFrameConfig_;
acldvppPicDesc *encodeInputDesc_;
static bool runFlag = true;

uint32_t AlignmentHelper(uint32_t origSize, uint32_t alignment)
{
    if (alignment == 0) {
        return 0;
    }
    uint32_t alignmentH = alignment - 1;
    return (origSize + alignmentH) / alignment * alignment;
}

string getTime()
{
    time_t timep;
    time (& timep);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y%m%d%H%M%S", localtime(&timep));
    return tmp;
}

bool ReadFileToDeviceMem(const char *fileName, void *&dataDev, uint32_t &dataSize)
{
    // read data from file.
    FILE *fp = fopen(fileName, "rb+");
    if(fp == nullptr)
    {
        ERROR_LOG("Failed to open  file %s.", fileName);
        return FAILED;
    }

    fseek(fp, 0, SEEK_END);
    long fileLenLong = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    auto fileLen = static_cast<uint32_t>(fileLenLong);

    dataSize = fileLen;
    // Malloc input device memory
    auto aclRet = acldvppMalloc(&dataDev, dataSize);

    size_t readSize = fread(dataDev, 1, fileLen, fp);
    if (readSize < fileLen) {
        free(dataDev);
		fclose(fp); 
        return false;
    }

    free(dataDev);
	fclose(fp); 
    return true;
}

void *ThreadFunc(void *arg)
{
    // Notice: create context for this thread
    int deviceId = 0;
    aclrtContext context = nullptr;
    aclError ret = aclrtCreateContext(&context, deviceId);
    while (runFlag) {
        // Notice: timeout 1000ms
        aclError aclRet = aclrtProcessReport(1000);
    }

    ret = aclrtDestroyContext(context);
    return (void*)0;
}

bool WriteToFile(FILE *outFileFp_, const void *dataDev, uint32_t dataSize)
{

    bool ret = true;
    size_t writeRet = fwrite(dataDev, 1, dataSize, outFileFp_);
    if (writeRet != dataSize) {
        ret = false;
    }
    fflush(outFileFp_);

    return ret;
}

//3.Create callback functions
void callback(acldvppPicDesc *input, acldvppStreamDesc *output, void *userdata)
{
    //Get the output memory encoded by VENC, and call  WriteToFile to write the data in the output 
	  memory to the file
    void *vdecOutBufferDev = acldvppGetStreamDescData(output);
    uint32_t size = acldvppGetStreamDescSize(output);
 
    if (!WriteToFile(outFileFp_, vdecOutBufferDev, size)) {
        ERROR_LOG("write file failed.");
    }

    INFO_LOG("Write a picture size %d ", size);
}

bool setupVencDesc(int inputWidth, int inputHeight)
{
    aclError ret;
    /*4.Set the properties of the channel description information when creating the video code
	 stream processing channel, in which the callback callback function needs to be created in 
	 advance by the user.*/
    //vencChannelDesc_ is aclvencChannelDesc type
    vencChannelDesc_ = aclvencCreateChannelDesc();

    ret = aclvencSetChannelDescThreadId(vencChannelDesc_, threadId_);
    /* Sets the callback function*/
    ret = aclvencSetChannelDescCallback(vencChannelDesc_, callback);

    //The H265_MAIN_LEVEL video encoding protocol is used in the example
    ret = aclvencSetChannelDescEnType(vencChannelDesc_, static_cast<acldvppStreamFormat>(enType_));
    //PIXEL_FORMAT_YVU_SEMIPLANAR_420 is used in the example
    ret = aclvencSetChannelDescPicFormat(vencChannelDesc_, format_);
    ret = aclvencSetChannelDescPicWidth(vencChannelDesc_, inputWidth);
    ret = aclvencSetChannelDescPicHeight(vencChannelDesc_, inputHeight);
    ret = aclvencSetChannelDescKeyFrameInterval(vencChannelDesc_, 1);

    /* 5.Create video stream processing channel */
    ret = aclvencCreateChannel(vencChannelDesc_);

    //6. Create the description information of the coded input image and set the value of each property
    //encodeInputDesc_ is acldvppPicDesc
    uint32_t widthAlignment = 16;
    uint32_t heightAlignment = 2;
    uint32_t encodeInHeightStride = AlignmentHelper(inputHeight, heightAlignment);
    uint32_t encodeInWidthStride = AlignmentHelper(inputWidth, widthAlignment);
    if (encodeInWidthStride == 0 || encodeInHeightStride == 0) {
        ERROR_LOG("InitEncodeInputDesc AlignmentHelper failed");
        return FAILED;
    }
    
    encodeInputDesc_ = acldvppCreatePicDesc();
    if (encodeInputDesc_ == nullptr) {
        ERROR_LOG("acldvppCreatePicDesc encodeInputDesc_ failed");
        return FAILED;
    }

    acldvppSetPicDescFormat(encodeInputDesc_, PIXEL_FORMAT_YUV_SEMIPLANAR_420);
    acldvppSetPicDescWidth(encodeInputDesc_, inputWidth);
    acldvppSetPicDescHeight(encodeInputDesc_, inputHeight);
    acldvppSetPicDescWidthStride(encodeInputDesc_, encodeInWidthStride);
    acldvppSetPicDescHeightStride(encodeInputDesc_, encodeInHeightStride);
	
	/*Create aclvencFrameConfig type of data, create the single frame encoding configuration parameter
	 when VENC encoding.*/
    vencFrameConfig_ = aclvencCreateFrameConfig();
    aclvencSetFrameConfigForceIFrame(vencFrameConfig_, 0);

    return SUCCESS;
}


int main(int argc, char *argv[]) {
    bool bSetChannelId = true;
    int channelId = 0;  //camera port

    //Check the input during application execution, which requires camera channel input
    if((argc < 2) || (argv[1] == nullptr)){
        ERROR_LOG("Please input: ./main ChannelID");
        bSetChannelId =false;
    }

    //Get the Camera Channel ID
    if(bSetChannelId)
    {
        string channelName = string(argv[1]);
        Utils::GetChannelID(channelName, channelId);
        if(0xFF == channelId){
            ERROR_LOG("channelId = %d  ERROR \n", channelId);
            return FAILED;
        }
    }

    Camera  cameraDevice(channelId, cameraFps_, inputWidth_, inputHeight_);
    if(false == cameraDevice.IsOpened(channelId))
    {
        if (cameraDevice.Open(channelId)) {
            ERROR_LOG("Failed to open channelId =%d.", channelId);
            return FAILED;
        }
    }

    /* 1. ACL initialization */
    char aclConfigPath[32] = {'\0'};
    aclError ret = aclInit(aclConfigPath);

    /* 2. Run the management resource application, including Device, Context, Stream */
    ret = aclrtSetDevice(deviceId_);
    ret = aclrtCreateContext(&context_, deviceId_);
    ret = aclrtCreateStream(&stream_);

    /* 3. VDEC resource initialization */
    // create threadId
    pthread_create(&threadId_, nullptr, ThreadFunc, nullptr);
    (void)aclrtSubscribeReport(static_cast<uint64_t>(threadId_), stream_);

    setupVencDesc(inputWidth_, inputHeight_);

    string fileName = getTime();

    if(enType_ == H265_MAIN_LEVEL)
    {
        fileName += ".h265";
    }
    else
    {
        fileName += ".h264";
    }

    outFileFp_ = fopen(fileName.c_str(), "ab");
    if(outFileFp_ == nullptr)
    {
        ERROR_LOG("Failed to open  file %s.", fileName.c_str());
        return FAILED;
    }

	
    int restLen = 100;
    //Picture by picture
    ImageData image;
	
    while(restLen)
    {
        cameraDevice.Read(channelId, image);
        if (image.data == nullptr) {
            ERROR_LOG("Read image %d failed", channelId);
			fclose(outFileFp_);
            return FAILED;
        }
        INFO_LOG("Camera image width %d, Camera image height %d ", image.alignWidth, image.alignHeight);
        acldvppSetPicDescData(encodeInputDesc_, reinterpret_cast<void *>(image.data.get()));
        acldvppSetPicDescSize(encodeInputDesc_, image.size);
        /* The system automatically calls callback callback function to write the encoded data to the file 
		    after executing the video stream encoding, and then releases the related resources in time*/
        ret = aclvencSendFrame(vencChannelDesc_, encodeInputDesc_, nullptr, vencFrameConfig_, nullptr);
        restLen = restLen - 1;
    }

    if(true == cameraDevice.IsOpened(channelId))
    {
        INFO_LOG("camera device is opened");
        if (cameraDevice.Close(channelId)) {
            ERROR_LOG("Failed to Close channelId =%d.", channelId);			
			fclose(outFileFp_);
            return FAILED;
        }
    }

    aclvencDestroyFrameConfig(vencFrameConfig_);

    ret = aclvencDestroyChannel(vencChannelDesc_);
    aclvencDestroyChannelDesc(vencChannelDesc_);
    vencChannelDesc_ = nullptr;
    (void)aclrtUnSubscribeReport(static_cast<uint64_t>(threadId_), stream_);

    // destory thread
    runFlag = false;
    void *res = nullptr;
    pthread_join(threadId_, &res);
	
	fclose(outFileFp_);
	
    ret = aclrtDestroyStream(stream_);
    stream_ = nullptr;
    ret = aclrtDestroyContext(context_);
    context_ = nullptr;
    ret = aclrtResetDevice(deviceId_);
    ret = aclFinalize();

    INFO_LOG("Execute sample success");
    return SUCCESS;
}




