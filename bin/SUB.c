#include"head.h"
#include"detect.h"
#include"dirent.h"
typedef struct job_info{    //the structure data of job_info
	int _id;
	char _path[256];
	int _pot;	
}job_info;
void run_vasp(char *_tar_path,int n)
{
	char command_sub[100],creat_pot[100];
	if(!chdir(_tar_path)) printf("Changed to the target Dir. Starting VASP.......\n");
	if(detect_potcar()==-1) 
	{printf("No POTCAR.Creating......\n");strcpy(creat_pot,"POT");system(creat_pot);}
	sprintf(command_sub,"mpirun -np %d vasp_std",n);
	system(command_sub);
	
	
}
int sub_all(job_info *task,int n)
{				
		printf("All detected %d JOBS will be submitted.You sure?[y/n]:",n);
			if(getchar()=='y'){
				for(int j=1;j<=n;j++){
					printf("Running id= %d\n",j);
					run_vasp((task+j)->_path,12);    //develop a function,get cores in configure file.
				}
		}else {printf("STOP SUB.\n");exit(0);}
}
int mode_choice()
{
	//get information form .path_temp
	job_info task[100];
	FILE *_reader;
	_reader=fopen(".path_temp","r");
	if(_reader==NULL) {printf("Something goes wrong!\n"); exit(1);}
	int i=1;task[0]._id=0,task[0]._pot=0;
	fscanf(_reader,"%s",task->_path);
	while(fscanf(_reader,"%d%s%d",&task[i]._id,task[i]._path,&task[i]._pot)!=EOF){
		printf("%d %s %d\n",task[i]._id,task[i]._path,task[i]._pot);
		i++;
	}
	//mode_choice part;
	int options[100]={0},count_temp=0;char ch;
	printf("Pick the ID you want to run(0=all run,a negative number=end):");
	while((ch=getchar())&&ch!='\n'){
		ungetc(ch,stdin);
		scanf("%d",&options[count_temp]);
		count_temp++;
	}
	if(options[0]==0) {sub_all(task,i-1);return 0;}				 
	printf("You have picked %d JOBS:",count_temp);
	for(int j=0;j<count_temp;j++)printf("%d  ",options[j]);
	putchar('\n');
	printf("Do you Want to run?[y/n]:");
	if(getchar()=='y'){
		for(int temp=0;temp<count_temp;temp++){
		printf("Runing id= %d\n",options[temp]);
			run_vasp(task[options[temp]]._path,12);
		}
	}else {printf("STOP SUB.\n");exit(0);}
	
	
}
int main()
{
	char echo_path[256],current_path[256];
	strcpy(echo_path,"touch .path_temp;echo $(pwd) > .path_temp");
	system(echo_path);    //touch .path_temp,to write down pwd and targeted dir.
	getcwd(current_path,255);    //current_path=the working space.
	printf("Searching Dir:%s\n",current_path);
	printf("--------------Detected JOBS.------------\n");
	sub_task_check(current_path,current_path);      //sub_task_check: a function from dirent.h
	printf("------------------DONE------------------\n");
	chdir(current_path);    //switch to initial path.important
	printf("Do you want to continuce?[y/n]:");
	if(getchar()=='y'){
		getchar();
		mode_choice();
	}
	chdir(current_path);
	//system("rm .path_temp");
	return 0;
}
