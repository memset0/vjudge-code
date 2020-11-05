#include <bits/stdc++.h>
using namespace std;
int main() {
    string s1, s2;
    int h1, m1, h2, m2, h3, m3;
    cin >> s1 >> s2;
    h1 = (s1[0] - '0') * 10 + s1[1] - '0';
    m1 = (s1[3] - '0') * 10 + s1[4] - '0';
    h2 = (s2[0] - '0') * 10 + s2[1] - '0';
    m2 = (s2[3] - '0') * 10 + s2[4] - '0';
    m3 = (m1 + m2) / 2;
    h3 = (h1 + h2) / 2;
    if ((h1 + h2) % 2)
        m3 += 30; 
    if (m3 >= 60)
        m3 %= 60, h3 = (h3 + 1) % 24;
    if (h3 < 10)
        cout << 0;
    cout << h3;
    cout << ":";
    if (m3 < 10)
        cout << 0;
    cout << m3;
    return 0;
}