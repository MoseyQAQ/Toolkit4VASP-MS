#include"head.h"
#include"detect.h"

#ifndef __DIRENT_H__
#define __DIRENT_H__
int sub_task_check(char *dirPATH,char *current_path)
{
	static int job_count=0;
	DIR *dir;
	char full_path[300],echo[256];
	dir=opendir(dirPATH);
	if(detect_project_sub(dirPATH)){
		job_count++;
		printf("ID:%d   %s  check passed. ",job_count,dirPATH);
		if(detect_potcar()==-1) printf("No POTCAR.\n");
		else putchar('\n');
		sprintf(echo,"echo %d %s %d >> %s/.path_temp",job_count,dirPATH,detect_potcar(),current_path);
		system(echo);
	}
	if(!dir){
		printf("Error! Failed to open directory.\n");
		return -1;
	}
	struct dirent *info;
	while(1){
		if((info=readdir(dir))==0) break;
		if(strncmp(info->d_name,".",1)==0) continue;
		if(info->d_type==4){
			sprintf(full_path,"%s/%s",dirPATH,info->d_name);
			sub_task_check(full_path,current_path);
		}
	}
	closedir(dir);
	return 0;
}
#endif
