#include <iostream>
#include "func.hpp"

int main() {
    int arr[10000];
    int size;

    std::cout << "Input numbers of posledovatelnost: " << std::endl;
    std::cin >> size;


    std::cout << "Input posledovatelnost numbers more than 0: " << std::endl;
    for (int i = 0; i < size; i++) {
        std::cin >> arr[i];
        if (arr[i] <= 0) {
            std::cout << "Numders must be more than 0" << std::endl;
            return 1;
        }
    }


    for (int i = 0; i < size; i++) {
        if (mult18(arr[i])) {
            DELETE(arr, size, i);
            i--;
        }
    }

    for (int i = 0; i < size; i++) {
        if (y7n0(arr[i])) {
            DUBLICATE(arr, size, i);
            i++;
        }
    }


    std::cout << "Result: " << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }

    return 0;
}






/* func.hpp
#pragma once

bool mult18(int num);
bool y7n0(int num);
void DELETE(int arr[], int &size, int ind);
void DUBLICATE(int arr[], int &size, int ind);
*/

/*func.cpp
#include <iostream>
#include "func.hpp"

bool mult18(int num) {
	int pr = 1;
	int tmp = num;
	while (tmp > 1) {
		int d = tmp % 10;
		pr *= d;
		tmp /= 10;
	}
	return pr % 18 == 0;
}

bool y7n0(int num) {
	bool sem = false;
	int tmp = num;
	while (tmp > 0) {
		int d = tmp % 10;
		if (d == 7) {
			sem = true;
		}
		tmp /= 10;
	}
	return (sem == true);
}

void DELETE(int arr[], int& size, int ind) {
	for (int i = ind; i < size - 1; i++) {
		arr[i] = arr[i + 1];
	}
	size--;
}

void DUBLICATE(int arr[], int& size, int ind) {
	if (size >= 10000) return;
	for (int i = size; i > ind; i--) {
		arr[i] = arr[i - 1];
	}
	arr[ind + 1] = arr[ind];
	size++;
}
*/