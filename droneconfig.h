#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<stdlib.h>

struct dronebank{
    char name[25];
    char password[20];
    char phonenum[11];
    char dronetype[20];
    float weight;
};

struct dronebank *droneArray;   // 声明一个指针，尚未分配空间
int capacity=10;              // 记录当前分配的最大元素个数
int count=0;                  //count是总在册人数,number是编号
float min_weight=0;

int input(int number){
    printf("请输入姓名\n");
    scanf("%s",droneArray[number].name);
    printf("请输入密码\n");
    scanf("%s",droneArray[number].password);
    printf("请输入电话号码\n");
    scanf("%s",droneArray[number].phonenum);
    printf("请输入飞机类型\n");
    scanf("%s",droneArray[number].dronetype);
    printf("请输入飞机重量\n");
    scanf("%f",droneArray[number].weight);
    return 1;
}

void save(int i){
}

void display(int number);

int memorycontrol(int capacity){
    droneArray=(struct dronebank*)malloc(capacity*sizeof(struct dronebank));
    if(droneArray==NULL) return 0;
}

int memoryexpand(int capacity,int count){
    if(count>=capacity){
        capacity+=6;
        droneArray=(struct dronebank*)realloc(droneArray,capacity*sizeof(struct dronebank));
    }
    if(droneArray==NULL){
        return 0;
    }
}

float sort(int number,float min_weight){
    if(droneArray[number].weight<=min_weight){
        min_weight=droneArray[number].weight;
        memcpy(&droneArray[capacity-1].weight,&droneArray[number-1].weight,sizeof(struct dronebank));
        memcpy(&droneArray[number-1].weight,&droneArray[number].weight,sizeof(struct dronebank));
        memcpy(&droneArray[number].weight,&droneArray[capacity-1].weight,sizeof(struct dronebank));
    }
    return min_weight;
}

int registe(int command,int count){   //command==2为登录 command==1是注册
    if(command==1){
        int number=count;
        input(number);
        if(!input(number)){
            number=count-1;
            return number;
        }
        return number;
    }
}

int login(char *name,char * password,int count){
    for(int i=0;i<count;i++){
        if(droneArray[i].name==*name && droneArray[i].password==*password){
            display(i);
        }else{
            printf("error");
        }
    }
    return 0;
}

void display(int number){
    printf("%s\n",droneArray[number].name);
    printf("%s\n",droneArray[number].password);
    printf("%s\n",droneArray[number].phonenum);
    printf("%s\n",droneArray[number].dronetype);
    printf("%f\n",droneArray[number].weight);
}