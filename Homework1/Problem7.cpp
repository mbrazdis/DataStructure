#include <iostream>
#include <fstream>
#include <vector>

/*
Se consideră o structură fractie, cu câmpurile de tip int numarator şi numitor.
Această structură dispune de o metodă reductie, care reduce fracţia (ex: 12/30 devine 2/5),
de funcţii pentru operaţii aritmetice, de funcţii de comparare.
De asemenea o funcţie de transformare în număr zecimal (ex: 2/5 = 0.4).
Să se se citească un vector de fracţii. Fiecare dintre acestea să se reducă.
Să se sorteze vectorul cât mai eficient şi să se calculeze suma elementelor sale.
Scrieţi funcţii de citire/ afişare pentru fracţii.
Punctajul maxim se acordă pentru rezolvarea completă, elegantă şi eficientă.(4p)
*/


struct fractie{
    int numarator;
    int numitor;

    void reducti(){
        int a = numarator;
        int b = numitor;
        while (a != b){
            if(a > b) a = a - b;
            else if(a < b) b = b - a;
        }
        numarator /= a;
        numitor /= a;
    }
    double numarZecimal() const {
        return static_cast<double> (numarator)/numitor;
    }
};

std::vector<fractie>* citire (const std::string& fileName) {
    std::ifstream inputFile(fileName);
    if(!inputFile){
        std::cerr << "Fisierul nu s a putut deschide!";
        return nullptr;
    }
    auto* myList = new std::vector<fractie>();
    int numarator, numitor;
    while(inputFile >> numarator >> numitor) {
        myList->push_back({numarator,numitor});
    }
    inputFile.close();
    return myList;
}

void afisare(std::vector<fractie>& myList){
    std::cout << "\nFractiile reduse sunt urmatoarele: \n\n";
    std::cout << "Fr init|Fr simp|nr zec\n\n";
    for(auto& elem : myList){

        std::cout << elem.numarator << "/" << elem.numitor << " = ";
        elem.reducti();
        std::cout << elem.numarator << "/" << elem.numitor << " = ";
        std::cout << elem.numarZecimal() << std::endl;
    }
}

int main() {
    auto* myList = citire("/Users/mikebraz/Desktop/faculta/SD/tema1/problema7/data.txt");

    afisare(*myList);

    return 0;
}
