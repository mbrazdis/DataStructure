#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

/*Palindrom. Se consideră un vector de caractere (citit din fişier).
Să se scrie o funcţie care are ca parametru acest şir şi care returnează
un palindrom format cu toate caracterele şirului, dacă acest lucru este
posibil sau un şir vid altfel. Implementaţi eficient folosind unordered_map din stl. (4p)*/

long palindrom(std::vector<int> &vec) {
    std::unordered_map<int, int> freqMap;
    int count = 0;
    long palindrom = 0;
    int imparFreq;
    for(int num : vec) freqMap[num]++;
    for(auto pair : freqMap)
        if(pair.second % 2 == 1) {
            count++;
            imparFreq = pair.first;
        }
    if(count > 1) return 0;
    else {
        for (auto num : freqMap)
            for(int j = 0; j < num.second/2; j++)
                if(num.first != imparFreq) palindrom = (palindrom * 10) + num.first;
        long copyPalindrom = palindrom;
        for(int i = 0; i < freqMap[imparFreq]; i++) palindrom = (palindrom * 10) + imparFreq;
        while(copyPalindrom != 0) {
            palindrom = (palindrom * 10) + (copyPalindrom % 10);
            copyPalindrom /= 10;
        }
    }
    return palindrom;
}

std::vector<int>* citire(const std::string& fileName) {
    std::ifstream inputFile(fileName);
    if(!inputFile) {
        std::cerr << "Nu s-a putut deschide fisierul!";
        return nullptr;
    }
    auto* vec = new std::vector<int>();
    int x;
    while(inputFile >> x){
        vec->push_back(x);
    }
    inputFile.close();
    return vec;
}

int main() {
    std::vector<int>* vec = citire("/Users/mikebraz/Desktop/faculta/SD/Tema3/problema 4/data.txt");
    std::cout << palindrom(*vec);
    return 0;
}
