#include <iostream>
#include <list>
#include <fstream>
#include <sstream>

/*
Implementare tabelă de dispersie - liste înlănţuite. Construiţi o clasă HashTable (sau HashMap) potrivită,
care să includă operaţiile de inserţie, căutare şi ştergere. Elementele stocate vor fi de tip (cheie, valoare).
Folosiţi pair din stl. Rezolvarea coliziunilor se va realiza prin liste înlănţuite (folosiţi std::list).
Dacă factorul de încarcare al tabelei depăşeşte 1.0, se cere redi- mensionarea tabelei (aproximativ dublul dimensiunii iniţiale)
şi redistribuirea elementelor în noua tabelă (rehashing). În funcţia main citiţi dintr-un fişier n elemente de tip pereche
(cheie-valoare) (n>20), repartizaţi elementele în tabelă, apoi permiteţi căutarea, adăugarea sau ştergerea de elemente (meniu). (5p).
Punctaj suplimentar - pentru implementarea unei funcţii de hashig pentru şiruri de caractere - 1,5p
ATENŢIE: Nu folosiţi std::vector. Folosiţi eventual std::array sau int * pentru a implementa tabela de dispersie.
*/


class HashTable {
private:
    static const int initialSize = 10;
    int hashGroups;
    std::list<std::pair<int, std::string>>* table;
    std::list<std::pair<std::string, std::string>>* stringTable;

    void rehash();

public:
    HashTable();
    ~HashTable();
    bool isEmpty() const;
    int hashFunction(int key) const;
    int hashFunction(const std::string& key) const;
    void insertItem(int key, const std::string& value);
    void insertItem(const std::string& key, const std::string& value);
    void removeItem(int key);
    void removeItem(const std::string& key);
    std::string searchTable(int key);
    std::string searchTable(const std::string& key);
    void printTable();
};

HashTable::HashTable() {
    hashGroups = initialSize;
    table = new std::list<std::pair<int, std::string>> [hashGroups];
    stringTable = new std::list<std::pair<std::string, std::string>> [hashGroups];
}

HashTable::~HashTable() {
    delete[] table;
    delete[] stringTable;
}

bool HashTable::isEmpty() const {
    int sum{};
    for(int i{}; i < hashGroups; i++){
        sum += table[i].size();
    }
    if(!sum) {
        return true;
    }
    return false;
}

int HashTable::hashFunction(int key) const {
    return key % hashGroups;
}

int HashTable::hashFunction(const std::string &key) const {
    int hash = 0;
    for(char ch : key) {
        hash = (hash * 31 + ch) % hashGroups;
    }
    return hash;
}

void HashTable::insertItem(int key, const std::string& value) {
    int hashValue = hashFunction(key);
    auto& cell = table[hashValue];
    auto bItr = begin(cell);
    bool keyExists = false;
    for (; bItr != end(cell); bItr++) {
        if (bItr->first == key) {
            keyExists = true;
            bItr->second = value;
            std::cout << "[WARNING] Cheia exista. valoarea a fost inlocuita.\n";
            break;
        }
    }
    if (!keyExists) {
        cell.emplace_back(key, value);
    }
    float loadFactor = 0;
    for (int i = 0; i < hashGroups; i++) {
        loadFactor += table[i].size();
    }
    loadFactor /= hashGroups;
    if (loadFactor > 1.0) {
        rehash();
    }
}

void HashTable::insertItem(const std::string& key, const std::string &value) {
    int hashValue = hashFunction(key);
    auto& cell = stringTable[hashValue];
    for(auto& pair : cell) {
        if(pair.first == key) {
            pair.second = value;
            std::cout << "[WARNING] Cheia exista. Valoarea a fost inlocuita.\n";
            return;
        }
    }
    cell.emplace_back(key, value);

    float loadFactor = 0;
    for(int i = 0; i < hashGroups; i++) {
        loadFactor += table[i].size() + stringTable[i].size();
    }
    loadFactor /= hashGroups;
    if(loadFactor > 1.0) {
        rehash();
    }
}


void HashTable::removeItem(int key) {
    int hashValue = hashFunction(key);
    auto& cell = table[hashValue];
    auto bItr = begin(cell);
    bool keyExists = false;
    for(; bItr != end(cell); bItr++) {
        if(bItr->first == key) {
            keyExists = true;
            cell.erase(bItr);
            std::cout << "[Info] Perechea a fost stearsa!\n";
            break;
        }
    }
    if(!keyExists) {
        std::cout << "[WARNING] Cheia nu exista. Perechea nu a fost stearsa!\n";
    }
}

void HashTable::removeItem(const std::string &key) {
    int hashValue = hashFunction(key);
    auto& cell = stringTable[hashValue];
    auto bItr = begin(cell);
    bool keyExists = false;
    for(; bItr != end(cell); bItr++) {
        if(bItr->first == key) {
            keyExists = true;
            cell.erase(bItr);
            std::cout << "[Info] Perechea a fost stearsa!\n";
            break;
        }
    }
    if(!keyExists) {
        std::cout << "[WARNING] Cheia nu exista. Perechea nu a fost stearsa!\n";
    }
}

std::string HashTable::searchTable(int key) {
    int hashValue = hashFunction(key);
    auto& cell = table[hashValue];
    auto bItr = begin(cell);
    for(; bItr != end(cell); bItr++) {
        if(bItr->first == key) {
            return bItr->second;
        }
    }
    return "";
}

std::string HashTable::searchTable(const std::string &key) {
    int hashValue = hashFunction(key);
    auto& cell = stringTable[hashValue];
    auto bItr = begin(cell);
    for(; bItr != end(cell); bItr++) {
        if(bItr->first == key) {
            return bItr->second;
        }
    }
    return "";
}

void HashTable::printTable() {
    for(int i{}; i < hashGroups; i++) {
        if(table[i].empty()) continue;

        auto bItr = table[i].begin();
        for(; bItr != table[i].end(); bItr++) {
            std::cout << "[INFO] Key: " << bItr->first << " Value: " << bItr->second << " HashCode: "<< HashTable::hashFunction(bItr->first) <<std::endl;
        }
    }

    std::cout <<"\n\n";

    for(int i{}; i < hashGroups; i++) {
        if(stringTable[i].empty()) continue;

        auto bItr = stringTable[i].begin();
        for(; bItr != stringTable[i].end(); bItr++) {
            std::cout << "[INFO] Key: " << bItr->first << " Value: " << bItr->second << " HashCode: "<< HashTable::hashFunction(bItr->first) <<std::endl;
        }
    }
}

void HashTable::rehash() {
    int oldHashGroups = hashGroups;
    hashGroups *= 2;

    auto* newTable = new std::list<std::pair<int, std::string>>[hashGroups];
    auto* newStringTable = new std::list<std::pair<std::string, std::string>>[hashGroups];

    for (int i = 0; i < oldHashGroups; i++) {
        for (auto& pair : table[i]) {
            int newHashValue = pair.first % hashGroups;
            newTable[newHashValue].push_back(pair);
        }
    }

    for (int i = 0; i < oldHashGroups; i++) {
        for (auto& pair : stringTable[i]) {
            int newHashValue = 0;
            for (char ch : pair.first) {
                newHashValue = (newHashValue * 31 + ch) % hashGroups;
            }
            newStringTable[newHashValue].push_back(pair);
        }
    }

    delete[] table;
    delete[] stringTable;

    table = newTable;
    stringTable = newStringTable;
}
void citireFisier(const std::string& fileName, HashTable& table) {
    std::ifstream inputFile(fileName);
    if(!inputFile) {
        std::cerr << "Nu s-a putut deschide fisierul!\n";
        return;
    }
    std::string line;
    while(std::getline(inputFile, line)) {
    std::istringstream  iss(line);
        std::string type;
        if (!(iss >> type)) {continue;}
        if(type == "int") {
            int key;
            std::string value;
            if(iss >> key >> value){
                table.insertItem(key, value);
            }
        }else if(type == "str") {
            std::string key;
            std::string value;
            if(iss >> key >> value){
                table.insertItem(key, value);
            }
        }
    }
    inputFile.close();
}

void handleMenu(HashTable& table) {
    citireFisier("/Users/mikebraz/Desktop/faculta/SD/Tema3/problema1/data.txt", table);

    int choice;
    do {
        std::cout << "\n1. Adauga element.\n2. Cauta element. \n3. Sterge element.\n4. Afiseaza tabela.\n0. Exit.\n";
        std::cout << "\nOptiunea: ";
        std::cin >> choice;
        switch (choice) {
            case 1: {
                std::string keyType;
                std::cout << "\nAlegeti tipul de cheie(int/str): ";
                std::cin >> keyType;
                if(keyType == "int") {
                    int key;
                    std::string value;
                    std::cout << "\nIntroduceti cheia: ";
                    std::cin >> key;
                    std::cout << "\nIntroduceti valoarea: ";
                    std::cin >> value;
                    table.insertItem(key, value);
                    std::cout << "\nElementul a fost adaugat cu succes!\n";
                }else if (keyType == "str") {
                    std::string key;
                    std::string value;
                    std::cout << "\nIntroduceti cheia: ";
                    std::cin >> key;
                    std::cout << "\nIntroduceti valoarea: ";
                    std::cin >> value;
                    table.insertItem(key, value);
                    std::cout << "\nElementul a fost adaugat cu succes!\n";
                }else {
                    std::cout << "\n[WARNING] Cheie invalida!\n";

                }
                break;
            }

            case 2: {
                std::string keyType;
                std::cout << "\nAlegeti tipul de cheie(int/str): ";
                std::cin >> keyType;
                if (keyType == "int") {
                    int key;
                    std::string value;
                    std::cout << "\nIntroduceti cheia: ";
                    std::cin >> key;
                    std::string valueSearch = table.searchTable(key);
                    if(!valueSearch.empty()) {
                        std::cout << "Valoarea: " << valueSearch << std::endl;
                    } else {
                        std::cout << "\n[WARNING] Cheie invalida!\n";
                    }
                } else if (keyType == "str") {
                    std::string key;
                    std::string value;
                    std::cout << "\nIntroduceti cheia: ";
                    std::cin >> key;
                    std::string valueSearch = table.searchTable(key);
                    if(!valueSearch.empty()) {
                        std::cout << "Valoarea: " << valueSearch << std::endl;
                    } else {
                        std::cout << "Cheia nu a fost identificata!";
                    }
                } else {
                    std::cout << "\n[WARNING] Cheie invalida!\n";
                }
                break;
            }
            case 3: {
                std::string keyType;
                std::cout << "\nAlegeti tipul de cheie(int/str): ";
                std::cin >> keyType;
                if(keyType == "int") {
                    int key;
                    std::string value;
                    std::cout << "\nIntroduceti cheia: ";
                    std::cin >> key;
                    table.removeItem(key);
                    std::cout << "\nElementul a fost sters cu succes!\n";
                }else if (keyType == "str") {
                    std::string key;
                    std::string value;
                    std::cout << "\nIntroduceti cheia: ";
                    std::cin >> key;
                    table.removeItem(key);
                    std::cout << "\nElementul a fost sters cu succes!\n";
                }else {
                    std::cout << "\n[WARNING] Cheie invalida!\n";

                }
                break;
            }
            case 4: {
                if(table.isEmpty()) {
                    std::cout << "\n[WARNING] Tabela este goala!\n";
                }
                table.printTable();
                break;
            }
            case 0: {
                std::cout << "Iesire..\n";
            }
        }
    } while(choice != 0);
}

int main() {
    HashTable table;
    HashTable table1;
    handleMenu(table);
    return 0;
}
