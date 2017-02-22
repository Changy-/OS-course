#include "rpcprog.h"
#include "string.h"
#include "time.h"


// it's defined in rpcprog.h
char **getrpc_1_svc(char **msg, struct svc_req *rqstp){

	static char *result;
	//succeed to receive message from client

	printf("%s --> receive secret\n",*msg);
    char str[1024];
	strcpy(str,*msg);

    FILE *fp;
	int i = 0;
	int sum=0;
    //find the amount of digits in the string 
	while( i <= strlen(str) ) {
        if (str[i] >= '0' && str[i]<='9') sum++;

		i++;
	}
	// open secrets.out file and write msg and digit count.
	if ((fp = fopen("secrets.out","ab+")) == NULL) printf("error!");
            fprintf(fp,"original input:%s\nDigit count:%d\n",*msg,sum);
    fclose(fp);
    
    // return value
	result = "received";

	return &result;
}
