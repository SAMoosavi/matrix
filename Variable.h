#ifndef MATRIX_VARIABLE_H
#define MATRIX_VARIABLE_H

#include <string>
#include <vector>

class Variable {
public:
    Variable(double constant, std::string variable, int64_t power);
    Variable(double constant, std::string variable);
    Variable(double constant);

    Variable operator+(const Variable& variable);
    Variable operator-(const Variable& variable);
    Variable operator*(const Variable& variable);
    Variable operator/(const Variable& variable);
    Variable& operator-=(const Variable& variable);
    Variable& operator+=(const Variable& variable);
    Variable& operator*=(const Variable& variable);
    Variable& operator/=(const Variable& variable);

private:
    double constant;
    std::string variable;
    int64_t power;
};


#endif //MATRIX_VARIABLE_H
