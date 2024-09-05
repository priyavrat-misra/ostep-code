// using fork(), pipe(), wait() and exec() for piping
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, argc < 2 ? "insufficient arguments\n" : "too many arguments\n");
        exit(EXIT_FAILURE);
    } else {
        int pipefd[2];
        if (pipe(pipefd) == -1) {
            fprintf(stderr, "pipe failed\n");
            exit(EXIT_FAILURE);
        }

        int cpid = fork();
        if (cpid < 0) {
            fprintf(stderr, "fork failed\n");
            exit(EXIT_FAILURE);
        } else if (cpid == 0) {  /* child reads from pipe */
            close(pipefd[1]);  /* close unused write end */
            char buf;
            while (read(pipefd[0], &buf, 1) > 0)
                write(STDOUT_FILENO, &buf, 1);

            write(STDOUT_FILENO, "\n", 1);
            close(pipefd[0]);
        } else {  /* parent writes argv[1] to pipe */
            close(pipefd[0]);  /* close unused read end */
            write(pipefd[1], argv[1], strlen(argv[1]));
            close(pipefd[1]);  /* reader will see EOF */
            wait(NULL);
        }
    }

    return EXIT_SUCCESS;
}
