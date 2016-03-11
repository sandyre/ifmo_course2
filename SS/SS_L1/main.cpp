#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <vector>
using namespace std;
using namespace chrono;
using chrono::high_resolution_clock;

/* START: COPY FUNCTIONS DECLARATIONS */
#include <Windows.h>
#include <stdio.h>
int copyfile_custom(string in, string out)
{
	const int buffer_size = 4096;
	char buffer[buffer_size];

	FILE *from, *to;
	from = fopen(in.c_str(), "rb");
	to = fopen(out.c_str(), "wb");

	if (from == NULL)
	{
		perror(in.c_str());
		return 1;
	}
	if (to == NULL)
	{
		perror(out.c_str());
		return 2;
	}

	size_t bytes_in, bytes_out;
	while (bytes_in = fread(buffer, 1, buffer_size, from) > 0)
	{
		bytes_out = fwrite(buffer, 1, bytes_in, to);

		if (bytes_out != bytes_in)
		{
			perror("Error writing to file.");
			return 3;
		}
	}

	fclose(from);
	fclose(to);
}

int copyfile_windows_custom(string in, string out)
{
	const int buffer_size = 4096;

	HANDLE hIn, hOut;
	DWORD nIn, nOut;
	CHAR buffer[buffer_size];

	hIn = CreateFile(std::wstring(in.begin(), in.end()).c_str(),
		GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hIn == INVALID_HANDLE_VALUE) 
	{
		printf("Unable to open input file. Error: %õ\n", GetLastError());
		return 2;
	}
	hOut = CreateFile(std::wstring(out.begin(), out.end()).c_str(), 
		GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hOut == INVALID_HANDLE_VALUE) 
	{
		printf("Unable to open output file. Error: %x\n", GetLastError());
		return 3;
	}

	while (ReadFile(hIn, buffer, buffer_size, &nIn, NULL) && nIn > 0)
	{
		WriteFile(hOut, buffer, nIn, &nOut, NULL);
		if (nIn != nOut)
		{
			printf("Error writing to file: %x\n", GetLastError());
			return 4;
		}
	}

	CloseHandle(hIn);
	CloseHandle(hOut);
}

int copyfile_windows_builtin(string in, string out)
{
	if (!CopyFile(std::wstring(in.begin(), in.end()).c_str(), 
		std::wstring(out.begin(), out.end()).c_str(), FALSE)) 
	{
		printf("Error executing function CopyFile: %x\n", GetLastError());
		return 1;
	}
	return 0;
}
/* END: COPY FUNCTIONS DECLARATIONS*/

struct Result
{
	string name;
	string surname;
	string discipline;
	double score = 0;
};

double calculateAVR(string in)
{
	vector<Result> results;
	ifstream input(in, ios_base::in);

	int results_counter = 0;
	double scores_sum = 0;

	while (!input.eof())
	{
		Result temp;
		input >> temp.name >> temp.surname >> temp.discipline >> temp.score;

		scores_sum += temp.score;
		++results_counter;
	}
	input.close();

	return (scores_sum) / results_counter;
}

int main(int argc, char* argv[])
{
	string copymode;
	bool run_full = false;
	bool calculate_AVR = false;
	bool help = false;

	for (int i = 0; i < argc; i++)
	{
		string arg = argv[i];
		if (arg == "-m") copymode = argv[i + 1];
		if (arg == "--all") run_full = true;
		if (arg == "--printAVR") calculate_AVR = true;
		if (arg == "--help") help = true;
	}

	if (help == true)
	{
		cout << endl;
		cout << "SYNOPSIS" << endl;
		cout << "\t copyfile --help" << endl;
		cout << "\t copyfile --all" << endl;
		cout << "\t copyfile -m [custom | windows_custom | windows_builtin] [--printAVR] source_file target_file" << endl;
		return 0;
	}

	if (run_full)
	{
		// FULL AND PRINT RESULTS
		string copy_mode = copymode;
		string first_path = argv[argc - 2];
		string second_path = argv[argc - 1];

		// CUSTOM SECTION
		high_resolution_clock::time_point start, end;
		
		start = high_resolution_clock::now();

		copyfile_custom(first_path, second_path);

		end = high_resolution_clock::now();
		duration<double> time_custom = duration_cast<duration<double>>(end - start);

		// WINDOWS CUSTOM SECTION
		start = high_resolution_clock::now();

		copyfile_windows_custom(first_path, second_path);

		end = high_resolution_clock::now();
		duration<double> time_windows_custom = duration_cast<duration<double>>(end - start);

		// WINDOWS BUILTIN SECTION
		start = high_resolution_clock::now();

		copyfile_windows_builtin(first_path, second_path);

		end = high_resolution_clock::now();
		duration<double> time_windows_builtin = duration_cast<duration<double>>(end - start);

		// Print results
		cout << endl;
		cout << "File in: " << first_path << endl;
		cout << "File out: " << second_path << endl;
		cout << "Custom copy resulted in:         \t" << time_custom.count() << endl;
		cout << "Windows custom copy resulted in: \t" << time_windows_custom.count() << endl;
		cout << "Windows builtin copy resulted in:\t" << time_windows_builtin.count() << endl;
		cout << endl;

		if (calculate_AVR == true)
		{
			cout << "Calculated average score: " << calculateAVR(first_path);
		}

		return 0;
	}

	if (!run_full && argc >= 4)
	{
		string copy_mode = copymode;
		string first_path = argv[argc-2];
		string second_path = argv[argc-1];

		if (copy_mode == "custom")
		{
			high_resolution_clock::time_point start = high_resolution_clock::now();

			copyfile_custom(first_path, second_path);

			high_resolution_clock::time_point end = high_resolution_clock::now();
			duration<double> time_elapsed = duration_cast<duration<double>>(end - start);

			cout << "Time elapsed: " << time_elapsed.count() << " seconds." << endl;
		}

		if (copy_mode == "windows_custom")
		{
			high_resolution_clock::time_point start = high_resolution_clock::now();

			copyfile_windows_custom(first_path, second_path);

			high_resolution_clock::time_point end = high_resolution_clock::now();
			duration<double> time_elapsed = duration_cast<duration<double>>(end - start);

			cout << "Time elapsed: " << time_elapsed.count() << " seconds." << endl;
		}

		if (copy_mode == "windows_builtin")
		{
			high_resolution_clock::time_point start = high_resolution_clock::now();

			copyfile_windows_builtin(first_path, second_path);

			high_resolution_clock::time_point end = high_resolution_clock::now();
			duration<double> time_elapsed = duration_cast<duration<double>>(end - start);

			cout << "Time elapsed: " << time_elapsed.count() << " seconds." << endl;
		}

		if (calculate_AVR == true)
		{
			cout << "Calculated average score: " << calculateAVR(first_path);
		}

		return 0;
	}

	else cout << "Wrong command syntax. Use copyfile --help for help.";
}
