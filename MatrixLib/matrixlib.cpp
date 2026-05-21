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

}
