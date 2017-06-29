//
// Created by fly on 17-6-28.
//

#include "UCLRSA.h"

std::string UCLRSA::RSASign(const std::string &originalData) {

    FILE *PriKeyFile = fopen("../tools/signatureUtils/keyFiles/rsa_private_key.pem", "rb");
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
    int res = RSA_sign(NID_sha1, (const unsigned char *) originalData.c_str(), originalData.size(),
             RSAsignBin, &siglen, RSAPriKey);
    if(res != 1){
        assert(false);
        return "";
    }
    char *RSAsignBase64;
    Base64Encode(RSAsignBin, siglen, &RSAsignBase64);
    delete[] RSAsignBin;
    RSA_free(RSAPriKey);
    fclose(PriKeyFile);
    CRYPTO_cleanup_all_ex_data();
    return RSAsignBase64;
}

bool UCLRSA::RSAVerify(const std::string &originalData, const std::string &signData) {

    FILE *PubKeyFile = fopen("../tools/signatureUtils/keyFiles/rsa_public_key.pem", "rb");
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
    Base64Decode(signData.c_str(), &RSAsignBin, &length);

    int ret = RSA_verify(NID_sha1, (const unsigned char *) originalData.c_str(), originalData.size(),
                         RSAsignBin, length, RSAPubKey);
    RSA_free(RSAPubKey);
    fclose(PubKeyFile);
    CRYPTO_cleanup_all_ex_data();
    if (ret == 1) {
        return true;
    }
    return false;
}