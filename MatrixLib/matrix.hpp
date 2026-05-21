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
void swap(matrix& a,matrix& b);
}
