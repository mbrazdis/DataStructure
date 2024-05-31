#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>

/*
Se consideră un vector cu nr elemente numere naturate din intervalul [30,80],
Să se determine şi să se afişeze elementul care apare de cele mai multe ori.(2p)
*/


int nrAparitii(std::vector<int>& myList){
    std::unordered_map<int, int> frecventa;
    for(int numar : myList) {
        frecventa[numar]++;
    }
    int numarMaxim = myList[0];
    int frecventaMax = frecventa[numarMaxim];

    for (const auto& pereche : frecventa) {
        if(pereche.second > frecventaMax) {
        numarMaxim = pereche.first;
        frecventaMax = pereche.second;
        }
    }
    return numarMaxim;
}

std::vector<int>* citire(const std::string& filename) {
    std::ifstream inputFile(filename);
    if(!inputFile) {
        std::cerr << "Nu s-a putut deschide fisierul!";
        return nullptr;
    }
    auto* myList = new std::vector<int>;
    int elem;
    while(inputFile >> elem) {
        if(elem < 30 || elem > 80) {
            std::cerr << "Numerele trebuie sa fie in intervalul [30,80]!";
            return nullptr;
        }
        myList->push_back(elem);
    }
    inputFile.close();
    return myList;


}


int main() {
    std::vector<int>* myList = citire("/Users/mikebraz/Desktop/faculta/SD/tema1/problema3/data.txt");
    if(!myList) return 1;

    std::cout << "Vectorul este: ";
    for(const auto &elem : *myList) {
        std::cout << elem << ", ";
    }
    std::cout << std::endl;
    std::cout << "Numarul care apare de cele mai multe ori in vector este: "
    << nrAparitii(*myList) << std::endl;

    delete myList;
    return 0;
}
