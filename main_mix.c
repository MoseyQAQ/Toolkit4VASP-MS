#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
void r4rom_xcd(char filedir[],char filename[]);
void r4rom_outmol(char filedir[],char filename[]);
void manu()
{
        printf("====================================================================\n");
        printf("=================1.import data from file.===========================\n");
        printf("=================2.convert data end export==========================\n");
        printf("====================================================================\n");
        printf("Chose the mode:");
}
typedef struct data
{
    char ID[10];
    double e;
    int type;
    int shape;
}data;
typedef struct xcdinfo
{
    int steps;
    double energy;
}xcdinfo;
void bubblesort(data tar[],int n)
{
    data temp;
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-1-i;j++){
            if(tar[j].e<tar[j+1].e){
                temp=tar[j];
                tar[j]=tar[j+1];
                tar[j+1]=temp;
            }
        }
    }
}
void function2()
{
    data tar[100];
    FILE *open,*write;
    int i=0;char ch;
    printf("Ensure that there isn't an output.dat in your working dictionary！！\n");
    printf("Press any key to import the data.\n");
    getchar();
    printf("============================INPUT===================================\n");
    open=fopen("input.dat","r");
    if(open==NULL)
    {
        printf("Error,the input.dat doesn't exist.\n");
        return 1;
    }
    else{
        while(!feof(open)){
            fscanf(open,"%s%lf%d%d",tar[i].ID,&tar[i].e,&tar[i].type,&tar[i].shape);
            printf("%s    %.10lf    %d    %d\n",tar[i].ID,tar[i].e,tar[i].type,tar[i].shape);
            i++;
        }//用input.dat中接收
        printf("============================END======================================\n");
        printf("Press any key to sort the data.\n");
        getchar();
        printf("===========================OUTPUT====================================\n");
        bubblesort(tar,i);//排序
        for(int j=0;j<i;j++){
            printf("%s    %.10lf    %d    %d\n",tar[j].ID,tar[j].e,tar[j].type,tar[j].shape);
        }
        printf("============================END======================================\n");
        printf("save the result?(y/n):");
        char ch=getchar();
        if(ch=='y'||ch=='yes'||ch=='1'){
            printf("The file will be saved as csv.Be careful,the original csv file will be covered.\nEnter the filename:");
            char filename[100];char csv[]=".csv";
            scanf("%s",filename);
            strcat(filename,csv);
            write=fopen(filename,"w+");
            //创建filename的csv文件
            printf("Chose the mode you like:\n  1.convert to eV;\n  2.convert to relative;\n  3.Default;\nTips:you can choose both of them.\n");
            int mode_choice;
            scanf("%d",&mode_choice);
            //选择模式：1，转化单位为eV；2，转化为相对；3，默认；1和2可同时选
            if(mode_choice==3){
                for(int j=0;j<i;j++)
                    fprintf(write,"%s,%.10lf,%d,%d\n",tar[j].ID,tar[j].e,tar[j].type,tar[j].shape);
            }
            else if(mode_choice==1){
                for(int j=0;j<i;j++)
                    fprintf(write,"%s,%.15lf,%d,%d\n",tar[j].ID,tar[j].e*27.211,tar[j].type,tar[j].shape);
            }
            else if(mode_choice==2){
                for(int j=0;j<i;j++)
                    fprintf(write,"%s,%.10lf,%d,%d\n",tar[j].ID,tar[j].e-tar[i-1].e,tar[j].type,tar[j].shape);
            }
            else if((mode_choice==12)||(mode_choice==21)){
                for(int j=0;j<i;j++){
                    fprintf(write,"%s,%.15lf,%d,%d\n",tar[j].ID,(tar[j].e-tar[i-1].e)*27.211,tar[j].type,tar[j].shape);
                }
            }
            printf("DONE!\n");
            system("pause");
        }
        fclose(open);fclose(write);
    }
}
void function1()
{
    char filedir[1000];char filename[100],file_type[20];int count=0,j=0;
    printf("The location of input file(you can also pull it into here):");
    gets(filedir);
    int filelen=strlen(filedir);
    //下面开始读取文件名
    for(int i=filelen;filedir[i]!=92;i--)
        count++;
    for(int i=filelen-count+1;filedir[i];i++){
        filename[j]=filedir[i];
        j++;
    }
    filename[j]='\0';
    //获取文件名结束
    //识别文件类型，目前支持outmol，energy（xcd）文件！
    if(filename[strlen(filename)-1]=='d'){
        strcpy(file_type,"energy.xcd");
    }else if(filename[strlen(filename)-1]=='l'){
        strcpy(file_type,"outmol");
    }else {printf("This type of file are not support now!\n");exit (1);}
    printf("Filename:%s,identified as the %s file\n",filename,file_type);
    if(strcmp(file_type,"energy.xcd")==0){
        r4rom_xcd(filedir,filename);
    }else if(strcmp(file_type,"outmol")==0){
        r4rom_outmol(filedir,filename);
    }

}
int main()
{
    manu();
    int manu_choice;
    scanf("%d",&manu_choice);
    if(manu_choice==2){
        system("cls");
        function2();
    }else if(manu_choice==1)
    {
        getchar();
        system("cls");
        function1();
    }
    return 0;
}
void r4rom_xcd(char filedir[],char filename[])
{
    FILE *read;
    read=fopen(filedir,"r");
}
void r4rom_outmol(char filedir[],char filename[])
{

}
