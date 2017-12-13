#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "mkaddr.h"
 
#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif
 
extern int mkaddr(
				    void *addr,
			    int *addrlen,
			    char *str_addr,
			    char *protocol);

#define MAXQ 4

void doBroadcast();
 
/*
* This function reports the error and
* exits back to the shell:
*/
static void
displayError(const char *on_what) {
  fputs(strerror(errno),stderr);
  fputs(": ",stderr);
  fputs(on_what,stderr);
  fputc('\n',stderr);
  exit(1);
}

void doBroadcast() {
  int z;      /* Status return code */
  int s;      /* Socket */
  struct sockaddr_in adr_srvr;/* AF_INET */
  int len_srvr;               /* length */
  struct sockaddr_in adr_bc;  /* AF_INET */
  int len_bc;                 /* length */
  static int so_broadcast = TRUE;
  static char
  *sv_addr = "127.0.0:*",
  *bc_addr = "127.255.255.2 9097";
 
 /*
  * Form the server address:
  */
  len_srvr = sizeof adr_srvr;

  z = mkaddr(
 		  &adr_srvr,  /* Returned address */
		  &len_srvr,  /* Returned length */
		  sv_addr,    /* Input string addr */
		  "udp");     /* UDP protocol */
  	adr_srvr.sin_family = AF_INET;
  	adr_srvr.sin_port = (in_port_t)htons(9097);
		adr_srvr.sin_addr.s_addr = htonl(INADDR_ANY);

  if ( z == -1 )
	displayError("Bad server address");
 
 /*
  * Form the broadcast address:
  */
  len_bc = sizeof adr_bc;
 
  z = mkaddr(
	  &adr_bc, /* Returned address */
	  &len_bc, /* Returned length */
	  bc_addr, /* Input string addr */
	  "udp"); /* UDP protocol */
  	adr_bc.sin_addr.s_addr = htonl(INADDR_BROADCAST);
  	adr_bc.sin_port = (in_port_t)htons(9098);
 
  if ( z == -1 )
	displayError("Bad broadcast address");
 
 /*
  * Create a UDP socket to use:
  */
  s = socket(AF_INET,SOCK_DGRAM,0);
  if ( s == -1 )
	displayError("socket()");
 
 /*
  * Allow broadcasts:
  */
  z = setsockopt(s,
				 SOL_SOCKET,
				 SO_BROADCAST,
				 &so_broadcast,
				 sizeof so_broadcast);
 
  if ( z == -1 )
	displayError("setsockopt(SO_BROADCAST)");

 /*
  * Bind an address to our socket, so that
  * client programs can listen to this
  * server:
  */
  z = bind(s,
		  (struct sockaddr *)&adr_srvr,
		  len_srvr);
 
  if ( z == -1 )
	displayError("bind()");
 
  for (;;) {

	 /*
	  * Broadcast the updated info:
	  */

	  // char * msg = "Hi I am Udara";
  	char buffer[256];
  	// printf("Please enter the message :\n");
    // readHumidity();
	// bzero(buffer, 256);
	// fgets(buffer,255,stdin);
    strcpy(buffer, read_dht11_dat());

	  z = sendto(s,
				 buffer,
				 strlen(buffer),
				 0,
				(struct sockaddr *)&adr_bc,
				len_bc); 
	 
	  if ( z == -1 )
		displayError("sendto()");

	  sleep(4);
  }
 
}
