#include <iostream>;
int main() {
	int i, j, n, m;
	std::cout << "Input size of matrix:" << std::endl;
	std::cin >> n;
	std::cin >> m;
	int** matrix = new int* [n];
	for (int i = 0; i < n; i++) {
		matrix[i] = new int[m];
	}
	std::cout << "Input values of matrix:" << std::endl;
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			std::cin >> matrix[i][j];
		}
	}
	int maxAbsSum = 0;
	int maxAbsSumRow = 0;
	int firstRowSum = 0;
	for (j = 0; j < m; j++) {
		firstRowSum += matrix[0][j];
	}
	maxAbsSum = std::abs(firstRowSum);

	for (int i = 0; i < n; i++) {
		int currentRowSum = 0;
		for (int j = 0; j < m; j++) {
			currentRowSum += (matrix[i][j]);
		}
		int currentAbsSum = std::abs(currentRowSum);

		if (currentAbsSum > maxAbsSum) {
			maxAbsSum = currentAbsSum;
			maxAbsSumRow = i;
		}
	}


	for (int j = 0; j < m; j++) {
		matrix[maxAbsSumRow][j] = 9999;
	}


	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			std::cout << matrix[i][j] << "\t";
		}
		std::cout << std::endl;
	}

	for (int i = 0; i < n; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;

	return 0;
}