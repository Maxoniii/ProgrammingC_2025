#include <iostream>

int main() {
    int A, B, C;

    std::cout << "Input three natural numbers:";
    std::cin >> A >> B >> C;

    if (A < B && B < C) {
        std::cout << C - B - A << std::endl;
    }
    else if (A % C == 0) {
        std::cout << A / C + B << std::endl;
    }
    else {
        std::cout << A + B + C << std::endl;
    }

    return 0;
}
