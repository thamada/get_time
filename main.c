#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include "get_time.h"

void sleep_in_usertime(double sec) {

    uint64_t nj  = (uint64_t)((double)(0x2000-0x330) * sec); // Intel i5-14600KF 5.3 GHz

    for(uint64_t i=0; i<0x10000ull; i++) {
        for(uint64_t j=0; j<nj; j++) {
            static double x = 0.1234;
            x = x * 1.0001;
            if (0 == i % 0x100000ull && 0 == j % 0x100000ull)
                if (x < 0.0) 
                    printf("%ld, %e\n", i, x);
        }
    }
}

void print(double t) {
    printf("t = %.8f sec\n", t);
}

int main() {

    double wait_sec = 1.00000000;
    double t = 0.;

    // measure the wallclock-time
    t = get_time_wctime();
    sleep_in_usertime(wait_sec);
    t = get_time_wctime() - t;
    print(t);

    // measure the wallclock-time
    t = get_time_wctime();
    usleep(wait_sec * 1000000.0); /* --- zero sec counts for usertime --- */
    t = get_time_wctime() - t;
    print(t);

    // measure the user-time
    t = get_time_utime();
    sleep_in_usertime(wait_sec);
    t = get_time_utime() - t;
    print(t);

    // measure the user-time
    t = get_time_utime();
    usleep(wait_sec * 1000000.0); /* --- zero sec counts for usertime --- */
    t = get_time_utime() - t;
    print(t);

    return (EXIT_SUCCESS);
}
