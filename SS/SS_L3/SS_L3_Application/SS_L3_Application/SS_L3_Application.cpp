// SS_L3_Application.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

typedef float(*pFIRFunction)(float);

int main()
{
	HMODULE dll = LoadLibrary ( L"SS_L3_Library.dll" );

	std::cout << "DLL Loaded ... ";
	if (dll != NULL)
	{
		std::cout << "OK." << std::endl;
		pFIRFunction function = (pFIRFunction)GetProcAddress ( dll, "?FastInverseRoot@@YAMM@Z" );
		if (function != NULL)
		{
			float input_data = 0;
			float result = 0;
			std::cout << "Enter some value (float) to get FastInverseSquareRoot from: ";
			std::cin >> input_data;
			result = function ( input_data );
			std::cout << "The output is: " << result << std::endl;
		}
	}
	else
	{
		std::cout << "FAILED." << std::endl;
	}
	FreeLibrary ( dll );
	system ( "pause" );
	return 0;
}

