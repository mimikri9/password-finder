#include "des3.h"
#include <algorithm>
#include <array>
#include <string>

void DES3::decryptInCbcMode(const std::vector<byte8> &encrData, const byte8 &desInitVector,
                                          const std::string &key1, const std::string &key2)
{
    byte8 key1_ = std::stoul(key1, nullptr, 16);
    byte8 key2_ = std::stoul(key2, nullptr, 16);

    byte8 encodedData = 0;
    byte8 byte8Result = 0;

    decryptedData.reserve(encrData.size());

    DES des1(key1_);
    DES des2(key2_);
    DES des3(key1_);

    for (int dataIdx = encrData.size() - 1; dataIdx >= 0; --dataIdx) {

        if (dataIdx > 0) {
            byte8Result = des1.decrypt(des2.encrypt(des3.decrypt(encrData[dataIdx]))) ^ encrData[dataIdx - 1];
        } else {
            byte8Result = des1.decrypt(des2.encrypt(des3.decrypt(encrData[dataIdx]))) ^ desInitVector;
        }

        decryptedData.push_back(byte8Result);
    }

    std::reverse(decryptedData.begin(), decryptedData.end());
}

