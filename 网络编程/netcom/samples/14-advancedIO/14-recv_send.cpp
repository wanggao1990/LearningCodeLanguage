#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h> // sockaddr_in, inet_addr
#include <unistd.h>    // close
#include <cstring>     // memset, bezro, strerror
#include <errno.h>

#include <fcntl.h> // fcntl
#include <signal.h>

#include <time.h>     //localtime
#include <sys/time.h>

#define LOG(fmt, arg...)                                                       \
    do                                                                         \
    {                                                                          \
        struct timeval tv;                                                     \
        gettimeofday(&tv, NULL);                                               \
        char tmpbuf[10];                                                       \
        strftime(tmpbuf, 10, "%H:%M:%S", localtime(&tv.tv_sec));               \
        printf("[%s.%06d] %s: " fmt "\n", tmpbuf, tv.tv_usec, __func__, ##arg);\
    } while (0)

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



static int main_udp(){

  /// 1、创建socket
 // int socket_fd = socket(AF_INET,SOCK_STREAM, 0);   // tcp
  int socket_fd = socket(AF_INET,SOCK_DGRAM, 0);   // udp
  if (socket_fd == -1){
    LOG("create socket failed. %s", strerror(errno));
    return 1;
  }else{
    LOG("create socket (fd = %d) success.", socket_fd);
  }

  /// 2、连接服务端
  const char *SRV_ADDR = "127.0.0.1";
  const int SRV_PORT = 8080;

  sockaddr_in servaddr;
  servaddr.sin_family = AF_INET;
  inet_pton(servaddr.sin_family, SRV_ADDR, &servaddr.sin_addr);
  servaddr.sin_port = htons(SRV_PORT);

  if(::bind(socket_fd, (sockaddr*)&servaddr, sizeof(servaddr)) < 0){
    LOG("bind %s:%d failed. %s\n", SRV_ADDR, SRV_PORT, strerror(errno));
    return 1;
  }else{
    LOG("bind %s:%d success.\n", SRV_ADDR, SRV_PORT);
  }
  

  // 3、 发送到服务端
  int len ;
  char buf[100]={}; 
  while (1)
  {
    // 接收
    len = ::recv(socket_fd, buf, sizeof(buf), MSG_PEEK);  //阻塞以等待数据到来
    if(len < 0){    
      LOG("recv failed. %s", strerror(errno));
      break;
    }
    LOG("recv (%d) one: %s",len, buf);

    int buf2[100]={};
    len = ::recv(socket_fd, buf2, len, 0); // 读取已就绪的数据，长度为len
    if(len < 0){    
      LOG("recv failed. %s", strerror(errno));
      break;
    }
    LOG("recv (%d) two: %s\n",len, buf2);

   // break;
  }

  /// 4、关闭连接
  ::close(socket_fd);
}



static int main_tcp(){

  /// 1、创建socket
  int socket_fd = socket(AF_INET,SOCK_STREAM, 0);   // tcp
  //int socket_fd = socket(AF_INET,SOCK_DGRAM, 0);   // udp
  if (socket_fd == -1){
    LOG("create socket failed. %s", strerror(errno));
    return 1;
  }else{
    LOG("create socket (fd = %d) success.", socket_fd);
  }

  /// 2、连接服务端
  const char *SRV_ADDR = "127.0.0.1";
  const int SRV_PORT = 8080;

  sockaddr_in servaddr;
  servaddr.sin_family = AF_INET;
  inet_pton(servaddr.sin_family, SRV_ADDR, &servaddr.sin_addr);
  servaddr.sin_port = htons(SRV_PORT);

  if(::bind(socket_fd, (sockaddr*)&servaddr, sizeof(servaddr)) < 0){
    LOG("bind %s:%d failed. %s", SRV_ADDR, SRV_PORT, strerror(errno));
    return 1;
  }else{
    LOG("bind %s:%d success.", SRV_ADDR, SRV_PORT);
  }

  int ret = ::listen(socket_fd,5);
  if(ret == -1){
    LOG("%s: listen failed. %s", __func__, strerror(errno));
      return 1;
  }else{     
    LOG("%s: listening ...", __func__);
  }

  int sock_id = ::accept(socket_fd, NULL, NULL); 
  if(sock_id < 0){
    LOG("accept error. %s", strerror(errno));
    return 1;
  }  
  

  // 3、 发送到服务端
  int len ;
  char buf[100]={}; 
  while (1)
  {
    // 接收
    len = ::recv(sock_id, buf, sizeof(buf), MSG_PEEK);  //阻塞以等待数据到来
    if(len < 0){    
      LOG("recv failed. %s", strerror(errno));
      break;
    }
    LOG("recv (%d) one: %s",len, buf);

    sleep(1);

    // int buf2[100]={};
    // len = ::recv(sock_id, buf2, sizeof(buf2), 0);  // 读取已就绪的数据，长度为len
    // if(len < 0){    
    //   LOG("recv failed. %s", strerror(errno));
    //   break;
    // }
    // LOG("recv (%d) two: %s\n",len, buf2);

   // break;
  }
  ::close(sock_id);

  /// 4、关闭连接
  ::close(socket_fd);
}



int main()
{
  //main_udp();
  main_tcp();
}