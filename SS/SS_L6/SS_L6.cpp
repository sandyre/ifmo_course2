#include "stdafx.h"
#include <Windows.h>

#define VK_C 0x43
#define VK_D 0x44
HHOOK hhkLowLevelKybd;
HANDLE console;
CONSOLE_SCREEN_BUFFER_INFO info;
bool C_PRESSED = false;
bool D_PRESSED = false;
bool ALT_PRESSED = false;
bool SHIF_PRESSED = false;
LRESULT CALLBACK LowLevelKeyboardProc ( int nCode, WPARAM wParam, LPARAM lParam )
{
	KBDLLHOOKSTRUCT * stKey = (KBDLLHOOKSTRUCT *)lParam;
	bool ButtonPressed = !(stKey->flags & 0b10000000);

	switch (stKey->vkCode)
	{
		case VK_C:
			if (ButtonPressed) C_PRESSED = true;
			else C_PRESSED = false;
			break;
		case VK_D:
			if (ButtonPressed) D_PRESSED = true;
			else D_PRESSED = false;
			break;
		case VK_LSHIFT:
		case VK_RSHIFT:
			if (ButtonPressed) SHIF_PRESSED = true;
			else SHIF_PRESSED = false;
			break;
		case VK_LMENU:
		case VK_RMENU:
			if (ButtonPressed) ALT_PRESSED = true;
			else ALT_PRESSED = false;
			break;
	}
	
	if (SHIF_PRESSED && ALT_PRESSED && C_PRESSED)
	{
		SYSTEM_INFO siSysInfo;

		// Copy the hardware information to the SYSTEM_INFO structure. 
		GetSystemInfo ( &siSysInfo );

		printf ( "Hardware information: \n" );
		printf ( "  OEM ID: %u\n", siSysInfo.dwOemId );
		printf ( "  Number of processors: %u\n",
			siSysInfo.dwNumberOfProcessors );
		printf ( "  Page size: %u\n", siSysInfo.dwPageSize );
		printf ( "  Processor type: %u\n", siSysInfo.dwProcessorType );
		printf ( "  Minimum application address: %lx\n",
			siSysInfo.lpMinimumApplicationAddress );
		printf ( "  Maximum application address: %lx\n",
			siSysInfo.lpMaximumApplicationAddress );
		printf ( "  Active processor mask: %u\n",
			siSysInfo.dwActiveProcessorMask );
	}
	if (SHIF_PRESSED && ALT_PRESSED && D_PRESSED)
	{
		printf ( "Program exit." );
		exit ( 0 );
	}

	return CallNextHookEx ( hhkLowLevelKybd, nCode, wParam, lParam );
}

SERVICE_STATUS serviceStatus;
SERVICE_STATUS_HANDLE hStatus;
int main ( DWORD argc, LPTSTR argv[] )
{
	console = GetStdHandle ( STD_OUTPUT_HANDLE );
	GetConsoleScreenBufferInfo ( console, &info );
	// Install the low-level keyboard & mouse hooks
	hhkLowLevelKybd = SetWindowsHookEx ( WH_KEYBOARD_LL, LowLevelKeyboardProc, 0, 0 );

	// Keep this app running until we're told to stop
	MSG msg;
	while (!GetMessage ( &msg, NULL, NULL, NULL )) 
	{    //this while loop keeps the hook
		TranslateMessage ( &msg );
		DispatchMessage ( &msg );
	}

	UnhookWindowsHookEx ( hhkLowLevelKybd );
	SetConsoleTextAttribute ( console, info.wAttributes );
	CloseHandle ( console );
	return 0;
}