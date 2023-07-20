#include "bits/stdc++.h"
using namespace std;

int T;
int n;
int a[114514], b[114514];
int stk[233], h;
int astk[233];
int o[114514];

bool calc() {
  for (int i = n; i >= 1; i--) {
    if (i == 1) {
      o[i] = 0;
      continue;
    }
    int v = a[i];
    h = 0;
    for (int j = i; j; j /= 2) {
      stk[++h] = j;
    }
    reverse(stk + 1, stk + h + 1);
    for (int j = 1; j <= h; j++) {
      astk[j] = b[stk[j]];
    }
    int k;
    for (k = h; k >= 1; k--) {
      if (astk[k] == v) break;
    }
    if (k == 0) return true;
    int vp = astk[k-1];
    if (k == h) {
      if (v < vp) {
        o[i] = 1;
      } else {
        o[i] = 0;
      }
      continue;
    }
    for (int l = k + 1; l <= h; l++) {
      if ((v < astk[l]) != (v < astk[h])) {
        return true;
      }
    }
    if (!(k == 1 || vp == v || (v > astk[h]) != (v > vp))) {
      return true;
    }
    if (v > astk[h]) {
      o[i] = 1;
    } else {
      o[i] = 0;
    }
    for (int l = k; l < h; l++) {
      astk[l] = astk[l+1];
    }
    astk[h] = v;
    for (int j = 1; j <= h; j++) {
      b[stk[j]] = astk[j];
    }
  }
  return false;
}

int main() {
  cin.sync_with_stdio(0);
  cin.tie(0);
  cin >> T;
  while(T--) {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    bool impossible = calc();
    if (impossible) {
      cout << "Impossible\n";
    } else {
      for (int i = 1; i <= n; i++) cout << o[i];
      cout << "\n";
    }
  }
}