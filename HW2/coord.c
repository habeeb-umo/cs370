#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
//int coordinator( int divisor, int dend1, int dend2, int dend3, int dend4 );

extern int checker(int a, int b);

int main(int argc, const char* argv[]) {

	if( (argc != 6) ){
	
	printf ("Error! Not enough arguments\n");
	return 0;
	
	}

/*	if( (*argv[1] == '0') || (*argv[2] == '0') || (*argv[3] == '0') || (*argv[4] == '0') ||
	    (*argv[5] == '0') ){
	
		return 0;
	}
*/

	for(int i = 2; i < 6; i++){
		
		pid_t retVal = fork();	
		
		if(retVal < 0){
			
			printf("Failed to fork!\n");
			return 0;
		}	

		if(retVal != 0){
			
			printf("Coordinator: forked process with ID %d.\n", retVal);
			printf("Coordinator: waiting for process [%d].\n", retVal);	
				
			int status;
			if(wait(&status) >= 0){
				if(WEXITSTATUS(status) != 0){	
				printf("Checker process [%d]: %d *IS* divisible by %d.\n", retVal, atoi(argv[i]), atoi(argv[1]));
				printf("Checker process [%d]: Returning 1.\n", retVal);
				printf("Coordinator: child process %d returned 1\n", retVal);
	
				}
				else{
				printf("Checker process [%d]: %d *IS NOT* divisible by %d.\n", retVal, atoi(argv[i]), atoi(argv[1]));
				printf("Checker process [%d]: Returning 0.\n", retVal);
				printf("Coordinator: child process %d returned 0\n", retVal);

				}
			}
			
		}
	
	
		

		else{
			printf("Checker process [%d]: Starting.\n", getpid());
			//checker(atoi(argv[1]), atoi(argv[i]));
			execlp("./checker", argv[1], argv[i], (char *) NULL);	
		}
	}
	
	printf("Coordinator: exiting.\n");
	return 0;
	
}
/*
int coordinator( int divisor, int dend1, int dend2, int dend3, int dend4 ){

	for(int i = 1; i < 5; i++){
		
		int retVal = fork();
		
		if(retVal < 0){
			
			printf("Something went wrong\n");
			return 0;
		}	

		if(retVal != 0){
	
			printf("Parent process: %d\n", getppid());
		//	wait(NULL);
			return 0;
		}

		else{
			printf("Child process: %d\n", getpid());
				checker(divisor, atoi(argv[i));
				
		}
	}
	return 0;
}
*/
