/*echo_client*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <sys/types.h>
#include <pwd.h>
#include <signal.h>




void err_func(char *msg)
{
perror(msg);
exit(EXIT_FAILURE);
}


void handler(int signo) {
  /* handle SIGCHLD */
  exit(EXIT_SUCCESS);

}

int main(int argc, char **argv)
{
  int sockfd, len, sockfd2;
  char buf[BUFSIZ];
  char buf2[BUFSIZ];
  struct sockaddr_in serv;
  unsigned short port;

  fd_set readfds, rfds, writefds, wfds;
  int ret = 1;

  int status;

  pid_t pid;

  char myname[1024];

  pid_t getppid(void);
  pid_t getpid(void);

  struct passwd *passwd;
  passwd = getpwuid(getuid());


  if(argc != 3){
    printf("usage: client server_ip server_port\n");
    exit(EXIT_FAILURE);
  }

  if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    err_func("socket");
  serv.sin_family = AF_INET ;
  port = (unsigned short)strtol(argv[2] , NULL , 10);
  serv.sin_port = htons(port);
  inet_aton(argv[1], &(serv.sin_addr));



  strcat(myname, passwd->pw_name);
  strcat(myname, "> ");

  if(connect(sockfd, (struct sockaddr *)&serv, sizeof(struct sockaddr_in)) < 0)
    err_func("connect");


  if ((pid = fork()) == 0){
    do {
      memset(buf,0,BUFSIZ);
      len = read(STDIN_FILENO, buf, BUFSIZ-strlen(myname)-1);
      buf[len] = '\0';
      memset(buf2,0,BUFSIZ);
      strcat(buf2,myname);
      strcat(buf2,buf);
      send(sockfd, buf2, strlen(buf2), 0);
    } while(strncasecmp(buf, "EXIT\r\n", 6) != 0 && strncasecmp(buf, "EXIT\n", 5) != 0);



    exit(EXIT_SUCCESS);

  } else {
    while(1) {



      len = recv(sockfd, buf, BUFSIZ, 0);
      if (len < 1) { break; }

      printf("%s", buf);

      signal(SIGCHLD,handler);

    }

    wait(NULL);
    close(sockfd);


  }
  return 0;

}
