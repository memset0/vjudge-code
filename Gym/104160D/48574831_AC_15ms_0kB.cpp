#include <bits/stdc++.h>
using namespace std;
int main() {
#ifdef popteam
    freopen("D.in", "r", stdin);
#endif
    string s;
    cin >> s;
    map<char, int> mp;
    for (int i = 0; i < s.length(); i++)
        mp[s[i]]++;
    if (mp['T'] >= 3) {
        cout << "T1" << endl;
    } else {
        cout << "DRX" << endl;
    }
}