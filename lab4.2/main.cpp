#include <iostream>

int main() {
    int x;

    std::cout << "Input x (-1 or 1): ";
    std::cin >> x;

    if (x == -1) {
        std::cout << "Negative number" << std::endl;
    }
    else if (x == 1) {
        std::cout << "Positive number" << std::endl;
    }
    else {
        std::cout << "Error: x must be 1 or -1!" << std::endl;
    }

    return 0;
}