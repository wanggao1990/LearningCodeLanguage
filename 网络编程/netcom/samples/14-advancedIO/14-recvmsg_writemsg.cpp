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



int main(){

  /// 1、创建socket
  int socket_fd = socket(AF_INET,SOCK_DGRAM, 0);   // udp
  if (socket_fd == -1){
    LOG("create socket failed. %s", strerror(errno));
    return 1;
  }else{
    LOG("create socket (fd = %d) success.", socket_fd);
  }

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
    iovec iovectobuf;
    iovectobuf.iov_base = buf;
    iovectobuf.iov_len = strlen(buf);

    msghdr msgto;
    memset(&msgto, 0, sizeof(msgto));
    msgto.msg_name = &servaddr;
    msgto.msg_namelen = sizeof(servaddr);
    msgto.msg_iov = &iovectobuf;
    msgto.msg_iovlen = 1; // 1个发送缓冲区iovec

    len = sendmsg(socket_fd, &msgto, 0);
    //len = ::sendto(socket_fd, buf, strlen(buf),0, (sockaddr*)&servaddr, sizeof(servaddr));
    if(len < 0){
      LOG("send failed.Exit. %s", strerror(errno));
      break;
    }
    LOG("send success.");

    // 接收
    memset(buf,0, 20); // buf缓冲区清零，分两段使用

    iovec iovecfrombuf[2];
    iovecfrombuf[0].iov_base = buf;
    iovecfrombuf[0].iov_len = 5;
    iovecfrombuf[1].iov_base = buf+10;
    iovecfrombuf[1].iov_len = 5;

    sockaddr_in clientaddr;

    msghdr msgfrom;
    memset(&msgfrom, 0, sizeof(msgfrom));
    msgfrom.msg_name = &clientaddr;            // 可选择是否需要解析对端地址, NULL为不需要
    msgfrom.msg_namelen = sizeof(clientaddr);  
    msgfrom.msg_iov = iovecfrombuf;
    msgfrom.msg_iovlen = 2; // 2个接收缓冲区iovec

    len = recvmsg(socket_fd, &msgfrom, 0);
    //len = ::recvfrom(socket_fd, buf, sizeof(buf), 0, NULL, NULL);
    if(len < 0){    
      if(errno == EWOULDBLOCK){  // 套接字超时，不退出
        LOG("recv timeout.");
        continue;
      }
      LOG("recv failed. %s", strerror(errno));
      break;
    }

    char client_ip[INET6_ADDRSTRLEN];
    inet_ntop(AF_INET, &clientaddr.sin_addr, client_ip, sizeof(clientaddr));
    int port = ntohs(clientaddr.sin_port);
    LOG("recv %s:%d(%d): msg1=%s, msg2=%s", client_ip, port, len, 
    //LOG("recv (%d): msg1=%s, msg2=%s", len, 
      iovecfrombuf[0].iov_base, iovecfrombuf[1].iov_base);    
  }

  /// 4、关闭连接
  ::close(socket_fd);
}