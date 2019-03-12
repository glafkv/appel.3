#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	
	int choice = 0;
	opterr = 0;
	//Files
	char *infile = "input.txt";
	char *palinFile = "palin.out";
	char *noPalinFile = "nopalin.out";
	FILE *infptr = fopen(infile, "r");
	FILE *outfptr1 = fopen(palinFile, "a");
	FILE *outfptr2 = fopen(noPalinFile, "a");
	

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
	char str[80];
	fgets(str,80,infptr);
	printf("%s", str);





	//close the files
	fclose(infptr);
	fclose(outfptr1);
	fclose(outfptr2);
return 0;
}//end of program
