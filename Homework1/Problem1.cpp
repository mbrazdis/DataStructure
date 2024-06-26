
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

/*Numim perechea (x,y) pereche ordonată dacă x<y.
(a) Să se verifice dacă un vector conţine doar perechi ordonate (care satisfact
    condiţia de mai sus) (1p).

(b) Să se verifice dacă oricare x din prima jumătate a vectorul formează o
    pereche ordonată cu oricare y din cea de-a doua jumătate.(2p)*/

bool perechiOrdonate(std::vector<std::pair<int, int>>& myList) {
    for (const auto& pair : myList) {
        if (pair.first >= pair.second)
            return false;
    }
    return true;
}
bool jumatatiOrdonate(std::vector<std::pair<int, int>>& myList) {
    size_t halfSize = myList.size() / 2;
    for(auto it = myList.begin(); it != myList.begin() + halfSize; ++it) {
        const auto& pair = *it;
        for(auto it2 = myList.begin() + halfSize; it2 != myList.end(); ++it2) {
            const auto& pair2 = *it2;
            if (pair.first >= pair2.second) {
                return false;
            }
        }
    }
    return true;
}

std::vector<std::pair<int, int>>* citire(const std::string& filename) {
    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cerr << "Nu s-a putut deschide fisierul!" <<std::endl;
        return nullptr;
    }
    auto* myList = new std::vector<std::pair<int, int>>();
    int firstElement, secondElement;
    while (inputFile >> firstElement >> secondElement) {
        myList->push_back(std::make_pair(firstElement, secondElement));
    }

    inputFile.close();
    return myList;

}

int main() {
    std::vector<std::pair<int, int>>* myList = citire("/Users/mikebraz/Desktop/faculta/SD/tema1/problema1/data.txt");
    if(!myList) {
        return 1;
    }

    std::cout << std::endl << "Vectorul de perechi este: " << std::endl;
    for (const auto& pair : *myList) {
        std::cout << "(" << pair.first << "," << pair.second << ")" << ", " ;
    }
    std::cout << std::endl;
    std::cout << std::endl;

    if (perechiOrdonate(*myList)) {
        std::cout << "a) Perechile sunt ordonate." << std::endl;
    } else {
        std::cout << "a) Perechile nu sunt ordonate." << std::endl;
    }

    std::cout << std::endl;

    if (jumatatiOrdonate(*myList)) {
        std::cout << "b) Oricare x din prima jumătate a vectorul formează o\n"
                     "pereche ordonată cu oricare y din cea de-a doua jumătate." << std::endl;
    } else {
        std::cout << "b) Oricare x din prima jumătate a vectorul NU formează o\n"
                     "pereche ordonată cu oricare y din cea de-a doua jumătate." << std::endl;
    }

    delete myList;
    return 0;
}

