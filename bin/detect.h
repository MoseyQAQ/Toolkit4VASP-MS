#include"head.h"
/*
functions:
	1.detect_output_files():to check if there is any output files.If it does,return 1; else 0;
	2.detect_poscar,detect_incar,detect_poscar,detect_potcar:if there is a targeted file,return 1;otherwise, retrun -1;
	3.detect_input_files():to check input files.with all 4 input files,return 1.don't have potcar, return 0;else return -1;
	4.detect_project_sub:if it's a job,return 1; else return 0;
	
target:
	function:
		1.sub:automatically detect the job you want to sub.and sub it;
			logic:if a floder has only "INCAR,POSCAR,KPOINTS",it's recongized
			as a job,if there is no POTCAR.it will be created automatically.
		2.continue_task:
			
	
*/
#ifndef __DETECT_H__
#define __DETECT_H__
int detect_output_files()
{
	char output_files[13][12]={
	"CHG","CHGCAR","CONTCAR","DOSCAR",
	"ELGENVAL","IBZKPT","OSZICAR","OUTCAR",
	"PCDAT","REPORT","vasprun.xml","WAVECAR","XDATCAR"
	};
	FILE *output;
	for(int i=0;i<13;i++){
		output=fopen(output_files[i],"r");
		if(output != NULL) {
			fclose(output);
			return 1;
		}
	}
	return 0;
	
}
int detect_poscar()
{
	FILE *pos;
	pos=fopen("POSCAR","r");
	if(pos==NULL)
		return -1;
	else {fclose(pos);return 1;}
}
int detect_kpoints()
{
	FILE *kpoints;
	kpoints=fopen("KPOINTS","r");
	if(kpoints==NULL)
		return -1;
	else {fclose(kpoints);return 1;}
}
int detect_incar()
{
	FILE *incar;
	incar=fopen("INCAR","r");
	if(incar==NULL)
		return -1;
	else {fclose(incar);return 1;}
}
int detect_potcar()
{
	FILE *potcar;
	potcar=fopen("POTCAR","r");
	if(potcar==NULL)
		return -1;
	else {fclose(potcar);return 1;}
}
int detect_input_files()
{
	if((detect_poscar()==1)&&(detect_kpoints()==1)&&(detect_incar()==1)&&(detect_potcar()==1))
		return 1;
	else if((detect_poscar()==1)&&(detect_kpoints()==1)&&(detect_incar()==1)&&(detect_potcar()==-1))    
		return 0;										
	else 
		return -1;
}
int detect_project_sub(char *PATH)
{	
	chdir(PATH);
	if((detect_output_files()==1) || (detect_input_files()==-1))	return 0;
	else return 1;
}
int project_status()
{
	
}
#endif

