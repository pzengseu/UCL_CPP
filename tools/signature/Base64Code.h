//
// Created by fly on 17-6-28.
//

#ifndef UCL_CPP_BASE64CODE_H
#define UCL_CPP_BASE64CODE_H

#include <openssl/pem.h>
#include <cstring>

char *Base64Encode(const unsigned char *input, int length);

char *Base64Decode(const char *input, size_t inputLength, size_t *binLength);

#endif //UCL_CPP_BASE64CODE_H
