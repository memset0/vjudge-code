#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 9;
int n, cnt, ans, match[N];
char buf[N];
stack<int> stk;

struct node {
  int ch[3], tag;
  char val;
} t[N];

inline int merge(int ls, int rs) {
  for (int i = 0; i < 3; i++) {
    if (!t[ls].ch[i]) {
      t[ls].ch[i] = rs;
      break;
    }
  }
  int sum = t[ls].tag;
  if (t[ls].val == 'B') {
    if (t[ls].ch[2]) {
      int tmp = merge(t[ls].ch[0], merge(t[ls].ch[1], t[ls].ch[2]));
      t[tmp].tag += sum + 1;
      return tmp;
    }
  } else if (t[ls].val == 'K') {
    if (t[ls].ch[1]) {
      t[t[ls].ch[0]].tag += sum + 1;
      return t[ls].ch[0];
    }
  } else if (t[ls].val == 'I') {
    if (t[ls].ch[0]) {
      t[t[ls].ch[0]].tag += sum + 1;
      return t[ls].ch[0];
    }
  } else {
    if (t[ls].ch[2]) {
      int tmp = merge(merge(t[ls].ch[0], t[ls].ch[2]), t[ls].ch[1]);
      t[tmp].tag += sum + 1;
      return tmp;
    }
  }
  return ls;
}

inline int solve(int l, int r) {
  if (match[r] == l)
    return solve(l + 1, r - 1);
  if (l == r) {
    t[++cnt].val = buf[l];
    return cnt;
  }
  if (match[r]) {
    return merge(solve(l, match[r] - 1), solve(match[r] + 1, r - 1));
  } else {
    return merge(solve(l, r - 1), solve(r, r));
  }
}

inline void dfs(int x) {
  if (!x)
    return;
  ans += t[x].tag;
  for (int i = 0; i < 3; i++) {
    dfs(t[x].ch[i]);
  }
}

int main() {

  scanf("%s", buf + 1);
  n = strlen(buf + 1);
  for (int i = 1; i <= n; i++) {
    if (buf[i] == '(') {
      stk.push(i);
    }
    if (buf[i] == ')') {
      match[i] = stk.top(), stk.pop();
    }
  }

  int id = solve(1, n);
  dfs(id);
  printf("%d\n", ans);
}