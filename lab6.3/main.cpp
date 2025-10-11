#include <iostream>;
int main() {
	int i, j, n, m, matrix[100][100];
	std::cout << "Input size of matrix:" << std::endl;
	std::cin >> n;
	std::cin >> m;
	std::cout << "Input values of matrix:" << std::endl;
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			std::cin >> matrix[i][j];
		}
	}
	int maxAbsSum = 0;
	int maxAbsSumValue = 0;
	for (int j = 0; j < m; j++) {
		maxAbsSum += abs(matrix[0][j]);
	}

	for (int i = 0; i < n; i++) {
		int currentAbsSum = 0;
		for (int j = 0; j < m; j++) {
			currentAbsSum += abs(matrix[i][j]);
		}
		if (currentAbsSum > maxAbsSum) {
			maxAbsSum = currentAbsSum;
			maxAbsSumValue = i;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			matrix[maxAbsSumValue][j] = 9999;
		}
	}
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			std::cout << matrix[i][j] << "\t";
		}
		std::cout << std::endl;
	}
	return 0;
}