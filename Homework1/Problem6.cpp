#include <iostream>
#include <vector>
#include <fstream>

/*
Se consideră un vector de n puncte. Fiecare punct este un element de tipul
unei structuri cu două câmpuri, reprezentând coordonatele spaţiale (x, y).
Să se afişeze perechile de 4 puncte care pot forma un dreptunghi.
Dacă nu există astfel de pereche se va afişa un mesaj corespunzător(3p)
*/

struct Point {
    int x;
    int y;
};

std::vector<Point>* citire(const std::string& filename){
    std::ifstream inputFile(filename);
    if(!inputFile){
        std::cerr << "Fisierul nu s a putut deschide!";
        return nullptr;
    }
    auto* puncte = new std::vector<Point>();
    int x, y;
    while (inputFile >> x >> y) {
        puncte->push_back({x, y});
    }
    inputFile.close();
    return puncte;
}

bool perpendicular(Point p1, Point p2, Point p3) {
    return (p2.y - p1.y) * (p3.y - p2.y) + (p2.x - p1.x) * (p3.x - p2.x) == 0;
}

std::vector<std::vector<Point>>* dreptunghi (std::vector<Point>& puncte) {
    auto dreptunghiuri = new std::vector<std::vector<Point>>();
    int n = puncte.size();
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            for(int k = j + 1;k < n; k++){
                for(int l = k + 1; l < n; l++){
                    Point a = puncte[i];
                    Point b = puncte[j];
                    Point c = puncte[k];
                    Point d = puncte[l];
                    if(perpendicular(a, b, c) && perpendicular(b, c, d) && perpendicular(c, d, a) && perpendicular(d, a, b) ||
                       perpendicular(a, c, b) && perpendicular(c, b, d) && perpendicular(b, d, a) && perpendicular(d, a, c) ||
                       perpendicular(a, b, d) && perpendicular(b, d, c) && perpendicular(d, c, a) && perpendicular(c, a, b)){
                        dreptunghiuri->push_back({a, b, c, d});
                    }
                }
            }
        }
    }
    return dreptunghiuri;
}

int main() {
    std::vector<Point>* puncte = citire("/Users/mikebraz/Desktop/faculta/SD/tema1/problema6/data.txt");

    std::cout << "Vectorul de puncte este urmatorul: \n";
    for(const auto& elem : *puncte) {
        std::cout << "(" <<elem.x << ", " << elem.y << ")" << std::endl;
     }

    std::vector<std::vector<Point>>* dreptunghiuri = dreptunghi(*puncte);
    if(!dreptunghiuri->empty()) {
        for(const auto& dr : *dreptunghiuri) {
            for (const auto &p : dr) {
                std::cout << "(" << p.x << ", " << p.y << ") ";
            }
            std::cout << std::endl;
        }
    } else {
        std::cerr << "Nu s-au gasit perechi de puncte care sa formeze dreptunghiuri!";

    }
    delete puncte;
    delete dreptunghiuri;
    return 0;
}
