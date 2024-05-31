#include <iostream>
#include <stack>
/*

 *PROBLEMA 5*

Parantezare corectă: Se dă un şir de paranteze deschise şi închise de tip (, ), [, ], {, }.
Să se verifice dacă şirul este corect. Folosiţi o stiva (std::stack) pentru rezolvare.
Exemplu: şirul [()()] este corect, şirul ([]) nu este corect, şirul ()] (nu este corect.(3p)
*/
bool parantezeCorecte(const std::string& expresie) {
    std::stack<char> stiva;

    for (char paranteza : expresie) {
        if (paranteza == '(' || paranteza == '[' || paranteza == '{') {
            if (!stiva.empty() &&
                ((stiva.top() == '(' && paranteza == '[') ||
                (stiva.top() == '(' && paranteza == '{') ||
                (stiva.top() == '[' && paranteza == '{'))) {
                return false;
            }
            stiva.push(paranteza);
        } else if (paranteza == ')' || paranteza == ']' || paranteza == '}') {
            if (stiva.empty()) {
                return false;
            } else if ((paranteza == ')' && stiva.top() != '(') ||
                       (paranteza == ']' && stiva.top() != '[') ||
                       (paranteza == '}' && stiva.top() != '{')) {
                return false;
            }if (!stiva.empty() &&
                 ((stiva.top() == ']' && paranteza == ')') ||
                 (stiva.top() == '}' && paranteza == ')') ||
                 (stiva.top() == '}' && paranteza == ']'))) {
                return false;
            } else {
                stiva.pop();
            }
        }
    }

    return stiva.empty();
}

int main() {
    std::string expresie;
    std::cout << "Introduceti expresia: ";
    std::cin >> expresie;

    if (parantezeCorecte(expresie)) {
        std::cout << "Expresia este corecta.\n";
    } else {
        std::cout << "Expresia nu este corecta.\n";
    }

    return 0;
}
