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

sem_t mutex;

void* thread(void* arg){
	sem_wait(&mutex);
	printf("Entered\n");
	sleep(4);
	printf("Exiting\n");
	sem_post(&mutex);
}
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
	
	//Semaphore section
	sem_init(&mutex, 0,1);
	pthread_t t1,t2;
	pthread_create(&t1, NULL, thread, NULL);
	sleep(2);
	pthread_create(&t2,NULL,thread,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	sem_destroy(&mutex);
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
	
	
	

	//close the files
	fclose(infptr);
	fclose(outfptr1);
	fclose(outfptr2);
return 0;
}//end of program


