#include <cinttypes>
#include <cstddef>

#include <algorithm>
#include <tuple>
#include <variant>
#include <vector>

#include "polynomial.h"
#include <gtest/gtest.h>

using namespace std;

using Coefficient = vector<int>;
using Root = vector<double>;
using SolveParameter = tuple<Coefficient, Root>;

class SharedCoefficients: public ::testing::Test {
protected:
	Coefficient coefficients1;
	Coefficient coefficients2;
	Polynomial<int> expected_result;

	virtual inline void CreateExpectedResult() = 0;

	void SetUp() override
	{
		coefficients1 = Coefficient{-1, 1};
		coefficients2 = Coefficient{1, -4, 6, -4, 1};
		CreateExpectedResult();
	}
};

class SharedCoefficientAndElement: public ::testing::Test {
protected:
	Coefficient coefficients;
	int element;
	Polynomial<int> expected_result;

	virtual inline void CreateExpectedResult() = 0;

	void SetUp() override
	{
		coefficients = Coefficient{-1, 1};
		element = 4;
		CreateExpectedResult();
	}
};

class PolynomialSumWithPolynomial: public SharedCoefficients {
protected:
	void CreateExpectedResult() override
	{
		Coefficient expected_coefficients = coefficients2;
		for (size_t i = 0; i < coefficients1.size(); i++)
			expected_coefficients[i] += coefficients1[i];
		expected_result = Polynomial(expected_coefficients);
	}
};

TEST_F(PolynomialSumWithPolynomial, WithoutEqual)
{
	const Polynomial<int> result = Polynomial(coefficients1) + Polynomial(coefficients2);
	EXPECT_EQ(expected_result, result);
}

TEST_F(PolynomialSumWithPolynomial, Equal)
{
	Polynomial<int> result = Polynomial(coefficients1);
	result += Polynomial(coefficients2);

	EXPECT_EQ(expected_result, result);
}

class PolynomialSumWithElement: public SharedCoefficientAndElement {
protected:
	void CreateExpectedResult() override
	{
		Coefficient expected_coefficients = coefficients;
		expected_coefficients[0] += element;
		expected_result = Polynomial(expected_coefficients);
	}
};

TEST_F(PolynomialSumWithElement, WithoutEqual)
{
	const Polynomial<int> result = Polynomial(coefficients) + element;
	EXPECT_EQ(Polynomial(expected_result), result);
}

TEST_F(PolynomialSumWithElement, Equal)
{
	Polynomial<int> polynomial = Polynomial(coefficients);
	polynomial += element;
	EXPECT_EQ(Polynomial(expected_result), polynomial);
}

class PolynomialSymmetry: public SharedCoefficients {
protected:
	void CreateExpectedResult() override
	{
		Coefficient expected_coefficients = coefficients1;
		for (auto &element: expected_coefficients)
			element = -1 * element;
		expected_result = Polynomial(expected_coefficients);
	}
};

TEST_F(PolynomialSymmetry, PolynomialSymmetry)
{
	const Polynomial<int> polynomial = Polynomial(coefficients1);
	EXPECT_EQ(-polynomial, Polynomial(expected_result));
}

class PolynomialSubmissionWithPolynomial: public SharedCoefficients {
protected:
	void CreateExpectedResult() override
	{
		Coefficient expected_coefficients(coefficients2.size());
		std::transform(coefficients2.begin(), coefficients2.end(), expected_coefficients.begin(),
		               [](auto element) { return element * -1; });
		for (size_t i = 0; i < coefficients1.size(); i++)
			expected_coefficients[i] += coefficients1[i];
		expected_result = Polynomial(expected_coefficients);
	}
};

TEST_F(PolynomialSubmissionWithPolynomial, WithoutEqual)
{
	const Polynomial<int> result = Polynomial(coefficients1) - Polynomial(coefficients2);
	EXPECT_EQ(Polynomial(expected_result), result);
}

TEST_F(PolynomialSubmissionWithPolynomial, PolynomialSubmissionEqualWithPolynomial)
{
	Polynomial<int> polynomial = Polynomial(coefficients1);
	polynomial -= Polynomial(coefficients2);

	EXPECT_EQ(Polynomial(expected_result), polynomial);
}

class PolynomialSubmissionWithElement: public SharedCoefficientAndElement {
protected:
	void CreateExpectedResult() override
	{
		Coefficient expected_coefficients = coefficients;
		expected_coefficients[0] -= element;
		expected_result = Polynomial(expected_coefficients);
	}
};

TEST_F(PolynomialSubmissionWithElement, WithoutEqual)
{
	const Polynomial<int> result = Polynomial(coefficients) - element;
	EXPECT_EQ(Polynomial(expected_result), result);
}


TEST_F(PolynomialSubmissionWithElement, Equal)
{
	Polynomial<int> polynomial = Polynomial(coefficients);
	polynomial -= element;
	EXPECT_EQ(Polynomial(expected_result), polynomial);
}

class PolynomialMultipleWithPolynomial: public SharedCoefficients {
protected:
	void CreateExpectedResult() override
	{
		Coefficient expected_coefficients(coefficients1.size() + coefficients2.size() - 1, 0);
		for (size_t i = 0; i < coefficients1.size(); i++) {
			for (size_t j = 0; j < coefficients2.size(); j++)
				expected_coefficients[i + j] += coefficients1[i] * coefficients2[j];
		}
		expected_result = Polynomial(expected_coefficients);
	}
};

TEST_F(PolynomialMultipleWithPolynomial, WithoutEqual)
{
	const Polynomial<int> result = Polynomial(coefficients1) * Polynomial(coefficients2);
	EXPECT_EQ(Polynomial(expected_result), result);
}

TEST_F(PolynomialMultipleWithPolynomial, Equal)
{
	Polynomial<int> result = Polynomial(coefficients1);
	result *= Polynomial(coefficients2);
	EXPECT_EQ(Polynomial(expected_result), result);
}

class PolynomialMultipleWithElement: public SharedCoefficientAndElement {
protected:
	void CreateExpectedResult() override
	{
		Coefficient expected_coefficients = coefficients;
		for (auto &coefficient: expected_coefficients)
			coefficient *= element;
		expected_result = Polynomial(expected_coefficients);
	}
};

TEST_F(PolynomialMultipleWithElement, PolynomialMultipleWithElement)
{
	const Polynomial<int> result = Polynomial(coefficients) * element;
	EXPECT_EQ(Polynomial(expected_result), result);
}


TEST_F(PolynomialMultipleWithElement, PolynomialMultipleEqualWithElement)
{
	Polynomial<int> result = Polynomial(coefficients);
	result *= element;
	EXPECT_EQ(Polynomial(expected_result), result);
}

class PowerCoefficients: public ::testing::Test {
protected:
	Coefficient base;
	Polynomial<int> fourth_power;
	uint8_t degree;

	void SetUp() override
	{
		base = Coefficient{-1, 1};
		fourth_power = Polynomial(Coefficient{1, -4, 6, -4, 1});
		degree = 4;
	}
};

TEST_F(PowerCoefficients, PolynomialPower)
{
	const Polynomial<int> result = Polynomial(base).power(degree);
	EXPECT_EQ(fourth_power, result);
}

TEST_F(PowerCoefficients, PolynomialPowerEqual)
{
	Polynomial<int> result(base);
	result.power_equal(degree);
	EXPECT_EQ(fourth_power, result);
}

class DerivativeCoefficients: public ::testing::Test {
protected:
	Coefficient base;
	Polynomial<int> derivative;

	void SetUp() override
	{
		base = Coefficient{-9, 0, 5, 0, -3, 0, 10};
		derivative = Polynomial(Coefficient{0, 10, 0, -12, 0, 60});
	}
};

TEST_F(DerivativeCoefficients, PolynomialDerivative)
{
	const Polynomial<int> result = Polynomial(base).derivative();
	EXPECT_EQ(derivative, result);
}

TEST_F(DerivativeCoefficients, PolynomialDerivativeEqual)
{
	Polynomial<int> result(base);
	result.derivative_equal();
	EXPECT_EQ(derivative, result);
}

class SetValueTest: public ::testing::Test {
protected:
	Polynomial<int32_t> polynomial;

	void SetUp() override
	{
		polynomial = Polynomial(Coefficient{-1, 3, -3, 1});
	}
};

TEST_F(SetValueTest, InputInt32)
{
	constexpr const int32_t input = 5;
	constexpr const int32_t output = 64;

	const int32_t result = polynomial.set_value(input);

	EXPECT_EQ(result, output);
}

TEST_F(SetValueTest, Double)
{
	constexpr const double input = 3.75;
	constexpr const double output = 20.796875;

	const double result = polynomial.set_value(input);

	EXPECT_EQ(result, output);
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

class CoefficientTest: public ::testing::Test {
protected:
	Coefficient coefficients;
	Polynomial<int32_t> polynomial;

	void SetUp() override
	{
		coefficients = Coefficient{-1, 3, -3, 1};
		polynomial = Polynomial(coefficients);
	}
};

TEST_F(CoefficientTest, BracketOperator)
{
	for (size_t i = 0; i < coefficients.size(); i++)
		EXPECT_EQ(coefficients[i], polynomial[i]);
}

TEST_F(CoefficientTest, At)
{
	for (size_t i = 0; i < coefficients.size(); i++)
		EXPECT_EQ(coefficients.at(i), polynomial.at(i));
}