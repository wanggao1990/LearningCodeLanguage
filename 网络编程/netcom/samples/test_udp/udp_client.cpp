#include <iostream>

#include <sys/socket.h>
#include <arpa/inet.h>      // sockaddr_in, inet_addr
#include <unistd.h>         // close
#include <cstring>

#include <error.h>

//constexpr const char* SRV_ADDR = "localhost";
constexpr const char* SRV_ADDR = "127.0.0.1";
constexpr       int   SRV_PORT = 8080;

constexpr int SOCKET_FAILED = -1;



//void udp_client()
int main()
{
    /// 1、创建socket
    int socket_fd = ::socket(AF_INET, SOCK_DGRAM, 0);   // udp
    if(socket_fd == SOCKET_FAILED){
        printf("%s: create socket failed.\n", __func__);
        exit(1);
    }else{
         printf("%s: create socket (fd = %d) success.\n", __func__, socket_fd);
    }

    /// 2、连接到服务端
    sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(SRV_ADDR);
    servaddr.sin_port = htons(SRV_PORT);

    socklen_t sock_len = sizeof(sockaddr);

    // 2、 发送到服务端
    int len ;
    char buf[1024];
    while (1)
    {
        fgets(buf, sizeof(buf), stdin);
        if(strlen(buf) == 0)
            continue;
        if (strcmp(buf, "exit\n") == 0)
            break;

        // 发送
        len = ::sendto(socket_fd, buf, strlen(buf), 0, (sockaddr*)&servaddr, sock_len);
        if(len < 0){
            printf("%s: send failed. %s \n", __func__, strerror(errno));
            break;
        }

        // 接收
        //len = ::read(socket_fd, buf, strlen(buf));
        //len = ::recv(socket_fd, buf, strlen(buf), 0);
        //len = ::recvfrom(socket_fd, buf, strlen(buf), 0, NULL, NULL);

        sockaddr_in clientaddr;
        socklen_t sc_len;
        len = ::recvfrom(socket_fd, buf, strlen(buf), 0, (sockaddr*)&clientaddr, &sc_len);

        if(len < 0){
            printf("%s: recv failed. %s \n", __func__, strerror(errno));
            break;
        }else if(len == 0){
            printf("server closed.\n");
            break;
        }    
       // buf[len] = 0;

        //fputs(buf, stdout);
       // printf("recv %2d: %s", len, buf);

        else{
            char ip[INET6_ADDRSTRLEN];    
            inet_ntop(clientaddr.sin_family, &clientaddr.sin_addr, ip, sc_len);
            
            int port = ntohs(clientaddr.sin_port);

           // buf[len] = '\0';
            printf("%s: server [%s:%d] recv %2d: %s", __func__, ip, port, len, buf);
        }
    }

   //::close(socket_fd);

   ::shutdown(socket_fd, SHUT_RDWR);   // 输入 exit， udp ?? 实际没有影响？？？ 
}
