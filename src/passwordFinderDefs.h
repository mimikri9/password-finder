#pragma once

#include <cstdint>
#include <string>
#include <vector>

using byte8 = uint64_t;
using byte4 = uint32_t;
using byte2 = uint16_t;
using byte  = uint8_t;

using KeyCollection = std::vector<std::string>;
using KeyCollectionCIterator = std::vector<std::string>::const_iterator;

