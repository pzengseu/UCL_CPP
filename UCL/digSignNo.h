//
// Created by fly on 17-7-11.
//

#ifndef UCL_CPP_DIGSIGNNO_H
#define UCL_CPP_DIGSIGNNO_H

#define CRC32        1
#define MD5          2
#define SHA_256      3
#define SHA_512      4

#define RSA          1
#define ECDSA        2
#define DSA          3
#define ECC          4
#define HMAC         5

//Unit of length:Byte
#define CRC32_LEN    4
#define MD5_LEN      32
#define SHA_256_LEN  32
#define SHA_512_LEN  64

#define RSA_LEN      128
#define ECDSA_LEN    32
#define DSA_LEN      128
#define ECC_LEN      20
#define HMAC_MD5     16
#define HMAC_SHA1    20

#endif //UCL_CPP_DIGSIGNNO_H
