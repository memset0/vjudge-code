#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int _abs(int x) { return x > 0 ? x : -x; }

int n, m, q, v;
struct Pair {
	bool A, B;
} s[2000], t[2000];
char c1, c2;
int cnt[8], ans[4005];
int s0[2000], s1[2000];
int t0[2000], t1[2000];
void read(void) {
	while ((c1 = getchar()) == '\n' || c1 == ' ')
		;
	c2 = getchar();
	s[n].A = c1 - '0';
	s[n++].B = c2 - '0';
	while ((c1 = getchar()) != '\n' && c1 != ' ') {
		s[n].A = c1 - '0';
		s[n++].B = getchar() - '0';
	}
	while ((c1 = getchar()) == '\n' || c1 == ' ')
		;
	c2 = getchar();
	t[m].A = c1 - '0';
	t[m++].B = c2 - '0';
	while ((c1 = getchar()) != '\n' && c1 != ' ') {
		t[m].A = c1 - '0';
		t[m++].B = getchar() - '0';
	}
	return;
}

inline void reverseS(int i) {
	ans[++q] = (i + 1) << 1;
	for (int j = 0; (j << 1) <= i; j++) {
		swap(s[j], s[i - j]);
		swap(s[j].A, s[j].B);
		if ((j << 1) != i) swap(s[i - j].A, s[i - j].B);
	}
	return;
}
inline void reverseT(int i) {
	for (int j = 0; (j << 1) <= i; j++) {
		swap(t[j], t[i - j]);
		swap(t[j].A, t[j].B);
		if ((j << 1) != i) swap(t[i - j].A, t[i - j].B);
	}
	return;
}
inline void debug(void) {
	for (int i = 0; i < n; i++) printf("%d%d ", s[i].A, s[i].B);
	putchar('\n');
	for (int i = 0; i < n; i++) printf("%d%d ", t[i].A, t[i].B);
	putchar('\n');
	printf("--------------------------\n");
	return;
}

inline void init(void) {
	s0[0] = t0[0] = s1[0] = t1[0] = 0;
	for (int i = 0; i < n; i++) {
		if (i > 0) {
			s0[i] = s0[i - 1];
			s1[i] = s1[i - 1];
			t0[i] = t0[i - 1];
			t1[i] = t1[i - 1];
		}
		if (s[i].A == 0 && s[i].B == 1) s0[i]++;
		if (s[i].A == 1 && s[i].B == 0) s1[i]++;
		if (t[i].A == 0 && t[i].B == 1) t0[i]++;
		if (t[i].A == 1 && t[i].B == 0) t1[i]++;
	}
	return;
}

inline void rev(void) {
	if (s0[n - 1] == t0[n - 1]) return;
	for (int i = 0; i < n; i++) {
		if (s0[n - 1] - s0[i] + s1[i] == t0[n - 1]) {
			reverseS(i);
			return;
		}
		if (s0[n - 1] == t0[n - 1] - t0[i] + t1[i]) {
			reverseT(v = i);
			return;
		}
		for (int j = 0; j < n; j++)
			if (s0[n - 1] - s0[i] + s1[i] == t0[n - 1] - t0[j] + t1[j]) {
				reverseS(i);
				reverseT(v = j);
				return;
			}
	}
}
inline int find(int x) {
	for (int i = x; i < n; i++)
		if (s[i].A == t[x].A && s[i].B == t[x].B) return i;
	return -1;
}

void solve(void) {
	n = m = 0;
	q = v = -1;
	memset(cnt, 0, sizeof(cnt));
	read();
	for (int i = 0; i < n; i++) {
		cnt[s[i].A * 2 + s[i].B]++;
		cnt[t[i].A * 2 + t[i].B + 4]++;
	}
	if (cnt[0] != cnt[4] || cnt[3] != cnt[7] || cnt[1] + cnt[2] != cnt[5] + cnt[6]) {
		printf("-1\n");
		return;
	}
	init();
	rev();
	for (int i = 0; i < n; i++) {
		int t = find(i);
		if (t > 0) reverseS(t - 1);
		if (i != n - 1) reverseS(t);
	}
	if (v != -1) {
		reverseS(v);
		reverseT(v);
	}
	printf("%d\n", q + 1);
	for (int i = 0; i <= q; i++) printf("%d ", ans[i]);
	putchar('\n');
	return;
}

int main(void) {
	int T;
	scanf("%d", &T);
	while (T--) solve();
	return 0;
}