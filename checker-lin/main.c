#include <stdio.h>
#include <string.h>
#include "util/so_stdio.h"
#include "main.h"

int main() {
    // FILE * file = fopen("fisierO.in", "w");
    // for (int i = 0; i < buf_len; i++) {
	// 	int c = fputc((int)buf[i], file);
	// }
    // // so_fputc(65, file);
    // // so_fputc(66, file);

    // fclose(file);

    SO_FILE * file = so_fopen("fisierP.in", "w");
    for (int i = 0; i < buf_len; i++) {
		int c = so_fputc((int)(buf[i]), file);
	}
    // so_fputc(65, file);
    // so_fputc(66, file);

    so_fclose(file);

    return 0;
}