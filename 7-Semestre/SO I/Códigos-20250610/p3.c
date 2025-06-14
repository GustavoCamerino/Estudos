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
        printf("hello, I am child (pid:%d)\n", (int) getpid());
        char *myargs[3];
        myargs[0] = strdup("wc");     // programa: word count
        myargs[1] = strdup("out.txt"); // argumento: arquivo
        myargs[2] = NULL;             // termina a lista de argumentos

        execvp(myargs[0], myargs);    // substitui o processo atual
        printf("this should not print out\n");
    } else {
        // processo pai
        int rc_wait = wait(NULL);
        printf("parent of %d (rc_wait:%d) (pid:%d)\n",rc, rc_wait, (int) getpid());
    }
    return 0;
}
