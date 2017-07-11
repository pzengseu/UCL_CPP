//
// Created by fly on 17-6-28.
//

#ifndef UCL_CPP_UCLRSA_H
#define UCL_CPP_UCLRSA_H

#include "Base64Code.h"
#include "../digest/UCLSHA_256.h"
#include <cassert>
#include <sstream>

class UCLRSA{
public:
    static char *RSASign(const std::string &originalData);

    static bool RSAVerify(const std::string &originalData, const std::string &signData);
};

#endif //UCL_CPP_UCLRSA_H
