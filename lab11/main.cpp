#include "func.hpp"
#include <iostream>

int main() {
	const int MAX_SIZE = 100;
	int posl[MAX_SIZE];
	int n = 0;

	std::cout << "Input number of numbers: ";
	std::cin >> n;

	if (n <= 0 || n > MAX_SIZE) {
		std::cout << "Incorrect size" << std::endl;
		return 1;
	}

	std::cout << "Input natural numbers: ";
	for (int i = 0; i < n; i++) {
		std::cin >> posl[i];
		if (posl[i] <= 0) {
			std::cout << "Numbers must be natural (more than 0)" << std::endl;
			return 1;
		}
	}

	Node* head = CREATE(posl, n);

	std::cout << "Primary sequence: ";
	PRINT(head);

	if (nevfg(posl, n, true) || nevfg(posl, n, false)) {
		std::cout << "Posledovatelnost is nevozrastaet" << std::endl;
		head = DELETE(head);
		head = DUBLICATE(head);
	}
	else {
		std::cout << "Sorting by first digit" << std::endl;
		head = sortfg(head);
	}

	std::cout << "Result: ";
	PRINT(head);

	CLEAR(head);

	return 0;
}



/*#pragma once

struct Node {
	int data;
	Node* next;
};


int fg(int n);
int lg(int n);
bool palindrom(int n);
bool nevfg(int arr[], int size, bool usefg);
Node* MAKE(int value);
void ADD(Node* head, int value);
void PRINT(Node* head);
void CLEAR(Node* head);
Node* CREATE(int arr[], int size);
Node* DELETE(Node* head);
Node* DUBLICATE(Node* head);
Node* sortfg(Node* head);









#include <iostream>
#include "func.hpp"

Node* MAKE(int value) {
	Node* p = new Node;
	p->data = value;
	p->next = nullptr;
	return p;
}

void PRINT(Node* head) {
	Node* p = head;
	while (p != nullptr) {
		std::cout << p->data << " ";
		p = p->next;
	}
	std::cout << std::endl;
}

void ADD(Node* head, int value) {
	Node* p = MAKE(value);
	p->next = head->next;
	head->next = p;
}

void CLEAR(Node* head) {
	Node* p = head;
	while (p != nullptr) {
		Node* tmp = p;
		p = p->next;
		delete tmp;
	}
}

int fg(int n) {
	while (n >= 10) {
		n /= 10;
	}
	return n;
}

int lg(int n) {
	return n % 10;
}

bool palindrom(int n) {
	if (n < 10) return false;

	int orig = n;
	int fake = 0;

	while (n > 0) {
		int l = n % 10;
		fake = fake * 10 + l;
		n = n / 10;
	}
	if (orig == fake) {
		return true;
	}
	else {
		return false;
	}
}

bool nevfg(int arr[], int size, bool usefg) {
	for (int i = 1; i < size; i++) {
		int nast, pred;

		if (usefg) {
			nast = fg(arr[i]);
			pred = fg(arr[i - 1]);
		}
		else {
			nast = lg(arr[i]);
			pred = lg(arr[i - 1]);
		}
		if (nast > pred) {
			return false;
		}
	}
	return true;
}


Node* CREATE(int arr[], int size) {
	if (size == 0) return nullptr;

	Node* head = MAKE(arr[0]);
	Node* nast = head;

	for (int i = 1; i < size; i++) {
		nast->next = MAKE(arr[i]);
		nast = nast->next;
	}


	return head;
}

Node* DELETE(Node* head) {
	Node ex;
	ex.next = head;

	Node* p = &ex;
	while (p->next != nullptr) {
		if (p->next->data >= 1 && p->next->data <= 9) {
			Node* tmp = p->next;
			p->next = p->next->next;
			delete tmp;
		}
		else {
			p = p->next;
		}
	}
	return ex.next;
}

Node* DUBLICATE(Node* head) {
	Node* p = head;
	while (p != nullptr) {
		if (palindrom(p->data)) {
			ADD(p, p->data);
			p = p->next;
		}
		p = p->next;
	}
	return head;
}

Node* sortfg (Node* head) {
	if (head == nullptr || head->next == nullptr) {
		return head;
	}

	bool raz;
	do {
		raz = false;
		Node* nast = head;
		Node* pred = nullptr;

		while (nast != nullptr && nast->next != nullptr) {
			int dnast = fg(nast->data);
			int sled = fg(nast->next->data);

			if (dnast > sled) {
				Node* nextNode = nast->next;

				nast->next = nextNode->next;
				nextNode->next = nast;

				if (pred == nullptr) {
					head = nextNode;
				}
				else {
					pred->next = nextNode;
				}


				pred = nextNode;
				raz = true;
			}
			else {

				pred = nast;
				nast = nast->next;
			}
		}
	} while (raz);

	return head;
}
*/