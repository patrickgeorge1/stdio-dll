#include <stdio.h>
#include "util/so_stdio.h"

int main() {
    printf("blagh\n");

    SO_FILE *stream = NULL;
    int test = so_fileno(stream);
    printf("%d\n", test);

    return 0;
}