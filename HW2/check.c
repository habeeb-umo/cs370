#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, const char* argv[]) {
	//If not enough arguments are supplied, throw an error	
	if( (argc != 2) ){
	
		printf ("Error! Not enough arguments for checker program!\n");
		exit(1);
	
	}
	//If the divisor == 0, undefined/cannot be done, so return 0. Else, modulo check to see if divisible
	if( (*argv[0] == '0') ) {
	
		return 0;

	}
	
	else{
		int divisor = atoi(argv[0]);
		int dividend = atoi(argv[1]);
		//Is divisible
		if( dividend % divisor == 0 )
			return 1;
		
		else
			return 0;
		
		
	}

}


