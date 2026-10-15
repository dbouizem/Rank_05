#ifndef BIGINT_HPP
# define BIGINT_HPP

# include <string>
# include <ostream>
# include <sstream>
# include <algorithm>

class bigint
{
private:
	std::string digit;

public:
	bigint();
	bigint(unsigned long n);
	bigint(bigint const& other);
	~bigint();
	bigint& operator=(bigint const& other);
	// Output
	friend std::ostream& operator<<(std::ostream& out, bigint const& n);
	// += + ++v v++
	bigint& operator+=(bigint const& other);
	bigint operator+(bigint const& other) const;
	bigint& operator++();
	bigint operator++(int);
	// == !=
	bool operator==(bigint const& other) const;
	bool operator!=(bigint const& other) const;
	// > >= < <=
	bool operator>(bigint const& other) const;
	bool operator>=(bigint const& other) const;
	bool operator<(bigint const& other) const;
	bool operator<=(bigint const& other) const;
	// <<= <<
	bigint& operator<<=(bigint const& other);
	bigint operator<<(bigint const& other) const;
	// >>= >>
	bigint& operator>>=(bigint const& other);
	bigint operator>>(bigint const& other) const;
};

#endif
