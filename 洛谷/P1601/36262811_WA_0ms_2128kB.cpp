#include <bits/stdc++.h>
using namespace std;
const int maxn = 510;
int a[maxn], b[maxn], c[maxn];
string sa, sb;
int cge(char c) {
	if ('1' <= c && c <= '9') return c - '0';
	else return 0;
}
int main() {
	cin >> sa >> sb;
	int len = max(sa.length(), sb.length());
	for (int i = 1; i <= len; i++) {
		a[i] = cge(sa[len - i]);
		b[i] = cge(sb[len - i]);
	}
	for (int i = 1; i <= len; i++) {
		c[i] += a[i] + b[i];
		c[i + 1] += c[i] / 10;
		c[i] %= 10;
	}
	if (c[len + 1] > 0) len++;
	for (int i = len; i > 0; i--)
		cout << c[i];
	cout << endl;
	return 0;
}