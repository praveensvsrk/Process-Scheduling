#include<stdio.h>
#define NUM 4
typedef struct {
	char name;
	int burstTime;
	int arrivalTime;
	int waitTime;

}process;
typedef struct {
	process list[NUM];
	int size;
	int front;
	int rear;
}processQueue;

void initQueue(processQueue *pq) {
	pq->size=0;
	pq->front=0;
	pq->rear=-1;
	
}
void enQueue(processQueue *pq, process *p) {
	pq->size++;
	pq->rear++;
	pq->list[pq->rear]=*p;
	printf("\t\tProcess %c entered the queue\n",p->name);
		
}
void deQueue(processQueue *pq) {
	printf("\t\tProcess %c ended\n",pq->list[pq->front].name);
	pq->size--;
	pq->front++;
	
}
void sortQueueByBT(processQueue *pq){
	int i,j;
	for(i=pq->front+1; i<=pq->rear; i++) {
		for(j=i+1; j<=pq->rear; j++) {
			if(pq->list[i].burstTime > pq->list[j].burstTime){
				process temp=pq->list[i];
				pq->list[i]=pq->list[j];
				pq->list[j]=temp;
			}
		}
	}
}
void sortListByAT(process list[]){
	int i,j;
	for(i=0; i<NUM; i++) {
		for(j=i+1; j<NUM; j++) {
			if(list[i].arrivalTime > list[j].arrivalTime){
				process temp=list[i];
				list[i]=list[j];
				list[j]=temp;
			}
		}
	}
}
void checkProcessQueue(processQueue *pq, process list[], int time){
	int i;
	for(i=0; i<NUM; i++){
		if(time==list[i].arrivalTime) {
			enQueue(pq, &list[i]);
		}
	} 
}

void run(process *p){
	printf("\tProcess %c occupied CPU, Time left = %d\n",p->name,p->burstTime);
	p->burstTime--;
	
}
void wait(process *p){
	printf("\tProcess %c waiting for CPU\n",p->name);
	p->waitTime++;
}
int main(){
	int i,j,time;
	process list[NUM];
	processQueue queue;
	int totalWaitTime=0;	
	int totalBurstTime=0;
	printf("***Shortest Job First - non preemptive scheduling***\n");
	for(i=0; i<NUM; i++){	
		printf("Enter Process %d Burst time: ", i);
		scanf("%d", &list[i].burstTime);
		printf("Enter Process %d Arrival time: ", i);
		scanf("%d", &list[i].arrivalTime);
		list[i].name=(char)(i+48);
		list[i].waitTime=0;
		totalBurstTime+=list[i].burstTime;
		
	}
	sortListByAT(list);
	initQueue(&queue);
	for(time=0; time<totalBurstTime; time++) {
		printf("CPU Cycle %d\n",time);
		checkProcessQueue(&queue,list,time);
		sortQueueByBT(&queue);
		
		if(queue.size!=0)
			run(&queue.list[queue.front]);//run current process
		else 
			printf("\nCPU Idle\n");		
		for(i=queue.front+1; i<=queue.rear; i++){ //all the rest of processes wait
			wait(&queue.list[i]);
		}
		if(queue.size!=0 && queue.list[queue.front].burstTime==0){
			totalWaitTime += queue.list[queue.front].waitTime;
			deQueue(&queue);
		}
				
		
		
	}	
	
			
	printf("\nAverage wait time - %f\n", (float)(totalWaitTime)/NUM);
	return 0;

	
}
