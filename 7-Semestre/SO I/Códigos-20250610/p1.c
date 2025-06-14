#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    printf("hello (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {
        // fork falhou
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // processo filho
        printf("child (pid:%d)\n", (int) getpid());
    } else {
        // processo pai
        printf("parent of %d (pid:%d)\n", rc, (int) getpid());
    }

    return 0;
}
