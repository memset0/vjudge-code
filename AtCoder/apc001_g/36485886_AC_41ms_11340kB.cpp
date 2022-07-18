#include <bits/stdc++.h>
#define SZ(x) ((int)x.size())
using namespace std;
const int N = 2e5 + 9;
int n, c, len, ans[N];
char s[N];
vector<int> v[N];
void solve(const vector<int> &v) {
  for (int i = 0; i < SZ(v); i += 4) {
		ans[v[i]] = ans[v[i + 2]] = ++c;
		ans[v[i + 1]] = ans[v[i + 3]] = ++c;
	}
}
void print() {
  puts("Yes");
  vector<int> rest;
  for (int i = 1; i <= len; i++)
    if (!ans[i]) rest.push_back(i);
  for (int i = 0; i < SZ(rest); i += 2) {
		ans[rest[i]] = ans[rest[i + 1]] = ++c;
	}
  for (int i = 1; i <= len; i++) printf("%d%c", ans[i], " \n"[i == len]);
}
int main() {
  scanf("%d%s", &n, s + 1), len = n + n, s[len] = '1';
  auto nxt = [&](int x) { return x == len ? 1 : x + 1; };
  if (count(s + 1, s + len + 1, '1') == len) {
    if (n % 2) return puts("No"), 0;
    vector<int> v(len);
    iota(v.begin(), v.end(), 1);
    solve(v);
    print();
    return 0;
  }
  int m = 0;
  for (int i = 1; i <= len; i++)
    if (s[i == 1 ? len : i - 1] == '0' && s[i] == '1') {
      int j = i;
      while (s[nxt(j)] == '1') j = nxt(j);
      ++m;
      for (int k = i; k != j; k = nxt(k)) v[m].push_back(k);
      v[m].push_back(j), v[m].push_back(nxt(j));
      if (j < i) break;
      i = j;
    }
  int s = 0;
  for (int i = 1; i <= m; i++) s += SZ(v[i]) - 2;
  if (s % 2) return puts("No"), 0;
  if (s % 4 == 2) {
    int a = -1, b = -1;
    for (int i = 1; i <= m; i++)
      if (SZ(v[i]) > 2) (a == -1 ? a : b) = i;
    if (b == -1) return puts("No"), 0;
    ans[v[a][1]] = ans[v[b][1]] = ++c;
    vector<int> A = {v[a][0]}, B = {v[b][0]};
    for (int i = 2; i < SZ(v[b]); i++) A.push_back(v[b][i]);
    for (int i = 2; i < SZ(v[a]); i++) B.push_back(v[a][i]);
    v[a] = A, v[b] = B;
  }
  for (int i = 2; i <= m; i++) {
    ans[v[1].back()] = ans[v[i][0]] = ++c, v[1].pop_back(),
    v[i].erase(v[i].begin());
    v[1].insert(v[1].end(), v[i].begin(), v[i].end());
  }
  ans[v[1][0]] = ans[v[1].back()] = ++c, v[1].erase(v[1].begin()),
  v[1].pop_back();
  solve(v[1]);
	print();
} // old codes