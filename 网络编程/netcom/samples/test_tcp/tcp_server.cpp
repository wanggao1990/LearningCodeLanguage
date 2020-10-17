#include <stdio.h>

#include <sys/socket.h>
#include <arpa/inet.h>      // sockaddr_in, inet_addr
#include <unistd.h>         // close
#include <cstring>
#include <errno.h>

#include <thread>

//constexpr const char* SRV_ADDR = "localhost";
constexpr const char* SRV_ADDR = "127.0.0.1";
constexpr       int   SRV_PORT = 8080;


static
void client_service(int sock_id, sockaddr_storage clientaddr, socklen_t sock_len)
{
    // 如果sock_len为0， 说明 accept的对端地址参数传入为NULL，需要使用getpeername获取对端信息
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
        printf("new socket id = %d, clent %s:%d\n", sock_id, client_ip, port);
    }
    else if(sock_len == sizeof(sockaddr_in6)){
        sockaddr_in6 *cliAddr = (sockaddr_in6 *)&clientaddr;
        inet_ntop(AF_INET6, &cliAddr->sin6_addr, client_ip, sock_len);
        port = ntohs(cliAddr->sin6_port);
        printf("new socket id = %d, clent %s:%d\n", sock_id, client_ip, port);
    }

    int len;
    char buf[1024];
    while (1)
    {
        len = read(sock_id, buf, sizeof(buf));
        if(len < 0){
            printf("%s: recv failed. %s\n", __func__, strerror(errno));
            break;
        }else if(len == 0){  // tcp 读取长度为0,表示对端关闭连接
            printf("%s: client socket %d, %s:%d disconnet. recv len = 0.\n", 
                    __func__, sock_id, client_ip, port);
            break;
        }
        buf[len] = 0; //避免接收数据较上一次短，导致输出显示错误

        if (strcmp(buf, "exit\n") == 0)
            break;

        printf("recv from socket %d, %s:%d (%d): %s\n", sock_id, client_ip, port, len, buf );

        // echo 
        len = ::write(sock_id, buf, strlen(buf));
        if(len < 0){
            printf("%s: send failed. %s\n", __func__, strerror(errno));
            break;
        }
    }
    ::close(sock_id);
}

int enableReuseAddr(int sock)
{
    int optval = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1)
        return -1;
    return 0;
}


int main()
{
    /// 1、创建socket
    int socket_fd = socket(AF_INET,SOCK_STREAM, 0);   // tcp
    //int socket_fd = ::socket(AF_INET,SOCK_DGRAM, 0);   // udp
    if(socket_fd == -1){
        printf("%s: create socket failed. %s\n", __func__, strerror(errno));
        return 1;
    }else{
         printf("%s: create socket (fd = %d) success.\n", __func__, socket_fd);
    }

    int optval;
    socklen_t optlen = sizeof(optval);
     if (getsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &optval, &optlen) == 0 ){
        printf("reuseaddr: %s\n", optval == 0 ? "false":"true");
     }

    // if(enableReuseAddr(socket_fd)<0)
        // printf("set reuseaddr failed. %s\n", strerror(errno));
    

    /// 2、绑定到本地端口
    sockaddr_in servaddr;
    //memset(&servaddr, 0, sizeof(sockaddr_in));   // string.h
    //bzero(&servaddr, sizeof(sockaddr_in));        // strings.h
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET,SRV_ADDR, &servaddr.sin_addr);
    servaddr.sin_port = htons(SRV_PORT);

    int ret = ::bind(socket_fd, (const sockaddr*)&servaddr, sizeof(servaddr));
    if(ret == -1){
        printf("%s: bind %s:%d failed. %s\n", __func__, SRV_ADDR, SRV_PORT, strerror(errno));
        return 1;
    }else{     
        printf("%s: bind %s:%d success.\n", __func__, SRV_ADDR, SRV_PORT);
    }

    /// 3、监听
    ret = ::listen(socket_fd,5);
    if(ret == -1){
        printf("%s: listen failed. %s\n", __func__, strerror(errno));
        return 1;
    }else{     
        printf("%s: listening ...\n", __func__);
    }

    while(true){

        // 等待连接
        sockaddr_storage clientaddr;  // 可以满足IPv4和IPv6的内存需求

        // 必须给sock_len初始长度, accept会根据实际情况重新赋值，  这里 128 -> 16
        socklen_t        sock_len = sizeof(clientaddr); 
        int sock_id = ::accept(socket_fd, (sockaddr*)&clientaddr,&sock_len); 

        if(sock_id < 0){
            printf("%s: accept error. %s\n", __func__, strerror(errno));
             return 1;
        }  

        // // 有新的连接就开辟一个线程
        // std::thread([=]{
        //     // char* client_ip = inet_ntoa(clientaddr.sin_addr);
        //     // printf("new socket id = %d, clent %s\n", sock_id, client_ip);
        //
        //     // 获取对端信息
        //     socklen_t  sock_len;
        //     getpeername(sock_id, (sockaddr*)&clientaddr, &sock_len); 
        //
        //     //const char* client_ip = inet_ntoa(clientaddr.sin_addr);
        //     char client_ip[20];
        //     if()
        //     inet_ntop(clientaddr.sin_family, )
        //
        //     int client_port = ntohs(clientaddr.sin_port);
        //     printf("new socket id = %d, clent %s:%d\n", sock_id, client_ip, client_port);
        //
        //     int len;
        //     char buf[1024]; // 发送
        //
        //     while (1)
        //     {
        //         len = read(sock_id, buf, sizeof(buf), 0);
        //         if(len < 0){
        //             printf("%s: recv failed. \n", __func__);
        //             break;
        //         }else if(len == 0){  // tcp 读取长度为0,表示对端关闭连接
        //             printf("%s: client socket %d, %s disconnet. recv len = 0. \n", 
        //                 __func__, sock_id, client_ip );
        //             break;
        //         }
        //         buf[len] = '\0';
        //
        //         if (strcmp(buf, "exit\n") == 0)
        //             break;
        //
        //         printf("recv from socket %d, %s (%d): %s", sock_id, client_ip, len, buf );
        //
        //         // echo 
        //         memcpy(buf + len - 1, "(echo)", 7);
        //         len = ::write(sock_id, buf, strlen(buf), 0);
        //         if(len < 0){
        //             printf("%s: send failed. \n", __func__);
        //             break;
        //         }
        //     }
        //     ::close(sock_id);
        // }).detach();


        std::thread(client_service,sock_id,clientaddr,sock_len).detach();
    }

    /// 4、关闭连接
    ::close(socket_fd);



}

