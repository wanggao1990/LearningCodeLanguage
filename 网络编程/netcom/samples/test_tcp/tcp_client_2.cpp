#include <iostream>

#include <sys/socket.h>
#include <arpa/inet.h>      // sockaddr_in, inet_addr
#include <unistd.h>         // close
#include <cstring>

#include <thread>

//constexpr const char* SRV_ADDR = "localhost";
constexpr const char* SRV_ADDR = "127.0.0.1";
constexpr       int   SRV_PORT = 8080;


int main()
{
    /// 1、创建socket
    auto creat_socket = []{
        int socket_fd = socket(AF_INET,SOCK_STREAM, 0);   // tcp
        if(socket_fd == -1){
            printf("%s: create socket failed.\n", __func__);
            //exit(1);
        }else{
            printf("%s: create socket (fd = %d) success.\n", __func__, socket_fd);
        }
        return socket_fd;
    };

    int socket_fd = creat_socket();
    if(socket_fd == -1)
        exit(1);

    /// 2、连接到服务端
    sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(SRV_ADDR);
    servaddr.sin_port = htons(SRV_PORT);

    socklen_t sock_len = sizeof(sockaddr);

    auto tcp_connect = [=](int socket_fd){
     
        int ret = ::connect(socket_fd, (sockaddr*)&servaddr, sock_len);
        if(ret < 0) {
            printf("%s: connect failed.\n", __func__);
          //  exit(1);
        }else{
            printf("%s: connect %s:%d success.\n", __func__, SRV_ADDR, SRV_PORT);

            sockaddr_in localaddr;
            getsockname(socket_fd, (sockaddr*)&localaddr, (socklen_t *)&sock_len);
            printf("local addr: %s:%d\n", inet_ntoa(localaddr.sin_addr), ntohs(localaddr.sin_port));
        }

        return ret;
    };


    while(true){

        //  不断尝试连接
        int ret = tcp_connect(socket_fd);
        if(ret < 0){
           // std::this_thread::sleep_for()
           sleep(1);
           continue;
        }

        // 发送和接收
        bool bConnected = true; // atomic

        std::thread recvThread = std::thread([=, &bConnected]{
            int len ;
            char buf[1024]; 
            while(bConnected)
            {
                len = ::recv(socket_fd, buf, sizeof(buf), 0);
                if(len < 0){
                    printf("server failed.\n");
                    bConnected = false;   // 后面的sendThread等待输入才能退出
                    break;
                }else if(len == 0){
                    printf("server closed.\n");
                    bConnected = false;
                    break;
                }else{
                    buf[len] = '\0';
                    printf("recv (%d): %s\n", len, buf);
                }
            }
        });

        std::thread sendThread = std::thread([=, &bConnected]{
            int len ;
            char buf[1024]; 
            while(bConnected)
            {
                fgets(buf, sizeof(buf), stdin);
                if (strcmp(buf, "exit\n") == 0)
                    break;   
                    //TODO     测试退出后  shutdown 之后是否影响其他进程

                len = ::send(socket_fd, buf, strlen(buf), 0);
                if(len < 0){
                    printf("send failed.Exit.\n");
                    break;
                }
            }   
        });
        recvThread.join();
        sendThread.join();

        //::shutdown(socket_fd, SHUT_RDWR);
        ::close(socket_fd);

        socket_fd = creat_socket();
        if(socket_fd == -1)
            exit(1);
    }
}
