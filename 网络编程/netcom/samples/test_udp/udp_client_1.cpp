#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>  // sockaddr_in, inet_addr
#include <unistd.h>     // close
#include <cstring>

#include <errno.h>


constexpr const char *SRV_ADDR = "127.0.0.1";
constexpr int SRV_PORT = 8080;

int main()
{
    /// 1、创建socket
    int socket_fd = ::socket(AF_INET, SOCK_DGRAM, 0); // udp
    if(socket_fd == -1){
        printf("%s: create socket failed.\n", __func__);
        return -1;
    }else{
         printf("%s: create socket (fd = %d) success.\n", __func__, socket_fd);
    }

    // 2、 发送到服务端
    sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(8080);

    // //增加connect()功能
    // int ret = ::connect(socket_fd, (const sockaddr*)&servaddr, sizeof(servaddr));
    // if(ret < 0) {
    //     printf("%s: connect failed. %s \n", __func__, strerror(errno));
    //     return 0;
    // }else{
    //     printf("%s: connect %s:%d success.\n", __func__, SRV_ADDR, SRV_PORT);
    // }

    int len ;
    char buf[1024] = "hello sockte!";

    while(1)
    {
        // 发送(已连接的UDP套接字)
        //len = ::write(socket_fd, buf, strlen(buf));
        //len = ::recv(socket_fd, buf, strlen(buf), 0);             //同上
        len = ::sendto(socket_fd, buf, strlen(buf), 0, NULL, 0); //同上

        // 发送（未连接的UDP套接字，不调用connect）
       // len = ::sendto(socket_fd, buf, strlen(buf), 0, (sockaddr*)&servaddr, sizeof(servaddr));
        if(len < 0){
            printf("%s: send failed. %s \n", __func__, strerror(errno));
            return 1;
        }

        // 接收
        len = ::read(socket_fd, buf, strlen(buf));
        //len = ::recv(socket_fd, buf, strlen(buf), 0);
        if(len < 0){
            printf("%s: recv failed. %s \n", __func__, strerror(errno));
            return 1;
        }
        else{
            printf("recv %2d: %s\n", len, buf);
        }

        sleep(1);
    }

   // 3、关闭退出
   ::close(socket_fd);
}
