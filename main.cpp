#include <iostream>
#include <ranges>
#include <vector>

#include "Matrix.h"
#include "concept.h"
#include "Polynomial.h"

using namespace std;


template <Containerable Container, typename Element = typename Container::value_type>
	requires Multiplicationable<Element> && AssignSumable<Element>
constexpr Element multiplication(const Container& lhs, const Container& rhs)
{
	if (lhs.size() != rhs.size())
		throw invalid_argument("Cannot multiply spans of different sizes");
	Element result{};
	for (size_t i = 0; i < lhs.size(); ++i)
		result += lhs[i] * rhs[i];

	return result;
}

template <Containerable Container, typename Element = typename Container::value_type>
constexpr Element operator*(const Container& lhs, const Container& rhs)
{
	return multiplication(lhs, rhs);
}

template <Containerable Container, typename Element = typename Container::value_type>
	requires Sumable<Element>
constexpr Container sum(const Container& lhs, const Container& rhs)
{
	if (lhs.size() != rhs.size())
		throw invalid_argument("Cannot sum spans of different sizes");
	Container result(lhs.size());
	for (size_t index = 0; index < lhs.size(); ++index)
		result[index] = rhs[index] + lhs[index];
	return result;
}

template <Containerable Container, typename Element = typename Container::value_type>
constexpr Container operator+(const Container& lhs, const Container& rhs)
{
	return sum(lhs, rhs);
}


class W {
public:
	W()
		: num(0)
	{
	}

	W(int num)
		: num(num)
	{
	}

	W operator*(const W& other) const
	{
		return W{num * other.num};
	}

	W operator+(const W& other) const
	{
		return W{num + other.num};
	}

	W& operator+=(const W& other)
	{
		num += other.num;
		return *this;
	}

	W& operator*=(const W& other)
	{
		num *= other.num;
		return *this;
	}

	[[nodiscard]] int get() const
	{
		return num;
	}

private:
	int num;
};


template <typename T>
void print(const T& a)
{
	if constexpr (ranges::range<T>) {
		for (const auto& aa: a) {
			print(aa);
		}
		cout << endl;
	} else {
		cout << a.get() << " ";
	}
}

int main()
{
	vector<vector<W>> a = {
			{1, 2, 2, 2},
			{3, 2, 2, 4},
			{3, 2, 2, 4},
	};
	vector<vector<W>> b = {
			{1, 2, 2, 2},
			{3, 2, 2, 4},
			{3, 2, 2, 4},
			{3, 2, 2, 4},
	};
	Matrix<W> v1(a);
	Matrix<W> v2 = b;

	Matrix<W> po = v1 * v2;
	v1 *= v2;
	print(po.get_table());
	print(v1.get_table());

    Expression expr(12, 'x', 3);
    Expression expr1(-12, 'x', 3);

    std::cout << expr << '\n';
    expr*=Expression(13, "x^5");
    std::cout << expr << '\n';

    auto temp = expr * Expression(10);
    Polynomial polynomial(std::vector<Expression> {Expression(1, 'x', 1), Expression(-2)});
    Polynomial polynomial1(std::vector<Expression> {Expression(1, 'x', 1), Expression(-3)});
    Polynomial polynomial2(1, polynomial, 2);
    Polynomial polynomial3(1, polynomial1, 2);
    Polynomial polynomial4 = polynomial2 * polynomial3;
    std::cout << polynomial4 << '\n';

    auto result = polynomial4.solve(1000000);
    std::cout << polynomial4.set_value(make_pair('x', 2)) << '\n';
    for (const auto& ans: result) {
        std::cout << ans << '\t';
    }

	//    cout << po << endl;
	return 0;
}
