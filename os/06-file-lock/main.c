#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main(int argc,char* argv[]){
    int fd;
    char buffer[255];
    struct flock fvar;
    if(argc==1){
        printf("Usage: %s <filename>\n",argv[0]);return 1;
    }
    if((fd = open(argv[1],O_RDWR) )==-1){
        fprintf(stderr,"Error opening\n");return 1;
    }
    fvar.l_type = F_WRLCK;
    fvar.l_whence = SEEK_SET;
    fvar.l_start = 0;
    fvar.l_len = 100;

    if((fcntl(fd,F_SETLK,&fvar))==0){
        sleep(20);
    }else{
        fcntl(fd,F_GETLK,&fvar);
        printf("File already claimed by (%d)\n",fvar.l_pid);
        return 1;
    }

    printf("Press any key to remove lock\n");
    getchar();

    if((fcntl(fd,F_UNLCK,&fvar))==-1){
        fprintf(stderr,"Error unlocking\n");
        return 1;
    }
    printf("Unlocked\n");
    close(fd);

    return 0;
}