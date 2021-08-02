#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char command[1000]="cat ";
int detect_pos()
{
	FILE *pos;
	pos=fopen("POSCAR","r");
	if(pos==NULL){
		printf("There is no POSCAR file! Please check.");
		putchar('\n');
		exit(1);
	}
	else return 1;
}
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
int main(){
	detect_pos();
	touch_temp();
	read_generate_command();
	system(command);
	system("rm .temp");
	printf("\nThe POSCAR file has been created.\n");
	printf("--------check information-------\n");
	system("grep TIT POTCAR");
	printf("-----------Done!----------------\n");
	return 0;
}
