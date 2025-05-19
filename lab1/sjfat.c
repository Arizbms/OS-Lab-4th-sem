#include<stdio.h>

int main() {
    int n;
    printf("Enter no of processes: ");
    scanf("%d", &n);

    int bt[n], at[n], tat[n], wt[n], process[n];
    int completed[n], current_time = 0, total_completed = 0;
    float wtavg = 0, tatavg = 0;

    printf("Enter burst time of each process:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &bt[i]);
        process[i] = i;
        completed[i] = 0;
    }

    printf("Enter arrival time of each process:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &at[i]);
    }

    while (total_completed < n) {
        int idx = -1, min_bt = 1e9;
        for (int i = 0; i < n; i++) {
            if (!completed[i] && at[i] <= current_time && bt[i] < min_bt) {
                min_bt = bt[i];
                idx = i;
            }
        }
        if (idx == -1) {
            current_time++; // no process has arrived yet, increment time
            continue;
        }
        wt[idx] = current_time - at[idx];
        if (wt[idx] < 0) wt[idx] = 0;
        tat[idx] = wt[idx] + bt[idx];
        current_time += bt[idx];
        completed[idx] = 1;
        total_completed++;
        wtavg += wt[idx];
        tatavg += tat[idx];
    }

    printf("\nProcess\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], wt[i], tat[i]);
    }
    printf("\nAverage turnaround time: %.2f", tatavg / n);
    printf("\nAverage waiting time: %.2f", wtavg / n);

    return 0;
}
