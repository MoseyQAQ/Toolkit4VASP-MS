#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "sys/un.h"
#include "psub.h"

#define UNIXSTR_PATH "/tmp/psub.srt"
#define LISTENQ 5
#define BUFFER_SIZE 256
//test version


int main(int argc, char *argv[])
{

    char path[BUFFER_SIZE], ProjectName[BUFFER_SIZE];
    getcwd(path, BUFFER_SIZE);  //get current path;
    if(argc == 2){
        getFolderName(path, ProjectName);
    }else if(argc == 3){
        strcpy(ProjectName, argv[2]);
    }  else{
        printf("Error Usage.\n");
        exit(-1);
    }    // get Project name;
    char script[BUFFER_SIZE];
    strcpy(script, argv[1]); //get script's name;
    if(detectFiles(script) == -1){
        perror("Script doesn't exist. SYSTEM");
        exit(-1);
    }

    char CODE_TO_SERVER[BUFFER_SIZE];
    sprintf(CODE_TO_SERVER, "PSUB|%s|%s|%s",path, script,ProjectName);//generate code sent to server;
    printf("%s\n",CODE_TO_SERVER);
    int sockfd;
    struct sockaddr_un servaddr;
    char mes_from_server[BUFFER_SIZE];
    sockfd = socket(AF_LOCAL, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sun_family =AF_LOCAL;
    strcpy(servaddr.sun_path, UNIXSTR_PATH);
    if(connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) == -1){
        perror("Error: Can't connect to pSUB-server. SYSTEM");
        exit(-1);
    }
    // connect to server.

    write(sockfd, CODE_TO_SERVER, strlen(CODE_TO_SERVER));
    read(sockfd, mes_from_server, BUFFER_SIZE);
    printf("%s",mes_from_server);
    return 0;

}