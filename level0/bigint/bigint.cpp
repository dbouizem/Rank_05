#include "bigint.hpp"

bigint::bigint():digit("0")
{}

bigint::bigint(unsigned long n)
{
	std::ostringstream stream;

	stream << n;
	digit = stream.str();
}

bigint::bigint(bigint const& other):digit(other.digit)
{}

bigint::~bigint()
{}

bigint&	bigint::operator=(bigint const& other)
{
	if(this != &other)
		digit = other.digit;
	return *this;
}

std::ostream& operator<<(std::ostream& out, bigint const& n)
{
	out << n.digit;
	return out;
}

//--------------

bigint& bigint::operator+=(bigint const& other)
{
	int i = static_cast<int>(digit.size()) - 1;
	int j = static_cast<int>(other.digit.size()) - 1;
	int carry = 0;
	std::string result;

	while(i >= 0 || j >= 0 || carry != 0)
	{
		int left = 0;
		int right = 0;
		if (i >= 0)
			left = digit[i--] - '0';
		if (j >= 0)
			right = other.digit[j--] - '0';
		int sum = left + right + carry;
		result.push_back((sum % 10) + '0');
		carry = sum / 10;
	}
	std::reverse(result.begin(), result.end());//on untilsr le std::reverse()SNAS METTRE.RESULT
	digit = result;
	return *this;
}

bigint bigint::operator+(bigint const& other)const
{
	bigint result(*this);
	result += other;
	return result;
}

bigint& bigint::operator++()
{
	*this += bigint(1);// ATTENTION on fait pas DIGIT += 1 pas posible car le 1 est int et la on est dans les objet type bigint
	return *this;
}

bigint bigint::operator++(int)
{
	bigint old(*this);
	++(*this);
	return old;
}

//--------------

bool bigint::operator<(bigint const& other) const
{
	if (digit.size() != other.digit.size())
		return digit.size() < other.digit.size();
	return digit < other.digit;
}

bool bigint::operator>(bigint const& other) const
{
	return other < *this;
}

bool bigint::operator<=(bigint const& other) const
{
	return !(*this > other);
}

bool bigint::operator>=(bigint const& other) const
{
	return !(*this < other);
}

bool bigint::operator==(bigint const& other) const
{
	return digit == other.digit;
}

bool bigint::operator!=(bigint const& other) const
{
	return !(*this == other);
}

//--------------

bigint& bigint::operator<<=(bigint const& other)
{
	std::size_t	shift = 0;
	std::istringstream stream(other.digit);

	stream >> shift;
	if (digit != "0")// "0"
		digit.append(shift, '0');//'0'
	return *this;
}

bigint bigint::operator<<(bigint const& other) const
{
	bigint result(*this);
	result <<= other;
	return result;
}

bigint& bigint::operator>>=(bigint const& other)
{
	if (other >= bigint(static_cast<unsigned long>(digit.size())))
	{
		digit = "0";
		return *this;
	}
	std::size_t shift = 0;
	std::istringstream stream(other.digit);
	stream >> shift;
	digit.erase(digit.size() - shift);
	return *this;
}

bigint bigint::operator>>(bigint const& other) const
{
	bigint result(*this);
	result >>= other;
	return result;
}
