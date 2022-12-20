#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 101

int main() {
	char ch;
	char input[MAX];
	int i;
	

	while(1) {
		scanf("%s",&input);
		input[strlen(input)] = '\n';
		
		for(i=0;i<strlen(input);i++){
			ch = input[i];
			if(ch == ',' || ch == '\n'){
				
			}
		}
	

	}


}
