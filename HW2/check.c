#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, const char* argv[]) {
	
	if( (argc != 2) ){
	
		printf ("Error! Not enough arguments for checker program!\n");
		exit(1);
	
	}

	if( (*argv[0] == '0') ) {
	
		return 0;

	}

	else{
		int divisor = atoi(argv[0]);
		int dividend = atoi(argv[1]);
		
		if( dividend % divisor == 0 )
			return 1;
		
		else
			return 0;
		
		
	}

}


