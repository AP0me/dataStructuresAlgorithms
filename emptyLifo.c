#include <stdio.h>
#include <stdlib.h>

typedef struct Lifo {
  int iTop, nSize; // i for "Index", n for "iNteger"
  int* pLifo;      // p for "Pointer"
} SLifo;           // S for "Structure"

// function signatures:
int CLifo(SLifo *p, int nSize); // constructor, in an object-oriented language
// functions should return an error code: 0 if ok, error number otherwise
int CLifo_getSize(SLifo *p);
int CLifo_setSize(SLifo *p, int nSize); // if s>nSize, enlarge, if s<nSize,
// be careful not to lose data!
int CLifo_push(SLifo *p, int n); // check that the stack is large enough
int CLifo_pop(SLifo *p); // check that the stack is not empty
int CLifo_print(SLifo *p); // prints the contents of the stack
int d_CLifo(SLifo *p); // Destructor in an object-oriented language

// Implemented functions:
int CLifo_getSize(SLifo *p) {return p->nSize;}

int main(){
  int n,nErrNo=1; // nErrNo for Error Number
  SLifo myLifo;

  printf("Enter a stack size > 0: ");scanf("%d",&n);
  nErrNo=CLifo(&myLifo,n);
  if (nErrNo){
    fprintf(stderr,"Error code %d while creating the stack\n",nErrNo);
    return 1;
  }
  
  printf("Push positive integers (pop with -1, end with -2)\n");
  while (n!=-2){
    scanf("%d",&n);
    if (n==-1) CLifo_pop(&myLifo);
    else if (n > 0) CLifo_push(&myLifo,n);
    CLifo_print(&myLifo);
  }

  d_CLifo(&myLifo);

  return 0;
}




