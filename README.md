## QTeamSpeak3 
A Qt-Wrapper around the native TeamSpeak-SDK. It provides the same functionality in the Qt style.

#### Depends
* The compiler needs support C++11
* [TeamSpeak 3 SDK](http://TeamSpeak.com/downloads#sdk) >= 3.0.0
* [Qt](https://qt.io/download/) >= 5.6.0
* [Cmake](https://cmake.org/download/) >= 3.9.0

#### CMake build
~~~
git clone https://github.com/faming-wang/QTeamSpeak3.git ./QTeamSpeak3
cd QTeamSpeak3
~~~
Create a build directory
~~~
mkdir out
~~~
Run the cmake command in the build directory to configure
~~~
cd out
cmake .. -D Qt5_DIR=[you qt lib root path]/lib/cmake/Qt5
~~~
On Windows
~~~
msbuild QTeamSpeak3.sln /property:Configuration=Debug /property:Platform="Win32"
msbuild QTeamSpeak3.sln /property:Configuration=Release /property:Platform="Win32"
~~~
On Linux or MacOS
~~~
make
make install
~~~
On IOS
[sa cmake-ios](https://github.com/leetal/ios-cmake)
