#include <iostream>
#include <fstream>
#include <vector>

/*
 * Să se verifice şi să se afişeze dacă un vector
 * este superior sau inferior. Un vector este superior
 * dacă acesta conţine mai multe elemente cu valoarea
 * mai mare decât media aritmetică a întregului vector
 * şi inferior altfel.(2p)
*/

std::vector<int>* citire (const std::string& filename) {
    std::ifstream inputFile(filename);
    if(!inputFile) {
        std::cerr << "Fisierul nu s-a putut deschide" << std::endl;
        return nullptr;
    }
    auto* myList = new std::vector<int>;
    int elem;
    while (inputFile >> elem) {
        myList->push_back(elem);
    }
    inputFile.close();
    return myList;

}

bool medieAritmetica(std::vector<int>& myList) {
    int sum = 0;
    for(const auto& item : myList){
        sum += item;
    }
    size_t size = myList.size();
    double aritmetica = sum / size;
    int cont = 0;
    for(const auto& item : myList) {
        if(item > aritmetica) ++cont;
    }
    if(cont > size/2) return true;
    else return false;
}

int main() {

    std::vector<int>* myList = citire("/Users/mikebraz/Desktop/faculta/SD/tema1/problema2/data.txt");
    if(!myList) {
        return 1;
    }

    std::cout << "Vectorul este urmatorul: " << std::endl;
    for (const auto& elem : *myList){
        std::cout << elem << ", ";
    }
    std::cout << std::endl;

    if(medieAritmetica(*myList)) {
        std::cout << "Vectorul este superior";
    } else {
        std::cout << "Vectorul este inferior";
    }

    delete myList;
    return 0;
}
