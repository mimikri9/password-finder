#include <exception>
#include <iostream>
#include <string>

#include "inputDataHandler.h"
#include "keyGen.h"
#include "passwordFinderDefs.h"
#include "worker.h"

int main(int argc, char* argv[])
{
    int exitCode = EXIT_SUCCESS;

    if (argc < 2) {
        std::cout << "Error: no filename specified" << std::endl;
        exitCode = EXIT_FAILURE;
        return exitCode;
    }

    try {
        InputDataHandler inputDataHandler;
        inputDataHandler.parseFile(argv[1]);

        KeyGen keyGen;
        keyGen.generateKeys();

        const KeyCollection &keys = keyGen.getKeys();

        Worker worker;

        if (argc > 2) {
           worker.testKey(inputDataHandler, argv[2]); 
        } else {
            std::cout << "The key is searching...\n";

            KeyCollectionCIterator keyIt = worker.tryKeys(keys.cbegin(), keys.cend(), 
                                                                    inputDataHandler);
            if (keyIt == keys.cend()) {
                std::cout << "No key found" << std::endl;
            } else {
                std::cout << "The searched key is: " << *keyIt << std::endl;
            }
        }

    } catch (const std::exception &ex) {
        exitCode = EXIT_FAILURE;
        std::cerr << "Error: " << ex.what() << std::endl;
    } catch (...) {
        exitCode = EXIT_FAILURE;
        std::cerr << "Error: unknown" << std::endl;
    }

    return exitCode;
}


