#include <iostream>
#include "djb2.h"
#include <string>
#include <bitset>

using namespace std;

unsigned long djb2Hash(const std::string &str) {
    unsigned long hash = 5381; // Initial seed value
    cout << "binary representation" << endl;
    for (char c : str) {
        cout << "character: " << c << "  ==>  " << bitset<8>(c) << "  ==>  ";
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
        cout << bitset<64>(hash) << endl;
    }
    return hash;
}

