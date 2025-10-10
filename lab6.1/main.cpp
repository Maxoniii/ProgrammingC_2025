#include <iostream>
int main() {
	int n;
	int sum = 0;
	int digits[10000];
	std::cout << "Input  n - posledovatelnost" << std::endl;
	std::cin >> n;
	if (n <= 0 || n > 10000) {
		std::cout << "Incorrect value" << std::endl;
	}
	for (int i = 0; i < n; i++) {
		std::cin >> digits[i];
	}
	int sum19 = 0;
	for (int i = 0; i < n; i++) {
		int num = digits[i];
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

}