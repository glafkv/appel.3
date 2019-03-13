#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

#define shared_key 8675309

int shmid;
char *shmaddr;

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


	shmdt(shmaddr);
	shmctl(shmid, IPC_RMID,NULL);




return 0;
}

