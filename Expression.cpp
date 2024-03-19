#include "Expression.h"
#include <format>
#include <cmath>



std::vector<Expression::Variable> Expression::create_variables(const std::string &_variables) {
    std::vector<Variable> result(26, Variable(' ', 0));
    size_t i = 0, temp;
    int64_t _power;
    while (i < _variables.size()) {
        if (is_alpha(_variables[i])) {
            temp = i + 2;
            if (_variables[i + 1] != '^')
                throw std::invalid_argument("_variables format should be like this:\nx^2\n");
            _power = find_number(temp, _variables);

            result[_variables[i] - 'a'].variable = _variables[i];
            result[_variables[i] - 'a'].power += _power;

            i = temp;
        } else
            throw std::invalid_argument("_variables format should be like this:\nx^2y^3\n");
    }
    return find_variables(result);
}

constexpr std::vector<Expression::Variable> Expression::find_variables(const std::vector<Variable> &_variables) {
    std::vector<Expression::Variable> result;
    for (const auto &variable: _variables) {
        if (variable.power != 0)
            result.emplace_back(variable);
    }
    return result;
}

int64_t Expression::find_number(size_t &index, const std::string &_variables) {
    std::string result;
    if (_variables[index] == '-') {
        result += '-';
        ++index;
    }
    while (index < _variables.size() && is_number(_variables[index])) {
        result += _variables[index];
        ++index;
    }
    return std::stoi(result);
}

bool Expression::is_similar_terms(const Expression &expression) const {
    bool result = true;
    if (_variables.size() != expression._variables.size())
        result = false;
    else {
        std::vector<int16_t> all_alphabets(26, -1);
        for (int16_t i = 0; i < _variables.size(); ++i)
            all_alphabets[_variables[i].variable - 'a'] = i;
        int16_t temp;
        for (const auto &var: expression._variables) {
            temp = all_alphabets[var.variable - 'a'];
            if ((temp == -1) || (_variables[temp].variable != var.variable ||
                                 (_variables[temp].power * this->_power) != (var.power * expression._power))) {
                result = false;
                break;
            }
        }
    }

    return result;
}


Expression::Expression(double _constant, const char variable, int64_t _power) :
        _constant(_constant),
        _power(_power) {
    if (_constant != 0 && _power != 0)
        _variables.emplace_back(variable);
}

Expression::Expression(double _constant, const std::string &_variables) :
        _constant(_constant),
        _power(1) {
    if (_constant != 0)
        this->_variables = create_variables(_variables);
}

Expression::Expression(double _constant) :
        _constant(_constant),
        _power(1) {}

Expression &Expression::operator+=(const Expression &expression) {
    if (is_similar_terms(expression)) {
        _constant += expression._constant;
        check_expression();
    } else
        throw std::invalid_argument("two expressions should have same _variables and same _powers.");

    return *this;
}

Expression &Expression::operator-=(const Expression &expression) {
    if (is_similar_terms(expression)) {
        _constant -= expression._constant;
        check_expression();
    } else
        throw std::invalid_argument("two expressions should have same _variables and same _powers.");
    return *this;
}

Expression &Expression::operator*=(const Expression &expression) {
    _constant *= expression._constant;
    std::vector<int16_t> alphas(26, -1);
    for (int16_t i = 0; i < _variables.size(); ++i) {
        alphas[_variables[i].variable - 'a'] = i;
        _variables[i].power *= _power;
    }
    _power = 1;
    for (const auto &var: expression._variables) {
        if (alphas[var.variable - 'a'] == -1)
            _variables.emplace_back(var.variable, var.power * expression._power);
        else
            _variables[alphas[var.variable - 'a']].power += var.power * expression._power;
    }
    check_expression();
    return *this;
}

Expression &Expression::operator/=(const Expression &expression) {
    if (expression.constant() != 0) {
        _constant /= expression._constant;
        std::vector<int16_t> alphas(26, -1);
        for (int16_t i = 0; i < _variables.size(); ++i) {
            alphas[_variables[i].variable - 'a'] = i;
            _variables[i].power *= _power;
        }
        _power = 1;
        for (const auto &var: expression._variables) {
            if (alphas[var.variable - 'a'] == -1)
                _variables.emplace_back(var.variable, -1 * var.power * expression._power);
            else
                _variables[alphas[var.variable - 'a']].power -= var.power * expression._power;
        }
        check_expression();
    }
    return *this;
}

void Expression::check_expression() {
    if (_constant == 0) {
        _variables.clear();
        _power = 1;
    } else {
        size_t i = 0;
        while (i < _variables.size()) {
            if (_variables[i].power == 0) {
                std::swap(_variables[i], _variables.back());
                _variables.pop_back();
            } else
                ++i;
        }
    }
}

Expression Expression::operator+(const Expression &expression) const {
    return Expression(*this) += expression;
}

Expression Expression::operator-(const Expression &expression) const {
    return Expression(*this) -= expression;
}

Expression Expression::operator*(const Expression &expression) const {
    return Expression(*this) *= expression;
}

Expression Expression::operator/(const Expression &expression) const {
    return Expression(*this) /= expression;
}



long double Expression::set_value(const std::vector<std::pair<char, double>> &values) const {
    if (_variables.size() > values.size())
        throw std::invalid_argument(std::format("there should be {} at least argument.", _variables.size()));
    std::vector<double> alphabets(26, INT64_MIN);
    for (const auto &pair: values)
        alphabets[pair.first - 'a'] = pair.second;

    long double result = 0;
    double temp;
    for (auto &var: _variables) {
        temp = alphabets['a' + var.variable];
        if (temp == INT64_MIN)
            throw std::invalid_argument(std::format("not specified {} in values.", var.variable));
        result += powf64x(temp, var.power);
    }
    result = powf64x(result, _power) * _constant;

    return result;
}

long double Expression::set_value(const std::pair<char, double> &value) const {
    if (_variables.size() > 1)
        throw std::invalid_argument(std::format("there should be {} at least argument.", _variables.size()));

    long double result = 0;
    if (!_variables.empty()) {
        for (auto &var: _variables) {
            if (var.variable != value.first)
                throw std::invalid_argument(std::format("not specified {} in values.", var.variable));
            result += powf64x(value.second, var.power);
        }
        result = powf64x(result, _power) * _constant;
    } else
        result = _constant;

    return result;
}
