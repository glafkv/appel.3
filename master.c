#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/sem.h>
#include <sys/stat.h>

#define shared_key 8675309
#define SEM_NAME "/makeSem"

int shmid;
char *shmaddr;
sem_t *sem;

int main(int argc, char *argv[])
{
	
	int choice = 0;
	opterr = 0;
	//Files
	char *infile = "input.txt";
	char *palinFile = "palin.out";
	char *noPalinFile = "nopalin.out";
	FILE *infptr = fopen(infile, "r");
	FILE *outfptr1 = fopen(palinFile, "w");
	FILE *outfptr2 = fopen(noPalinFile, "w");
	

	while((choice = getopt(argc,argv, "hf:")) != -1){
		switch(choice){
			case 'h':
				printf("\tI'm here to help!\n");
				printf("*********************\n");
				printf("-h brings up the help menu\n");
				printf("-f inputfile : indicate the name of your input file. The default is input.txt\n");
				printf("To run the program type : ./main -f filename\n");
				exit(0);
			case 'f':
				infile = optarg;
				break;
			case '?':
				if(optopt == 'f')
					fprintf(stderr,"Argument 'f' requires accompanying input\n", optopt);
				else
					fprintf(stderr,"Unknown option\n");
				return 1;
			default:
			abort();
		}//end of switch statement
	}//end of while statement
	
	if (argc < 2){
		fprintf(stderr, "Process %s requires an additional argument\n", argv[0]);
		return 1;
	}//end if statement
	
	//If the file doesn't exist
	if(infptr == NULL){
		perror("main.c: Error: ");
		exit(EXIT_FAILURE);
	}
	if(outfptr1 == NULL){
		perror("main.c: Error: ");
		exit(EXIT_FAILURE);
	}
	if(outfptr2 == NULL){
		perror("main.c: Error: ");
		exit(EXIT_FAILURE);
	}
	
	/*char str1[80], str2[80];
	int begin,middle,end, length = 0;
	//Doesn't take number palindromes
	 while(fgets(str1, sizeof(str1),infptr) != NULL){
		//token=strtok(str1,s);
		str1[strlen(str1)-1] = '\0';
		while(str1[length]!='\0')
			length++;
		
		end = length-1;
		middle = length/2;
		for(begin = 0; begin < middle; begin++){
			if(str1[begin]!=str1[end]){
				fprintf(outfptr2, "Not: %s\n", str1);
				break;
			}
			end--;
		}
		if(begin==middle){
			fprintf(outfptr1,"Palindrome: %s\n", str1);
		}
		
	}*/
	
	//Create the semaphor
	char parameter1 [12];
	char *ptr;
	int array[3];

	if((shmid = shmget(shared_key,1024,IPC_CREAT | IPC_EXCL | 0666)) < 0)
	{
		perror("shmget: ");
		exit(1);
	}
	
	shmaddr = (char *) shmat (shmid, 0,0);
	ptr = shmaddr + sizeof (array);
	
	array[0] = sprintf(ptr, "0") +1;
	ptr += array[0];
	array[1] = sprintf(ptr, "74") +1;
	ptr += array[1];
	array[2] = sprintf(ptr, "932") +1;

	memcpy(shmaddr, &array, sizeof (array));

	sem = sem_open(SEM_NAME, O_CREAT | O_EXCL, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH, 0666, 1);
	
	if(sem == SEM_FAILED){
		shmdt(shmaddr);
		shmctl(shmid, IPC_RMID,NULL);
		
		sem_unlink(SEM_NAME);
		sem_close(sem);
		perror("Semaphore failure.");
		
		exit(EXIT_FAILURE);	
	}
	sprintf(parameter1, "%d", shmid);
	
	if(fork()==0){
		execlp("./palin", "./palin", parameter1, (char *)NULL);
		fprintf(stderr, "Failed to exec to palin.\n");
	}
	sleep(1);
	sem_wait(sem);
	printf("master.c is using the semaphore");
	sem_post(sem);
	
	shmdt(shmaddr);
	shmctl(shmid, IPC_RMID,NULL);
	sem_close(sem);
	sem_unlink(SEM_NAME);
	//close the files
	fclose(infptr);
	fclose(outfptr1);
	fclose(outfptr2);
return 0;
}//end of program


