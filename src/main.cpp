#include <iostream>
#include <ranges>
#include <vector>

#include "concept.h"
#include "matrix.h"
#include "polynomial.h"

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

	template <typename T>
	W operator*(const T& other) const
	{
		return W{num * other};
	}


	template <typename T>
	W operator+(const T& other) const
	{
		return W{num + other};
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

	W operator-() const
	{
		return W(num * -1);
	}

	[[nodiscard]] int get() const
	{
		return num;
	}

	bool operator==(const int& other) const
	{
		return num == other;
	}

	bool operator==(const W& other) const
	{
		return num == other.num;
	}

private:
	int num;
};
std::ostream& operator<<(ostream& os, const W& w)
{
	os << w.get() << ' ';
	return os;
}


template <typename T>
void print(const T& a)
{
	if constexpr (ranges::range<T>) {
		for (const auto& aa: a) {
			print(aa);
		}
		cout << endl;
	} else {
		cout << a << " ";
	}
}

template <typename T>
bool is_vectors_equal(const vector<T>& vec1, const vector<T>& vec2)
{
	if (vec1.size() != vec2.size())
		return false;
	for (const auto& iterator1: vec1) {
		bool is_found = false;
		for (const auto& iterator2: vec2) {
			if (Polynomial<T>::compare_with_precision(iterator1, iterator2, 6))
				is_found = true;
		}
		if (!is_found)
			return false;
	}
	return true;
}

int main()
{
	vector<vector<W>> a = {
			{1, 2, 2, 2},
			{3, 2, 2, 4},
			{3, 2, 2, 4},
	};
	Matrix<W> b = {
			{1, 2, 2, 2},
			{3, 2, 2, 4},
			{3, 2, 2, 4},
			{3, 2, 2, 4},
	};
	Matrix<W> v1(a);
	const Matrix<W>& v2 = b;

	// Matrix<W> po = v1 * v2;
	// v1 *= v2;
	// print(po.get_table());
	// print(v1.get_table());
	// Matrix<W> v3 = v2 * 10;
	// print(v3.get_table());
	// Matrix<int> v4(vector<vector<int>>({
	// 		{1, 2, 2, 2},
	// 		{3, 2, 2, 4},
	// 		{3, 2, 2, 4},
	// 		{3, 2, 2, 4},
	// }));
	// cout << v4.determinant() << endl;
	// Matrix<W> v5 = v2 + v4;
	// print(v5.get_table());
	// Matrix<W> v6 = v2 * v4;
	// print(v6.get_table());
	// Matrix<W> v7 = 10 * v2;
	// print(v7.get_table());

	using Coefficient = vector<int>;
	using Root = vector<double>;

	vector<int> temp = {0, 3, -4, 1};
	Polynomial<int> p(temp);

	// auto roots = p.solve();
	// for (auto& root: roots) {
	// 	cout << root << '\n';
	// }

	const vector<int> coefficients1 = {2, -3, 1};
	const vector<int> coefficients2 = {0, -3, 1};
	Polynomial<int> polynomial(coefficients1);

	Root roots = polynomial.solve(100);
	Root expected_roots = {1, 2};
	print(is_vectors_equal(expected_roots, roots));

	polynomial *= Polynomial(coefficients2);
	roots = polynomial.solve(100);
	print(is_vectors_equal(expected_roots, roots));


	return 0;
}
