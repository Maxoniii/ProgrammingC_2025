#include "bigint.h"
#include <algorithm>
#include <cctype>
#include <cmath>
#include <stdexcept>


void BigInt::normalize() {
    while (digits.size() > 1 && digits.back() == 0) {
        digits.pop_back();
    }
    if (digits.size() == 1 && digits[0] == 0) {
        negative = false;
    }
}

int BigInt::compare_abs(const BigInt& a, const BigInt& b) {
    if (a.digits.size() != b.digits.size()) {
        return a.digits.size() < b.digits.size() ? -1 : 1;
    }
    for (int i = static_cast<int>(a.digits.size()) - 1; i >= 0; --i) {
        if (a.digits[i] != b.digits[i]) {
            return a.digits[i] < b.digits[i] ? -1 : 1;
        }
    }
    return 0;
}

BigInt BigInt::add_abs(const BigInt& a, const BigInt& b) {
    BigInt result;
    result.digits.clear();
    int carry = 0;
    size_t maxSize = std::max(a.digits.size(), b.digits.size());
    for (size_t i = 0; i < maxSize || carry; ++i) {
        int sum = carry;
        if (i < a.digits.size()) sum += a.digits[i];
        if (i < b.digits.size()) sum += b.digits[i];
        result.digits.push_back(sum % 10);
        carry = sum / 10;
    }
    return result;
}

BigInt BigInt::subtract_abs(const BigInt& a, const BigInt& b) {
    BigInt result;
    result.digits.clear();
    int borrow = 0;
    for (size_t i = 0; i < a.digits.size(); ++i) {
        int diff = a.digits[i] - borrow;
        if (i < b.digits.size()) diff -= b.digits[i];
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.digits.push_back(diff);
    }
    result.normalize();
    return result;
}

BigInt BigInt::multiply_abs(const BigInt& a, const BigInt& b) {
    BigInt result;
    result.digits.assign(a.digits.size() + b.digits.size(), 0);
    for (size_t i = 0; i < a.digits.size(); ++i) {
        int carry = 0;
        for (size_t j = 0; j < b.digits.size() || carry; ++j) {
            long long cur = result.digits[i + j] + carry;
            if (j < b.digits.size()) cur += a.digits[i] * b.digits[j];
            result.digits[i + j] = cur % 10;
            carry = cur / 10;
        }
    }
    result.normalize();
    return result;
}

void BigInt::divide_abs(const BigInt& a, const BigInt& b, BigInt& quotient, BigInt& remainder) {
    if (b.digits.size() == 1 && b.digits[0] == 0) {
        throw std::invalid_argument("Division by zero");
    }
    quotient = BigInt("0");
    remainder = a;

    if (compare_abs(a, b) < 0) {
        return;
    }


    std::vector<char> quotDigits;
    BigInt current;
    for (int i = static_cast<int>(a.digits.size()) - 1; i >= 0; --i) {
        current.digits.insert(current.digits.begin(), a.digits[i]);
        current.normalize();


        int digit = 0;
        int low = 0, high = 10;
        while (low <= high) {
            int mid = (low + high) / 2;
            BigInt product = multiply_abs(b, BigInt(std::to_string(mid)));
            if (compare_abs(product, current) <= 0) {
                digit = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        quotDigits.push_back(digit);
        if (digit > 0) {
            BigInt product = multiply_abs(b, BigInt(std::to_string(digit)));
            current = subtract_abs(current, product);
        }
    }


    std::reverse(quotDigits.begin(), quotDigits.end());
    quotient.digits.clear();
    for (char d : quotDigits) {
        quotient.digits.push_back(d);
    }
    quotient.normalize();

    remainder = current;
    remainder.normalize();
}


BigInt::BigInt() : negative(false) {
    digits.push_back(0);
}

BigInt::BigInt(const std::string& str) {
    if (str.empty()) {
        throw std::invalid_argument("Пустая строка");
    }
    size_t start = 0;
    negative = false;
    if (str[0] == '-') {
        negative = true;
        start = 1;
    }
    if (start == str.length()) {
        throw std::invalid_argument("Только знак минус");
    }
    digits.clear();
    for (size_t i = start; i < str.length(); ++i) {
        if (!std::isdigit(str[i])) {
            throw std::invalid_argument("Недопустимый символ в числе");
        }
        digits.push_back(str[i] - '0');
    }
    std::reverse(digits.begin(), digits.end());
    normalize();
    if (digits.size() > 1000) {
        throw std::length_error("Число превышает 1000 цифр");
    }
}

BigInt::BigInt(const char* str) : BigInt(std::string(str)) {}

std::string BigInt::toString() const {
    if (digits.empty()) return "0";
    std::string res;
    if (negative && !(digits.size() == 1 && digits[0] == 0)) {
        res += '-';
    }
    for (int i = static_cast<int>(digits.size()) - 1; i >= 0; --i) {
        res += static_cast<char>(digits[i] + '0');
    }
    return res;
}

BigInt BigInt::operator-() const {
    BigInt result = *this;
    if (!(result.digits.size() == 1 && result.digits[0] == 0)) {
        result.negative = !result.negative;
    }
    return result;
}


bool BigInt::operator==(const BigInt& other) const {
    return negative == other.negative && digits == other.digits;
}

bool BigInt::operator!=(const BigInt& other) const {
    return !(*this == other);
}

bool BigInt::operator<(const BigInt& other) const {
    if (negative != other.negative) {
        return negative;
    }
    if (negative) {
        return compare_abs(*this, other) > 0;
    } else {
        return compare_abs(*this, other) < 0;
    }
}

bool BigInt::operator>(const BigInt& other) const {
    return other < *this;
}

bool BigInt::operator<=(const BigInt& other) const {
    return !(other < *this);
}

bool BigInt::operator>=(const BigInt& other) const {
    return !(*this < other);
}


BigInt& BigInt::operator+=(const BigInt& other) {
    if (negative == other.negative) {
        digits = add_abs(*this, other).digits;
    } else {
        int cmp = compare_abs(*this, other);
        if (cmp == 0) {
            digits = {0};
            negative = false;
        } else if (cmp > 0) {
            digits = subtract_abs(*this, other).digits;
        } else {
            digits = subtract_abs(other, *this).digits;
            negative = other.negative;
        }
    }
    normalize();
    return *this;
}

BigInt& BigInt::operator-=(const BigInt& other) {
    *this += (-other);
    return *this;
}

BigInt& BigInt::operator*=(const BigInt& other) {
    digits = multiply_abs(*this, other).digits;
    negative = negative != other.negative;
    if (digits.size() == 1 && digits[0] == 0) negative = false;
    normalize();
    return *this;
}

BigInt& BigInt::operator/=(const BigInt& other) {
    BigInt quotient, remainder;
    divide_abs(*this, other, quotient, remainder);
    bool resNeg = negative != other.negative;
    *this = quotient;
    if (digits.size() == 1 && digits[0] == 0) {
        negative = false;
    } else {
        negative = resNeg;
    }
    normalize();
    return *this;
}

BigInt& BigInt::operator%=(const BigInt& other) {
    BigInt quotient, remainder;
    divide_abs(*this, other, quotient, remainder);

    *this = remainder;
    negative = negative;
    normalize();
    return *this;
}

BigInt BigInt::operator+(const BigInt& other) const {
    BigInt result = *this;
    result += other;
    return result;
}

BigInt BigInt::operator-(const BigInt& other) const {
    BigInt result = *this;
    result -= other;
    return result;
}

BigInt BigInt::operator*(const BigInt& other) const {
    BigInt result = *this;
    result *= other;
    return result;
}

BigInt BigInt::operator/(const BigInt& other) const {
    BigInt result = *this;
    result /= other;
    return result;
}

BigInt BigInt::operator%(const BigInt& other) const {
    BigInt result = *this;
    result %= other;
    return result;
}


BigInt& BigInt::operator++() {
    *this += BigInt("1");
    return *this;
}

BigInt BigInt::operator++(int) {
    BigInt temp = *this;
    ++(*this);
    return temp;
}

BigInt& BigInt::operator--() {
    *this -= BigInt("1");
    return *this;
}

BigInt BigInt::operator--(int) {
    BigInt temp = *this;
    --(*this);
    return temp;
}


BigInt BigInt::pow(int exponent) const {
    if (exponent < 0) {
        throw std::invalid_argument("Отрицательная степень недопустима");
    }
    BigInt result("1");
    BigInt base = *this;
    while (exponent > 0) {
        if (exponent & 1) {
            result *= base;
        }
        base *= base;
        exponent >>= 1;
    }
    return result;
}

BigInt BigInt::root(int n) const {
    if (n <= 0) {
        throw std::invalid_argument("Корень должен быть положительным");
    }
    if (negative && n % 2 == 0) {
        throw std::invalid_argument("Корень отрицательного числа не может быть целым");
    }

    BigInt absVal = negative ? -*this: *this;

    if(absVal == BigInt("0")){
        return BigInt("0");
    }
    size_t numDig = absVal.digits.size();
    size_t rootDig = ceil((numDig/n)+1);

    BigInt high;
    if(rootDig<=1){
        high = BigInt("9");
    }
    else{
        std::string highstr(rootDig, '9');
        high = BigInt(highstr);
    }
    BigInt low("0");
    BigInt one("1");
    BigInt result("0");

    while (high.pow(n) < *this && high.pow(n) < high) {
        high = high * BigInt("2");
    }

    while (low <= high) {
        BigInt mid = (low + high) / BigInt("2");
        BigInt power = mid.pow(n);
        int cmp = compare_abs(power, *this);
        if (cmp == 0) {
            result = mid;
            break;
        } else if (cmp < 0) {
            result = mid;
            low = mid + one;
        } else {
            high = mid - one;
        }
    }

    if (negative && n % 2 == 1) {
        result.negative = true;
    }
    return result;
}



std::ostream& operator<<(std::ostream& os, const BigInt& num) {
    os << num.toString();
    return os;
}

std::istream& operator>>(std::istream& is, BigInt& num) {
    std::string s;
    is >> s;
    num = BigInt(s);
    return is;
}
