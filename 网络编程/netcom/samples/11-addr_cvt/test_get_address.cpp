#include <stdio.h>

#include <sys/socket.h>
#include <arpa/inet.h> // sockaddr_in, inet_addr
#include <unistd.h>    // close
#include <cstring>     // memset, bezro
#include <errno.h>

constexpr const char *SRV_ADDR = "127.0.0.1";
constexpr int SRV_PORT = 8080;

static
void print_getsockname(int socket_fd)
{
    sockaddr_storage storage;
    socklen_t sock_len = sizeof(storage); // 必须给初值
    int ret = getsockname(socket_fd, (sockaddr *)&storage, &sock_len);
    if (ret < 0)
    {
        printf("getsockname error: %s\n", strerror(errno));
        return;
    }

    if (storage.ss_family == AF_INET)
    {
        sockaddr_in *addr = (sockaddr_in *)&storage;
        printf("local addr: %s:%d\n", inet_ntoa(addr->sin_addr), ntohs(addr->sin_port));
    }
    else if (storage.ss_family == AF_INET6)
    {
        sockaddr_in6 *addr = (sockaddr_in6 *)&storage;
        char ip[INET6_ADDRSTRLEN];
        inet_ntop(AF_INET6, &addr->sin6_addr, ip, sizeof(addr));
        printf("local addr: %s:%d\n", ip, ntohs(addr->sin6_port));
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

static
int tcp_get_local()
{
    /// 创建socket
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0); // tcp

    /// 连接
    sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
    servaddr.sin_port = htons(8080);

    /// bind 或 connect
    int ret;

    sockaddr_in localaddr;
    localaddr.sin_family = AF_INET;
    //inet_pton(AF_INET,"127.0.0.1" , &localaddr.sin_addr);
    localaddr.sin_addr.s_addr = INADDR_ANY;
    //localaddr.sin_port = 0;
    localaddr.sin_port = htons(9090);
    ret = ::bind(socket_fd, (sockaddr *)&localaddr, sizeof(localaddr));
    if (ret < 0)
    {
        printf("bind error: %s\n", strerror(errno));
    }

    ret = ::connect(socket_fd, (sockaddr *)&servaddr, sizeof(servaddr));
    if (ret < 0)
    {
        printf("bind error: %s\n", strerror(errno));
        return 0;
    }

    /// 获取本地信息
    print_getsockname(socket_fd);
}

static
int udp_get_local()
{
    /// 创建socket

    //int socket_fd = socket(AF_INET,SOCK_STREAM, 0);   // tcp
    int socket_fd = socket(AF_INET, SOCK_DGRAM, 0); // udp

    /// 连接
    sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
    servaddr.sin_port = htons(8080);

    /// bind 或 connect
    int ret;

    sockaddr_in localaddr;
    localaddr.sin_family = AF_INET;
    //inet_pton(AF_INET,SRV_ADDR, &localaddr.sin_addr);
    localaddr.sin_addr.s_addr = INADDR_ANY;
    //localaddr.sin_port = 0;
    localaddr.sin_port = htons(48529);

    ret = ::bind(socket_fd, (sockaddr *)&localaddr, sizeof(localaddr));
    if (ret < 0)
    {
        printf("bind error: %s\n", strerror(errno));
    }

    // ret = ::connect(socket_fd, (sockaddr*)&servaddr, sizeof(servaddr));
    // if(ret < 0){
    //     printf("bind error: %s\n", strerror(errno));
    //     return 0;
    // }

    // // 对于为bind的套接字，必须发送数据后，内核会分配端口
    // ret = sendto(socket_fd, "",0,0, (sockaddr*)&servaddr, sizeof(servaddr));
    // if(ret < 0){
    //     printf("bind error: %s\n", strerror(errno));
    // }

    /// 获取本地信息
    print_getsockname(socket_fd);

    ret = sendto(socket_fd, "", 0, 0, (sockaddr *)&servaddr, sizeof(servaddr));
    if (ret < 0)
    {
        printf("bind error: %s\n", strerror(errno));
    }
}

static
void get_udp_peer()
{
    /// 创建socket
    int socket_fd = socket(AF_INET, SOCK_DGRAM, 0); // udp
    if (socket_fd == -1)
    {
        printf("%s: create socket failed.\n", __func__);
        return;
    }

    /// bind
    int ret;
    sockaddr_in localaddr;
    localaddr.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &localaddr.sin_addr);
    localaddr.sin_port = htons(8080);

    ret = ::bind(socket_fd, (sockaddr *)&localaddr, sizeof(localaddr));
    if (ret < 0)
    {
        printf("bind error: %s\n", strerror(errno));
    }

    /// 接收
    char buf[1024];
    int len;

    while (true)
    {
        sockaddr_storage storage;
        socklen_t sock_len = sizeof(storage); // 必须给初值

        len = ::recvfrom(socket_fd, buf, sizeof(buf), 0, (struct sockaddr *)&storage, &sock_len);
        if (len < 0)
        {
            printf("recv failed. err %s\n", strerror(errno));
            return;
        }
        buf[len] = '\0';

        /// 输出对端信息
        if (storage.ss_family == AF_INET)
        {
            sockaddr_in *addr = (sockaddr_in *)&storage;
            char ip[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &addr->sin_addr, ip, sock_len);
            printf("recv client [%s:%d] %2d: %s", ip, ntohs(addr->sin_port), len, buf);
        }
        else if (storage.ss_family == AF_INET6)
        {
            sockaddr_in6 *addr = (sockaddr_in6 *)&storage;
            char ip[INET6_ADDRSTRLEN];
            inet_ntop(AF_INET6, &addr->sin6_addr, ip, sock_len);
            printf("recv client [%s:%d] %2d: %s", ip, ntohs(addr->sin6_port), len, buf);
        }
    }

    // 关闭连接
    ::close(socket_fd);
}

static
void get_udp_peer_in_client_connect()
{
    int socket_fd = socket(AF_INET, SOCK_DGRAM, 0); // udp

    /// 连接
    sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
    servaddr.sin_port = htons(8080);
    
    ::connect(socket_fd, (sockaddr *)&servaddr, sizeof(servaddr));

    /// 获取地址信息
    print_getpeername(socket_fd);
    print_getsockname(socket_fd);

    // 当前socket_fd是一个已连接的UDP套接字, 理论上需要使用write或send函数
    //::sendto(socket_fd,"123",3, 0, (sockaddr*)&servaddr, sizeof(servaddr));
    ::write(socket_fd, "123", 3);

    // 关闭连接
    ::close(socket_fd);
}

static
void tcp_get_peer()
{
    /// 创建socket
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0); // tcp

    /// bind
    int ret;
    sockaddr_in localaddr;
    localaddr.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &localaddr.sin_addr);
    localaddr.sin_port = htons(8080);

    ret = ::bind(socket_fd, (sockaddr *)&localaddr, sizeof(localaddr));

    // 监听
    ::listen(socket_fd, 5);

    // 等待连接
    // sockaddr_storage storage;
    // socklen_t sock_len = sizeof(storage); // 必须给初值
    //int sock_id = ::accept(socket_fd, (sockaddr *)&storage, &sock_len);
    int sock_id = ::accept(socket_fd, NULL, NULL);

    /// 输出对端信息
    sockaddr_storage storage;
    socklen_t sock_len = sizeof(storage); // 必须给初值
    ret = ::getpeername(sock_id, (sockaddr *)&storage, &sock_len);
    if (ret < 0){
        printf("getpeername error: %s\n", strerror(errno));
    }
    else{
        if (storage.ss_family == AF_INET){
            sockaddr_in *addr = (sockaddr_in *)&storage;
            char ip[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &addr->sin_addr, ip, sock_len);
            printf("peer [%s:%d] \n", ip, ntohs(addr->sin_port));
        }
        else if (storage.ss_family == AF_INET6){
            sockaddr_in6 *addr = (sockaddr_in6 *)&storage;
            char ip[INET6_ADDRSTRLEN];
            inet_ntop(AF_INET6, &addr->sin6_addr, ip, sock_len);
            printf("peer [%s:%d] \n", ip, ntohs(addr->sin6_port));
        }
    }

    // 关闭连接
    ::close(sock_id);
    ::close(socket_fd);
}

int main()
{
    //tcp_get_local();
    //udp_get_local();

    // get_udp_peer();
    //  get_udp_peer_in_client_connect();

    tcp_get_peer();
}