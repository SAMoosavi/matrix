#ifndef MATRIX_EXPRESSION_H
#define MATRIX_EXPRESSION_H

#include <cstdint>
#include <string>
#include <vector>

class Expression {
public:
    Expression(double constant, const char variable, int64_t power);
    Expression(double constant, const std::string& variables);
    Expression(double constant);

    Expression operator+(const Expression& expression);
    Expression operator-(const Expression& expression);
    Expression operator*(const Expression& expression);
    Expression operator/(const Expression& expression);

    Expression& operator+=(const Expression& expression);
    Expression& operator-=(const Expression& expression);
    Expression& operator*=(const Expression& expression);
    Expression& operator/=(const Expression& expression);

private:
    struct Variable {
        char variable;
        int64_t power = 1;
    };
    double constant;
    std::vector<Variable> variables;
    int64_t power;
};


#endif //MATRIX_EXPRESSION_H
