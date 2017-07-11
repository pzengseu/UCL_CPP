//
// Created by fly on 17-6-28.
//

#include "UCLRSA.h"

char *UCLRSA::RSASign(const std::string &originalData) {

    FILE *PriKeyFile = fopen("../tools/signature/keyFiles/rsa_private_key.pem", "rb");
    if (PriKeyFile == NULL) {
        assert(false);
        return "";
    }
    RSA *RSAPriKey = RSA_new();
    if (PEM_read_RSAPrivateKey(PriKeyFile, &RSAPriKey, 0, 0) == NULL) {
        assert(false);
        return "";
    }
    unsigned int siglen;
    int RSASize = RSA_size(RSAPriKey);
    unsigned char *RSAsignBin = new unsigned char[RSASize];
    std::string convertData = originalData;
    if (originalData.length() == 128) {
        convertData = sha256(originalData);
    }
    int res = RSA_sign(NID_sha1, (const unsigned char *) convertData.c_str(), convertData.size(),
                       RSAsignBin, &siglen, RSAPriKey);
    if (res != 1) {
        assert(false);
        return "";
    }
    char *RSAsignBase64;
    RSAsignBase64 = Base64Encode(RSAsignBin, siglen);

    delete[] RSAsignBin;
    RSA_free(RSAPriKey);
    fclose(PriKeyFile);
    CRYPTO_cleanup_all_ex_data();
    return RSAsignBase64;
}

bool UCLRSA::RSAVerify(const std::string &originalData, const std::string &signData) {

    FILE *PubKeyFile = fopen("../tools/signature/keyFiles/rsa_public_key.pem", "rb");
    if (PubKeyFile == NULL) {
        assert(false);
        return "";
    }
    RSA *RSAPubKey = RSA_new();
    if (PEM_read_RSA_PUBKEY(PubKeyFile, &RSAPubKey, 0, 0) == NULL) {
        assert(false);
        return "";
    }
    unsigned char *RSAsignBin;
    size_t length;
    RSAsignBin = (unsigned char *) Base64Decode(signData.c_str(), signData.length(), &length);
    std::string convertData = originalData;
    if (originalData.length() == 128) {
        convertData = sha256(originalData);
    }
    int ret = RSA_verify(NID_sha1, (const unsigned char *) convertData.c_str(), convertData.size(),
                         RSAsignBin, length, RSAPubKey);
    RSA_free(RSAPubKey);
    fclose(PubKeyFile);
    CRYPTO_cleanup_all_ex_data();
    if (ret == 1) {
        return true;
    }
    return false;
}