##include <iostream>
int main() {
    int n;
    int sum = 0;
    std::cout << "Input  n - posledovatelnost" << std::endl;
    std::cin >> n;
    int* digits = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> digits[i];
        if (digits[i] <= 0 || digits[i] > 10000) {
            std::cout << "Incorrect value" << std::endl;
            delete[] digits;
            return 1;
        }
    }
    int sum19 = 0;
    for (int i = 0; i < n; i++) {
        int num = digits[i];
        sum = 0;
        while (num > 0) {
            sum += num % 10;
            num /= 10;
        }
        if (sum == 19) {
            sum19 = 1;
            break;
        }
    }
    if (sum19 == 0) {
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                if (digits[i] < digits[j]) {
                    std::swap(digits[i], digits[j]);
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        std::cout << digits[i] << " ";
    }
    std::cout << std::endl;
    delete[] digits;
    return 0;
}
