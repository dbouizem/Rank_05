#include "vect2.hpp"
#include <iostream>


int main()
{
	vect2 v1;
	vect2 v2(1, 2);
	vect2 const v3(v2); // constructure de copie
	vect2 v4 = v2; // constructure d'affectation

	std::cout << "v1: " << v1 << std::endl;
	//std::cout << "v1: " << "{" << v1[1] << ", " << v1[1] << "}" << std::endl;
	std::cout << "v2: " << v2 << std::endl;
	std::cout << "v3: " << v3 << std::endl;
	std::cout << "v4: " << v4 << std::endl;

	std::cout << "v4++ " << v4++ << std::endl;// postfixe operator++(int) return objet
	std::cout << "v4: " << v4 << std::endl;
	std::cout << "++v4 " << ++v4 << std::endl;// prefixe operator++() return Ref

	std::cout << "v4-- " << v4-- << std::endl;
	std::cout << "v4: " << v4 << std::endl;
	std::cout << "--v4 " << --v4 << std::endl;




}
