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

const char *SRV_ADDR = "127.0.0.1";
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

static int connect_nonb(int sockfd, const sockaddr* pServAddr, socklen_t socklen, int nsec)
{
  int n, error = 0;

  setNonblocking(sockfd); //设置套接字为非阻塞

  if( (n=connect(sockfd, pServAddr, socklen)) < 0 ){
    if(errno != EINPROGRESS) return -1;
  }

  if(n == 0)
    goto done;

  fd_set  rset, wset;
  timeval tval;

  FD_ZERO(&rset);
  FD_SET(sockfd, &rset);
  wset = rset;
  tval.tv_sec = nsec;
  tval.tv_usec = 0;

  if( (n=select(sockfd+1, &rset, &wset, NULL, nsec ? &tval: NULL)) == 0){
    close(sockfd);
    error = ETIMEDOUT;
    return -1;
  }

  if(FD_ISSET(sockfd, &rset) || FD_ISSET(sockfd, &wset)){
    socklen_t len = sizeof(error);
    if( getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, &len) < 0){
      LOG("getsockopt failed. %s.", strerror(errno));
      return -1;
    }
  }else{
    LOG("select error: sock not set. %s.", strerror(errno));
    return -1;
  }

done:
  setNonblocking(sockfd,0); // 清除非阻塞标志

  if(error){
    close(sockfd);
    errno = error;
     LOG("error: %s.", strerror(errno));
    return -1;
  }
  return 0;
}

int main()
{
      /// 1、创建socket
  //int socket_fd = socket(AF_INET, SOCK_DGRAM, 0); // udp
  int socket_fd = socket(AF_INET,SOCK_STREAM, 0);   // tcp
  if (socket_fd == -1){
    LOG("create socket failed. %s", strerror(errno));
    return 1;
  }else{
    LOG("create socket (fd = %d) success.", socket_fd);
  }

  // 设置非阻塞
  //setNonblocking(socket_fd, 1);

  /// 2、连接服务器
  sockaddr_in servaddr;
  servaddr.sin_family = AF_INET;
  inet_pton(servaddr.sin_family, SRV_ADDR, &servaddr.sin_addr);
  servaddr.sin_port = htons(SRV_PORT);

  if( connect_nonb(socket_fd, (const sockaddr*)&servaddr, sizeof(servaddr), 5) < 0){
    return 0;
  }

  char buf[1024]={}; 
  int len;

 while (1)
  {
    len = ::send(socket_fd, buf, 100, 0);
    if (len < 0){
        LOG("send failed. err %s.", strerror(errno));
        if(errno == EAGAIN){
          usleep(100*1000); // 演示需要，实际根据情况给一定的延时
          continue;
        }else{
          LOG("send failed. err %s.", strerror(errno));
          break;
        }
    }else if(len == 0){
      LOG("server closed.");
      break;
    }

    LOG("send success.");

    sleep(3);
  }

  /// 4、关闭连接
  ::close(socket_fd);
}