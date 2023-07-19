#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
int n = argc - 1;
int fd[2];
pipe(fd);
pid_t pid = fork();
if (pid == 0) {
for (int i = n / 2; i < n; i++) {
int x = atoi(argv[i + 1]);
printf("The area of the square with side %d is %d\n", x, x * x);
}
close(fd[0]);
close(fd[1]);
exit(0);
} else {
for (int i = 1; i <= n / 2; i++) {
int x = atoi(argv[i]);
printf("The area of the square with side %d is %d\n", x, x * x);
}
wait(NULL);
}
return 0;
}
