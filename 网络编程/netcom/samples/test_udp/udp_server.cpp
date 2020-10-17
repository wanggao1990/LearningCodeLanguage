#include <stdio.h>

#include <sys/socket.h>
#include <arpa/inet.h> // sockaddr_in, inet_addr
#include <unistd.h>    // close
#include <cstring>

#include <errno.h>


//constexpr const char* SRV_ADDR = "localhost";
constexpr const char *SRV_ADDR = "127.0.0.1";
constexpr int SRV_PORT = 8080;

constexpr int SOCKET_FAILED = -1;

//void udp_server()
int main()
{
    /// 1、创建socket
    int socket_fd = ::socket(AF_INET, SOCK_DGRAM, 0); // udp
    if (socket_fd == SOCKET_FAILED)
    {
        printf("%s: create socket failed.\n", __func__);
        return 1;
    }
    else
    {
        printf("%s: create socket (fd = %d) success.\n", __func__, socket_fd);
    }

    /// 2、绑定到本地端口
    sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    //servaddr.sin_addr.s_addr = inet_addr(SRV_ADDR);
    inet_pton(servaddr.sin_family, SRV_ADDR, &servaddr.sin_addr);
    servaddr.sin_port = htons(SRV_PORT);

    int ret = ::bind(socket_fd, (const sockaddr *)&servaddr, sizeof(servaddr));
    if (ret == -1){
        printf("%s: bind %s:%d failed.\n", __func__, SRV_ADDR, SRV_PORT);
        return 1;
    }
    else{
        printf("%s: bind %s:%d success.\n", __func__, SRV_ADDR, SRV_PORT);
    }

    /// 3、等待接收和响应
    char buf[1024]; // 发送
             
    sockaddr_in clientaddr;
    socklen_t   socklen = sizeof(clientaddr);

    while (1)
    {
       // int len = ::read(socket_fd, buf, sizeof(buf));
       //  int len = ::recv(socket_fd, buf, sizeof(buf), 0);  

        // 不关心数据发送者的协议地址,后面两个参数指定为空指针， 效果同上
       // int len = ::recvfrom(socket_fd, buf, sizeof(buf), 0,  NULL, NULL);
    
        int len = ::recvfrom(socket_fd, buf, sizeof(buf), 0, (struct sockaddr *)&clientaddr, &socklen);

        if (len < 0){
            printf("%s: recv failed. err %s \n", __func__, strerror(errno));
            break;
        
        }
        else{
            char ip[INET6_ADDRSTRLEN];    
            inet_ntop(clientaddr.sin_family, &clientaddr.sin_addr, ip, socklen);
            
            int port = ntohs(clientaddr.sin_port);

            buf[len] = '\0';
            printf("%s: client [%s:%d] recv %2d: %s", __func__, ip, port, len, buf);
        }

        //buf[len] = '\0';

        if (strcmp(buf, "exit\n") == 0)
            break;

        //len = ::write(socket_fd, buf, sizeof(buf));
        //len = ::send(socket_fd, buf, sizeof(buf), 0);
        len = ::sendto(socket_fd, buf, sizeof(buf), 0, (struct sockaddr *)&clientaddr, socklen);
        if (len < 0)
        {
            printf("%s: send failed. err %s \n", __func__, strerror(errno));
            break;
        }
        else if (len == 0)
        {
            printf("%s: send len = 0. \n", __func__);
            break;
        }
    }

    /// 4、关闭连接
    ::close(socket_fd);
}
