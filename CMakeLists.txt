cmake_minimum_required(VERSION 3.6)
project(UCL_CPP)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp property/UCLPropertyBase.h property/UCLPropertyBase.cpp property/UCLPropertyHead.cpp property/UCLPropertyHead.h
        property/UCLPropertySet.h property/SNPS.h property/SNPS.cpp property property/CDPS.h property/CDPS.cpp property/CGPS.h property/UCLPropertySet.cpp UCL.cpp test.h)
add_executable(UCL_CPP ${SOURCE_FILES})