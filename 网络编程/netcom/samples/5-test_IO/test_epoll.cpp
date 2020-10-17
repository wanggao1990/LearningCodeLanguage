#include <stdio.h>

#include <sys/socket.h>
#include <arpa/inet.h> // sockaddr_in, inet_addr
#include <unistd.h>    // close
#include <cstring>     // memset, bezro
#include <errno.h>

#include <sys/epoll.h>

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
static int tcp_server_epoll();

int main()
{

    tcp_server_epoll();
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


static int tcp_server_epoll()
{
    // 1、创建socket
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

    /// epoll操作
    // 创建epoll
    const int maxevents = 2048;
    int epollftd = ::epoll_create(maxevents);
    if(epollftd == -1){
        LOG("%s: epoll create faild. %s\n", __func__, strerror(errno));
        return 1;
    }else{
        LOG("%s: epoll create success. (epollfd = %d) \n", __func__, epollftd);
    }

    // 注册服务端监听
    epoll_event listen_event;  
    listen_event.data.fd = socket_fd;      
    listen_event.events = EPOLLIN|EPOLLPRI;   // 同select读, 默认水平触发

    ret = epoll_ctl(epollftd, EPOLL_CTL_ADD, listen_event.data.fd, &listen_event);
    if(ret == -1){
        LOG("%s: epoll_ctrl EPOLL_CTL_ADD failed. %s\n", __func__, strerror(errno));
        return 1;
    }

    // 创建接收epoll触发事件的epoll_event的数组
    epoll_event pEvents[maxevents];
    int nready;  

    int len;
    char buf[1024];
    while (true)
    {
        nready = ::epoll_wait(epollftd, pEvents, maxevents, 30000);

        //LOG("%s: epoll_wait ==================\n", __func__); // 测试maxevents取值不同的情况

        if (nready == -1){ // 出错
            LOG("%s: epoll_wait failed. %s\n", __func__, strerror(errno));
            return 1;
        }
        else if (nready == 0){ // 超时
            LOG("%s: epoll_wait timeout.\n", __func__);
            continue;
        }

        for (int i = 0; i < nready; i++)
        {
            const epoll_event& eventRef = pEvents[i];

            if(eventRef.data.fd == socket_fd) // 新的客户端连接
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
    
                // 将新建立连接的客户端加入epoll队列
                epoll_event ev;
                ev.events = EPOLLIN | EPOLLPRI ;
                ev.data.fd = sock_id;
                ::epoll_ctl(epollftd, EPOLL_CTL_ADD, ev.data.fd, &ev);
            }
            else if(eventRef.events & (EPOLLIN|EPOLLPRI|EPOLLERR)) // 读事件
            {
                len = read(eventRef.data.fd, &buf, sizeof(buf));
                if (len < 0){
                    LOG("%s: recv failed. %s\n", __func__, strerror(errno)); // 出错
                    return 1;
                }
                else if (len == 0){ // 对端关闭连接
                    LOG("%s: client socket %d disconnet. recv len = 0. \n", __func__, eventRef.data.fd);
                    
                    // 从epoll队列移除事件
                    epoll_event ev;
                    ev.data.fd = pEvents[i].data.fd; 
                    ev.events = EPOLLIN | EPOLLPRI ;

                    // 水平触发时，若不处理该事件，会无限接收客户断开连接的事件
                    // 边沿触发时，
                    //::epoll_ctl(epollftd, EPOLL_CTL_DEL, pEvents[i].data.fd, &ev);  
                    
                    ::close(eventRef.data.fd);   

                }else{
                    buf[len] = 0;
                    LOG("%s: recv from socket %d (%d): %s", __func__, eventRef.data.fd, len, buf);

                    // echo
                    len = ::write(eventRef.data.fd, buf, strlen(buf));
                    if (len < 0){
                        printf("%s: send failed. %s\n", __func__, strerror(errno));
                        return 1;
                    }
                }
            }
        } 
    }

    ::close(socket_fd); // 注意，这里实际是执行不到的
}
