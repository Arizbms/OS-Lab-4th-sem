#include<stdio.h>
#include<conio.h>
int main(){
    int n;
    printf("Enter no of processes:");
    scanf("%d",&n);
    int bt[n],tat[n],wt[n],process[n],wtavg,tatavg;
    printf("Enter burst time of each process:");
    for(int i=0;i<n;i++){
        process[i]=i;
        scanf("%d",&bt[i]);
    }
    for(int i=0;i<n;i++){
        for(int k=i+1;k<n;k++){
            if(bt[k]<bt[i]){
                int temp=bt[i];
                bt[i]=bt[k];
                bt[k]=temp;

                //swap process id
                temp=process[i];
                process[i]=process[k];
                process[k]=temp;
            }
        }

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
printf("\nProcess %d : BT:%d WT:%d TAT:%d\n",(process[i]+1),bt[i],wt[i],tat[i]);

    }
    printf("\nAverage turnaround time:%f",(float)tatavg/n);
    printf("\nAverage waiting time:%f",(float)wtavg/n);
    return 0;
}


OUTPUT:
Enter no of processes:4
Enter burst time of each process:6 8 7 3

Process 4 : BT:3 WT:0 TAT:3

Process 1 : BT:6 WT:3 TAT:9

Process 3 : BT:7 WT:9 TAT:16

Process 2 : BT:8 WT:16 TAT:24

Average turnaround time:13.000000
Average waiting time:7.000000
