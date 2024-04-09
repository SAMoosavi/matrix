#include <stdexcept>
#include <cmath>
#include <format>
#include <algorithm>
#include "Polynomial.h"

// Internal_Monomial
int64_t Polynomial::Internal_Monomial::find_number(size_t &index, const std::string &variables) {
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

bool Polynomial::Internal_Monomial::is_similar_terms(const Internal_Monomial &expression) const {
    bool result = true;
    if (variables.size() != expression.variables.size())
        result = false;
    else {
        std::vector<int16_t> all_alphabets(26, -1);
        for (int16_t i = 0; i < variables.size(); ++i)
            all_alphabets[variables[i].variable - 'a'] = i;
        int16_t temp;
        for (const auto &var: expression.variables) {
            temp = all_alphabets[var.variable - 'a'];
            if ((temp == -1) || (variables[temp].variable != var.variable ||
                                 (variables[temp].power) != (var.power))) {
                result = false;
                break;
            }
        }
    }

    return result;
}


Polynomial::Internal_Monomial::Internal_Monomial(double constant, char variable, uint64_t power) :
        constant(constant) {
    if (constant != 0 && power != 0)
        variables.emplace_back(variable, power);
}

Polynomial::Internal_Monomial::Internal_Monomial(double constant, std::vector<Variable> variables) :
        constant(constant) {
    if (constant != 0)
        this->variables = std::move(variables);
}

Polynomial::Internal_Monomial::Internal_Monomial(double constant) :
        constant(constant) {}

Polynomial::Internal_Monomial::Internal_Monomial(const Polynomial::Internal_Monomial &another) : constant(another.constant) {
    variables = another.variables;
}

Polynomial::Internal_Monomial::Internal_Monomial(Polynomial::Internal_Monomial &&another) noexcept :
    constant(another.constant),
    variables(std::move(another.variables)) {}

Polynomial::Internal_Monomial &Polynomial::Internal_Monomial::operator+=(const Internal_Monomial &expression) {
    if (is_similar_terms(expression)) {
        constant += expression.constant;
        check_expression();
    } else
        throw std::invalid_argument("two expressions should have same variables and same powers.");

    return *this;
}

Polynomial::Internal_Monomial &Polynomial::Internal_Monomial::operator-=(const Internal_Monomial &expression) {
    if (is_similar_terms(expression)) {
        constant -= expression.constant;
        check_expression();
    } else
        throw std::invalid_argument("two expressions should have same variables and same powers.");
    return *this;
}

Polynomial::Internal_Monomial &Polynomial::Internal_Monomial::operator*=(const Internal_Monomial &expression) {
    constant *= expression.constant;
    std::vector<int16_t> alphas(26, -1);
    for (int16_t i = 0; i < variables.size(); ++i)
        alphas[variables[i].variable - 'a'] = i;

    for (const auto &var: expression.variables) {
        if (alphas[var.variable - 'a'] == -1)
            variables.emplace_back(var.variable, var.power);
        else
            variables[alphas[var.variable - 'a']].power += var.power;
    }
    check_expression();
    return *this;
}

Polynomial::Internal_Monomial &Polynomial::Internal_Monomial::operator/=(const Internal_Monomial &expression) {
    if (expression.get_constant() != 0) {
        constant /= expression.constant;
        std::vector<int16_t> alphas(26, -1);
        for (int16_t i = 0; i < variables.size(); ++i)
            alphas[variables[i].variable - 'a'] = i;
        for (const auto &var: expression.variables) {
            if (alphas[var.variable - 'a'] == -1)
                variables.emplace_back(var.variable, -1 * var.power);
            else
                variables[alphas[var.variable - 'a']].power -= var.power;
        }
        check_expression();
    }
    return *this;
}

void Polynomial::Internal_Monomial::check_expression() {
    if (constant == 0)
        variables.clear();
    else {
        size_t i = 0;
        while (i < variables.size()) {
            if (variables[i].power == 0) {
                std::swap(variables[i], variables.back());
                variables.pop_back();
            } else
                ++i;
        }
    }
}

long double Polynomial::Internal_Monomial::set_value(const std::vector<std::pair<char, double>> &values) const {
    if (variables.size() > values.size())
        throw std::invalid_argument(std::format("there should be {} at least argument.", variables.size()));
    std::vector<double> alphabets(26, INT64_MIN);
    for (const auto &pair: values)
        alphabets[pair.first - 'a'] = pair.second;

    long double result = 0;
    double temp;
    for (auto &var: variables) {
        temp = alphabets['a' + var.variable];
        if (temp == INT64_MIN)
            throw std::invalid_argument(std::format("not specified {} in values.", var.variable));
        result += powf64x(temp, var.power);
    }
    result *= constant;

    return result;
}

long double Polynomial::Internal_Monomial::set_value(const std::pair<char, double> &value) const {
    if (variables.size() > 1)
        throw std::invalid_argument(std::format("there should be {} at least argument.", variables.size()));

    long double result = 0;
    if (!variables.empty()) {
        for (auto &var: variables) {
            if (var.variable != value.first)
                throw std::invalid_argument(std::format("not specified {} in values.", var.variable));
            result += powf64x(value.second, var.power);
        }
        result *= constant;
    } else
        result = constant;

    return result;
}

// Polynomial
void Polynomial::delete_repeated_expressions(std::vector<Internal_Monomial> &expressions) {
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

Polynomial::PolynomialVariableMaxPower Polynomial::createvariables(const std::vector<uint64_t> &alphabets) {
    Polynomial::PolynomialVariableMaxPower result;
    for (size_t i = 0; i < alphabets.size(); ++i) {
        if (alphabets[i] != 0)
            result.emplace_back('a' + i, alphabets[i]);
    }
    return result;
}

int32_t Polynomial::create_random_number(const int32_t &max_value) {
    srand(time(0));
    return rand() % max_value;
}

bool Polynomial::Internal_Monomial::compare_expressions_by_power(const Polynomial::Internal_Monomial &first,
                                                          const Polynomial::Internal_Monomial &second) {
    int64_t power1 = 0, power2 = 0;
    for (const auto &var: first.get_variables())
        power1 += var.power;
    for (const auto &var: second.get_variables())
        power2 += var.power;
    return power1 > power2;
}

std::vector<Polynomial::Internal_Monomial> Polynomial::calculate_quotient(const long double &root) const {
    std::vector<Internal_Monomial> result = all_expressions;
    std::sort(result.begin(), result.end(), Internal_Monomial::compare_expressions_by_power);
    long double temp;
    for (size_t i = 0; i < result.size() - 1; ++i) {
        if (i == 0) {
            temp = result.begin()->get_constant();
            result.begin()->decrease_power();
        } else {
            temp = temp * root + result[i].get_constant();
            result[i].set_constant(temp);
            result[i].decrease_power();
        }
    }
    result.pop_back();

    return std::move(result);
}

Polynomial::Polynomial(double constant, const Polynomial &polynomial, const uint64_t &power) :
        all_expressions(polynomial.all_expressions) {
    if (constant != 0 || power != 0) {
        this->power_equal(power);
        Internal_Monomial temp(constant);
        if (constant != 1) {
            for (auto &expr: all_expressions)
                expr *= temp;
        }
    }
}

Polynomial::Polynomial(double constant, const char variable, uint64_t power) :
        all_expressions(std::vector<Polynomial::Internal_Monomial>{{constant, variable, power}}) {}

Polynomial::Polynomial(double constant) :
        all_expressions(std::vector<Internal_Monomial>{Internal_Monomial(constant)}) {}

Polynomial::Polynomial(const Polynomial &another) {
    all_expressions = another.all_expressions;
}

Polynomial::Polynomial(Polynomial &&another) noexcept :
        all_expressions(std::move(another.all_expressions)) {}

Polynomial::Polynomial(Polynomial::Internal_Monomial expression) :
        all_expressions(std::vector<Internal_Monomial>{std::move(expression)}) {};

Polynomial::Polynomial(std::vector<Internal_Monomial> expressions) :
        all_expressions(std::move(expressions)) {}

Polynomial::Polynomial(Polynomial::Monomial monomial) {
    if (monomial.constant != 0)
        all_expressions.emplace_back(monomial.constant, std::move(monomial.variables));
}

Polynomial::Polynomial(std::vector<Monomial> monomials) {
    for (auto &monomial: monomials) {
        if (monomial.constant != 0)
            all_expressions.emplace_back(monomial.constant, std::move(monomial.variables));
    }
}

Polynomial::Internal_Monomial *Polynomial::find_similar_expression(const Internal_Monomial &expression) const {
    Internal_Monomial *result = nullptr;
    for (auto &expr: all_expressions) {
        if (expr.is_similar_terms(expression)) {
            result = (Internal_Monomial *) &expr;
            break;
        }
    }

    return result;
}

Polynomial &Polynomial::operator+=(const Polynomial &another) {
    Internal_Monomial *temp;
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
    Internal_Monomial *temp;
    for (auto &expr: another.all_expressions) {
        temp = find_similar_expression(expr);
        if (temp)
            *temp -= expr;
        else {
            all_expressions.emplace_back(Internal_Monomial(-1) *= expr);
        }
    }

    return *this;
}

Polynomial &Polynomial::operator*=(const Polynomial &another) {
    Polynomial result = Polynomial(0);
    Internal_Monomial temp(0);
    for (const auto &expr: another.all_expressions) {
        for (const auto &temp_expr: all_expressions) {
            temp = temp_expr * expr;
            result += Polynomial(std::move(temp));
        }
    }
    *this = result;
    return *this;
}

Polynomial &Polynomial::operator/=(const Monomial &another) {
//    it is temporary
    Internal_Monomial temp(another.constant, another.variables);
    for (auto &temp_expr: all_expressions)
        temp_expr /= temp;
    return *this;
}

Polynomial &Polynomial::power_equal(const uint64_t &power) {
    Polynomial another = *this;
    size_t i = 1;
    while (i * 2 <= power) {
        *this *= *this;
        i *= 2;
    }
    while (i < power) {
        *this *= another;
        ++i;
    }

    if (power < 0) {
        for (auto &expr: all_expressions)
            expr.power_equal(-1);
    }
    return *this;
}


bool Polynomial::check_solve_validation(const Polynomial::PolynomialVariableMaxPower &variableMaxPower) const {
    bool result = false;
    if (variableMaxPower.empty()) {
        // need to test when it completed
        if (all_expressions.begin()->get_constant() == 0)
            throw std::runtime_error("this Polynomial has infinity answers.");
        else
            throw std::runtime_error("there is no answer.");
    } else if (variableMaxPower.size() > 1)
        throw std::runtime_error("there is no support to solving multi-variable polynomials.");
    else
        result = true;

    return result;
}

Polynomial::PolynomialRoot
Polynomial::solve(double guess, const uint16_t &max_iteration, const uint16_t &precision) const {
    PolynomialVariableMaxPower variableMaxPower = find_variables_and_max_power();
    PolynomialRoot roots;
    if (check_solve_validation(variableMaxPower)) {
        // it need to test that the polynomial save unique expressions
        if (variableMaxPower.begin()->power == 1)
            roots = solve_linear_equation(precision);
        else if (variableMaxPower.begin()->power == 2)
            roots = solve_quardatic_equation(precision);
        else    // does not answer when you have many same roots
            roots = solve_greater_equation(guess, max_iteration, precision);
    }
    return roots;
}

Polynomial::PolynomialVariableMaxPower Polynomial::find_variables_and_max_power() const {
    // check  when there is constant only
    PolynomialVariableMaxPower result;
    std::vector<uint64_t> alphabets(26, 0);
    for (const auto &expr: all_expressions) {
        if (expr.get_constant() != 0) {
            for (const auto &var: expr.get_variables()) {
                if (var.power > alphabets[var.variable - 'a'])
                    alphabets[var.variable - 'a'] = var.power;
            }
        }
    }

    result = createvariables(alphabets);

    return std::move(result);
}

Polynomial::Internal_Monomial *Polynomial::find_expression_by_power(uint64_t target_power) const {
    Internal_Monomial *result = nullptr;
    if (target_power == 0) {
        for (auto &expr: all_expressions) {
            if (expr.get_variables().empty() || (expr.get_variables().begin()->power == target_power)) {
                result = (Internal_Monomial *) &expr;
                break;
            }
        }
    } else {
        for (auto &expr: all_expressions) {
            if (!expr.get_variables().empty() && (expr.get_variables().begin()->power == target_power)) {
                result = (Internal_Monomial *) &expr;
                break;
            }
        }
    }
    return result;
}

Polynomial::PolynomialRoot Polynomial::solve_linear_equation(const uint16_t &precision) const {
    // expressions need to be simplified
    PolynomialRoot result(1);
    Internal_Monomial *constant = find_expression_by_power(0);
    Internal_Monomial *one_power = find_expression_by_power(1);

    result[0] = round(static_cast<long double>(-1 * constant->get_constant()) / one_power->get_constant(), precision);

    return result;
}

Polynomial::PolynomialRoot Polynomial::solve_quardatic_equation(const uint16_t &precision) const {
    PolynomialRoot result;
    Internal_Monomial *constant = find_expression_by_power(0);
    Internal_Monomial *one_power = find_expression_by_power(1);
    Internal_Monomial *two_power = find_expression_by_power(2);

    double delta = pow(one_power->get_constant(), 2) - 4 * two_power->get_constant() * constant->get_constant();

    if (delta >= 0) {
        result.emplace_back(
                round((static_cast<long double>(-1 * one_power->get_constant()) + sqrt(delta)) / 2 *
                      two_power->get_constant(), precision));
        result.emplace_back(
                round((static_cast<long double>(-1 * one_power->get_constant()) - sqrt(delta)) / 2 *
                      two_power->get_constant(), precision));
    }

    return result;
}

Polynomial::NewtonOutput
Polynomial::solve_by_newton_technique(double guess, const uint16_t &max_iteration, const uint16_t &precision) const {
    NewtonOutput result;
    Polynomial derivated = derivate(1);
    const char variable = find_variables_and_max_power().begin()->variable;
    long double previous_answer = LDBL_MIN_10_EXP, current_answer = guess;
    long double polynomial_answer, derivated_answer;
    uint16_t iteration = 0;
    while (!compare_with_precision(previous_answer, current_answer, precision) && iteration < max_iteration) {
        previous_answer = current_answer;
        polynomial_answer = set_value(std::make_pair(variable, previous_answer));
        derivated_answer = derivated.set_value(std::make_pair(variable, previous_answer));
        if (compare_with_precision(polynomial_answer, 0.0, precision))
            break;
        else if (compare_with_precision(derivated_answer, 0.0, precision / 2)) {
            // it could replace with 2 or three as precision. check this
            if (compare_with_precision(polynomial_answer, 0.0, precision / 2))
                result.is_repeated = true;
            else
                current_answer = create_random_number();
        } else {
            current_answer = previous_answer - (polynomial_answer / derivated_answer);
        }
        ++iteration;
    }
    if (compare_with_precision(set_value(std::make_pair(variable, current_answer)), 0.0, precision / 2))
        result.root = round(current_answer, precision);
    return std::move(result);
}

Polynomial Polynomial::derivate(uint64_t degree) const {
    // just derivate for single variables
    if (find_variables_and_max_power().size() > 1)
        throw std::invalid_argument("it can not calculate derivate of multi variable polynomials.");
    else {
        // need to check that a positive power can not be a negative power after derivation
        std::vector<Internal_Monomial> expressions;
        double constant;
        Variable *temp;
        for (auto &expr: all_expressions) {
            temp = (Variable *) &expr.get_variables()[0];
            if (temp != nullptr) {
                constant = expr.get_constant() *
                           calculate_constant_of_derivated(temp->power, degree);
                expressions.emplace_back(constant, temp->variable, temp->power - degree);
            }
        }
        return std::move(Polynomial(std::move(expressions)));
    }
}

int64_t Polynomial::calculate_constant_of_derivated(int64_t power, uint64_t degree) const {
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
    for (auto &expr: all_expressions)
        result += expr.set_value(values);

    return result;
}

long double Polynomial::set_value(const std::pair<char, double> &value) const {
    auto size = find_variables_and_max_power().size();
    if (size > 1)
        throw std::invalid_argument(std::format("there should exist {} pair in values.", size));
    long double result = 0;
    for (auto &expr: all_expressions)
        result += expr.set_value(value);

    return result;
}

Polynomial::PolynomialRoot Polynomial::solve_greater_equation(double guess, const uint16_t &max_iteration,
                                                              const uint16_t &precision) const {
    PolynomialRoot result;
    Polynomial temp(all_expressions);
    NewtonOutput newton_answer;
    while (temp.all_expressions.size() > 1) {
        newton_answer = temp.solve_by_newton_technique(guess, max_iteration, precision);
        if (newton_answer.root != LDBL_MAX)
            save_newton_answer(result, newton_answer, temp);
        else {
            auto fixed_point_result = temp.solve_by_fixed_point_technique(guess, max_iteration, precision);
            if (fixed_point_result != LDBL_MAX)
                save_fixed_point_answer(result, fixed_point_result, temp);
            else  // it may was wrong
                break;
        }
        guess = 0;
    }
    return result;
}

long double Polynomial::solve_by_fixed_point_technique(double guess,
                                                       const uint16_t &max_iteration,
                                                       const uint16_t &precision) const {
    long double result = LDBL_MAX;
    Polynomial g = create_g_function();
    const char variable = find_variables_and_max_power().begin()->variable;
    long double previous = guess - 1, current = guess;
    long double f_answer;
    uint16_t iteration = 0;
    while (!compare_with_precision(previous, current, precision) && iteration < max_iteration) {
        previous = current;
        f_answer = set_value(std::make_pair(variable, previous));
        if (compare_with_precision(f_answer, 0, precision))
            break;
        current = g.set_value(std::make_pair(variable, previous));
        ++iteration;
    }
    if (compare_with_precision(set_value(std::make_pair(variable, current)), 0.0, precision / 2))
        result = round(current, precision);
    return result;
}

const Polynomial::Internal_Monomial &Polynomial::find_expression(const std::vector<Internal_Monomial> &expressions,
                                                          const char &variable, const int64_t &power) {
    for (const auto &expr: expressions) {
        for (const auto &var: expr.get_variables()) {
            if (var.variable == variable) {
                if (power != INT64_MIN && var.power == power) {
                    return expr;
                }
            }
        }
    }
    return *expressions.end();
}

size_t Polynomial::find_index(const std::vector<Internal_Monomial> &expressions, const char &variable, const int64_t &power) {
    size_t result = 0;
    for (const auto &expr: expressions) {
        for (const auto &var: expr.get_variables()) {
            if (var.variable == variable) {
                if (power != INT64_MIN && var.power == power) {
                    return result;
                }
            }
        }
        ++result;
    }
    return UINT64_MAX;
}
