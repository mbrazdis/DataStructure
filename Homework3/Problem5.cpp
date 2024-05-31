#include <iostream>
#include <unordered_set>
#include <fstream>

/*
Permutări. Se consideră două şiruri de caractere (citite din fişier). 
Să se scrie o funcţie care are ca parametru cele două şiruri şi care 
returnează true dacă al doilea este o permutare a primului şi false altfel. 
Implementaţi folosind unordered_set din stl. (2p)
*/

bool permutari(const std::string& string1, const std::string& string2){
    std::unordered_set<std::pair<char, int>> set1 (string1.begin(), string1.end());
    std::unordered_set<std::pair<char, int>> set2;

    for(char ch1 : string1) {

    }
}

std::pair<std::string, std::string>* citire(const std::string& fileName) {
    std::ifstream inputFile(fileName);
    std::string string1, string2;

    if(!inputFile) {
        std::cerr << "Fisierul nu s-a putu deschide!";
        return nullptr;
    }
    std::getline(inputFile, string1);
    std::getline(inputFile, string2);

    auto * pereche = new std::pair<std::string, std::string>();
    inputFile.close();
    return pereche;
}

int main() {
    auto* pereche = citire("/Users/mikebraz/Desktop/faculta/SD/Tema3/problema5/data.txt");
    auto pair1 = pereche->first;
    auto pair2 = pereche->second;
    permutari(pair1, pair2);
    return 0;
}
