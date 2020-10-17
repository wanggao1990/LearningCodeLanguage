#include <stdio.h>

#include <sys/socket.h>
#include <arpa/inet.h> // sockaddr_in, inet_addr
#include <unistd.h>    // close
#include <cstring>     // memset, bezro
#include <errno.h>

#include <sys/poll.h>

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

static int tcp_server_nonblocking();
static int tcp_server_poll();

int main()
{

    tcp_server_poll();
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

static int tcp_server_poll()
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
    ret = ::listen(socket_fd, 2048);
    if (ret == -1){
        LOG("%s: listen failed. %s\n", __func__, strerror(errno));
        return 1;
    }else{
        LOG("%s: listening ...\n", __func__);
    }

    /// poll的参数
    struct pollfd fdarray[2048];  
    // 添加监听
    fdarray[0].fd = socket_fd;
    fdarray[0].events = POLLIN|POLLPRI;   // 同select读
    // 初始化其他结构对象
    for(int i=1; i<2048; ++i)
        fdarray[i].fd = -1;    // fd为负值的pollfd结构会被poll忽略

    int maxi = 0;         // fdarray数组中正在使用最大下标值
    int timeout = 30000;  //  ms
    int nready;           //  就绪的描述符，poll返回值

    int len;
    char buf[1024];
    while (true)
    {
        nready = ::poll(fdarray, maxi + 1, timeout);

        if (nready == -1){ // 出错
            LOG("%s: select failed. %s\n", __func__, strerror(errno));
            return 1;
        }
        else if (nready == 0){ // 超时
            LOG("%s: select timeout.\n", __func__);
            continue;
        }

        if (fdarray[0].revents & (POLLIN|POLLPRI)) // 新的客户端连接
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

            // 将新建立连接的客户端加入fdarray
            int i;
            for( i = 1; i < 2048; i++) 
                if(fdarray[i].fd < 0){
                    fdarray[i].fd = sock_id;
                    fdarray[i].events = POLLIN|POLLPRI;
                    if( i > maxi) 
                        maxi = i;
                    break;
                }

            if( i == 2048 ){
                LOG("%s: too many clients\n", __func__);
                break; // 退出 
            }

            if(--nready <= 0)
                continue;     // 若当前poll返回为nready为1，避免执行后续的轮询操作
        }

        // 遍历其他pollfd结构
        for (int i = 1; i <= maxi; ++i)
        {
            int fd = fdarray[i].fd;
            if ( fdarray[i].revents  & (POLLIN|POLLPRI|POLLERR))
            {
                len = read(fd, &buf, sizeof(buf));
                if (len < 0){
                    LOG("%s: recv failed. %s\n", __func__, strerror(errno));
                    return 1;
                }
                else if (len == 0){ // 对端关闭连接
                    LOG("%s: client socket %d disconnet. recv len = 0. \n", __func__, fd);

                    // 从fdarray中移除
                    ::close(fd);
                    fdarray[i].fd = -1;

                    if( i == maxi )
                        while( fdarray[maxi].fd < 0) --maxi;
                        
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

                if(--nready <= 0)
                    break;        // 根据poll返回值和已处理描述符次数降低轮询次数
            }
        }     
    }

    ::close(socket_fd);
}
