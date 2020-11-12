#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)

using namespace std;

typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef long long ll;

template <typename _T> inline void read(_T &f) {
  f = 0;
  _T fu = 1;
  char c = getchar();
  while (c < '0' || c > '9') {
    if (c == '-') {
      fu = -1;
    }
    c = getchar();
  }
  while (c >= '0' && c <= '9') {
    f = (f << 3) + (f << 1) + (c & 15);
    c = getchar();
  }
  f *= fu;
}

template <typename T> void print(T x) {
  if (x < 0)
    putchar('-'), x = -x;
  if (x < 10)
    putchar(x + 48);
  else
    print(x / 10), putchar(x % 10 + 48);
}

template <typename T> void print(T x, char t) {
  print(x);
  putchar(t);
}

queue<pair<ll, ll>> q;
map<pair<ll, ll>, int> wxw;
map<pair<ll, ll>, int>::iterator it;
int T;
ll x, y;

int main() {
  read(T);
  while (T--) {
    while (!q.empty())
      q.pop();
    read(x);
    read(y);
    wxw.clear();
    int cnt = 1;
    wxw[make_pair(x, y)] = 1;
    q.push(make_pair(x, y));
    while (!q.empty()) {
      pair<ll, ll> u = q.front();
      q.pop();
      for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
          ll newx = u.first + i, newy = u.second + j;
          if (__gcd(newx, newy) > 1 && !wxw.count(make_pair(newx, newy))) {
            wxw[make_pair(newx, newy)] = 1;
            q.push(make_pair(newx, newy));
            ++cnt;
          }
        }
      }
      if (cnt >= 10000) {
        printf("0/1\n");
        break;
      }
    }
    if (cnt >= 10000)
      continue;
    int sum = 0, deg = 0;
    for (it = wxw.begin(); it != wxw.end(); ++it) {
      for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
          ll newx = (it->first).first + i, newy = (it->first).second + j;
          if (__gcd(newx, newy) > 1) {
            ++sum;
          }
        }
      }
    }
    for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {
        ll newx = x + i, newy = y + j;
        if (__gcd(newx, newy) > 1) {
          ++deg;
        }
      }
    }
    int d = __gcd(deg, sum);
    printf("%d/%d\n", deg / d, sum / d);
  }
  return 0;
}