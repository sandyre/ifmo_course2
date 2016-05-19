#include <dlfcn.h>
#include "stdio.h"
#include "stdlib.h"
#include "L3.h"

int main ()
{
    void * lib_handle = dlopen("L3.dylib", RTLD_LOCAL|RTLD_LAZY);
    if ( lib_handle != 0 )
    {
        printf ( "Library loaded successfully.\n" );
    }
    else
    {
        printf("[%s] Unable to load library: %s\n", __FILE__, dlerror());
        exit(EXIT_FAILURE);
    }

    int ( * Lab7_Asm )(void) = dlsym ( lib_handle, "Lab7_Asm" );
    if ( Lab7_Asm == NULL )
    {
        printf ( "Error loading Lab7_Asm function." );
        exit(0);
    }

    printf ( "Invoking Lab7 (ASM).\n" );
    Lab7_Asm(); // Calling Lab7.
    printf ( "\n" );

    int ( * _Z4L2_Cv )(void) = dlsym ( lib_handle, "_Z4L2_Cv" );
    if ( _Z4L2_Cv == NULL )
    {
        printf ( "Error loading Lab7_Asm function." );
        exit(0);
    }


    printf ( "Invoking Lab2 (C).\n" );
    _Z4L2_Cv(); // Calling Lab2.
    printf ( "\n" );

    if ( !dlclose( lib_handle ) )
    {
        printf ( "Library closed successfully.\n" );
    }
}