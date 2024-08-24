// calling fork(), wait() and exec()
#include <stdio.h>  // printf, fprintf, stderr
#include <stdlib.h>  // exit
#include <unistd.h>  // fork, exec*
#include <sys/wait.h>  // wait

int main(int argc, char *argv[]) {
	printf("(pid:%d) hello world\n", (int) getpid());
	
    int rc = fork();
	if (rc < 0) {
		fprintf(stderr, "fork failed\n");
		exit(EXIT_FAILURE);
	} else if (rc == 0) {
		printf("(pid:%d) hello, I am child\n", (int) getpid());
		char *myargs[] = {"wc", "p3.c", NULL};

		execvp(myargs[0], myargs); // or execvp("/usr/bin/wc", myargs);
		// v or l: vector or list (note: NULL has to be passed as well)
		// p: search path env (if not used, then have to add the full path)
		// e: to pass a different set of environment variables
		// e.g., execl("/usr/bin/wc", "wc", "p3.c", NULL);

		printf("this line won't print");
	} else {
		int rc_wait = wait(NULL);
		printf("(pid:%d) (rc_wait:%d) hello, I am parent of %d\n", (int) getpid(), rc_wait, rc);
	}

	return EXIT_SUCCESS;
}
