#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int key;
  int height;
  struct node *left;
  struct node *right;
} Node;

int height(Node *node) {
  if (node == NULL) {
  return 0;
  } else {
  return node->height;
  }
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

Node* createNode(int key) {
  Node *newNode = (Node*) malloc(sizeof(Node));
  newNode->key = key;
  newNode->height = 1;
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
}

Node* rightRotate(Node *y) {
  Node *x = y->left;
  Node *T2 = x->right;

  x->right = y;
  y->left = T2;

  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;

  return x;
}

Node* leftRotate(Node *x) {
  Node *y = x->right;
  Node *T2 = y->left;

  y->left = x;
  x->right = T2;

  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;

  return y;
}

int getBalance(Node *node) {
  if (node == NULL) {
  return 0;
  } else {
  return height(node->left) - height(node->right);
  }
}

Node* insert(Node *node, int key) {
  if (node == NULL) {
  return createNode(key);
  }

  if (key < node->key) {
  node->left = insert(node->left, key);
  } else if (key > node->key) {
  node->right = insert(node->right, key);
  } else {
  return node;
  }

  node->height = 1 + max(height(node->left), height(node->right));

  int balance = getBalance(node);

  if (balance > 1 && key < node->left->key) {
  return rightRotate(node);
  }

  if (balance < -1 && key > node->right->key) {
  return leftRotate(node);
  }

  if (balance > 1 && key > node->left->key) {
  node->left = leftRotate(node->left);
  return rightRotate(node);
  }

  if (balance < -1 && key < node->right->key) {
  node->right = rightRotate(node->right);
  return leftRotate(node);
  }

  return node;
}
void printAVL(Node *node, int space) {
  if (node == NULL) {
    return;
  }

  space += 5;

  printAVL(node->right, space);

  printf("\n");

  for (int i = 5; i < space; i++) {
    printf(">");
  }

  printf("%d\n", node->key);

  printAVL(node->left, space);
}

int main() {
  Node *root = NULL;

  root = insert(root, 10);
  root = insert(root, 0);
  root = insert(root, 6);
  root = insert(root, 11);
  root = insert(root, -1);
  root = insert(root, 1);
  root = insert(root, 2);

  printAVL(root, 0);


}


