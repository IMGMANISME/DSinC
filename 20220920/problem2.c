#include <stdio.h>
#define Max 100000

int main(){//�D�{�� 
	int a;
	while(1){
	scanf("%d",&a);//Ū�J����� 
	function(a); 
	}
}

void function(int b){
	int n;
	int count[Max];
	int i ;
	int j = 0;
	for(i = 0; i < b; i++){
		scanf("%d",&n);//Ū�J�Q�i��� 
		while(n != 0){
			count[j] = n%(-2);
			if(count[j] < 0){
				count[j] * (-1);
			}
				j = j + 1;
				n = n/(-2);
		}
		printf("Case #%d :", i+1);//��X-2�i��� 
		 for(;j > 0;j--){
		 	printf("%d",count[j-1]);
		 }
		 printf("\n");
		}
	}

