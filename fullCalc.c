#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
int LL_add(struct queue* queAddr, int data){
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

struct queue* LL_Print(struct queue* queAddr){
  printf("begining\n");
  struct queue* temp = queAddr;
  for(int i=0; temp->next != NULL; i++){
    printf("%d - %d - %p\n", i, temp->data, temp->next);
    temp=temp->next;
  } printf("the end\n");
  return queAddr;
}

int LL_del(struct queue* queAddr){
  struct queue* temp = queAddr;
  while(1){
    if(temp->next->next != NULL){
      printf("data=%d\n", temp->data);
      if(temp->next->data == NULL){
        printf("debug %d\n", temp->data);
        int poped = (*temp).data;
        temp->data = NULL;
        printf("hi1\n");
        return poped;
      }
      temp=temp->next;
    }
    else{
      if(temp->data != NULL){
        printf("debug2 %d, %p\n", temp->data, temp);
        int poped = (*temp).data;
        temp->data = NULL;
        return poped;
      }else{ printf("stack is empty"); return 0; }
    }
  }
}
int isStringDigit(char chars[10], int sizeofN){
  int allAreDigits=1;
  for (int i=0; i<sizeofN; i++){
    if(!isdigit(chars[i])){
      printf("%c\n", chars[i]);
      allAreDigits=0;
    }
  }
  return allAreDigits;
}
int main(){
  struct queue  myFifo;
  struct queue* myFifoAddr = &myFifo;
  int numAdded;
  char n[10]; int nErrNo=1; //nErrNo for Error Number
  printf("Enter a queue size > 0: "); scanf("%s",&n);
  int lenStack=atoi(n);
  CLifo(myFifoAddr, lenStack);
  if (0){//if(nErrNo){//TODO error number is never set;
    fprintf(stderr,"Error code %d while creating the queue\n",nErrNo);
    return 1;
  }
  printf("toQueue positive numbers (fromqueue with -1, end with -2)\n");
  LL_Print(myFifoAddr);
  while (numAdded!=-2){
    scanf("%s", &n);
    if (isStringDigit(n, 1) || n[0]=='D' || n[0]=='T'){
      numAdded=atoi(n);
      if      (n[0]=='T') { break; }
      else if (n[0]=='D') { LL_del(myFifoAddr); }
      else                { LL_add(myFifoAddr, numAdded); }
      LL_Print(myFifoAddr);
    }
    else{
      int num1=LL_del(myFifoAddr);
      int num2=LL_del(myFifoAddr);
      switch (n[0]) {
        case '+': LL_add(myFifoAddr, (num1 + num2)); break;
        case '-': LL_add(myFifoAddr, (num1 - num2)); break;
        case '*': LL_add(myFifoAddr, (num1 * num2)); break;
        case '/': LL_add(myFifoAddr, (num1 / num2)); break;
        case '%': LL_add(myFifoAddr, (num1 % num2)); break;
        default: printf("Invalid operator: %c", n[0]); exit(1);
      }
      LL_Print(myFifoAddr);
    }
  }

  return 0;
}