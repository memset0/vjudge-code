#include<bits/stdc++.h>
#define cmp f01
#define cge f02
#define getlen f03
using namespace std;
const int maxn = 20;
long long x, y, ans = 0;
int a[maxn], b[maxn], c[maxn];
inline int cge(long long n, int a[]) {
	memset(a, 0, sizeof(a));
	while (n > 0) {
		a[++a[0]] = n % 10;
		n /= 10;
	}
}
inline int cmp(int a[], int b[]) {
	if (a[0] == b[0]) {
		for (int i = 1; i <= a[0]; i++)
			if (a[i] < b[i]) return -1;
			else if (a[i] > b[i]) return 1;
		return 0;
	}
	else if (a[0] < b[0]) return -1;
	else return 1;
}
inline int write(int a[]) {
	cout << a[0] << " ";
	for (int i = 1; i <= a[0]; i++)
		cout << a[i];
	cout << endl;
}
int main() {
	cin >> x >> y;
	if (x > y) swap(x, y);
	cge(x, a), cge(y, b);
	for (int len = a[0]; len <= b[0]; len++) {
		//枚举长度 
		for (int i = 1; i < 10; i++) {
			//枚举有趣的数中重复的数 
			for (int j = 0; j < 10; j++) {
				//枚举有趣的数中的单独的数 
				if (i == j) continue; //去除全部数字都重复的情况 
				for (int k = 2; k <= i; k++) {
					//枚举单独的数字的位置
					for (int kk = 1; kk <= len; kk++) {
						//生成数
						if (kk == k) c[kk] = j;
						else c[kk] = i;
					}
					c[0] = len;
//					write(c);
					if (cmp(a, c) == 1) continue; // a > c
					if (cmp(c, b) == 1) continue; // b < c
					ans++;
				}
			}
		}
	}
//	write(a), write(b);
	cout << ans << endl;
	return 0; 
}