#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char** environ;

int main(int argc, char* argv[], char* envp[]) {
    if (argc < 2) {
        fprintf(stderr, "insufficient arguments\n");
        exit(EXIT_FAILURE);
    }
    
    char *newargv[] = {"/usr/bin/env", NULL};
    char *newenvp[] = {"A=a", "B=b", "C=c", NULL};
    switch (argv[1][0]) {
        case '1':
            execve(newargv[0], newargv, NULL);
            break;
        case '2':
            execve(newargv[0], newargv, envp);
            break;
        case '3':
            execve(newargv[0], newargv, newenvp);
            break;
        default:
            execve(newargv[0], newargv, NULL);
    }

    return EXIT_SUCCESS;
}
