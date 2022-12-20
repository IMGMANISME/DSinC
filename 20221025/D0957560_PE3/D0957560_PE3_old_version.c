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
	char name[10]; // �Ȥ�W�r
	int arr_time; // �Ȥ��F�Ȧ�ɶ�
	int ser_time; // �Ȥ᧹���~�ȭn��h�֮ɶ�
} Customer;

Customer c1;

typedef struct TellerQueue {
	int status; // status, 0: close, 1:�u�ѤU�@��Ȥ�A�Y�N close, 2: open
	int front; // front pointer�A���V�Ĥ@�� element �� index
	int rear; // rear pointer�A���V�̫�@�� element ���U�@�� index
	int count; // queue ���b�ƶ����H��
	int current_served_time; // �ثe�b�B�z�~�Ȫ��ȤH��B�z�����ѤU���ɶ�
	Customer queue[MAX_QUEUE_SIZE]; // �H array �������� Circular Queue�C
} TellerQueue;

TellerQueue teller_queue[10];

void add(char*,int*,int*);

void close(int,int);

int main() {
	FILE* input = fopen("input 1.txt","r");
	FILE* output = fopen("output.txt","w");
	int i,j;

	fscanf(input,"%d",&teller_amount);
	//printf("%d\n",teller_amount);

	for(i = 0; i < teller_amount; i++) {
		teller_queue[i].status = 2;//set teller to open situation
		teller_queue[i].front = 0;//set 0 for front
		teller_queue[i].rear = 0;//set 0 for rear
		teller_queue[i].count = 0;//set 0 for count
		teller_queue[i].current_served_time = 0;//set 0 for current_served_time
	}

	char temp[21];

	while(fgets(temp, 20, input) != NULL) {

		fscanf(input,"%s %d %d",&c1.name,&c1.arr_time,&c1.ser_time);
		global_clock = c1.arr_time;

		if(strcmp("#",c1.name) == 0) {
			int set_close_clock = c1.arr_time;
			int close_teller = c1.ser_time;
			teller_amount--;
			while(global_clock == set_close_clock) {
				teller_queue[close_teller].status = 1;
				teller_queue[close_teller].count = 1;
				close(c1.arr_time,c1.ser_time);
				break;
			}
			teller_queue[close_teller].current_served_time = 0;//delete teller's served time record
			teller_queue[close_teller].status = 0;//close teller's service window
			teller_queue[close_teller].count = 0;
			continue;
		} else if(strcmp("@",c1.name) == 0) {
			int set_open_clock = c1.arr_time;
			int open_teller = c1.ser_time;
			teller_amount++;
			while(global_clock == set_open_clock) {
				teller_queue[open_teller].status = 2;//open teller's service window
				break;
			}
			continue;
		} else {
			add(c1.name,&c1.arr_time,&c1.ser_time);
			printf("%s %d %d\n",c1.name,c1.arr_time,c1.ser_time);
			fprintf(output,"%s %d %d\n",c1.name,c1.arr_time,c1.ser_time);
		}
	}
	/*
	for(i = 0; i < teller_amount; i++) {
		for(j = 0; j < teller_queue[i].count; j++) {
			printf("i == %d\n",i);
			printf("j == %d\n",j);
			printf("%s %d %d\n",teller_queue[i].queue[j].name, teller_queue[i].queue[j].arr_time, teller_queue[i].queue[j].ser_time);
			printf("-------------------------------------\n");
		}
	}
	*/
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

void close(int b,int c) {
	int mini;
	int i,j;
	while(b == global_clock) {
		for(i = teller_queue[c].front + 2; i < teller_queue[c].count; i++){
			add(teller_queue[c].queue[i].name,&teller_queue[c].queue[i].arr_time,&teller_queue[c].queue[i].ser_time);
		}
	}
	/*
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
	}*/
}

