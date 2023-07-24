#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node{
  int  iCode;
  char cChar;
  struct Node* next;
};

void printLL(struct Node* begin){
  struct Node* temp=begin; int i=0; int x=0;
  for(i=0; temp!=NULL; i++){
    if(temp->cChar != '\0'){
      printf("%d : %d%c\n", i, temp->iCode, temp->cChar, temp);
    }
    temp=temp->next;
  }
  printf("length: %d\n", i);
}

struct Node* createLL(struct Node* begin, char initTable[6], int size){
  struct Node* temp=begin; struct Node* mem;
  for(int i=0; i<size; i++){
    temp->iCode = -1;
    temp->cChar = initTable[i];
    printf("%c\n", temp->cChar);
    temp->next  = malloc(sizeof(struct Node*));
    mem = temp;
    temp=temp->next;
  }
  temp->next=NULL;
  return mem;
}

int SearchLL(struct Node* begin, char cChar, int iCode){
  struct Node* temp = begin; int index = 0;
  while(temp != NULL){
    if((temp->cChar == cChar)&&(temp->iCode == iCode)){
      return index;
    }
    temp = temp->next;
    index++;
  } return -1; // not found
}

struct Node* addToLL(struct Node* lastNode, char cChar, int iCode){
  lastNode->next = malloc(sizeof(struct Node));
  lastNode->next->iCode = iCode;
  lastNode->next->cChar = cChar;
  lastNode->next->next = NULL;
  lastNode=lastNode->next;
  return lastNode;
}

void LZW_Alg(struct Node* begin, struct Node* lastNode, char Sentence[35], int size){
  int lastICode=-1;
  for(int i=0; i<size; i++){
    int index = SearchLL(begin, Sentence[i], lastICode);
    printf("foundOrNot? %d%c: %d  \n", lastICode, Sentence[i], index);
    if(index == -1){
      lastNode = addToLL(lastNode, Sentence[i], lastICode);
      printf("add: %d%c \n", lastICode, Sentence[i]);
      lastICode=-1;
      i--;
    }
    else{
      lastICode=index;
    }
  }
}

void main() {
  struct Node* begin = malloc(sizeof(struct Node));
  char initTable[] ="edi_t";

  struct Node* lastNode = createLL(begin, initTable, 5);
  printf("created...\n");
  printLL(begin);
  char Sentence[] = "eddie_editted_it_did_eddie_edit_it";
  addToLL(lastNode, 'L', -1);
  LZW_Alg(begin, lastNode, Sentence, sizeof(Sentence)/sizeof(Sentence[0]));

  printLL(begin);
}
