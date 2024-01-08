#include "stdio.h"
#include "stdbool.h"
#define N (int)(1e5 + 9)
int n, len, ans[N];
bool vis[N];
int main() {
  scanf("%d", &n);
  for (int i = 2; i <= n; i++) {
    if (!vis[i]) {
      ++len;
      ans[len] = i;
    } 
    for (int j = i * 2; j <= n; j += i) {
      vis[j] = true;
    }
  }
  int sum = 0;
  int cnt = 0;
  for (int i = 1; i <= len; i++) {
    if (sum + ans[i] > n) {
      break;
    }
    cnt++;
    sum += ans[i];
    printf("%d\n", ans[i]);
  }
  printf("%d\n", cnt);
}