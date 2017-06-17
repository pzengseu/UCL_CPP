cmake_minimum_required(VERSION 3.6)
project(UCL_CPP)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp
        code/header_file/UCLCode.h code/header_file/UCLFormatV2.h code/UCLCode.cpp code/UCLCodeExtension.cpp code/header_file/UCLCodeExtension.h
        property/UCLPropertyBase.h property/UCLPropertyBase.cpp property/UCLPropertyHead.cpp property/UCLPropertyHead.h
        property/UCLPropertySet.h  property/UCLPropertySet.cpp UCL/UCL.h UCL/UCL.cpp UCL/test.h property/GenerateProperty.h property/GenerateProperty.cpp
        tools/md5.h tools/md5.cpp tools/UCLCRC32.h tools/UCLCRC32.cpp tools/UCLSHA_256.h tools/UCLSHA_256.cpp
        tools/UCLSHA_512.h tools/UCLSHA_512.cpp UCL/testUCLCode.h UCL/testUCLCode.cpp property/UCLPropertiesInfo.h property/UCLPropertiesInfo.cpp UCL/test.cpp property/GenCDPSProperty.h property/GenCDPSProperty.cpp property/GenCGPSProperty.cpp property/GenCGPSProperty.h)
add_executable(UCL_CPP ${SOURCE_FILES})