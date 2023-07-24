#include <stdio.h>
#include <stdlib.h>

struct queue{
  int* data;
  struct queue* next;
};

struct queue* CLifo(struct queue* queAddr, int maximumSize){
  struct queue* temp = queAddr;
  for(int i=0; i<maximumSize; i++){
    temp->next = malloc(sizeof(struct queue));
    temp->data = NULL;
    temp=temp->next;
  }
  temp->next = NULL;
  return queAddr;
}
int CLifo_push(struct queue* queAddr, int data){
  struct queue* temp = queAddr;
  while(temp){
    if(temp->data==NULL){
      temp->data=data; break;
    }
    if(temp->next == NULL){
      printf("Stack is full\n"); break;
    }
    temp = temp->next;
  }
}

struct queue* CLifo_print(struct queue* queAddr){
  printf("begining\n");
  struct queue* temp = queAddr;
  for(int i=0; temp->next != NULL; i++){
    printf("%d - %d - %p\n", i, temp->data, temp->next);
    temp=temp->next;
  } printf("the end\n");
  return queAddr;
}

struct queue* CLifo_pop(struct queue* queAddr){
  struct queue* temp = queAddr;
  while(1){
    if(temp->next->next != NULL){
      printf("data=%d\n", temp->data);
      if(temp->next->data == NULL){
        printf("debug %d\n", temp->data);
        temp->data = NULL;
        return queAddr;
      }
      temp=temp->next;
    }
    else{
      if(temp->data != NULL){
        printf("debug2 %d, %p\n", temp->data, temp);
        temp->data = NULL;
        return queAddr;
      }else{ printf("stack is empty"); return queAddr; }
    }
  }
}

int main(){
  struct queue  myFifo;
  struct queue* myFifoAddr = &myFifo;

  int n, nErrNo=1; // nErrNo for Error Number
  printf("Enter a queue size > 0: ");scanf("%d",&n);
  CLifo(myFifoAddr, n);
  if (0){//if(nErrNo){//TODO error number is never set;
    fprintf(stderr,"Error code %d while creating the queue\n",nErrNo);
    return 1;
  }
  printf("toQueue positive numbers (fromqueue with -1, end with -2)\n");
  CLifo_print(myFifoAddr);
  while (n!=-2){
    scanf("%d",&n);
    if      (n==-2) { break; }
    else if (n==-1) { myFifoAddr=CLifo_pop(myFifoAddr); }
    else            { CLifo_push(myFifoAddr, n); }
    CLifo_print(myFifoAddr);
  }

  return 0;
}