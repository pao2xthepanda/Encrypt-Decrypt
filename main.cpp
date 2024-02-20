#include <iostream>
#include <cctype>
#include <cstring>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

string encryption(string inputPlain, string key){
    int inputPlainArray[inputPlain.length()] = {};
    int outputArray[inputPlain.length()] = {};
    int keyArray[key.length()] = {};
    for (int i = 0; i < inputPlain.length(); ++i){
        inputPlainArray[i] = inputPlain[i] - 64;
        if (i < key.length()){
            keyArray[i] = key[i] - 64;
        }
    }
    for (int i = 0; i < inputPlain.length(); ++i){
        if (i < key.length()){
            outputArray[i] = inputPlainArray[i] + keyArray[i] + 64;
            while (outputArray[i] < 32){
                outputArray[i] = outputArray[i] + 95;
            }
            while (outputArray[i] > 126){
                outputArray[i] = outputArray[i] - 95;
            }
        }
        else {
            outputArray[i] = inputPlainArray[i] + 64;
            while (outputArray[i] < 32){
                outputArray[i] = outputArray[i] + 95;
            }
            while (outputArray[i] > 126){
                outputArray[i] = outputArray[i] - 95;
            }
        }
    }
    int outputSize = sizeof(outputArray) / sizeof(outputArray[0]);
    string outputCipher;
    for (int i = 0; i < outputSize; ++i) {
        outputCipher += static_cast<char>(outputArray[i]);
        }
    return outputCipher;
}

string decryption(string inputCipher, string key){
    int inputCipherArray[inputCipher.length()] = {};
    int outputArray[inputCipher.length()] = {};
    int keyArray[key.length()] = {};
    for (int i = 0; i < inputCipher.length(); ++i){
        inputCipherArray[i] = inputCipher[i] - 64;
        if (i < key.length()){
            keyArray[i] = key[i] - 64;
        }
    }
    for (int i = 0; i < inputCipher.length(); ++i){
        if (i < key.length()){
            outputArray[i] = inputCipherArray[i] - keyArray[i] + 64;
            while (outputArray[i] < 32){
                outputArray[i] = outputArray[i] + 95;
            }
            while (outputArray[i] > 126){
                outputArray[i] = outputArray[i] - 95;
            }
        }
        else {
            outputArray[i] = inputCipherArray[i] + 64;
            while (outputArray[i] < 32){
                outputArray[i] = outputArray[i] + 95;
            }
            while (outputArray[i] > 126){
                outputArray[i] = outputArray[i] - 95;
            }
        }
    }
    int outputSize = sizeof(outputArray) / sizeof(outputArray[0]);
    string outputPlain;
    for (int i = 0; i < outputSize; ++i) {
        outputPlain += static_cast<char>(outputArray[i]);
        }
    return outputPlain;
}

int main(){
    int method;
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
        output = encryption(input, key);
    }
    else if (method == 2){
        output = decryption(input, key);
    }
    else {
        return 1;
    }
    result << output;
    result.close();
    return 0;
}