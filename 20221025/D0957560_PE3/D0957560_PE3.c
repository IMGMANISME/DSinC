#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_QUEUE_SIZE 10

int global_clock = 0;
int teller_amount = 0;
int teller_count = 0;
int last_arr_time[10] = {0};
int last_ser_time[10] = {0};

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

void close(int, int);

void open(int, int);

void check_leave();

int main() {
	FILE* input = fopen("input.txt","r");
	FILE* output = fopen("output.txt","w");

	char temp[20];

	fscanf(input,"%d",&teller_amount);
	teller_count = teller_amount;

	int i,j;

	for(i = 0; i < teller_amount; i++) {
		teller_queue[i].status = 2;
		teller_queue[i].count = 0;
		teller_queue[i].front = 0;
		teller_queue[i].rear = 1;
		teller_queue[i].current_served_time = 0;
	}

	while(fgets(temp, 20, input) != NULL) {

		fscanf(input,"%s %d %d",&C.name,&C.arr_time,&C.ser_time);

		if(strcmp("#",C.name) == 0) {
			int close_time = C.arr_time;
			int close_teller = C.ser_time;
			close(close_time,close_teller);
			teller_count--;
			//printf("input == #\n");
		} else if(strcmp("@",C.name) == 0) {
			int open_time = C.arr_time;
			int open_teller = C.ser_time;
			open(open_time,open_teller);
			teller_count++;
			//printf("input == @\n");
		} else {
			add(C.name,&C.arr_time,&C.ser_time);
			//printf("%s %d %d\n",C.name,C.arr_time,C.ser_time);
		}
		check_leave();
	}

	fclose(input);
	fclose(output);
}

void add(char* a, int* b, int* c) {
	//global_clock = *b;
	int i, j, mini;
	if(teller_amount > 1) {
		for(i = 0; i < teller_count - 1; i++) {//find the minimum count in all teller's customer queue
			if(teller_queue[i].count <= teller_queue[i + 1].count) {
				mini = i;
			} else {
				mini = i + 1;
			}
		}
	} else {
		mini = 0;
	}
	if(teller_queue[mini].count == 0) {
		teller_queue[mini].current_served_time = 0;
	} else {
		teller_queue[mini].current_served_time = (last_ser_time[mini] + teller_queue[mini].current_served_time) - (*b - last_arr_time[mini]);
	}
	last_arr_time[mini]= *b;
	last_ser_time[mini]= *c;
	strcpy(teller_queue[mini].queue[teller_queue[mini].rear].name,a);
	teller_queue[mini].queue[teller_queue[mini].rear].arr_time = *b + *c + teller_queue[mini].current_served_time;
	teller_queue[mini].queue[teller_queue[mini].rear].ser_time = mini;
	global_clock = teller_queue[mini].queue[teller_queue[mini].rear].arr_time;
	teller_queue[mini].rear++;
	teller_queue[mini].count++;

	//printf("%s %d %d\n", a, *b, *c);
}

void close(int a, int b) {
	int i,j;
	while(a == global_clock) {
		for(i = teller_queue[b].front + 2; i <= teller_queue[b].rear; i++ )
			add(teller_queue[b].queue[i].name,&teller_queue[b].queue[i].arr_time,&teller_queue[b].queue[i].ser_time);
		teller_queue[b].status = 0;
		teller_queue[b].count = 0;
		teller_queue[b].rear = 1;
		teller_queue[b].front = 0;
		teller_queue[b].current_served_time = 0;
	}
}

void open(int a, int b) {
	while(a == global_clock) {
		teller_queue[b].status = 2;
		teller_queue[b].rear = 1;
		teller_queue[b].front = 0;
	}
}

void check_leave(global_time) {
	int i, j;
	for(i = 0; i < teller_amount; i++) {
		for(j = teller_queue[i].front + 1; j < teller_queue[i].rear; j++) {
			while(global_time == teller_queue[i].queue[j].arr_time){
			}
			printf("%s %d %d\n", teller_queue[i].queue[j].name, teller_queue[i].queue[j].arr_time ,teller_queue[i].queue[j].ser_time);
			fprintf(output, "%s %d %d\n", teller_queue[i].queue[j].name, teller_queue[i].queue[j].arr_time ,teller_queue[i].queue[j].ser_time);
		}
	}
}

