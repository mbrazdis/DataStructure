#include <iostream>
#include <unordered_map>
#include <fstream>
#include <list>
#include <sstream>

/* Problema 6
Se consideră un număr de competiţii sportive la care s-au inscris concurenţi.
Pentru fiecare competiţie există o listă cu numele şi prenumele concurenţilor
(pereche de valori de tip std::string). Aceste liste se citesc dintr- un fişier.
Să se scrie o funcţie care indică persoanele care participă la mai mult de o singură competiţie. (2p)
*/


//pentru a calcula hash-ul unei perechi pair. esential pentru a folosi pair ca si key intr-un unordered_map
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};


void participariMultiple (std::unordered_map<std::string, std::list<std::pair<std::string, std::string>>>& myList) {
    std::unordered_map<std::pair<std::string, std::string>, int, pair_hash> participariMultiple;

for(auto& sport : myList){
        for(auto& participant : sport.second) participariMultiple[participant]++;
    }

for(auto& participare : participariMultiple){
        if (participare.second > 1) {
            std::cout << participare.first.first << " " << participare.first.second << std::endl;
        }
    }
}

std::unordered_map<std::string, std::list<std::pair<std::string, std::string>>>* citire (const std::string& fileName) {
    std::ifstream inputFile(fileName);
    if (!inputFile) {
        std::cerr << "Fisierul nu s-a putut deschide!";
        return nullptr;
    }
    auto *mylist = new std::unordered_map<std::string, std::list<std::pair<std::string, std::string>>>();
    std::string line;
    while (getline(inputFile, line)) {
        std::istringstream ss(line);
        std::string competitie;
        std::getline(ss, competitie, '-');

        competitie.erase(0, competitie.find_first_not_of(" \t"));
        competitie.erase(competitie.find_last_not_of(" \t") + 1);

        std::string names;
        std::getline(ss, names);

        std::list<std::pair<std::string, std::string>> participanti;
        std::istringstream nameStream(names);
        std::string name;

        while (std::getline(nameStream, name, ',')) {
            name.erase(0, name.find_first_not_of(" \t"));
            name.erase(name.find_last_not_of(" \t") + 1);

            std::istringstream numeComplet(name);
            std::string nume, prenume;
            std::getline(numeComplet, prenume, ',');
            std::getline(numeComplet, nume);

            participanti.emplace_back(prenume, nume);
        }
        (*mylist)[competitie] = participanti;
    }
    return mylist;
}
int main() {
    auto* myList = citire("/Users/mikebraz/Desktop/faculta/SD/Tema3/problema6/data.txt");
    std::cout << "\nPersoanele care participa la mai multe competitii sunt urmatoarele:\n\n";
    participariMultiple(*myList);
    delete myList;
    return 0;
}
