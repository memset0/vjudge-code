#include "bits/stdc++.h"
using namespace std;

string s;
int n, k;
unordered_map<string, int> m;

int main()
{
  cin.sync_with_stdio(false); cin.tie(0);
  cin >> s;
  n = s.size();
  cin >> k;
  for (int i = 0; i + k <= n; ++i) {
    ++m[s.substr(i, k)];
  }
  pair<string, int> z;
  for (auto x : m) {
    if (x.second > z.second) z = x;
  }
  cout << z.second << endl;
  return 0;
}