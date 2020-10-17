#ifndef __SOCK_H_
#define __SOCK_H_

#include	<sys/types.h>	/* basic system data types */
#include	<sys/socket.h>	/* basic socket definitions */

#if TIME_WITH_SYS_TIME
#include	<sys/time.h>	/* timeval{} for select() */
#include	<time.h>		/* timespec{} for pselect() */
#else
#if HAVE_SYS_TIME_H
#include	<sys/time.h>	/* includes <time.h> unsafely */
#else
#include	<time.h>		/* old system? */
#endif
#endif

#include	<netinet/in.h>	/* sockaddr_in{} and other Internet defns */
#include	<arpa/inet.h>	/* inet(3) functions */
#include	<errno.h>
#include	<fcntl.h>		/* for nonblocking */
#include	<netdb.h>
#include	<signal.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<sys/stat.h>	/* for S_xxx file mode constants */
#include	<sys/uio.h>		/* for iovec{} and readv/writev */
#include	<unistd.h>
#include	<sys/wait.h>
#include	<sys/un.h>		/* for Unix domain sockets */


#ifdef	HAVE_SYS_SELECT_H
# include	<sys/select.h>	/* for convenience */
#endif

#ifdef	HAVE_POLL_H
# include	<poll.h>		/* for convenience */
#endif

#ifdef	HAVE_STRINGS_H
# include	<strings.h>		/* for convenience */
#endif

/* Three headers are normally needed for socket/file ioctl's */
#ifdef	HAVE_SYS_IOCTL_H
# include	<sys/ioctl.h>
#endif


#ifndef	HAVE_BZERO
#define	bzero(ptr,n)		memset(ptr, 0, n)
/* $$.If bzero$$ */
/* $$.If memset$$ */
#endif


/* Following could be derived from SOMAXCONN in <sys/socket.h>, but many
   kernels still #define it as 5, while actually supporting many more */
#define	LISTENQ		1024	/* 2nd argument to listen() */

/* Miscellaneous constants */
#define	MAXLINE		4096	/* max text line length */
#define	BUFFSIZE	8192	/* buffer size for reads and writes */


/* prototypes for our own library functions */
struct addrinfo *host_serv(const char *, const char *, int, int);
int		 tcp_connect(const char *, const char *);
int		 tcp_listen(const char *, const char *, socklen_t *);
int		 udp_client(const char *, const char *, sockaddr **, socklen_t *);
int		 udp_connect(const char *, const char *);
int		 udp_server(const char *, const char *, socklen_t *);

/* prototypes for our Unix wrapper functions: see {Sec errors} */
void	*Calloc(size_t, size_t);
void	 Close(int);
void	 Dup2(int, int);
int		 Fcntl(int, int, int);
void	 Gettimeofday(struct timeval *, void *);
int		 Ioctl(int, int, void *);

void	*Malloc(size_t);
int	 Mkstemp(char *);
void	*Mmap(void *, size_t, int, int, int, off_t);
int		 Open(const char *, int, mode_t);

ssize_t	 Read(int, void *, size_t);
void	 Sigaddset(sigset_t *, int);
void	 Sigdelset(sigset_t *, int);
void	 Sigemptyset(sigset_t *);
void	 Sigfillset(sigset_t *);
int		 Sigismember(const sigset_t *, int);
void	 Sigpending(sigset_t *);
void	 Sigprocmask(int, const sigset_t *, sigset_t *);
void	 Unlink(const char *);
void	 Write(int, void *, size_t);

/* prototypes for our own library wrapper functions */
struct addrinfo *Host_serv(const char *, const char *, int, int);

int		 Tcp_connect(const char *, const char *);
int		 Tcp_listen(const char *, const char *, socklen_t *);
int		 Udp_client(const char *, const char *, sockaddr **, socklen_t *);
int		 Udp_connect(const char *, const char *);
int		 Udp_server(const char *, const char *, socklen_t *);


/* prototypes for our socket wrapper functions: see {Sec errors} */
int		 Accept(int, sockaddr *, socklen_t *);
void	 Bind(int, const sockaddr *, socklen_t);
void	 Connect(int, const sockaddr *, socklen_t);
void	 Getpeername(int, sockaddr *, socklen_t *);
void	 Getsockname(int, sockaddr *, socklen_t *);
void	 Getsockopt(int, int, int, void *, socklen_t *);
void	 Listen(int, int);
#ifdef	HAVE_POLL
int		 Poll(struct pollfd *, unsigned long, int);
#endif
int		 Select(int, fd_set *, fd_set *, fd_set *, struct timeval *);
void	 Send(int, const void *, size_t, int);
void	 Sendto(int, const void *, size_t, int, const sockaddr *, socklen_t);
void	 Sendmsg(int, const struct msghdr *, int);
void	 Setsockopt(int, int, int, const void *, socklen_t);
void	 Shutdown(int, int);
int		 Sockatmark(int);
int		 Socket(int, int, int);
void	 Socketpair(int, int, int, int *);
void	 Writen(int, void *, size_t);


void	 err_dump(const char *, ...);
void	 err_msg(const char *, ...);
void	 err_quit(const char *, ...);
void	 err_ret(const char *, ...);
void	 err_sys(const char *, ...);

#endif // __SOCK_H_