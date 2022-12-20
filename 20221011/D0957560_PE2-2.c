#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// func() 代表找出 location - 1這個人在那裡吃飯 
int func(int *arr, int location) {
	if (arr[location - 1] < 0) {
		return func(arr, -arr[location - 1]);
	} else {
		return arr[location - 1];
	}
}

int main() {
	FILE *input = fopen("input.txt", "r");
	FILE *output = fopen("output.txt", "w");
	char ch;
	char input_str[1000];
	char str[5];
	int ch_counter = 0;
	int arr[100];
	int arr_counter = 0;
	int i;
	/*read each input data*/
	fscanf(input, "%s", input_str);//input file data
	input_str[strlen(input_str)] = '\n';//set last char == '\n'
	for (i = 0; i < strlen(input_str); i++) {//check every char in String
		ch = input_str[i];//asign input char to char ch
		if (ch == ',' || ch == '\n') {//check if char in input_str is ',' or EOF
			if (str[0] == '=') {//check if str[] first char == '='
				char *new_str = strtok(str, "=");//take away char'=' that from str[] and asign str[] to *new_str
				arr[arr_counter++] = -atoi(new_str);//transfer data char in *new_str to int and * (-1) and asign to arr[]  
			} else {
				arr[arr_counter++] = atoi(str);//transfer data char in *new_str to int and asign to arr[]
			}
			memset(str, 0, sizeof(str));//reset str[]
			ch_counter = 0;//reset ch counter
		} else {
			str[ch_counter++] = ch;//asign ch into array str[] 
		}
	}
	/*confirm each data type*/
	for (i = 0; i < arr_counter; i++) {
		arr[i] = func(arr, i + 1);
	}
	/*output each data into a .txt file*/
	for (i = 0; i < arr_counter; i++) {
		fprintf(output, "%d", arr[i]);
		if (i < arr_counter - 1) {
			fprintf(output, ",");
		}
	}

	fclose(input);
	fclose(output);
}
