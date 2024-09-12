// using dup2() for redirection
// usage: ./lw '>' p6.out | ./lw '<' p6.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, argc < 3 ? "insufficient arguments\n" : "too many arguments\n");
        exit(EXIT_FAILURE);
    }

    int cid = fork();
    if (cid < 0) {
        fprintf(stderr, "fork failed\n");
        exit(EXIT_FAILURE);
    } else if (cid == 0) {
        if (*argv[1] == '>') {
            int fd = open(argv[2], O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
            dup2(fd, STDOUT_FILENO);
            close(fd);
            execlp("ls", "ls", NULL);
        } else if (*argv[1] == '<') {
            int fd = open(argv[2], O_RDONLY, S_IRUSR);
            dup2(fd, STDIN_FILENO);
            close(fd);
            execlp("wc", "wc", NULL);
        } else {
            fprintf(stderr, "invalid redirection symbol\n");
            exit(EXIT_FAILURE);
        }
    }
    wait(NULL);
    return EXIT_SUCCESS;
}
