#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <utility>

/*
Operaţii pe un arbore binar. Se citeşte dintr-un fişier un arbore binar. (2.5p).
Modul de citire este la alegere.Variante propuse:
• se citesc 2 parcurgeri din care se construieşte arborele
• se citesc: 3 vectori - unul cu cheile arborelui, unul cu copii stângi pentru fiecare nod,
unul cu copii drepţi pentru fiecare nod
• citire pe niveluri (în lăţime)
• printr-un vector de taţi
Să se implementeze următoarele funcţii pentru arbore:
• O funcţie ce calculează înălţimea unui subarbore (1p).
• Funcţii pentru parcurgerea arborelui (RSD, SRD, SDR, Niveluri) (1p). •
 O funcţie care afişează frunzele de la stânga la dreapta (1p).
• O funcţie care verifică dacă doi arbori sunt identici (2p).
• O funcţie care verifică dacă un arbore e complet (1p).
*/


struct Node {
    int data;
    Node* left;
    Node* right;

    explicit Node(int x) : data(x), left(nullptr), right(nullptr) {}
};

std::queue<int>* parcurgereRSD(Node* root, std::queue<int>* coada) {
    if(root == nullptr) return coada;

    coada->push(root->data);
    parcurgereRSD(root->left, coada);
    parcurgereRSD(root->right, coada);

    return coada;
}

std::queue<int>* parcurgereSRD(Node* root, std::queue<int>* coada) {
    if(root == nullptr) return coada;

    parcurgereSRD(root->left, coada);
    coada->push(root->data);
    parcurgereSRD(root->right, coada);

    return coada;
}

std::queue<int>* parcurgereSDR(Node* root, std::queue<int>* coada) {
    if(root == nullptr) return coada;

    parcurgereSDR(root->left, coada);
    parcurgereSDR(root->right, coada);
    coada->push(root->data);

    return coada;
}

void afisareFrunze(Node* root) {
    if(root == nullptr) return;
    if (root->left == nullptr && root->right == nullptr)
        std::cout << root->data << " ";
    afisareFrunze(root->left);
    afisareFrunze(root->right);
}

bool arboriIdentici(Node* root1, Node* root2) {
    std::queue<int> coada1, coada2;
    parcurgereRSD(root1, &coada1);
    parcurgereRSD(root2, &coada2);
    while(!coada1.empty() || !coada2.empty()){
        if(coada1.front() != coada2.front()) return false;
        else {
            coada1.pop();
            coada2.pop();
        }
    }
    return true;
}

int lungimeMax(Node* node) {
    if(node == nullptr) {
        return -1;
    }
    int lungimeStanga = lungimeMax(node->left);
    int lungimeDreapta = lungimeMax(node->right);
    return 1 + std::max(lungimeStanga, lungimeDreapta);
}

Node* citireInLatime(const std::string &fileName){
    std::ifstream inputFile(fileName);
    if(!inputFile) {
        std::cerr << "Fisierul nu s-a putut deschide!";
        return nullptr;
    }

    std::string line;
    std::getline(inputFile, line);
    std::istringstream iss(line);
    int data;

    if (!(iss >> data)) {
        return nullptr;
    }

    Node* root = new Node(data);
    std::queue<Node*> coada;
    coada.push(root);

    while(!coada.empty()) {
        Node* curent = coada.front();
        coada.pop();

        if(iss >> data){
            if(data != 0){
                curent->left = new Node(data);
                coada.push(curent->left);
            }
        }

        if(iss >> data) {
            if(data != 0) {
                curent->right = new Node(data);
                coada.push(curent->right);
            }
        }
    }
    inputFile.close();
    return root;
}

void afisare(std::queue<int>* coada){
    while(!coada->empty()){
        std::cout << coada->front() << " ";
        coada->pop();
    }
    std::cout << std::endl;
}

int main() {

    Node* root = citireInLatime("/Users/mikebraz/Desktop/faculta/SD/tema4/problema2/data.txt");
    Node* root2 = citireInLatime("/Users/mikebraz/Desktop/faculta/SD/tema4/problema2/data2.txt");

    std::queue<int> coadaRSD;
    parcurgereRSD(root, &coadaRSD);
    std::cout << "Parcurgere RSD: ";
    afisare(&coadaRSD);

    std::queue<int> coadaSRD;
    parcurgereSRD(root, &coadaSRD);
    std::cout << "Parcurgere SRD: ";
    afisare(&coadaSRD);

    std::queue<int> coadaSDR;
    parcurgereSDR(root, &coadaSDR);
    std::cout << "Parcurgere SDR: ";
    afisare(&coadaSDR);

    std::cout << "Frunzele de la stanga la dreapta: ";
    afisareFrunze(root);
    std::cout << std::endl << "Inaltime: " << lungimeMax(root);

    if(arboriIdentici(root, root2)) {
        std::cout << "\nArbori identici!\n";
    } else{
        std::cout << "\nArbori diferiti!\n";
    }
    delete root;
    return 0;
}
