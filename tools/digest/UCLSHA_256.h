//
// Created by Fly on 2017/1/16.
//

#ifndef UCL_CPP_UCLSHA_256_H
#define UCL_CPP_UCLSHA_256_H

#include <iostream>
#include <cstring>
using namespace std;

string sha256(const string &str);

class UCLSHA_256{
public:
    uint32_t rRot(uint32_t val, int pos);
};

#endif //UCL_CPP_UCLSHA_256_H
