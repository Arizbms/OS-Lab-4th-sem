#include <stdio.h>

int main() {
    int P, R, i, j, k;

    printf("Enter number of processes: ");
    scanf("%d", &P);
    printf("Enter number of resources: ");
    scanf("%d", &R);

    int allocation[P][R], max[P][R], need[P][R], available[R];

    // Input Allocation matrix
    printf("Enter Allocation matrix\n");
    for (i = 0; i < P; i++)
        for (j = 0; j < R; j++)
            scanf("%d", &allocation[i][j]);

    // Input Max matrix
    printf("Enter Max matrix\n");
    for (i = 0; i < P; i++)
        for (j = 0; j < R; j++)
            scanf("%d", &max[i][j]);

    // Input Available vector
    printf("Enter Available Resources: ");
    for (i = 0; i < R; i++)
        scanf("%d", &available[i]);

    // Calculate Need matrix
    for (i = 0; i < P; i++)
        for (j = 0; j < R; j++)
            need[i][j] = max[i][j] - allocation[i][j];

    // Resource Request
    int request[R], pid;
    printf("Enter New Request Details\n");
    printf("Enter pid: ");
    scanf("%d", &pid);
    printf("Enter Request for Resources: ");
    for (i = 0; i < R; i++)
        scanf("%d", &request[i]);

    // Combined check for Request ≤ Need and Request ≤ Available
   
    for (i = 0; i < R; i++) {
        if (request[i] > need[pid][i] || request[i] > available[i]) {
            printf("Request nof feasible");
            return 1;
        }
    }

    // Pretend to allocate
    for (i = 0; i < R; i++) {
        available[i] -= request[i];
        allocation[pid][i] += request[i];
        need[pid][i] -= request[i];
    }

    // Banker's Safety Algorithm
    int finish[P], safeSequence[P], count = 0;
    for (i = 0; i < P; i++) finish[i] = 0;

    while (count < P) {
        int found = 0;
        for (i = 0; i < P; i++) {
            if (!finish[i]) {
                int canAllocate = 1;
                for (j = 0; j < R; j++) {
                    if (need[i][j] > available[j]) {
                        canAllocate = 0;
                        break;
                    }
                }

                if (canAllocate) {
                    printf("P%d is visited( ", i);
                    for (k = 0; k < R; k++) {
                        available[k] += allocation[i][k];
                        printf("%d ", available[k]);
                    }
                    printf(")\n");

                    safeSequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (!found) {
            printf("SYSTEM IS NOT IN SAFE STATE\n");
            return 1;
        }
    }

    printf("SYSTEM IS IN SAFE STATE\n");
    printf("The Safe Sequence is -> (");
    for (i = 0; i < P; i++) {
        printf("P%d\t", safeSequence[i]);
    }
    printf(" )\n");

    // Print table
    printf("\n%-10s%-15s\n", "Process", "Need");
    for (i = 0; i < P; i++) {
        printf("P%-9d", i);
        for (j = 0; j < R; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }


    return 0;
}



O/P:
Enter number of processes: 5
Enter number of resources: 3
Enter Allocation matrix
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2
Enter Max matrix
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3
Enter Available Resources: 3 3 2
Enter New Request Details
Enter pid: 1
Enter Request for Resources: 1 0 2
P1 is visited( 5 3 2 )
P3 is visited( 7 4 3 )
P4 is visited( 7 4 5 )
P0 is visited( 7 5 5 )
P2 is visited( 10 5 7 )
SYSTEM IS IN SAFE STATE
The Safe Sequence is -> (P1	P3	P4	P0	P2	 )

Process   Need           
P0        7 4 3 
P1        0 2 0 
P2        6 0 0 
P3        0 1 1 
P4        4 3 1 
