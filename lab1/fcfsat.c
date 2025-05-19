#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], tat[n], wt[n], completed[n];
    float total_wt = 0, total_tat = 0;
    int current_time = 0, total_completed = 0;

    printf("Enter burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &bt[i]);
        completed[i] = 0;
    }

    printf("Enter arrival time for each process:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &at[i]);
    }

    while (total_completed < n) {
        int idx = -1;
        int min_at = 1e9;

        for (int i = 0; i < n; i++) {
            if (!completed[i] && at[i] <= current_time && at[i] < min_at) {
                min_at = at[i];
                idx = i;
            }
        }

        if (idx == -1) {
            current_time++; // No process has arrived yet
            continue;
        }

        wt[idx] = current_time - at[idx];
        if (wt[idx] < 0) wt[idx] = 0;

        current_time += bt[idx];
        tat[idx] = wt[idx] + bt[idx];

        completed[idx] = 1;
        total_completed++;

        total_wt += wt[idx];
        total_tat += tat[idx];
    }

    printf("\nProcess\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}
