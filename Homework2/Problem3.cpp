#include <iostream>

/*Să se implementeze o listă dublu înlănţuită cu funcţionalităţile descrise în continuare. 
Se cere utilizarea unei structuri node care are trei câmpuri: un camp pentru informaţie 
(de tip int) şi două câmpuri de tip pointer la node pentru legăturile către elementele 
precedent şi următor. Se cere utilizarea unei structuri List care are ca membri două variabile
de tip node∗ reprezentând primul respectiv ultimul element din listă, o variabilă de tip int 
reprezentând numărul de elemente din listă şi funcţiile:
 
• push_back(key) - adaugă cheia key la finalul listei
• insert(node ∗ N od, int val) - inserează un element cu cheia val înainte de
nodul indicat de Nod.
• funcţia size() - returnează numărul de elemente din listă.
• merge(ListaL) - concatenează lista curentă cu lista L. După apel lista curentă conţine elementele celor două liste concatenate, iar L devine vidă.
• print() - afişează elementele listei
• palindrom(Lista L) - verifică dacă lista este palindrom
• compare(Lista L1, ListaL2) - returnează 1 dacă L1 şi L2 sunt identice şi 0 altfel.
 
În funcţia main creaţi un scurt context de testare şi apelaţi funcţiile imple- mentate.*/


struct list {
    struct node {
        int key;
        node* next;
        node* prev;
    };

    node* head;
    node* tail;
    int size;

    list() : head(nullptr), tail(nullptr), size(0) {}

    void push_back(int value) {
        node* newNode = new node();
        newNode->key = value;
        newNode->next = nullptr;
        newNode->prev = tail;
        if(tail) {
            tail->next = newNode;
        } else {
            head = newNode;
        }
        tail = newNode;
        size++;
    }
    void insert(node *nod, int value) {
        node* newNode = new node();
        newNode->key = value;
        if (nod == head) {

            newNode->next = head;
            newNode->prev = nullptr;
            if (head) {
                head->prev = newNode;
            }
            head = newNode;
        } else {

            newNode->prev = nod->prev;
            newNode->next = nod;
            if (nod->prev) {
                nod->prev->next = newNode;
            }
            nod->prev = newNode;
        }
        size++;
    }
    int returnSize() const{
        return size;
    }

    static void print(node *head) {
        node* nod = head;
        if(!head) {
            std::cout << "Lista este goala!";
            return;
        } else {
            while(nod != nullptr) {
                std::cout << nod->key << " ";
                nod = nod->next;
            }
        }
    }
    void merge(list& ListaL) {
        if(!ListaL.head) return;

        if(!head) {
            head = ListaL.head;
            tail = ListaL.tail;
        } else {
            tail->next = ListaL.head;
            ListaL.head->prev = tail;
            tail = ListaL.tail;
        }

        size += ListaL.size;

        ListaL.head = nullptr;
        ListaL.tail = nullptr;
        ListaL.size = 0;
    }

    static void palindrom (list& ListaL) {
        if(!ListaL.head) return;

        node* nod1 = ListaL.head;
        node* nod2 = ListaL.tail;
        while(nod1 != nullptr && nod2 != nullptr && nod1->prev != nod2 && nod1 != nod2) {
            if(nod1->key != nod2->key) {
                std::cout << "Lista nu este palindrom!";
                return;
            }
            nod1 = nod1->next;
            nod2 = nod2->prev;
        }
        std::cout << "Lista este palindrom!";
    }

    static int compare (list& Lista1, list& Lista2) {
        if(!Lista1.head || !Lista2.head) return 0;
        node* nod1 = Lista1.head;
        node* nod2 = Lista2.head;

        while (nod1 != nullptr && nod2 != nullptr) {
            if(nod1->key != nod2->key) return 0;
            nod1 = nod1->next;
            nod2 = nod2->next;
        }
        return 1;
    }
};

int main() {

    list* lista = new list();

    lista->push_back(1);
    lista->push_back(2);
    lista->push_back(3);
    lista->push_back(4);

    std::cout << "Prima lista: ";
    list::print(lista->head);

    lista->insert(lista->tail, 5);
    std::cout << "\nPrima lista, dupa insert: ";
    list::print(lista->head);

    std::cout << "\nSize-ul liste este: " << lista->returnSize();

    list* lista2 = new list();

    lista2->push_back(4);
    lista2->push_back(5);
    lista2->push_back(3);
    lista2->push_back(2);
    lista2->push_back(1);
    std::cout << "\nA 2-a lista: ";
    list::print(lista2->head);

    std::cout << "\nCele 2 liste concatenate: ";
    lista->merge(*lista2);
    list::print(lista->head);
    std::cout << "\nSize-ul liste este: " << lista->returnSize();
    std::cout << std::endl;
    std::cout << "Size-ul listei 2: " << lista2->returnSize() << ". ";
    list::print(lista2->head);

    std::cout << std::endl;
    list::palindrom(*lista);

    list* lista3 = new list();

    lista3->push_back(1);
    lista3->push_back(2);
    lista3->push_back(3);
    lista3->push_back(5);
    lista3->push_back(4);
    lista3->push_back(4);
    lista3->push_back(5);
    lista3->push_back(3);
    lista3->push_back(2);
    lista3->push_back(1);

    std::cout << "\nLista 3 este: ";
    list::print(lista3->head);
    if(list::compare(*lista, *lista3)) std::cout<< "\nCele 2 liste sunt identice!";
    else std::cout << "\nCele 2 liste nu sunt identice!";

    delete lista;
    delete lista2;
    delete lista3;

    return 0;
}
