#include <iostream>

int main() {
    int x, i;


    std::cout << "Input number x (0 < x < 10^9): ";
    std::cin >> x;
    std::cout << "Input number of bit i (0 - 31): ";
    std::cin >> i;


    int m = ~(1 << i);
    x = x & m;

    std::cout << "Result: " << x << std::endl;

    return 0;
}
