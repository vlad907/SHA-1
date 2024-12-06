#include <iostream>
#include "djb2test.h"
#include <string>
#include <bitset>


unsigned long djb2test(const std::string &str) {
    unsigned long hash = 5381; // Initial seed value
    for (char c : str) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash;
}

