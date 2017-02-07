#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, const char* argv[]) {

	if( (argc != 6) ){
	
		printf ("Usage: ./coordinator <divisor> <dividend> <dividend> <dividend> <dividend>\n");
		return 0;
	
	}

	for(int i = 2; i < 6; i++){
		
		pid_t retVal = fork();	
		
		if(retVal < 0){
			
			printf("Failed to fork!\n");
			return 0;
		}	

		if(retVal != 0){
			
			int status;

			printf("Coordinator: forked process with ID %d.\n", retVal);
			printf("Coordinator: waiting for process [%d].\n", retVal);	

			if(wait(&status) >= 0){

				if(WEXITSTATUS(status) != 0){
		
					printf("Checker process [%d]: %d *IS* divisible by %d.\n", retVal, atoi(argv[i]), atoi(argv[1]));
					printf("Checker process [%d]: Returning 1.\n", retVal);
					printf("Coordinator: child process %d returned 1.\n", retVal);
				}

				else{

					printf("Checker process [%d]: %d *IS NOT* divisible by %d.\n", retVal, atoi(argv[i]), atoi(argv[1]));
					printf("Checker process [%d]: Returning 0.\n", retVal);
					printf("Coordinator: child process %d returned 0.\n", retVal);
				}
			}
			
		}	

		else{

			printf("Checker process [%d]: Starting.\n", getpid());
			execlp("./checker", argv[1], argv[i], (char *) NULL);	
		}
	}
	
	printf("Coordinator: exiting.\n");
	return 0;
	
}

