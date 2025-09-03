#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t s;

void *child(void *arg) {
    sem_wait(&s);
    printf("child\n");
    sem_post(&s);
    return NULL;
}

int main() {
    pthread_t p;
    printf("parent: begin\n");

    sem_init(&s, 0, 1);

    pthread_create(&p, NULL, child, NULL);

    sem_wait(&s);
    printf("parent: end\n");
    sem_post(&s);

    pthread_join(p, NULL);
    return 0;
}
