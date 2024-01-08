#include "stdio.h"
#include "stdlib.h"

#define N (int)(1e6 + 9)

typedef struct Heap *PtrToHeap;
struct Heap {
  int siz;
  int a[N];
};

void clear(PtrToHeap h) { h->siz = 0; }

void push(PtrToHeap h, int x) {
  h->siz++;
  h->a[h->siz] = x;
  int u = h->siz;
  while (u > 1 && h->a[u] < h->a[u >> 1]) {
    int tmp = h->a[u];
    h->a[u] = h->a[u >> 1];
    h->a[u >> 1] = tmp;
    u >>= 1;
  }
}

void pop(PtrToHeap h) {
  int tmp = h->a[1];
  h->a[1] = h->a[h->siz];
  h->a[h->siz] = tmp;
  h->siz--;
  int u = 1;
  while ((u << 1) <= h->siz) {
    if ((u << 1 | 1) <= h->siz) {
      // lchild && rchild
      if (h->a[u] <= h->a[u << 1] && h->a[u] <= h->a[u << 1 | 1]) break;
      if (h->a[u << 1] < h->a[u << 1 | 1]) {
        int tmp = h->a[u];
        h->a[u] = h->a[u << 1];
        h->a[u << 1] = tmp;
        u = u << 1;
      } else {
        int tmp = h->a[u];
        h->a[u] = h->a[u << 1 | 1];
        h->a[u << 1 | 1] = tmp;
        u = u << 1 | 1;
      }
    } else {
      if (h->a[u] > h->a[u << 1]) {
        int tmp = h->a[u];
        h->a[u] = h->a[u << 1];
        h->a[u << 1] = tmp;
        u = u << 1;
      } else {
        break;
      }
    }
  }
}

int top(PtrToHeap h) { return h->a[1]; }

int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  int n, op, x;
  PtrToHeap heap = (PtrToHeap)malloc(sizeof(struct Heap));
  clear(heap);
  scanf("%d", &n);
  while (n--) {
    scanf("%d", &op);
    if (op == 1) {
      scanf("%d", &x);
      push(heap, x);
    } else if (op == 2) {
      printf("%d\n", top(heap));
    } else {
      pop(heap);
    }
    // for (int i = 1; i <= heap->siz; i++) fprintf(stderr, "%d%c", heap->a[i], " \n"[i == heap->siz]);
  }
}