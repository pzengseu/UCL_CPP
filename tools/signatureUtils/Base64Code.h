//
// Created by fly on 17-6-28.
//

#ifndef UCL_CPP_BASE64CODE_H
#define UCL_CPP_BASE64CODE_H

#include <openssl/pem.h>
#include <cstring>

void Base64Encode(const unsigned char *buffer, size_t length, char **base64Text);

size_t calcDecodeLength(const char *b64input);

void Base64Decode(const char *b64message, unsigned char **buffer, size_t *length);

#endif //UCL_CPP_BASE64CODE_H
