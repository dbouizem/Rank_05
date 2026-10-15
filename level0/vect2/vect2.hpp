#ifndef VECT2_HPP
#define VECT2_HPP

# include <iostream>

class vect2
{
private:
	int x;
	int y;

public:
// Canonic format
	vect2();
	vect2(int x, int y);
	vect2(vect2 const& other);
	~vect2();
	vect2& operator=(vect2 const& other);
// Output
	//friend std::ostream operator<<(std::ostream out, vect2 vect);// il return un Ref vers le out donc std::ostream& et il prend un Ref vers out donc std::ostream& et aussi un refconst vers le vect donc vect2 const& vect
	friend std::ostream& operator<<(std::ostream& out, vect2 const& vect);
// [] []const
	//vect2& operator[](int index);//il return un  Ref vers un int la valeur de index x ou y donc un int PAS un vect2
	//vect2 const& operator[](int index)const;// return un ref vers un int const&
	int& operator[](int index);
	int const& operator[](int index)const;
// ++v v++ --v v--
	vect2& operator++(); //++v
	vect2 operator++(int);//v++
	vect2& operator--();//--v
	vect2 operator--(int);//v--
// += -= *=
	vect2& operator+=(vect2 const& other);
	vect2& operator-=(vect2 const& other);
	vect2& operator*=(int scalar);
// + - v*int int*v -()
	vect2 operator+(vect2 const& other)const;
	vect2 operator-(vect2 const& other)const;
	vect2 operator*(int scalar)const;
	friend vect2 operator*(int scalar, vect2 const& vect);
	vect2 operator-()const;// const a la fin on change pas le objet
// == !=
	bool operator==(vect2 const& other)const;
	bool operator!=(vect2 const& other)const;
};

#endif
