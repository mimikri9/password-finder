#include "worker.h"

#include <algorithm>
#include <functional>
#include <future>
#include <thread>
#include <iostream>

#include "crypto/des3.h"
#include "crypto/md5.h"
#include "crypto/sha256.h"
#include "supportFunc.h"

#include <iostream>


const unsigned long Worker::keysPerThread(50);

KeyCollectionCIterator Worker::tryKeysParrallel(KeyCollectionCIterator first, KeyCollectionCIterator last,
                                                std::atomic<bool> &done, const InputDataHandler &inputData)
{
    try {

        const unsigned long numOfKeys = std::distance(first, last);

        if (numOfKeys < (2 * keysPerThread)) {

            for (auto keysIt = first; (keysIt != last) && !done.load(); ++keysIt) {

                MD5 md5 = MD5(*keysIt);
                std::string md5result = md5.hexdigest();

                int md5ResultSize = md5result.size();
                int md5ResultMiddle = md5ResultSize/2;

                std::string key1 = md5result.substr(0, md5ResultMiddle);
                std::string key2 = md5result.substr(md5ResultMiddle, md5ResultSize - md5ResultMiddle);

                DES3 des3;
                des3.decryptInCbcMode(inputData.getEncryptedData(),
                                      inputData.getDesInitVector(),
                                      key1,
                                      key2);
                std::string decryptResult = convertDataToString(des3.getDecryptedData());

                if (sha256(decryptResult) == inputData.getSha256ofOrigData()) {
                    done.store(true);
                    std::cout << "Decrypt result is \n" << decryptResult << '\n';
                    return keysIt;
                }
            }

            return last;

        } else {
            KeyCollectionCIterator midPoint = first + (numOfKeys/2);
            //incorrect, but more faster on my machine. Maybe should try std::thread::hardware_concurrency() and std::thread.... :
            //std::future<KeyCollectionCIterator> asyncResult = std::async(std::launch::async, &Worker::tryKeysParrallel, this,
            //correct, but slower on my machine(???). 
            std::future<KeyCollectionCIterator> asyncResult = std::async(&Worker::tryKeysParrallel, this,
                                                               midPoint, last, std::ref(done), std::ref(inputData));
            KeyCollectionCIterator directResult = tryKeysParrallel(first, midPoint, done, inputData);
            return (directResult == midPoint) ? asyncResult.get() : directResult;
        }

    } catch(...) {
        done = true;
        throw;
    }
}

void Worker::testKey(const InputDataHandler &inputData, const char * testKey)
{
    std::string result;

    MD5 md5 = MD5(testKey);
    std::string md5result = md5.hexdigest();

    int md5ResultSize = md5result.size();
    int md5ResultMiddle = md5ResultSize/2;

    std::string key1 = md5result.substr(0, md5ResultMiddle);
    std::string key2 = md5result.substr(md5ResultMiddle, md5ResultSize - md5ResultMiddle);

    DES3 des3;
    des3.decryptInCbcMode(inputData.getEncryptedData(),
                          inputData.getDesInitVector(),
                          key1,
                          key2);
    std::string decryptResult = convertDataToString(des3.getDecryptedData());

     std::cout << "Decrypt result is:\n" << decryptResult << '\n';

    if (sha256(decryptResult) == inputData.getSha256ofOrigData()) {
        std::cout <<  "Test passed!" << std::endl;
    } else {
        std::cout <<  "Test failed!" << std::endl;
    }
}

KeyCollectionCIterator Worker::tryKeys(KeyCollectionCIterator first, KeyCollectionCIterator last,
                                                               const InputDataHandler &inputData)
{
    std::atomic<bool> done(false);
    return tryKeysParrallel(first, last, done, inputData);
}