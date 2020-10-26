#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h> // sockaddr_in, inet_addr
#include <unistd.h>    // close
#include <cstring>     // memset, bezro, strerror
#include <errno.h>

#include <fcntl.h> // fcntl
#include <signal.h>

#include <sys/time.h>


#define LOG(fmt, arg...)                                                            \
    do                                                                              \
    {                                                                               \
        struct timeval tv;                                                          \
        gettimeofday(&tv, NULL);                                                    \
        printf("[%ld.%06d] %s: " fmt "\n", tv.tv_sec, tv.tv_usec, __func__, ##arg); \
    } while (0)



static int setsockopt_rcvtimeo(int fd, int sec)
{
  timeval tv;
  tv.tv_sec = sec;
  tv.tv_usec = 0;
  return setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
}

int main()
{
  /// 1、创建socket
  int socket_fd = socket(AF_INET,SOCK_DGRAM, 0);   // udp
  if (socket_fd == -1){
    LOG("create socket failed. %s", strerror(errno));
    return 1;
  }else{
    LOG("create socket (fd = %d) success.", socket_fd);
  }

  // 套接字接收超时设置
  setsockopt_rcvtimeo(socket_fd, 5);

  /// 2、连接服务端
  sockaddr_in servaddr;
  servaddr.sin_family = AF_INET;
  inet_pton(servaddr.sin_family, "127.0.0.1", &servaddr.sin_addr);
  servaddr.sin_port = htons(8080);

  // 3、 发送到服务端
  int len ;
  char buf[1024]; 
  while (1)
  {
    printf("send: ");
    fgets(buf, sizeof(buf), stdin);   // 等待用户输入
    if (strcmp(buf, "exit") == 0)
      break;


    // 发送
    len = ::sendto(socket_fd, buf, strlen(buf),0, (sockaddr*)&servaddr, sizeof(servaddr));
    if(len < 0){
      LOG("send failed.Exit. %s", strerror(errno));
      break;
    }
    LOG("send success.");

    // 接收
    len = ::recvfrom(socket_fd, buf, sizeof(buf), 0, NULL, NULL);
    if(len < 0){    
      if(errno == EWOULDBLOCK){  // 套接字超时，不退出
        LOG("recv timeout.");
        continue;
      }
      LOG("recv failed. %s", strerror(errno));
      break;
    }
    LOG("recv (%d): %s", len, buf);    
  }

  /// 4、关闭连接
  ::close(socket_fd);
}