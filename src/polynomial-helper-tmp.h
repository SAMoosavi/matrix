#ifndef POLYNOMIAL_HELPER_TMP_H
#define POLYNOMIAL_HELPER_TMP_H

#include <random>

#include "polynomial-helper.h"

namespace polynomial_helper
{

template <Numberable Number>
constexpr Number round(Number number, uint8_t precision) noexcept
{
	const double precision_number = std::pow(10.0, precision);
	return static_cast<Number>(std::round(number * precision_number) / precision_number);
}

template <Integrable Int>
Int create_random_number(Int begin, Int end) noexcept
{
	if (begin == end)
	{
		begin -= 1;
		end += 1;
	}

	static std::random_device random;
	static std::mt19937 gen(random());

	std::uniform_int_distribution<Int> distribution(begin, end);

	return distribution(gen);
}

}		 // namespace polynomial_helper

#endif