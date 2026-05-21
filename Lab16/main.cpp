#include <iostream>
#include "matrix.hpp"


int main(){
    mt::matrix A(5,6);
    for (size_t i = 0; i < A.get_str(); ++i) {
        for (size_t j = 0; j < A.get_slb(); ++j) {
            A.sh(i, j) = i * 10.0 + j;
        }
    }

    mt::matrix D(1,1);
    for (size_t i = 0; i < A.get_str(); ++i) {
        for (size_t j = 0; j < A.get_slb(); ++j) {
            A.sh(i, j) = i * 10.0 + j;
        }
    }

    D = A;
    D.print();

    std::cout<<"Matrix A: "<<std::endl;
    A.print();


    std::cout<<"Copy matrix A = B"<<std::endl;
    mt::matrix B = A;

    B.sh(0,0)= 99.0;

    A.print();

    B.print();

    mt::matrix C(1,1);
    C = A;
    C.print();


    std::cout<<"Before swap: "<< A.sh(0,0)<< "   " << C.sh(0,0)<<std::endl;

    mt::swap(A,C);
    std::cout<<"After swap: "<< A.sh(0,0)<< "   " << C.sh(0,0)<<std::endl;



    return 0;

}
