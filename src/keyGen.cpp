#include "keyGen.h"

KeyGen::KeyGen()
{
    keyCollection.reserve(numberOfCombinations);
}

const int KeyGen::numberOfCombinations(238328);

void KeyGen::generateKeys()
{
    std::string key;
    
    for (char t = 48; t < 123; ++t) {

        if ((t > 57 && t < 65) || (t > 90 && t < 97)) {
            continue;
        }

        key.push_back(t);

        for (char z = 48; z < 123; ++z) {

            if ((z > 57 && z < 65) || (z > 90 && z < 97)) {
                continue;
            }

            key.push_back(z);

            for (char x = 48; x < 123; ++x) {

                if ((x > 57 && x < 65) || (x > 90 && x < 97)) {
                    continue;
                }
                key.push_back(x);

                keyCollection.push_back(key);
                key.pop_back();
            }

            key.pop_back();
        }

        key.pop_back();
    }
}

const KeyCollection & KeyGen::getKeys()
{
    return keyCollection;
}