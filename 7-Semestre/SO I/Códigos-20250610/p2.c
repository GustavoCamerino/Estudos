#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    printf("hello (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {
        // fork falhou
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // processo filho
        printf("hello, I am child (pid:%d)\n", (int) getpid());
    } else {
        // processo pai
        int wc = wait(NULL);
        printf("hello, I am parent of %d (wc:%d) (pid:%d)\n",
               rc, wc, (int) getpid());
    }
    return 0;
}
