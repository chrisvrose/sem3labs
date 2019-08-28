#include<stdio.h>

#include<sys/types.h>
#include<sys/stat.h>

#include<fcntl.h>
#include<unistd.h>


int main(int argc,char* argv[]){
    if(argc==1){
        printf("Usage: rm <file1> [file2] ...\n");
        return 0;
    }
    for(int i=1;i<argc;i++){
        if(unlink(argv[i])!=0){
            fprintf(stderr,"E:Cannot remove file: %s\n",argv[i]);
            continue;
        }
    }
    return 0;
}