#include <stdio.h>

#include <sys/socket.h>
#include <arpa/inet.h>      // sockaddr_in, inet_addr
#include <unistd.h>         // close
#include <cstring>          // memset, bezro
#include <errno.h>

constexpr const char* SRV_ADDR = "127.0.0.1";
constexpr       int   SRV_PORT = 8080;

int main()
{
    /// 1、创建socket
    int socket_fd = socket(AF_INET,SOCK_STREAM, 0);   // tcp
    if(socket_fd == -1) {
        printf("%s: create socket failed. %s\n", __func__, strerror(errno));
        return 1;
    }
    else {
        printf("%s: create socket (fd = %d) success.\n", __func__, socket_fd);
    }

    /// 2、连接到服务端
    sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET,SRV_ADDR, &servaddr.sin_addr);
    servaddr.sin_port = htons(SRV_PORT);

    int ret = ::connect(socket_fd, (sockaddr*)&servaddr, sizeof(servaddr));
    if(ret < 0) {
        printf("%s: connect failed.\n", __func__);
        return 1;
    }else{
        printf("%s: connect %s:%d success.\n", __func__, SRV_ADDR, SRV_PORT);

        sockaddr_in localaddr;
        socklen_t   sock_len = sizeof(localaddr);  // 必须给初值
        // 必须给初始长度, getsockname会根据实际情况重新赋值，  这里 16 -> 16
        // 若出现初始值<0，  会报错，提示  Invalid argument
        ret = getsockname(socket_fd, (sockaddr*)&localaddr, &sock_len);
        if(ret == -1){
            printf("%s: getsockname failed. %s\n", __func__, strerror(errno));
        }else{
            printf("%s: local addr: %s:%d\n", 
                __func__, inet_ntoa(localaddr.sin_addr), ntohs(localaddr.sin_port));
        }
    }

    // 3、 发送到服务端
    int len ;
    char buf[1024]; 
    while (1)
    {
        printf("%s: send: ", __func__);
        fgets(buf, sizeof(buf), stdin);   // 等待用户输入
        if (strcmp(buf, "exit\n") == 0)
            break;

        // 发送
        len = ::write(socket_fd, buf, strlen(buf));
        if(len < 0){
            printf("%s: send failed.Exit. %s\n", __func__, strerror(errno));
            break;
        }
        // echo
        len = ::read(socket_fd, buf, sizeof(buf));
        if(len < 0){
            printf("%s: recv failed. %s\n", __func__, strerror(errno));
            break;
        }else if(len == 0){
            printf("%s: server closed.\n", __func__);
            break;
        } 
        printf("%s: recv (%d): %s\n", __func__, len, buf);

        // ::shutdown(socket_fd,SHUT_WR);
        // break;
    }

    /// 4、关闭连接
    ::close(socket_fd);
}
