#include "time.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "threads.h"
#define BUFFER_SIZE 256
#ifndef __PSUB_H__
#define __PSUB_H__

struct waiting_queue{
    int ID;
    int status;
    char path[BUFFER_SIZE];
    char script[BUFFER_SIZE];
    char name[BUFFER_SIZE];
    char sub_time[BUFFER_SIZE];
};

struct working_queue{
    int ID;
    char path[BUFFER_SIZE];
    char script[BUFFER_SIZE];
    char name[BUFFER_SIZE];
    char sub_time[BUFFER_SIZE];
    char start_time[BUFFER_SIZE];
    int status;
};

struct  finished_quque{
    int ID;
    char path[BUFFER_SIZE];
    char script[BUFFER_SIZE];
    char name[BUFFER_SIZE];
    char sub_time[BUFFER_SIZE];
    char start_time[BUFFER_SIZE];
    char end_time[BUFFER_SIZE];

};

char *getTime(char *timegetted)
{
    char buf[256];
    struct tm *ptr;
    time_t it;
    time(&it);
    ptr = localtime(&it);
    sprintf(buf, "%4d/%02d/%02d  %d:%d:%d",ptr->tm_year, ptr->tm_mon, ptr->tm_mday, ptr->tm_hour, ptr->tm_min, ptr->tm_sec);
    strcpy(timegetted, buf);
    return timegetted;
}
int detectFiles(char *script)
{
    FILE *opener;
    opener = fopen(script, "r");
    if(opener == NULL)
        return -1;
    else{
        fclose(opener);
        return 1;
    }
}   // 1 == exists; -1 == not
char *getFolderName(char *PATH,char *FolderName)
{
    int i,count=0;
    for(i=strlen(PATH)-1;PATH[i]!='/';i--);
    i++;
    for(;PATH[i]!='\0';i++){
        FolderName[count]=PATH[i];
        count++;
    }FolderName[count]='\0';
    return FolderName;

}

#endif
