#include <array>
#include <string>

#include "passwordFinderDefs.h"


std::string convertDataToString(const std::vector<byte8> &decryptedData);
std::array<byte, 8> splitByte8(const byte8 &data);