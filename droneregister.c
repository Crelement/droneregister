#include"droneconfig.h"
uint8_t u;
int main(){
   // FILE *fp;
    load();
    // memoryexpand();
    droneArray=(struct dronebank *)realloc(droneArray,count*sizeof(struct dronebank));
    while(1){
     menu();
     system("cls");
    }
       
    return 0;
}