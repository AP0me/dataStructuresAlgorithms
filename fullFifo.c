#include <stdio.h>
#include <stdlib.h>

struct queue{
  int* data;
  struct queue* next;
};

struct queue* constructFifo(struct queue* queAddr, int maximumSize){
  struct queue* temp = queAddr;
  for(int i=0; i<maximumSize; i++){
    struct queue* debugMem = malloc(sizeof(struct queue));
    printf("lll %p vs %p be %p\n", temp->next, queAddr->next, debugMem);
    temp->next = debugMem;
    temp->data = NULL;
    temp=temp->next;
  }
  temp->next = NULL;
  return queAddr;
}
int toQueue(struct queue* queAddr, int data){
  struct queue* temp = queAddr;
  while(1){
    if(temp->next!=NULL){
      if(temp->data==NULL){
        (*temp).data=data;
        break;
      }
      temp=temp->next;
    }
    else{
      if(temp->data==NULL){
        (*temp).data=data;
        break;
      }
      else{
        printf("Stack is full\n");
        break;
      }
    }
  }
}
struct queue* printQueue(struct queue* queAddr){
  printf("begining\n");
  struct queue* temp = queAddr;
  for(int i=0; temp->next != NULL; i++){
    printf("%d - %d - %p\n", i, temp->data, temp->next);
    temp=temp->next;
  }
  printf("the end\n");
  return queAddr;
}
struct queue* fromQueue(struct queue* queAddr){
  struct queue* temp = queAddr;
  if(temp->next!=NULL){
    if(temp->data!=NULL){
      temp->data=NULL;
      struct queue* lastEnd = temp->next;
      temp->next=NULL;

      struct queue* newFifoAddr = malloc(sizeof(struct queue));
      temp = lastEnd;
      while(1){
        if(temp->next==NULL){
          temp->data = NULL;
          temp->next = newFifoAddr;
          newFifoAddr->next=NULL;

          printQueue(temp);
          return lastEnd;
        }
        temp=temp->next;
      }
    }
  }
}


// function signatures:
//int constructFifo(SFifo *p, int n);
//int toQueue(SFifo *p, int n);
//int fromQueue(SFifo *p);
//int printQueue(SFifo *p);
//int destructFifo(SFifo *p);
// implemented functions:

int main(){
  struct queue  myFifo;
  struct queue* myFifoAddr = &myFifo;

  int n, nErrNo=1; // nErrNo for Error Number
  printf("Enter a queue size > 0: ");scanf("%d",&n);
  constructFifo(myFifoAddr, n);
  if (0){//if(nErrNo){//TODO error number is never set;
    fprintf(stderr,"Error code %d while creating the queue\n",nErrNo);
    return 1;
  }
  printf("toQueue positive numbers (fromqueue with -1, end with -2)\n");
  printQueue(myFifoAddr);
  while (n!=-2){
    scanf("%d",&n);
    if      (n==-2) { break; }
    else if (n==-1) { myFifoAddr=fromQueue(myFifoAddr); }
    else            { toQueue(myFifoAddr, n); }
    printQueue(myFifoAddr);
  }
  //destructFifo(myFifoAddr);

  return 0;
}