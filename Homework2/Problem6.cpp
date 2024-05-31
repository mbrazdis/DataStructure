#include <iostream>
#include <fstream>
#include <queue>
#include <random>

/*
Implementare coadă. Să se implementeze o coadă utilizând liste înlănţuite. Vă trebuie:
• o structură node cu două câmpuri - un câmp pentru informaţie (de tipul cerut de problema curentă) 
 şi un câmp de tip pointer la node pentru legătura la elementul următor.
• o structură Queue cu
– două câmpuri de tip pointer la nod, pentru primul şi ultimul element iniţializate cu NULL (nullptr).
– un câmp nr_elem de tip int - numărul de elemente din coada.
- funcţia push(elem) - pune elem la sfarsitul cozii
– funcţia pop() - elimină elementul de la începutul cozii
– funcţile front() şi back() returnează primul respectiv ultimul element din coadă
– funcţia empty() - verifică dacă coada este vidă.
– funcţia clear() - goleşte coada
– funcţia size() - returnează numărul de elemente din coada
Această coadă va fi utilizată în următoarea problemă:
La un examen se pot prezenta candidaţi pe durata a două zile. 
În fiecare zi timpul alocat pentru examinare este de t ore (t ≤ 5). 
La examen se înscriu n candidaţi. Se citesc din fişier t, n 
precum şi candidaţii cu numele (de tip std::string). 
Ei vor fi introduşi într-o coadă, de unde vor fi extraşi pe rând pentru examinare. 
Pentru fiecare candidat, care este la rând, se generează o durată aleatorie cu o valoare între 15 minute şi 25 minute. În momentul în care timpul t s-a terminat, deci se încheie prima zi de evaluare, candidaţii care au rămas în coada vor fi extraşi pe rând şi trecuţi într-un fişier de ieşire, care va reprezenta lista candidaţilor pentru ziua a doua de examinare. (4p)
*/



struct node {
    std::string nume;
    node *next;
};

struct Queue {
    node *front = nullptr;
    node *back = nullptr;
    int nr_elem = 0;

    void push(node *elem) {
        if(!front) {
            front = elem;
            back = elem;
        } else {
            back->next = elem;
            back = elem;
        }
        elem->next = nullptr;
        nr_elem++;
    }

    void pop() {
        if(!front) {
            return;
        }
        node* temp = front;
        if (front == back) {
            front = nullptr;
            back = nullptr;
        } else {
            front = front->next;
        }
        delete temp;
        nr_elem--;
    }

    std::string rfront() const {
        if(front) {
            return front->nume;
        }
        return "";

    }

    std::string rback() const {
        if(back) {
            return back->nume;
        }
        return "";
    }

    bool empty() const {
        return nr_elem == 0;
    }
    void clear () {
        while(!front) {
            pop();
        }
    }
    int size() const {
        return nr_elem;
    }
    bool citire(const std::string &fileName, int &t, int &n) {
        std::ifstream file(fileName);
        if(!file.is_open()) {
            std::cerr << "Fisierul nu s a putut deschide" << std::endl;
            return false;
        }
        file >> t;
        file >> n;
        file.ignore();

        std::string name;
        for(int i = 0; i < n; i++){
            std::getline(file, name);
            node *newNode = new node();
            newNode->nume = name;
            this->push(newNode);
        }
        file.close();
        return true;

    }
    static void printare(const std::string &fileName, const Queue &queue) {
        std::ofstream file(fileName);
        if(!file.is_open()) {
            std::cerr << "fisierul nu s a putut deschide" << std::endl;
            return;
        }
        file << queue.nr_elem << "\n";
        node* current = queue.front;
        while(current) {
            file << current->nume << "\n";
            current = current->next;
        }
        file.close();
    }

};

int generateRandomNumber(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}

int main() {

    Queue q;
    Queue q2;
    int t, n;
    q.citire("/Users/mikebraz/Desktop/faculta/SD/Tema2/problema6/dataIn.txt", t, n);

    int timp = t * 60;
    while(!q.empty() && timp > 0) {
        timp -= generateRandomNumber(15,25);
        if(timp >= 0) {
            q.pop();
        }
    }
    while (!q.empty()) {
        q2.push(new node{q.rfront(), nullptr});
        q.pop();
    }

    Queue::printare("/Users/mikebraz/Desktop/faculta/SD/Tema2/problema6/dataOut.txt", q2);

    return 0;
}
