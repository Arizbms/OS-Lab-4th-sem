#include <stdio.h>
void sort_by_period(int n, int id[], int period[], int exec[]) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (period[i] > period[j]) {
                int temp;
                temp = period[i]; period[i] = period[j]; period[j] = temp;
                temp = exec[i]; exec[i] = exec[j]; exec[j] = temp;
                temp = id[i]; id[i] = id[j]; id[j] = temp;
            }
        }
    }
}
int main() {
    int n, t_max;
    printf("Enter number of tasks: ");
    scanf("%d", &n);
    int id[n], period[n], exec[n], remaining[n];
    for (int i = 0; i < n; i++) {
        id[i] = i + 1;
        printf("Enter period and execution time for Task %d: ", id[i]);
        scanf("%d %d", &period[i], &exec[i]);
        remaining[i] = 0;
    }
    printf("Enter total simulation time: ");
    scanf("%d", &t_max);
    sort_by_period(n, id, period, exec);
    for (int t = 0; t < t_max; t++) {
        for (int i = 0; i < n; i++)
            if (t % period[i] == 0)
                remaining[i] = exec[i];
        int ran = 0;
        for (int i = 0; i < n; i++) {
            if (remaining[i] > 0) {
                printf("Time %2d: Task %d running\n", t, id[i]);
                remaining[i]--;
                ran = 1;
                break;
            }
        }
        if (!ran)
            printf("Time %2d: CPU idle\n", t);
    }
}

O/P:
Enter number of tasks: 2
Enter period and execution time for Task 1: 5 2
Enter period and execution time for Task 2: 10 2
Enter total simulation time: 10
Time  0: Task 1 running
Time  1: Task 1 running
Time  2: Task 2 running
Time  3: Task 2 running
Time  4: CPU idle
Time  5: Task 1 running
Time  6: Task 1 running
Time  7: CPU idle
Time  8: CPU idle
Time  9: CPU idle
