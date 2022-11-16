#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void find(char*, char*, int);
FILE* input;
FILE* output;

int main() {
	input = fopen("input.txt","r");
	output = fopen("output.txt","w");

	int i, node_count;
	char PreOrder[51];
	char InOrder[51];
	char PostOrder[51];


	if(!feof(input)) {
		
		fscanf(input,"%d",&node_count);
		printf("%d\n",node_count);
		
		fscanf(input,"%s",&PreOrder);
		printf("PreOrder = ");
		//fprintf(output,"\nPreOrder = ");
		for(i = 0; i < node_count; i++) {
			printf("%c",PreOrder[i]);
			//fprintf(output,"%c",PreOrder[i]);
		}
		
		printf("\n");
		//fprintf(output,"\n");
		
		fscanf(input,"%s",&InOrder);
		printf("InOrder = ");
		//fprintf(output,"\nInOrder = ");
		for(i = 0; i < node_count; i++) {
			printf("%c",InOrder[i]);
			//fprintf(output,"%c",InOrder[i]);
		}


		printf("\nPostOrder = ");
		//fprintf(output,"\nPostOrder = ");
		find(PreOrder, InOrder, node_count);
	}

	fclose(input);
	fclose(output);
}

void find(char* a, char* b, int num) {
	if (num == 0) {
		return;
	}
	int index = 0;
	int i;
	for (i = 0; i < num; i++) {
		if (b[i] == a[0]) {
			break;
		}
		index++;
	}
	find(a + 1, b, index);
	find(a + index + 1, b + index + 1, num - index - 1);
	printf("%c", a[0]);
	fprintf(output,"%c",a[0]);
}
