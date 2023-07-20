#include <bits/stdc++.h>
using namespace std;
int T, n;
bool ch[26];
string s;
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> T;
  while (T--) {
    memset(ch, 0, sizeof(ch));
    cin >> n;
    for (int i = 1; i <= (n << 1) + 1; i++) {
      cin >> s;
      for (int j = 0; j < s.length(); j++) ch[s[j] - 'a'] ^= 1;
    }
    for (int i = 0; i < 26; i++)
      if (ch[i]) {
        cout << (char)(i + 'a') << endl;
      }
  }
}