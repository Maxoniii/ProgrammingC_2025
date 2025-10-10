#include <iostream>
#include <cmath>


int main() {
    double num;
    double min_num = 0.0;
    double res = 1.0;
    int min_index = 0;
    int count = 0;
    int n;
    std::cout << "Input amount of numbers: " << std::endl;
    std::cin >> n;
    std::cout << "Input numders: " << std::endl;
    for (int i = 0; i < n; i++) {
        std::cin >> num;
        if ((num < 0) && (num != int(num))) {
            count += 1;

            if (count == 1) {
                min_num == num;
                min_index = i;
                res = num;
            }
            else {
                res *= num;

                if (num < min_num) {
                    min_num = num;
                    min_index = i;

                }
            }
        }
    }
    std::cout << "Multiplication of numbers: " << res << std::endl;
    std::cout << "Minimum of number:" << min_num << std::endl;
    std::cout << "Minimum of index: " << min_index << std::endl;










    return 0;
}