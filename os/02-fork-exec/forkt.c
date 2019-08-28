#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>


int main(int argc, char *argv[]){
	if(argc==1){
		fprintf(stderr,"E:Enter number as argument\n");
		return 1;
	}
	int wstatus=1;
	pid_t last = fork();
	if(last<0){
		fprintf(stderr,"E:Could not fork");
		return 1;
	}
	else if(last==0){
		execl("./fact.out","fact.out",argv[1],NULL);
	}else{
		printf("Parent PID:\t%5d\nChild PID:\t%5d\n",getpid(),last);
		int pidd = wait(&wstatus);
		printf("After wait:\nWait status:%d, PID was: %d\n",wstatus,pidd);
	}
	return 0;
}
