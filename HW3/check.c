#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>
int main(int argc, const char* argv[]) {
	//If not enough arguments are supplied, throw an error	
	if( (argc != 3) ){
	
		printf ("Error! Not enough arguments for checker program!\n");
		exit(1);
	
	}
	//If the divisor == 0, undefined/cannot be done, so return 0. Else, modulo check to see if divisible
	if( (*argv[0] == '0') ) {
	
		return 0;

	}
	
	else{
		int shmid;
		int* shmptr;
		int pipefd = atoi(argv[2]);
		read(pipefd, &shmid, sizeof(shmid));
		int divisor = atoi(argv[0]);
		int dividend = atoi(argv[1]);
		shmptr = shmat(shmid, NULL, 0);
		//Is divisible
		if( dividend % divisor == 0 ){
		
		printf("Checker process [%d]: starting.\n", getpid());
		printf("Checker process [%d]: read %d bytes containing shm ID %d\n", (int)getpid(), (int)sizeof(shmid), (int)shmid);	
		printf("Checker process [%d]: %d *IS* divisible by %d.\n", getpid(), dividend, divisor);
		//change value in shared memory
		*shmptr = 1;
		printf("Checker process [%d]: wrote result (1) to shared memory.\n", getpid());
		shmdt(shmptr);
			exit(1);
		}
		else{
		printf("Checker process [%d]: starting.\n", getpid());
		printf("Checker process [%d]: read %d bytes containing shm ID %d\n", (int)getpid(), (int)sizeof(shmid), (int)shmid);	
		printf("Checker process [%d]: %d *IS NOT* divisible by %d.\n", getpid(), dividend, divisor);
		//change value in shared memory
		*shmptr = 0;
		printf("Checker process [%d]: wrote result (0) to shared memory.\n", getpid());
		shmdt(shmptr);
			exit(0);
		}

	}

	

}


