#include <stdio.h>
#include <stdlib.h>

#define MAXN 10

typedef struct TreeNode *Tree;
struct TreeNode {
  int Element;
  Tree Left;
  Tree Right;
};

Tree BuildTree(int inorder[], int postorder[], int N);

void Inorder_output(Tree T) {
  if (!T) return;
  Inorder_output(T->Left);
  printf("%d ", T->Element);
  Inorder_output(T->Right);
}

void Postorder_output(Tree T) {
  if (!T) return;
  Postorder_output(T->Left);
  Postorder_output(T->Right);
  printf("%d ", T->Element);
}

int main() {
  Tree T;
  int inorder[MAXN], postorder[MAXN], N, i;

  scanf("%d", &N);
  for (i = 0; i < N; i++) scanf("%d", &inorder[i]);
  for (i = 0; i < N; i++) scanf("%d", &postorder[i]);
  T = BuildTree(inorder, postorder, N);
  printf("Check:\n");
  Inorder_output(T);
  printf("\n");
  Postorder_output(T);
  printf("\n");

  return 0;
}

/* Your function will be put here */
Tree BuildTree(int inorder[], int postorder[], int N) {
  if (N <= 0) return 0;
  int M;
  for (; M < N; M++)
    if (inorder[M] == postorder[N - 1]) {
      break;
    }
  Tree T = (Tree)malloc(sizeof(struct TreeNode));
  T->Element = postorder[N - 1];
  T->Left = BuildTree(inorder, postorder, M);
  T->Right = BuildTree(inorder + M + 1, postorder + M, N - M - 1);
  return T;
}