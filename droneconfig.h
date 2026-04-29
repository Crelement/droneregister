#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>

typedef struct dronebank{
    char name[25];
    char password[20];
    char phonenum[12];
    char dronetype[20];
    char registertime[20];
    float weight;   
}Dronebank;
typedef struct flyapply{
    char dronetype[20];
    char applytime[20];
    char applyaddress[50];
    char applyreason[100];
    char logtime[20];
    char certificate[20];
    bool passstatus;
}Flyapply;
Dronebank*droneArray;
Flyapply*applyArray;
SYSTEMTIME st;
int capacity=1,count;

void input(int number){
    printf("please enter your name\n");
    scanf("%24s",droneArray[number].name);
    printf("enter your password\n");
    scanf("%19s",droneArray[number].password);
    printf("enter your phonenumber\n");
    scanf("%11s",droneArray[number].phonenum);
    printf("your dronetype\n");
    scanf("%19s",droneArray[number].dronetype);
    printf("the weight of your drone\n");
    scanf("%f",&droneArray[number].weight);
    GetSystemTime(&st);
    sprintf(droneArray[number].registertime,"%04d-%02d-%02d %02d:%02d:%02d",
        st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
}

void load(){
	FILE*fp=fopen("dronebank.txt","r");
	if(!fp){
        printf("File open failed. Initialize with empty data\n");
		count=0;
		droneArray=NULL;
        applyArray=NULL;
		return;
	}
	fscanf(fp,"%d",&count);
	droneArray=(struct dronebank*)malloc(count*sizeof(struct dronebank));
    applyArray=(struct flyapply*)malloc(count*sizeof(struct flyapply));
	if(!droneArray||!applyArray){
		printf("Memory allocation failed!\n");
		fclose(fp);
		exit(1);
	}
	for(int i=0;i<count;i++){
		fscanf(fp,"%24s %19s %11s %19s %f %19s",
			droneArray[i].name,
			droneArray[i].password,
			droneArray[i].phonenum,
			droneArray[i].dronetype,
			&droneArray[i].weight,
            droneArray[i].registertime);
	}
    capacity=count<=capacity?capacity+6:count;
	fclose(fp);
	printf("file load success\n");
	system("pause");
	system("cls");
}

void save(){
	FILE*fp=fopen("dronebank.txt","w");
	if(!fp){
        printf("File open failed. Data not saved!\n");
		return;
	}
	fprintf(fp,"%d\n",count);
	for(int i=0;i<count;i++){
		fprintf(fp,"%s %s %s %s %f %s\n",
			droneArray[i].name,
			droneArray[i].password,
			droneArray[i].phonenum,
			droneArray[i].dronetype,
			droneArray[i].weight,
            droneArray[i].registertime);
	}
	fclose(fp);
}

bool memoryexpand(){
    if(count>capacity){
        capacity*=2;
        Dronebank*temp=(Dronebank*)realloc(droneArray,capacity*sizeof(Dronebank));
        if(!temp){
            printf("Memory allocation failed!\n");
            return false;
        }
        droneArray=temp;
    }
    return true;
}

void registe(){
   ++count;
   if(!memoryexpand()){
        return;
   }
   input(count-1);
   insert_element(count-1);
   system("cls");
   printf("register success\n");
   system("pause");
}

void display(int number){
    printf("username: %s\n",droneArray[number].name);
    printf("password: %s\n",droneArray[number].password);
    printf("phonenumber: %s\n",droneArray[number].phonenum);
    printf("dronetype: %s\n",droneArray[number].dronetype);
    printf("weight: %f\n",droneArray[number].weight);
    printf("registertime: %s\n",droneArray[number].registertime);
    if(droneArray[number].weight>=250){
        printf("need special certificates CAAC\n");
    }
}

void list(){
    for(int i=0;i<count;++i){
        printf("%s\n",droneArray[i].name);
        printf("%s\n",droneArray[i].dronetype);
    }
    system("pause");
}

void applydisplay(int number){
    printf("applydronetype %s\n",applyArray[number].dronetype);  
    printf("applytime %s\n",applyArray[number].applytime);
    if(applyArray[number].passstatus){
        printf("pass\n");
   }else{
       printf("Approval in progress\n");
   }
}

void apply(int number){
    printf("enter the dronetype you want to fly\n");
    scanf("%19s",applyArray[number].dronetype);
    printf("enter the apply address\n");
    scanf("%49s",applyArray[number].applyaddress);
    printf("enter the apply reson\n");
    scanf("%99s",applyArray[number].applyreason);
    printf("enter the applytime\n");
    scanf("%19s",applyArray[number].applytime);
    printf("enter you certificate\n");
    scanf("%19s",applyArray[number].certificate);
    GetSystemTime(&st);
    sprintf(applyArray[number].logtime,"%04d-%02d-%02d %02d:%02d:%02d",
        st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
    applyArray[number].passstatus=false;
}

bool login(){
    char name[25];
    char password[20];
    printf("please enter yourname\n");
    scanf("%24s",name);
    printf("enter the password\n");
    scanf("%19s",password);
    for(int i=0;i<count;++i){
        if(!strcmp(droneArray[i].name,name)){
            if(!strcmp(droneArray[i].password,password)){
                display(i);
                printf("-------------------\n");
                printf("applyhistory\n");
                applydisplay(i);
                printf("-------------------\n");
                printf("apply for flying press 1\n");
                int c=_getch()-'0';
                switch (c){
                    case 1:
                        apply(i);
                        system("cls");
                        printf("please wait for approval\n");
                        system("pause");
                        break;
                    default:
                        break;
                }
                return true;
            }
            else{
                printf("Wrong password\n");
                system("pause");
                return false
            }
        }
    }
    printf("User not found\n");
    system("pause");
    return false;
}

void menu(){
    printf("Welcome to drone assignment system\n");
    printf("1.Register\n");
    printf("2.Login\n");
    printf("3.List\n");
    printf("4.Exit\n");
    int c=_getch()-'0';
    switch(c){
        case 1:registe();break;
        case 2:login();break;
        case 3:list();break;
        case 4:
            save();
            printf("presented by Cr\n");
            system("pause");
            exit(0);
    }
}