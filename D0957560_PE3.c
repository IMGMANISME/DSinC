#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_QUEUE_SIZE 10

int global_clock = 0;
int last_arr_time[10] = {0};
int last_ser_time[10] = {0};
int teller_amount;
int teller_number;
int total_time;

typedef struct Customer {
	char name[10]; // 客戶名字
	int arr_time; // 客戶到達銀行時間
	int ser_time; // 客戶完成業務要花多少時間
} Customer;

Customer c1;

typedef struct TellerQueue {
	int status; // status, 0: close, 1:只剩下一位客戶，即將 close, 2: open
	int front; // front pointer，指向第一個 element 的 index
	int rear; // rear pointer，指向最後一個 element 的下一個 index
	int count; // queue 中在排隊的人數
	int current_served_time; // 目前在處理業務的客人到處理完畢剩下的時間
	Customer queue[MAX_QUEUE_SIZE]; // 以 array 型式模擬 Circular Queue。
} TellerQueue;

TellerQueue teller_queue[10];

void add(char*,int*,int*);

void delete(int*,int*);

int main() {
	FILE* input = fopen("input.txt","r");
	FILE* output = fopen("output.txt","w");
	int i,j;

	fscanf(input,"%d ",&teller_amount);
	printf("%d\n",teller_amount);

	for(i = 0; i < teller_amount; i++) {
		teller_queue[i].status = 2;//set teller to open situation
		teller_queue[i].front = 0;//set 0 for front
		teller_queue[i].rear = 0;//set 0 for rear
		teller_queue[i].count = 0;//set 0 for count
		teller_queue[i].current_served_time = 0;//set 0 for current_served_time
	}

	char temp[21];

	while(fgets(temp, 20, input) != NULL) {

		//printf("%s\n",temp);

		fscanf(input,"%s ",&c1.name);
		fscanf(input," %d",&c1.arr_time);
		fscanf(input," %d",&c1.ser_time);
		//printf("%s %d %d\n",c1.name,c1.arr_time,c1.ser_time);
		global_clock = c1.arr_time;

		if(strcmp("#",c1.name) == 0) {
			//printf("$1\n");
			int set_close_clock = c1.arr_time;
			int close_teller = c1.ser_time;
			teller_amount--;
			while(global_clock == set_close_clock) {
				teller_queue[close_teller].status = 1;
				teller_queue[close_teller].count = 1;
				delete(&c1.arr_time,&c1.ser_time);
				break;
			}
			teller_queue[close_teller].current_served_time = 0;//delete teller's served time record
			teller_queue[close_teller].status = 0;//close teller's service window
			printf("close teller No.%d's service window\n",close_teller);
			teller_queue[close_teller].count = 0;
			continue;
		} else if(strcmp("@",c1.name) == 0) {
			//printf("$2\n");
			int set_open_clock = c1.arr_time;
			int open_teller = c1.ser_time;
			teller_amount++;
			while(global_clock == set_open_clock) {
				teller_queue[open_teller].status = 2;//open teller's service window
				printf("open teller No.%d's service window\n",open_teller);
				break;
			}
			continue;
		} else {
			//printf("$3\n");
			add(c1.name,&c1.arr_time,&c1.ser_time);
			printf("%s %d %d\n",c1.name,c1.arr_time,c1.ser_time);
			fprintf(output,"%s %d %d\n",c1.name,c1.arr_time,c1.ser_time);
		}

		/*while(global_clock == ) {

		}*/
	}
	fclose(input);
	fclose(output);

}



void add(char* a,int* b,int* c) {
	int i;
	int mini;
	if(teller_amount > 1) {
		for(i = 0; i < teller_amount - 1; i++) {//find the minimum count in all teller's customer queue
			if(teller_queue[i].count <= teller_queue[i + 1].count) {
				mini = i;
			} else {
				mini = i + 1;
			}
		}
	} else {
		mini = 0;
	}
	teller_queue[mini].rear++;
	teller_queue[mini].queue[teller_queue[mini].rear] = c1;//assign coustomer to teller's customer queue
	if(teller_queue[mini].count == 0) {
		teller_queue[mini].current_served_time = 0;
	} else {
		teller_queue[mini].current_served_time = (last_ser_time[mini] + teller_queue[mini].current_served_time) - (c1.arr_time - last_arr_time[mini]);
	}
	teller_queue[mini].count++;
	last_arr_time[mini]= c1.arr_time;
	last_ser_time[mini]= c1.ser_time;
	*b = *b + *c + teller_queue[mini].current_served_time;
	*c = mini;
}

void delete(int* b,int* c) {
	int mini;
	int i,j;
	for(i = 0; i < teller_amount - 1; i++) {//find the minimum count in all teller's customer queue
		if(teller_queue[i].count <= teller_queue[i + 1].count) {
			mini = i;
		} else {
			mini = i + 1;
		}
	}

	for(j = 0; j < teller_queue[*c].count - 1; j++) {
		teller_queue[mini].queue[teller_queue[mini].rear + 1] =teller_queue[*c].queue[teller_queue[*c].rear + 1];
		teller_queue[mini].rear ++;
		teller_queue[*c].rear ++;
	}
}
