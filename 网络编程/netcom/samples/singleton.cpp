#include <stdio.h>
#include <unistd.h>  // getpid
#include <fcntl.h>
#include <errno.h>
#include <cstring>


#define PID_FILE    "/tmp/singleton.pid"
    
static int check_singleton()
{  
    struct flock lock;

    int fd = open(PID_FILE,  O_RDWR|O_CREAT,  S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
    if (fd < 0 ) {
       // printf("open pid file failed. %s\n", strerror(errno));  
        return -1;
    }

    if (fcntl(fd, F_GETLK, &lock) < 0) {
       // printf("fcntl F_GETLK failed. %s\n", strerror(errno));  
        return -1;
    }
    if (lock.l_type != F_UNLCK) {
       // printf("pid file status is not F_UNLCK. %s\n", strerror(errno));  
        return -1;
    }
    lock.l_type = F_WRLCK;
    lock.l_pid = getpid();
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    if (fcntl(fd, F_SETLKW, &lock) < 0) {
        //printf("fcntl F_SETLKW failed. %s\n", strerror(errno));  
        return -1;
    }

    return  0;
}

int main()
{

    if(check_singleton() != 0){
        printf("already running...\n");  
        return -1;
    }

    printf("hello check_singleton\n");  
    printf("press to exit.");
    getchar();

    return 0;
}