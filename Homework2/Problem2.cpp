#include <iostream>

/*
Să se implementeze o listă dublu înlănţuită cu funcţionalităţile descrise în continuare. 
 Se cere utilizarea unei structuri node care are trei câmpuri: un câmp pentru informaţie (de tip int) 
 şi două câmpuri de tip pointer la node pentru legăturile către elementele precedent şi următor. 
 Se cere utilizarea unei structuri List care are ca membri două variabile de tip node∗ reprezentând primul 
 respectiv ultimul element din listă, o variabilă de tip int reprezentând numărul de elemente din listă şi funcţiile:
 
• push_front(key) - adaugă cheia key în capul listei
• push_back(key) - adaugă cheia key la finalul listei
• pop_front() - şterge primul element din listă
• pop_back() - şterge ultimul element din listă
• find(key) - caută o cheie key în listă - returnează pointer la nodul cu cheia key sau NULL
• clear() - şterge toate elementele listei
• print() - afişează elementele listei
• remove(int key) - şterge toate apariţiile cheii key (implică căutare)
• erase(node∗Nod) -şterge un element Nod din listă (NU implică căutare)
• size() - returnează numărul de elemente din listă.
• print() - afişează elementele listei
 
În funcţia main creaţi un scurt context de testare şi apelaţi funcţiile imple- mentate.(2p)
*/


struct list {
    struct Node {
        int key;
        Node* next;
        Node* previous;
    };

    Node* head;
    Node* tail;
    int size;

    list() : head(nullptr), tail(nullptr), size(0) {}

    void push_front(int value) {
        Node *newNode = new Node();
        newNode->key = value;
        newNode->next = head;
        newNode->previous = nullptr;

        if(!head) {
            tail = newNode;
        } else {
            head->previous = newNode;
        }
        head = newNode;
        size++;
    }
    void push_back(int value) {
        Node *newNode = new Node();
        newNode->key = value;
        newNode->next = nullptr;
        newNode->previous = tail;
        if(tail) {
            tail->next = newNode;
        } else {
            head = newNode;
        }
        tail = newNode;
        size++;
    }

    void pop_front() {
        if(!head) return;
        Node* toDelete = head;
        head = head->next;
        if (head) {
           head->previous = nullptr;
        } else {
            tail = nullptr;
        }
        delete toDelete;
        size--;
    }

    void pop_back() {
        if(!head) return;
        Node* toDelete = tail;
        tail = tail -> previous;
        if(tail) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete toDelete;
        size--;
    }

    Node* find (int value) const {
        Node* current = head;
        while (current != nullptr) {
            if(current->key == value) return current;
            current = current->next;
        }
        return nullptr;
    }

    static void print(Node* head) {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->key << std::endl;
            current = current->next;
        }
    }

    void clear() {
        if(!head) return;
        while(head) {
        Node* toDelete = tail;
        tail = tail -> previous;
        if(tail) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete toDelete;
        size--;
        }
    }

    void remove (int value) {
        Node *current = head;
        while (current != nullptr) {
            if (current->key == value) {
                Node *toDelete = current;
                if (current == head) {
                    head = current->next;
                    if (head) {
                        head->previous = nullptr;
                    } else {
                        tail = nullptr;
                    }
                } else if (current == tail) {
                    tail = current->previous;
                    if (tail) {
                        tail->next = nullptr;
                    } else {
                        head = nullptr;
                    }
                } else {
                    current->previous->next = current->next;
                    current->next->previous = current->previous;
                }
                current = current->next;
                delete toDelete;
                size--;
            } else {
                current = current->next;
            }
        }
    }

    void erase(Node* node) {
        if(node == head) {
            head = node->next;
            if(head) {
                head->previous = nullptr;
            } else {
                tail = nullptr;
            }
        } else if (node == tail) {
            tail = node -> previous;
            if(tail) {
                tail->next = nullptr;
            } else {
                head = nullptr;
            }
        } else {
            node->previous->next = node->next;
            node->next->previous = node->previous;
        }
        delete node;
        size--;
    }

    int returnSize() const{
        return size;
    }
};




int main() {

    list* l = new list();
    l->push_back(1);
    l->push_back(2);
    l->push_back(3);
    l->push_front(0);
    //list::print(l->head);
   /* l->pop_front();
    list::print((l->head));
    l->pop_back();
    list::print(l->head);*/


    //Node* found = l->find(2);
    //std::cout << found->key;

    l->clear();
    //list::print(l->head);
    l->push_back(1);
    l->push_back(2);
    l->push_back(3);
    l->push_back(1);
    l->push_back(2);
    l->push_back(3);
    l->remove(2);
    //list::print(l->head);

    list::Node* found = l->find(1);
    l->erase(found);
    list::print(l->head);

    std::cout << l->returnSize();

    delete l;
    return 0;
}
