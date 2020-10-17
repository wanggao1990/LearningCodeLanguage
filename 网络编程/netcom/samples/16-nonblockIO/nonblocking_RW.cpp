#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h> // sockaddr_in, inet_addr
#include <unistd.h>  // close
#include <cstring>   // memset, bezro, strerror
#include <errno.h>

#include <fcntl.h>  // fcntl

#include <sys/time.h>

#define LOG(fmt, arg...) \
do{ \
  struct timeval tv; \
  gettimeofday(&tv, NULL); \
  printf("[%ld.%d] %s: " fmt, tv.tv_sec, tv.tv_usec, __func__, ##arg); \
} while (0)


const char *SRV_ADDR = "127.0.0.1";
int SRV_PORT = 8080;


static int setNonblocking(int fd, int enable)
{
    int flags;
    if(flags = fcntl(fd, F_GETFL, 0) < 0){
        perror("");
        return -1;
    }
    // 开启或关闭
    if(enable == 0) flags &= ~O_NONBLOCK;
    else            flags |= O_NONBLOCK;

    if(fcntl(fd, F_SETFL, flags) < 0){
        perror("");
        return -1;
    }
    return 0;
}



int main()
{
    /// 1、创建socket
    int socket_fd = socket(AF_INET,SOCK_DGRAM, 0);   // udp
    //int socket_fd = socket(AF_INET,SOCK_STREAM, 0);   // tcp
    if(socket_fd == -1) {
        LOG("create socket failed. %s\n", strerror(errno));
        return 1;
    }
    else {
        LOG("create socket (fd = %d) success.\n", socket_fd);
    }

    // 设置非阻塞
    setNonblocking(socket_fd, 1);

    /// 2、绑定到本地端口
    sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    inet_pton(servaddr.sin_family, SRV_ADDR, &servaddr.sin_addr);
    servaddr.sin_port = htons(SRV_PORT);

    int ret = ::bind(socket_fd, (const sockaddr *)&servaddr, sizeof(servaddr));
    if (ret == -1){
        LOG("bind %s:%d failed.\n", SRV_ADDR, SRV_PORT);
        return 1;
    }
    else{
        LOG("bind %s:%d success.\n", SRV_ADDR, SRV_PORT);
    }

        /// 3、等待接收和响应
    char buf[1024]; // 发送
             
    sockaddr_in clientaddr;
    socklen_t   socklen = sizeof(clientaddr);

    while (1)
    {
        //int len = ::read(socket_fd, buf, sizeof(buf));
        //int len = ::recv(socket_fd, buf, sizeof(buf), 0);  
        //int len = ::recvfrom(socket_fd, buf, sizeof(buf), 0,  NULL, NULL);
        int len = ::recvfrom(socket_fd, buf, sizeof(buf), 0, (struct sockaddr *)&clientaddr, &socklen);

        if (len < 0){
            LOG("recv failed. err %d (%s) \n", errno, strerror(errno));
           // break;    
           if(errno == EAGAIN) continue;
        }
        else{
            char ip[INET6_ADDRSTRLEN];    
            inet_ntop(clientaddr.sin_family, &clientaddr.sin_addr, ip, socklen);
            
            int port = ntohs(clientaddr.sin_port);

            buf[len] = '\0';
            LOG("client [%s:%d] recv %2d: %s\n", ip, port, len, buf);
        }

        //buf[len] = '\0';

        if (strcmp(buf, "exit") == 0)
            break;

        // //len = ::write(socket_fd, buf, sizeof(buf));
        // //len = ::send(socket_fd, buf, sizeof(buf), 0);
        // len = ::sendto(socket_fd, buf, sizeof(buf), 0, (struct sockaddr *)&clientaddr, socklen);
        // if (len < 0)
        // {
        //     LOG("send failed. err %s \n", strerror(errno));
        //     break;
        // }
        // else if (len == 0)
        // {
        //     LOG("send len = 0. \n");
        //     break;
        // }
    }

    /// 4、关闭连接
    ::close(socket_fd);
}