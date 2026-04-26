#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>

struct dronebank{
    char name[25];
    char password[20];
    char phonenum[12];
    char dronetype[20];
    char registertime[20];
    float weight;   
};
struct flyapply{
    char dronetype[20];
    char applytime[20];
    char applyaddress[50];
    char applyreason[100];
    char logtime[20];
    char certificate[20];
     uint8_t passstatus;
};

struct dronebank bufferzone;
struct dronebank *droneArray;
struct flyapply *applyArray;
int capacity=10;
int count=0;
float min_weight=0;
 SYSTEMTIME st;

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
	FILE*fp=fopen("info.txt","r");
	if(fp==NULL){
		count=0;
		droneArray=NULL;
		return;
	}
	fscanf(fp,"%d",&count);
	droneArray=(struct dronebank*)malloc(count*sizeof(struct dronebank));
    applyArray=(struct flyapply*)malloc(count*sizeof(struct flyapply));
	if(droneArray==NULL){
		printf("Memory allocation failed!\n");
		fclose(fp);
		exit(1);
	}
	for(int i=0;i<count;i++){
		fscanf(fp,"%s %s %s %s %f %20s",
			droneArray[i].name,
			droneArray[i].password,
			droneArray[i].phonenum,
			droneArray[i].dronetype,
			&droneArray[i].weight,droneArray[i].registertime);
        fscanf(fp,"%s %s %s %s %s %s %1s",
            applyArray[i].dronetype,
            applyArray[i].applytime,
            applyArray[i].applyaddress,
            applyArray[i].applyreason,
            applyArray[i].logtime,
            applyArray[i].certificate,
            &applyArray[i].passstatus);
	}
    capacity=count<=capacity?capacity+6:count;
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
		fprintf(fp,"%s %s %s %s %f %20s\n",
			droneArray[i].name,
			droneArray[i].password,
			droneArray[i].phonenum,
			droneArray[i].dronetype,
			droneArray[i].weight,droneArray[i].registertime);
             fprintf(fp,"%s %s %s %s %s %s %s\n",
            applyArray[i].dronetype,
            applyArray[i].applytime,
            applyArray[i].applyaddress,
            applyArray[i].applyreason,
            applyArray[i].logtime,
            applyArray[i].certificate,
            &applyArray[i].passstatus);
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

int memoryflyapplyexpand(){
    applyArray=(struct flyapply *)realloc(applyArray,capacity*sizeof(struct flyapply));
    if(count>=capacity){
        capacity+=6;
        applyArray=(struct flyapply*)realloc(applyArray,capacity*sizeof(struct flyapply));
    }
    if(applyArray==NULL){
        return 0;
    }
    return 1;

}

float sort(int number){   
    for(int i=0;i<count-1;i++){
        if(droneArray[number] .weight<=droneArray[i+1].weight  && droneArray[number].weight>=droneArray[i].weight){
           // min_weight=droneArray[number].weight;
            bufferzone=droneArray[number];
            int t=i;
            while(t+2<count){ 
                droneArray[i+2]=droneArray[i+1];
                t++;
            }
            droneArray[i+1]=bufferzone;
            break;
            /*memcpy(&bufferzone.weight,&droneArray[number-1].weight,sizeof(struct dronebank));
            memcpy(&droneArray[number-1].weight,&droneArray[number].weight,sizeof(struct dronebank));
            memcpy(&droneArray[number].weight,&bufferzone.weight,sizeof(struct dronebank));*/
        }
    }
    return droneArray[number].weight;
}

void insert_element(int number) {
    bufferzone = droneArray[number];  // 暂存待插入元素
    int pos = 0;

    // 1. 找到插入位置
    for (pos = 0; pos < count; pos++) {
        if (bufferzone.weight <= droneArray[pos].weight)
            break;
    }
    // 如果 pos == count，说明应插入到末尾

    // 2. 移动元素（注意删除原位置时的下标调整）
    if (pos < number) {
        // 插入点在原位置之前 → 将 [pos, number-1] 后移一位
        for (int i = number; i > pos; i--) {
            droneArray[i] = droneArray[i-1];
        }
    } /*else if (pos > number) {
        // 插入点在原位置之后 → 将 [number+1, pos] 前移一位
        for (int i = number; i < pos-1; i++) {
            droneArray[i] = droneArray[i+1];
        }
        pos--;  // 因为移走了一个元素，插入位置左移一格
    } else {
        // pos == number，无需移动，直接返回
        return;
    }*/

    // 3. 放入正确位置
    droneArray[pos] = bufferzone;
}

void registe(){   //command==2涓虹櫥锟?? command==1鏄敞锟??
   count++;
   memoryexpand();
   memoryflyapplyexpand();
   input(count-1);
   //min_weight=sort(count-1); 
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
    printf("%20s\n",applyArray[number].dronetype);  
    printf("%20s\n",applyArray[number].applytime);
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
     sprintf(droneArray[number].registertime,"%04d-%02d-%02d %02d:%02d:%02d",
        st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
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
            applydisplay(i);
            printf("apply for flying press 1\n");
             int c=_getch()-'0';
            switch (c){
                case 1:
                apply(i);
                system("cls");
                printf("please wait for approval\n");
                system("pause");
                break;
                default :break;
            }
           
            //system("pause");
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