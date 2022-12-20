#include<stdio.h> 

int child = 1;
int adult = 0;
int total = 1;

int generate(int total, int g) {
	if(g != 0) {
		total = child + adult;
		child = adult * 2;
		adult = total;
		g--;
		generate(total ,g);
	} else {
		printf("%d\n", total);
		child = 1;
		adult = 0;
	}
}

int main() {
	int input;
	while(1) {
		input = 35;
		scanf("%d", &input);
		if(input == 35) {
			break;
		} else {
			if(1 > input || input > 20) {
				printf("Error!\n");
				continue;
			} else {
				generate(total, input);
				continue;
			}
		}
	}
}
