#include <iostream>
#include <vector>
#include <fstream>
/*
Se consideră un vector V cu nr elemente numere naturate. Să se construiască un al doilea vector W ,
care conţine fiecare element din V , care are în compo- nenţă doar cifre impare, dublicându-le.(2p)
Exemplu: V=[1,2,5,13,27,3,57]->W=[1,1,5,5,13,13,3,3,57,57]
*/

std::vector<int>* citire(const std::string& filename) {
    std::ifstream inputFile(filename);
    if(!inputFile) {
        std::cerr << "Nu s-a putut deschide firiserul!";
        return nullptr;
    }
    auto* myList = new std::vector<int>();
    int elem;
    while(inputFile >> elem) myList->push_back(elem);
    inputFile.close();
    return myList;
}

std::vector<int>* dublareImpare(std::vector<int>& myList){
    auto* w = new std::vector<int>();
    for(const auto& elem : myList) {
        if(elem % 2 == 1) {
            w->push_back(elem);
            w->push_back(elem);
        }
    }
    return w;
}

int main() {
    std::vector<int>* myList = citire("/Users/mikebraz/Desktop/faculta/SD/tema1/problema4/data.txt");
    if(!myList) return 1;
    std::cout << "V=[";
    for(const auto& elem : *myList) {
        std::cout << elem << ",";
    }
    std::cout << "]" << std::endl;

    std::vector<int>* w = dublareImpare(*myList);
    if(!w) return 1;
    std::cout << "W=[";
    for(const auto& item : *w) {
        std::cout << item << ",";
    }
    std::cout << "]";

    delete myList;
    delete w;
    return 0;
}
