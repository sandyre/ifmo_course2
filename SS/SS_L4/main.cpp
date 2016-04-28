#include <iostream>
#include <fstream>
#include <random>
#include <unistd.h>
using namespace std;

// MAC OSX implementation. Probably not the best one, but it works.
void print_pd_info(pid_t process_pid)
{
    char buffer[256];
    sprintf(buffer, "FCOUNT=`lsof -p $%d | grep -v \" txt \" | wc -l`;echo \"PID: $%d $FCOUNT\"", process_pid, process_pid);
    system(buffer);
}

void insertionSort (vector<int> &data)
{
    int i, j, tmp;

    for ( i = 1; i < data.size(); i++ )
    {
        j = i;
        tmp     = data[i];
        while ( j > 0 && tmp < data[j - 1] )
        {
            data[j] = data[j - 1];
            j--;
        }
        data[j] = tmp;
    }
}

int main (int argc, char * argv[])
{
    enum Command
    {
        SORT = 1,
        SEARCH_FOR
    };
    enum SortType
    {
        INSERTION = 1,
        QUICK
    };

    int status;
    pid_t    current_pid;
    Command  exec_command;
    SortType exec_sort_type;
    string   filename;
    int32_t  search_target;

    auto start = chrono::high_resolution_clock::now();
    auto end   = chrono::high_resolution_clock::now();
    current_pid = getpid();

    cout << "Application started. Currently, its parent process." << endl;
    print_pd_info (current_pid);

    if(!strncmp(argv[1],"sort",4))
    {
        exec_command   = SORT;
        if(!strncmp(argv[2],"--insertion-sort", strlen("--insertion-sort")))
            exec_sort_type = INSERTION;
        else if(!strncmp(argv[2],"--quick-sort", strlen("--quick-sort")))
            exec_sort_type = QUICK;
        else
        {
            cerr << "Unsupported sorting format. Check docs. Aborting.\n";
            exit(0);
        }
        filename = argv[3];
    }
    else if(!strncmp(argv[1],"search_for", strlen("search_for")))
    {
        exec_command  = SEARCH_FOR;
        search_target = stoi(argv[2]);
        filename      = argv[3];
    }

    for ( auto i = 0; i < 3; ++i)
    {
        if(fork() == 0)
        {
            cout << "Application started. Currently, its child (forked) process." << endl;
            print_pd_info (getpid());
            switch ( exec_command )
            {
                case SORT:
                {
                    start = chrono::high_resolution_clock::now ();
                    ifstream input_file(filename);
                    vector<int> array_to_sort;
                    array_to_sort.reserve (10000); // reserve space for 10000 elements. perfomance feature.
                    while(!input_file.eof ())
                    {
                        int tmp = 0;
                        input_file >> tmp;
                        array_to_sort.push_back(tmp);
                    }
                    if ( exec_sort_type == INSERTION )
                    {
                        insertionSort (array_to_sort);
                    }
                    else if ( exec_sort_type == QUICK )
                    {
                        sort(array_to_sort.begin(), array_to_sort.end());
                    }

                    end = chrono::high_resolution_clock::now ();
                    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
                    std::cout << "Array sorted. Elapsed time: " << duration.count () << " ms." << endl;
                    break;
                }
                case SEARCH_FOR:
                {
                    start = chrono::high_resolution_clock::now ();
                    ifstream input_file(filename);
                    vector<int> array_to_search;
                    array_to_search.reserve (10000); // reserve space for 10000 elements. perfomance feature.
                    while(!input_file.eof ())
                    {
                        int tmp = 0;
                        input_file >> tmp;
                        array_to_search.push_back(tmp);
                    }

                    // We need to sort array first.
                    sort(array_to_search.begin(), array_to_search.end());

                    auto search_result = find (array_to_search.begin(), array_to_search.end(), search_target);
                    if ( search_result != array_to_search.end() )
                        cout << "Element found!" << endl;

                    end = chrono::high_resolution_clock::now ();
                    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
                    std::cout << "Array sorted and element searched. Elapsed time: " << duration.count () << " ms." << endl;
                    input_file.close();
                    break;
                }
            }

            exit(0);
        }
    }

    int processesExited = 0;
    while (processesExited++ < 3) {
        wait(&status);
        printf("Child exited\n");
    }
}