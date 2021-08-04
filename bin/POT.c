#include"head.h"
#include"detect.h"
char command[1000]="cat ";
void touch_temp()
{
	system("touch .temp;cat POSCAR | head -n 6 | tail -n 1 > .temp;");
}
void read_generate_command()
{
	FILE *pot;pot=fopen(".temp","r");
	char elements[20][4];int count=0;
	char root[1000]="$lib_PBE/";
	while(fscanf(pot,"%s",elements[count])!=EOF){
		strcat(root,elements[count]);strcat(root,"/POTCAR");
		strcat(command,root);
		strcat(command," ");
		strcpy(root,"$lib_PBE/");
		count++;
	}
	strcat(command," > POTCAR");
	printf("You have %d type(s) of element in the POSCAR file:\n",count);
	for(int j=0;j<count;j++)
		printf("%s   ",elements[j]);
	
}
void pot_core_function()
{
	touch_temp();
	read_generate_command();
	system(command);
	system("rm .temp");
	printf("\nThe POTCAR file has been created.\n");
	printf("--------check information-------\n");
	system("grep TIT POTCAR");
	printf("-----------Done!----------------\n");
}
int main(){
	if(detect_poscar()==-1) {              //detect_poscar :a function from "detect.h"
		printf("There is no POSCAR file detected. Please check.\n");
		exit(1);
	}
	printf("POSCAR file detected!\n");
	if(detect_potcar()==1){               //detect_potcar: a function from "detect.h"
		printf("There is a POTCAR file already. Want to  overwrite?(y/n)\n");
		if(getchar()=='y')
			pot_core_function();
		else
			return 0;
		}
	else pot_core_function();
	return 0;
}
