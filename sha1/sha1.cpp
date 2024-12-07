#include <iostream>
#include "sha1.h"
#include <vector>
#include <bitset>
#include <iomanip>


using namespace std;

uint32_t leftRotate(uint32_t value, uint32_t shift) {
    return (value << shift) | (value >> (32 - shift));
}

vector<uint8_t> padMessage(const string &message) {
    vector<uint8_t> padded(message.begin(), message.end());
    uint64_t originalLength = message.size() * 8;

    // Append a single '1' bit
    padded.push_back(0x80);

    // Add zero padding until the message is 64 bits shy of a multiple of 512
    while ((padded.size() * 8) % 512 != 448) {
        padded.push_back(0x00);
    }

    // Append the original length as a 64-bit big-endian integer
    for (int i = 7; i >= 0; --i) {
        padded.push_back((originalLength >> (i * 8)) & 0xFF);
    }

    return padded;
}

vector<uint32_t> parseMessageBlocks(const vector<uint8_t> &paddedMessage) {
    vector<uint32_t> blocks;

    for (size_t i = 0; i < paddedMessage.size(); i += 4) {
        uint32_t block = 0;
        for (int j = 0; j < 4; ++j) {
            block = (block << 8) | paddedMessage[i + j];
        }
        blocks.push_back(block);
    }

    return blocks;
}

string sha1(const string &message) {
    // Initialize hash values
    uint32_t h0 = 0x67452301;
    uint32_t h1 = 0xEFCDAB89;
    uint32_t h2 = 0x98BADCFE;
    uint32_t h3 = 0x10325476;
    uint32_t h4 = 0xC3D2E1F0;

    // Preprocess message
    vector<uint8_t> paddedMessage = padMessage(message);
    vector<uint32_t> messageBlocks = parseMessageBlocks(paddedMessage);


    cout << "Padded Message (Binary):" << endl;
    for (uint8_t byte : paddedMessage) {
        cout << bitset<8>(byte) << " ";
    }
    
    cout << "\n\n" << endl;

    cout << "Message Block (Binary):" << endl;
    for (uint8_t byte : messageBlocks) {
        cout << bitset<32>(byte) << " ";
    }

    cout << "\n\n" << endl;

    while (true) {
        cout << "Press Enter to continue: ";
        string input;
        getline(cin, input);
        if (input.empty()) {
            break;
        }
    }

    // Process each 512-bit block
    for (size_t i = 0; i < messageBlocks.size() / 16; ++i) {
        // Prepare the message schedule
        uint32_t W[80];
        cout << "words 0-80" << endl;
        for (int t = 0; t < 16; ++t) {
            W[t] = messageBlocks[i * 16 + t];
            cout << " W[" << t << "] " << bitset<32>(W[t]);
        }
        cout << "\n\n" << endl;
        for (int t = 16; t < 80; ++t) {
            W[t] = leftRotate(W[t - 3] ^ W[t - 8] ^ W[t - 14] ^ W[t - 16], 1);
            cout << " W[" << t << "] " << bitset<32>(W[t]);
        }
        cout << "\n\n" << endl;
        while (true) {
            cout << "Press Enter to continue: ";
            string input;
            getline(cin, input);
            if (input.empty()) {
                break;
            }
        }

        // Initialize working variables
        uint32_t A = h0;
        uint32_t B = h1;
        uint32_t C = h2;
        uint32_t D = h3;
        uint32_t E = h4;

        // Main loop
        for (int t = 0; t < 80; ++t) {
            uint32_t F, K;
            if (t < 20) {
                F = (B & C) | ((~B) & D);
                K = 0x5A827999;
            } else if (t < 40) {
                F = B ^ C ^ D;
                K = 0x6ED9EBA1;
            } else if (t < 60) {
                F = (B & C) | (B & D) | (C & D);
                K = 0x8F1BBCDC;
            } else {
                F = B ^ C ^ D;
                K = 0xCA62C1D6;
            }

            uint32_t TEMP = leftRotate(A, 5) + F + E + W[t] + K;
            E = D;
            D = C;
            C = leftRotate(B, 30);
            B = A;
            A = TEMP;
            cout << " A :" << bitset<32>(A) << " B :" << bitset<32>(B) << " C :" << bitset<32>(C) << " D :" << bitset<32>(D) << " E :" << bitset<32>(E) << endl;
        }
        
        cout << "\n\n" << endl;
        cout << "after 80 rounds we get" << endl;

        // Update hash values
        h0 += A;
        h1 += B;
        h2 += C;
        h3 += D;
        h4 += E;
        
        cout << " A :" << bitset<32>(A) << " B :" << bitset<32>(B) << " C :" << bitset<32>(C) << " D :" << bitset<32>(D) << " E :" << bitset<32>(E) << endl;

    }
    
    // Concatenate final hash
    stringstream hash;
    hash << hex << setfill('0');
    hash << setw(8) << h0 << setw(8) << h1 << setw(8) << h2 << setw(8) << h3 << setw(8) << h4;

    return hash.str();
}


