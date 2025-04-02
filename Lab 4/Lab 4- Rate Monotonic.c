#include <stdio.h>
#define MAX_TASKS 10

typedef struct {
    int id;
    int execution;
    int period;
    int remaining_time;
    int next_arrival;
} task;

void sort_by_priority(task tasks[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (tasks[i].period > tasks[j].period) {
                task temp = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = temp;
            }
        }
    }
}

void rate_monotonic(task tasks[], int n) {
    int time = 0, completed = 0;

    while (completed < n) {
        int executed = -1;

        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining_time > 0 && time >= tasks[i].next_arrival) {
                executed = i;
                break;
            }
        }

        if (executed != -1) {
            printf("Time %d: Task %d is executed\n", time, tasks[executed].id);
            tasks[executed].remaining_time--;

            if (tasks[executed].remaining_time == 0) {
                tasks[executed].next_arrival += tasks[executed].period;
                tasks[executed].remaining_time = tasks[executed].execution;
                completed++;
            }
        }

        time++;
    }
}

int main() {
    int n;
    printf("Enter no. of tasks: ");
    scanf("%d", &n);

    task tasks[n];
    for (int i = 0; i < n; i++) {
        tasks[i].id = i + 1;
        printf("\nEnter details for Task: %d\n", i + 1);
        printf("Execution Time: ");
        scanf("%d", &tasks[i].execution);
        printf("Period: ");
        scanf("%d", &tasks[i].period);

        tasks[i].remaining_time = tasks[i].execution;
        tasks[i].next_arrival = 0;
    }

    sort_by_priority(tasks, n);
    rate_monotonic(tasks, n);

    return 0;
}
