#include "inputDataHandler.h"

#include <algorithm>
#include <exception>
#include <fstream>
#include <sstream>

void InputDataHandler::readFile(const char *fileName) 
{
    std::ifstream file(fileName, std::ios_base::binary);
    if (!file) {
        throw std::runtime_error("can't open input file"); 
    }

    byte8 rawData = 0;
    byte8 inverseRawData = 0;

    char *begin = reinterpret_cast<char*>(&inverseRawData);
    char *end = begin + sizeof(&inverseRawData);
    char *dest = reinterpret_cast<char*>(&rawData);

    bool firstStep = true;

    while(file.readsome(begin, sizeof(inverseRawData)) > 0) {
        std::reverse_copy(begin, end, dest);

        if (firstStep) {
            desInitVector = rawData;
            firstStep = false;
            continue;
        }

        encryptedData.push_back(rawData);
    }
}

void InputDataHandler::parseFile(const char *fileName)
{
    readFile(fileName);

    static const short sha256ofOrigDataLengthInByte8 = 4;
    auto encryptedDataSize = encryptedData.size();
    std::stringstream rawData;

    if (encryptedDataSize >= sha256ofOrigDataLengthInByte8) {

        for (int idx = encryptedDataSize - sha256ofOrigDataLengthInByte8; 
                                       idx != encryptedDataSize; ++idx) {
            rawData << std::hex << encryptedData[idx];
        }
    }

    sha256ofOrigData = rawData.str();
    rawData.str({});

    for (int idx  = 0; idx != sha256ofOrigDataLengthInByte8; ++idx) {
        if (!encryptedData.empty()) {
            encryptedData.pop_back();
        }
    }
}
