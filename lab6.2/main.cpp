#include <iostream>
int main() {
    int n;
    int sum = 0;
    int digits[1000];
    std::cout << "Input  n - posledovatelnost" << std::endl;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> digits[i];
        if (digits[i] <= 0 || digits[i] > 1000) {
            std::cout << "Incorrect value" << std::endl;
        }
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (digits[i] > digits[j]) {
                int sum1 = 0;
                int ex1 = digits[j];
                while (ex1 > 0) {
                    sum1 += ex1 % 10;
                    ex1 /= 10;
                }
                int sum2 = 0;
                int ex2 = digits[j + 1];
                while (ex2 > 0) {
                    sum2 += ex2 % 10;
                    ex2 /= 10;
                }
                int one1 = digits[j];
                while (one1 >= 10) {
                    one1 /= 10;
                }
                int one2 = digits[j + 1];
                while (one2 >= 10) {
                    one2 /= 10;
                }
                bool swap = false;

                if (sum1 > sum2) {
                    swap = true;
                }
                if (one1 > one2) {
                    swap = true;
                }
                else if (sum1 == sum2 && one1 == one2) {
                    swap = true;
                }
                if (swap) {
                    int ex = digits[j];
                    digits[j] = digits[j + 1];
                    digits[j + 1] = ex;
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        std::cout << digits[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}