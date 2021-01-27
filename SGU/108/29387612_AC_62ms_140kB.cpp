#include <bits/stdc++.h>
using namespace std;

int n, m, len, now, self[63], arr[10000], ans[2000];
struct atom {
  int id, num, ans;
  inline bool operator<(const atom &rhs) const { return num < rhs.num; }
} num[5000];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++) {
    scanf("%d", &num[i].num);
    num[i].id = i;
  }
  sort(num, num + m);
  for (int i = 0; i < 10000; i++) {
    arr[i] = arr[i / 10] + i % 10;
  }
  for (int i = 0; i < 63; i++) {
    self[i] = 1;
  }
  for (int i = 1; i <= n; i++) {
    if (self[i % 63]) {
      len++;
      while (num[now].num == len) {
        num[now++].ans = i;
      }
    }
    self[i % 63] = 1;
    int next = i + arr[i / 10000] + arr[i % 10000];
    self[next % 63] = 0;
  }
  printf("%d\n", len);
  for (int i = 0; i < m; i++) {
    ans[num[i].id] = num[i].ans;
  }
  for (int i = 0; i < m; i++) {
    printf("%d%c", ans[i], " \n"[i + 1 == m]);
  }
}