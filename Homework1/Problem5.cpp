#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
/*
Un număr de bază b este reţinut într-un std:pair<int, int> ce conţine
valoarea şi baza de numeraţie în care acesta este reprezentat. Se citesc mai multe
astfel de numere reprezentate în baze diferite.
Să se determine perechile de valori egale.(3p)
*/

std::vector<std::pair<int, int>>* citire(const std::string& fileName) {
    std::ifstream inputFile(fileName);
    if(!inputFile) {
        std::cerr << "Fisierul nu s a putut deschide";
        return nullptr;
    }
    auto* myList = new std::vector<std::pair<int, int>>();
    int numar, baza;
    while(inputFile >> numar >> baza) {
        myList->push_back(std::make_pair(numar, baza));
    }
    inputFile.close();
    return myList;
}

void determinarePerechiEgale(const std::vector<std::pair<int, int>>& myList) {
    std::unordered_map<int, std::vector<int>> mp;

    for(const auto& p : myList) {
        int valoare = p.first;
        int baza = p.second;
        mp[valoare].push_back(baza);
    }

    std::cout << "Perechi de valori egale: \n";
    for (const auto& entry : mp) {
        if (entry.second.size() > 1) {
            std::cout << "Valoare: " << entry.first << ", Baze: ";
            for (const auto& base :entry.second) {
                std::cout << " " << base;
            }
            std::cout << ")\n";
        }
    }
}

int main() {
    std::vector<std::pair<int, int>>* myList = citire("/Users/mikebraz/Desktop/faculta/SD/tema1/problema5/data.txt");
    if (!myList) return 1;

    std::cout << "Perechile introduse sunt urmatoarele: \n";
    for(const auto& elem : *myList) {
        std::cout << "(" << elem.first << ", " << elem.second << ")\n";
    }
    determinarePerechiEgale(*myList);
    delete myList;
    return 0;
}
