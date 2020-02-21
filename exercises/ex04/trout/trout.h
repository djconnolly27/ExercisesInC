#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <time.h>
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/un.h>
#include <stdarg.h>
#include <syslog.h>

#define MAXLINE 4096
#define BUFSIZE 1500


typedef struct rec {                /* outgoing UDP data */
  u_short seq;          /* sequence number */
} Rec;



                  /* length of a socket address */
// int datalen = sizeof (Rec);         /* length of the data in a datagram */
// #define datalen sizeof (Rec)
// // int max_ttl = 30;
// #define max_ttl 30
extern int max_ttl;
extern int datalen;

/* the following are a few definitions from Stevens' unp.h */


#define max(a,b) ((a) > (b) ? (a) : (b))

/* the following are prototypes for the Stevens utilities in util.c */


void Sendto(int fd, const void *ptr, size_t nbytes, int flags,
	    const struct sockaddr *sa, socklen_t salen);

void loop_ttl ();
