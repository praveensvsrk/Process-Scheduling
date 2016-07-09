#include<stdio.h>
#define NUM 4
typedef struct process{
	char *name;
	int burstTime;
	int arrivalTime;
}process;
int main(){
	int i;
	process list[NUM];
	float waitTime=0;
	int totalBurstTime=0;
	for(i=0; i<NUM; i++){
		printf("Enter Process %d Burst time: ", i);
		scanf("%d", &list[i].burstTime);
		printf("Enter Process %d Arrival time: ", i);
		scanf("%d", &list[i].arrivalTime);
		waitTime += (totalBurstTime - list[i].arrivalTime);
		totalBurstTime += list[i].burstTime;
	}
		
	printf("\nAverage wait time - %.2f\n", waitTime/NUM);
	return 0;
	
	
}
