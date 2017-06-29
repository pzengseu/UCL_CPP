cmake_minimum_required(VERSION 3.6)
project(UCL_CPP)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp
        code/header_file/UCLCode.h code/header_file/UCLFormatV2.h code/UCLCode.cpp code/UCLCodeExtension.cpp
        code/header_file/UCLCodeExtension.h property/UCLPropertyBase.h property/UCLPropertyBase.cpp
        property/UCLPropertyHead.cpp property/UCLPropertyHead.h property/UCLPropertySet.h
        property/UCLPropertySet.cpp UCL/UCL.h UCL/UCL.cpp UCL/test.h property/GenerateProperty.h
        property/GenerateProperty.cpp tools/digestUtils/UCLMD5.h tools/digestUtils/UCLMD5.cpp
        tools/digestUtils/UCLCRC32.h tools/digestUtils/UCLCRC32.cpp tools/digestUtils/UCLSHA_256.h
        tools/digestUtils/UCLSHA_256.cpp tools/digestUtils/UCLSHA_512.h tools/digestUtils/UCLSHA_512.cpp
        UCL/testUCLCode.h UCL/testUCLCode.cpp property/UCLPropertiesInfo.h property/UCLPropertiesInfo.cpp
        UCL/test.cpp property/GenCDPSProperty.h property/GenCDPSProperty.cpp property/GenCGPSProperty.cpp
        property/GenCGPSProperty.h tools/signatureUtils/Base64Code.h tools/signatureUtils/Base64Code.cpp
        tools/signatureUtils/UCLRSA.h tools/signatureUtils/UCLRSA.cpp)
add_executable(UCL_CPP ${SOURCE_FILES})
target_link_libraries(UCL_CPP ssl crypto)