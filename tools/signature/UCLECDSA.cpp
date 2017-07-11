//
// Created by fly on 17-7-11.
//

#include "UCLECDSA.h"

char *UCLECDSA::ECDSASign(const std::string &originalData) {

    FILE *PriKeyFile = fopen("../tools/signature/keyFiles/ec_private_key.pem", "rb");
    if (PriKeyFile == NULL) {
        assert(false);
        return "";
    }
    EC_KEY *ECDSAPriKey = EC_KEY_new();
    if (PEM_read_ECPrivateKey(PriKeyFile, &ECDSAPriKey, 0, 0) == NULL) {
        assert(false);
        return "";
    }
    unsigned int siglen;
    int ECDSASize = ECDSA_size(ECDSAPriKey);
    unsigned char *ECDSAsignBin = new unsigned char[ECDSASize];
    int ret = ECDSA_sign(NID_sha1, (const unsigned char *) originalData.c_str(), originalData.size(),
                         ECDSAsignBin, &siglen, ECDSAPriKey);
    if(ret != 1){
        assert(false);
        return "";
    }
    char *ECDSAsignBase64;
    ECDSAsignBase64 = Base64Encode(ECDSAsignBin, siglen);

    delete[] ECDSAsignBin;
    EC_KEY_free(ECDSAPriKey);
    fclose(PriKeyFile);
    CRYPTO_cleanup_all_ex_data();
    return ECDSAsignBase64;
}

bool UCLECDSA::ECDSAVerify(const std::string &originalData, const std::string &signData) {

    FILE *PubKeyFile = fopen("../tools/signature/keyFiles/ec_public_key.pem", "rb");
    if (PubKeyFile == NULL) {
        assert(false);
        return "";
    }
    EC_KEY *ECDSAPubKey = EC_KEY_new();
    if (PEM_read_EC_PUBKEY(PubKeyFile, &ECDSAPubKey, 0, 0) == NULL) {
        assert(false);
        return "";
    }
    unsigned char *ECDSAsignBin;
    size_t length;
    ECDSAsignBin = (unsigned char *) Base64Decode(signData.c_str(), signData.length(), &length);

    int ret = ECDSA_verify(NID_sha1, (const unsigned char *) originalData.c_str(), originalData.size(),
                         ECDSAsignBin, length, ECDSAPubKey);
    EC_KEY_free(ECDSAPubKey);
    fclose(PubKeyFile);
    CRYPTO_cleanup_all_ex_data();
    if (ret == 1) {
        return true;
    }
    return false;
}