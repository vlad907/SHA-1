#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <limits>
#include <vector>
#include <cstdlib>
#include "main.h"

//all included header files for all hash algorithms
#include "../djb2/djb2.h"
#include "../sha1/sha1.h"
#include "../sha1/sha1test.h"
#include "../djb2/djb2test.h"


// library for openssl sha1
#include <openssl/sha.h>


using namespace std;

void choose(){
    int choice;
    bool t = true;
    while(t) {
        //ascii art
        fstream ascii("src/ascii.txt");
        string line;
        while (getline(ascii, line)) {
            cout << line << endl;
        }
        //selection
        fstream select("src/selection.txt");
        while (getline(select, line)) {
            cout << line << endl;
        }
        // Get user input
        std::cin >> choice;

        // Validate input
        if (std::cin.fail() || choice < 1 || choice > 3) {
            std::cin.clear(); // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "❌ Invalid choice! Please enter a number between 1 and 3.\n";
            continue; // Restart the loop
        }
        // Process valid choices
        switch (choice) {
            case 1:
                system("clear");
                djb2();
                t = false;
                break;
            case 2:
                system("clear");
                sha();
                t = false;
                break;
            case 3:
                system("clear");
                test();
                break;
            default:
                std::cout << "Unknown error occurred.\n";
        }

    }
}

void djb2() {
    string input;

    // Clear the input buffer to handle leftover newline characters
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    cout << "Enter a string to hash: ";
    getline(cin, input); // Use getline to handle spaces in input

    unsigned long hashValue = djb2Hash(input);
    cout << "Hash Value: " << hashValue << endl;

    cout << "Continue with DJB2? (y/n): ";
    char choice;
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        djb2(); // Recursive call for DJB2
    } else {
        cout << "DJB2 skipped." << endl;
        system("clear");
        choose();
    }
}

void sha() {
    string input;
    // Clear the input buffer to handle leftover newline characters
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "Enter a message: ";
    getline(cin, input);

    string hash = sha1(input);
    cout << "SHA-1 Hash: " << hash << endl;
    cout << "Continue with SHA-1? (y/n): ";
    char choice;
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        sha(); // Recursive call for sha
    } else {
        cout << "SHA-1 skipped." << endl;
        system("clear");
        choose();
    }
}

string sha1_openssl(const string& input) {
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1(reinterpret_cast<const unsigned char *>(input.c_str()), input.size(), hash);

    // Convert the hash to a hexadecimal string
    std::ostringstream hex_stream;
    for (int i = 0; i < SHA_DIGEST_LENGTH; ++i) {
        hex_stream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }

    return hex_stream.str();
}

void testdj() {
    vector<string> test_cases = {
        "", // Empty string
        "aaaaaaaaaaaaaaaaaaaaaaaa", // Long string of repeated characters
        "test",
        "helloworld",
        "123456" //testing
    };
    
    int passed = 0;
    
    for (int i = 0; i < test_cases.size(); i++) {
        unsigned long test = djb2test(test_cases[i]);
        if (djb2test(test_cases[i]) == test) {
            cout << "test number " << i+1 << " test case input : " << test_cases[i] << " test case output : "<< test <<  " : passed" << endl;
            passed++;
        } else {
            cout << "test number " << i+1 << " test case input : " << test_cases[i] << " expected test case output : " << test << " : failed" << endl;
        }
    }
    
    cout << "passed tests: " << passed << " out of " << test_cases.size() << " test cases" << endl;
    
    while (true) {
        cout << "Press Enter to continue: ";
        string input;
        getline(cin, input);
        if (input.empty()) {
            system("clear");
            break;
        }
    }
}

void testsha1() {
    vector<string> test_cases = {
        "", // Empty string
        "abc", // Known SHA-1 test vector
        "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq", // Long string
        "The quick brown fox jumps over the lazy dog", // Common test phrase
        "The quick brown fox jumps over the lazy dog.", // Same as above, but with a period
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", // Long string of repeated characters
        "1234567890", // Numbers only
        "!@#$%^&*()_+-={}[]|\\:\";'<>?,./", // Special characters
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Praesent.", // Mixed input
        std::string(511, 'a'), // 511 characters (edge case before 512-bit chunk)
        std::string(512, 'a'), // 512 characters (one full chunk)
        std::string(513, 'a')  // 513 characters (one chunk + 1)
    };
    
    int passed = 0;
    
    for (int i = 0; i < test_cases.size(); i++) {

        if (SHA_1(test_cases[i]) == sha1_openssl(test_cases[i])) {
            cout << "test number " << i+1 << " test case input : " << test_cases[i] << " test case output : "<< sha1_openssl(test_cases[i]) <<  " : passed" << endl;
            passed++;
        } else {
            cout << "test number " << i+1 << " test case input : " << test_cases[i] << " expected test case output : " << sha1_openssl(test_cases[i]) << " : failed" << endl;
        }
    }
    
    cout << "passed tests: " << passed << " out of " << test_cases.size() << " test cases" << endl;
    
    while (true) {
        cout << "Press Enter to continue: ";
        string input;
        getline(cin, input);
        if (input.empty()) {
            system("clear");
            break;
        }
    }

}

void test() {
    string input;
    // Clear the input buffer to handle leftover newline characters
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    cout << "Please select the following" << endl;
    cout << "[1] DJB2 testing" << endl;
    cout << "[2] SHA-1 testing" << endl;
    getline(cin, input);
    if (input == "1") {
        testdj();
    }else if (input == "2") {
        testsha1();
    }
}


int main () {
    choose();
    return 0;
}