#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "sys/un.h"
#include "psub.h"
#include "pthread.h"
// I love FaZe Clan Forever.
// I love Lyuchen Forever. 2002.9.2 - 2021-8.25. Rest in Peace.
//new function: swap 2 jobs;using lianbiao;stdout;
#define UNIXSTR_PATH "/tmp/psub.srt"
#define LISTENQ 5
#define BUFFER_SIZE 256
#define LOCAL
int listenfd, connfd;
socklen_t len;
struct  sockaddr_un servaddr, cliaddr;
char code_from_client[BUFFER_SIZE], timegetted[BUFFER_SIZE];
struct waiting_queue waitting_queue[50];
//struct working_queue working_queue[30];
int waitting_count = 0;
//int working_count = 0;

int socket_establish();
int listenClient();
int psub();
int pbatch();
int pcommand();
int code_translator();
int work_center();
int working();
int psubit(int id);
int remove_from_waiting_list(int id);
int remove_from_working_list(int index);

int main()
{
    #ifdef LOCAL
    freopen("log","w",stdout);
    #endif

    if(socket_establish() != 0){
        perror("socket_establish() ERROR!\n");
        exit(-1);
    }// establish a socket;
    while(1)
    {
        listen(listenfd, LISTENQ);
        len = sizeof(cliaddr);
        connfd = accept(listenfd, (struct  sockaddr *) &cliaddr, &len);
        listenClient();  // accept info from client and decode it.
        //work_center();   //check work list and wait list.
        working();   //submit status = 1 job to daemon, start job.
    }
    printf("out loop!!!\n");
    return 0;
}

int socket_establish()
{
    listenfd = socket(AF_LOCAL, SOCK_STREAM, 0);
    unlink(UNIXSTR_PATH);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sun_family = AF_LOCAL;
    strcpy(servaddr.sun_path, UNIXSTR_PATH);
    bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    return 0;
}
int listenClient()
{
    while(1)
    {
        bzero(code_from_client, BUFFER_SIZE);
        bzero(timegetted, BUFFER_SIZE);
        if(read(connfd, code_from_client, BUFFER_SIZE) == 0)
            break;
        else{
            write(connfd, "Psub-server: Data written successfully.\n", BUFFER_SIZE);
        }
        getTime(timegetted);
        printf("%s--Client: %s\n",timegetted,code_from_client);
        code_translator();
    }
    close(connfd);
    return 0;
}
int psub()
{
    if(waitting_count >= 50){
        perror("MAX waitting queue. Please wait.\n");
    }

    char buffer[5];
    char buffer_path[BUFFER_SIZE], buffer_script[BUFFER_SIZE], buffer_ProjectName[BUFFER_SIZE];
    sscanf(code_from_client, "%s|%s|%s|%s",buffer, buffer_path, buffer_script, buffer_ProjectName );

    strcpy(waitting_queue[waitting_count].path, buffer_path);
    strcpy(waitting_queue[waitting_count].script, buffer_script);
    strcpy(waitting_queue[waitting_count].name, buffer_ProjectName);
    waitting_queue[waitting_count].ID = waitting_count + 1;
    strcpy(waitting_queue[waitting_count].sub_time, timegetted);
    printf("Added to waiting-list: %d, %s, %s\n",waitting_queue[waitting_count].ID, waitting_queue[waitting_count].name, waitting_queue[waitting_count].sub_time);
    waitting_queue[waitting_count].status = 0;
    waitting_count++;
    return 0;
}
int pbatch()
{
    return 0;
}
int pcommand()
{
    return 0;
}
int code_translator()
{
    if(code_from_client[1] == 'S'){
        psub();
    }
    else if(code_from_client[1] == 'B'){
        pbatch();
    }
    else if(code_from_client[1] == 'C'){
        pcommand();
    }
    else if(code_from_client[1] == 'd'){
        char buffer[10];
        char buf[3];
        sscanf(code_from_client, "%s %s",buffer, buf);
        int buff = atoi(buf);
        waitting_queue[buff-1].status = 3; //chang code to 3; means it has finished.
        printf("id = %d finished!!!\n",buff);
    } else if(code_from_client[1] == 'K'){
        char buffer[10];
        char buf[3];
        sscanf(code_from_client, "%s %s",buffer, buf);
        int buff = atoi(buf);
        waitting_queue[buff-1].status = 3;
        printf("id = %d killed!!!\n",buff);
    }
    return 0;
}
int work_center()
{

   /*if(working_count == 0 & waitting_count != 0){
       printf("working center\n");
       working_queue[working_count].ID = working_count + 1;
       strcpy(working_queue[working_count].path, waitting_queue[0].path);
       strcpy(working_queue[working_count].script,waitting_queue[0].script);
       strcpy(working_queue[working_count].name, waitting_queue[0].name);
       strcpy(working_queue[working_count].sub_time, timegetted);
       getTime(working_queue[waitting_count].start_time);
       working_queue[working_count].status = 1;  // 1 means ready, but not be submitted.
       printf("Added to working-list:%d, %s, %s\n",working_queue[working_count].ID, working_queue[working_count].name, working_queue[waitting_count].start_time);
       working_count++;
       remove_from_waiting_list(1); //del first job in waitting list.
       waitting_count--;

   } // added first job in waitting list to working list; and the working list doesnt have any jobs.
    for(int i = 0;i < working_count; i ++){
        if(working_queue[i].status == 3){   //go through, if status == 3, this finished job remove to finished.
            remove_from_working_list(i);
            // move this finished job from working queue to finished queue.
        }
    }*/
    return 0;
}
int working()
{   //go through the working list, check whether there is status code = 1, submit it, change code 2;
    int i;
    for(i = 0; i < waitting_count; i++){   // when meet first job could be submiited.
        if( waitting_queue[i].status == 2){
            //psubit(i);   //generating argv;
            //waitting_queue[i].status = 2; //change CODE = 2, means submitted to daemon.
            //break;
            return 0;
        }
    }
    for(i = 0; i < waitting_count; i ++){
        if(waitting_queue[i].status == 0){
            psubit(i);
            waitting_queue[i].status = 2;
            break;
        }
    }
    return 0;
}
int psubit(int id)
{

    char buf[12] = "psub-daemon";
    char buffer[BUFFER_SIZE];
    sprintf(buffer, "%s \"%s\" %s %s %d",buf, waitting_queue[id].path, waitting_queue[id].script, waitting_queue[id].name, waitting_queue[id].ID);
    system(buffer);
    printf("psub-daemon: job %d started\n",waitting_queue[id].ID);
    return 0;
}
/*int remove_from_waiting_list(int id)
{
    for(int i = id - 1; i < waitting_count - 1; i++){
        strcpy(waitting_queue[i].path, waitting_queue[i+1].path);
        strcpy(waitting_queue[i].script, waitting_queue[i+1].script);
        strcpy(waitting_queue[i].name, waitting_queue[i+1].name);
        strcpy(waitting_queue[i].sub_time, waitting_queue[i+1].sub_time);
    }
    bzero(waitting_queue[waitting_count - 1].path, BUFFER_SIZE);
    bzero(waitting_queue[waitting_count - 1].script, BUFFER_SIZE);
    bzero(waitting_queue[waitting_count - 1].name, BUFFER_SIZE);
    bzero(waitting_queue[waitting_count - 1].sub_time, BUFFER_SIZE);
    return 0;
}
int remove_from_working_list(int index)
{

    return 0;
}
 */