#include "stdbool.h"
#include "stdio.h"

#define N 35
int n, inorder[N], postorder[N], ch[N][2];

int buildTree(int *inorder, int *postorder, int n) {
  if (n <= 0) return 0;
  int u = postorder[n - 1];
  int m = 0;
  for (; m < n; m++) {
    if (inorder[m] == u) break;
  }
  ch[u][0] = buildTree(inorder, postorder, m);
  ch[u][1] = buildTree(inorder + m + 1, postorder + m, n - m - 1);
  return u;
}

struct atom {
  int node, depth, timestamp;
} q[N];
int tot = 0;

void dfs(int u, int depth) {
  if (!u) return;
  ++tot;
  q[tot].node = u;
  q[tot].depth = depth;
  q[tot].timestamp = tot;
  for (int i = 0; i < 2; i++) { dfs(ch[u][i], depth + 1); }
}

int main() {
#ifdef memset0
  freopen("data11.in", "r", stdin);
#endif

  scanf("%d", &n);
  for (int i = 1; i <= n; i++) scanf("%d", inorder + i);
  for (int i = 1; i <= n; i++) scanf("%d", postorder + i);
  int rt = buildTree(inorder + 1, postorder + 1, n);
  dfs(rt, 1);

  for (int i = 1; i <= tot; i++)
    for (int j = 1; j < tot; j++)
      if (q[j].depth > q[j + 1].depth || q[j].depth == q[j + 1].depth && q[j].timestamp > q[j + 1].timestamp) {
        struct atom tmp = q[j];
        q[j] = q[j + 1];
        q[j + 1] = tmp;
      }

  for (int l = 1, r; l <= tot; l = r + 1) {
    r = l;
    while (r + 1 <= tot && q[r + 1].depth == q[r].depth) ++r;
    if (q[l].depth & 1) {
      for (int i = r; i >= l; i--) printf("%d%c", q[i].node, " \n"[i == l && r == tot]);
    } else {
      for (int i = l; i <= r; i++) printf("%d%c", q[i].node, " \n"[i == tot]);
    }
  }
}