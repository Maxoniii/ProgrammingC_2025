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

#include "matrix.hpp"
#include <iostream>
#include <algorithm>

namespace mt{

void matrix::_swap(matrix& other){
    std::swap(str_,other.str_);
    std::swap(slb_,other.slb_);
    std::swap(data_,other.data_);

}
matrix::matrix(): str_(0), slb_(0), data_(nullptr){}

matrix::matrix(size_t str, size_t slb):str_(str),slb_(slb),data_(new double[str*slb]){

    std::fill(data_, data_ + str * slb, 0.0);

}

matrix::~matrix(){
    if (data_!= nullptr){
        delete[] data_;
        data_ = nullptr;
    }
}


matrix::matrix(const matrix& other)
    : str_(other.str_), slb_(other.slb_), data_(new double[str_ * slb_]) {

    std::copy(other.data_, other.data_ + str_ * slb_, data_);
}


matrix& matrix::operator= (matrix other){

    _swap(other);
    return *this;
}

double& matrix::sh(size_t str,size_t slb){
    if (str>=str_ || slb>=slb_){
        std::cout<<"Error: Escape from matrix"<<std::endl;

        static double zagl = 0.0;
        return zagl;
    }

    return data_[str*slb_+slb];
}


const double& matrix::sh(size_t str, size_t slb) const {
    if (str >= str_ || slb >= slb_) {
        std::cout << "Error: Escape from matrix" << std::endl;
        static const double zagl = 0.0;
        return zagl;
    }
    return data_[str * slb_ + slb];
}


void matrix::print() const{
    if (is_empty()){
        std::cout<<"Matrix is empty"<<std::endl;
        return;
    }

    for (size_t i =0; i<str_; i++){
        for(size_t j = 0; j<slb_; j++){
            std::cout<<sh(i,j)<<' ';
        }
        std::cout<<std::endl;
    }
}


void matrix::swap_with(matrix& other){
    _swap(other);

}

void swap(matrix&a,matrix&b){
    a.swap_with(b);
}



matrix& matrix::operator++() {
    for (size_t i = 0; i < str_ * slb_; ++i) {
        data_[i] += 1.0;
    }
    return *this;
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

matrix operator*(const matrix& lhs, const matrix& rhs) {
    matrix result(lhs);
    result *= rhs;
    return result;
}


matrix operator*=(const matrix& rhs) {
    if (this->get_slb() != rhs.get_str) {
        throw std::invalid_argument("Размеры матрицы должны совпадать для сложения");
    }
    matrix result(this->get_str(), rhs.get_slb());
    for (size_t i = 0; i < this->get_str(); ++i) {
        for (size_t j = 0; j < rhs.get_slb(); ++j) {
            double sum = 0.0;
            for (size_t k = 0; k < this->get_slb(); ++k) {
                sum += this->sh(i, k) * rhs.sh(k, j);
            }
            result.sh(i, j) = sum;
        }
    }
}
matrix matrix::get_minor_matrix(size_t str, size_t slb) {
    matrix result(this->get_str() - 1, this->get_slb() - 1);
    size_t t_i = 0;
    for (size_t i = 0; i < this->get_str(); ++i) {
        if (i == str) continue;

        size_t t_j = 0;
        for (size_t j = 0; j < this->get_slb(); ++j) {
            if (j == slb) continue;
            result.sh(t_i, t_j) = this->sh(i, j);
            t_j++;
        }
        t_i++;
    }
    return result;
}

double matrix::determinate() const {
    if (this->get_str() != this->get_slb()) {
        throw std::logic_error("Определитель считается только для квадратных матриц");

    }
    size_t n = this->get_str();

    if (n == 1) {
        return this->sh(0, 0);
    }

    if (n == 2) {
        return (this->sh(0, 0) * this->sh(1, 1)) - (this->sh(0, 1) * this->sh(1, 0));
    }

    if (n == 3) {
        double glavn_elem=(this->sh(0, 0) * this->sh(1, 1) * this->sh(2, 2)) + (this->sh(1, 0) * this->sh(2, 1) * this->sh(0, 2)) + (this->sh(0, 1) * this->sh(1, 2) * this->sh(2, 0));
        double poboch_elem = (this->sh(0, 2) * this->sh(1, 1) * this->sh(2, 0)) + (this->sh(0, 1) * this->sh(1, 0) * this->sh(2, 2) + (this->sh(1, 2) * this->sh(2, 1) * this->sh(0, 0));
        return glavn_elem - poboch_elem;
    }

    double deter = 0.0;
    double sign = 1.0;
    
    for (size_t j = 0; j < size; ++j) {
        double nast = this->sh(0, j);

        matrix obrezn = this->get_minor_matrix(0, j);

        double mini_determinite = obrezn.determinate();

        deter += sign * nast * mini_determinate;

        sign = -sign;
    }

    return deter;
}


double matrix::algebr_dop(size_t i, size_t j) const
    if (this->get_str() != this->get_slb()) {
        throw std::logic_error("Алгебраическое дополнение считается только для квадратных матриц");
    }
    
    sign = ((i + j) % 2 == 0) ? 1.0 : -1.0;

    return sign * this->get_minor_matrix(i, j).determinant();
}

#ifndef MATRIX_H
#define MATRIX_H

class matrix
{
public:
    matrix();
};
#endif // MATRIX_H

#pragma once 
#include <cstddef>
#include <stdexcept>
namespace mt{
class matrix{
private:
    size_t str_;
    size_t slb_;
    double* data_;

    void _swap(matrix& other);
public:
    matrix();

    explicit matrix(size_t str,size_t slb);

    ~matrix();

    matrix(const matrix& other);
    
    matrix& operator=(matrix other);


    double& sh(size_t str,size_t slb);

    const double& sh(size_t str, size_t slb) const;

    void print()const;

    void swap_with(matrix& other);

    size_t get_str()const{
        return str_;
    };

    size_t get_slb()const{
        return slb_;
    };

    size_t get_quantity()const{
        return str_*slb_;
    };


    bool is_empty()const{
        return str_ == 0 || slb_==0;
    };

    matrix& operator++();
    matrix operator++(int);



};
matrix operator+(const matrix& lhs,const matrix& rhs);
matrix operator*(const matrix& lhs, const matrix& rhs);
void swap(matrix& a,matrix& b);
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


#include "matrix.hpp"
#include <iomanip>

// Конструкторы
matrix::matrix() : str(0), slb(0) {}

matrix::matrix(size_t n, size_t m) : str(n), slb(m) {
    data.resize(n, std::vector<double>(m, 0.0));
}

matrix::matrix(const matrix& other) : str(other.str), slb(other.slb), data(other.data) {}

// Операторы присваивания
matrix& matrix::operator=(const matrix& other) {
    if (this != &other) {
        str = other.str;
        slb = other.slb;
        data = other.data;
    }
    return *this;
}

// Доступ к элементам
double& matrix::operator()(size_t i, size_t j) {
    if (i >= str || j >= slb) {
        throw std::out_of_range("Индекс вне границ матрицы");
    }
    return data[i][j];
}

double matrix::operator()(size_t i, size_t j) const {
    if (i >= str || j >= slb) {
        throw std::out_of_range("Индекс вне границ матрицы");
    }
    return data[i][j];
}

// Геттеры
size_t matrix::get_str() const { return str; }
size_t matrix::get_slb() const { return slb; }

double matrix::sh(size_t i, size_t j) const {
    if (i >= str || j >= slb) {
        throw std::out_of_range("Индекс вне границ матрицы");
    }
    return data[i][j];
}

// Ввод матрицы
void matrix::input() {
    std::cout << "Введите элементы матрицы " << str << "x" << slb << ":\n";
    for (size_t i = 0; i < str; ++i) {
        for (size_t j = 0; j < slb; ++j) {
            std::cin >> data[i][j];
        }
    }
}

// Вывод матрицы
void matrix::print() const {
    for (size_t i = 0; i < str; ++i) {
        for (size_t j = 0; j < slb; ++j) {
            std::cout << std::setw(10) << std::setprecision(4) << data[i][j] << " ";
        }
        std::cout << "\n";
    }
}

// Получение минорной матрицы (удаление строки row и столбца col)
matrix matrix::get_minor_matrix(size_t row, size_t col) const {
    if (str <= 1 || slb <= 1) {
        throw std::logic_error("Нельзя получить минор из матрицы 1x1");
    }
    
    matrix result(str - 1, slb - 1);
    
    size_t minor_i = 0;
    for (size_t i = 0; i < str; ++i) {
        if (i == row) continue;
        
        size_t minor_j = 0;
        for (size_t j = 0; j < slb; ++j) {
            if (j == col) continue;
            result.data[minor_i][minor_j] = data[i][j];
            minor_j++;
        }
        minor_i++;
    }
    
    return result;
}

// Алгебраическое дополнение элемента (i,j)
double matrix::algebraic_complement(size_t i, size_t j) const {
    // Проверка на квадратность
    if (str != slb) {
        throw std::logic_error("Алгебраическое дополнение только для квадратных матриц");
    }
    
    // Получаем минорную матрицу
    matrix minor_matrix = get_minor_matrix(i, j);
    
    // Вычисляем минор (определитель минорной матрицы)
    double minor = minor_matrix.determinant();
    
    // Алгебраическое дополнение с учётом знака (-1)^(i+j)
    double sign = ((i + j) % 2 == 0) ? 1.0 : -1.0;
    
    return sign * minor;
}

// Вычисление определителя (ваша реализация с выводом)
double matrix::determinant() const {
    std::cout << "\n=== Вызов determinant() для матрицы размером " << str << "x" << slb << " ===\n";
    
    // Шаг 1: Проверка на квадратность
    if (this->get_str() != this->get_slb()) {
        throw std::logic_error("Определитель считается только для КВАДРАТНЫЙ матриц!");
    }
    
    size_t size = this->get_str();
    
    // Выводим матрицу
    std::cout << "Текущая матрица:\n";
    this->print();
    std::cout << std::endl;
    
    // Шаг 2: БАЗОВЫЕ СЛУЧАИ (Остановка рекурсии)
    
    // Матрица 1х1
    if (size == 1) {
        double result = this->sh(0, 0);
        std::cout << "Базовый случай: матрица 1x1, определитель = " << result << "\n";
        std::cout << "=== Возврат: " << result << " ===\n\n";
        return result;
    }
    
    // Матрица 2х2 (обычный "крест")
    if (size == 2) {
        double a = this->sh(0, 0), b = this->sh(0, 1);
        double c = this->sh(1, 0), d = this->sh(1, 1);
        double result = a * d - b * c;
        std::cout << "Базовый случай: матрица 2x2\n";
        std::cout << "det = (" << a << " * " << d << ") - (" << b << " * " << c << ") = " << result << "\n";
        std::cout << "=== Возврат: " << result << " ===\n\n";
        return result;
    }
    
    // Матрица 3х3 (Правило треугольников / Саррюса)
    if (size == 3) {
        double a = this->sh(0,0), b = this->sh(0,1), c = this->sh(0,2);
        double d = this->sh(1,0), e = this->sh(1,1), f = this->sh(1,2);
        double g = this->sh(2,0), h = this->sh(2,1), i_elem = this->sh(2,2);
        
        double plus_elements = a * e * i_elem + b * f * g + d * h * c;
        double minus_elements = c * e * g + b * d * i_elem + f * h * a;
        double result = plus_elements - minus_elements;
        
        std::cout << "Базовый случай: матрица 3x3 (правило Саррюса)\n";
        std::cout << "Плюс слагаемые: " << a << "*" << e << "*" << i_elem << " + " 
                  << b << "*" << f << "*" << g << " + " << d << "*" << h << "*" << c 
                  << " = " << plus_elements << "\n";
        std::cout << "Минус слагаемые: " << c << "*" << e << "*" << g << " + "
                  << b << "*" << d << "*" << i_elem << " + " << f << "*" << h << "*" << a
                  << " = " << minus_elements << "\n";
        std::cout << "det = " << plus_elements << " - " << minus_elements << " = " << result << "\n";
        std::cout << "=== Возврат: " << result << " ===\n\n";
        return result;
    }
    
    // Шаг 3: РЕКУРСИЯ (Для матриц 4х4, 5х5 и больше)
    std::cout << "Рекурсивный случай: разложение по первой строке\n";
    std::cout << "Формула: det = Σ (-1)^(0+j) * a[0][j] * M[0][j]\n\n";
    
    double total_det = 0.0;
    double sign = 1.0;
    
    for (size_t j = 0; j < size; ++j) {
        double current_element = this->sh(0, j);
        
        std::cout << "--- Шаг " << j + 1 << " ---\n";
        std::cout << "Элемент a[0][" << j << "] = " << current_element << "\n";
        std::cout << "Знак: " << (sign > 0 ? "+" : "-") << "\n";
        
        // Вырезаем минорную матрицу
        matrix smaller_matrix = this->get_minor_matrix(0, j);
        std::cout << "Минорная матрица M[0][" << j << "] (удалены строка 0 и столбец " << j << "):\n";
        smaller_matrix.print();
        std::cout << "Рекурсивный вызов для минора...\n";
        
        // Рекурсивный вызов
        double smaller_det = smaller_matrix.determinant();
        
        double term = sign * current_element * smaller_det;
        total_det += term;
        
        std::cout << "Вклад в определитель: " << (sign > 0 ? "+" : "-") 
                  << "(" << current_element << " * " << smaller_det << ") = " << term << "\n";
        std::cout << "Текущая сумма = " << total_det << "\n\n";
        
        sign = -sign;
    }
    
    std::cout << "=== Окончательный определитель = " << total_det << " ===\n\n";
    return total_det;
}

// Демонстрация алгебраических дополнений
void matrix::print_with_minors() const {
    if (str != slb) {
        std::cout << "Матрица не квадратная!\n";
        return;
    }
    
    std::cout << "\n=== АЛГЕБРАИЧЕСКИЕ ДОПОЛНЕНИЯ ===\n";
    std::cout << "Исходная матрица:\n";
    print();
    
    for (size_t i = 0; i < str; ++i) {
        for (size_t j = 0; j < slb; ++j) {
            double complement = algebraic_complement(i, j);
            std::cout << "A[" << i << "][" << j << "] = ";
            std::cout << "(-1)^(" << i << "+" << j << ") * M[" << i << "][" << j << "] = ";
            double sign = ((i + j) % 2 == 0) ? 1.0 : -1.0;
            std::cout << (sign > 0 ? "+" : "-") << " * " << abs(complement) << " = " << complement << "\n";
        }
    }
}

// Демонстрация полного процесса вычисления
void matrix::print_determinant_details() const {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "ВЫЧИСЛЕНИЕ ОПРЕДЕЛИТЕЛЯ\n";
    std::cout << std::string(60, '=') << "\n";
    
    try {
        double det = determinant();
        std::cout << "\n" << std::string(60, '-') << "\n";
        std::cout << "ИТОГОВЫЙ РЕЗУЛЬТАТ: det = " << det << "\n";
        std::cout << std::string(60, '-') << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
    }
}




#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <vector>
#include <stdexcept>

class matrix {
private:
    size_t str;  // количество строк
    size_t slb;  // количество столбцов
    std::vector<std::vector<double>> data;  // данные матрицы
    
public:
    // Конструкторы
    matrix();
    matrix(size_t n, size_t m);
    matrix(const matrix& other);
    
    // Деструктор
    ~matrix() = default;
    
    // Операторы присваивания
    matrix& operator=(const matrix& other);
    
    // Доступ к элементам
    double& operator()(size_t i, size_t j);
    double operator()(size_t i, size_t j) const;
    
    // Геттеры
    size_t get_str() const;
    size_t get_slb() const;
    
    // Доступ к элементу (ваш метод sh)
    double sh(size_t i, size_t j) const;
    
    // Ввод/вывод
    void input();
    void print() const;
    
    // Получение минорной матрицы (удаление строки row и столбца col)
    matrix get_minor_matrix(size_t row, size_t col) const;
    
    // Алгебраическое дополнение элемента (i,j)
    double algebraic_complement(size_t i, size_t j) const;
    
    // Вычисление определителя
    double determinant() const;
    
    // Дополнительные методы для демонстрации
    void print_with_minors() const;
    void print_determinant_details() const;
};

#endif


#include "matrix.hpp"
#include <iostream>
#include <iomanip>

void print_separator() {
    std::cout << "\n" << std::string(70, '=') << "\n";
}

int main() {
    std::cout << "ПРОГРАММА ДЛЯ ВЫЧИСЛЕНИЯ ОПРЕДЕЛИТЕЛЯ МАТРИЦ\n";
    std::cout << "Демонстрация работы рекурсивного алгоритма через миноры\n";
    
    // ========== ТЕСТ 1: Матрица 1x1 ==========
    print_separator();
    std::cout << "ТЕСТ 1: Матрица 1x1\n";
    matrix m1(1, 1);
    m1(0, 0) = 5;
    m1.print_determinant_details();
    
    // ========== ТЕСТ 2: Матрица 2x2 ==========
    print_separator();
    std::cout << "ТЕСТ 2: Матрица 2x2\n";
    matrix m2(2, 2);
    m2(0, 0) = 1; m2(0, 1) = 2;
    m2(1, 0) = 3; m2(1, 1) = 4;
    m2.print_determinant_details();
    
    // ========== ТЕСТ 3: Матрица 3x3 ==========
    print_separator();
    std::cout << "ТЕСТ 3: Матрица 3x3 (правило Саррюса)\n";
    matrix m3(3, 3);
    m3(0, 0) = 2; m3(0, 1) = -1; m3(0, 2) = 0;
    m3(1, 0) = 1; m3(1, 1) = 3;  m3(1, 2) = 2;
    m3(2, 0) = 4; m3(2, 1) = 0;  m3(2, 2) = -1;
    m3.print_determinant_details();
    
    // Дополнительно: покажем алгебраические дополнения для матрицы 3x3
    print_separator();
    m3.print_with_minors();
    
    // ========== ТЕСТ 4: Матрица 4x4 (рекурсивный случай) ==========
    print_separator();
    std::cout << "ТЕСТ 4: Матрица 4x4 (рекурсивное разложение)\n";
    matrix m4(4, 4);
    m4(0, 0) = 1; m4(0, 1) = 2; m4(0, 2) = 0; m4(0, 3) = 1;
    m4(1, 0) = 0; m4(1, 1) = 1; m4(1, 2) = 1; m4(1, 3) = 0;
    m4(2, 0) = 1; m4(2, 1) = 0; m4(2, 2) = 2; m4(2, 3) = 1;
    m4(3, 0) = 0; m4(3, 1) = 1; m4(3, 2) = 0; m4(3, 3) = 2;
    m4.print_determinant_details();
    
    // ========== ТЕСТ 5: Матрица 4x4 (единичная) ==========
    print_separator();
    std::cout << "ТЕСТ 5: Единичная матрица 4x4 (определитель = 1)\n";
    matrix m5(4, 4);
    for (size_t i = 0; i < 4; ++i) {
        m5(i, i) = 1;
    }
    m5.print_determinant_details();
    
    // ========== ТЕСТ 6: Ввод матрицы от пользователя ==========
    print_separator();
    std::cout << "ТЕСТ 6: Ввод матрицы пользователем\n";
    size_t n;
    std::cout << "Введите размер квадратной матрицы: ";
    std::cin >> n;
    
    matrix user_matrix(n, n);
    user_matrix.input();
    user_matrix.print_determinant_details();
    
    // ========== Дополнительно: связь миноров и определителя ==========
    print_separator();
    std::cout << "ВАЖНОЕ ЗАМЕЧАНИЕ О СВЯЗИ МИНОРОВ И ОПРЕДЕЛИТЕЛЯ:\n";
    std::cout << "Определитель матрицы можно вычислить как сумму произведений\n";
    std::cout << "элементов любой строки на их алгебраические дополнения:\n\n";
    std::cout << "det = Σ a[i][j] * A[i][j]\n";
    std::cout << "где A[i][j] = (-1)^(i+j) * M[i][j], а M[i][j] - минор (определитель минорной матрицы)\n\n";
    
    std::cout << "В моей реализации:\n";
    std::cout << "1. Для 1x1 и 2x2 - прямые формулы\n";
    std::cout << "2. Для 3x3 - правило Саррюса\n";
    std::cout << "3. Для 4x4 и больше - рекурсивное разложение по первой строке\n";
    std::cout << "4. Каждый рекурсивный вызов уменьшает размерность матрицы\n";
    std::cout << "5. Рекурсия доходит до базовых случаев 1x1, 2x2 или 3x3\n";
    
    std::cout << "\nПрограмма завершена.\n";
    
    return 0;
}






























#include "matrix.hpp"
#include <iostream>
#include <algorithm>
#include <stdexcept>

namespace mt {

void matrix::_swap(matrix& other) {
    std::swap(str_, other.str_);
    std::swap(slb_, other.slb_);
    std::swap(data_, other.data_);
}

matrix::matrix() : str_(0), slb_(0), data_(nullptr) {}

matrix::matrix(size_t str, size_t slb) : str_(str), slb_(slb), data_(new double[str * slb]) {
    std::fill(data_, data_ + str * slb, 0.0);
}

matrix::~matrix() {
    if (data_ != nullptr) {
        delete[] data_;
        data_ = nullptr;
    }
}

matrix::matrix(const matrix& other)
    : str_(other.str_), slb_(other.slb_), data_(new double[str_ * slb_]) {
    std::copy(other.data_, other.data_ + str_ * slb_, data_);
}

matrix& matrix::operator=(matrix other) {
    _swap(other);
    return *this;
}

double& matrix::sh(size_t str, size_t slb) {
    if (str >= str_ || slb >= slb_) {
        std::cout << "Error: Escape from matrix" << std::endl;
        static double zagl = 0.0;
        return zagl;
    }
    return data_[str * slb_ + slb];
}

const double& matrix::sh(size_t str, size_t slb) const {
    if (str >= str_ || slb >= slb_) {
        std::cout << "Error: Escape from matrix" << std::endl;
        static const double zagl = 0.0;
        return zagl;
    }
    return data_[str * slb_ + slb];
}

void matrix::input() {
    if (is_empty()) {
        std::cout << "Matrix is empty, nothing to input" << std::endl;
        return;
    }
    for (size_t i = 0; i < str_; ++i) {
        for (size_t j = 0; j < slb_; ++j) {
            std::cin >> sh(i, j);
        }
    }
}

void matrix::print() const {
    if (is_empty()) {
        std::cout << "Matrix is empty" << std::endl;
        return;
    }
    for (size_t i = 0; i < str_; i++) {
        for (size_t j = 0; j < slb_; j++) {
            std::cout << sh(i, j) << ' ';
        }
        std::cout << std::endl;
    }
}

void matrix::swap_with(matrix& other) {
    _swap(other);
}

void swap(matrix& a, matrix& b) {
    a.swap_with(b);
}

matrix& matrix::operator++() {
    for (size_t i = 0; i < str_ * slb_; ++i) {
        data_[i] += 1.0;
    }
    return *this;
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

matrix operator*(const matrix& lhs, const matrix& rhs) {
    matrix result(lhs);
    result *= rhs;
    return result;
}

matrix& matrix::operator*=(const matrix& rhs) {
    if (this->get_slb() != rhs.get_str()) {
        throw std::invalid_argument("Количество столбцов левой матрицы должно совпадать с количеством строк правой");
    }
    matrix result(this->get_str(), rhs.get_slb());
    for (size_t i = 0; i < this->get_str(); ++i) {
        for (size_t j = 0; j < rhs.get_slb(); ++j) {
            double sum = 0.0;
            for (size_t k = 0; k < this->get_slb(); ++k) {
                sum += this->sh(i, k) * rhs.sh(k, j);
            }
            result.sh(i, j) = sum;
        }
    }
    *this = result;
    return *this;
}

matrix matrix::get_minor_matrix(size_t str, size_t slb) const {
    matrix result(this->get_str() - 1, this->get_slb() - 1);
    size_t t_i = 0;
    for (size_t i = 0; i < this->get_str(); ++i) {
        if (i == str) continue;

        size_t t_j = 0;
        for (size_t j = 0; j < this->get_slb(); ++j) {
            if (j == slb) continue;
            result.sh(t_i, t_j) = this->sh(i, j);
            t_j++;
        }
        t_i++;
    }
    return result;
}

double matrix::determinate() const {
    if (this->get_str() != this->get_slb()) {
        throw std::logic_error("Определитель считается только для квадратных матриц");
    }
    
    size_t n = this->get_str();

    if (n == 0) return 0.0;
    if (n == 1) return this->sh(0, 0);

    if (n == 2) {
        return (this->sh(0, 0) * this->sh(1, 1)) - (this->sh(0, 1) * this->sh(1, 0));
    }

    if (n == 3) {
        double glavn_elem = (this->sh(0, 0) * this->sh(1, 1) * this->sh(2, 2)) + 
                            (this->sh(1, 0) * this->sh(2, 1) * this->sh(0, 2)) + 
                            (this->sh(0, 1) * this->sh(1, 2) * this->sh(2, 0));
        
        double poboch_elem = (this->sh(0, 2) * this->sh(1, 1) * this->sh(2, 0)) + 
                             (this->sh(0, 1) * this->sh(1, 0) * this->sh(2, 2)) + 
                             (this->sh(1, 2) * this->sh(2, 1) * this->sh(0, 0));
        return glavn_elem - poboch_elem;
    }

    double deter = 0.0;
    for (size_t j = 0; j < n; ++j) {
        deter += this->sh(0, j) * this->algebr_dop(0, j);
    }

    return deter;
}

double matrix::algebr_dop(size_t i, size_t j) const {
    if (this->get_str() != this->get_slb()) {
        throw std::logic_error("Алгебраическое дополнение считается только для квадратных матриц");
    }
    
    double sign = ((i + j) % 2 == 0) ? 1.0 : -1.0;
    return sign * this->get_minor_matrix(i, j).determinate();
}

} // namespace mt

