#include <stdio.h>
#include <stdlib.h>
#include "common.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
	    fprintf(stderr, "usage: cpu <string>\n");
        return EXIT_FAILURE;
    }

    while (1) {
	    printf("%s\n", argv[1]);
	    Spin(1);
    }

    return EXIT_SUCCESS;
}
