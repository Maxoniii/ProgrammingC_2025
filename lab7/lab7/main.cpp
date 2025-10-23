#include <iostream>
#include "func.hpp"
int main() {
	const int NMax = 100;
	int matrix[NMax][100];
	int n{};

	Read(matrix ,n);
	dothis(matrix, n);
	Write(matrix, n);

	return 0;

}