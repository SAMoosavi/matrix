#ifndef MATRIX_EXPRESSION_H
#define MATRIX_EXPRESSION_H

#include <cstdint>
#include <string>
#include <vector>
#include <iostream>

class Expression {
public:
    struct Variable {
        char variable;
        int64_t power = 1;

        inline bool operator==(const Variable &another) const;
    };

    Expression(double constant, const char variable, int64_t power);

    Expression(double constant, const std::string &variables);

    explicit Expression(double constant);

    Expression &operator+=(const Expression &expression);

    Expression &operator-=(const Expression &expression);

    Expression &operator*=(const Expression &expression);

    Expression &operator/=(const Expression &expression);

    inline Expression &power_equal(const int64_t &pow);

    Expression operator+(const Expression &expression) const;

    Expression operator-(const Expression &expression) const;

    Expression operator*(const Expression &expression) const;

    Expression operator/(const Expression &expression) const;

    inline Expression power(const int64_t &pow) const;

    bool is_similar_terms(const Expression &expression) const;

    inline double constant() const;

    inline const std::vector<Variable> &variables() const;

    inline int64_t power() const;

    long double set_value(const std::vector<std::pair<char, double>> &values) const;

    long double set_value(const std::pair<char, double> &value) const;

    inline bool operator==(const Expression &expression) const;

    friend inline std::ostream &operator<<(std::ostream &os, const Expression &expr);

private:
    double _constant;
    std::vector<Variable> _variables;
    int64_t _power;

    static std::vector<Variable> create_variables(const std::string &variables);

    static constexpr std::vector<Variable> find_variables(const std::vector<Variable> &variables);

    static inline constexpr bool is_alpha(const char &ch) noexcept;

    static inline constexpr bool is_number(const char &ch) noexcept;

    static int64_t find_number(size_t &index, const std::string &variables);

    void check_expression();
};

#include "Expression-inl.h"


#endif //MATRIX_EXPRESSION_H
