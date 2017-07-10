//
// Created by fly on 17-6-28.
//
#include "UCLDSA.h"
#include <iostream>

using namespace std;

unsigned int siglen;

std::string UCLDSA::DSASign(const std::string &originalData) {

    FILE *PriKeyFile = fopen("../KeyFiles/dsa_private_key.pem", "rb");
    if (PriKeyFile == NULL) {
        assert(false);
        return "";
    }
    DSA *DSAPriKey = DSA_new();
    if (PEM_read_DSAPrivateKey(PriKeyFile, &DSAPriKey, 0, 0) == NULL) {
        assert(false);
        return "";
    }
//    unsigned int siglen;
    int DSASize = DSA_size(DSAPriKey);
    unsigned char *DSAsignBin = new unsigned char[DSASize];
    DSA_sign(NID_sha1, (const unsigned char *) originalData.c_str(), originalData.size(),
             DSAsignBin, &siglen, DSAPriKey);
    string DSAsignBase64;
    DSAsignBase64 = Base64Encode(DSAsignBin, siglen);
    delete[] DSAsignBin;
    DSA_free(DSAPriKey);
    fclose(PriKeyFile);
    CRYPTO_cleanup_all_ex_data();
    cerr << siglen << endl;
    return DSAsignBase64;
}

bool UCLDSA::DSAVerify(const std::string &originalData, const std::string &signData) {

    FILE *PubKeyFile = fopen("../KeyFiles/dsa_public_key.pem", "rb");
    if (PubKeyFile == NULL) {
        assert(false);
        return "";
    }
    DSA *DSAPubKey = DSA_new();
    if (PEM_read_DSA_PUBKEY(PubKeyFile, &DSAPubKey, 0, 0) == NULL) {
        assert(false);
        return "";
    }
    unsigned char *DSAsignBin;
    size_t length;
    DSAsignBin = (unsigned char *) Base64Decode(signData.c_str(), signData.length(), &length);
    cerr << length << endl;

    int ret = DSA_verify(NID_sha1, (const unsigned char *) originalData.c_str(), originalData.size(),
                         DSAsignBin, length, DSAPubKey);
    DSA_free(DSAPubKey);
    fclose(PubKeyFile);
    CRYPTO_cleanup_all_ex_data();
    if (ret == 1) {
        return true;
    }
    return false;
}