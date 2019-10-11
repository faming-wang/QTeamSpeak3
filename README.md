## QTeamSpeak3 
使用 Qt 封装的 TeamSpeak3 SDK. 它以Qt风格提供了相同的功能。
你可能需要了解TeamSpeak3的帮助文档。

#### 依赖
* 编译器需要支持C++11
* [TeamSpeak 3 SDK](http://TeamSpeak.com/downloads#sdk) >= 3.0.0
* [Qt](https://qt.io/download/) >= 5.6.0
* [Cmake](https://cmake.org/download/) >= 3.9.0

#### Cmake 编译
~~~
git clone https://github.com/faming-wang/QTeamSpeak3.git ./QTeamSpeak3
cd QTeamSpeak3
~~~
创建一个构建目录
~~~
mkdir out
~~~
在构建目录中运行 cmake 命令来配置
~~~
cd out
cmake .. -D Qt5_DIR=[you qt lib root path]/lib/cmake/Qt5
~~~
On Window
~~~
msbuild QTeamSpeak3.sln /property:Configuration=Debug /property:Platform="Win32"
msbuild QTeamSpeak3.sln /property:Configuration=Release /property:Platform="Win32"
~~~
On Linux or MacOS
~~~
make
make install
~~~
