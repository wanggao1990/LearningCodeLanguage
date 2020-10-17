#include <stdio.h>

#include <unistd.h> // gethostname

#include <arpa/inet.h> // sockaddr_in, inet_addr
#include <netdb.h>		 // gethostby***,  getaddrinfo,   h_error enum

#include <errno.h>
#include <cstring>



#include <ifaddrs.h>
static void test_getifaddrs();  // 获取本机局域网地址

static void test_ip_ioctl();

static void test_gethostname();

// 根据主机名（ip点分十进制串）得到ip地址，仅支持IPv4
static void test_gethostbyname(); // 仅支持IPv4
static void test_gethostbyname_r(); // 仅支持IPv4, 可重入版本
static void test_gethostbyaddr(); // 仅支持IPv4

static void test_getserverbyXXXX();

static void test_getaddrinfo(); // 代替 gethostbyname， 支持IPv4/IPv6
static void test_getnameinfo(); // 代替 gethostbyaddr

int main()
{

  test_ip_ioctl();

  //test_getifaddrs();

  // test_gethostname();       // 获取主机名

  //test_gethostbyname();
  //  test_gethostbyaddr();

  //test_getserverbyXXXX();

  //test_getaddrinfo();
 // test_getnameinfo();


  //test_gethostbyname_r();
}


#include <net/if.h>
#include <sys/ioctl.h> 
static void test_ip_ioctl()
{
   // https://www.cnblogs.com/baiduboy/p/7287026.html
  int inet_sock;  
  ifreq ifr;  
  char ip[46]={};  

  inet_sock = socket(AF_INET, SOCK_DGRAM, 0);  
  strcpy(ifr.ifr_name, "eth0");  // 指定网卡名称
  ioctl(inet_sock, SIOCGIFADDR, &ifr);  
  inet_ntop(AF_INET, &(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr), ip, sizeof(sockaddr_in));
    
  printf("%s IP Address %s\n", ifr.ifr_name, ip);
}

static void test_getifaddrs()
{  
  printf("\n\n=====================================================\n");
  printf("test getifaddrs\n\n");

  ifaddrs *ifAddrStruct = NULL;
  
  if (getifaddrs(&ifAddrStruct) < 0){
    printf("getifaddrs failed. %s", strerror(errno));
  }

  for (ifaddrs *ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
    if (!ifa->ifa_addr) {
      continue;
    }
    if (ifa->ifa_addr->sa_family == AF_INET) { // check it is IP4
      // is a valid IP4 Address
      void* tmpAddrPtr= &((sockaddr_in *)ifa->ifa_addr)->sin_addr;
      char addressBuffer[INET_ADDRSTRLEN];
      inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
      printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer); 
    } else if (ifa->ifa_addr->sa_family == AF_INET6) { // check it is IP6
      // is a valid IP6 Address
      void* tmpAddrPtr = &((sockaddr_in6 *)ifa->ifa_addr)->sin6_addr;
      char addressBuffer[INET6_ADDRSTRLEN];
      inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
      printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer); 
    } 
  }
 
  freeifaddrs(ifAddrStruct);
}

static void test_gethostname()
{
  printf("\n\n=====================================================\n");
  printf("test gethostname\n\n");

  char host[32] = {0};
  if (gethostname(host, sizeof(host)) < 0)
  {
    printf("gethostname failed. %s", strerror(errno));
  }
  printf("hostname: %s\n", host);
}

static void test_gethostbyname()
{

  printf("\n\n=====================================================\n");
  printf("test gethostbyname\n\n");

  //char host[] = "localhost";  // 127.0.0.1
  //char host[] = "taobao.com";
  char host[] = "www.taobao.com";
  //char host[] = "www.cnn.com";
  //char host[] = "magicsky.com";    // segmentfault seeor
  // char host[] = "www.magicsky.com";    // 39.97.180.162

  // char host[] = "DESKTOP-HD3JDLQ";    // 本机
  //char host[] = "DESKTOP-UANHMRS";    // 本机

 // char host[] = "www.microsoft.com";
  //char host[] = "www.baidu.com";

  printf("check host: %s\n\n", host);

  struct hostent *hptr;
  if ((hptr = gethostbyname(host)) == NULL)
  { // 只能返回IPv4地址，host允许是点分十进制字串
    // 错误时，设置全局变量h_errno，取值在<netdb.h>中 HOST_NOTFOUND,TRY_AGAIN, NO_RECOVERY, NO_DATA
    printf("gethostbyname error from \"%s\": %s\n", host, hstrerror(h_errno));
    return;
  }
  printf("official name: %s\n", hptr->h_name);

  char **pptr;
  for (pptr = hptr->h_aliases; *pptr != NULL; pptr++)
  {
    printf("  alias: %s\n", *pptr);
  }
  char str[16];
  for (pptr = hptr->h_addr_list; *pptr != NULL; pptr++)
  {
    printf("address: %s\n", inet_ntop(hptr->h_addrtype, *pptr, str, 16));
  }
}


static void test_gethostbyname_r()
{
  char host[] = "www.taobao.com";
  printf("check host: %s\n\n", host);

  struct hostent hostbuf, *res = NULL;
  char buf[8192] = {0};
  int err = 0;

  if( gethostbyname_r(host, &hostbuf, buf, sizeof(buf), &res, &err) < 0){
    printf("gethostbyname_r error from \"%s\": %s\n", host, hstrerror(err));
    return;
  }

  printf("official name: %s\n", res->h_name);

  char **pptr;
  for (pptr = res->h_aliases; *pptr != NULL; pptr++){
    printf("  alias: %s\n", *pptr);
  }
  char str[16];
  for (pptr = res->h_addr_list; *pptr != NULL; pptr++){
    printf("address: %s\n", inet_ntop(res->h_addrtype, *pptr, str, 16));
  }
}

static void test_gethostbyaddr()
{
  printf("\n\n=====================================================\n");
  printf("test getservbyaddr\n\n");

  // IPv4
  // char ip[] = "39.97.180.162"; // "www.magicsky.com"
  // char ip[] = "127.0.0.1" ;       // "localhost"
  // char ip[] = "192.168.250.100" ;
  char ip[] = "221.230.147.106"; // "localhost"

  in_addr addr;
  inet_aton(ip, &addr);
  // inet_pton(AF_INET, ip, &addr)

  struct hostent *hptr;
  if ((hptr = gethostbyaddr(&addr, sizeof(addr), AF_INET)) == NULL)
  {
    printf("gethostbyaddr error from: %s\n", hstrerror(h_errno));
    return;
  }

  printf("official name: %s\n", hptr->h_name);

  char **pptr;
  for (pptr = hptr->h_aliases; *pptr != NULL; pptr++)
  {
    printf("  alias: %s\n", *pptr);
  }
  char str[16];
  for (pptr = hptr->h_addr_list; *pptr != NULL; pptr++)
  {
    printf("address: %s\n", inet_ntop(hptr->h_addrtype, *pptr, str, 16));
  }
}

static void test_getserverbyXXXX()
{
  printf("\n\n=====================================================\n");
  printf("test getservbyname\n\n");

  servent *sptr;

  // sptr = getservbyname("http", "tcp");
  // if(sptr == NULL){
  //      printf("getservbyname error. %s\n", hstrerror(h_errno));
  //      return;
  // }

  // printf("service name: %s, port: %d, proto: %s",
  //     sptr->s_name, ntohs(sptr->s_port), sptr->s_proto);

  char **pptr;
  // for(pptr = sptr->s_aliases; *pptr != NULL; pptr++){
  //     printf(", alias: %s", *pptr);
  // }

  // return ;

  printf("\n\n=====================================================\n");
  printf("test getservbyport\n\n");

  int srvport = 80;

  sptr = getservbyport(htons(srvport), "udp");
  if (sptr == NULL)
  {
    printf("getservbyport error. %s\n", hstrerror(h_errno));
    return;
  }
  printf("service name: %s, port: %d, proto: %s\n", sptr->s_name, srvport, sptr->s_proto);
  for (pptr = sptr->s_aliases; *pptr != NULL; pptr++)
  {
    printf("  alias: %s\n", *pptr);
  }
}

void test_getaddrinfo()
{
  printf("\n\n=====================================================\n");
  printf("test getaddrinfo\n\n");

  //char host[] = "localhost";  // 127.0.0.1
  //char host[] = "taobao.com";
   char host[] = "www.taobao.com";
  //char host[] = "www.cnn.com";
  //char host[] = "magicsky.com";    // segmentfault seeor
  //char host[] = "www.magicsky.com";    // 39.97.180.162
  //char host[] = "www.magic-dji.f3322.net";
  //char host[] = "www.csdn.net";

   //char host[] = "www.microsoft.com";
  //char host[] = "www.baidu.com";
  //char host[] = "localhost";

  char service[] = "80"; //http/80, ssh/22, domain/53 …

  struct addrinfo hints, *res;
  // hints用于筛选指定类型结果
  bzero(&hints, sizeof(hints));
  // hints.ai_flags = AI_PASSIVE;
 // hints.ai_flags |= AI_CANONNAME;
  // hints.ai_flags |= AI_CANONNAME | AI_PASSIVE;
  //hints.ai_flags |= AI_V4MAPPED | AI_ALL;
 //  hints.ai_flags |= AI_NUMERICSERV;
  // hints.ai_family = AF_UNSPEC;
 //  hints.ai_family = AF_INET6;
   hints.ai_socktype = SOCK_STREAM;
 // hints.ai_socktype = SOCK_DGRAM;

  int ret;
  if ((ret = getaddrinfo("localhost", "http", NULL, &res)) < 0){
    printf("get addrinfo error: %s\n", gai_strerror(ret)); // getaddrinfo error
    return;
  }

  // 返回成功且ai_flags设置AI_CANONNAME，有且今有第一个addrinfo中规范主机名不为空
  printf("canonname: %s\n", res->ai_canonname); 

  // 打印输出
  for (; res != NULL; res = res->ai_next){
    char family[16] = {0};
    char socktype[16] = {0};
    char protocal[16] = {0};
    char ip[INET6_ADDRSTRLEN] = {0};
    int port; // 不指定服务即参数service传递NULL时，返回端口为0

    if (res->ai_family == AF_INET){
      memcpy(family, "AF_INET", strlen("AF_INET"));

      sockaddr_in *addr = (sockaddr_in *)res->ai_addr;
      inet_ntop(res->ai_family, &addr->sin_addr, ip, res->ai_addrlen);
      port = ntohs(addr->sin_port);
    }
    else if (res->ai_family == AF_INET6){
      memcpy(family, "AF_INET6", strlen("AF_INET6"));

      sockaddr_in6 *addr = (sockaddr_in6 *)res->ai_addr;
      inet_ntop(res->ai_family, &addr->sin6_addr, ip, res->ai_addrlen);
      port = ntohs(addr->sin6_port);
    }
    else{
      printf("unknow famaly %d\n", res->ai_family);
      continue;
    }

    switch (res->ai_socktype){
      case SOCK_DGRAM: memcpy(socktype, "SOCK_DGRAM", strlen("SOCK_DGRAM")); break;
      case SOCK_STREAM:memcpy(socktype, "SOCK_STREAM", strlen("SOCK_STREAM")); break;
      case SOCK_RAW: memcpy(socktype, "SOCK_RAW", strlen("SOCK_RAW")); break;
      default:
        printf("\nunknow socktype %d\n", res->ai_socktype);
        memcpy(socktype, "UNKNOW", strlen("UNKNOW"));
    }

    switch (res->ai_protocol){
      case IPPROTO_IP: memcpy(protocal, "IPPROTO_IP", strlen("IPPROTO_IP"));break;
      case IPPROTO_UDP: memcpy(protocal, "IPPROTO_UDP", strlen("IPPROTO_UDP")); break;
      case IPPROTO_TCP: memcpy(protocal, "IPPROTO_TCP", strlen("IPPROTO_TCP"));break;
      default:
        printf("unknow protocal %d\n", res->ai_protocol);
        memcpy(protocal, "UNKNOW", strlen("UNKNOW"));
    }

    printf(
      "\nai_family: %s\n"
      "ai_socktype: %s\n"
      "ai_protocol: %s\n"
      "ip addres: %s %d\n",
      family, socktype, protocal, ip, port);
  }

  freeaddrinfo(res); // 使用getaddrinfo后必须调用以释放动态分配的res内存
}

static void test_getnameinfo()
{
  printf("\n\n=====================================================\n");
  printf("test getnameinfo\n\n");


  char host[] = "127.0.0.1";

  char hbuf[NI_MAXHOST]; 
  char sbuf[NI_MAXSERV];

  int hbuflen = sizeof(hbuf);
  int sbuflen = sizeof(sbuf);

  sockaddr_in addr;
  addr.sin_family = AF_INET;
  inet_pton(AF_INET, host, &addr.sin_addr);
  addr.sin_port = htons(8080);

  
  int flags = 0;  
  //flags |= NI_DGRAM;

  int ret = getnameinfo((struct sockaddr *)&addr, sizeof(addr),
                        hbuf, hbuflen, sbuf, sbuflen, flags);

  if (ret < 0){
    printf("getnameinfo error: %s\n", gai_strerror(ret)); // getnameinfo error
    return;
  }

  printf("hbuf: %s, sbuf: %s\n", hbuf, sbuf);
}