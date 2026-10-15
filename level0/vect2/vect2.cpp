#include <iostream>
#include "vect2.hpp"

vect2::vect2():x(0), y(0)
{}

vect2::vect2(int x, int y):x(x), y(y)
{}

vect2::vect2(vect2 const& other):x(other.x), y(other.y)
{}

vect2::~vect2()
{}

vect2& vect2::operator=(vect2 const& other)
{
	if (this != &other)
	{
		x = other.x;
		y = other.y;
	}
	return (*this);
}

std::ostream& operator<<(std::ostream& out, vect2 const& vect)
{
	out << "{" << vect.x << ", " << vect.y << "}";// ATTENTION le rendu est vect.x pas vect[0] et vect.y PAS vect[1]
	return (out);
}

int& vect2::operator[](int index)
{
	if (index == 0)
		return (x);
	return (y);
}

int const& vect2::operator[](int index) const
{
	if (index == 0)
		return (x);
	return (y);
}

vect2& vect2::operator++()
{
	++x;
	++y;
	return (*this);
}

vect2 vect2::operator++(int)
{
	vect2 old(*this);
	++(*this);
	return (old);
}

vect2& vect2::operator--()
{
	--x;
	--y;
	return (*this);
}

vect2 vect2::operator--(int)
{
	vect2 old(*this);
	--(*this);
	return (old);
}

vect2& vect2::operator+=(vect2 const& other)
{
	x += other.x;
	y += other.y;
	return (*this);
}

vect2& vect2::operator-=(vect2 const& other)
{
	x -= other.x;
	y -= other.y;
	return (*this);
}

vect2& vect2::operator*=(int scalar)
{
	x *= scalar;
	y *= scalar;
	return (*this);
}

vect2 vect2::operator+(vect2 const& other)const
{
	return (vect2(x + other.x, y + other.y));
}

vect2 vect2::operator-(vect2 const& other)const
{
	return (vect2(x - other.x, y - other.y));
}

vect2 vect2::operator*(int scalar)const
{
	return (vect2(x * scalar, y * scalar));
}

vect2 operator*(int scalar, vect2 const& vect)
{
	return (vect * scalar);
}

vect2 vect2::operator-()const
{
	return ((*this) * -1);
}

bool vect2::operator==(vect2 const& other)const
{
	return (x == other.x && y == other.y);
}

bool vect2::operator!=(vect2 const& other)const
{
	return (!(*this == other));
}
