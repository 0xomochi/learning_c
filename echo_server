/*echo_server*/

#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <netdb.h>

#define TIMEOUT 5
#define BUF_LEN BUFSIZ-1



int main (void)
{

  struct timeval tv;
  fd_set readfds, rfds;
  int ret;
  int sock1, sock2;

  int maxfd ;



  int sock_req;
  int sock_clients[1024];
  int nclients;

  int max_client;




  struct addrinfo hints;          /* input for getaddrinfo()  */
  struct addrinfo *res = NULL;    /* output from getaddrinfo()  */
  struct addrinfo *res0;


  struct sockaddr_storage ss;
  socklen_t ss_len = sizeof(ss);
  int error;
  int i;


  int len;
  char buf[BUF_LEN+1];


  memset(&hints, 0, sizeof(hints));

  hints.ai_family = PF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  error = getaddrinfo(NULL, "12345", &hints, &res0);

  if (error ){
    fprintf(stderr, "getaddrinfo error\n");
    exit(1);
  }

  sock_req = socket(res0->ai_family, res0->ai_socktype, res0->ai_protocol);
  if (bind(sock_req, res0->ai_addr, res0->ai_addrlen) < 0) {
      perror("bind");
  }
  listen(sock_req, 5);

  freeaddrinfo(res0);


  FD_SET(sock_req, &readfds);
  max_client = sock_req;
  nclients = 0;

  while(1){
    FD_ZERO(&readfds);
    FD_SET(sock_req, &readfds);
    for ( i = 0;i< nclients; i++) {

      FD_SET(sock_clients[i],&readfds);
      if (max_client < sock_clients[i]) {
	max_client = sock_clients[i];

      }
    }

    memcpy(&rfds, &readfds, sizeof(fd_set));

    select(max_client + 1, &rfds, NULL, NULL, NULL);

    if(FD_ISSET(sock_req, &rfds)) {
      sock_clients[nclients] = accept(sock_req, (struct sockaddr *)&ss, &ss_len);
      nclients++;
      fprintf(stderr, "nclients %d\n", nclients);
      continue;
    }

    int rec;


    for (i = 0; i<nclients; i++) {



      if (FD_ISSET(sock_clients[i], &rfds) ){
	//echo_back_to_other();

	fprintf(stderr, "clients %d \n", i);
	memset(buf, 0, BUFSIZ);



	len = recv(sock_clients[i], buf, BUFSIZ-1, 0);
	if (len < 0) {perror("recv");}




	buf[len] = '\0';

	for (int j = 0;  j < nclients ; j++) {

	  fprintf(stderr, "buf %lu, %s", strlen(buf), buf);
	  rec = send(sock_clients[j], buf, sizeof(buf), 0);
	}


	if (strcmp(buf,"") == 0 ){
	  fprintf(stderr, "Client %d is out.\n", i);


	  for (int j = i+1; j < nclients;j++) {
	    sock_clients[j-1] = sock_clients[j];
	  }
	  nclients--;
	  FD_CLR(sock_clients[nclients], &rfds);




	}


      }



    }
  }

}
