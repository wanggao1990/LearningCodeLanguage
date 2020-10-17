#include <stdio.h>
#include <sys/socket.h>
#include <cstring>          // memset, bezro
#include <errno.h>

#include <unistd.h>

#include <arpa/inet.h>    // inet_ntoa

#include "optvalstr.h"

#define OPT_STR(_optname) #_optname

static int test_getoptions()
{
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(fd == -1) {
        printf("%s: create socket failed. %s\n", __func__, strerror(errno));
        return 1;
    }
    else {
        printf("%s: create socket (fd = %d) success.\n", __func__, fd);
    }

    int opt_val;
    socklen_t socklen = sizeof(opt_val);
    int ret = getsockopt(fd, SOL_SOCKET, SO_SNDBUF, &opt_val, &socklen);
    if(ret < 0 ){
        printf("%s: getsockopt failed. %s\n", __func__, strerror(errno));
        return 1;
    }else{
        printf("%s: socket option %s = \n", __func__, OPT_STR(SO_SNDBUF)
            
        );    
    }
}

static void test_getoptions2()
{
    int fd;
    socklen_t len;
    sock_opt val;
    struct sock_opts* ptr;

    for(ptr = sock_opts; ptr->opt_str != NULL; ptr++)
    {
        printf("%s\t", ptr->opt_str);
        if(ptr->opt_val_str == NULL){
            printf("(undefined)\n");
        }else{
            switch(ptr->opt_level){
                case SOL_SOCKET:
                case IPPROTO_IP:
                case IPPROTO_TCP:
                   // fd = ::socket(AF_INET, SOCK_STREAM, 0);
                    fd = ::socket(AF_INET, SOCK_DGRAM, 0);
                    break;
#ifdef IPV6
                case IPPROTO_IPV6:
                    fd = socket(AF_INET6, SOCK_STREAM, 0);
                    break;  
#endif
                default:
                    printf("Can't create fd for level %d. %s\n", ptr->opt_level, strerror(errno));
                    continue;
            }

            len = sizeof(val);
            if(::getsockopt(fd,ptr->opt_level, ptr->opt_name, &val, &len) == -1){
                printf("getsockopt failed. %s\n", strerror(errno));
                //return;
            }else{
                printf("default = %s\n", (*ptr->opt_val_str)(&val,len)); 
            }

            ::close(fd);
        }
    }
}

#include <sys/socket.h>

int getRecvBufferSize(int sock)
{
    int recvSize;
    socklen_t len;
    if (getsockopt(sock, SOL_SOCKET, SO_RCVBUF, &recvSize, &len) == -1) {
        return 0;
    }else {
        printf("套接字的输入缓冲大小是: %d\n",recvSize);
    }
    return recvSize;
}

int getSendBufferSize(int sock)
{
    int sendSize;
    socklen_t len;
    if (getsockopt(sock, SOL_SOCKET, SO_SNDBUF, &sendSize, &len) == -1) {
        return 0;
    }else {
        printf("套接字的输出缓冲大小是: %d\n",sendSize);
    }
    return sendSize;
}



int main()
{
    //int fd = ::socket(AF_INET, SOCK_DGRAM, 0);
   // getSendBufferSize(fd);   // TCP 512k     UDP 160k
   // getRecvBufferSize(fd);   // TCP 1024k    UDP 160k
  


    test_getoptions2();
}