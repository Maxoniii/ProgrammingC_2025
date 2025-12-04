#include <iostream>


int main() {
	unsigned long long h = 257;
	std::cout << "Number: " << h << std::endl;
	std::cout << "Size: " << sizeof(h) << " bytes" << std::endl;


	unsigned char* byte = (unsigned char*)&h;


	std::cout << "Bytes: ";
	for (int i = 0; i < sizeof(h); i++) {
		std::cout << static_cast<int>(byte[i]) << " ";
	}
	std::cout << std::endl;

	return 0;
}