#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 101

int priority(char);

void transfer(char* infix, char* postfix) { //transfer infix to postix
	char stack[MAX] = {'\0'};
	int infix_counter;
	int postfix_counter = 0;
	int stack_counter = 0;
	char check;
	while(strlen(infix) != 0) {
		infix[strlen(infix)] = ')';
		for(infix_counter = 0; infix_counter < strlen(infix); infix_counter++) {
			//printf("infix_counter = %d\n",infix_counter);
			check = infix[infix_counter];
			if(check == '(') {
				//printf("check = (\n");
				postfix[postfix_counter] = infix[infix_counter + 1];
				postfix_counter++;
				infix_counter++;
			} else if(check == '+' || check == '-' || check == '*' || check == '/' ) {
				//printf("check = operator\n");
				//printf("stack_counter = %d\n", stack_counter);
				if(priority(check)>priority(stack[stack_counter])) {
					//printf("oper > \n");
					if(stack_counter == 0) {
						//printf("stack_counter = NULL \n");
						stack[stack_counter] = check;
					} else {
						//printf("stack_counter != NULL \n");
						stack[stack_counter] = stack[stack_counter - 1];
						stack[stack_counter - 1] = check;
					}
					stack_counter++;
				} else if(priority(check)<priority(stack[stack_counter])) {
					//printf("oper < \n");
					stack[stack_counter] = check;
				} else {
					//printf("oper = \n");
					postfix[postfix_counter] = stack[stack_counter];
					postfix_counter++;
					memset(stack,0,strlen(stack));//clear stack
					stack_counter = 0;
				}

			} else if(check == ')') {
				//printf("check = ) \n");
				int i;
				for(i = 0; i < stack_counter; i++) {
					postfix[postfix_counter] = stack[i];
					postfix_counter++;
				}
				memset(stack,0,strlen(stack));//clear stack
				stack_counter = 0;
			} else {
				//printf("check = abc\n");
				postfix[postfix_counter] = infix[infix_counter];
				postfix_counter += 1;
			}
			/*printf("postfix_counter = %d\n", postfix_counter);
			printf("postfix = %s\n", postfix);
			printf("stack_counter = %d\n", stack_counter);
			printf("stack = %s\n", stack);
			printf("--------------------------------------------------\n");
			*/
		}
		break;
	}
}


int priority(char oper) { //define priority of operater
	switch(oper) {
		case'+':
		case'-':
			return 2;
		case'*':
		case'/':
			return 1;
		default:
			return 0;
	}
}

int main(void) {
	char infix[MAX] = {'\0'};
	char postfix[MAX] = {'\0'};
	int i;
	FILE* input = fopen("infix.txt","r");
	FILE* output = fopen("postfix.txt","w");

	//printf("Please enter infix expression : ");
	fscanf(input,"%s",&infix);
	//scanf("%s",&infix);//input infix
	transfer(infix,postfix);//transfer infix to postfix

	printf("Postfix expression = ");
	for (i = 0; postfix[i] != '\0'; i++) {
		fprintf(output,"%c",postfix[i]);
		printf("%c",postfix[i]);//output postfix
	}

	fclose(input);
	fclose(output);
}
