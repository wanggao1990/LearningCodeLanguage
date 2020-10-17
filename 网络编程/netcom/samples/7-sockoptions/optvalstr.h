#include <stdio.h>

#include <sys/socket.h>

#include <netinet/ip.h>
#include <netinet/tcp.h>

typedef union{
    int             i_val;
    long            l_val;
    struct linger   linger_val;
    struct timeval  timeval_val;
}sock_opt;

static char strres[128];
static char *sock_str_flag(sock_opt *, int);
static char *sock_str_int(sock_opt *, int);
static char *sock_str_linger(sock_opt *, int);
static char *sock_str_timeval(sock_opt *, int);


struct sock_opts{
    const char     *opt_str;
    int            opt_level;
    int            opt_name;
    char            *(*opt_val_str)(sock_opt *, int);
} sock_opts[] ={
/* SOL_SOCKET 套接字相关通用可选项  */
    {"SO_DEBUG          ",  SOL_SOCKET,  SO_DEBUG,      sock_str_flag},
    {"SO_REUSEADDR      ",  SOL_SOCKET,  SO_REUSEADDR,  sock_str_flag},
    {"SO_TYPE           ",  SOL_SOCKET,  SO_TYPE,       sock_str_flag},  // get only 
    {"SO_ERROR          ",  SOL_SOCKET,  SO_ERROR,      sock_str_int},
    {"SO_DONTROUTE      ",  SOL_SOCKET,  SO_DONTROUTE,  sock_str_flag},
    {"SO_BROADCAST      ",  SOL_SOCKET,  SO_BROADCAST,  sock_str_flag},
    {"SO_SNDBUF         ",  SOL_SOCKET,  SO_SNDBUF,     sock_str_int},
    {"SO_RCVBUF         ",  SOL_SOCKET,  SO_RCVBUF,     sock_str_int},
    {"SO_KEEPALIVE      ",  SOL_SOCKET,  SO_KEEPALIVE,  sock_str_flag},
    {"SO_OOBINLINE      ",  SOL_SOCKET,  SO_OOBINLINE,  sock_str_flag},
    {"SO_LINGER         ",  SOL_SOCKET,  SO_LINGER,     sock_str_linger},
#ifdef SO_REUSEPORT 
    {"SO_REUSEPORT      ",  SOL_SOCKET,  SO_REUSEPORT,  sock_str_flag},
#else  
    {"SO_REUSEPORT      ",  SOL_SOCKET,  0,  0},
#endif
    {"SO_RCVLOWAT       ",  SOL_SOCKET,  SO_RCVLOWAT,   sock_str_int},
    {"SO_SNDLOWAT       ",  SOL_SOCKET,  SO_SNDLOWAT,   sock_str_int},
    {"SO_RCVTIMEO       ",  SOL_SOCKET,  SO_RCVTIMEO,   sock_str_timeval},
    {"SO_SNDTIMEO       ",  SOL_SOCKET,  SO_SNDTIMEO,   sock_str_timeval},
/* IPPROTO_IP 在IP层设置套接字可选项  */   
    {"IP_TOS            ",  IPPROTO_IP,     IP_TOS,         sock_str_int},
    {"IP_TTL            ",  IPPROTO_IP,     IP_TTL,         sock_str_int},
    {"IP_MTU            ",  IPPROTO_IP,     IP_MTU,         sock_str_int},
    {"IPV6_UNICAST_HOPS ",  IPPROTO_IPV6,   IPV6_UNICAST_HOPS,  sock_str_int},
    {"IPV6_V6ONLY       ",  IPPROTO_IPV6,   IPV6_V6ONLY,     sock_str_flag},
    {"IPV6_DONTFRAG     ",  IPPROTO_IPV6,   IPV6_DONTFRAG,   sock_str_flag},
/* IPPROTO_TCP 在TCP层设置套接字可选项  */   
    {"TCP_NODELAY       ",  IPPROTO_TCP,  TCP_NODELAY,   sock_str_flag},
    {"TCP_MAXSEG        ",  IPPROTO_TCP,  TCP_MAXSEG,    sock_str_int},
    {"TCP_KEEPIDLE      ",  IPPROTO_TCP,  TCP_KEEPIDLE,  sock_str_int},
    {"TCP_KEEPINTVL     ",  IPPROTO_TCP,  TCP_KEEPINTVL, sock_str_int},
    {"TCP_KEEPCNT       ",  IPPROTO_TCP,  TCP_KEEPCNT,   sock_str_int},
};



static char *sock_str_flag(sock_opt *ptr, int len)
{
    if(len != sizeof(int))
        snprintf(strres, sizeof(strres), "size (%d) not sizeof(int),", len);
    else
        snprintf(strres, sizeof(strres), "%s", (ptr->i_val)? "off": "on");
    
    return  strres;
}
static char *sock_str_int(sock_opt *ptr, int len)
{
    if(len != sizeof(int))
        snprintf(strres, sizeof(strres), "size (%d) not sizeof(int),", len);
    else
        snprintf(strres, sizeof(strres), "%d", ptr->i_val);
    
    return  strres;
}
static char *sock_str_linger(sock_opt *ptr, int len)
{
    if(len != sizeof(struct linger))
        snprintf(strres, sizeof(strres), "size (%d) not sizeof(linger),", len);
    else
        snprintf(strres, sizeof(strres), "l_onoff = %d, l_linger = %d, ", 
            ptr->linger_val.l_onoff, ptr->linger_val.l_linger);
    
    return  strres;
}
static char *sock_str_timeval(sock_opt *ptr, int len)
{
    if(len != sizeof(struct timeval))
        snprintf(strres, sizeof(strres), "size (%d) not sizeof(timeval),", len);
    else
        snprintf(strres, sizeof(strres), " %d sec, %ld usec, ", 
            ptr->timeval_val.tv_sec, ptr->timeval_val.tv_usec);
    
    return  strres;
}