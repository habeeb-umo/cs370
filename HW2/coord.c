#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, const char* argv[]) {
	//If there are not enough arguments, throw a usage error
	if( (argc != 6) ){
	
		printf ("Usage: ./coordinator <divisor> <dividend1> <dividend2> <dividend3> <dividend4>\n");
		return 0;
	
	}
	//For each argument, perform fork a process to check
	for(int i = 2; i < 6; i++){
		
		pid_t retVal = fork();	
		//If the fork returns -1, it failed
		if(retVal < 0){
			
			printf("Failed to fork!\n");
			return 0;
		}	
		//If the fork returns anything > 0, that is the pid of the child
		if(retVal != 0){
			
			int status;

			printf("Coordinator: forked process with ID %d.\n", retVal);
			printf("Coordinator: waiting for process [%d].\n", retVal);	
			//If the status of the process after wait == 0, not divisible, else it is divisible
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

