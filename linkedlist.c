#include <stdio.h>
#include <stdlib.h>

struct Node{
  int* data;
  struct Node* next;
  struct Node* prev;
};

struct Node* createBT(int maximumSize){
  struct Node* newStart = malloc(sizeof(struct Node));
  struct Node* temp = newStart;
  struct Node* tmem = newStart;
  for(int i=0; i<maximumSize; i++){
    if(i+1==maximumSize){
      temp->next=NULL;
    }
    else{
      temp->next=malloc(sizeof(struct Node));
    }
    if(i!=0){ temp->prev=tmem; }
    *(temp->data)=5;
    tmem=temp;
    temp=temp->next;
  }
  return newStart;
}

void LL_Print(struct Node* root, int maximumSize) {
  struct Node* temp = root;
  for(int i=0; i<maximumSize; i++){
    if(i+1==maximumSize){
      return;
    }
    printf("%d:>%d\n", i, *(temp->data));
    temp=temp->next;
  }
}

int main(){
  int size; scanf("%d", &size);
  printf("%d\n", size);
  struct Node* newBT = createBT(size);
  LL_Print(newBT, size);
  return 0;
}
