#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h> // sockaddr_in, inet_addr

#include <cstring>  // memset, bzero

#include <string>  // c++   stoi

int main()
{   
    struct sockaddr_in addr_in4;
    // 初始化内存(若ip和ort都赋值非零值，可去掉)
    memset(&addr_in4,0,sizeof(addr_in4));
    // 协议地址族
    addr_in4.sin_family = AF_INET; // IPv4
    // 地址赋值
    const char ip4_addr[] = "192.168.3.100";
    addr_in4.sin_addr.s_addr = INADDR_ANY;            //INADDR_ANY=0, 内核选择
    addr_in4.sin_addr.s_addr = inet_addr(ip4_addr);   //废弃，仅IPv4
    inet_aton(ip4_addr, &addr_in4.sin_addr);          // 仅IPv4
    inet_pton(AF_INET, ip4_addr, &addr_in4.sin_addr); // 通用IPv4/6,建议
    // 端口赋值
    addr_in4.sin_port = 0;           // 内核选择
    addr_in4.sin_port = htons(8080); //网络序




    struct sockaddr_in6 addr_in6;
    memset(&addr_in6, 0, sizeof(addr_in6));
    // 协议地址族
    addr_in6.sin6_family = AF_INET6; // IPv6
    // 地址赋值
    const char ip6_addr[] = "fe80::30bb:634b:434:bca4";
    addr_in6.sin6_addr = IN6ADDR_ANY_INIT; // 内核选择
    addr_in6.sin6_addr.s6_addr16[0] = htons(std::stoi("fe80",0,16));
    addr_in6.sin6_addr.s6_addr16[1] = 0;
    addr_in6.sin6_addr.s6_addr16[2] = 0;
    addr_in6.sin6_addr.s6_addr16[3] = 0;//手动赋值
    addr_in6.sin6_addr.s6_addr16[4] = htons(std::stoi("30bb",0,16));
    addr_in6.sin6_addr.s6_addr16[5] = htons(std::stoi("634b",0,16));
    addr_in6.sin6_addr.s6_addr16[6] = htons(std::stoi("434",0,16));
    addr_in6.sin6_addr.s6_addr16[7] = htons(std::stoi("bca4",0,16)); 
    inet_pton(AF_INET6, ip6_addr, &addr_in6.sin6_addr);  // 建议
    // 端口赋值
    addr_in6.sin6_port = 0;           // 内核选择
    addr_in6.sin6_port = htons(8080); //网络序
}