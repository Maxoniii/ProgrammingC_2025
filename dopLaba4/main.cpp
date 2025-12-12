#pragma once
void swap(int& a, int& b);
void obmen(int* arr, int n);
void buble(int* arr, int n);
void quick(int* arr, int n);
void count(int* arr, int n);
bool sort(int* arr, int n);











#include "func.hpp"
#include <iostream>

void swap(int& a, int& b) {
	int tmp = a;
	a = b;
	b = tmp;
}

void obmen(int* arr, int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (arr[i] > arr[j]) {
				swap(arr[i], arr[j]);
			}
		}
	}
}


void buble(int* arr, int n) {
	bool otsort;
	for (int i = 0; i < n - 1; i++) {
		otsort = false;
		for (int j = 0; j < n - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				swap(arr[j], arr[j + 1]);
				otsort = true;
			}
		}
		if (!otsort)break;
	}
}


int posl_elem(int* arr, int low, int high) {
	int posl = arr[high];
	int i = low - 1;

	for (int j = low; j < high; j++) {
		if (arr[j] < posl) {
			i++;
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i + 1], arr[high]);
	return i + 1;
}



void recursionsort(int* arr, int low, int high) {
	if (low < high) {
		int p = posl_elem(arr, low, high);
		recursionsort(arr, low, p - 1);
		recursionsort(arr, p + 1, high);
	}
}



void quick(int* arr, int n) {
	recursionsort(arr, 0, n - 1);
}


void count(int* arr, int n) {
	const int min = -500000;
	const int max = 500000;
	const int value = max - min + 1;

	int* count = new int[value]();
	for (int i = 0; i < value; i++) {
		count[i] = 0;
	}

	for (int i = 0; i < n; i++) {
		if (arr[i]<min || arr[i]>max) {
			delete[]count;
			return;
		}
		count[arr[i] - min]++;
	}
	int ind = 0;
	for (int i = 0; i < value; i++) {
		while (count[i] > 0) {
			arr[ind] = i + min;
			ind++;
			count[i]--;
		}
	}
	delete[]count;
}


bool sort(int* arr, int n) {
	for (int i = 1; i < n; i++) {
		if (arr[i - 1] > arr[i]) {
			return false;
		}
	}
	return true;
}









#include <iostream>
#include <fstream>
#include <chrono>
#include "func.hpp"
#include <iomanip>


/*int main() {
    std::ifstream in("input.txt");
    std::ofstream out("obmen.txt");


    int n;
    in >> n;
    int* mas = new int[n];

    for (int i = 0; i < n; i++)
        in >> mas[i];


    auto start = std::chrono::high_resolution_clock::now();

    obmen(mas, n);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    if (!sort(mas, n)) {
        std::cout << "Massiv not sorted" << std::endl;
    }

    std::cout << "Obmen Sort: " << std::fixed <<std::setprecision(6)<<duration.count()<< "sec" << std::endl;

    for (int i = 0; i < n; i++) {
        out << mas[i] << " ";
    }
    delete[] mas;
    in.close();
    out.close();

    return 0;
}*/


/*int main() {
    std::ifstream in("input.txt");
    std::ofstream out("obmen.txt");

    int n;
    in >> n;
    int* mas = new int[n];

    for (int i = 0; i < n; i++)
        in >> mas[i];

    auto start = std::chrono::high_resolution_clock::now();

    buble(mas, n);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    if (!sort(mas, n)) {
        std::cout << "Massiv not sorted" << std::endl;
    }

    std::cout << "Bubble Sort: " << std::fixed <<std::setprecision(6)<<duration.count()<< "sec" << std::endl;

    for (int i = 0; i < n; i++) {
        out << mas[i] << " ";
    }
    delete[] mas;
    in.close();
    out.close();

    return 0;

}*/


/*int main() {
    std::ifstream in("input.txt");
    std::ofstream out("obmen.txt");

    int n;
    in >> n;
    int* mas = new int[n];

    for (int i = 0; i < n; i++)
        in >> mas[i];

    auto start = std::chrono::high_resolution_clock::now();
    quick(mas, n);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    if (!sort(mas, n)) {
        std::cout << "Massiv not sorted" << std::endl;
    }
    std::cout << "Quick Sort: " << std::fixed <<std::setprecision(6)<<duration.count()<< "sec" << std::endl;

    for (int i = 0; i < n; i++) {
        out << mas[i] << " ";
    }
    delete[] mas;
    in.close();
    out.close();

    return 0;
}*/


int main() {
    std::ifstream in("input.txt");
    std::ofstream out("obmen.txt");

    int n;
    in >> n;
    int* mas = new int[n];

    for (int i = 0; i < n; i++)
        in >> mas[i];

    auto start = std::chrono::high_resolution_clock::now();
    count(mas, n);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    if (!sort(mas, n)) {
        std::cout << "Massiv not sorted" << std::endl;
    }
    std::cout << "Count Sort: " << std::fixed << std::setprecision(6) << duration.count() << "sec" << std::endl;

    for (int i = 0; i < n; i++) {
        out << mas[i] << " ";
    }
    delete[] mas;
    in.close();
    out.close();

    return 0;
}

















100
5 - 3 8 0 - 1 7 2 - 5 4 1 10 - 8 3 - 2 9 6 - 7 12 - 10 11 - 4 15 - 6 13 14 - 9 18 - 12 17 16 - 11 20 - 13 19 22 - 14 21 24 - 15 23 26 - 16 25 28 - 17 27 30 - 18 29 32 - 19 31 34 - 20 33 36 - 21 35 38 - 22 37 40 - 23 39 42 - 24 41 44 - 25 43 46 - 26 45 48 - 27 47 50 - 28 49 52 - 29 51 54 - 30 53 56 - 31 55 58 - 32 57 60 - 33 59 62 - 34 61 64 - 35 63








