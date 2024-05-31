#include <iostream>
#include <vector>
#include <stack>

/*
Inversare elemente vector. Să se inverseze elementele unui vector utilizănd o stivă. 
Primul element se va intershimba cu ultimul, al doilea cu penultimul, etc. (2p)
*/


std::vector<int>* revrse(std::vector<int>* vec) {
    std::stack<int>stiva;
    for(auto elem : *vec) {
        stiva.push(elem);
    }
    for(int & i : *vec) {
        i = stiva.top();
        stiva.pop();
    }
    return vec;
}

int main() {
    auto *vec = new std::vector<int>();
    *vec = {1, 2, 3, 4, 5};
    vec = revrse(vec);
    for (auto elem : *vec) {
        std::cout << elem << " ";
    }

    delete vec;
    return 0;
}
