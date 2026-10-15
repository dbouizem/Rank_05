#pragma once

#include "searchable_bag.hpp"

class set
{
private:
	searchable_bag *bag;

public:
	set(searchable_bag &src);
	set(const set &other);
	set& operator=(const set &other);
	~set();

	void insert(int value);
	void insert(int *array, int size);
	void print() const;
	void clear();

	bool has(int value) const;

	searchable_bag &get_bag();
	const searchable_bag &get_bag() const;
};
