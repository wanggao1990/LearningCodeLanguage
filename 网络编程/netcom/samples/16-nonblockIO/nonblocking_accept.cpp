#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h> // sockaddr_in, inet_addr
#include <unistd.h>    // close
#include <cstring>     // memset, bezro, strerror
#include <errno.h>

#include <fcntl.h> // fcntl

#include <time.h>     // localtime
#include <sys/time.h> // gettimeoftoday

#define LOG(fmt, arg...)                                                    \
  do{                                                                       \
    struct timeval tv;                                                      \
    gettimeofday(&tv, NULL);                                                \
    char tmpbuf[10];                                                        \
    strftime(tmpbuf, 10, "%H:%M:%S", localtime(&tv.tv_sec));                \
    printf("[%s.%06d] %s: " fmt "\n", tmpbuf, tv.tv_usec, __func__, ##arg); \
  } while (0)

//const char *SRV_ADDR = "127.0.0.1";
const char *SRV_ADDR = "192.168.3.100";
int SRV_PORT = 8080;

static int setNonblocking(int fd, int enable = 1)
{
  int flags;
  if (flags = fcntl(fd, F_GETFL, 0) < 0){
    perror("");
    return -1;
  }
  // 开启或关闭
  if (enable == 0)  flags &= ~O_NONBLOCK;
  else              flags |= O_NONBLOCK;

  if (fcntl(fd, F_SETFL, flags) < 0){
    perror("");
    return -1;
  }
  return 0;
}


static int client_RST()
{
  /// 1、创建socket
  int socket_fd = socket(AF_INET,SOCK_STREAM, 0);   // tcp
  if (socket_fd == -1){
    LOG("create socket failed. %s", strerror(errno));
    return 1;
  }else{
    LOG("create socket (fd = %d) success.", socket_fd);
  }

  /// 2、连接服务器
  sockaddr_in servaddr;
  servaddr.sin_family = AF_INET;
  inet_pton(servaddr.sin_family, SRV_ADDR, &servaddr.sin_addr);
  servaddr.sin_port = htons(SRV_PORT);

  int ret = ::connect(socket_fd, (const sockaddr *)&servaddr, sizeof(servaddr));
  if (ret == -1){
    LOG("connect %s:%d failed. %s", SRV_ADDR, SRV_PORT, strerror(errno));
    return 1;
  }else{
    LOG("connect %s:%d success.", SRV_ADDR, SRV_PORT);
  }

  // 3、模拟的中止连接，发送RST
  struct linger ling;
  ling.l_onoff = 1; 
  ling.l_linger = 0;

  // wsl 18.04实测设置成功后.调用close不发送RST （ununtu16.04 实体机可行）
  ret = setsockopt(socket_fd, SOL_SOCKET, SO_LINGER, &ling, sizeof(ling));
  if (ret < 0){
     LOG("setsockopt SO_LINGER failed. %s", strerror(errno));
  }

  close(socket_fd);   // 套接字上不能发送和读写; 发送RST到服务端; 不进入TIME_WAIT状态

  return 0;
}


static int server_accept()
{
  /// 1、创建socket
  int socket_fd = socket(AF_INET,SOCK_STREAM, 0);   // tcp
  if (socket_fd == -1){
    LOG("create socket failed. %s", strerror(errno));
    return 1;
  }else{
    LOG("create socket (fd = %d) success.", socket_fd);
  }

  /// 2、绑定到本地端口
  sockaddr_in servaddr;
  servaddr.sin_family = AF_INET;
  inet_pton(servaddr.sin_family, SRV_ADDR, &servaddr.sin_addr);
  servaddr.sin_port = htons(SRV_PORT);

  int ret = ::bind(socket_fd, (const sockaddr *)&servaddr, sizeof(servaddr));
  if (ret == -1){
    LOG("bind %s:%d failed. %s.", SRV_ADDR, SRV_PORT, strerror(errno));
    return 1;
  }else{
    LOG("bind %s:%d success.", SRV_ADDR, SRV_PORT);}

  /// 3、监听
  ret = ::listen(socket_fd,5);
  if(ret == -1){
    LOG("listen failed. %s", strerror(errno));
    return 1;
  }else{     
    LOG("listening ...");
  }

  /// 4、等待连接 nonblocking accept
  {
    fd_set  rset;
    timeval tval;

    while(true)
    {
      FD_ZERO(&rset);
      FD_SET(socket_fd, &rset);
      tval.tv_sec = 5;
      tval.tv_usec = 0;

      int n=select(socket_fd+1, &rset, NULL, NULL, &tval);
      if(n == 0){
        errno = ETIMEDOUT;
        usleep(1000);
        continue;
      }
      else{
        if(FD_ISSET(socket_fd, &rset)){   // 新的连接

          LOG("listening socket readable.");
          sleep(5);

          setNonblocking(socket_fd,1); //开启非阻塞, 否则当前accept可能阻塞

          sockaddr_in clientaddr;
          socklen_t socklen = sizeof(clientaddr);
          int sock_id = ::accept(socket_fd, (sockaddr*)&clientaddr, &socklen); 
          if(sock_id < 0)
          {
            LOG("accept error. %s", strerror(errno));

            if(errno == EAGAIN || errno == EWOULDBLOCK || errno == ECONNABORTED || 
               errno == EPROTO || errno == EINTR)
            {
              LOG("accept ignore error. %s", strerror(errno));
              continue;
            }else{
              return -1;
            } 
          }else{
            LOG("accept success.");
          }
          
          setNonblocking(socket_fd,0); // 关闭非阻塞

          char ip[INET6_ADDRSTRLEN];
          inet_ntop(clientaddr.sin_family, &clientaddr.sin_addr, ip, socklen);
          int port = ntohs(clientaddr.sin_port);
          LOG("accept client [%s:%d]", ip, port);

        }else{
          LOG("select other event.");
        }
      }
    }
  }
  /// 5、关闭连接
  ::close(socket_fd);

  return 0;
}

int main()
{
  

  //client_RST();
  server_accept();
}
