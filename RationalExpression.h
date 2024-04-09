#ifndef MATRIX_RATIONALEXPRESSION_H
#define MATRIX_RATIONALEXPRESSION_H

#include "Polynomial.h"

class RationalExpression {
public:
    explicit RationalExpression(Polynomial numerator, Polynomial denominator = Polynomial(1));

    RationalExpression& operator+=(const RationalExpression& another);
    RationalExpression& operator-=(const RationalExpression& another);
    RationalExpression& operator*=(const RationalExpression& another);
    RationalExpression& operator/=(const RationalExpression& another);
    RationalExpression& power_equal(const int64_t& power);

    inline RationalExpression operator+(const RationalExpression& another) const;
    inline RationalExpression operator-(const RationalExpression& another) const;
    inline RationalExpression operator*(const RationalExpression& another) const;
    inline RationalExpression operator/(const RationalExpression& another) const;
    inline RationalExpression power(const int64_t& power) const;

    Polynomial::PolynomialRoot solve(double guess = 0, const uint16_t &max_iteration = 100,
                                     const uint16_t &precision = 6) const;

    long double set_value(const std::vector<std::pair<char, double>> &values) const;

    long double set_value(const std::pair<char, double> &values) const;

private:
    Polynomial numerator;
    Polynomial denominator;
};

#include "RationalExpression-inl.h"

#endif //MATRIX_RATIONALEXPRESSION_H
