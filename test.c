int main(){
    int n, tq;
    printf("Enter number of Processes: ");
    scanf("%d", &n);
    int arrival[n], bt[n], rem_bt[n], wt[n],
     tat[n], completion[n];
    char process[n][5];

    for(int i = 0; i<n; i++){
        sprintf(process[i], "P%d", i+1);
        printf("%s - Arrival Time: ", process[i]);
        scanf("%d", &arrival[i]);
        printf("%s - Burst Time: ", process[i]);
        scanf("%d", &bt[i]);
        rem_bt[i] = bt[i];
        wt[i] = tat[i] = 0;
    }
    printf("Enter time quantume: ");
    scanf("%d", &tq);

    int done = 0, time = 0;
    printf("\nGantt Chart:\n0");

    while(done<n){
        int check = 0;
        for(int i = 0; i<n; i++){
            if(arrival[i]<= time && rem_bt[i] > 0){
                check = 1;
                if(rem_bt[i]>tq){
                    time+=tq;
                    rem_bt[i]-=tq;
                    printf(" | %s | %d", process[i], time);
                }else{
                    time+=rem_bt[i];
                    tat[i] = time - arrival[i];
                    wt[i] = tat[i] - bt[i];
                    completion[i] = time;
                    rem_bt[i] = 0;
                    done++;
                    printf(" | %s | %d", process[i], time);
                }
            }
       }
       if(!check) time++;
    }
    return 0;
}