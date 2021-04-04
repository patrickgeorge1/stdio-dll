#include <stdio.h>
#include <string.h>
#include "util/so_stdio.h"

int main() {
        printf("--------------\n");

    SO_FILE * stream = so_fopen("fisier.in", "r");
    if (stream == NULL) printf("IS NULL\n");
    int test = so_fgetc(stream);
    printf("%d\n", test);
    so_fclose(stream);

    return 0;
}