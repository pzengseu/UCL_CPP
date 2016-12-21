cmake_minimum_required(VERSION 3.6)
project(UCL_CPP)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp property/UCLPropertyBase.h property/UCLPropertyBase.cpp property/UCLPropertyHead.cpp property/UCLPropertyHead.h
        property/UCLPropertySet.h  property/UCLPropertySet.cpp UCL.h UCL.cpp test.h property/GenerateProperty.h property/GenerateProperty.cpp)
add_executable(UCL_CPP ${SOURCE_FILES})