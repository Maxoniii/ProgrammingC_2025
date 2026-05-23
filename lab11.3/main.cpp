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



matrix matrix::operator++(int) {
    matrix temp(*this);
    ++(*this);
    return temp;
}


matrix operator+(const matrix& lhs, const matrix& rhs) {
    if (lhs.get_str() != rhs.get_str() || lhs.get_slb() != rhs.get_slb()) {
        throw std::invalid_argument("Размеры матрицы должны совпадать для сложения");
    }
    matrix result(lhs.get_str(), lhs.get_slb());
    for (size_t i = 0; i < lhs.get_str(); ++i) {
        for (size_t j = 0; j < lhs.get_slb(); ++j) {
            result.sh(i, j) = lhs.sh(i, j) + rhs.sh(i, j);
        }
    }
    return result;
}

matrix& matrix::operator*=(const matrix& rhs) {
    // Проверка согласованности размеров: число столбцов левой == числу строк правой
    if (this->get_slb() != rhs.get_str()) {
        throw std::invalid_argument("Размеры матриц несовместимы для умножения");
    }

    // Создаем временную матрицу нужного размера
    matrix result(this->get_str(), rhs.get_slb());

    // Алгоритм умножения строк на столбцы
    for (size_t i = 0; i < this->get_str(); ++i) {
        for (size_t j = 0; j < rhs.get_slb(); ++j) {
            double sum = 0.0;
            for (size_t k = 0; k < this->get_slb(); ++k) {
                sum += this->sh(i, k) * rhs.sh(k, j);
            }
            result.sh(i, j) = sum;
        }
    }

    // Присваиваем результат текущему объекту
    *this = result; 
    return *this;
}



// 1. Получение матрицы-минора (без строки row_to_remove и столбца col_to_remove)
matrix matrix::get_minor_matrix(size_t row_to_remove, size_t col_to_remove) const {
    if (this->get_str() <= 1 || this->get_slb() <= 1) {
        throw std::logic_error("Невозможно получить минор для матрицы размера меньше 2x2");
    }

    // Новая матрица будет на 1 строку и 1 столбец меньше
    matrix result(this->get_str() - 1, this->get_slb() - 1);
    
    size_t target_i = 0;
    for (size_t i = 0; i < this->get_str(); ++i) {
        if (i == row_to_remove) continue; // Пропускаем удаляемую строку
        
        size_t target_j = 0;
        for (size_t j = 0; j < this->get_slb(); ++j) {
            if (j == col_to_remove) continue; // Пропускаем удаляемый столбец
            
            result.sh(target_i, target_j) = this->sh(i, j);
            target_j++;
        }
        target_i++;
    }
    return result;
}

// 2. Рекурсивное вычисление определителя (детерминанта) матрицы
double matrix::determinant() const {
    if (this->get_str() != this->get_slb()) {
        throw std::logic_error("Определитель считается только для квадратных матриц");
    }

    size_t n = this->get_str();

    // Базовые случаи для рекурсии
    if (n == 1) {
        return this->sh(0, 0);
    }
    if (n == 2) {
        return this->sh(0, 0) * this->sh(1, 1) - this->sh(0, 1) * this->sh(1, 0);
    }

    double det = 0.0;
    // Разложение по первой строке (индекс 0)
    for (size_t j = 0; j < n; ++j) {
        double sign = (j % 2 == 0) ? 1.0 : -1.0;
        det += sign * this->sh(0, j) * this->get_minor_matrix(0, j).determinant();
    }
    return det;
}

// 3. Вычисление алгебраического дополнения для элемента (i, j)
double matrix::cofactor(size_t i, size_t j) const {
    if (this->get_str() != this->get_slb()) {
        throw std::logic_error("Алгебраическое дополнение считается только для квадратных матриц");
    }
    
    // Знак определяется суммой индексов (-1)^(i+j)
    // В C++ индексы с 0, поэтому математическая логика сохраняется
    double sign = ((i + j) % 2 == 0) ? 1.0 : -1.0;
    
    // Алгебраическое дополнение — это знак умноженный на детерминант минора
    return sign * this->get_minor_matrix(i, j).determinant();
}



matrix operator*(const matrix& lhs, const matrix& rhs) {
    matrix result(lhs); // Копируем левую матрицу
    result *= rhs;      // Используем внутренний оператор *=
    return result;      // Возвращаем результат
}





double matrix::determinant() const {
    // Шаг 1: Проверяем, квадратная ли матрица. Другие не считаются!
    if (this->get_str() != this->get_slb()) {
        throw std::logic_error("Определитель можно посчитать только для КВАДРАТНОЙ матрицы!");
    }

    size_t size = this->get_str(); // Получаем размер (например, 3 для матрицы 3х3)

    // Шаг 2: БАЗА (Самый низ матрешки)
    // Если матрица 1х1 — определитель равен этому единственному числу
    if (size == 1) {
        return this->sh(0, 0);
    }

    // Если матрица 2х2 — считаем по простой формуле "крест-накрест" (ad - bc)
    if (size == 2) {
        double main_diagonal = this->sh(0, 0) * this->sh(1, 1); // Главная (левый верх - правый низ)
        double side_diagonal = this->sh(0, 1) * this->sh(1, 0); // Побочная (правый верх - левый низ)
        return main_diagonal - side_diagonal; 
    }

    // Шаг 3: РЕКУРСИЯ (Разбиваем большую матрицу)
    // Если матрица 3х3, 4х4 и больше — раскладываем её по первой строке
    double total_det = 0.0;
    double sign = 1.0; // Знаки у элементов всегда чередуются: плюс, минус, плюс, минус...

    for (size_t j = 0; j < size; ++j) {
        // 1. Берем число из первой строки: это всегда строка 0, столбец j
        double current_element = this->sh(0, j);

        // 2. Получаем «вырезанную» матрицу-минор (удаляем строку 0 и текущий столбец j)
        matrix smaller_matrix = this->get_minor_matrix(0, j);

        // 3. Считаем определитель этой маленькой матрицы (матрешка открывается дальше)
        double smaller_det = smaller_matrix.determinant();

        // 4. Складываем всё в общую копилку с учетом знака (+ или -)
        total_det += sign * current_element * smaller_det;

        // 5. Меняем знак для следующего элемента (был плюс — станет минус, и наоборот)
        sign = -sign; 
    }

    return total_det; // Возвращаем итоговый ответ
}
double matrix::determinant() const {
    // Шаг 1: Проверка на квадратность
    if (this->get_str() != this->get_slb()) {
        throw std::logic_error("Определитель считается только для КВАДРАТНЫЙ матриц!");
    }

    size_t size = this->get_str();

    // Шаг 2: БАЗОВЫЕ СЛУЧАИ (Остановка рекурсии)
    
    // Матрица 1х1
    if (size == 1) {
        return this->sh(0, 0);
    }

    // Матрица 2х2 (обычный "крест")
    if (size == 2) {
        return this->sh(0, 0) * this->sh(1, 1) - this->sh(0, 1) * this->sh(1, 0);
    }

    // Матрица 3х3 (Правило треугольников / Саррюса)
    if (size == 3) {
        // Главные диагонали и параллельные им треугольники (идут со знаком ПЛЮС)
        double plus_elements = this->sh(0, 0) * this->sh(1, 1) * this->sh(2, 2) +
                               this->sh(0, 1) * this->sh(1, 2) * this->sh(2, 0) +
                               this->sh(1, 0) * this->sh(2, 1) * this->sh(0, 2);

        // Побочные диагонали и параллельные им треугольники (идут со знаком МИНУС)
        double minus_elements = this->sh(0, 2) * this->sh(1, 1) * this->sh(2, 0) +
                                this->sh(0, 1) * this->sh(1, 0) * this->sh(2, 2) +
                                this->sh(1, 2) * this->sh(2, 1) * this->sh(0, 0);

        return plus_elements - minus_elements;
    }

    // Шаг 3: РЕКУРСИЯ (Для матриц 4х4, 5х5 и больше)
    double total_det = 0.0;
    double sign = 1.0; 

    for (size_t j = 0; j < size; ++j) {
        double current_element = this->sh(0, j);
        
        // Вырезаем минорную матрицу (она станет на 1 размер меньше)
        matrix smaller_matrix = this->get_minor_matrix(0, j);

        // Рекурсивный вызов (если матрица была 4х4, то smaller_matrix станет 3х3 
        // и на следующем шаге мгновенно посчитается по формуле выше!)
        double smaller_det = smaller_matrix.determinant();

        total_det += sign * current_element * smaller_det;

        sign = -sign; // Чередуем знак (+ , - , + , -)
    }

    return total_det;
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






