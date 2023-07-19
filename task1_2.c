#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void exit_handler(int sig) {
printf("Exit handler\n");
}

int main(int argc, char *argv[]) {
	pid_t pid;
int status;

signal(SIGINT, exit_handler);

	if ((pid = fork()) < 0) {
	perror("fork");
	exit(1);
} else if (pid == 0) { /* child process */
printf("Child process:\n");
for (int i = 0; i < argc; i++) {
printf("argv[%d]: %s\n", i, argv[i]);
}
exit(0);
} else { /* parent process */
printf("Parent process:\n");
for (int i = 0; i < argc; i++) {
	printf("argv[%d]: %s\n", i, argv[i]);
}
	wait(&status);
	if (WIFEXITED(status)) {
printf("Child exited with code %d\n", WEXITSTATUS(status));
	}
	}

return 0;
}
