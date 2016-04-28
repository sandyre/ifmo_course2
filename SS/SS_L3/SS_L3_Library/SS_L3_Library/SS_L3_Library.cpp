// SS_L3_Library.cpp: определяет экспортированные функции для приложения DLL.
//

#include "stdafx.h"
#include "SS_L3_Library.h"

SS_L3_LIBRARY_API float FastInverseRoot ( float number )
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y = number;
	i = *(long *)&y;                         
	i = 0x5f3759df - (i >> 1);
	y = *(float *)&i;
	y = y * (threehalfs - (x2 * y * y));

	return y;
}