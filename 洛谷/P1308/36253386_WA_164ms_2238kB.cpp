#include <bits/stdc++.h>
using namespace std;
string cge(string s) {
	for (int i = 0; i < s.length(); i++)
		if (s[i] > 'Z') s[i] -= 'z' - 'Z';
	return s;
}
int main() {
	string s;
	cin >> s;
	s = cge(s);
	char c[100];
	string a;
	int cnt = 0, pls;
	int i = 0;
	while (scanf("%s", c) != EOF) {
		a = cge(c);
		if (a == s) {
			if (!cnt) pls = i;
			cnt++;
		}
		i++;
	}
	if (cnt) cout << cnt << " " << pls << endl;
	else cout << "-1\n";
	return 0;
}