#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "func.hpp"

int main() {
    std::ifstream input_file("input.txt");
    if (!input_file.is_open()) {
        std::cout << "Not open file" << std::endl;
        return 1;
    }

    std::string text;
    std::string line;
    while (std::getline(input_file, line)) {
        text += line + "\n";
    }
    input_file.close();

    int bykv_count[26] = { 0 };
    for (int i = 0; i < text.length(); i++) {
        char c = text[i];
        if (is_alpha(c)) {
            char low_c = to_lower(c);
            int ind = low_c - 'a';
            if (ind >= 0 && ind < 26) {
                bykv_count[ind]++;
            }
        }
    }
    std::vector<int> posl;
    std::vector<char>bykv;

    for (int i = 0; i < 26; i++) {
        if (bykv_count[i] > 0) {
            posl.push_back(bykv_count[i]);
            bykv.push_back('a' + i);
        }
    }

    int n = posl.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (posl[j] < posl[j + 1]) {
                int trp_posl = posl[j];
                posl[j] = posl[j + 1];
                posl[j + 1] = trp_posl;

                char trp_char = bykv[j];
                bykv[j] = bykv[j + 1];
                bykv[j + 1] = trp_char;

            }
        }
    }


    std::vector<char>povtor;
    int count;
    if (n < 8) {
        count = n;
    }
    else {
        count = 8;
    }
    for (int i = 0; i < count; i++) {
        povtor.push_back(bykv[i]);
    }


    std::string result;
    int i = 0;
    while (i < text.length()) {
        if (is_alpha(text[i])) {
            int word_st = i;
            std::string orig;

            while (i < text.length() && is_alpha(text[i])) {
                orig += text[i];
                i++;
            }

            std::string low_word = to_lower(orig);
            int fd_count = 0;
            std::string fd_bykv;


            for (int j = 0; j < povtor.size(); j++) {
                char nast_bykv = povtor[j];
                bool bykv_fd = false;
                for (int k = 0; k < low_word.length(); k++) {
                    if (low_word[k] == nast_bykv) {
                        bykv_fd = true;
                        break;
                    }
                }
                if (bykv_fd) {
                    fd_count++;
                    fd_bykv += to_upper_sym(nast_bykv);
                }
            }


            if (fd_count >= 5) {
                std::string up_word = to_upper(orig);
                result += up_word;
                result += " (" + fd_bykv + ") ";
            }
            else {
                result += orig;
            }
        }
        else {
            result += text[i];
            i++;
        }
    }

    std::ofstream output_file("output.txt");
    if (!output_file.is_open()) {
        std::cout << "Not create .txt" << std::endl;
        return 1;
    }
    output_file << result;
    output_file.close();


    std::cout << "Result wrote in output.txt" << std::endl;
    std::cout << "Most posl letters: ";
    for (int j = 0; j < povtor.size(); j++) {
        std::cout << povtor[j];
        if (j < povtor.size() - 1) std::cout << ", ";
    }
    return 0;
}







#include <iostream>
#include "func.hpp"


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


char to_upper_sym(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - LOWUP;
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



std::string to_upper(const std::string& s) {
    std::string result = s;
    for (int i = 0; i < result.length(); i++) {
        result[i] = to_upper_sym(result[i]);
    }
    return result;
}








#pragma once
#include <iostream>
#include <string>
#include <vector>

bool is_alpha(char c);
char to_lower(char c);
char to_upper_sym(char c);
std::string to_lower(const std::string& s);
std::string to_upper(const std::string& s);






