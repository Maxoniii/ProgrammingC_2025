#include "func.hpp"
#include <iostream>

int main() {
	int n = 0;

	std::cout << "Input number of numbers: ";
	std::cin >> n;

	if (n <= 0) {
		std::cout << "Incorrect size" << std::endl;
		return 1;
	}

	std::cout << "Input natural numbers: ";
	Node* head = CREATELIST(n);


	Node* tmp = head;
	bool nat = true;
	while (tmp != nullptr) {
		if (tmp->data <= 0) {
			nat = false;
			break;
		}
		tmp = tmp->next;
	}

	if (!nat) {
		std::cout << "Nummbers must be natural" << std::endl;
		CLEAR(head);
		return 1;
	}

	std::cout << "Primary posledovatelnost: " << std::endl;
	PRINT(head);



	bool byfirst = nevfg(head, true);
	bool bylast = nevfg(head, false);

	if (byfirst || bylast) {
		std::cout << "Posledovatelnost nevozrastaet: " << std::endl;
		head = DELETE(head);
		head = DUBLICATE(head);

	}
	else {
		std::cout << "Sort by first digit" << std::endl;
		head = sortfg(head);
	}
	std::cout << "Result: " << std::endl;
	
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
bool nevfg(Node*, bool usefg);
Node* MAKE(int value);
void ADD(Node* head, int value);
void PRINT(Node* head);
void CLEAR(Node* head);
Node* CREATELIST(int value);
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
	return orig == fake;
}

bool nevfg(Node* head, bool usefg) {
	if (head == nullptr || head->next == nullptr) {
		return true;
	}
	Node* nast = head;
	Node* sled = head->next;

	while (sled != nullptr) {
		int dnast, dsled;
		if (usefg) {
			dnast = fg(nast->data);
			dsled = fg(sled->data);
		}
		else {
			dnast = lg(nast->data);
			dsled = lg(sled->data);
		}
		if (dnast < dsled) {
			return false;
		}
		nast = sled;
		sled = sled->next;
	}
	return true;

		
}
	


Node* CREATELIST(int n) {
	if (n <= 0) return nullptr;
	int value;
	std::cin >> value;
	Node* head = MAKE(value);
	Node* nast = head;

	for (int i = 1; i < n; i++) {
		std::cin >> value;
		nast->next = MAKE(value);
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

Node* sortfg(Node* head) {
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
				int temp = nast->data;
				nast->data = nast->next->data;
				nast->next->data = temp;

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
