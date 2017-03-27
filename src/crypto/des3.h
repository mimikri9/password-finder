#pragma once

#include <string>
#include <vector>

#include "des.h"

class DES3 {
public:
    DES3() = default;

    DES3(const DES3 &) = delete;

    DES3(DES3 &&) = delete;

    DES3 & operator=(const DES3 &) = delete;

    DES3 & operator=(DES3 &&) = delete;

    void decryptInCbcMode(const std::vector<byte8> &data, const byte8 &desInitVector,
                                    const std::string &key1, const std::string &key2);

    const std::vector<byte8> & getDecryptedData();

private:
    std::vector<byte8> decryptedData;
}; 

inline const std::vector<byte8> & DES3::getDecryptedData() {
    return decryptedData;
}


