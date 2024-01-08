// Skyqwq
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second
#define mp make_pair

using namespace std;

typedef pair<int, int> PII;
typedef long long LL;

template <typename T> bool chkMax(T &x, T y) { return (y > x) ? x = y, 1 : 0; }
template <typename T> bool chkMin(T &x, T y) { return (y < x) ? x = y, 1 : 0; }

template <typename T> void inline read(T &x) {
    int f = 1; x = 0; char s = getchar();
    while (s < '0' || s > '9') { if (s == '-') f = -1; s = getchar(); }
    while (s <= '9' && s >= '0') x = x * 10 + (s ^ 48), s = getchar();
    x *= f;
}

const int N = 2e6 + 5;

int n, tn;

char str[N];

int a[N], V = -1;

bool st[N];

int c[N];

priority_queue<int, vector<int>, greater<int> > q[N];

int cnt[N], b[N];

int C[N];

void add(int x, int k) {
	for (; x <= n; x += x & -x) C[x] += k;
}

int ask(int x) {
	int ret = 0;
	for (; x; x -= x & -x) ret += C[x];
	return ret;
}

int kth(int k) {
	int p = 0;
	int now = 0;
	for (int i = 19; i >= 0; i--) {
		if ((p | (1 << i)) <= n && now + C[p | (1 << i)] < k) {
			p |= 1 << i;
			now += C[p];
		}
	}

	return p + 1;
}

int sum = 0;

int nxt(int x) {
	int now = ask(x);
	if (now == sum) return -1;
	return kth(now + 1);
}

int pre(int x) {
	int now = ask(x);
	if (now == 1) return -1;
	return kth(now - 1);
}



void rebuild() {
	int tot = 0;
	if ((tot = ask(n)) > 0)  {
		for (int i = 1; i <= tot; i++) {
			int loc = kth(i);
			//cout << loc << " awa" << i << "kt\n";
			b[i] = a[loc];
		}
	}

	for (int i = 1; i <= tot; i++) a[i] = b[i], c[i] = -1;
	n = tot;
	for (int i = 1; i <= n; i++) C[i] = 0;
	for (int i = 1; i <= n; i++) add(i, 1);
	for (int i = 1; i <= tn; i++) {
		cnt[i] = 0;
		while (!q[i].empty()) q[i].pop();
	}

	
	int w = 0;
	for (int i = n; i; i--) {
		//cout << i << "??" << V << "??\n";
		if (i + V <= n) {
			if (i + V + 1 <= n) w >>= 1;
			w |= (a[i] << V);
			c[i] = w;
			cnt[c[i]]++;
			//cout << i << " ??? " << w << " awa " << (a[i]) << "..." << V << "??" << (a[i] << V) << endl;
			q[w].push(i);
		} else {
			int loc = n - i;
			//cout << i << "---" << a[i] << endl;
			w |= (a[i] << loc);
		}
	}
}

int t1, t2, A[N], B[N];

int X[N], t3;

void del2(int u) {
	cnt[c[u]]--;
	c[u] = -1;
	add(u, -1); sum--;
}

void del(int u) {
	//cout << u << " del\n";
	cnt[c[u]]--;
	c[u] = -1;
	t1 = t2 = 0;
	int it = u;

	for (int i = 1; i <= V; i++) {
		it = nxt(it);
		if (it == -1) break;
		B[++t2] = it;
	}

	it = u;

	for (int i = 1; i <= V; i++) {
		it = pre(it);
		if (it == -1) break;
		A[++t1] = it;
	}


	t3 = 0;
	for (int i = t1; i >= 1; i--) X[++t3] = A[i];
	for (int i = 1; i <= t2; i++) X[++t3] = B[i];
	int w = 0;
	for (int j = t3; j; j--) {
		int i = X[j];
		if (j + V <= t3) {
			if (j + V + 1 <= t3) w >>= 1;
			w |= (a[i] << V);

			
		} else {
			int loc = t3 - j;
			w |= (a[i] << loc);
			
		}
		if (j <= t1) {
			if (j + V <= t3) {
				if (~c[i]) cnt[c[i]]--;
				c[i] = w;
				//cout << " rem " << i << "is" << w << "???" << endl;
				cnt[c[i]]++;
				q[w].push(i);
				
			} else {
				int loc = t3 - j;
				w |= (a[i] << loc);
				if (~c[i]) {
					cnt[c[i]]--;
					c[i] = -1;
				}
			}
		}
	}

	add(u, -1); sum--;
//	cout << "...\n";
//	cout << kth(2) << "??" << ask(2) << endl;
//	cout << "cnt----" << cnt[6] << endl;
}

void sv(int x) {
	//cout << "sv" << x << "\n";
	if (cnt[x] == 0) {
		puts("-1 0");
		return;
	}
	while (!q[x].empty()) {
		int u = q[x].top(); q[x].pop();
		if (c[u] != x) continue;
		printf("%d %d\n", ask(u), cnt[x]);

		int it = u;
		vector<int> Z;
		for (int i = 0; i <= V; i++) {
			assert (it != -1) ;
			Z.pb(it);
			it = nxt(it);
		}
		for (int i = 1; i < Z.size(); i++) del2(Z[i]);
		del(Z[0]);
		return;
	}
	
}

int main() {
   	read(n); tn = n; sum = n;
   	scanf("%s", str + 1);
   	for (int i = 1; i <= n; i++) a[i] = str[i] - '0', add(i, 1);
   	

   	for (int i = 1; i <= tn; i++) {
   		int h = 0;
   		for (int j = 0; j < 20; j++)
   			if (i >> j & 1) h = j;
   		if (V != h) {
   			
   			V = h;
   			//cout << i << " " << V << " remake\n";
   			rebuild();
   		}

   		sv(i);
   	
   	}
    return 0;
}