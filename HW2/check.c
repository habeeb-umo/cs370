#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

//int checka (int dividend, int divisor);

int main(int argc, const char* argv[]) {
	//printf("check1)\n");
	//printf("argc: %d\n", argc);

	if( (argc != 2) ){
	
		printf ("Error! Not enough arguments for Checker!\n");
		return 0;
	
	}

	if( (*argv[0] == '0') ) {
	
		printf("Can't divide by 0!\n");
		return 0;

	}
	else{
		int divisor = atoi(argv[0]);
		int dividend = atoi(argv[1]);
		
		if( dividend % divisor == 0){
			//printf("yes, divisible.\n");
		//	printf("%d *IS* divisible by %d.\n", dividend, divisor);
			return 1;
		}
		else{
			//printf("no, indivisible.\n");
		//	printf("%d *IS NOT* divisible by %d.\n", dividend, divisor);
			return 0;
		}
		
	}
    //printf("check2\n");
}

/*int checka (int dividend, int divisor){

	if( dividend % divisor == 0 ){

		printf("yes, divisible.\n");
		return 1;

	}
	else{

		printf("no, indivisible.\n");
		return 0;

	}
	
}*/
