#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>
#include <string>
#include <vector>

class BigInt {
private:
    std::vector<char> digits;
    bool negative;


    static int compare_abs(const BigInt& a, const BigInt& b);
    static BigInt add_abs(const BigInt& a, const BigInt& b);
    static BigInt subtract_abs(const BigInt& a, const BigInt& b);
    static BigInt multiply_abs(const BigInt& a, const BigInt& b);
    static void divide_abs(const BigInt& a, const BigInt& b, BigInt& quotient, BigInt& remainder);


    void normalize();

public:
    BigInt();
    BigInt(const std::string& str);
    BigInt(const char* str);
    BigInt(const BigInt&) = default;
    BigInt& operator=(const BigInt&) = default;
    ~BigInt() = default;

    std::string toString() const;


    BigInt operator-() const;


    bool operator==(const BigInt& other) const;
    bool operator!=(const BigInt& other) const;
    bool operator<(const BigInt& other) const;
    bool operator>(const BigInt& other) const;
    bool operator<=(const BigInt& other) const;
    bool operator>=(const BigInt& other) const;

    BigInt& operator+=(const BigInt& other);
    BigInt& operator-=(const BigInt& other);
    BigInt& operator*=(const BigInt& other);
    BigInt& operator/=(const BigInt& other);
    BigInt& operator%=(const BigInt& other);

    BigInt operator+(const BigInt& other) const;
    BigInt operator-(const BigInt& other) const;
    BigInt operator*(const BigInt& other) const;
    BigInt operator/(const BigInt& other) const;
    BigInt operator%(const BigInt& other) const;

    BigInt& operator++();
    BigInt operator++(int);
    BigInt& operator--();
    BigInt operator--(int);


    BigInt pow(int exponent) const;
    BigInt root(int n) const;


};

std::istream& operator>>(std::istream& is, BigInt& num);
std::ostream& operator<<(std::ostream& os, const BigInt& num);

#endif // BIGINT_H
