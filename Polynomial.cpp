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

Polynomial::Polynomial(std::vector<Expression> expression) {
    delete_repeated_expressions(expression);
    all_expressions = std::move(expression);
}

Polynomial::Polynomial(Expression expression):
    all_expressions(std::vector<Expression>{std::move(expression)})
{}

Expression *Polynomial::find_expression(const Expression &expression) const {
    Expression* result = nullptr;
    for (auto& expr: all_expressions) {
        if (expr.is_similar_terms(expression)) {
            result = (Expression*) &expr;
            break;
        }
    }

    return result;
}

Polynomial& Polynomial::operator+=(const Polynomial &another) {
    Expression* temp;
    for (auto& expr: another.all_expressions) {
        temp = find_expression(expr);
        if (temp)
            *temp += expr;
        else
            all_expressions.emplace_back(expr);
    }

    return *this;
}

Polynomial& Polynomial::operator-=(const Polynomial &another) {
    Expression* temp;
    for (auto& expr: another.all_expressions) {
        temp = find_expression(expr);
        if (temp)
            *temp -= expr;
        else{
            all_expressions.emplace_back(Expression(-1) *= expr);
        }
    }

    return *this;
}

Polynomial& Polynomial::operator*=(const Polynomial &another) {
    Polynomial temp = *this, first_stage = *this;
    for (const auto & expr: another.all_expressions) {
        for (auto & temp_expr: temp.all_expressions)
            temp_expr *= expr;
        *this += temp;
        temp = first_stage;
    }
    return *this;
}

Polynomial &Polynomial::operator/=(const Expression &another) {
    for (auto& expr: all_expressions)
        expr *= another;
    return *this;
}





