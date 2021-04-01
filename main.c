#include <stdio.h>
#include "util/so_stdio.h"

int main() {
    printf("----------------\n");

    SO_FILE var;
    var.mods[1] = 3;
    printf("%d\n", var.mods[1]);


    return 0;
}