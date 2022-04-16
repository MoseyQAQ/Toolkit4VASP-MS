#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "signal.h"
#include "sys/param.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "sys/un.h"
#include "sys/stat.h"
#include "psub.h"

#define UNIXSTR_PATH "/tmp/psub.srt"
#define LISTENQ 5
#define BUFFER_SIZE 256

void init_daemon(void)
{
    int pid, i;
    if(pid = fork())
        exit(0);
    else if(pid < 0)
        exit(1);
    if(pid = fork())
        exit(0);
    else if(pid < 0)
        exit(1);
    for(i = 0; i < NOFILE; ++i)
        close(i);
    umask(0);
    return;
}

int main(int argc, char *argv[])
{
    init_daemon();

    char haha[BUFFER_SIZE];int c=0;
    for(int i=1;i<strlen(argv[1])-1;i++)
        haha[c++]=argv[1][i];
    chdir(argv[1]);
    char command[BUFFER_SIZE];
    char pwd[BUFFER_SIZE];
    getcwd(pwd,BUFFER_SIZE);
    char ha[BUFFER_SIZE];
    sprintf(command, "bash %s > %s.out", argv[2], argv[3]);
    system(command);// start script.

    //socket.
    int sockfd;
    struct sockaddr_un servaddr;
    sockfd = socket(AF_LOCAL, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sun_family =AF_LOCAL;
    strcpy(servaddr.sun_path, UNIXSTR_PATH);
    connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

    //write
    char mes_from_server[BUFFER_SIZE];
    char CODE_TO_SERVER[BUFFER_SIZE];
    sprintf(CODE_TO_SERVER, "pdaemon %s", argv[4]);
    write(sockfd, CODE_TO_SERVER, strlen(CODE_TO_SERVER));
    read(sockfd, mes_from_server, BUFFER_SIZE);
    printf("%s",mes_from_server);
    return  0;
}
