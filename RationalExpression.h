#ifndef MATRIX_RATIONALEXPRESSION_H
#define MATRIX_RATIONALEXPRESSION_H

#include "Polynomial.h"

class RationalExpression {
public:
    explicit RationalExpression(Polynomial numerator, Polynomial denominator = Polynomial(1));

    RationalExpression(const RationalExpression& another);

    RationalExpression(RationalExpression&& another) noexcept ;

    inline bool operator==(const RationalExpression& another) const;

    inline RationalExpression &operator+=(const RationalExpression &another);

    inline RationalExpression &operator-=(const RationalExpression &another);

    inline RationalExpression &operator*=(const RationalExpression &another);

    inline RationalExpression &operator/=(const RationalExpression &another);

    inline RationalExpression &power_equal(const int64_t &power);

    inline RationalExpression &derivate_equal();

    inline RationalExpression operator+(const RationalExpression &another) const;

    inline RationalExpression operator-(const RationalExpression &another) const;

    inline RationalExpression operator*(const RationalExpression &another) const;

    inline RationalExpression operator/(const RationalExpression &another) const;

    inline RationalExpression power(const int64_t &power) const;

    inline RationalExpression derivate() const;

    Polynomial::PolynomialRoot solve(double guess = 0, const uint16_t &max_iteration = 100,
                                     const uint16_t &precision = 6) const;

    inline long double set_value(const std::vector<std::pair<char, double>> &values) const;

    inline long double set_value(const std::pair<char, double> &values) const;

private:
    Polynomial numerator;
    Polynomial denominator;

    inline Polynomial calculate_common_denominator(const Polynomial& another) const;
};

#include "RationalExpression-inl.h"

#endif //MATRIX_RATIONALEXPRESSION_H
