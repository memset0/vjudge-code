#include <bits/stdc++.h>
using namespace std;
string s;
int k;
int main() {
	cin >> k >> s;
	for (int i = 0; i < s.length(); i++) {
		s[i] += k;
		if (s[i] > 'z') s[i] -= 26;
	}
	cout << s << endl;
}