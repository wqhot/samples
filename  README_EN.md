English|[中文](README.md)

# samples

#### introduce
Ascend Sample, please go to the appropriate folder for your application, or click the description link below to select the application you want.

The developers submitted samples including source code, README, reference model License files, compiled deployment scripts (optional), test cases, and README, and followed the following standards

- The source code
Sample implemented C++ code or python code

- readme
readme  To guide the user in understanding and deploying the sample, include the following:

Brief introduction:

1. Principle of the case, including network structure and application frame diagram;

2. Sample code architecture and implementation process description;

Key requirements:

1. Source of the model, requirements on data, disclaimer, etc.;

2. Model transformation methods, steps and key parameters;

3. Requirements for input data of offline model obtained from model transformation;

4. Case compilation and operation method;

5. Apply deployment environment configuration, including environment variable Settings, dependent third-party software packages and libraries, and installation methods;

6. Application of reasoning accuracy and performance requirements: as far as possible to the original model level.


Advice:

1. The case can be optimized (optional).

- license files

The Sample warehouse USES the Apache License 2.0. If there is no reference to other open source projects in the project, a separate License is not required. If there is a reference to a non-Apache License 2.0 project, please provide the corresponding License in the code.

- Code compilation scripts

If the project requires command line compilation, you need to provide the compilation script and run it correctly

- Sample deployment and running scripts

If the project requires command line deployment, the deployment script needs to be provided and run correctly

- Test cases and test case README

Provide test cases and README



#### Programming specification

- Specifications and standards

1. C + + code to follow Google programming specification: [Google c + + Coding Guidelines] (http://google.github.io/styleguide/cppguide.html).
Unit test tests follow specifications: [Googletest Primer] (https://github.com/google/googletest/blob/master/googletest/docs/primer.md).

2. Python code follows PEP8 specification: [Python PEP8 Coding Style](https://pep8.org/);
Unit test follow specifications: [pytest] (http://www.pytest.org/en/latest/)

- Specification remarks

1. Use string first, avoid char*;
2. Prohibit the use of printf and use cout uniformly;
3. Try to use smart Pointers in memory management;
4. Do not call exit in the function;
5. Do not use tools such as IDE to automatically generate code;
6. Control third-party library dependencies. If third-party dependencies are introduced, instructions for installation and use of third-party dependencies shall be provided;
7. English comments should be used all the time, and the rate of comments is 30%-40%. Self-comments are encouraged.
8. The function header must be annotated to explain the function, input and output;
9. Unified error code, through which error code can confirm that the branch returns an error;
10. Prohibit the printing of a pile of logs with no impact error level;

#### Directions for use

1. - [for_atlas200dk_1 32.0.0 _common] (https://gitee.com/ascend/samples/tree/1.32.0.0/common) : common stored inside the faster - - the deploy, sample - README, the SDK - ezdvpp, SDK - presenter, respectively used for rapid deployment of the sample and compile ezdvpp and presenter of deployment.
2. - [for_atlas200dk_1 32.0.0 _sample - ascendcamera] (https://gitee.com/ascend/samples/tree/1.32.0.0/sample-ascendcamera) : Ascend Camera main function is through plate cameras to collect data on the Atlas 200 DK developers, after DVPP converted to JPG, then saved as a file or a remote output.
3. - [for_atlas200dk_1 32.0.0 _sample - carplaterecognition] (https://gitee.com/ascend/samples/tree/1.32.0.0/sample-carplaterecognition) : developers of this application can be deployed to the Atlas 200 dk of camera data real-time acquisition, and the forecast of vehicle license plate in the video information function.
Affected by the model, the accuracy is low. If the accuracy needs to be improved, the training model can be replaced by yourself.
4. - [for_atlas200dk_1 32.0.0 _sample - classification] (https://gitee.com/ascend/samples/tree/1.32.0.0/sample-classification) : the Application supports running in Atlas 200 DK or AI to accelerate cloud servers, can realize the function of the classification of the common network reasoning and output before n reasoning results.
5. - [for_atlas200dk_1 32.0.0 _sample - colorization] (https://gitee.com/ascend/samples/tree/1.32.0.0/sample-colorization) : this application support to run on the Atlas 200 DK, realized the function of automatic color of black and white image.
6. - [for_atlas200dk_1 32.0.0 _sample - facedetection] (https://gitee.com/ascend/samples/tree/1.32.0.0/sample-facedetection) : developers of this application can be deployed to the Atlas 200 dk for camera, real-time data acquisition, and to predict the function of the face in the video information.
7. - [for_atlas200dk_1 32.0.0 _sample - facialrecognition] (https://gitee.com/ascend/samples/tree/1.32.0.0/sample-facialrecognition) :
Developers can deploy this Application to the Atlas 200 DK to realize face registration, and predict the face information in the video through the camera, compare it with the registered face, and predict the most likely user.
8. - [for_atlas200dk_1 32.0.0 _sample headposeestimation - python] (https://gitee.com/ascend/samples/tree/1.32.0.0/sample-headposeestimation-python) :
The developer will deploy the application to the Atlas 200 DK or AI accelerated cloud Server to decode the local MP4 file or RTSP video stream, estimate the head position of the face image in the video frame, and send the predicted result information to the Presenter Server for display.
9. - [for_atlas200dk_1 32.0.0 _sample - objectdetection] (https://gitee.com/ascend/samples/tree/1.32.0.0/sample-objectdetection) : the Application supports running in Atlas 200 DK or AI to accelerate cloud server, to achieve the goal of faster - - RCNN detect network reasoning function.
10. - [for_atlas200dk_1 32.0.0 _sample - objectdetectionbyyolov3] (https://gitee.com/ascend/samples/tree/1.32.0.0/sample-objectdetectionbyyolov3) :
This Application support runs on Atlas 200 DK or AI accelerated cloud server, realizing the reasoning function of yolov3 target detection network.
11. - [for_atlas200dk_1 32.0.0 _sample - segmentation - python] (https://gitee.com/ascend/samples/tree/1.32.0.0/sample-segmentation-python) : the Application supports running on Atlas 200 DK, implements the reasoning function of the network of erfnet and output images with reasoning results.
12. - [for_atlas200dk_1 32.0.0 _sample - videoanalysisperson] (https://gitee.com/ascend/samples/tree/1.32.0.0/sample-videoanalysisperson) :
The developer will deploy the Application to the Atlas 200 DK or AI accelerated cloud Server to decode the local MP4 file or RTSP video stream, detect the pedestrian and face in the video frame and predict their properties, generate structured information and send it to the Server side for preservation and display.

