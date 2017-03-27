#pragma once
//Parses input file and stores parsed data

#include <string>
#include <vector>

#include "passwordFinderDefs.h"

class InputDataHandler {
public:
    InputDataHandler() = default;

    InputDataHandler(const InputDataHandler &) = delete;

    InputDataHandler(InputDataHandler &&) = delete;

    InputDataHandler & operator=(const InputDataHandler &) = delete;

    InputDataHandler & operator=(InputDataHandler &&) = delete;

    void parseFile(const char *fileName);

    byte8 getDesInitVector() const;

    const std::vector<byte8> & getEncryptedData() const;

    const std::string & getSha256ofOrigData() const;

private:

    void readFile(const char *fileName);

private:
    byte8 desInitVector;
    std::vector<byte8> encryptedData;
    std::string sha256ofOrigData; 
};


inline byte8 InputDataHandler::getDesInitVector() const
{
    return desInitVector;
}

inline const std::vector<byte8> & InputDataHandler::getEncryptedData() const
{
    return encryptedData; 
}

inline const std::string & InputDataHandler::getSha256ofOrigData() const
{
    return sha256ofOrigData;
}