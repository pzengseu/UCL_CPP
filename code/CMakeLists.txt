cmake_minimum_required(VERSION 3.6)
project(UCL_V0_1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp header_file/UCLCode.h header_file/UCLFormatV2.h UCLCode.cpp UCLCodeExtension.cpp header_file/UCLCodeExtension.h)
add_executable(UCL_V0_1 ${SOURCE_FILES})