#include <iostream>
#include <cctype>
#include <cstring>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

string vignereAsciiEnc(string input, string key){
    int inputArray[input.length()] = {};
    int outputArray[input.length()] = {};
    int keyArray[key.length()] = {};
    for (int i = 0; i < input.length(); ++i){
        inputArray[i] = input[i] - 64;
    }
    for (int i = 0; i < key.length(); ++i){
        keyArray[i] = key[i] - 64;
    }
    int inputArraySize = sizeof(inputArray) / sizeof(inputArray[0]);
    int keyArraySize = sizeof(keyArray) / sizeof(keyArray[0]);
    std::vector<int> keyStream;
    while (keyStream.size() < inputArraySize) {
        keyStream.insert(keyStream.end(), keyArray, keyArray + keyArraySize);
    }
    keyStream.resize(inputArraySize);
    for (int i = 0; i < input.length(); ++i){
        outputArray[i] = inputArray[i] + keyStream[i] + 64;
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

string vignereAsciiDec(string input, string key){
    int inputArray[input.length()] = {};
    int outputArray[input.length()] = {};
    int keyArray[key.length()] = {};
    for (int i = 0; i < input.length(); ++i){
        inputArray[i] = input[i] - 64;
    }
    for (int i = 0; i < key.length(); ++i){
        keyArray[i] = key[i] - 64;
    }
    int inputArraySize = sizeof(inputArray) / sizeof(inputArray[0]);
    int keyArraySize = sizeof(keyArray) / sizeof(keyArray[0]);
    std::vector<int> keyStream;
    while (keyStream.size() < inputArraySize) {
        keyStream.insert(keyStream.end(), keyArray, keyArray + keyArraySize);
    }
    keyStream.resize(inputArraySize);
    for (int i = 0; i < input.length(); ++i){
        outputArray[i] = inputArray[i] - keyStream[i] + 64;
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
    int method = -1;
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
    cout << "1 - Encryption, 2 - Decryption: ";
    cin >> method;
    if (method == 1){
        output = vignereAsciiEnc(input, key);
    }
    else if (method == 2){
        output = vignereAsciiDec(input, key);
    }
    else {
        return 1;
    }
    result << output;
    result.close();
    return 0;
}