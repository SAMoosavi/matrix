#include <stdexcept>
#include <cmath>
#include <format>
#include <cfloat>
#include "Polynomial.h"

void Polynomial::delete_repeated_expressions(std::vector<Expression> &expressions) {
    for (size_t i = 0; i < expressions.size(); ++i) {
        size_t j = i + 1;
        while (j < expressions.size()) {
            if (expressions[i].is_similar_terms(expressions[j])) {
                expressions[i] += expressions[j];
                std::swap(expressions[j], expressions.back());
                expressions.pop_back();
            } else
                ++j;
        }
    }
}

Polynomial::PolynomailVariableMaxPower Polynomial::create_variables(const std::vector<int64_t> &alphabets) {
    Polynomial::PolynomailVariableMaxPower result;
    for (size_t i = 0; i < alphabets.size(); ++i) {
        if (alphabets[i] != INT64_MIN)
            result.emplace_back('a' + i, alphabets[i]);
    }
    return result;
}

int32_t Polynomial::create_random_number(const int32_t &max_value) {
    srand(time(0));
    return rand() % max_value;
}

Polynomial::Polynomial(std::vector<Expression> expressions) {
    if (!expressions.empty()) {
        delete_repeated_expressions(expressions);
        all_expressions = std::move(expressions);
    } else
        throw std::invalid_argument("there should be one expression at least.");
}

Polynomial::Polynomial(Expression expression) :
        all_expressions(std::vector<Expression>{std::move(expression)}) {}

Expression *Polynomial::find_similar_expression(const Expression &expression) const {
    Expression *result = nullptr;
    for (auto &expr: all_expressions) {
        if (expr.is_similar_terms(expression)) {
            result = (Expression *) &expr;
            break;
        }
    }

    return result;
}

Polynomial &Polynomial::operator+=(const Polynomial &another) {
    Expression *temp;
    for (auto &expr: another.all_expressions) {
        temp = find_similar_expression(expr);
        if (temp)
            *temp += expr;
        else
            all_expressions.emplace_back(expr);
    }
    return *this;
}

Polynomial &Polynomial::operator-=(const Polynomial &another) {
    Expression *temp;
    for (auto &expr: another.all_expressions) {
        temp = find_similar_expression(expr);
        if (temp)
            *temp -= expr;
        else {
            all_expressions.emplace_back(Expression(-1) *= expr);
        }
    }

    return *this;
}

Polynomial &Polynomial::operator*=(const Polynomial &another) {
    Polynomial temp = *this, first_stage = *this;
    for (const auto &expr: another.all_expressions) {
        for (auto &temp_expr: temp.all_expressions)
            temp_expr *= expr;
        *this += temp;
        temp = first_stage;
    }
    return *this;
}

Polynomial &Polynomial::operator/=(const Expression &another) {
    for (auto &expr: all_expressions)
        expr *= another;
    return *this;
}

Polynomial Polynomial::operator+(const Polynomial &another) const {
    return Polynomial(*this) += another;
}

Polynomial Polynomial::operator-(const Polynomial &another) const {
    return Polynomial(*this) -= another;
}

Polynomial Polynomial::operator*(const Polynomial &another) const {
    return Polynomial(*this) *= another;
}

Polynomial Polynomial::operator/(const Expression &another) const {
    return Polynomial(*this) /= another;
}

bool Polynomial::check_solve_validation(const Polynomial::PolynomailVariableMaxPower &variableMaxPower) const {
    bool result = false;
    if (variableMaxPower.empty()) {
        // need to test when it completed
        if (all_expressions.begin()->constant() == 0)
            throw std::runtime_error("this Polynomial has infinity answers.");
        else
            throw std::runtime_error("there is no answer.");
    } else if (variableMaxPower.size() > 1)
        throw std::runtime_error("there is no support to solving multi-variable polynomials.");
    else
        result = true;

    return result;
}

Polynomial::PolynomialRoot Polynomial::solve(double guess) const {
    PolynomailVariableMaxPower variableMaxPower = find_variables_and_max_power();
    PolynomialRoot roots;
    if (check_solve_validation(variableMaxPower)) {
        // it need to test that the polynomial save unique expressions
        if (variableMaxPower.begin()->power == 1)
            roots = solve_linear_equation();
        else if (variableMaxPower.begin()->power == 2)
            roots = solve_quardatic_equation();
        else if (variableMaxPower.begin()->power == 3)
            roots = solve_cubic_equation();
        else
            roots = solve_by_newton_technique(guess);
    }
    return roots;
}

Polynomial::PolynomailVariableMaxPower Polynomial::find_variables_and_max_power() const {
    // check  when there is constant only
    PolynomailVariableMaxPower result;
    std::vector<int64_t> alphabets(26, INT64_MIN);
    for (const auto &expr: all_expressions) {
        if (expr.constant() != 0) {
            for (const auto &var: expr.variables()) {
                if (var.power * expr.power() > alphabets['z' - var.variable])
                    alphabets['z' - var.variable] = var.power * expr.power();
            }
        }

    }

    result = create_variables(alphabets);

    return result;
}

Expression *Polynomial::find_expression_by_power(int64_t target_power) const {
    Expression *result = nullptr;
    if (target_power == 0) {
        for (auto &expr: all_expressions) {
            if (expr.variables().empty() || (expr.variables().begin()->power * expr.power() == target_power)) {
                result = (Expression *) &expr;
                break;
            }
        }
    } else {
        for (auto &expr: all_expressions) {
            if (expr.variables().begin()->power * expr.power() == target_power) {
                result = (Expression *) &expr;
                break;
            }
        }
    }
    return result;
}

Polynomial::PolynomialRoot Polynomial::solve_linear_equation() const {
    // expressions need to be simplified
    PolynomialRoot result(1);
    Expression *constant = find_expression_by_power(0);
    Expression *one_power = find_expression_by_power(1);

    result[0] = -1 * constant->constant() / one_power->constant();

    return result;
}

Polynomial::PolynomialRoot Polynomial::solve_quardatic_equation() const {
    PolynomialRoot result;
    Expression *constant = find_expression_by_power(0);
    Expression *one_power = find_expression_by_power(1);
    Expression *two_power = find_expression_by_power(2);

    double delta = pow(one_power->constant(), 2) - 4 * two_power->constant() * constant->constant();

    if (delta == 0) {
        result.emplace_back(-1 * one_power->constant() / 2 * two_power->constant());
    } else if (delta > 0) {
        result.emplace_back((-1 * one_power->constant() + sqrt(delta)) / 2 * two_power->constant());
        result.emplace_back((-1 * one_power->constant() - sqrt(delta)) / 2 * two_power->constant());
    }

    return result;
}

Polynomial::PolynomialRoot Polynomial::solve_cubic_equation() const {
    Expression *constant = find_expression_by_power(0);
    Expression *one_power = find_expression_by_power(1);
    Expression *two_power = find_expression_by_power(2);
    Expression *three_power = find_expression_by_power(3);

    double a = two_power->constant() / three_power->constant();
    double b = one_power->constant() / three_power->constant();
    double c = constant->constant() / three_power->constant();

    double p = b - pow(a, 2) / 3;
    double q = 2 * pow(a, 3) / 27 - a * b / 3 + c;
    double delta = pow(q, 2) / 4 + pow(p, 3) / 27;

    return find_cubic_roots(delta, p, q, a);
}

Polynomial::PolynomialRoot Polynomial::find_cubic_roots(double delta, double p, double q, double a) const {
    PolynomialRoot result;
    double temp;
    // right now i just find Real answers not complexes
    if (delta > 0) {
        temp = pow((-1 * q / 2 + sqrt(delta)), 1.0 / 3) +
               pow((-1 * q / 2 - sqrt(delta)), 1.0 / 3) - a / 3;
        result.emplace_back(temp);
    } else if (delta == 0) {
        temp = pow(q / 2, 1.0 / 3) - a / 3;
        result.emplace_back(temp);
        temp = -2 * pow(q / 2, 1.0 / 3) - a / 3;
        result.emplace_back(temp);
    } else {
        double temp1 = 2.0 / sqrt(3) * sqrt(-1 * p);
        double temp2 = (1.0 / 3) * asin((3 * sqrt(3) * q / (2 * pow(-1 * p, 3.0 / 2))));
        temp = temp1 * sin(temp2) - a / 3;
        result.emplace_back(temp);
        temp = -1 * temp1 * sin(temp2 + M_PI / 3) - a / 3;
        result.emplace_back(temp);
        temp = temp1 * cos(temp2 + M_PI / 6) - a / 3;
        result.emplace_back(temp);
    }
    return result;
}

Polynomial::PolynomialRoot Polynomial::solve_by_newton_technique(double guess) const {
    Polynomial derivated = derivate(1);
    const char variable = find_variables_and_max_power().begin()->variable;
    long double previous_answer = LDBL_MIN_10_EXP, current_answer = guess;
    long double polynomial_answer, derivated_answer;
    while (!compare_with_precision(previous_answer, current_answer, 6)) {
        previous_answer = current_answer;
        polynomial_answer = this->set_value(std::make_pair(variable, previous_answer));
        derivated_answer = derivated.set_value(std::make_pair(variable, previous_answer));
        if (polynomial_answer == 0)
            break;
        else if (derivated_answer == 0) {
            // bug
            current_answer = create_random_number();
        } else{
            current_answer = previous_answer - (polynomial_answer / derivated_answer);
        }
    }

    return PolynomialRoot{static_cast<double>(current_answer)};
}

Polynomial Polynomial::derivate(uint64_t degree) const {
    // just derivate for single variables
    if (find_variables_and_max_power().size() > 1)
        throw std::invalid_argument("it can not calculate derivate of multi variable polynomials.");
    else {
        std::vector<Expression> expressions;
        double constant;
        Expression::Variable* temp;
        for (auto& expr: all_expressions) {
            temp = (Expression::Variable*) &expr.variables()[0];
            constant = expr.constant() *
                    caluculate_derivate_constant(expr.power() * temp->power, degree);
            expressions.emplace_back(constant, temp->variable, expr.power() * temp->power - degree);
        }
        return Polynomial(expressions);
    }
}

int64_t Polynomial::caluculate_derivate_constant(int64_t power, uint64_t degree) const {
    int64_t result = 1;
    while (degree > 0) {
        result *= power;
        --power;
        --degree;
    }
    return result;
}

long double Polynomial::set_value(const std::vector<std::pair<char, double>> &values) const {
    auto size = find_variables_and_max_power().size();
    if (size != values.size())
        throw std::invalid_argument(std::format("there should exist {} pair in values.", size));
    long double result = 0;
    for (auto & expr: all_expressions)
        result += expr.set_value(values);

    return result;
}

long double Polynomial::set_value(const std::pair<char, double> &value) const {
    auto size = find_variables_and_max_power().size();
    if (size > 1)
        throw std::invalid_argument(std::format("there should exist {} pair in values.", size));
    long double result = 0;
    for (auto & expr: all_expressions)
        result += expr.set_value(value);

    return result;
}





