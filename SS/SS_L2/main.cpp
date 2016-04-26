#include <iostream>
#include <vector>
#include <random>
#include <assert.h>
#include <sys/mman.h>
#include <sys/file.h>
using namespace std;
using namespace chrono;
using chrono::high_resolution_clock;

class BasePointer
{
public:
    BasePointer ( size_t _length, size_t _sector_size )
    {
        base_ptr = new char[_length];

        sector_size = _sector_size;
        memory_sectors.resize( _length / _sector_size );
        for ( auto i = memory_sectors.begin (); i != memory_sectors.end (); ++i )
        {
            *i = false;
        }
    }

    ~BasePointer ()
    {
        delete base_ptr;
    }

    char * malloc ( size_t length );

private:
    vector < bool > memory_sectors;

    size_t sector_size;
    char * base_ptr;
};

char * BasePointer::malloc ( size_t length )
{
    bool   memory_allocated = false;
    size_t memory_can_allocate = 0;
    size_t first_block, last_block = 0;
    for (auto i = 0; i < memory_sectors.size (); ++i)
    {
        if (memory_sectors[i] == false)
        {
            first_block = i;
            memory_can_allocate += sector_size;
        }

        for (auto j = i; j < memory_sectors.size (); ++j)
        {
            if ( memory_sectors[j] == false) memory_can_allocate += sector_size;
            if ( memory_can_allocate >= length)
            {
                memory_allocated = true;
                last_block = j - 1;
                break;
            }
        }

        if (memory_allocated)
        {
            for (auto i = first_block; i <= last_block; ++i)
            {
                memory_sectors[i] = true;
            }

            return (base_ptr + first_block * sector_size);
        }
    }
}

class FileMapper
{
public:
    FileMapper ( size_t i );
    ~FileMapper ();

    void*alloc ( size_t size );
    void free ( void *ptr, size_t size );

private:
    void MapMemoryToFile ();

    vector<bool> isAllocated;
    char* start;    // start of mapped memory
};

FileMapper::FileMapper ( size_t bytesAmount ) {
    isAllocated.insert ( isAllocated.begin (), bytesAmount, false );
    MapMemoryToFile ();
}
FileMapper::~FileMapper () {
    if (munmap ( start, isAllocated.size () ) == -1)
        perror ( "munmap fails" );
}

void FileMapper::MapMemoryToFile () {
    int fd = open ( "FileToMap.fmobj", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH );
    if (fd == -1)
        perror ( "File opening fails" );
    else
        ftruncate ( fd, isAllocated.size () ); // resize mapped file

    start = (char*)mmap ( 0, isAllocated.size (), PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0 );

    if (start == MAP_FAILED)
        perror ( "mmap fails" );
    close ( fd );
}

void* FileMapper::alloc ( size_t byteAmount ) {
    int currentByteCounter = 0;

    assert ( byteAmount > 0 );

    for (int i = 0; i < isAllocated.size (); ++i) {
        if (!isAllocated[i]) {
            currentByteCounter++;

            if (currentByteCounter == byteAmount) {
                for (int j = i - byteAmount + 1; j <= i; j++)
                    isAllocated[j] = true;

                return start + i - byteAmount + 1;
            }
        }
        else {
            currentByteCounter = 0;
        }
    }

    perror ( "Not enough memory" );
}


int main ( int argc, char *argv[] )
{
    const int m = 1000000;
    for (int i = 1; i <= 10; ++i)
    {
        random_device rd;
        mt19937 gen (rd ());
        uniform_int_distribution<> dis (1, m);

        vector<unsigned int> input;
        for ( int j = 0; j < i * 1000; ++j )
        {
            input.push_back (dis (gen));
        }

        // CLASSIC WAY
        high_resolution_clock::time_point classic_start = high_resolution_clock::now ();
        {
            unsigned int *data = new unsigned int[input.size ()];
            memcpy (data, input.data (), input.size () * sizeof (unsigned int));

            int *buckets = new int[m];

            for ( unsigned int j = 0; j < m; ++j )
                buckets[ j ] = 0;
            for ( unsigned int i = 0; i < input.size (); ++i )
                ++buckets[ data[ i ] ];
            for ( unsigned int i = 0, j = 0; j < m; ++j )
                for ( unsigned int k = buckets[ j ]; k > 0; --k )
                    data[ i++ ] = j;

            delete[] buckets;
            delete[] data;
        }
        high_resolution_clock::time_point classic_end = high_resolution_clock::now ();
        duration<double> classic_time_elapsed = duration_cast<duration<double>> (classic_end - classic_start);

        high_resolution_clock::time_point b_ptr_start = high_resolution_clock::now ();
        // BASE-POINTERS WAY.
        {
            BasePointer b_ptr (10000000, 10);
            unsigned int *data = ( unsigned int * ) b_ptr.malloc (sizeof (unsigned int) * input.size ());
            memcpy (data, input.data (), input.size () * sizeof (unsigned int));

            int *buckets = new int[m];

            for ( unsigned int j = 0; j < m; ++j )
                buckets[ j ] = 0;
            for ( unsigned int i = 0; i < input.size (); ++i )
                ++buckets[ data[ i ] ];
            for ( unsigned int i = 0, j = 0; j < m; ++j )
                for ( unsigned int k = buckets[ j ]; k > 0; --k )
                    data[ i++ ] = j;

            delete[] buckets;
        }
        high_resolution_clock::time_point b_ptr_end = high_resolution_clock::now ();
        duration<double> b_ptr_time_elapsed = duration_cast<duration<double>> (b_ptr_end - b_ptr_start);

        // FILEMAPPING WAY.
        high_resolution_clock::time_point fm_start = high_resolution_clock::now ();
        {
            FileMapper fm (10000000);
            unsigned int *data = ( unsigned int * ) fm.alloc (sizeof (unsigned int) * input.size ());
            memcpy (data, input.data (), input.size () * sizeof (unsigned int));

            int *buckets = new int[m];

            for ( unsigned int j = 0; j < m; ++j )
                buckets[ j ] = 0;
            for ( unsigned int i = 0; i < input.size (); ++i )
                ++buckets[ data[ i ] ];
            for ( unsigned int i = 0, j = 0; j < m; ++j )
                for ( unsigned int k = buckets[ j ]; k > 0; --k )
                    data[ i++ ] = j;

            delete[] buckets;
        }
        high_resolution_clock::time_point fm_end = high_resolution_clock::now ();
        duration<double> fm_time_elapsed = duration_cast<duration<double>> (fm_end - fm_start);

        // PRINTING RESULT.
        cout << "RESULTS \t" << "STANDART \t" << "BASE_PTR \t" << "FILEMAPPING" << endl;
        cout << "N = " << input.size () << "\t" << classic_time_elapsed.count () << "\t" <<
        b_ptr_time_elapsed.count () << "\t \t" << fm_time_elapsed.count () << endl;
    }
}