#include <stdio.h>

#include <sys/socket.h>
#include <arpa/inet.h> // sockaddr_in, inet_addr
#include <unistd.h>  // close
#include <cstring>   // memset, bezro
#include <errno.h>

#include <netinet/tcp.h>  // tcp options

#include <thread>

#include <sys/time.h>

#define LOG(fmt, arg...) \
do{ \
  struct timeval tv; \
  gettimeofday(&tv, NULL); \
  printf("[%ld.%03ld] %s: " fmt, \
         tv.tv_sec, tv.tv_usec / 1000, __func__, ##arg); \
} while (0)

//const char *SRV_ADDR = "127.0.0.1";
const char *SRV_ADDR = "192.168.0.101";
const int SRV_PORT = 8080;


static
void client_service(int sock_id, sockaddr_storage clientaddr, socklen_t sock_len)
{
  if(sock_len == 0){
    sock_len = sizeof(clientaddr);
    getpeername(sock_id, (sockaddr*)&clientaddr, &sock_len); 
  }

  char client_ip[INET6_ADDRSTRLEN]; // 足够存IPv4和IPv6地址
  int port;
  if(sock_len == sizeof(sockaddr_in)){
    sockaddr_in *cliAddr = (sockaddr_in *)&clientaddr;
    //char* client_ip = inet_ntoa(cliAddr->sin_addr);
    inet_ntop(AF_INET, &cliAddr->sin_addr, client_ip, sock_len);
    port = ntohs(cliAddr->sin_port);
    LOG("new socket id = %d, clent %s:%d\n", sock_id, client_ip, port);
  }
  else if(sock_len == sizeof(sockaddr_in6)){
    sockaddr_in6 *cliAddr = (sockaddr_in6 *)&clientaddr;
    inet_ntop(AF_INET6, &cliAddr->sin6_addr, client_ip, sock_len);
    port = ntohs(cliAddr->sin6_port);
    LOG("new socket id = %d, clent %s:%d\n", sock_id, client_ip, port);
  }
  
  // 给已连接套接字设置SO_KEEPALIVE选项
  int keepAlive = 1; // 开启keepalive属性. 缺省值: 0(关闭)
  int ret = setsockopt(sock_id, SOL_SOCKET, SO_KEEPALIVE, &keepAlive, sizeof(keepAlive));
  if(ret < 0) LOG("set SOL_SOCKET, SO_KEEPALIVE failed.\n");
  
  int len;
  char buf[1024];
  while (1)
  {
    len = read(sock_id, buf, sizeof(buf));
    if(len < 0){
      LOG("recv failed. %s\n", strerror(errno));
      break;
    }else if(len == 0){  // tcp 读取长度为0,表示对端关闭连接
      LOG("client socket %d, %s:%d disconnet. recv len = 0.\n", sock_id, client_ip, port);
      break;
    }
    buf[len] = 0; //避免接收数据较上一次短，导致输出显示错误

    if (strcmp(buf, "exit\n") == 0)
      break;

    LOG("recv from socket %d, %s:%d (%d): %s\n", sock_id, client_ip, port, len, buf );

    // // echo 
    // len = ::write(sock_id, buf, strlen(buf));
    // if(len < 0){
    //   LOG("send failed. %s\n", strerror(errno));
    //   break;
    // }
  }
  ::close(sock_id);
}


int main()
{
  /// 1、创建socket
  int socket_fd = socket(AF_INET, SOCK_STREAM, 0); // tcp
  //int socket_fd = ::socket(AF_INET,SOCK_DGRAM, 0);   // udp
  if (socket_fd == -1){
    LOG("create socket failed. %s\n", strerror(errno));
    return 1;
  }
  else{
    LOG("create socket (fd = %d) success.\n", socket_fd);
  }


  ///////  keepalive test
  // 给监听套接字设置SO_KEEPALIVE选项
  int keepAlive = 1; // 开启keepalive属性. 缺省值: 0(关闭)
  int ret = setsockopt(socket_fd, SOL_SOCKET, SO_KEEPALIVE, &keepAlive, sizeof(keepAlive));
  if(ret < 0) LOG("set SOL_SOCKET, SO_KEEPALIVE failed.\n");
  
  int keepIdle = 10; // 如果在10秒内没有任何数据交互,则进行探测..缺省值:7200(s)
  ret = setsockopt(socket_fd, IPPROTO_TCP, TCP_KEEPIDLE, &keepIdle, sizeof(keepIdle));
  if(ret < 0) LOG("set IPPROTO_TCP, SO_KEEPALIVE failed.\n");
  
  int keepInterval = 5; // 探测时发探测包的时间间隔为5秒. 缺省值:75(s)
  ret = setsockopt(socket_fd, IPPROTO_TCP, TCP_KEEPINTVL, &keepInterval, sizeof(keepInterval));
  if(ret < 0) LOG("set IPPROTO_TCP, SO_KEEPALIVE failed.\n");
     
  int keepCount = 3; // 探测重试的次数. 全部超时则认定连接失效..缺省值:9(次)
  ret = setsockopt(socket_fd, IPPROTO_TCP, TCP_KEEPCNT, &keepCount, sizeof(keepCount));
  if(ret < 0) LOG("set IPPROTO_TCP, TCP_KEEPCNT failed.\n");

  /// 2、绑定到本地端口
  sockaddr_in servaddr;
  servaddr.sin_family = AF_INET;
  inet_pton(AF_INET, SRV_ADDR, &servaddr.sin_addr);
  servaddr.sin_port = htons(SRV_PORT);

  //int ret = ::bind(socket_fd, (const sockaddr *)&servaddr, sizeof(servaddr));
  ret = ::bind(socket_fd, (const sockaddr *)&servaddr, sizeof(servaddr));
  if (ret == -1){
    LOG("bind %s:%d failed. %s\n", SRV_ADDR, SRV_PORT, strerror(errno));
    return 1;
  }else{
    LOG("bind %s:%d success.\n", SRV_ADDR, SRV_PORT);
  }


  /// 3、监听
  ret = ::listen(socket_fd, 5);
  if(ret < 0){
    LOG("listen failed. %s\n", strerror(errno));
    return 1;
  }else{
    LOG("listening ...\n");
  }

  while(true)
  {
    // 等待连接
    sockaddr_storage clientaddr;  // 可以满足IPv4和IPv6的内存需求

    // 必须给sock_len初始长度, accept会根据实际情况重新赋值，  这里 128 -> 16
    socklen_t    sock_len = sizeof(clientaddr); 
    int sock_id = ::accept(socket_fd, (sockaddr*)&clientaddr,&sock_len); 

    if(sock_id < 0){
      LOG("accept error. %s\n", strerror(errno));
      return 1;
    }  

    std::thread(client_service,sock_id,clientaddr,sock_len).detach();
  }

  /// 4、关闭连接
  ::close(socket_fd);
}
