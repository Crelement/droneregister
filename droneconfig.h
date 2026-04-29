#include<stdio.h>
#include<stdbool.h>
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
}*droneArray;
struct flyapply{
    char dronetype[20];
    char applytime[20];
    char applyaddress[50];
    char applyreason[100];
    char logtime[20];
    char certificate[20];
    bool passstatus;
}*applyArray;
int capacity=0;
int count=0;
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

void load() {
    FILE *fp = fopen("info.txt", "r");
    if (!fp) {
        count = 0;
        droneArray = NULL;
        applyArray = NULL;
        capacity = 0;
        return;
    }
    if (fscanf(fp, "%d", &count) != 1) {
        printf("File format error!\n");
        fclose(fp);
        exit(1);
    }
    droneArray = (struct dronebank*)malloc(count * sizeof(struct dronebank));
    applyArray = (struct flyapply*)malloc(count * sizeof(struct flyapply));
    if (!droneArray || !applyArray) {
        printf("Memory allocation failed!\n");
        fclose(fp);
        exit(1);
    }
    for (int i = 0; i < count; i++) {
        if (fscanf(fp, "%24s %19s %11s %19s %f %19s",
            droneArray[i].name, droneArray[i].password, droneArray[i].phonenum,
            droneArray[i].dronetype, &droneArray[i].weight, droneArray[i].registertime) != 6) {
            printf("File format error (dronebank)!\n");
            fclose(fp);
            free(droneArray); free(applyArray);
            droneArray = applyArray = NULL;
            count = 0; capacity = 0;
            return;
        }
        int pass;
        if (fscanf(fp, "%19s %19s %49s %99s %19s %19s %d",
            applyArray[i].dronetype, applyArray[i].applytime, applyArray[i].applyaddress,
            applyArray[i].applyreason, applyArray[i].logtime, applyArray[i].certificate,
            &pass) != 7) {
            printf("File format error (flyapply)!\n");
            fclose(fp);
            free(droneArray); free(applyArray);
            droneArray = applyArray = NULL;
            count = 0; capacity = 0;
            return;
        }
        applyArray[i].passstatus = (pass != 0);
    }
    capacity = count;   // 与实际分配数一致
    fclose(fp);
    printf("file load success\n");
    system("pause");
    system("cls");
}

void save() {
    FILE *fp = fopen("info.txt", "w");
    if (!fp) {
        printf("file open failed\n");
        return;
    }
    fprintf(fp, "%d\n", count);
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s %s %s %s %f %s\n",
            droneArray[i].name, droneArray[i].password, droneArray[i].phonenum,
            droneArray[i].dronetype, droneArray[i].weight, droneArray[i].registertime);
        fprintf(fp, "%s %s %s %s %s %s %d\n",
            applyArray[i].dronetype, applyArray[i].applytime, applyArray[i].applyaddress,
            applyArray[i].applyreason, applyArray[i].logtime, applyArray[i].certificate,
            (int)applyArray[i].passstatus);
    }
    fclose(fp);
}

bool memoryexpand() {
    if (droneArray == NULL || count >= capacity) {
        size_t new_cap = (capacity == 0) ? 10 : capacity * 2;
        struct dronebank *temp = realloc(droneArray, new_cap * sizeof(struct dronebank));
        if (!temp) return false;
        droneArray = temp;
        capacity = new_cap;
    }
    return true;
}

bool memoryflyapplyexpand() {
    if (applyArray == NULL || count >= capacity) {
        size_t new_cap = (capacity == 0) ? 10 : capacity * 2;
        struct flyapply *temp = realloc(applyArray, new_cap * sizeof(struct flyapply));
        if (!temp) return false;
        applyArray = temp;
        capacity = new_cap;
    }
    memset(applyArray + count, 0, (capacity - count) * sizeof(struct flyapply));
    return true;
}

void insert_element(int number) {
    bufferzone = droneArray[number];
    int pos = 0;
    while (pos < count && bufferzone.weight > droneArray[pos].weight)
        pos++;
    if (pos == count) pos = count - 1;
    if (pos < number) {
        for (int i = number; i > pos; i--)
            droneArray[i] = droneArray[i-1];
    } else if (pos > number) {
        for (int i = number; i < pos; i++)
            droneArray[i] = droneArray[i+1];
        pos--;
    }
    droneArray[pos] = bufferzone;
}

void registe(){
    count++;
    if (!memoryexpand() || !memoryflyapplyexpand()) {
         printf("Memory allocation failed!\n");
         exit(1);
    }
    memset(&applyArray[count-1], 0, sizeof(struct flyapply));
    applyArray[count-1].passstatus = false;
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
                return 1;
            }
            else{
                printf("Wrong password\n");
                system("pause");
                return 0;
            }
        }
    }
    printf("User not found\n");
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