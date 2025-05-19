#include<stdio.h>
#include<conio.h>
int main(){
    int n;
    printf("Enter no of processes:");
    scanf("%d",&n);
    int bt[n],tat[n],wt[n],wtavg,tatavg;
    printf("Enter burst time of each process:");
    for(int i=0;i<n;i++){
        scanf("%d",&bt[i]);
    }
    wt[0]=wtavg=0;
    tat[0]=tatavg=bt[0];
    for(int i=1;i<n;i++){
        wt[i]=wt[i-1]+bt[i-1];
        tat[i]=tat[i-1]+bt[i];
        wtavg=wtavg+wt[i];
        tatavg=tatavg+tat[i];
    }

    for(int i=0;i<n;i++){
        printf("\nProcess %d : BT:%d WT:%d TAT:%d\n",(i+1),bt[i],wt[i],tat[i]);
    }
    printf("\nAverage turnaround time:%f",(float)tatavg/n);
    printf("\nAverage waiting time:%f",(float)wtavg/n);
    return 0;
}

OUTPUT:Enter no of processes:4
Enter burst time of each process:2 2 3 6

Process 1 : BT:2 WT:0 TAT:2

Process 2 : BT:2 WT:2 TAT:4

Process 3 : BT:3 WT:4 TAT:7

Process 4 : BT:6 WT:7 TAT:13

Average turnaround time:6.500000
Average witing time:3.250000
