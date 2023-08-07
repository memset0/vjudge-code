#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <vector>
typedef std::string str;
typedef long long ll;
typedef std::pair<ll, ll> pii;

const int MAXN = 2011;
std::map<str, int> mp;
pii cnt[MAXN], ans;
pii merge(pii a, pii b) { return pii(a.first * b.first, a.second * b.first + a.first * b.second + a.second * b.second); }
std::vector<str> seq, fir;
str d, e, f;
int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  int n, m;
  std::cin >> n;
  seq.resize(n), fir.resize(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> seq[i];
    if (!mp.count(seq[i])) mp[seq[i]] = i;
  }
  std::cin >> m;
  for (int i = 0; i < m; ++i) {
    std::cin >> d >> e >> f;
    if (!mp.count(d)) continue;
    int x = mp[d];
    fir[x] = e;
    if (f == "correct") ++cnt[x].first;
    else
      ++cnt[x].second;
  }
  ans = pii(1, 0);
  for (int i = 0; i < n; ++i) {
    int x = mp[seq[i]];
    // printf("cnt[%d]=(%lld,%lld)\n",x,cnt[x].first,cnt[x].second);
    ans = merge(ans, cnt[x]);
  }
  if (ans == pii(1, 0)) {
    for (int i = 0; i < n; ++i) std::cout << fir[mp[seq[i]]] << " ";
    std::cout << "\ncorrect\n";
    return 0;
  }
  if (ans == pii(0, 1)) {
    for (int i = 0; i < n; ++i) std::cout << fir[mp[seq[i]]] << " ";
    std::cout << "\nincorrect\n";
    return 0;
  }
  printf("%lld correct\n", ans.first);
  printf("%lld incorrect\n", ans.second);
  return 0;
}