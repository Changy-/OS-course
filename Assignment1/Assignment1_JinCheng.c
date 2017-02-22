#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>


int main(){
	while(1){

	// provide prompt to users
	printf("start--->> use CTRL+Z to end:\n");
	printf("You can enter linux commands(100 characters most):\n");

	// command is no more than 100 characters
	char command[100];

	//get input
	gets(command);
	printf("--->>result<<---\n");

	// system() function will use fork to create a child process first, then execute the command.
	// so, I don't need to fork() a new process.
	int tmp=system(command);

	//when executing command fails.
	if(tmp == 1){
		printf("command is null.");	
	}
	if(tmp == -1){
		printf("failed to create child process.");	
	}
	if(tmp == 127){
		printf("failed to run /bin/sh");	
	}	

	printf("\n");
	printf("\n");

	}
	return 0;
}
