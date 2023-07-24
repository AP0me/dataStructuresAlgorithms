#include <stdio.h>
#include <stdlib.h>

typedef struct Fifo {
  int itoQueue, ifromQueue, nSize; // i for "Index", n for "iNteger"
  int* pFifo;                    // p for "Pointer"
} SFifo;                         // S for "Structure"

// function signatures:
int constructFifo(SFifo *p, int n);
int toQueue(SFifo *p, int n);
int fromQueue(SFifo *p);
int printQueue(SFifo *p);
int destructFifo(SFifo *p);

// implemented functions:

int main(){
  int n, nErrNo=1; // nErrNo for Error Number
  SFifo myFifo;

  printf("Enter a queue size > 0: ");scanf("%d",&n);
  nErrNo=constructFifo(&myFifo,n);
  if (nErrNo){
    fprintf(stderr,"Error code %d while creating the queue\n",nErrNo);
    return 1;
  }
  
  printf("toQueue positive numbers (fromqueue with -1, end with -2)\n");
  while (n!=-2){
    scanf("%d",&n);
    if (n==-2) break; 
    if (n==-1) fromQueue(&myFifo);
    else toQueue(&myFifo,n);
  }

  destructFifo(&myFifo);

  return 0;
}



