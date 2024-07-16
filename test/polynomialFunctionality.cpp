#include <vector>
#include <tuple>

#include "polynomial.h"
#include <gtest/gtest.h>

using namespace std;

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

using Coefficient = vector<int>;
using Root = vector<double>;
	using SolveParameter = tuple<bool, Coefficient, Root>;

	class PolynomialTest: public testing::TestWithParam<SolveParameter> {
};

TEST_P(PolynomialTest, PolynomialSecondDegree)
{
    const vector<int> coefficients = {2, -3, 1};
	Polynomial<int> polynomial(coefficients);

    if (std::get<0>(GetParam()))
    {
		const Root roots = polynomial.solve(100);
		const Root expected_roots = {1, 2};
		EXPECT_TRUE(is_vectors_equal(roots, expected_roots));
    } else
    {
		const Coefficient new_coefficients = std::get<1>(GetParam());
		const Root expected_roots = std::get<2>(GetParam());

		polynomial *= Polynomial(new_coefficients);
		const Root roots = polynomial.solve(100);
		EXPECT_TRUE(is_vectors_equal(roots, expected_roots));
    }
}

INSTANTIATE_TEST_SUITE_P(SolveParameters, PolynomialTest, testing::Values(
    make_tuple(true, vector<int>{2, -3, 1}, vector<double>{1, 2}),
    make_tuple(false, vector<int>{0, 1}, vector<double>{0, 1, 2}),
    make_tuple(false, vector<int>{0, -3, 1}, vector<double>{0, 1, 2, 3})
));