#include "rpcprog.h"
#include "string.h"


#define HOST "127.0.0.1"
static char **ret;
CLIENT *handle;

void rpcInput(char *msg){
	//generate a handle which is used to connect
	handle = clnt_create(HOST,RPCPROG,RPCVERS,"udp");
	if (handle == 0) {
		printf("Fail To Connect To Remote Server./n");
		exit(1);

	}
	//to find C00L
	char *contain_str = strstr(msg,"C00L"); 
	if(contain_str != NULL)
		// if find, send it to server;
		ret = getrpc_1(&msg, handle);
	else{
		printf("no secret, try again!\n");
	}
	
	clnt_destroy(handle);
}

int main(){

	while(1){
		char msg[1024];
		printf("---->input message: <----\n");
		//get input
		scanf("%s",msg);
		// rpc function
		rpcInput(msg);

	}
}


