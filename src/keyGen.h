#pragma once
//Generates keys [0-9a-zA-Z] and stores all combinations

#include "passwordFinderDefs.h"

class KeyGen {
public:
    KeyGen();

    KeyGen (const KeyGen &) = delete;

    KeyGen (KeyGen &&) = delete;

    KeyGen & operator=(const KeyGen &) = delete;

    KeyGen & operator=(KeyGen &&) = delete;

    void generateKeys();
    
    const KeyCollection & getKeys();

private:
    static const int numberOfCombinations;
    KeyCollection keyCollection;
};
