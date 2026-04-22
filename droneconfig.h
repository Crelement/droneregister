#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>

struct dronebank{
    char name[25];
    char password[20];
    char phonenum[11];
    char dronetype[20];
    float weight;
};

struct dronebank bufferzone;

struct dronebank *droneArray;   // 声明一个指针，尚未分配空间
int capacity=10;              // 记录当前分配的最大元素个数
int count=0;                  //count是总在册人数,number是编号
float min_weight=0;

uint8_t input(int number){
    printf("please enter your name\n");
    scanf("%s",droneArray[number].name);
    printf("enter your password\n");
    scanf("%s",droneArray[number].password);
    printf("enter your phonenumber\n");
    scanf("%s",droneArray[number].phonenum);
    printf("your dronetype\n");
    scanf("%s",droneArray[number].dronetype);
    printf("the weight of your drone\n");
    scanf("%f",&droneArray[number].weight);
    return 1;
}

void save(){
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

float sort(int number,float min_weight){
    if(droneArray[number].weight<=min_weight){
        min_weight=droneArray[number].weight;
        memcpy(&bufferzone.weight,&droneArray[number-1].weight,sizeof(struct dronebank));
        memcpy(&droneArray[number-1].weight,&droneArray[number].weight,sizeof(struct dronebank));
        memcpy(&droneArray[number].weight,&bufferzone.weight,sizeof(struct dronebank));
    }
    return min_weight;
}

uint8_t registe(){   //command==2为登录 command==1是注册
   count++;
   memoryexpand();
   input(count-1);
   min_weight=sort(count-1,min_weight);  
    return 0;
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


