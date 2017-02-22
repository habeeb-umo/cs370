#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>

int main(int argc, const char* argv[]) {
	//If there are not enough arguments, throw a usage error
	if( (argc != 6) ){
	
		printf ("Usage: ./coordinator <divisor> <dividend1> <dividend2> <dividend3> <dividend4>\n");
		return 0;
	
	}

		int shmids[4];
		int shmptrs[4];
		pid_t retVals[4];
	//For each argument, perform fork a process to check
		for(int i = 0; i < 4; i++){

		int fd[2];	
		int shmid = shmget(IPC_PRIVATE, sizeof(int), 0664 | IPC_CREAT);
		shmids[i] = shmid;
		pipe(fd);
		write(fd[1], &shmid, sizeof(int));
				
		pid_t retVal = fork();
		retVals[i] = retVal;
	
			//If the fork returns -1, it failed
			if(retVal < 0){
			
				printf("Failed to fork!\n");
				return 0;
			}	
			//If the fork returns anything > 0, that is the pid of the child
			if(retVal != 0){

				printf("Coordinator: forked process with ID %d.\n", retVal);
				printf("Coordinator: wrote shm ID %d to pipe (%d bytes).\n", shmid, sizeof(shmid));
				printf("Coordinator: waiting for process [%d].\n", retVal);	
				//If the status of the process after wait == 0, not divisible, else it is divisible
			}	
			else{
				//Read end of pipe int to char*
				char read_end[20];
				sprintf(read_end, "%d", fd[0]);

				printf("Checker process [%d]: Starting.\n", getpid());
				execlp("./checker", argv[1], argv[i], read_end, (char *) NULL);	
			}
		}
		for(int i = 0; i < 4; i++){
		int status;
	
		if(waitpid(retVals[i], &status, 0) >= 0){

			
			if(WEXITSTATUS(status) != 0){
		
				printf("Checker process [%d]: %d *IS* divisible by %d.\n", retVals[i], atoi(argv[i]), atoi(argv[1]));
				printf("Checker process [%d]: Returning 1.\n", retVals[i]);
				printf("Coordinator: child process %d returned 1.\n", retVals[i]);
			}
			else{

				printf("Checker process [%d]: %d *IS NOT* divisible by %d.\n", retVals[i], atoi(argv[i]), atoi(argv[1]));
				printf("Checker process [%d]: Returning 0.\n", retVals[i]);
				printf("Coordinator: child process %d returned 0.\n", retVals[i]);
			}
		}
			
	
	
	}
	
	printf("Coordinator: exiting.\n");
	return 0;
	
}

