#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int bt[n], at[n], wt[n], tat[n], completed[n], process[n];
    int current_time = 0;
    float wtavg = 0, tatavg = 0;

    printf("Enter burst times of each process:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &bt[i]);
        process[i] = i;
        completed[i] = 0;
    }

    printf("Enter arrival times of each process:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &at[i]);
    }

    // Sort by arrival time (stable FCFS)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (at[j] < at[i]) {
                // Swap arrival time
                int temp = at[i]; at[i] = at[j]; at[j] = temp;
                // Swap burst time
                temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;
                // Swap process ID
                temp = process[i]; process[i] = process[j]; process[j] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (current_time < at[i]) {
            current_time = at[i];  // Wait if process hasn't arrived
        }

        wt[i] = current_time - at[i];
        tat[i] = wt[i] + bt[i];
        current_time += bt[i];

        wtavg += wt[i];
        tatavg += tat[i];
    }

    printf("\nProcess\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", process[i] + 1, at[i], bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Turnaround Time: %.2f", tatavg / n);
    printf("\nAverage Waiting Time: %.2f", wtavg / n);

    return 0;
}
