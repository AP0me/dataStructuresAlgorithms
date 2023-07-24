#include <stdio.h>
#include <stdlib.h>

struct Node{
  int* data;
  struct Node* left;
  struct Node* rght;
};
struct Node* createBT(int maximumSize) {
  if (maximumSize <= 0) { return NULL; }
  struct Node* root = malloc(sizeof(struct Node));
  root->data = malloc(sizeof(int));
  *(root->data) = maximumSize-1;
  if (maximumSize == 1) {
    root->left = NULL;
    root->rght = NULL;
  } else {root->left = createBT(maximumSize-1); root->rght = createBT(maximumSize-1);}
  return root;
}

void LL_Print(struct Node* root, int level) {
  if (root == NULL) {return;}
  LL_Print(root->rght, level+1);
  for (int i = 0; i < level+1; i++) {
    printf("\t");
  }
  if (root->data == NULL) {
    printf("--\n");
  }else {printf("%d\n", *(root->data));}
  LL_Print(root->left, level+1);
}

int main(){
  int size; scanf("%d", &size);
  printf("%d\n", size);
  struct Node* newBT = createBT(size);
  LL_Print(newBT, size);
  return 0;
}
