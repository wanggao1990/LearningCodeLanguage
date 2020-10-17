#include <stdio.h>

#include <sys/socket.h>
#include <arpa/inet.h> // sockaddr_in, inet_addr
#include <unistd.h>    // close
#include <cstring>     // memset, bezro
#include <errno.h>


#include <sys/time.h>
#define LOG(fmt, arg...)                                                 \
    do                                                                   \
    {                                                                    \
        struct timeval tv;                                               \
        gettimeofday(&tv, NULL);                                         \
        printf("[%ld.%03ld] " fmt, tv.tv_sec, tv.tv_usec / 1000, ##arg); \
    } while (0)

const char *SRV_ADDR = "127.0.0.1";
const int SRV_PORT = 8080;

static int tcp_server_select();
static int tcp_server_nonblocking();
static int tcp_client_nonblocking();

int main()
{
    //tcp_client_nonblocking();
    //tcp_server_nonblocking();
    tcp_server_select();
}

static int tcp_server_nonblocking()
{
    // 创建socket
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0); // tcp
    if (socket_fd == -1){
        LOG("%s: create socket failed. %s\n", __func__, strerror(errno));
        return 1;
    }

    // 连接到服务器
    sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(SRV_ADDR);
    servaddr.sin_port = htons(SRV_PORT);

    int ret = ::bind(socket_fd, (const sockaddr*)&servaddr, sizeof(servaddr));
    if(ret < 0) {
        LOG("%s: bind failed.\n", __func__);
        return 1;
    }else{
        LOG("%s: bind %s:%d success.\n", __func__, SRV_ADDR, SRV_PORT);
    }

    /// 3、监听
    ret = ::listen(socket_fd,5);
    if(ret == -1){
        printf("%s: listen failed. %s\n", __func__, strerror(errno));
        return 1;
    }else{     
        printf("%s: listening ...\n", __func__);
    }


    int sock_id = ::accept(socket_fd, NULL, NULL);  //不需要 对端地址结构
    if(sock_id < 0) {
        printf("%s: accept error. %s\n", __func__, strerror(errno));
        return 1;
    }

    char buf[1024];
    int len;

    while(true){

        len = read(sock_id, buf, sizeof(buf));
        if(len < 0) {
            printf("%s: recv failed. %s\n", __func__, strerror(errno));
            break;
        }
        else if(len == 0) {  // tcp 读取长度为0,表示对端关闭连接
            printf("%s: client socket %d disconnet. recv len = 0. \n",__func__, sock_id);
            break;
        }

        // echo 
        len = ::write(sock_id, buf, strlen(buf));
        if(len < 0) {
            printf("%s: send failed. %s\n", __func__, strerror(errno));
            break;
        }
    }
    ::close(sock_id);
  
    ::close(socket_fd);
}

static int tcp_client_nonblocking()
{
    // 创建socket
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0); // tcp
    if (socket_fd == -1){
        LOG("%s: create socket failed. %s\n", __func__, strerror(errno));
        return 1;
    }

    //TODO    套接字设置为非阻塞


    // 连接到服务器
    sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(SRV_ADDR);
    servaddr.sin_port = htons(SRV_PORT);

    int ret = ::connect(socket_fd, (const sockaddr*)&servaddr, sizeof(servaddr));
    if(ret < 0) {
        LOG("%s: connect failed.\n", __func__);
        return 1;
    }else{
        LOG("%s: connect %s:%d success.\n", __func__, SRV_ADDR, SRV_PORT);
    }

    char buf[1024]={};
    fgets(buf, sizeof(buf), stdin);

    int len = ::write(socket_fd, buf, strlen(buf));
    if(len < 0) {
        LOG("%s: send failed. %s\n", __func__, strerror(errno));
        return  0;
    }
  
    ::close(socket_fd);
}


static int tcp_server_select()
{
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0); // tcp
    if (socket_fd == -1){
        LOG("%s: create socket failed. %s\n", __func__, strerror(errno));
        return 1;
    }else{
        LOG("%s: create socket (fd = %d) success.\n", __func__, socket_fd);
    }

    /// 2、绑定到本地端口
    sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(SRV_ADDR);
    servaddr.sin_port = htons(SRV_PORT);

    int ret = ::bind(socket_fd, (const sockaddr *)&servaddr, sizeof(servaddr));
    if (ret == -1){
        LOG("%s: bind %s:%d failed. %s\n", __func__, SRV_ADDR, SRV_PORT, strerror(errno));
        return 1;
    }else{
        LOG("%s: bind %s:%d success.\n", __func__, SRV_ADDR, SRV_PORT);
    }

    /// 3、监听
    ret = ::listen(socket_fd, 5);
    if (ret == -1){
        LOG("%s: listen failed. %s\n", __func__, strerror(errno));
        return 1;
    }else{
        LOG("%s: listening ...\n", __func__);
    }

    // select的参数
    int max_fd = socket_fd;
    fd_set fd_A;            // 监听fd、客户fd
    fd_set work_fd_A;      // 待检测的fd，用于select调用，每次调用都会被改变

    FD_ZERO(&fd_A);
    FD_SET(socket_fd, &fd_A);  // 添加监听fd

    timeval timeout;
    // linux 为非const指针，调用之后会修改为剩下的时间，因此需要每次赋值
    //timeout.tv_sec = 10;
    //timeout.tv_usec = 0;

    int len;
    char buf[1024];

    while (true)
    {
        FD_ZERO(&work_fd_A);
        memcpy(&work_fd_A, &fd_A, sizeof(fd_A));   

        timeout.tv_sec = 30;
        timeout.tv_usec = 0;

        ret = select(max_fd + 1, &work_fd_A, NULL, NULL, &timeout);

        if (ret == -1){ // 出错
            LOG("%s: select failed. %s\n", __func__, strerror(errno));
            return 1;
        }
        else if (ret == 0){ // 超时
            LOG("%s: select timeout.\n", __func__);
            continue;
        }

        if (FD_ISSET(socket_fd, &work_fd_A)) // 新的客户端连接
        {
            sockaddr_in clientaddr;
            socklen_t sock_len = sizeof(clientaddr);
            int sock_id = ::accept(socket_fd, (sockaddr *)&clientaddr, &sock_len);
            if (sock_id < 0){
                LOG("%s: accept error. %s\n", __func__, strerror(errno));
                return 1;
            }

            char client_ip[INET6_ADDRSTRLEN];
            inet_ntop(AF_INET, &clientaddr.sin_addr, client_ip, sock_len);
            int port = ntohs(clientaddr.sin_port);
            LOG("%s: new socket id = %d, clent %s:%d\n", __func__, sock_id, client_ip, port);

            // 将新建立连接的客户端 fd加入fdset
            FD_SET(sock_id, &fd_A);
            if (sock_id > max_fd) 
                max_fd = sock_id;
        }
        else
        {
            // 遍历查找已就绪的套接字
            // 0-stdin, 1-stdout, 2-stderr
            for (int fd = 0; fd <= max_fd; ++fd)
            {
                if (FD_ISSET(fd, &work_fd_A))
                {
                     len = read(fd, &buf, sizeof(buf));

                    if (len < 0){
                        LOG("%s: recv failed. %s\n", __func__, strerror(errno));
                        return 1;
                    }
                    else if (len == 0){ // 对端关闭连接
                        LOG("%s: client socket %d disconnet. recv len = 0. \n", __func__, fd);

                        // 从fdset中移除
                        ::close(fd);
                        FD_CLR(fd, &fd_A);

                        // 例如开始有3,4,5,6,7     （max_fd = 7 ）
                        // 后来5,6关闭，剩下 3,4,7 （max_fd = 7 ）
                        // 当7关闭，剩下3,4         max_fd应该减小为4
                        if (fd == max_fd){
                            while (FD_ISSET(max_fd, &fd_A) == false) --max_fd;
                        }
                        
                    }else{
                        buf[len] = 0;
                        LOG("%s: recv from socket %d (%d): %s", __func__, fd, len, buf);

                        // echo
                        len = ::write(fd, buf, strlen(buf));
                        if (len < 0){
                            printf("%s: send failed. %s\n", __func__, strerror(errno));
                            return 1;
                        }
                    }
                }
            }
        }
    }

    ::close(socket_fd);
}
