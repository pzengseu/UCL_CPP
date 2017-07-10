//
// Created by fly on 17-6-28.
//

#ifndef UCL_CPP_UCLDSA_H
#define UCL_CPP_UCLDSA_H

#include "../Base64Code.h"
#include <openssl/dsa.h>

#include <cassert>
#include <sstream>

class UCLDSA{
public:
    static std::string DSASign(const std::string &originalData);

    static bool DSAVerify(const std::string &originalData, const std::string &signData);
};

#endif //UCL_CPP_UCLDSA_H
