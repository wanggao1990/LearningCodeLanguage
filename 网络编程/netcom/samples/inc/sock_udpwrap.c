#include "sock_net.h"

int udp_connect(const char *host, const char *serv)
{
  int sockfd, n;
  struct addrinfo hints, *res, *ressave;

  bzero(&hints, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_DGRAM;

  if ((n = getaddrinfo(host, serv, &hints, &res)) != 0)
    err_quit("udp_connect error for %s, %s: %s",
             host, serv, gai_strerror(n));
  ressave = res;

  do{
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sockfd < 0)
      continue; /* ignore this one */

    if (connect(sockfd, res->ai_addr, res->ai_addrlen) == 0)
      break; /* success */

    Close(sockfd); /* ignore this one */
  } while ((res = res->ai_next) != NULL);

  if (res == NULL) /* errno set from final connect() */
    err_sys("udp_connect error for %s, %s", host, serv);

  freeaddrinfo(ressave);

  return (sockfd);
}
/* end udp_connect */

int Udp_connect(const char *host, const char *serv)
{
  int n;

  if ((n = udp_connect(host, serv)) < 0)
  {
    err_quit("udp_connect error for %s, %s: %s",
             host, serv, gai_strerror(-n));
  }
  return (n);
}

int udp_client(const char *host, const char *serv, sockaddr **saptr, socklen_t *lenp)
{
  int sockfd, n;
  struct addrinfo hints, *res, *ressave;

  bzero(&hints, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_DGRAM;

  if ((n = getaddrinfo(host, serv, &hints, &res)) != 0)
    err_quit("udp_client error for %s, %s: %s",
             host, serv, gai_strerror(n));
  ressave = res;

  do{
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sockfd >= 0)
      break; /* success */
  } while ((res = res->ai_next) != NULL);

  if (res == NULL) /* errno set from final socket() */
    err_sys("udp_client error for %s, %s", host, serv);

  *saptr = Malloc(res->ai_addrlen);
  memcpy(*saptr, res->ai_addr, res->ai_addrlen);
  *lenp = res->ai_addrlen;

  freeaddrinfo(ressave);

  return (sockfd);
}
/* end udp_client */

int Udp_client(const char *host, const char *serv, sockaddr **saptr, socklen_t *lenptr)
{
  return (udp_client(host, serv, saptr, lenptr));
}

int udp_server(const char *host, const char *serv, socklen_t *addrlenp)
{
  int sockfd, n;
  struct addrinfo hints, *res, *ressave;

  bzero(&hints, sizeof(struct addrinfo));
  hints.ai_flags = AI_PASSIVE;
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_DGRAM;

  if ((n = getaddrinfo(host, serv, &hints, &res)) != 0)
    err_quit("udp_server error for %s, %s: %s",
             host, serv, gai_strerror(n));
  ressave = res;

  do{
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sockfd < 0)
      continue; /* error - try next one */

    if (bind(sockfd, res->ai_addr, res->ai_addrlen) == 0)
      break; /* success */

    Close(sockfd); /* bind error - close and try next one */
  } while ((res = res->ai_next) != NULL);

  if (res == NULL) /* errno from final socket() or bind() */
    err_sys("udp_server error for %s, %s", host, serv);

  if (addrlenp)
    *addrlenp = res->ai_addrlen; /* return size of protocol address */

  freeaddrinfo(ressave);

  return (sockfd);
}
/* end udp_server */

int Udp_server(const char *host, const char *serv, socklen_t *addrlenp)
{
  return (udp_server(host, serv, addrlenp));
}
