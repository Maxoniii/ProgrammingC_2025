#include <iostream>

int main() {
    int posl[10000];
    int n;

    std::cout << "Input nuber of poslegovatelnost: " << std::endl;
    std::cin >> n;


    std::cout << "Input posledovatelnost: " << std::endl;
    for (int i = 0; i < n; i++) {
        std::cin >> posl[i];
    }

    int newSize = 0;
    for (int i = 0; i < n; i++) {
        int num = posl[i];

        int lastDigit = num % 10;

        int firstDigit = num;
        while (firstDigit >= 10) {
            firstDigit /= 10;
        }

        if (firstDigit != lastDigit) {
            posl[newSize] = posl[i];
            newSize++;
        }
    }

    n = newSize;

    for (int i = 0; i < n; i++) {
        int num = posl[i];


        int firstDigit = num;
        while (firstDigit >= 10) {
            firstDigit /= 10;
        }

        if (firstDigit == 3) {
            for (int j = n; j > i + 1; j--) {
                posl[j] = posl[j - 1];
            }
            posl[i + 1] = posl[i];
            n++;
            i++;
        }
    }

    for (int i = 0; i < n; i++) {
        std::cout << posl[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}