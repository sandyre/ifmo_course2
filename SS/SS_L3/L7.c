#include <stdio.h>
#include <math.h> 

#define EXPORT __attribute__((visibility("default")))

EXPORT
int Lab7_Asm()
{
     const char enter_start_x[] = "Enter start X: ";
     const char enter_end_x[] = "Enter end X: ";
     const char enter_delta_x[] = "Enter step: ";
     const char enter_precision[] = "Enter precision: ";
     const char output_format[] = "Current X: %lf Calculated: %lf N: %lf Internal function: %lf\n";
     const char scanf_format[] = "%lf";
     double x_start, x_end = 0;
     double delta_x = 0;
     double precision = 0;
     double series_sum = 0;

     double current_sum_element = 0;
     double current_factorial = 0;
     double current_top = 0;

     double current_n = 0;
     double current_x = 0;
     printf ( enter_start_x );
     scanf ( scanf_format, &x_start );
     printf ( enter_end_x );
     scanf ( scanf_format, &x_end );
     printf ( enter_delta_x );
     scanf ( scanf_format, &delta_x );
     printf ( enter_precision );
     scanf ( scanf_format, &precision );

     current_x = x_start;
    
     while ( current_x <= x_end )
     {
        current_top = 1;
        series_sum = 1;
        current_sum_element = current_x;
        current_n = 1;
        current_factorial = 1;
        do
        {
            current_top = current_top * current_x * current_x;
            current_factorial = current_factorial * ( current_n );
            current_factorial = current_factorial * ( current_n + 1 );
            current_sum_element = current_top / current_factorial;
            series_sum = series_sum + current_sum_element;
            ++current_n;
            ++current_n;
        } while ( current_sum_element > precision );

        printf ( output_format , current_x,
                series_sum, current_n ,cosh ( current_x ) );
        current_x += delta_x;
     }
    return 1;
}
