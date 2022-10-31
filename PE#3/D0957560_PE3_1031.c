#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_QUEUE_SIZE 10

int global_clock = 0;
int teller_amount = 0;

typedef struct Customer {
	char name[10]; // 客戶名字
	int arr_time; // 客戶到達銀行時間
	int ser_time; // 客戶完成業務要花多少時間
} Customer;

Customer C;

typedef struct TellerQueue {
	int status; // status, 0: close, 1:只剩下一位客戶，即將 close, 2: open
	int front; // front pointer，指向第一個 element 的 index
	int rear; // rear pointer，指向最後一個 element 的下一個 index
	int count; // queue 中在排隊的人數
	int current_served_time; // 目前在處理業務的客人到處理完畢剩下的時間
	Customer queue[MAX_QUEUE_SIZE]; // 以 array 型式模擬 Circular Queue。
} TellerQueue;

TellerQueue teller_queue[10];

void add(char*, int*, int*);

int check();

int main() {
	FILE* input = fopen("input.txt","r");
	FILE* output = fopen("output.txt","w");

	char temp[20];

	fscanf(input,"%d",&teller_amount);

	int i;

	for(i = 0; i < teller_amount; i++) {
		teller_queue[i].status = 2;
		teller_queue[i].count = 0;
		teller_queue[i].front = 0;
		teller_queue[i].rear = 0;
		teller_queue[i].current_served_time = 0;
	}

	while(fgets(temp, 20, input) != NULL) {

		fscanf(input,"%s %d %d",&C.name,&C.arr_time,&C.ser_time);

		if(strcmp("#",C.name) == 0) {
			printf("input == #\n");
		} else if(strcmp("@",C.name) == 0) {
			printf("input == @\n");
		} else {
			add(C.name,&C.arr_time,&C.ser_time);
			printf("%s %d %d\n",C.name,C.arr_time,C.ser_time);
		}
	}

	fclose(input);
	fclose(output);
}

void add(char* a, int* b, int* c){
	printf("%s %d %d\n",a,*b,*c);
}

int check(){
	int check_amount;
	
}

