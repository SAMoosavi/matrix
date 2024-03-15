#include "Expression.h"
#include <stdexcept>


std::vector<Expression::Variable> Expression::create_variables(const std::string &variables) {
    std::vector<Variable> result(26, Variable(' ', 0));
    size_t i = 0, temp;
    int64_t power;
    while (i < variables.size()) {
        if (is_alpha(variables[i])) {
            temp = i + 2;
            if (variables[i + 1] != '^')
                throw std::invalid_argument("variables format should be like this:\nx^2\n");
            power = find_number(temp, variables);

            result['z' - variables[i]].variable = variables[i];
            result['z' - variables[i]].power += power;

            i = temp;
        } else
            throw std::invalid_argument("variables format should be like this:\nx^2y^3\n");
    }
    return find_variables(result);
}

constexpr std::vector<Expression::Variable> Expression::find_variables(const std::vector<Variable> &variables) {
    std::vector<Expression::Variable> result;
    for (const auto &variable: variables) {
        if (variable.power != 0)
            result.emplace_back(variable);
    }
    return result;
}

constexpr int64_t Expression::find_number(size_t &index, const std::string &variables) {
    std::string result;
    if (variables[index] == '-') {
        result += '-';
        ++index;
    }
    while (index < variables.size() && is_number(variables[index])) {
        result += variables[index];
        ++index;
    }
    return std::stoi(result);
}

Expression::Expression(double constant, const char variable, int64_t power) :
        constant(constant),
        power(power) {
    variables.emplace_back(variable);
}

Expression::Expression(double constant, const std::string &variables) :
        constant(constant),
        variables(create_variables(variables)),
        power(1) {}

Expression::Expression(double constant) :
        constant(constant),
        power(0) {}

constexpr bool Expression::are_expressions_same(const Expression &expression) const {
    bool result = true;
    if (variables.size() == expression.variables.size()) {
        for (size_t i = 0; i < variables.size(); ++i) {
            if (variables[i] != expression.variables[i]) {
                result = false;
                break;
            }
        }
    } else
        result = false;

    return result;
}


Expression Expression::operator+(const Expression &expression) {
    if (are_expressions_same(expression))
        constant += expression.constant;
    else
        throw std::invalid_argument("two expressions should have same variables and same powers.");
}

Expression Expression::operator-(const Expression &expression) {
    if (are_expressions_same(expression))
        constant -= expression.constant;
    else
        throw std::invalid_argument("two expressions should have same variables and same powers.");
}

Expression Expression::operator*(const Expression &expression) {
    constant *= expression.constant;
    std::vector<int16_t> alphas(26, -1);
    for (int16_t i = 0; i < variables.size(); ++i) {
        alphas['z' - variables[i].variable] = i;
        variables[i].power *= power;
    }
    power = 1;
    for (const auto &var: expression.variables) {
        if (alphas['z' - var.variable] == -1)
            variables.emplace_back(var.variable, var.power * expression.power);
        else
            variables[alphas['z' - var.variable]].power += var.power * expression.power;
    }
    return *this;
}

Expression Expression::operator/(const Expression &expression) {
    constant /= expression.constant;
    std::vector<int16_t> alphas(26, -1);
    for (int16_t i = 0; i < variables.size(); ++i) {
        alphas['z' - variables[i].variable] = i;
        variables[i].power *= power;
    }
    power = 1;
    for (const auto &var: expression.variables) {
        if (alphas['z' - var.variable] == -1)
            variables.emplace_back(var.variable, -1 * var.power * expression.power);
        else
            variables[alphas['z' - var.variable]].power -= var.power * expression.power;
    }
    return *this;
}
