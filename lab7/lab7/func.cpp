#include <iostream>
#include "func.hpp"

void Read( int matrix[][100], int &n) {
	std::cout << "Input size of matrix: " << std::endl;
	std::cin >> n;
	std::cout << "Input values of matrix: " << std::endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; ++j){
			std::cin >> matrix[i][j];
		}
	}
}


int Findmax(int matrix[][100], int n) {
	int MaxNum = matrix[0][0];
	int CountMaxNum = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (matrix[i][j] > MaxNum) {
				MaxNum = matrix[i][j];
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (matrix[i][j] == MaxNum) {
				CountMaxNum++;
			}
		}
	}
	return CountMaxNum;
}

void Write(int matrix[][100], int n){
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

bool Prime(int num) {
	if (num <= 1)return false;
	for (int i = 2; i <= num / 2; i++) {
		if (num % i == 0) {
			return false;
		}
	}
	return true;
}

int countPrime(int value[], int n) {
	int count = 0;
	for (int j = 0; j < n; j++) {
		if (Prime(value[j])) {
			count++;
		}
	}
	return count;
}

void sortofcountPrimeValue(int matrix[][100], int n) {
	int primeCount[100];
	for (int i = 0; i < n; i++) {
		primeCount[i] = countPrime(matrix[i], n);
	}

	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - 1 - i; j++) {
			if (primeCount[j] < primeCount[j + 1]) {
				for (int k = 0; k < n; k++) {
					int ex = matrix[j][k];
					matrix[j][k] = matrix[j + 1][k];
					matrix[j + 1][k] = ex;
				}
				int b = primeCount[j];
				primeCount[j] = primeCount[j + 1];
				primeCount[j + 1] = b;
			}
		}
	}
}

void dothis(int matrix[][100],int n){
	if (Findmax(matrix, n)) {
		sortofcountPrimeValue(matrix, n);
	}

}