    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <sys/wait.h>

    int main(int argc, char *argv[]) {
    pid_t pid;
    int status;

    if (argc < 2) {
    printf("Usage: %s command [args...]\n", argv[0]);
    return 1;
    }

    pid = fork();
    if (pid == -1) {
    	perror("fork");
    	return 1;
    } else if (pid == 0) {
    /* Child process */
    	execvp(argv[1], &argv[1]);
    	perror("execvp");
    	return 1;
    } else {
    /* Parent process */
    	wait(&status);
    	if (WIFEXITED(status)) {
    	printf("Exited with status %d\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
    	printf("Killed by signal %d\n", WTERMSIG(status));
    } else if (WIFSTOPPED(status)) {
    	printf("Stopped by signal %d\n", WSTOPSIG(status));
    } else if (WIFCONTINUED(status)) {
    	printf("Continued\n");
    }
    }

    return 0;
    }


