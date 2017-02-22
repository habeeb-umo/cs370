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
		pid_t retVals[4];
		int holder = 0;
		int holder2 = 2;
	//For each argument, create a pipe, shmid and fork a process to check
		for(int i = 2; i < 6; i++){
		int fd[2];	
		int shmid = shmget(IPC_PRIVATE, sizeof(int), 0664 | IPC_CREAT);
		shmids[holder] = shmid;
		pipe(fd);
				
		pid_t retVal = fork();
		retVals[holder] = retVal;
	
			//If the fork returns -1, it failed
			if(retVal < 0){
				close(fd[0]);
				close(fd[1]); 
				printf("Failed to fork!\n");
				return 0;
			}	
			//If the fork returns anything > 0, that is the pid of the child
			if(retVal != 0){
				close(fd[0]);
				write(fd[1], &shmids[holder], sizeof(int));
				printf("Coordinator: forked process with ID %d.\n", retVal);
				printf("Coordinator: wrote shm ID %d to pipe (%d bytes)\n", (int)shmid, (int)sizeof(shmid));
				//If the status of the process after wait == 0, not divisible, else it is divisible
			}	
			else{
				close(fd[1]);
				//Read end of pipe int to char*
				char read_end[1];
				sprintf(read_end, "%d", fd[0]);

				execlp("./checker", argv[1], argv[i], read_end, (char *) NULL);	
			}
			holder++;
		}
		for(int i = 0; i < 4; i++){
		int status;
		printf("Coordinator: waiting on child process ID %d. . .\n", retVals[i]);	
		if(waitpid(retVals[i], &status, 0) >= 0){
				
				if(WEXITSTATUS(status) != 0){
				printf("Coordinator: result 1 read from shared memory: %d is divisible by %d.\n", atoi(argv[holder2]), atoi(argv[1]));
				shmctl(shmids[i], IPC_RMID, NULL);	
				}
				else
				printf("Coordinator: result 0 read from shared memory: %d is not divisible by %d.\n", atoi(argv[holder2]), atoi(argv[1]));
				shmctl(shmids[i], IPC_RMID, NULL);
				}	
	
		holder2++;
		}	
		
		

	printf("Coordinator: exiting.\n");
	return 0;
}
