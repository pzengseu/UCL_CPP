//
// Created by fly on 17-6-28.
//

#include "Base64Code.h"

char *Base64Encode(const unsigned char *input, int length) {
    BIO *bmem = NULL;
    BIO *b64 = NULL;
    BUF_MEM *bptr = NULL;

    b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    bmem = BIO_new(BIO_s_mem());
    b64 = BIO_push(b64, bmem);
    BIO_write(b64, input, length);
    BIO_flush(b64);
    BIO_get_mem_ptr(b64, &bptr);

    char *buff = (char *) malloc(bptr->length + 1);
    memcpy(buff, bptr->data, bptr->length);
    buff[bptr->length] = 0;

    BIO_free_all(b64);

    return buff;
}

char *Base64Decode(const char* input, size_t inputLength, size_t *binLength) {
    BIO *b64 = NULL;
    BIO *bmem = NULL;
    char *buffer = (char *) malloc(inputLength);
    memset(buffer, 0, inputLength);

    b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    bmem = BIO_new_mem_buf(const_cast<char*>(input), inputLength);
    bmem = BIO_push(b64, bmem);
    *binLength = BIO_read(bmem, buffer, inputLength);

    BIO_free_all(bmem);

    return buffer;
}