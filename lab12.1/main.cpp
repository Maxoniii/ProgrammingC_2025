#include <iostream>
#include <string>
#include <cctype>



int main() {
    std::string s;
    std::cin >> s;

    if (s.length() > 100) {
        std::cout << "NO" << std::endl;
        return 0;
    }

    int lt = 0;
    int rt = s.length() - 1;
    bool Palindrome = true;

    while (lt < rt) {
        char leftChar = tolower(s[lt]);
        char rightChar = tolower(s[rt]);

        if (leftChar != rightChar) {
            Palindrome = false;
            break;
        }

        lt++;
        rt--;
    }

    if (Palindrome) {
        std::cout << "YES" << std::endl;
    }
    else {
        std::cout << "NO" << std::endl;
    }

    return 0;
}