#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#define SIZE 64516

int main(){
	int32_t arr1[SIZE], arr2[SIZE], received_ans[SIZE];

	FILE *first, *second, *ans;
	//first = fopen("first.txt", "r");
	//second = fopen("second.txt", "r");
	ans = fopen("ANS.TXT", "r");

	//fread(arr1, sizeof(int32_t), SIZE, first);
	//fread(arr2, sizeof(int32_t), SIZE, second);
	fread(received_ans, sizeof(int32_t), 20, ans);

	for(uint32_t i = 0; i < SIZE; i++){
		//assert(arr1[i]*arr2[i] == received_ans[i]);
		printf("%d\n",  received_ans[i]);
	}

	//printf("Calculated results matched expected values\n");

	return 0;
}
