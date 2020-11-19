# samples

#### 介绍
Ascend sample，请根据自己的需要进入对应文件夹获取应用，或者点击下面的说明链接选择需要的应用。

开发者提交的样例包括源码、readme、参考模型license文件、编译部署脚本（可选）、测试用例和readme，并遵循以下标准

- 源码
样例实现的C++代码或者python代码

- readme
readme用于指导用户理解和部署样例，要包含如下内容：

简介：

1. 案例的原理，包括网络结构和应用框架图；

2. 样例代码架构和实现流程说明；

关键要求：

1. 模型的出处、对数据的要求、免责声明等；

2. 模型转换方法、步骤和关键参数说明；

3. 模型转换得到的离线模型对输入数据的要求；

4. 案例编译运行方法；

5. 应用部署环境配置，包括环境变量设置，依赖的第三方软件包和库，以及安装方法；

6. 应用推理精度和性能要求：尽量达到原始模型水平。


建议：

1. 该案例可优化点（可选）。

- license文件

sample仓使用Apache License 2.0，如项目中未引用其他开源项目则不需要单独提供license，如引用了非Apache License 2.0的项目，请在代码中提供对应license。

- 代码编译脚本

如果工程需要命令行编译，则需要提供编译脚本，并且运行正确

- 样例部署和运行脚本

如果工程需要命令行部署，则需要提供部署脚本，并且运行正确

- 测试用例和测试用例readme

提供测试用例和readme



#### 编程规范

- 规范标准	

1. C++代码遵循google编程规范：[Google C++ Coding Guidelines](http://google.github.io/styleguide/cppguide.html)；单元测测试遵循规范： [Googletest Primer](https://github.com/google/googletest/blob/master/googletest/docs/primer.md)。

2. Python代码遵循PEP8规范：[Python PEP 8 Coding Style](https://pep8.org/)；单元测试遵循规范： [pytest](http://www.pytest.org/en/latest/)

- 规范备注	

1. 优先使用string类型，避免使用char*；
2. 禁止使用printf，一律使用cout；
3. 内存管理尽量使用智能指针；
4. 不准在函数里调用exit；
5. 禁止使用IDE等工具自动生成代码；
6. 控制第三方库依赖，如果引入第三方依赖，则需要提供第三方依赖安装和使用指导书；
7. 一律使用英文注释，注释率30%--40%，鼓励自注释；
8. 函数头必须有注释，说明函数作用，入参、出参；
9. 统一错误码，通过错误码可以确认那个分支返回错误；
10. 禁止出现打印一堆无影响的错误级别的日志；

#### 使用说明

1.  - [for_atlas200dk_1.32.0.0_sample-ascendcamera](https://gitee.com/ascend/samples/tree/1.32.0.0/sample-ascendcamera)：Ascend Camera主要功能是通过Atlas 200 DK开发者板上的摄像头采集数据，经过DVPP转换为jpg，最终保存为文件或者远程输出。
2. - [for_atlas200dk_1.32.0.0_sample-carplaterecognition](https://gitee.com/ascend/samples/tree/1.32.0.0/sample-carplaterecognition)：开发者可以将本application部署至Atlas 200DK上实现对摄像头数据的实时采集、并对视频中的车辆车牌信息进行预测的功能。受模型影响，精准度较低，如果需要提高精度，可以自己训练模型替换。
3. - [for_atlas200dk_1.32.0.0_sample-classification](https://gitee.com/ascend/samples/tree/1.32.0.0/sample-classification)：本Application支持运行在Atlas 200 DK或者AI加速云服务器上，实现了对常见的分类网络的推理功能并输出前n个推理结果。
4. - [for_atlas200dk_1.32.0.0_sample-colorization](https://gitee.com/ascend/samples/tree/1.32.0.0/sample-colorization)：本应用支持运行在Atlas 200 DK上，实现了对黑白图像自动上色的功能。
5. - [for_atlas200dk_1.32.0.0_sample-facedetection](https://gitee.com/ascend/samples/tree/1.32.0.0/sample-facedetection)：开发者可以将本application部署至Atlas 200DK上实现对摄像头数据的实时采集、并对视频中的人脸信息进行预测的功能。
6. - [for_atlas200dk_1.32.0.0_sample-facialrecognition](https://gitee.com/ascend/samples/tree/1.32.0.0/sample-facialrecognition)：开发者可以将本Application部署至Atlas 200 DK上实现人脸注册、并通过摄像头对视频中的人脸信息进行预测，与已注册的人脸进行比对，预测出最可能的用户。
7. - [for_atlas200dk_1.32.0.0_sample-headposeestimation-python](https://gitee.com/ascend/samples/tree/1.32.0.0/sample-headposeestimation-python)：开发者将本应用部署至Atlas 200 DK或者AI加速云服务器上实现对本地mp4文件或者RTSP视频流进行解码，对视频帧中的人脸图像进行头部姿势估计，并将预测的结果信息发送至Presenter Server端进行展示。
8. - [for_atlas200dk_1.32.0.0_sample-objectdetection](https://gitee.com/ascend/samples/tree/1.32.0.0/sample-objectdetection)：本Application支持运行在Atlas 200 DK或者AI加速云服务器上，实现了对faster-rcnn目标检测网络的推理功能。
9. - [for_atlas200dk_1.32.0.0_sample-objectdetectionbyyolov3](https://gitee.com/ascend/samples/tree/1.32.0.0/sample-objectdetectionbyyolov3)：本Application支持运行在Atlas 200 DK或者AI加速云服务器上，实现了对yolov3目标检测网络的推理功能。
10. - [for_atlas200dk_1.32.0.0_sample-segmentation-python](https://gitee.com/ascend/samples/tree/1.32.0.0/sample-segmentation-python)：本Application支持运行在Atlas 200 DK上，实现了erfnet网络的推理功能并输出带有推理结果的图片。
11. - [for_atlas200dk_1.32.0.0_sample-videoanalysisperson](https://gitee.com/ascend/samples/tree/1.32.0.0/sample-videoanalysisperson)：开发者将本Application部署至Atlas 200 DK或者AI加速云服务器上实现对本地mp4文件或者RTSP视频流进行解码，对视频帧中的行人和人脸进行检测并对其属性进行预测，生成结构化信息发送至Server端进行保存、展示的功能。





