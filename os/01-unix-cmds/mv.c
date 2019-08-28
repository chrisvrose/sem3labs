#include<stdio.h>

#include<sys/types.h>
#include<sys/stat.h>

#include<fcntl.h>
#include<unistd.h>


#define BSIZE 64

int main(int argc,char* argv[]){
    if(argc==1){
        printf("Usage: mv <old/path> <new/path>\n");
        return 0;
    }
    if(argc<3){
        fprintf(stderr,"E:Not enough arguments.\n");
        return 1;
    }
    int oldfd = open(argv[1],O_RDONLY);
    if(oldfd<0){
        fprintf(stderr,"E: Unable to access file.\n");
        return 1;
    }
    int newfd = open(argv[2],O_WRONLY|O_CREAT,0644);
    if(newfd<0){
        fprintf(stderr,"E:Error opening destination for write.\n");
        return 1;
    }
    char buffer[BSIZE];
    int lastRead=0,sumRead=0;
    while((lastRead=read(oldfd,buffer,BSIZE))!=0){
        if(write(newfd,buffer,lastRead)!=lastRead){
            fprintf(stderr,"E:Error copying file.Aborting.\n");
            return 1;
        }
        else{
            sumRead+=lastRead;
        }
    }
    printf("I: Copied %d bytes.\n",sumRead);
    if(unlink(argv[1])!=0){
        fprintf(stderr,"E:Cannot unlink file\n");
    }
    
    return 0;
}