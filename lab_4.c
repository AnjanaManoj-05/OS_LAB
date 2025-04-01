#include <stdio.h>
int mutex=0,full=0,empty=0,x=0;
void wait(int *s){
   --(*s);
}
void signal(int *s){
    ++(*s);
}
void producer(){
wait(&empty);
wait(&mutex);
x++;
printf("Producer has produced: Item %d\n",x);
signal(&mutex);
signal(&full);
}
void consumer(){
wait(&full);
if(full<0){
    printf("Buffer is empty!\n");
}
else{
printf("Consumer has consumed: Item %d\n",x);
}
x--;
wait(&mutex);
signal(&mutex);
signal(&empty);
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
