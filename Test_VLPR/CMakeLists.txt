# CMakeList.txt: Test_VLPR 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)
include_directories("D:/Software/opencv/build/include")
link_directories("D:/Software/opencv/build/x64/vc15/lib")
# 将源代码添加到此项目的可执行文件。

file(GLOB src_files *.cpp)
add_executable (Test_VLPR ${src_files})


# TODO: 如有需要，请添加测试并安装目标。
target_link_libraries(Test_VLPR opencv_world410d)
