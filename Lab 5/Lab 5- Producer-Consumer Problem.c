#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex, full, empty;
int x = 0;

void wait(sem_t *s) { sem_wait(s); }
void signal_sem(sem_t *s) { sem_post(s); }

void *producer(void *arg) {
    wait(&empty);
    wait(&mutex);
    x++;
    printf("Producer has produced: Item %d\n", x);
    signal_sem(&mutex);
    signal_sem(&full);
    return NULL;
}

void *consumer(void *arg) {
    wait(&full);
    wait(&mutex);

    if (x > 0) {
        printf("Consumer has consumed: Item %d\n", x);
        x--;
    }

    signal_sem(&mutex);
    signal_sem(&empty);
    return NULL;
}

int main() {
    pthread_t prod, cons;
    int choice;

    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, 1);

    while (1) {
        printf("Enter 1.Producer 2.Consumer 3.Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            pthread_create(&prod, NULL, producer, NULL);
            pthread_join(prod, NULL);
        } else if (choice == 2) {
            pthread_create(&cons, NULL, consumer, NULL);
            pthread_join(cons, NULL);
        } else if (choice == 3) {
            break;
        } else {
            printf("Invalid choice!\n");
        }
    }

    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);

    return 0;
}
