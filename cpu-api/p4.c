// using fork(), wait() and exec() for redirection
#include <stdio.h>  // printf, fprintf, stderr
#include <stdlib.h>  // exit
#include <unistd.h>  // fork, exec*
#include <fcntl.h>  // open, close, STDOUT_FILENO, O_*
#include <sys/wait.h>  // wait

int main(int argc, char *argv[]) {
	int rc = fork();
	if (rc < 0) {
		fprintf(stderr, "fork failed\n");
		exit(EXIT_FAILURE);
	} else if (rc == 0) {
        // child: redirect standard output to a file
		close(STDOUT_FILENO);
		open("./p4.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
		char *myargs[] = {"wc", "p4.c", NULL};
		execvp(myargs[0], myargs);
	} else {
        // parent goes down this path (original process)
		wait(NULL);
		execlp("ls", "ls", "-al", NULL);
	}

	return EXIT_SUCCESS;
}
