#include <iostream>
#include "func.hpp"
#include <string>
#include <vector>

int main() {
	std::string text;
	std::cout << "Enter text: " << std::endl;
	std::getline(std::cin, text);

	std::vector<std::string>words = all_words(text);

	std::vector<std::string>repeated_glasn_words;
	std::vector<std::string>inverted_words;

	for (int i = 0; i < words.size(); i++) {
		std::string word = words[i];

		if (repeat_glasn(word)) {
			repeated_glasn_words.push_back(word);
		}
		else {
			std::string inverted = invert(word);
			inverted_words.push_back(inverted);
		}
	}

	alphabet(repeated_glasn_words);

	std::cout << "Words with repeated glasn: " << std::endl;
	for (int i = 0; i < repeated_glasn_words.size(); i++) {
		std::cout << repeated_glasn_words[i] << " ";
	}
	std::cout << "Inverted words: " << std::endl;
	for (int i = 0; inverted_words[i].size(); i++) {
		std::cout << inverted_words[i] << " ";
	}

	return 0;
}







#include "func.hpp"
#include <iostream>


const char LOWUP = 32;

bool is_alpha(char c) {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}


char to_lower(char c) {
	if (c >= 'A' && c <= 'Z') {
		return c + LOWUP;
	}
	return c;
}

std::string to_lower(const std::string& s) {
	std::string result = s;
	for (int i = 0; i < result.length(); i++) {
		result[i] = to_lower(result[i]);
	}
	return result;
}

bool is_glasn(char c) {
	c = to_lower(c);
	const char* glasn = "aeiou";

	for (int i = 0; glasn[i] != '\0'; i++) {
		if (c == glasn[i]) {
			return true;
		}
	}
	return false;
}


std::vector<std::string> all_words(const std::string& text) {
	std::vector<std::string>words;
	std::string nast_word;

	for (int i = 0; i < text.length(); i++) {
		char c = text[i];

		if (is_alpha(c)) {
			nast_word += c;
		}
		else {
			if (!nast_word.empty()) {
				words.push_back(nast_word);
				nast_word.clear();
			}
		}
	}

	if (!nast_word.empty()) {
		words.push_back(nast_word);
	}
	return words;
}



bool repeat_glasn(const std::string& word) {
	std::string low_word = to_lower(word);

	bool seen[5] = { false };
	for (int i = 0; i < low_word.length(); i++) {
		char c = low_word[i];

		if (is_glasn(c)) {
			int index = -1;
			switch (c) {
			case 'a': index = 0;
				break;
			case 'e': index = 1;
				break;
			case 'i': index = 2;
				break;
			case 'o': index = 3;
				break;
			case 'u': index = 4;
				break;
			}

			if (index != -1 && seen[index]) {
				return true;
			}

			if (index != -1) {
				seen[index] = true;
			}
		}
	}
	return false;
}

std::string invert(const std::string& word) {
	std::string result = word;
	for (int i = 0; i < result.length() / 2; i++) {
		char trp = result[i];
		result[i] = result[result.length() - 1 - i];
		result[result.length() - 1 - i] = trp;
	}

	return result;
}


void alphabet(std::vector<std::string>& words) {
	int n = words.size();
	bool swapp;
	for (int i = 0; i < n - 1; i++) {
		swapp = false;

		for (int j = 0; j < n - i - 1; i++) {
			std::string word1 = to_lower(words[j]);
			std::string word2 = to_lower(words[j + 1]);

			if (word1 > word2) {
				std::string trp = words[j];
				words[j] = words[j + 1];
				words[j + 1] = trp;
				swapp = true;
			}
		}
		if (!swapp) {
			break;
		}
	}
}






#pragma once
#include <vector>
#include <string>

bool is_alpha(char c);
char to_lower(char c);
std::string to_lower(const std::string& s);
bool is_glasn(char c);
std::vector<std::string> all_words(const std::string& text);
bool repeat_glasn(const std::string& word);
std::string invert(const std::string& word);
void alphabet(std::vector<std::string>& words);