#pragma once
//The main algorithm 

#include <atomic>
#include <string>

#include "inputDataHandler.h"
#include "passwordFinderDefs.h"

class Worker {
public:
    Worker() = default;

    Worker(const Worker &) = delete;

    Worker(Worker &&) = delete;

    Worker & operator=(const Worker &) = delete;

    Worker & operator=(const Worker &&) = delete;

    KeyCollectionCIterator tryKeys(KeyCollectionCIterator first, KeyCollectionCIterator last, 
                                                           const InputDataHandler &inputData);

    void testKey(const InputDataHandler &inputData, const char * testKey);

private:
    KeyCollectionCIterator tryKeysParrallel(KeyCollectionCIterator first, KeyCollectionCIterator last,
                                           std::atomic<bool> &done, const InputDataHandler &inputData);

private:
    static const unsigned long keysPerThread;
};



