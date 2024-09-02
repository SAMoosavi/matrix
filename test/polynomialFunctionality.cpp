#include <cstddef>

#include <algorithm>
#include <tuple>
#include <vector>

#include "polynomial.h"
#include <gtest/gtest.h>

using namespace std;

using Coefficient = vector<int>;
using Root = vector<double>;
using SolveParameter = tuple<Coefficient, Root>;

class BasicOperationsCoefficients: public ::testing::Test {
protected:
	Coefficient coefficients1;
	Coefficient coefficients2; /* its size must be greater than coefficients1 */
	int element;

	void SetUp() override
	{
		coefficients1 = Coefficient{2, -3, 1};
		coefficients2 = Coefficient{3, 2, -3, 1};
		element = 10;
	}
};

TEST_F(BasicOperationsCoefficients, PolynomialSumWithPolynomial)
{
	Coefficient expected_result = coefficients2;
	for (size_t i = 0; i < coefficients1.size(); i++)
		expected_result[i] += coefficients1[i];

	const Polynomial<int> result = Polynomial(coefficients1) + Polynomial(coefficients2);
	EXPECT_EQ(Polynomial(expected_result), result);
}

TEST_F(BasicOperationsCoefficients, PolynomialSumWithElement)
{
	Coefficient expected_result = coefficients1;
	expected_result[0] += element;

	const Polynomial<int> result = Polynomial(coefficients1) + element;
	EXPECT_EQ(Polynomial(expected_result), result);
}

TEST_F(BasicOperationsCoefficients, PolynomialSumEqualWithPolynomial)
{
	Coefficient expected_result = coefficients2;
	for (size_t i = 0; i < coefficients1.size(); i++)
		expected_result[i] += coefficients1[i];

	Polynomial<int> polynomial = Polynomial(coefficients1);
	polynomial += Polynomial(coefficients2);

	EXPECT_EQ(Polynomial(expected_result), polynomial);
}

TEST_F(BasicOperationsCoefficients, PolynomialSumEqualWithElement)
{
	Coefficient expected_result = coefficients1;
	expected_result[0] += element;

	Polynomial<int> polynomial = Polynomial(coefficients1);
	polynomial += element;
	EXPECT_EQ(Polynomial(expected_result), polynomial);
}

TEST_F(BasicOperationsCoefficients, PolynomialSymmetry)
{
	Coefficient expected_result = coefficients1;
	for (auto &element: expected_result)
		element = -1 * element;

	const Polynomial<int> polynomial = Polynomial(coefficients1);
	EXPECT_EQ(-polynomial, Polynomial(expected_result));
}

TEST_F(BasicOperationsCoefficients, PolynomialSubmissionWithPolynomial)
{
	Coefficient expected_result(coefficients2.size());
	std::transform(coefficients2.begin(), coefficients2.end(), expected_result.begin(),
	               [](auto element) { return element * -1; });
	for (size_t i = 0; i < coefficients1.size(); i++)
		expected_result[i] += coefficients1[i];

	const Polynomial<int> result = Polynomial(coefficients1) - Polynomial(coefficients2);
	EXPECT_EQ(Polynomial(expected_result), result);
}

TEST_F(BasicOperationsCoefficients, PolynomialSubmissionWithElement)
{
	Coefficient expected_result = coefficients1;
	expected_result[0] -= element;

	const Polynomial<int> result = Polynomial(coefficients1) - element;
	EXPECT_EQ(Polynomial(expected_result), result);
}

TEST_F(BasicOperationsCoefficients, PolynomialSubmissionEqualWithPolynomial)
{
	Coefficient expected_result(coefficients2.size());
	std::transform(coefficients2.begin(), coefficients2.end(), expected_result.begin(),
	               [](auto element) { return element * -1; });
	for (size_t i = 0; i < coefficients1.size(); i++)
		expected_result[i] += coefficients1[i];


	Polynomial<int> polynomial = Polynomial(coefficients1);
	polynomial -= Polynomial(coefficients2);

	EXPECT_EQ(Polynomial(expected_result), polynomial);
}

TEST_F(BasicOperationsCoefficients, PolynomialSubmissionEqualWithElement)
{
	Coefficient expected_result = coefficients1;
	expected_result[0] -= element;

	Polynomial<int> polynomial = Polynomial(coefficients1);
	polynomial -= element;
	EXPECT_EQ(Polynomial(expected_result), polynomial);
}

TEST_F(BasicOperationsCoefficients, PolynomialMultipleWithPolynomial)
{
	Coefficient expected_result(coefficients1.size() + coefficients2.size() - 1, 0);
	for (size_t i = 0; i < coefficients1.size(); i++) {
		for (size_t j = 0; j < coefficients2.size(); j++)
			expected_result[i + j] += coefficients1[i] * coefficients2[j];
	}

	const Polynomial<int> result = Polynomial(coefficients1) * Polynomial(coefficients2);
	EXPECT_EQ(Polynomial(expected_result), result);
}

TEST_F(BasicOperationsCoefficients, PolynomialMultipleWithElement)
{
	Coefficient expected_result = coefficients1;
	for (auto &coefficient: expected_result)
		coefficient *= element;

	const Polynomial<int> result = Polynomial(coefficients1) * element;
	EXPECT_EQ(Polynomial(expected_result), result);
}

TEST_F(BasicOperationsCoefficients, PolynomialMultipleEqualWithPolynomial)
{
	Coefficient expected_result(coefficients1.size() + coefficients2.size() - 1, 0);
	for (size_t i = 0; i < coefficients1.size(); i++) {
		for (size_t j = 0; j < coefficients2.size(); j++)
			expected_result[i + j] += coefficients1[i] * coefficients2[j];
	}

	Polynomial<int> result = Polynomial(coefficients1);
	result *= Polynomial(coefficients2);
	EXPECT_EQ(Polynomial(expected_result), result);
}

TEST_F(BasicOperationsCoefficients, PolynomialMultipleEqualWithElement)
{
	Coefficient expected_result = coefficients1;
	for (auto &coefficient: expected_result)
		coefficient *= element;

	Polynomial<int> result = Polynomial(coefficients1);
	result *= element;
	EXPECT_EQ(Polynomial(expected_result), result);
}

class PowerCoefficients: public ::testing::Test {
protected:
	Coefficient base;
	Coefficient fourth_power;
	uint8_t degree;

	void SetUp() override
	{
		base = Coefficient{-1, 1};
		fourth_power = Coefficient{1, -4, 6, -4, 1};
		degree = 4;
	}
};

TEST_F(PowerCoefficients, PolynomialPower)
{
	const Polynomial<int> result = Polynomial(base).power(degree);
	EXPECT_EQ(Polynomial(fourth_power), result);
}

TEST_F(PowerCoefficients, PolynomialPowerEqual)
{
	Polynomial<int> result(base);
	result.power_equal(degree);
	EXPECT_EQ(Polynomial(fourth_power), result);
}

class PolynomialTest: public testing::TestWithParam<SolveParameter> {};

TEST_P(PolynomialTest, PolynomialSolveTest)
{
	const Coefficient coefficients = std::get<0>(GetParam());
	const Root expected_roots = std::get<1>(GetParam());

	const Polynomial<int> polynomial = Polynomial(coefficients);
	Root roots = polynomial.solve(100);
	std::sort(roots.begin(), roots.end());

	EXPECT_EQ(roots, expected_roots);
}

INSTANTIATE_TEST_SUITE_P(SolveParameters, PolynomialTest,
                         testing::Values(make_tuple(vector<int>{2, -3, 1}, vector<double>{1, 2}),
                                         make_tuple(vector<int>{0, 2, -3, 1}, vector<double>{0, 1, 2}),
                                         make_tuple(vector<int>{0, -6, 11, -6, 1}, vector<double>{0, 1, 2, 3})));