#include <stdio.h>

#include <sys/socket.h>
#include <arpa/inet.h>      // sockaddr_in, inet_addr
#include <unistd.h>         // close
#include <cstring>          // memset, bezro
#include <errno.h>

const char* SRV_ADDR = "127.0.0.1";
const int   SRV_PORT = 8080;

int main()
{
    /// 1、创建socket
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);   // tcp
    if(socket_fd == -1) {
        printf("%s: create socket failed. %s\n", __func__, strerror(errno));
        return 1;
    }
    else {
        printf("%s: create socket (fd = %d) success.\n", __func__, socket_fd);
    }

    //
    int val;
    socklen_t valLen = sizeof(val);
    int re = getsockopt(socket_fd,SOL_SOCKET,SO_REUSEADDR, &val, &valLen);
    
    val = 1;
    re = setsockopt(socket_fd,SOL_SOCKET,SO_REUSEADDR, &val, valLen);

    /// 2、绑定到本地端口
    sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(SRV_ADDR);
    servaddr.sin_port = htons(SRV_PORT);

    int ret = ::bind(socket_fd, (const sockaddr*)&servaddr, sizeof(servaddr));
    if(ret == -1) {
        printf("%s: bind %s:%d failed. %s\n", 
            __func__, SRV_ADDR, SRV_PORT, strerror(errno));
        return 1;
    }
    else {
        printf("%s: bind %s:%d success.\n", __func__, SRV_ADDR, SRV_PORT);
    }

    /// 3、监听
    ret = ::listen(socket_fd, 5);
    if(ret == -1) {
        printf("%s: listen failed. %s\n", __func__, strerror(errno));
        return 1;
    }
    else {
        printf("%s: listening ...\n", __func__);
    }

    // 4、等待客户端连接
   // sockaddr_in clientaddr;
   // socklen_t sock_len;
   // int sock_id = ::accept(socket_fd, (sockaddr*)&clientaddr, &sock_len);
    int sock_id = ::accept(socket_fd, NULL, NULL);  //不需要 对端地址结构
    if(sock_id < 0) {
        printf("%s: accept error. %s\n", __func__, strerror(errno));
        return 1;
    }

    // 5、持续回话，回显
    int len;
    char buf[1024];
    while(true) 
    {
        len = read(sock_id, buf, sizeof(buf));
        if(len < 0) {
            printf("%s: recv failed. %s\n", __func__, strerror(errno));
            break;
        }
        else if(len == 0) {  // tcp 读取长度为0,表示对端关闭连接
            printf("%s: client socket %d disconnet. recv len = 0. \n",__func__, sock_id);
            break;
        }
        buf[len]=0;
        printf("recv from socket %d (%d): %s\n", sock_id, len, buf);

        // echo 
        len = ::write(sock_id, buf, strlen(buf));
        if(len < 0) {
            printf("%s: send failed. %s\n", __func__, strerror(errno));
            break;
        }

        break;
    }
    ::close(sock_id);

    /// 6、关闭连接
    ::close(socket_fd);
}

