// SS_L5.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#define THREADS_COUNT 4
using namespace std::chrono;

CRITICAL_SECTION critSect;
HANDLE SyncMutex;
HANDLE SyncSemaphore;
HANDLE SyncEvent;
HANDLE hThreads[THREADS_COUNT];

int AskedValue = INT_MAX;
volatile int ThreadsFinishedSort = 0;
size_t ThreadsTimeStats[THREADS_COUNT];
std::vector < int > data_storage;

DWORD WINAPI Thread1_Work ( CONST LPVOID lpParam )
{
	size_t ThreadID = GetThreadId ( hThreads[0] );

	std::stringstream os;
	os << "Thread with ID: " << ThreadID << " started." << std::endl;
	std::cout << os.str ();
	os.str ( std::string () );
	os.clear ();

	// Mutex
	WaitForSingleObject ( SyncMutex, INFINITE ); // wait until SyncMutex is free
	SyncMutex = CreateMutex ( NULL, TRUE, NULL );

	os << "Thread with ID: " << ThreadID << " started sorting." << std::endl;
	std::cout << os.str ();
	os.str ( std::string () );
	os.clear ();

	auto start = high_resolution_clock::now ();
	// Insertion sort
	for (unsigned int uns = 1; uns < data_storage.size(); ++uns) 
	{
		int next = data_storage[uns];

		unsigned int idx;
		for (idx = uns; idx > 0 && data_storage[idx - 1] > next; --idx) 
		{
			data_storage[idx] = data_storage[idx - 1];
		}
		data_storage[idx] = next;
	}
	auto end = high_resolution_clock::now ();

	ReleaseMutex ( SyncMutex );

	os << "Thread with ID: " << ThreadID << " finished sorting." << std::endl;
	std::cout << os.str ();
	os.str ( std::string () );
	os.clear ();

	// Critical section.
	// Increment can be non-atomic operation, sync. required.
	EnterCriticalSection ( &critSect );
	++ThreadsFinishedSort;
	LeaveCriticalSection ( &critSect );

	WaitForSingleObject ( SyncSemaphore, INFINITE );
	bool ValueFound = std::binary_search ( data_storage.begin (), data_storage.end (), AskedValue );

	os << "Thread with ID: " << ThreadID << (ValueFound ? " found asked value." : " not found asked value.") << std::endl;
	std::cout << os.str ();
	os.str ( std::string () );
	os.clear ();

	ThreadsTimeStats[0] = duration_cast<milliseconds>(end - start).count ();

	return TRUE;
}

DWORD WINAPI Thread2_Work ( CONST LPVOID lpParam )
{
	size_t ThreadID = GetThreadId ( hThreads[1] );

	std::stringstream os;
	os << "Thread with ID: " << ThreadID << " started." << std::endl;
	std::cout << os.str ();
	os.str ( std::string () );
	os.clear ();

	// Mutex
	WaitForSingleObject ( SyncMutex, INFINITE ); // wait until SyncMutex is free
	SyncMutex = CreateMutex ( NULL, TRUE, NULL );

	os << "Thread with ID: " << ThreadID << " started sorting." << std::endl;
	std::cout << os.str ();
	os.str ( std::string () );
	os.clear ();

	auto start = high_resolution_clock::now ();
	// Bubble sort
	bool swapp = true;
	while (swapp) 
	{
		swapp = false;
		for (size_t i = 0; i < data_storage.size () - 1; ++i) 
		{
			if (data_storage[i] > data_storage[i + 1])
			{
				data_storage[i] += data_storage[i + 1];
				data_storage[i + 1] = data_storage[i] - data_storage[i + 1];
				data_storage[i] -= data_storage[i + 1];
				swapp = true;
			}
		}
	}
	auto end = high_resolution_clock::now ();

	ReleaseMutex ( SyncMutex );

	os << "Thread with ID: " << ThreadID << " finished sorting." << std::endl;
	std::cout << os.str ();
	os.str ( std::string () );
	os.clear ();

	// Critical section.
	// Increment can be non-atomic operation, sync. required.
	EnterCriticalSection ( &critSect );
	++ThreadsFinishedSort;
	LeaveCriticalSection ( &critSect );

	WaitForSingleObject ( SyncSemaphore, INFINITE );
	bool ValueFound = std::binary_search ( data_storage.begin (), data_storage.end (), AskedValue );

	os << "Thread with ID: " << ThreadID << (ValueFound ? " found asked value." : " not found asked value.") << std::endl;
	std::cout << os.str ();
	os.str ( std::string () );
	os.clear ();

	ThreadsTimeStats[1] = duration_cast<milliseconds>(end - start).count ();

	return TRUE;
}

DWORD WINAPI Thread3_Work ( CONST LPVOID lpParam )
{
	size_t ThreadID = GetThreadId ( hThreads[2] );

	std::stringstream os;
	os << "Thread with ID: " << ThreadID << " started." << std::endl;
	std::cout << os.str ();
	os.str ( std::string () );
	os.clear ();

	// Mutex
	WaitForSingleObject ( SyncMutex, INFINITE ); // wait until SyncMutex is free
	SyncMutex = CreateMutex ( NULL, TRUE, NULL );

	os << "Thread with ID: " << ThreadID << " started sorting." << std::endl;
	std::cout << os.str ();
	os.str ( std::string () );
	os.clear ();

	auto start = high_resolution_clock::now ();
	// STL quicksort
	std::sort ( data_storage.begin (), data_storage.end () );
	auto end = high_resolution_clock::now ();

	ReleaseMutex ( SyncMutex );

	os << "Thread with ID: " << ThreadID << " finished sorting." << std::endl;
	std::cout << os.str ();
	os.str ( std::string () );
	os.clear ();

	// Critical section.
	// Increment can be non-atomic operation, sync. required.
	EnterCriticalSection ( &critSect );
	++ThreadsFinishedSort;
	LeaveCriticalSection ( &critSect );

	WaitForSingleObject ( SyncSemaphore, INFINITE );
	bool ValueFound = std::binary_search ( data_storage.begin (), data_storage.end (), AskedValue );

	os << "Thread with ID: " << ThreadID << (ValueFound ? " found asked value." : " not found asked value.") << std::endl;
	std::cout << os.str ();
	os.str ( std::string () );
	os.clear ();

	ThreadsTimeStats[2] = duration_cast<milliseconds>(end - start).count ();

	return TRUE;
}

DWORD WINAPI Thread4_Work ( CONST LPVOID lpParam )
{
	size_t ThreadID = GetThreadId ( hThreads[2] );
	std::stringstream os;
	os << "Thread with ID: " << ThreadID << " started." << std::endl;
	std::cout << os.str ();
	os.str ( std::string () );
	os.clear ();

	WaitForSingleObject ( SyncEvent, INFINITE );

	os << "Thread with ID: " << ThreadID << " prints program execution results." << std::endl;
	std::cout << os.str ();
	os.str ( std::string () );
	os.clear ();

	for (size_t i = 0; i < THREADS_COUNT-1; ++i)
	{
		std::cout << "Thread #" << i + 1
			<< " finished sorting work in " << ThreadsTimeStats[i] << " milliseconds." << std::endl;
	}

	return TRUE;
}


int main(int argc, char * argv[])
{
	if (argc != 5)
	{
		std::cout << "Wrong usage pattern.\n \tSynopsys: -file %FILENAME% -search_for %VALUE" << std::endl;
		exit ( 10 );
	}

	std::string filename;
	for (size_t i = 0; i < argc; ++i)
	{
		if ( !strcmp ( argv[i], "-file" ) && argc > i )
		{
			filename = argv[i + 1];
		}
		if (!strcmp ( argv[i], "-search_for" ) && argc > i)
		{
			AskedValue = atoi ( argv[i] );
		}
	}

	InitializeCriticalSection ( &critSect );
	SyncSemaphore = CreateSemaphore ( NULL, THREADS_COUNT, THREADS_COUNT, NULL );
	SyncEvent = CreateEvent ( NULL, TRUE, FALSE, NULL );

	std::ifstream input ( filename );
	int tmp;
	while ( !input.eof () && input >> tmp )
	{
		data_storage.push_back ( tmp );
	}

	// Threads start, sync work is done inside of them.
	hThreads[0] = CreateThread ( NULL, 0, &Thread1_Work, NULL, 0, NULL );
	hThreads[1] = CreateThread ( NULL, 0, &Thread2_Work, NULL, 0, NULL );
	hThreads[2] = CreateThread ( NULL, 0, &Thread3_Work, NULL, 0, NULL );
	hThreads[3] = CreateThread ( NULL, 0, &Thread4_Work, NULL, 0, NULL );

	WaitForMultipleObjects ( THREADS_COUNT - 1, hThreads, TRUE, INFINITE );
	SetEvent ( SyncEvent );

	WaitForSingleObject ( hThreads[3], INFINITE ); // printstats thread.

	CloseHandle ( SyncSemaphore );
	CloseHandle ( SyncMutex );
	for (size_t i = 0; i < THREADS_COUNT; ++i)
	{
		CloseHandle ( hThreads[i] );
	}

	system ( "pause" );
}

