#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h> // sockaddr_in, inet_addr
#include <unistd.h>    // close
#include <cstring>     // memset, bezro, strerror
#include <errno.h>

#include <fcntl.h> // fcntl
#include <signal.h>

#include <sys/time.h>

#define LOG(fmt, arg...)                                                            \
    do                                                                              \
    {                                                                               \
        struct timeval tv;                                                          \
        gettimeofday(&tv, NULL);                                                    \
        printf("[%ld.%06d] %s: " fmt "\n", tv.tv_sec, tv.tv_usec, __func__, ##arg); \
    } while (0)

static void print_getsockname(int socket_fd)
{
    sockaddr_storage storage;
    socklen_t sock_len = sizeof(storage); // 必须给初值
    int ret = getsockname(socket_fd, (sockaddr *)&storage, &sock_len);
    if (ret < 0){
        LOG("getsockname error: %s", strerror(errno));
        return;
    }

    if (storage.ss_family == AF_INET){
        sockaddr_in *addr = (sockaddr_in *)&storage;
        LOG("local addr: %s:%d", inet_ntoa(addr->sin_addr), ntohs(addr->sin_port));
    }else if (storage.ss_family == AF_INET6){
        sockaddr_in6 *addr = (sockaddr_in6 *)&storage;
        char ip[INET6_ADDRSTRLEN];
        inet_ntop(AF_INET6, &addr->sin6_addr, ip, sizeof(addr));
        LOG("local addr: %s:%d", ip, ntohs(addr->sin6_port));
    }
}

static
void print_getpeername(int socket_fd)
{
    sockaddr_storage storage;
    socklen_t sock_len = sizeof(storage); // 必须给初值
    int ret = getpeername(socket_fd, (sockaddr *)&storage, &sock_len);
    if (ret < 0)
    {
        printf("getpeername error: %s\n", strerror(errno));
        return;
    }

    if (storage.ss_family == AF_INET)
    {
        sockaddr_in *addr = (sockaddr_in *)&storage;
        printf("peer addr: %s:%d\n", inet_ntoa(addr->sin_addr), ntohs(addr->sin_port));
    }
    else if (storage.ss_family == AF_INET6)
    {
        sockaddr_in6 *addr = (sockaddr_in6 *)&storage;
        char ip[INET6_ADDRSTRLEN];
        inet_ntop(AF_INET6, &addr->sin6_addr, ip, sizeof(addr));
        printf("peer addr: %s:%d\n", ip, ntohs(addr->sin6_port));
    }
}

const char *SRV_ADDR = "127.0.0.1";
const int SRV_PORT = 8080;

static void sigalarm_handle(int signo);

static int connect_timeo_sigalrm(int sock_fd, const sockaddr *addr, socklen_t socklen, int nsec);
static int test_connet_timeo();

static int recvform_timeo_sigalrm(int sock_fd, int nsec);
static int test_recvfrom_timeo();

int main()
{
    //test_connet_timeo();
    test_recvfrom_timeo();
}

static int connect_timeo_sigalrm(int sock_fd, const sockaddr *addr, socklen_t socklen, int nsec)
{
    __sighandler_t sigfunc = signal(SIGALRM, sigalarm_handle);
    int ret;

    if (alarm(nsec) != 0)
        LOG("connect timeout: alarm was already set");

    ret = connect(sock_fd, addr, socklen);
    if (ret < 0){
        //close(sock_fd);
        if (errno == EINTR)
            errno = ETIMEDOUT;
    }
    alarm(0);
    signal(SIGALRM, sigfunc); // restore previous signal handler

    return ret;
}

static void sigalarm_handle(int signo)
{
    return;
}

static int test_connet_timeo()
{
    /// 1、创建socket
    //int socket_fd = socket(AF_INET,SOCK_DGRAM, 0);   // udp
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0); // tcp
    if (socket_fd == -1){
        LOG("create socket failed. %s", strerror(errno));
        return 1;
    }else{
        LOG("create socket (fd = %d) success.", socket_fd);
    }

    int ret;

    // int opt = 1;
    // int ret = setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));
    // if(ret < 0){
    //     LOG("setsockopt reuseaddr failed.");
    // }

    /// 2、连接服务端
    sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    inet_pton(servaddr.sin_family, "127.0.0.1", &servaddr.sin_addr);
    servaddr.sin_port = htons(8080);

    while (1)
    {
        ret = connect_timeo_sigalrm(socket_fd, (const sockaddr *)&servaddr, sizeof(servaddr), 1);
        if (ret < 0){
            LOG("connect timeout. %s", strerror(errno));
            sleep(1);
        }else{
            LOG("connected server.");
            break;
        }
    }

    print_getsockname(socket_fd);

    /// 3、等待接收和响应
    char buf[1024]; // 发送

    sockaddr_in clientaddr;
    socklen_t socklen = sizeof(clientaddr);

    while (1)
    {
        int len = ::read(socket_fd, buf, sizeof(buf));
        //int len = ::recv(socket_fd, buf, sizeof(buf), 0);
        //int len = ::recvfrom(socket_fd, buf, sizeof(buf), 0,  NULL, NULL);
        //int len = ::recvfrom(socket_fd, buf, sizeof(buf), 0, (struct sockaddr *)&clientaddr, &socklen);

        if (len < 0){
            LOG("recv failed. err %d (%s)", errno, strerror(errno));
            if (errno == EAGAIN){
                //usleep(1000*100); // 10ms
                sleep(1);
                continue;
            }
            break;
        }else if (len == 0){
            LOG("server closed");
            break;
        }else{
            char ip[INET6_ADDRSTRLEN];
            inet_ntop(clientaddr.sin_family, &clientaddr.sin_addr, ip, socklen);

            int port = ntohs(clientaddr.sin_port);

            buf[len] = '\0';
            LOG("client [%s:%d] recv %2d: %s", ip, port, len, buf);
        }

        //buf[len] = '\0';

        if (strcmp(buf, "exit") == 0)    break;

        // 接收到的数据发送给客户端
        len = ::sendto(socket_fd, buf, sizeof(buf), 0, (struct sockaddr *)&clientaddr, socklen);
        if (len < 0){
            printf("%s: send failed. err %s", __func__, strerror(errno));
            break;
        }else if (len == 0){
            printf("%s: send len = 0.", __func__);
            break;
        }
    }

    /// 4、关闭连接
    ::close(socket_fd);
}






static int recvform_timeo_sigalrm(int socket_fd, int nsec)
{
    print_getpeername(socket_fd);

    char buf[1024];

    signal(SIGALRM, sigalarm_handle);

    while (1)
    {
        alarm(nsec);

        int len = ::recvfrom(socket_fd, buf, sizeof(buf), 0, NULL, NULL);
        if (len < 0){
            LOG("recv failed.");
            if (errno == EINTR) 
                LOG("timeout. %s", strerror(errno));    
            else
                break;
        }else if(len == 0){
            LOG("client closed.");
            break;
        }else{
            buf[len] = '\0';
            LOG("client recv %d: %s", len, buf);
            alarm(0); 
        }
    }

    alarm(0); 
    return 0;
}

static int test_recvfrom_timeo()
{
    /// 1、创建socket
    //int socket_fd = socket(AF_INET, SOCK_DGRAM, 0); // udp
    int socket_fd = socket(AF_INET,SOCK_STREAM, 0);   // tcp
    if (socket_fd == -1){
        LOG("create socket failed. %s", strerror(errno));
        return 1;
    }else{
        LOG("create socket (fd = %d) success.", socket_fd);
    }

    /// 2、绑定到本地端口
    sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    inet_pton(servaddr.sin_family, SRV_ADDR, &servaddr.sin_addr);
    servaddr.sin_port = htons(SRV_PORT);

    int ret = ::bind(socket_fd, (const sockaddr *)&servaddr, sizeof(servaddr));
    if (ret == -1)
    {
        LOG("bind %s:%d failed. %s.", SRV_ADDR, SRV_PORT, strerror(errno));
        return 1;
    }else{
        LOG("bind %s:%d success.", SRV_ADDR, SRV_PORT);
    }

    /// 3、监听
    ret = ::listen(socket_fd,5);
    if(ret == -1){
        LOG("%s: listen failed. %s", __func__, strerror(errno));
        return 1;
    }else{     
        LOG("%s: listening ...", __func__);
    }

    int sock_id = ::accept(socket_fd, NULL, NULL); 
    if(sock_id < 0){
        LOG("accept error. %s", strerror(errno));
        return 1;
    }  

    /// 等待接收数据
    recvform_timeo_sigalrm(sock_id, 3);
    close(sock_id);

    /// 4、关闭连接
    ::close(socket_fd);
}
