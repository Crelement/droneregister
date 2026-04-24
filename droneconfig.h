#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>

struct dronebank{
    char name[25];
    char password[20];
    char phonenum[12];
    char dronetype[20];
    float weight;
};

struct dronebank bufferzone;
struct dronebank *droneArray;
int capacity=10;
int count=0;
float min_weight=0;

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
}

void load(){
	FILE*fp=fopen("info.txt","r");
	if(fp==NULL){
		count=0;
		droneArray=NULL;
		return;
	}
	fscanf(fp,"%d",&count);
	droneArray=(struct dronebank*)malloc(count*sizeof(struct dronebank));
	if(droneArray==NULL){
		printf("Memory allocation failed!\n");
		fclose(fp);
		exit(1);
	}
	for(int i=0;i<count;i++){
		fscanf(fp,"%s %s %s %s %f",
			droneArray[i].name,
			droneArray[i].password,
			droneArray[i].phonenum,
			droneArray[i].dronetype,
			&droneArray[i].weight);
	}
    capacity=count<capacity?capacity:count;
	fclose(fp);
	printf("file load success\n");
	system("pause");
	system("cls");
}

void save(){
	FILE*fp=fopen("info.txt","w");
	if(fp==NULL){
		printf("file open failed\n");
		return;
	}
	fprintf(fp,"%d\n",count);
	for(int i=0;i<count;i++){
		fprintf(fp,"%s %s %s %s %f\n",
			droneArray[i].name,
			droneArray[i].password,
			droneArray[i].phonenum,
			droneArray[i].dronetype,
			droneArray[i].weight);
	}
	fclose(fp);
}

/*int memorycontrol(){
    droneArray=(struct dronebank*)malloc(capacity*sizeof(struct dronebank));
    if(droneArray==NULL) return 0;
}*/

int memoryexpand(){
    droneArray=(struct dronebank *)realloc(droneArray,capacity*sizeof(struct dronebank));
    if(count>=capacity){
        capacity+=6;
        droneArray=(struct dronebank*)realloc(droneArray,capacity*sizeof(struct dronebank));
    }
    if(droneArray==NULL){
        return 0;
    }
    return 1;
}

float sort(int number){
    for(int i=0;i<count;i++){
        if(droneArray[number].weight<=droneArray[i+1].weight  && droneArray[number].weight>=droneArray[i].weight){
            min_weight=droneArray[number].weight;
            memcpy(&bufferzone.weight,&droneArray[number-1].weight,sizeof(struct dronebank));
            memcpy(&droneArray[number-1].weight,&droneArray[number].weight,sizeof(struct dronebank));
            memcpy(&droneArray[number].weight,&bufferzone.weight,sizeof(struct dronebank));
        }
    }
    return droneArray[number].weight;
}

void registe(){   //command==2为登�? command==1是注�?
   count++;
   memoryexpand();
   input(count-1);
  // min_weight=sort(count-1);  
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

int login(){
    char name[25];
    char password[20];
    printf("please enter yourname\n");
    scanf("%s",name);
    printf("enter the password\n");
    scanf("%s",password);
    for(int i=0;i<count;++i){
        if(!strcmp(droneArray[i].name,name)&&!strcmp(droneArray[i].password,password)){
            display(i);
            system("pause");
            return 1;
        }
    }
    printf("error user or password\n");
    system("pause");
    return 0;
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