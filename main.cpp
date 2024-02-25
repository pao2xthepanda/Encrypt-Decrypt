#include <iostream>
#include <cctype>
#include <cstring>
#include <string>
#include <vector>
#include <fstream>
#include <bitset>
using namespace std;

string aesEncAscii(string input, string key, int algorithm){
    int lengthFactor = 128;
    while (lengthFactor < (input.length() * 8)){
        lengthFactor = lengthFactor + 128;
    }
    bool inputArray[lengthFactor] = {};
    int convertDecBin;
    int outputArray[input.length()] = {};
    int keyArray[key.length()] = {};
    for (int i = 0; i < input.length(); ++i){
        convertDecBin = input[i] - 32;
        if (convertDecBin >= 0 && convertDecBin <= 94){
            bitset<8> valueBin = convertDecBin;
            for(int j = 0, k = 7; j < 8; j++, k--){
                inputArray[(i * 8) + j] = valueBin[k];
            }
        }
        else {
            for(int j = 0, k = 7; j < 8; j++, k--){
                inputArray[(i * 8) + j] = 0;
            }
        }
    }
    int outputArraySize = sizeof(inputArray) / sizeof(inputArray[0]);
    string output;
    for (int i = 0; i < outputArraySize; ++i) {
        std::string outputLetter = std::to_string(inputArray[i]);
        output = output + outputLetter;
        }
    return output;
}

string vignereEncAscii(string input, string key, int algorithm){
    int inputArray[input.length()] = {};
    int outputArray[input.length()] = {};
    int keyArray[key.length()] = {};
    for (int i = 0; i < input.length(); ++i){
        inputArray[i] = input[i] - 32;
    }
    for (int i = 0; i < key.length(); ++i){
        if (algorithm == 3){
            keyArray[i] = key[0] - 32;
        }
        else {
            keyArray[i] = key[i] - 32;
        }
    }
    int inputArraySize = sizeof(inputArray) / sizeof(inputArray[0]);
    int keyArraySize = sizeof(keyArray) / sizeof(keyArray[0]);
    std::vector<int> keyStream;
    while (keyStream.size() < inputArraySize) {
        keyStream.insert(keyStream.end(), keyArray, keyArray + keyArraySize);
    }
    keyStream.resize(inputArraySize);
    for (int i = 0; i < input.length(); ++i){
        outputArray[i] = inputArray[i] + keyStream[i] + 32;
        while (outputArray[i] < 32){
            outputArray[i] = outputArray[i] + 95;
        }
        while (outputArray[i] > 126){
            outputArray[i] = outputArray[i] - 95;
        }
    }
    int outputArraySize = sizeof(outputArray) / sizeof(outputArray[0]);
    string output;
    for (int i = 0; i < outputArraySize; ++i) {
        output += static_cast<char>(outputArray[i]);
        }
    return output;
}

string vignereDecAscii(string input, string key, int algorithm){
    int inputArray[input.length()] = {};
    int outputArray[input.length()] = {};
    int keyArray[key.length()] = {};
    for (int i = 0; i < input.length(); ++i){
        inputArray[i] = input[i] - 32;
    }
    for (int i = 0; i < key.length(); ++i){
        if (algorithm == 3){
            keyArray[i] = key[0] - 32;
        }
        else {
            keyArray[i] = key[i] - 32;
        }
    }
    int inputArraySize = sizeof(inputArray) / sizeof(inputArray[0]);
    int keyArraySize = sizeof(keyArray) / sizeof(keyArray[0]);
    std::vector<int> keyStream;
    while (keyStream.size() < inputArraySize) {
        keyStream.insert(keyStream.end(), keyArray, keyArray + keyArraySize);
    }
    keyStream.resize(inputArraySize);
    for (int i = 0; i < input.length(); ++i){
        outputArray[i] = inputArray[i] - keyStream[i] + 32;
        while (outputArray[i] < 32){
            outputArray[i] = outputArray[i] + 95;
        }
        while (outputArray[i] > 126){
            outputArray[i] = outputArray[i] - 95;
        }
    }
    int outputArraySize = sizeof(outputArray) / sizeof(outputArray[0]);
    string output;
    for (int i = 0; i < outputArraySize; ++i) {
        output += static_cast<char>(outputArray[i]);
        }
    return output;
}

int main(){
    int method, algorithm = -1;
    string lineInput, keyInput, input, output, key;
    ifstream source, secret;
    ofstream result("E:/result.txt");
    source.open("E:/source.txt");
    while(!source.eof()) {
        getline(source, lineInput);
	    input += lineInput;
    }
    secret.open("E:/key.txt");
    while(!secret.eof()) {
        getline(secret, keyInput);
	    key += keyInput;
    }
    cout << "1 - Vignere, 2 - Beaufort, 3 - Caesar, 4 - AES: ";
    cin >> algorithm;
    while (algorithm != 1 && algorithm != 2 && algorithm != 3 && algorithm != 4){
        cout << "Invalid Value. Enter Valid Input.\n1 - Vignere, 2 - Beaufort, 3 - Caesar, 4 - AES: ";
        cin >> algorithm;
    }
    cout << "1 - Encryption, 2 - Decryption: ";
    cin >> method;
    while (method != 1 && method != 2){
        cout << "Invalid Value. Enter Valid Input.\n1 - Encryption, 2 - Decryption: ";
        cin >> method;
    }
    if (method == 1 && algorithm == 1){
        output = vignereEncAscii(input, key, algorithm);
    }
    else if (method == 2 && algorithm == 1){
        output = vignereDecAscii(input, key, algorithm);
    }
    else if (method == 1 && algorithm == 2){
        output = vignereDecAscii(input, key, algorithm);
    }
    else if (method == 2 && algorithm == 2){
        output = vignereEncAscii(input, key, algorithm);
    }
    else if (method == 1 && algorithm == 3){
        output = vignereEncAscii(input, key, algorithm);
    }
    else if (method == 2 && algorithm == 3){
        output = vignereDecAscii(input, key, algorithm);
    }
    else if (method == 1 && algorithm == 4){
        output = aesEncAscii(input, key, algorithm);
    }
    else if (method == 2 && algorithm == 4){
        output = aesEncAscii(input, key, algorithm);
    }
    else {
        return 1;
    }
    result << output;
    result.close();
    return 0;
}