#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

#define shared_key 8675309
#define SEM_NAME "/makeSem"

int shmid;
char *shmaddr;
sem_t *sem;
int main(int argc, char *argv[])
{

	char parameter1 [12];
	char *array[3]; 
	char *ptr;
	int *p;
	int shared_memory[3];
	int first, second, third;

	shmid = atoi(argv[1]);
	shmaddr = (char *) shmat (shmid, 0,0);
	sem = sem_open(SEM_NAME,O_CREAT,0666,1);
	
	if(sem == SEM_FAILED){
		perror("Semaphore failed.");
		exit(EXIT_FAILURE);
	}
	sem_wait(sem);	
	printf("palin.c is using the semaphore\n");

	//Get the info from the shared memory
	ptr = shmaddr + sizeof (shared_memory);
	p = (int *) shmaddr;
	array[0] = ptr;
	ptr += *p++;
	
	array[1] = ptr;
	ptr += *p++;
	
	array[2] = ptr;
	ptr += *p++;

	first = atoi(array[0]);
	second = atoi(array[1]);
	third = atoi(array[2]);
	
	printf("%i,   %i,     %i\n", first, second, third);

	sem_post(sem);





return 0;
}

