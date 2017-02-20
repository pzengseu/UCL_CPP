//
// Created by Fly on 2017/1/16.
//

#ifndef UCL_CPP_UCLSHA_256_H
#define UCL_CPP_UCLSHA_256_H

#include <iostream>
#include <cstring>
using namespace std;

class UCLSHA_256{
public:
    uint32_t rRot(uint32_t val, int pos);
    string sha_256(string str);
};

#endif //UCL_CPP_UCLSHA_256_H
