#pragma once
#include "includes.hpp"
#include "form_utils.hpp"

namespace utils
{
	int getPercents(int f, int p);
	int getCenter(int f, int l);
	bool isEven(int n);

	template<class for_FREE_SINGLE>
	void freeAndNULL(for_FREE_SINGLE * p)
	{
		{
			delete p;
			p = nullptr;

			return (void)0;
		}
	}

	template<class for_FREE_ARRAY>
	void freeAndNULL(for_FREE_ARRAY * p[])
	{
		{
			delete[] p;
			p = nullptr;

			return (void)0;
		}
	}
}