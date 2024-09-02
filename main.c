#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_time.h"

int main() {

    double t = get_time();
    usleep(1234567.0);
    t = get_time() - t;
    printf("t = %.8f sec\n", t);

    return (EXIT_SUCCESS);
}
