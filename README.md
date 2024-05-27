# myans

## 开发平台说明

开发环境说明

* 操作系统：Ubuntu 24.04
* C++标准：C++14
* 编译器：g++ 13.2.0
* CMake：3.28.3
* gtest: 1.14.0

本示例使用C++14开发，所以编译运行本示例无需严格符合“开发平台说明”中的环境，支持C++14的Linux发行版均可编译运行本示例。

## 编译项目

执行以下脚本编译本项目

```shell
sudo apt install -y gcc g++ make cmake libgtest-dev
git clone https://github.com/xstar2091/myans.git
cd myans
mkdir build
cd build
cmake ..
make
```

运行测试

```shell
./myans_test
```
