#include <iostream>
#include <cctype>
#include <cstring>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

string vignereEncAscii(string input, string key){
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

string vignereDecAscii(string input, string key){
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
    cout << "1 - Vignere, 2 - Beaufort: ";
    cin >> algorithm;
    while (algorithm != 1 && algorithm != 2){
        cout << "Invalid Value. Enter Valid Input.\n1 - Vignere, 2 - Beaufort: ";
        cin >> algorithm;
    }
    cout << "1 - Encryption, 2 - Decryption: ";
    cin >> method;
    while (method != 1 && method != 2){
        cout << "Invalid Value. Enter Valid Input.\n1 - Encryption, 2 - Decryption: ";
        cin >> method;
    }
    if (method == 1 && algorithm == 1){
        output = vignereEncAscii(input, key);
    }
    else if (method == 2 && algorithm == 1){
        output = vignereDecAscii(input, key);
    }
    else if (method == 1 && algorithm == 2){
        output = vignereDecAscii(input, key);
    }
    else if (method == 2 && algorithm == 2){
        output = vignereEncAscii(input, key);
    }
    else {
        return 1;
    }
    result << output;
    result.close();
    return 0;
}