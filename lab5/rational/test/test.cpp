#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Rational/common_libs.h"
#include "../Rational/CRational.h"

TEST_CASE("Test functional of getter and setter")
{
	GIVEN("rational number without value")
	{
		CRational number;
		double numberInDoubleNotation = 0;

		THEN("numerator = 0 and denominator = 1")
		{
			REQUIRE(number.GetNumerator() == 0);
			REQUIRE(number.GetDenominator() == 1);
			REQUIRE(number.ToDouble() == numberInDoubleNotation);
		}
	}

	GIVEN("rational number with only numerator (1)")
	{
		CRational number(1);
		double numberInDoubleNotation = 1;

		THEN("numerator = 1 and denominator = 1")
		{
			REQUIRE(number.GetNumerator() == 1);
			REQUIRE(number.GetDenominator() == 1);
			REQUIRE(number.ToDouble() == numberInDoubleNotation);
		}
	}

	GIVEN("rational number (4/3)")
	{
		CRational number(4, 3);
		double numberInDoubleNotation = 4 / 3;

		THEN("numerator = 4 and denominator = 3")
		{
			REQUIRE(number.GetNumerator() == 4);
			REQUIRE(number.GetDenominator() == 3);
			REQUIRE(number.ToDouble() == numberInDoubleNotation);
		}
	}

	GIVEN("rational number (4/0)")
	{
		THEN("error, invalid params")
		{
			REQUIRE_THROWS(CRational(4, 0));
		}
	}

	GIVEN("rational number (-4/3)")
	{
		CRational number(-4, 3);
		double numberInDoubleNotation = -4 / 3;

		THEN("numerator = -4 and denominator = 3")
		{
			REQUIRE(number.GetNumerator() == -4);
			REQUIRE(number.GetDenominator() == 3);
			REQUIRE(number.ToDouble() == numberInDoubleNotation);
		}
	}

	GIVEN("rational number (4/-3)")
	{
		CRational number(4, -3);
		double numberInDoubleNotation = -4 / 3;

		THEN("numerator = -4 and denominator = 3")
		{
			REQUIRE(number.GetNumerator() == -4);
			REQUIRE(number.GetDenominator() == 3);
			REQUIRE(number.ToDouble() == numberInDoubleNotation);
		}
	}
}

TEST_CASE("Test functional of normalize")
{
	GIVEN("rational number (4/2)")
	{
		CRational number(4, 2);
		double numberInDoubleNotation = 2;

		THEN("normalize fraction is (2/1)")
		{
			REQUIRE(number.GetNumerator() == 2);
			REQUIRE(number.GetDenominator() == 1);
			REQUIRE(number.ToDouble() == numberInDoubleNotation);
		}
	}

	GIVEN("rational number (-4/2)")
	{
		CRational number(-4, 2);
		double numberInDoubleNotation = -2;

		THEN("normalize fraction is (-2/1)")
		{
			REQUIRE(number.GetNumerator() == -2);
			REQUIRE(number.GetDenominator() == 1);
			REQUIRE(number.ToDouble() == numberInDoubleNotation);
		}
	}

	GIVEN("rational number (13/11)")
	{
		CRational number(13, 11);
		double numberInDoubleNotation = 13 / 11;

		THEN("normalize fraction is (13/11)")
		{
			REQUIRE(number.GetNumerator() == 13);
			REQUIRE(number.GetDenominator() == 11);
			REQUIRE(number.ToDouble() == numberInDoubleNotation);
		}
	}
}

TEST_CASE("Test functional unary + and -")
{
	GIVEN("rational number (4/2)")
	{
		CRational number(4, 2);
		double numberInDoubleNotation = 2;

		THEN("fraction is (2/1) with unary +")
		{
			number = +number;
			REQUIRE(number.GetNumerator() == 2);
			REQUIRE(number.GetDenominator() == 1);
			REQUIRE(number.ToDouble() == numberInDoubleNotation);
		}

		THEN("fraction is (-2/1) with unary -")
		{
			number = -number;
			REQUIRE(number.GetNumerator() == -2);
			REQUIRE(number.GetDenominator() == 1);
			REQUIRE(number.ToDouble() == -numberInDoubleNotation);
		}
	}

	GIVEN("rational number (-4/2)")
	{
		CRational number(-4, 2);
		double numberInDoubleNotation = -2;

		THEN("fraction is (2/1) with unary -")
		{
			number = -number;
			REQUIRE(number.GetNumerator() == 2);
			REQUIRE(number.GetDenominator() == 1);
			REQUIRE(number.ToDouble() == -numberInDoubleNotation);
		}

		THEN("fraction is (-2/1) with unary +")
		{
			number = +number;
			REQUIRE(number.GetNumerator() == -2);
			REQUIRE(number.GetDenominator() == 1);
			REQUIRE(number.ToDouble() == numberInDoubleNotation);
		}
	}
}

TEST_CASE("Test functional input and output")
{
	GIVEN("rational number (4/2) in input")
	{
		std::istringstream input("4/2");
		std::ostringstream output;
		CRational number;
		double numberInDoubleNotation = 2;

		input >> number;

		THEN("fraction is (2/1)")
		{
			REQUIRE(number.GetNumerator() == 2);
			REQUIRE(number.GetDenominator() == 1);
			REQUIRE(number.ToDouble() == numberInDoubleNotation);

		}

		THEN("fraction (2/1) in output")
		{
			output << number;
			REQUIRE(output.str() == "2/1");

			REQUIRE(number.GetNumerator() == 2);
			REQUIRE(number.GetDenominator() == 1);
			REQUIRE(number.ToDouble() == numberInDoubleNotation);

		}
	}

	GIVEN("(4;2) in input")
	{
		std::istringstream input("4;2");
		std::ostringstream output;
		CRational number;
		double numberInDoubleNotation = 0;

		input >> number;

		THEN("fraction is (0/1) and input is not good")
		{
			REQUIRE(number.GetNumerator() == 0);
			REQUIRE(number.GetDenominator() == 1);
			REQUIRE(number.ToDouble() == numberInDoubleNotation);
			REQUIRE_FALSE(input.good());
		}
	}

	GIVEN("(4/0) in input")
	{
		std::istringstream input("4/0");
		std::ostringstream output;
		CRational number;

		THEN("exception")
		{
			REQUIRE_THROWS(input >> number);
		}
	}
}

TEST_CASE("Test functional binary + and - (with and without assign)")
{
	GIVEN("rational numbers (1/3) and (1/2)")
	{
		CRational number1(1, 3);
		CRational number2(1, 2);

		THEN("(1/3) + (1/2) = (5/6)")
		{
			double numberInDoubleNotation = 5 / 6;

			CRational resultNumber = number1 + number2;
			REQUIRE(resultNumber.GetNumerator() == 5);
			REQUIRE(resultNumber.GetDenominator() == 6);
			REQUIRE(resultNumber.ToDouble() == numberInDoubleNotation);
		}

		THEN("(1/3) - (1/2) = (-1/3)")
		{
			double numberInDoubleNotation = -1 / 6;

			CRational resultNumber = number1 - number2;
			REQUIRE(resultNumber.GetNumerator() == -1);
			REQUIRE(resultNumber.GetDenominator() == 6);
			REQUIRE(resultNumber.ToDouble() == numberInDoubleNotation);
		}

		THEN("(1/3) + (1/2) = (5/6) with assign")
		{
			double numberInDoubleNotation = 5 / 6;

			number1 += number2;
			REQUIRE(number1.GetNumerator() == 5);
			REQUIRE(number1.GetDenominator() == 6);
			REQUIRE(number1.ToDouble() == numberInDoubleNotation);
		}

		THEN("(1/3) - (1/2) = (-1/3) with assign")
		{
			double numberInDoubleNotation = -1 / 6;

			number1 -= number2;
			REQUIRE(number1.GetNumerator() == -1);
			REQUIRE(number1.GetDenominator() == 6);
			REQUIRE(number1.ToDouble() == numberInDoubleNotation);
		}
	}

	GIVEN("rational numbers (1/3) and (1/2)")
	{
		CRational a(3, 3);
		CRational b(2, 2);
		CRational c(3, 1);

		WHEN("(((a += b) += c) += c)")
		{
			(((a += b) += c) += c);

			THEN("a == 8")
			{
				REQUIRE(a == 8);
			}
		}
	}

	GIVEN("rational numbers (2/4) and (3/6)")
	{
		CRational number1(2, 4);
		CRational number2(3, 6);

		THEN("(2/4) + (3/6) = (1/1)")
		{
			double numberInDoubleNotation = 1;

			CRational resultNumber = number1 + number2;
			REQUIRE(resultNumber.GetNumerator() == 1);
			REQUIRE(resultNumber.GetDenominator() == 1);
			REQUIRE(resultNumber.ToDouble() == numberInDoubleNotation);
		}

		THEN("(2/4) - (3/6) = (0/1)")
		{
			double numberInDoubleNotation = 0;

			CRational resultNumber = number1 - number2;
			REQUIRE(resultNumber.GetNumerator() == 0);
			REQUIRE(resultNumber.GetDenominator() == 1);
			REQUIRE(resultNumber.ToDouble() == numberInDoubleNotation);
		}
	}

	GIVEN("rational numbers (2/4) and 2")
	{
		CRational number(2, 4);

		THEN("(2/4) + 2 = (5/2)")
		{
			double numberInDoubleNotation = 5 / 2;

			CRational resultNumber = number + 2;
			REQUIRE(resultNumber.GetNumerator() == 5);
			REQUIRE(resultNumber.GetDenominator() == 2);
			REQUIRE(resultNumber.ToDouble() == numberInDoubleNotation);
		}

		THEN("(2/4) - 2 = (-3/2)")
		{
			double numberInDoubleNotation = -3 / 2;

			CRational resultNumber = number - 2;
			REQUIRE(resultNumber.GetNumerator() == -3);
			REQUIRE(resultNumber.GetDenominator() == 2);
			REQUIRE(resultNumber.ToDouble() == numberInDoubleNotation);
		}
	}

	GIVEN("rational numbers 2 and (2/4)")
	{
		CRational number(2, 4);

		THEN("2 + (2/4) = (5/2)")
		{
			double numberInDoubleNotation = 5 / 2;

			CRational resultNumber = 2 + number;
			REQUIRE(resultNumber.GetNumerator() == 5);
			REQUIRE(resultNumber.GetDenominator() == 2);
			REQUIRE(resultNumber.ToDouble() == numberInDoubleNotation);
		}

		THEN("2 - (2/4) = (3/2)")
		{
			double numberInDoubleNotation = 3 / 2;

			CRational resultNumber = 2 - number;
			REQUIRE(resultNumber.GetNumerator() == 3);
			REQUIRE(resultNumber.GetDenominator() == 2);
			REQUIRE(resultNumber.ToDouble() == numberInDoubleNotation);
		}

		THEN("(2/4) + 2 = (5/2) with assign")
		{
			double numberInDoubleNotation = 5 / 2;

			number += 2;
			REQUIRE(number.GetNumerator() == 5);
			REQUIRE(number.GetDenominator() == 2);
			REQUIRE(number.ToDouble() == numberInDoubleNotation);
		}

		THEN("(2/4) - 2 = (-3/2) with assign")
		{
			double numberInDoubleNotation = -3 / 2;

			number -= 2;
			REQUIRE(number.GetNumerator() == -3);
			REQUIRE(number.GetDenominator() == 2);
			REQUIRE(number.ToDouble() == numberInDoubleNotation);
		}
	}
}

TEST_CASE("Test functional binary / and * (with and without assign)")
{
	GIVEN("rational numbers (1/3) and (1/2)")
	{
		CRational number1(1, 3);
		CRational number2(1, 2);

		THEN("(1/3) * (1/2) = (1/6)")
		{
			double numberInDoubleNotation = 1 / 6;

			CRational resultNumber = number1 * number2;
			REQUIRE(resultNumber.GetNumerator() == 1);
			REQUIRE(resultNumber.GetDenominator() == 6);
			REQUIRE(resultNumber.ToDouble() == numberInDoubleNotation);
		}

		THEN("(1/3) / (1/2) = (2/3)")
		{
			double numberInDoubleNotation = 2 / 3;

			CRational resultNumber = number1 / number2;
			REQUIRE(resultNumber.GetNumerator() == 2);
			REQUIRE(resultNumber.GetDenominator() == 3);
			REQUIRE(resultNumber.ToDouble() == numberInDoubleNotation);
		}

		THEN("(1/3) * (1/2) = (1/6) with assign")
		{
			double numberInDoubleNotation = 1 / 6;

			number1 *= number2;
			REQUIRE(number1.GetNumerator() == 1);
			REQUIRE(number1.GetDenominator() == 6);
			REQUIRE(number1.ToDouble() == numberInDoubleNotation);
		}

		THEN("(1/3) / (1/2) = (2/3) with assign")
		{
			double numberInDoubleNotation = 2 / 3;

			number1 /= number2;
			REQUIRE(number1.GetNumerator() == 2);
			REQUIRE(number1.GetDenominator() == 3);
			REQUIRE(number1.ToDouble() == numberInDoubleNotation);
		}
	}

	GIVEN("rational numbers (2/4) and (3/6)")
	{
		CRational number1(2, 4);
		CRational number2(3, 6);

		THEN("(2/4) * (3/6) = (1/4)")
		{
			double numberInDoubleNotation = 1 / 4;

			CRational resultNumber = number1 * number2;
			REQUIRE(resultNumber.GetNumerator() == 1);
			REQUIRE(resultNumber.GetDenominator() == 4);
			REQUIRE(resultNumber.ToDouble() == numberInDoubleNotation);
		}

		THEN("(2/4) / (3/6) = (1)")
		{
			double numberInDoubleNotation = 1;

			CRational resultNumber = number1 / number2;
			REQUIRE(resultNumber.GetNumerator() == 1);
			REQUIRE(resultNumber.GetDenominator() == 1);
			REQUIRE(resultNumber.ToDouble() == numberInDoubleNotation);
		}
	}

	GIVEN("rational numbers (2/4) and 2")
	{
		CRational number(2, 4);

		THEN("(2/4) * 2 = (1)")
		{
			double numberInDoubleNotation = 1;

			CRational resultNumber = number * 2;
			REQUIRE(resultNumber.GetNumerator() == 1);
			REQUIRE(resultNumber.GetDenominator() == 1);
			REQUIRE(resultNumber.ToDouble() == numberInDoubleNotation);
		}

		THEN("(2/4) / 2 = (1/4)")
		{
			double numberInDoubleNotation = 1 / 4;

			CRational resultNumber = number / 2;
			REQUIRE(resultNumber.GetNumerator() == 1);
			REQUIRE(resultNumber.GetDenominator() == 4);
			REQUIRE(resultNumber.ToDouble() == numberInDoubleNotation);
		}
	}

	GIVEN("rational numbers 2 and (2/4)")
	{
		CRational number(2, 4);

		THEN("2 * (2/4) = (1)")
		{
			double numberInDoubleNotation = 1;

			CRational resultNumber = 2 * number;
			REQUIRE(resultNumber.GetNumerator() == 1);
			REQUIRE(resultNumber.GetDenominator() == 1);
			REQUIRE(resultNumber.ToDouble() == numberInDoubleNotation);
		}

		THEN("2 / (2/4) = (4)")
		{
			double numberInDoubleNotation = 4;

			CRational resultNumber = 2 / number;
			REQUIRE(resultNumber.GetNumerator() == 4);
			REQUIRE(resultNumber.GetDenominator() == 1);
			REQUIRE(resultNumber.ToDouble() == numberInDoubleNotation);
		}

		THEN("(2/4) * 2 = (1) with assign")
		{
			double numberInDoubleNotation = 1;

			number *= 2;
			REQUIRE(number.GetNumerator() == 1);
			REQUIRE(number.GetDenominator() == 1);
			REQUIRE(number.ToDouble() == numberInDoubleNotation);
		}

		THEN("(2/4) / 2 = (1/4) with assign")
		{
			double numberInDoubleNotation = 1 / 4;

			number /= 2;
			REQUIRE(number.GetNumerator() == 1);
			REQUIRE(number.GetDenominator() == 4);
			REQUIRE(number.ToDouble() == numberInDoubleNotation);
		}
	}

	GIVEN("rational numbers (2/4) and 0")
	{
		CRational number(2, 4);

		THEN("(2/4) * 0 = (0)")
		{
			double numberInDoubleNotation = 0;

			CRational resultNumber = number * 0;
			REQUIRE(resultNumber.GetNumerator() == 0);
			REQUIRE(resultNumber.GetDenominator() == 1);
			REQUIRE(resultNumber.ToDouble() == numberInDoubleNotation);
		}

		THEN("(2/4) / 0 = exception: Error while dividing on 0")
		{
			REQUIRE_THROWS(number / 0);
		}
	}
}

TEST_CASE("Test functional == and !=")
{
	GIVEN("rational numbers (1/3) and (1/2)")
	{
		CRational number1(1, 3);
		CRational number2(1, 2);

		THEN("(1/3) != (1/2)")
		{
			REQUIRE(number1 != number2);
			REQUIRE_FALSE(number1 == number2);
		}
	}

	GIVEN("rational numbers (3/1) and (6/2)")
	{
		CRational number1(3, 1);
		CRational number2(6, 2);

		THEN("(3/1) == (6/2)")
		{
			REQUIRE(number1 == number2);
			REQUIRE_FALSE(number1 != number2);
		}
	}

	GIVEN("rational numbers (3/2) and (6/1)")
	{
		CRational number1(3, 2);

		THEN("(3/2) != (6)")
		{
			REQUIRE(number1 != 6);
			REQUIRE_FALSE(number1 == 6);
		}
	}
}

TEST_CASE("Test functional >, <, >=, <=")
{
	GIVEN("rational numbers (1/3) and (1/2)")
	{
		CRational number1(1, 3);
		CRational number2(1, 2);

		THEN("(1/3) < (1/2)")
		{
			REQUIRE(number1 < number2);
			REQUIRE(number1 <= number2);
			REQUIRE_FALSE(number1 > number2);
			REQUIRE_FALSE(number1 >= number2);
		}
	}

	GIVEN("rational numbers (2/3) and (1/2)")
	{
		CRational number1(2, 3);
		CRational number2(1, 2);

		THEN("(1/3) > (1/2)")
		{
			REQUIRE(number1 > number2);
			REQUIRE(number1 >= number2);
			REQUIRE_FALSE(number1 <= number2);
			REQUIRE_FALSE(number1 < number2);
		}
	}

	GIVEN("rational numbers (3) and (15/5)")
	{
		CRational number(15, 5);

		THEN("3 >= (15/5)")
		{
			REQUIRE(3 >= number);
			REQUIRE(3 == number);
			REQUIRE(3 <= number);
			REQUIRE_FALSE(3 > number);
			REQUIRE_FALSE(3 < number);
		}

		THEN("3 <= (15/5)")
		{
			REQUIRE(3 <= number);
			REQUIRE(3 == number);
			REQUIRE(3 >= number);
			REQUIRE_FALSE(3 > number);
			REQUIRE_FALSE(3 < number);
		}
	}

	GIVEN("rational numbers (28/14) and (7/12)")
	{
		CRational number1(28, 14);
		CRational number2(7, 12);

		THEN("(28/14) > (7/12)")
		{
			REQUIRE(number1 > number2);
			REQUIRE(number1 >= number2);
			REQUIRE_FALSE(number1 <= number2);
			REQUIRE_FALSE(number1 < number2);
		}
	}
}

TEST_CASE("Test functional get compound fraction")
{
	GIVEN("rational number (1/3)")
	{
		CRational number(1, 3);

		THEN("0 and (1/3) is compound fraction")
		{
			std::pair<int, CRational> compoundFraction = number.ToCompoundFraction();
			REQUIRE(compoundFraction.first == 0);
			REQUIRE(compoundFraction.second == number);
		}
	}

	GIVEN("rational number (-1/3)")
	{
		CRational number(-1, 3);

		THEN("0 and (-1/3) is compound fraction")
		{
			std::pair<int, CRational> compoundFraction = number.ToCompoundFraction();
			REQUIRE(compoundFraction.first == 0);
			REQUIRE(compoundFraction.second == number);
		}
	}

	GIVEN("rational number (8/3)")
	{
		CRational number(8, 3);

		THEN("2 and (2/3) is compound fraction")
		{
			std::pair<int, CRational> compoundFraction = number.ToCompoundFraction();
			REQUIRE(compoundFraction.first == 2);
			REQUIRE(compoundFraction.second == CRational(2, 3));
		}
	}

	GIVEN("rational number (-8/3)")
	{
		CRational number(-8, 3);

		THEN("-2 and (-2/3) is compound fraction")
		{
			std::pair<int, CRational> compoundFraction = number.ToCompoundFraction();
			REQUIRE(compoundFraction.first == -2);
			REQUIRE(compoundFraction.second == CRational(-2, 3));
		}
	}

	GIVEN("rational number (-9/3)")
	{
		CRational number(-9, 3);

		THEN("-3 and (-1/1) is compound fraction")
		{
			std::pair<int, CRational> compoundFraction = number.ToCompoundFraction();
			REQUIRE(compoundFraction.first == -3);
			REQUIRE(compoundFraction.second == 0);
		}
	}

	GIVEN("rational number (9/3)")
	{
		CRational number(9, 3);

		THEN("3 and (1/1) is compound fraction")
		{
			std::pair<int, CRational> compoundFraction = number.ToCompoundFraction();
			REQUIRE(compoundFraction.first == 3);
			REQUIRE(compoundFraction.second == 0);
		}
	}
}