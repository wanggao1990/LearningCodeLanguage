#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h> // sockaddr_in, inet_addr
#include <unistd.h>  // close
#include <cstring>   // memset, bezro
#include <errno.h>

#include <sys/time.h>

#define LOG(fmt, arg...) \
do{ \
  struct timeval tv; \
  gettimeofday(&tv, NULL); \
  printf("[%ld.%03ld] %s: " fmt, \
         tv.tv_sec, tv.tv_usec / 1000, __func__, ##arg); \
} while (0)

const char *SRV_ADDR = "127.0.0.1";
const int SRV_PORT = 8080;

int enableReuseAddr(int sock)
{
    int optval = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1)
        return -1;
    return 0;
}

int main()
{
    /// 1、创建socket
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0); // tcp
    //int socket_fd = ::socket(AF_INET,SOCK_DGRAM, 0);   // udp
    if (socket_fd == -1) {
        LOG("create socket failed. %s\n", strerror(errno));
        return 1;
    }else{
        LOG("create socket (fd = %d) success.\n", socket_fd);
    }

    if(enableReuseAddr(socket_fd)<0)
        LOG("set reuseaddr failed. %s\n", strerror(errno));

    /// 2、绑定到本地端口
    sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, SRV_ADDR, &servaddr.sin_addr);
    servaddr.sin_port = htons(SRV_PORT);

    int ret = ::bind(socket_fd, (const sockaddr *)&servaddr, sizeof(servaddr));
    if (ret == -1)
    {
        LOG("bind %s:%d failed. %s\n", SRV_ADDR, SRV_PORT, strerror(errno));
        return 1;
    }else {
        LOG("bind %s:%d success.\n", SRV_ADDR, SRV_PORT);
    }

    getchar();

    close(socket_fd);
}