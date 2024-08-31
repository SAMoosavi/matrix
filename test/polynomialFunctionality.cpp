#include <algorithm>
#include <functional>
#include <tuple>
#include <vector>

#include "polynomial.h"
#include <gtest/gtest.h>

using namespace std;

using Coefficient = vector<int>;
using Root = vector<double>;
using SolveParameter = tuple<Coefficient, Root>;

class PolynomialTest: public testing::TestWithParam<SolveParameter> {
};

TEST_P(PolynomialTest, PolynomialSecondDegree)
{
	const Coefficient coefficients = std::get<0>(GetParam());
	const Root expected_roots = std::get<1>(GetParam());

	const auto polynomial = Polynomial(coefficients);
	Root roots = polynomial.solve(100);
	std::sort(roots.begin(), roots.end());

	EXPECT_EQ(roots,expected_roots);
}

INSTANTIATE_TEST_SUITE_P(SolveParameters, PolynomialTest, testing::Values(
	make_tuple(vector<int>{2, -3, 1}, vector<double>{1, 2}),
	make_tuple(vector<int>{0, 2, -3, 1}, vector<double>{0, 1, 2}),
	make_tuple(vector<int>{0, -6, 11, -6, 1}, vector<double>{0, 1, 2, 3})
));