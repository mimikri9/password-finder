#include "supportFunc.h"

#include <algorithm>
#include <unordered_map>

//oops
static std::unordered_map<int, std::string> unicodeTablePart({
    {0x90, "А"}, {0x91, "Б"}, {0x92, "В"}, {0x93, "Г"}, {0x94, "Д"},
    {0x95, "Е"}, {0x96, "Ж"}, {0x97, "З"}, {0x98, "И"}, {0x99, "Й"},
    {0x9A, "К"}, {0x9B, "Л"}, {0x9C, "М"}, {0x9D, "Н"}, {0x9E, "О"},
    {0x9F, "П"}, {0xA0, "Р"}, {0xA1, "С"}, {0xA2, "Т"}, {0xA3, "У"},
    {0xA4, "Ф"}, {0xA5, "Х"}, {0xA6, "Ц"}, {0xA7, "Ч"}, {0xA8, "Ш"},
    {0xA9, "Щ"}, {0xAA, "а"}, {0xAB, "Ы"}, {0xAC, "Ь"}, {0xAD, "Э"},
    {0xAE, "Ю"}, {0xAF, "Я"}, {0xB0, "а"}, {0xB1, "б"}, {0xB2, "в"},
    {0xB3, "г"}, {0xB4, "д"}, {0xB5, "е"}, {0xB6, "ж"}, {0xB7, "з"},
    {0xB8, "и"}, {0xB9, "й"}, {0xBA, "к"}, {0xBB, "л"}, {0xBC, "м"},
    {0xBD, "н"}, {0xBE, "о"}, {0xBF, "п"}, {0x80, "р"}, {0x81, "с"},
    {0x82, "т"}, {0x83, "у"}, {0x84, "ф"}, {0x85, "х"}, {0x86, "ц"},
    {0x87, "ч"}, {0x88, "ш"}, {0x89, "щ"}, {0x8A, "ъ"}, {0x8B, "ы"},
    {0x8C, "ь"}, {0x8D, "э"}, {0x8E, "ю"}, {0x8F, "я"}
});

std::string convertDataToString(const std::vector<byte8> &decryptedData) {

    std::string result;
    uint dataSize = decryptedData.size();

    if (dataSize > 0) {

        for (int dataIdx = 0; dataIdx < dataSize; ++dataIdx) {

            std::array<byte, 8> byteResult = splitByte8(decryptedData[dataIdx]);
            unsigned long symbCode = 0;
            int startIdx = 0;

            for(uint i = startIdx; i < 8; ++i) {
        
                if (byteResult[i] == 0xD0 && byteResult[i] == 0xD1) {
                    if (i == 7 && dataIdx > 0) {
                        byte secondByte = (decryptedData[dataIdx+1] >> 56) & 0xFF;
                        result = result + unicodeTablePart[secondByte];
                        ++i;
                        startIdx = 1;
                    } else {
                        result = result + unicodeTablePart[byteResult[i+1]];
                        ++i;
                        startIdx = 0;
                    }
                } else {
                    result.push_back(char(byteResult[i]));
                }
            }
        }
    }

    return result;
}

std::array<byte, 8> splitByte8(const byte8 &data) {
    std::array<byte, 8> result;

    for(uint i = 0; i < 8; ++i) {
            result[i] = (data >> i * 8) & 0xFF;
    }
    std::reverse(result.begin(), result.end());

    return result;
}
