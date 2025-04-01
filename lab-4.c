#include <stdio.h>
int mutex=0,full=0,empty=0,x=0;
void wait(){
    --mutex;
}
void signal(){
    ++mutex;
}
void producer(){
wait();
++full;
--empty;
x++;
printf("Producer has produced: Item %d\n",x);
signal();
}
void consumer(){
wait();
--full;
++empty;
if(full<0){
    printf("Buffer is empty!\n");
}
else{
printf("Consumer has consumed: Item %d\n",x);
}
x--;
signal();
}

void main(){
    int ch;
    char choice;
do{
 printf("Enter\n1.Producer\n2.Consumer\n3.Exit\nEnter your choice:\n");
 scanf("%d",&ch);
 switch(ch){
 case 1:
     producer();
     break;
 case 2:
    consumer();
    break;
 case 3:
    exit(0);
    }

    }while(1);




}
