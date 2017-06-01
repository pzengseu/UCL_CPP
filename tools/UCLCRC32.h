//
// Created by Fly on 2017/1/15.
//

#ifndef UCL_CPP_UCLCRC32_H
#define UCL_CPP_UCLCRC32_H

#include <iostream>
#include <string>

using namespace std;

const uint32_t POLYNOMIAL = 0xEDB88320;

string crc32(const string &buff);

class UCLCRC32 {

public:
    bool have_table;
    uint32_t table[256];

    UCLCRC32() {
        have_table = false;
    }

    void make_table();

};

#endif //UCL_CPP_UCLCRC32_H
