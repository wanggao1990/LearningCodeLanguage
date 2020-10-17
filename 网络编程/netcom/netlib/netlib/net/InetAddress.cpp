
#include "netlib/net/InetAddress.h"

#ifdef _WIN32
// struct in6_addr_uint
// {
//     union {
//         u_char Byte[16];
//         u_short Word[8];
//         uint32_t __s6_addr32[4];
//     } uext;
// };
#else
#include <string.h>             // memset
#include <netinet/tcp.h>
#include <netdb.h>
#endif


static const in_addr_t kInaddrAny = INADDR_ANY;
static const in_addr_t kInaddrLoopback = INADDR_LOOPBACK;



using namespace netlib;


InetAddress::InetAddress(uint16_t port, bool loopbackOnly, bool ipv6)
    : isIpV6_(ipv6)
{
    if (ipv6)
    {
        memset(&addr6_, 0, sizeof(addr6_));
        addr6_.sin6_family = AF_INET6;
        in6_addr ip = loopbackOnly ? in6addr_loopback : in6addr_any;
        addr6_.sin6_addr = ip;
        addr6_.sin6_port = htons(port);
    }
    else
    {
        memset(&addr_, 0, sizeof(addr_));
        addr_.sin_family = AF_INET;
        in_addr_t ip = loopbackOnly ? kInaddrLoopback : kInaddrAny;
        addr_.sin_addr.s_addr = htonl(ip);
        addr_.sin_port = htons(port);
    }
}