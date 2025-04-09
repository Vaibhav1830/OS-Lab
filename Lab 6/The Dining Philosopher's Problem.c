#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX 10

int total_philosophers;
int hungry_count;
int hungry_positions[MAX];

int left(int i) {
    return (i == 1) ? total_philosophers : i - 1;
}

int right(int i) {
    return (i == total_philosophers) ? 1 : i + 1;
}

int is_safe_to_eat(int pos, int eating[]) {
    return !eating[left(pos)] && !eating[right(pos)];
}

void one_can_eat_at_a_time() {
    int eating[MAX] = {0};

    for (int i = 0; i < hungry_count; i++) {
        int p = hungry_positions[i];
        printf("P %d is waiting\n", p);
    }

    for (int i = 0; i < hungry_count; i++) {
        int p = hungry_positions[i];
        eating[p] = 1;
        printf("P %d is granted to eat\n", p);
        sleep(1); // Simulate eating
        printf("P %d has finished eating\n", p);
        eating[p] = 0;
    }
}

void two_can_eat_at_a_time() {
    int eating[MAX] = {0};
    int i = 0;

    while (i < hungry_count) {
        int granted = 0;
        for (int j = i; j < hungry_count && granted < 2; j++) {
            int p = hungry_positions[j];
            if (is_safe_to_eat(p, eating)) {
                eating[p] = 1;
                printf("P %d is granted to eat\n", p);
                granted++;
                hungry_positions[j] = -1; // Mark as done
            }
        }

        for (int j = 0; j < hungry_count; j++) {
            if (hungry_positions[j] == -1) {
                printf("P %d has finished eating\n", j + 1);
                eating[j + 1] = 0;
                hungry_positions[j] = 0; // Reset
                i++;
            } else if (hungry_positions[j] != 0) {
                printf("P %d is waiting\n", hungry_positions[j]);
            }
        }
        sleep(1); // Simulate time between checks
    }
}

int main() {
    int choice;

    printf("Enter the total number of philosophers: ");
    scanf("%d", &total_philosophers);

    printf("How many are hungry: ");
    scanf("%d", &hungry_count);

    for (int i = 0; i < hungry_count; i++) {
        printf("Enter philosopher %d position (1 to %d): ", i + 1, total_philosophers);
        scanf("%d", &hungry_positions[i]);
    }

    do {
        printf("\n1. One can eat at a time\n");
        printf("2. Two can eat at a time\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Allow one philosopher to eat at any time\n");
                one_can_eat_at_a_time();
                break;
            case 2:
                printf("Allow two philosophers to eat at a time\n");
                two_can_eat_at_a_time();
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 3);

    return 0;
}
