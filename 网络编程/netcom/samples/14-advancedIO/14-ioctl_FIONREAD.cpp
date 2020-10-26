#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h> // sockaddr_in, inet_addr
#include <unistd.h>    // close
#include <cstring>     // memset, bezro, strerror
#include <errno.h>

#include <fcntl.h> // fcntl
#include <signal.h>

#include <time.h>     // localtime
#include <sys/time.h> // gettimeoftoday

#include <sys/ioctl.h> 

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



int main(){

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
  while (1)
  {
    // ioctl查询就绪数据
    int len;
    if(ioctl(socket_fd, FIONREAD, &len) < 0){
      LOG("ioctl FIONREAD failed. %s", strerror(errno));
    }
    if(len<1){
      //LOG("ioctl get bytes to read len=%d", len);
      usleep(1000);
      continue;
    }

    LOG("buf len=%d", len);   
    // 等到数据达到指定长度才进行读取
    if(len < 10) {
      sleep(1);
      continue;
    }

    // 接收
    char buf[100]={}; 
    
    // 方式1
    // len = ::recv(socket_fd, buf, sizeof(buf), 0);  //仅能读取上一次缓冲数据
    // if(len < 0){    
    //   LOG("recv failed. %s", strerror(errno));
    //   break;
    // }
    // LOG("recv (%d): %s",len, buf);
    
    // 方式2
    // len = ::recv(socket_fd, buf, len, MSG_WAITALL); //阻塞模式使用
    // LOG("recv (%d): %s",len, buf);  // 仅能读取上一次的数据，不能读取完全

    // //方式3
    int readN=0;
    while(readN < len){
      int tmpN = ::recv(socket_fd, buf + readN, len, 0);
      readN += tmpN;
    }
    LOG("recv (%d): %s",len, buf);
  }

  /// 4、关闭连接
  ::close(socket_fd);
}
