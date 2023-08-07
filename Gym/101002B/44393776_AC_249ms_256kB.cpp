#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#define N 5005
using namespace std;

int fa[N];
char s[N];
int m, n;
int sta[N], siz = 0, plk[N];
int idx = 0;
int L[N], R[N];
int trans(int x) {
  int cnt = 0;
  while (x) {
    cnt++;
    x /= 10;
  }
  return cnt;
}
bool solve(int k) {
  for (int i = 1; i <= n; i++) L[i] = R[i] = 0;
  R[n] = L[n] = k;
  R[fa[n]] = k;
  int tot = 0;
  tot = 2 * trans(k) + 2;
  // cout<<"solve:"<<k<<endl;
  if (tot > k) return false;
  for (int i = n - 1; i >= 1; i--) {
    if (!R[i]) {
      R[i] = L[i] = k - tot;
      tot = tot + 2 * trans(L[i]) + 2;
    } else {
      L[i] = k - tot;
      tot = tot + trans(L[i]) + trans(R[i]) + 2;
    }
    if (!R[fa[i]]) R[fa[i]] = R[i];
    if (tot > k) return false;
  }
  //  cout<<"solve:"<<k<<" "<<tot<<endl;
  if (tot == k) return true;
  else
    return false;
}
void dfs1(int l, int r, int ff) {
  if (l > r) return;
  if (r == l + 1) return;
  for (int pos = l + 1; pos < r; pos = plk[pos] + 1) {
    idx++;
    fa[idx] = ff;
    dfs1(pos, plk[pos], idx);
  }
}
int main() {
  scanf("%s", s + 1);
  m = strlen(s + 1);
  n = m / 2;
  for (int i = 1; i <= m; i++) {
    if (s[i] == '(') sta[++siz] = i;
    else
      plk[sta[siz--]] = i;
  } // cout<<"???"<<plk[1]<<endl;
  for (int pos = 1; pos < m; pos = plk[pos] + 1) {
    idx++;
    fa[idx] = 0;
    dfs1(pos, plk[pos], idx);
  } // puts("GGG");
  // for(int i=1;i<=n;i++)cout<<fa[i]<<" ";cout<<endl;
  int res = 0;
  for (int i = 1; i <= 12 * n; i++) {
    if (solve(i)) {
      res = i;
      break;
    }
  }
  // cout<<res<<endl;
  solve(res);
  for (int i = 1; i <= n; i++) printf("%d,%d:", L[i], R[i]);
  puts("");
}