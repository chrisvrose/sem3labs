#include<stdio.h>
#include<stdlib.h>

int fact(int n){
	if(n==0) return 1;
	else return n*fact(n-1);
}

int main(int argc,char *argv[]){
	if(argc!=2){
		fprintf(stderr,"E:Invalid args\n");
		return 1;
	}
	int a = atoi(argv[1]);
	printf("%d!=%d\n",a,fact(a));
	return 0;
}
