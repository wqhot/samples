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
#### 软件架构
软件架构说明

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

#### 安装教程

1.  xxxx
2.  xxxx
3.  xxxx

#### 使用说明

1.  xxxx
2.  xxxx
3.  xxxx

#### 参与贡献

1.  Fork 本仓库
2.  新建 Feat_xxx 分支
3.  提交代码
4.  新建 Pull Request



