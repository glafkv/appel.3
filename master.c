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

#define shared_key 8675309


int shmid;
char *shmaddr;

void reverse(char s[]){
	int c,i,j;
	for(i = 0, j=strlen(s)-1; i<j;i++,j--){
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}	
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
	
	char str1[80], str2[80];
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
		
	}
	
	

	//close the files
	fclose(infptr);
	fclose(outfptr1);
	fclose(outfptr2);
return 0;
}//end of program


