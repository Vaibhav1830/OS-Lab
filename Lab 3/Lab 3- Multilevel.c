#include <stdio.h>

int main() {
    int n, i;
    float wtavg = 0, tatavg = 0;

    printf("Enter total number of processes: ");
    scanf("%d", &n);

    int bt[n], wt[n], tat[n], queue[n];

    for (i = 0; i < n; i++) {
        printf("Enter Burst Time and Queue Type (1=System, 2=User) for Process %d: ", i + 1);
        scanf("%d %d", &bt[i], &queue[i]);
    }


    for (i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (queue[j] > queue[j + 1]) {
                int temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;

                temp = queue[j];
                queue[j] = queue[j + 1];
                queue[j + 1] = temp;
            }
        }
    }


    wt[0] = 0;
    tat[0] = bt[0];


    for (i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];
        tat[i] = wt[i] + bt[i];
        wtavg += wt[i];
        tatavg += tat[i];
    }

    wtavg /= n;
    tatavg = (tatavg + tat[0]) / n;


    printf("\nProcess\tQueue Type\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, queue[i], bt[i], wt[i], tat[i]);
    }


    printf("\nAverage Waiting Time = %.2f", wtavg);
    printf("\nAverage Turnaround Time = %.2f\n", tatavg);

    return 0;
}
