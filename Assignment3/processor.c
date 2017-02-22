#include <stdio.h>     
#include <sys/types.h>
#include <sys/ipc.h>     
#include <sys/shm.h>     
#include "control.h"
#include <stdlib.h> 
#include <string.h>
#define BUF_SIZE 1024     
#define MYKEY 25     
int  main()     
{     
    int shmid;     
    char * shmptr;     
	FILE *fp;
	
	if((fp = fopen("secrets.out","ab+")) == NULL){
		printf("open secrets.out failed!");
		exit(0);	
	}

    if((shmid = shmget(MYKEY,BUF_SIZE,IPC_CREAT)) ==-1)     
    {     
    	printf("shmget error!\n");     
    	exit(1);     
    }
	if((shmptr = shmat(shmid,0,0)) == (void *)-1){     
   		printf("shmat error!\n");     
    	exit(1);     
   	}  

	char tmp[1024];

	strcpy(tmp,shmptr);

    while(1){

		if(strcmp(tmp,shmptr) == 0){
			sleep(1);
		} 
		else{
			strcpy(tmp,shmptr);
			if(strstr(tmp,"COOL") != NULL){

				int count = 0;
				for(int i =0; tmp[i]!='\0';i++){
					if(tmp[i] - '0' >= 0 && tmp[i] - '0' <= 9){
						count++;
					}
				}
				char digit[10];
				fputs(shmptr,fp);
				fputs("  number of digits: ",fp);
				sprintf(digit, "%d", count);				
				fputs(digit,fp);				
				fputs("\n",fp);

			}
			if(strstr(tmp,"END") != NULL){
				fclose(fp);
				break;
			}

		}
	    
    }     

        exit(0);     
}
