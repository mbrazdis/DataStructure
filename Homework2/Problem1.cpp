#include <iostream>
#include <queue>

/*
1. Să se simuleze o stivă utilizând două cozi. 
Se va crea structura stivă cu funcţiile de 
push(), pop(), isEmpty() şi clear(), 
iar cele 2 cozi vor fi câmpuri ale struc- turii. 
Puteţi folosi implementare proprie de coadă sau queue din C++.(2p)
*/

struct Stiva {
private:
    std::queue<int> queue1;
    std::queue<int> queue2;
public:
    void pushNr(int nr) {
        queue1.push(nr);
    }

    void popLST() {
        while(queue1.size() != 1){
            queue2.push(queue1.front());
            queue1.pop();
        }
        queue1.pop();
        while(!queue2.empty()){
            queue1.push(queue2.front());
            queue2.pop();
        }

    }
    void print() {
        if(queue1.empty()){
            std::cout << "Stiva este goala!";
            return;
        }
        std::swap(queue1, queue2);
        while(!queue2.empty()) {
            std::cout << queue2.front() << " ";
            queue1.push(queue2.front());
            queue2.pop();
        }
        std::cout << std::endl;
    }
    bool isEmpty() {
        return queue1.empty();
    }

    void clear() {
        while(!queue1.empty()) {
            queue1.pop();
        }
    }
};

int main() {
    Stiva stiva;
    stiva.pushNr(1);
    stiva.pushNr(2);
    stiva.pushNr(3);
    stiva.print();
    stiva.popLST();
    stiva.print();

    if(stiva.isEmpty()) {
        std::cout << "Stiva este goala!\n";
    } else {
        std::cout << "Stiva nu este goala!\n";
    }

    stiva.clear();
    stiva.print();


    return 0;
}
