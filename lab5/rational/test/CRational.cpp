#include "CRational.h"
#include "common_libs.h"
#include <numeric>

CRational::CRational(int numerator, int denominator)
{
	if (denominator == 0)
	{
		throw std::invalid_argument("denominator can't be 0");
	}

	if (denominator < 0)
	{
		numerator = -numerator;
		denominator = -denominator;
	}

	m_numerator = numerator;
	m_denominator = denominator;

	Normalize();
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

double CRational::ToDouble() const
{
	return m_numerator / m_denominator;
}

void CRational::Normalize()
{
	int GCD = std::gcd(m_numerator, m_denominator);

	m_numerator /= GCD;
	m_denominator /= GCD;
}

std::pair<int, CRational> CRational::ToCompoundFraction() const
{
	int integerPart = m_numerator / m_denominator;

	return std::pair<int, CRational>(integerPart, CRational(m_numerator - integerPart * m_denominator, m_denominator));
}

CRational const CRational::operator+() const
{
	return *this;
}

CRational const CRational::operator-() const
{
	return CRational(-m_numerator, m_denominator);
}

CRational const operator+(const CRational& firstFraction, const CRational& secondFraction)
{
	int denumLCM = std::lcm(firstFraction.m_denominator, secondFraction.m_denominator);

	return CRational(firstFraction.m_numerator * (denumLCM / firstFraction.m_denominator) +
		(denumLCM / secondFraction.m_denominator) * secondFraction.m_numerator, denumLCM);
}

CRational const operator-(const CRational& firstFraction, const CRational& secondFraction)
{
	return firstFraction + (-secondFraction);
}

CRational& CRational::operator+=(const CRational& fraction)
{
	//упростить
	*this = CRational(this->m_numerator, this->m_denominator) + fraction;

	return *this;
}

CRational& CRational::operator-=(const CRational& fraction)
{
	*this = CRational(this->m_numerator, this->m_denominator) - fraction;

	return *this;
}

CRational& CRational::operator*=(const CRational& fraction)
{
	*this = CRational(this->m_numerator, this->m_denominator) * fraction;

	return *this;
}

CRational& CRational::operator/=(const CRational& fraction)
{
	*this = CRational(this->m_numerator, this->m_denominator) / fraction;

	return *this;
}

CRational const operator*(const CRational& firstFraction, const CRational& secondFraction)
{
	return CRational(firstFraction.m_numerator * secondFraction.m_numerator, firstFraction.m_denominator * secondFraction.m_denominator);
}

CRational const operator/(const CRational& firstFraction, const CRational& secondFraction)
{
	if (secondFraction.m_numerator == 0)
	{
		throw std::invalid_argument("Error while dividing on 0");
	}

	CRational invertedFraction(secondFraction.m_denominator, secondFraction.m_numerator);

	return firstFraction * invertedFraction;
}

bool operator==(const CRational& firstFraction, const CRational& secondFraction)
{
	return firstFraction.m_numerator == secondFraction.m_numerator && firstFraction.m_denominator == secondFraction.m_denominator;
}

bool operator!=(const CRational& firstFraction, const CRational& secondFraction)
{
	return !(firstFraction == secondFraction);
}

bool operator>(const CRational& firstFraction, const CRational& secondFraction)
{
	CRational resultFraction = firstFraction - secondFraction;

	return resultFraction.m_numerator > 0;
}

bool operator>=(const CRational& firstFraction, const CRational& secondFraction)
{
	CRational resultFraction = firstFraction - secondFraction;

	return resultFraction.m_numerator >= 0;
}

bool operator<(const CRational& firstFraction, const CRational& secondFraction)
{
	CRational resultFraction = firstFraction - secondFraction;

	return resultFraction.m_numerator < 0;
}

bool operator<=(const CRational& firstFraction, const CRational& secondFraction)
{
	CRational resultFraction = firstFraction - secondFraction;

	return resultFraction.m_numerator <= 0;
}

std::ostream& operator<<(std::ostream& oss, const CRational& fraction)
{
	oss << fraction.m_numerator << '/' << fraction.m_denominator;

	return oss;
}

std::istream& operator>>(std::istream& iss, CRational& fraction)
{
	char delimiter;
	int numerator;
	int denominator;

	if (!(iss >> numerator) || !(iss >> delimiter) || !(delimiter == '/') || !(iss >> denominator))
	{
		iss.setstate(std::ios_base::failbit);

		return iss;
	}

	if (denominator == 0)
	{
		throw std::invalid_argument("Denominator can't be 0");
	}

	fraction.m_numerator = numerator;
	fraction.m_denominator = denominator;

	fraction.Normalize();

	return iss;
}