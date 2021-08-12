#include "utils.hpp"

int utils::getPercents(int f, int p)
{
	return (p * (f / 100));
}

int utils::getCenter(int f, int l)
{
	return ((f - l) / 2);
}

bool utils::isEven(int n)
{
	return !(n % 2);
}