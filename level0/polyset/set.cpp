# include "set.hpp"

set::set(searchable_bag &src) : bag(&src)
{}

set::set(const set &other) : bag(other.bag)
{}

set &set::operator=(const set &other)
{
	if (this != &other)
		bag = other.bag;
	return *this;
}

set::~set()
{}

void set::insert(int value)
{
	if (!bag->has(value))
		bag->insert(value);
}

void set::insert(int *array, int size)
{
	for (int i = 0; i < size; i++)
	{
		insert(array[i]);// la on utiliser le insert de set que on vient de faire pas celle de bag
	}
}

void set::print() const
{
	bag->print();
}

void set::clear()
{
	bag->clear();
}

bool set::has(int value) const
{
	return bag->has(value);// la on fait pas oublier le return car il return true or false
}

searchable_bag &set::get_bag()
{
	return *bag;
}

const searchable_bag &set::get_bag() const
{
	return *bag;
}
