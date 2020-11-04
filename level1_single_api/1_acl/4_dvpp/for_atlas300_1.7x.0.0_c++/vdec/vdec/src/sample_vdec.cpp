#include "acl/acl.h"
#include "acl/ops/acl_dvpp.h"
#include "sample_vdec.h"

std::string filePath= "../vdec_h265_1frame_rabbit_1280x720.h265";
const int inputWidth = 1280;
const int inputHeight = 720;

int32_t deviceId_;
aclrtContext context_;
aclrtStream stream_;
pthread_t threadId_;
char *outFolder;
PicDesc picDesc_;

int32_t format_ = 1; // 1：YUV420 semi-planner（nv12）; 2：YVU420 semi-planner（nv21）

    /* 0：H265 main level
     * 1：H264 baseline level
     * 2：H264 main level
     * 3：H264 high level
     */
int32_t enType_ =0 ;

aclvdecChannelDesc *vdecChannelDesc_;
acldvppStreamDesc *streamInputDesc_;
acldvppPicDesc *picOutputDesc_;
void *picOutBufferDev_;
void *inBufferDev_;
uint32_t inBufferSize_;
static bool runFlag = true;

bool ReadFileToDeviceMem(const char *fileName, void *&dataDev, uint32_t &dataSize)
{
    // read data from file.
    FILE *fp = fopen(fileName, "rb+");

    fseek(fp, 0, SEEK_END);
    long fileLenLong = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    auto fileLen = static_cast<uint32_t>(fileLenLong);
    void *dataHost = malloc(fileLen);

    size_t readSize = fread(dataHost, 1, fileLen, fp);
    if (readSize < fileLen) {
        free(dataHost);		
		fclose(fp); 
        return false;
    }

    dataSize = fileLen;
    // Malloc input device memory
    auto aclRet = acldvppMalloc(&dataDev, dataSize);
    // copy input to device memory
    aclRet = aclrtMemcpy(dataDev, dataSize, dataHost, fileLen, ACL_MEMCPY_HOST_TO_DEVICE);
    free(dataHost);
		
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
bool WriteToFile(const char *fileName, const void *dataDev, uint32_t dataSize)
{
    void *dataHost = malloc(dataSize);
    if (dataHost == nullptr) {
        ERROR_LOG("malloc host data buffer failed. dataSize=%u\n", dataSize);
        return false;
    }

    // copy output to host memory
    auto aclRet = aclrtMemcpy(dataHost, dataSize, dataDev, dataSize, ACL_MEMCPY_DEVICE_TO_HOST);

    FILE *outFileFp = fopen(fileName, "wb+");

    bool ret = true;
    size_t writeRet = fwrite(dataHost, 1, dataSize, outFileFp);
    if (writeRet != dataSize) {
        ret = false;
    }
    free(dataHost);
    fflush(outFileFp);
    fclose(outFileFp);
    return ret;
}

//3. Create callback functions
void callback(acldvppStreamDesc *input, acldvppPicDesc *output, void *userdata)
{
    /*Get the output memory decoded by VDEC, call the custom function WriteToFile to write 
	the data in the output memory to the file, and then call the acldvppFree interface to release
	 the output memory*/
    void *vdecOutBufferDev = acldvppGetPicDescData(output);
    uint32_t size = acldvppGetPicDescSize(output);
    static int count = 1;
    std::string fileNameSave = "image" + std::to_string(count);
    if (!WriteToFile(fileNameSave.c_str(), vdecOutBufferDev, size)) {
        ERROR_LOG("write file failed.");
    }
    aclError ret = acldvppFree(reinterpret_cast<void *>(vdecOutBufferDev));
    // Release acldvppPicDesc type data, representing output picture description data after decoding
    ret = acldvppDestroyPicDesc(output);
	
    //......
    count++;
}

int main()
{	
	/* 1. ACL initialization */	
    const char *aclConfigPath = "../acl.json";
    aclError ret = aclInit(aclConfigPath);
	
	/* 2. Run the management resource application, including Device, Context, Stream */	
    ret = aclrtSetDevice(deviceId_);
    ret = aclrtCreateContext(&context_, deviceId_);
    ret = aclrtCreateStream(&stream_);
		
	/* 3. VDEC resource initialization */	
	// create threadId
    pthread_create(&threadId_, nullptr, ThreadFunc, nullptr);
    (void)aclrtSubscribeReport(static_cast<uint64_t>(threadId_), stream_);
	
	/*4.Set the properties of the channel description information when creating the video code stream
	 processing channel, in which the callback callback function needs to be created in advance by the
	  user.*/
	//vdecChannelDesc_ is aclvdecChannelDesc
	vdecChannelDesc_ = aclvdecCreateChannelDesc();
	
	// channelId: 0-15
	ret = aclvdecSetChannelDescChannelId(vdecChannelDesc_, 10);
	ret = aclvdecSetChannelDescThreadId(vdecChannelDesc_, threadId_);
	/* Sets the callback function*/
	ret = aclvdecSetChannelDescCallback(vdecChannelDesc_, callback);
	
	//The H265_MAIN_LEVEL video encoding protocol is used in the example
	ret = aclvdecSetChannelDescEnType(vdecChannelDesc_, static_cast<acldvppStreamFormat>(enType_));
	//PIXEL_FORMAT_YVU_SEMIPLANAR_420 is used in the example
	ret = aclvdecSetChannelDescOutPicFormat(vdecChannelDesc_, static_cast<acldvppPixelFormat>(format_));

	/* 5.Create video stream processing channel */
	ret = aclvdecCreateChannel(vdecChannelDesc_);
	
	/* Video decoding processing */
    int rest_len = 10;
    void *inBufferDev = nullptr;
    uint32_t inBufferSize = 0;
    size_t DataSize = (inputWidth * inputHeight * 3) / 2;

    // read file to device memory
    ReadFileToDeviceMem(filePath.c_str(), inBufferDev, inBufferSize);
	
	
 	// Create input video stream description information, set the properties of the stream information
	streamInputDesc_ = acldvppCreateStreamDesc(); 
    while (rest_len > 0) {
		
		//inBufferDev_ means the memory for input video data by Device, and inBufferSize_ means the memory size 
		ret = acldvppSetStreamDescData(streamInputDesc_, inBufferDev);
		ret = acldvppSetStreamDescSize(streamInputDesc_, inBufferSize);

		//Device memory picOutBufferDev_ is used to store output data decoded by VDEC
		ret = acldvppMalloc(&picOutBufferDev_, DataSize);

		//Create output image description information, set the image description information properties
		//PicOutputDesc_ is acldvppPicDesc
		picOutputDesc_ = acldvppCreatePicDesc();
		ret = acldvppSetPicDescData(picOutputDesc_, picOutBufferDev_);
		ret = acldvppSetPicDescSize(picOutputDesc_, DataSize);
		ret = acldvppSetPicDescFormat(picOutputDesc_, static_cast<acldvppPixelFormat>(format_));

		/* Perform video stream decoding. After decoding each frame of data, the system automatically 
		calls callback callback function to write the decoded data to the file, and then timely release
		 relevant resources*/
		ret = aclvdecSendFrame(vdecChannelDesc_, streamInputDesc_, picOutputDesc_, nullptr, nullptr);
		//......
		
		rest_len = rest_len - 1;		
    }
	acldvppFree(inBufferDev);
	
    ret = aclvdecDestroyChannel(vdecChannelDesc_);
    aclvdecDestroyChannelDesc(vdecChannelDesc_);
    vdecChannelDesc_ = nullptr;
	
    (void)aclrtUnSubscribeReport(static_cast<uint64_t>(threadId_), stream_);
	
	ret = acldvppDestroyStreamDesc(streamInputDesc_);
	
    // destory thread
    runFlag = false;
    void *res = nullptr;
    pthread_join(threadId_, &res);
    
    ret = aclrtDestroyStream(stream_);
    stream_ = nullptr;
    ret = aclrtDestroyContext(context_);
    context_ = nullptr;
    ret = aclrtResetDevice(deviceId_);
    ret = aclFinalize();
    return SUCCESS;
}
