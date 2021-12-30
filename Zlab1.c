#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <stdbool.h>

int numThreads, numProcs = 0; //declare global variables
bool done = false;
FILE *out_file;

void *showStats(){
	printf("Number of threads: %i \n", numThreads);
}

void *showProcs(){
	printf("Number of processes: %i \n", numProcs);
}

void *fileOut(){
	while(!done)
    {
        sleep(5);
        fprintf(out_file, "Number of threads: %i \n", numThreads);
		fprintf(out_file, "Number of processes: %i \n", numProcs);
    }
    return 0;
}

int main() {
	char str[100];
	int pid;
	char* cmd[100];
	pthread_t thread;
	
	out_file = fopen("INET4001_output.txt", "w"); //create & open output file
	
	pthread_create(&thread, NULL, fileOut, NULL); //create thread
	numThreads++; //increase number of threads to account for timer thread above

	while(!done){	
		printf("Enter Command: ");
		fgets(str, 100, stdin);       
		str[strlen(str) - 1] = '\0'; //get command

		if(strcmp(str,"quit")==0){
			done = true;
            exit(0); //exit loop
		}
		else if (strcmp(str, "showStats") == 0) {
			numThreads++;
			pthread_create(&thread, NULL, showStats, NULL); //create thread
			sleep(1); //sleep for a second so outputs don't come out at the same time
		}
		else if (strcmp(str, "showProcs") == 0) {
            numThreads++;
			pthread_create(&thread, NULL, showProcs, NULL); //create thread
			sleep(1); //sleep for a second so outputs don't come out at the same time
		}
		else{  

			numProcs++;
			pid = fork(); //create process
            int i = 0;
            cmd[i++] = strtok(str, " "); //parse command into parts

			if (pid == 0) { // I am the child
				int eresult= execvp(cmd[0], cmd); //execute given command
				if (eresult = -1){ //if execvp fails
					printf("invalid input \n");
					numProcs--; //decrease number of processes since this one failed
				}
			}
			else if (pid == -1) {
				perror("Error occurred while calling the fork function");
			}
			else { // i am the parent
				int status;
				waitpid(pid, &status, 0); //wait for child process to finish
			} 
		}

	}
	return 0;
}