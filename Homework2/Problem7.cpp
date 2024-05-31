#include <iostream>
#include <vector>

/*
Să se implementeze o coadă circulară. Pentru aceasta se cere crearea unei structuri COADA care să conţină:
• un câmp de tip vector de int numit DATA, care stochează elementele din coadă
• un câmp SIZE_MAX de tip int, care reprezintă capacitatea maximă a cozii
• două câmpuri de tip int BEGIN = poziţia primului element şi END - poziţia de după ultimul element din coadă.
• funcţia PUSH(elem) - pune elem în coadă
• funcţia POP() - elimină un element din coadă
• funcţia FRONT( ) - returnează valoarea aflată la începutul cozii
• funcţia EMPTY( ) - verifică dacă este vidă sau nu coada.
• funcţia CLEAR( ) - goleşte coada
În funcţia main se declară o variabilă de tip COADA, se inserează pe rând n elemente, cu n citit de la tastatură, 
apoi se extrag aceste elemente pe rând şi se afişază în ordinea extragerii.(4p)
*/

struct circularQueue {
    std::vector<int> DATA;
    int size_max;
    int BEGIN;
    int END;

    explicit circularQueue(int size) : size_max(size), BEGIN(0), END(0) {
        DATA.resize(size);
    }

    bool EMPTY() const {
        return BEGIN == END;
    }

    void PUSH(int elem) {
        if((END + 1) % size_max == BEGIN) {
            std::cerr << "Coada circulara este full!" << std::endl;
            return;
        }
        DATA[END] = elem;
        END = (END + 1) % size_max;
    }
    void POP() {
        if(EMPTY()) {
            std::cerr << "Coada este goala!" << std::endl;
            return;
        }
        BEGIN = (BEGIN + 1) % size_max;
    }

    int FRONT() const {
        if(EMPTY()) {
            std::cerr << "Coada este goala!" << std::endl;
            return -1;
        }
        return DATA[BEGIN];
    }

    void CLEAR() {
        END = 0;
        BEGIN = 0;
    }
};

int main() {

    int n;
    std::cout << "Introduceti marimea maxima a cozii: ";
    std::cin >> n;

    circularQueue queue(n);

    int num_elements;
    std::cout << "Introduceti cate elemente vrei sa introduci: ";
    std::cin >> num_elements;

    for(int i = 0; i < num_elements; i++) {
        std::cout << "Introduceti un element: ";
        int elem;
        std::cin >> elem;
        queue.PUSH(elem);
        std::cout << std::endl;
    }

    std::cout << "Extragerea elementelor in ordinea extragerii: \n";
    while(!queue.EMPTY()) {
        std::cout << queue.FRONT() << " ";
        queue.POP();
    }
    queue.CLEAR();
    return 0;
}
