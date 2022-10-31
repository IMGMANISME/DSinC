#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_QUEUE_SIZE 10

int global_clock = 0;
int teller_amount = 0;

typedef struct Customer {
	char name[10]; // �Ȥ�W�r
	int arr_time; // �Ȥ��F�Ȧ�ɶ�
	int ser_time; // �Ȥ᧹���~�ȭn��h�֮ɶ�
} Customer;

Customer C;

typedef struct TellerQueue {
	int status; // status, 0: close, 1:�u�ѤU�@��Ȥ�A�Y�N close, 2: open
	int front; // front pointer�A���V�Ĥ@�� element �� index
	int rear; // rear pointer�A���V�̫�@�� element ���U�@�� index
	int count; // queue ���b�ƶ����H��
	int current_served_time; // �ثe�b�B�z�~�Ȫ��ȤH��B�z�����ѤU���ɶ�
	Customer queue[MAX_QUEUE_SIZE]; // �H array �������� Circular Queue�C
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

