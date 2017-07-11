//
// Created by fly on 17-7-11.
//

#ifndef UCL_CPP_ECUCLRSA_H
#define UCL_CPP_ECUCLRSA_H

#include "Base64Code.h"

#include <cassert>
#include <sstream>

class UCLECDSA{
public:
    static char *ECDSASign(const std::string &originalData);

    static bool ECDSAVerify(const std::string &originalData, const std::string &signData);
};

#endif //UCL_CPP_ECUCLRSA_H
