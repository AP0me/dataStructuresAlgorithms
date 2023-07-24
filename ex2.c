#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int nVal;
  struct Node *pNext;
} SNode;

int LL_add(SNode *pList,int n);
LL_del(SNode **ppList,int n);
int LL_Print(SNode *pList);
LL_Destructor(SNode *pList);

int LL_add(SNode *pList, int n){
  SNode *pTemp = pList; 
  pList=(SNode *) malloc(sizeof(SNode));
  pList->nVal=n;
  pList->pNext=pTemp;
  return 0;
}

int LL_del(SNode *pList){
  SNode *pTemp = pList; 
  if (pList==Null) return 1;
  printf("[%d]->",pList->nVal);
  while(pTemp->pNext){
    pTemp=pTemp->pNext;
    printf("[%d]->",pList->nVal);
  }
  printf("\b/\n");
  return 0;
}

int LL_Print(SNode *pList){
  SNode *pTemp = pList; 
  if (pList==Null) return 1;
  printf("[%d]->",pList->nVal);
  while(pTemp->pNext){
    pTemp=pTemp->pNext;
    printf("[%d]->",pList->nVal);
  }
  printf("\b/\n");
  return 0;
}

int main(){
  SNode *pList=NULL;
  int n;
  char cAction;

  do{
    printf("(a)dd, (d)elete, (D)estruct, (q)uit: ");scanf(" %c",&cAction);
    if (cAction=='a'){
      printf("Enter a number to add to the list: ");scanf(" %d",&n);
      LL_add(&pList, n);
    } else if (cAction=='d'){
      printf("Enter a number to remove from the list:");scanf(" %d",&n);
      LL_del(&pList, n);
    } else if (cAction=='D'){
      LL_Destructor(&pList);
    }
    LL_Print(pList);
    printf("\n");
  }while(cAction!='q');

  return 0;
}