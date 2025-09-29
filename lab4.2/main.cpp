#include <iostream>


int main() {
    int N;

    
    std::cout << "Input number of product (1-5): ";
    std::cin >> N;

    
    switch (N) {
    case 1:
        std::cout << "Milk" << std::endl;
        break;
    case 2:
        std::cout << "Bread" << std::endl;
        break;
    case 3:
        std::cout << "Meat" << std::endl;
        break;
    case 4:
        std::cout << "Apples" << std::endl;
        break;
    case 5:
        std::cout << "Candles" << std::endl;
        break;
    default:
        std::cout << "Error: number of product " << N << " not found!" << std::endl;
        break;
    }

    return 0;
}